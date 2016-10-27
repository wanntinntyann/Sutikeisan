/*
 * 	Multi-Device 
 *
 *	Copyright (c) 2016 PEZY Computing, K.K.
 */

#include "../common/pzclutil.h" // PZCL utilities

///////////////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[])
{
	cl_platform_id                platform_id = NULL;
	cl_uint                       numDevices = 0;
	std::vector<cl_device_id>     vDeviceIDs;
	std::vector<cl_context>       vContexts;
	std::vector<cl_command_queue> vCommandQueues;
	std::vector<cl_program>       vPrograms;
	std::vector<cl_kernel>        vKernels;
	std::vector<cl_mem>           vBuffers;
	unsigned int*                 pHost = NULL;

	size_t  count = 8192;
	size_t  size  = sizeof(unsigned int) * count;

	cl_int result = CL_SUCCESS;

	const char* bin_name = "kernel.sc1/kernel.pz";

	printf("%s\n", bin_name );

	{
		// Get Platform IDs
	    if ((result = clGetPlatformIDs(1, &platform_id, NULL)) != CL_SUCCESS)
		{
	        printf("clGetPlatformIDs() failed : %dn", result);
			goto leaving;
	    }
	}
	
	{
		// Query the number of device.
	    if ((result = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 0, NULL, &numDevices)) != CL_SUCCESS)
		{
			printf("clGetDeviceIDs() failed : %d\n", result);
			goto leaving;
	    }
	   
		printf("Number of devices = %d\n", numDevices);
 
	    vDeviceIDs.resize(numDevices);
	    
	    // Obtain the list of cl_device_id
	    if ((result = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, numDevices, &vDeviceIDs[0], NULL)) != CL_SUCCESS)
		{
			printf("clGetDeviceIDs() failed : %d\n", result);
			goto leaving;
	    }
	}
	
	{
		// Init Per device object
		for( cl_uint i = 0; i < numDevices; i++)
		{
			cl_device_id     device_id     = vDeviceIDs[i];
			cl_context       context       = NULL;
			cl_command_queue command_queue = NULL;
			cl_program       program       = NULL;
			cl_kernel        kernel        = NULL;
			cl_mem           buffer        = NULL;

			const unsigned int clrValue    = 0xFFFFFFFF;

			// Create Context
			if( (context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &result)) == NULL )
			{
				printf("Create context failed %d\n", result);
				goto leaving;
			}
			
			vContexts.push_back(context);

			// Create Command Queue
			if( (command_queue = clCreateCommandQueue( context, device_id, 0, &result)) == NULL)
			{
				printf("clCreateCommandQueue failed, %d", result);
				goto leaving;
			}
			vCommandQueues.push_back(command_queue);

			{
				// Create program object
				std::vector<cl_device_id> device_id_lists;
				device_id_lists.push_back( device_id );
				program = PZCLUtil::CreateProgram( context, device_id_lists, bin_name );
				if(program == NULL)
				{
					printf("clCreateProgramWithBinary failed, %d\n", result);
					goto leaving;
				}
				
				vPrograms.push_back(program);
			}
			
			// Create kernel object
			if( (kernel = clCreateKernel(program, "Fill", &result)) == NULL)
			{
				printf("clCreateKernel failed, %d\n", result);
				goto leaving;
			}
			vKernels.push_back(kernel);
			
			if((buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &result)) == NULL)
			{
				printf("clCreateBuffer failed, %d\n", result);
				goto leaving;
			}
			vBuffers.push_back(buffer);
		
			if( ( result = clEnqueueFillBuffer(command_queue, buffer, &clrValue, sizeof(unsigned int), 0, size, 0, NULL, NULL)) != CL_SUCCESS )
			{
				printf("pzclEnqueueFillBuffer failed, %d\n", result);
				goto leaving;
			}
		}
	}
	
	{
		// Exec Kernel
		for( cl_uint i = 0; i < numDevices; i++)
		{
			cl_context       context       = vContexts[i];
			cl_command_queue command_queue = vCommandQueues[i];
			cl_kernel        kernel        = vKernels[i];
			cl_mem           buffer        = vBuffers[i];


			{
				// Setup Kernel argument
				std::vector<PZCLUtil::KernelArg> vArg;
				int iCount = (int)count;
				int value = (int)i;	

				vArg.push_back( PZCLUtil::KernelArg( sizeof(cl_mem), (void*)&buffer ) ); // ARG0
				vArg.push_back( PZCLUtil::KernelArg( sizeof(int)   , (void*)&value ) );  // ARG1
				vArg.push_back( PZCLUtil::KernelArg( sizeof(int)   , (void*)&iCount ) ); // ARG2
		
				if( (result = PZCLUtil::SetKernelArgs( kernel, vArg) ) != CL_SUCCESS)
				{
					printf("PZCLUtil::SetKernelArgs failed, %d", result);
					goto leaving;
				}
			}

			size_t global_work_size = PZSDK_RoundUpMultipleOfN(count, 128);

			if( (result = clEnqueueNDRangeKernel(command_queue, kernel, 1 /* must be 1D*/, NULL, &global_work_size, NULL, 0, NULL, NULL ) ) != CL_SUCCESS )
			{
				printf("clEnqueueNDRangeKernel failed, %d", result);
				goto leaving;
			}
		}
	}
	
	{
		// Alloc host mem
		pHost = new unsigned int[count];
		if( pHost == NULL )
		{
			printf("out of host memory");
			goto leaving;
		}
	}
	
	
	{
		// Check Result	
		for( cl_uint i = 0; i < numDevices; i++)
		{
			cl_context       context       = vContexts[i];
			cl_command_queue command_queue = vCommandQueues[i];
			cl_mem           buffer        = vBuffers[i];

			if((result = clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0, size, pHost, 0, NULL, NULL)))
			{
				printf("clEnqueueReadBuffer failed, %d", result);
				goto leaving;
			}
		
			// compare
			unsigned int expValue = i;
			size_t errCount = 0;
			for( size_t j = 0; j < count; j++)
			{
				if( expValue != pHost[j])
				{
					if( errCount < 32 )
					{
						printf("%d:%08X DATA:%08X EXP:%08X\n", (int)i, (int)(j*sizeof(cl_uint)), pHost[j], expValue);
					}
					++errCount;
				}
			}
			if(errCount)
			{
				printf("ERROR deviceId = %d %d / %d (%.3f %%)\n", i, errCount, count, errCount * 100.f / count);
			} else {
				printf("PASSED deviceId = %d\n", i);
			}
		}
	}


leaving:
	//-----------------------------------------
	//	Finalize
	//-------------------------------------------
	if( pHost )
	{
		delete [] pHost;
	}

	{
		std::vector<cl_mem>::iterator it = vBuffers.begin();
		while(it != vBuffers.end())
		{
			clReleaseMemObject((*it));
			++it;
		}
	}


	{
		std::vector<cl_kernel>::iterator it = vKernels.begin();
		while(it != vKernels.end())
		{
			clReleaseKernel( *it );
			++it;
		}
	}
	{
		std::vector<cl_program>::iterator it = vPrograms.begin();
		while(it != vPrograms.end())
		{
			clReleaseProgram( *it);
			++it;
		}
	}


	{
		std::vector<cl_command_queue>::iterator it = vCommandQueues.begin();
		while(it != vCommandQueues.end())
		{
			if( (result = clReleaseCommandQueue((*it))) != CL_SUCCESS )
			{
				printf("Release command queue failed %d\n", result);
			}
			++it;
		}
	}


	{
		std::vector<cl_context>::iterator it = vContexts.begin();
		while( it != vContexts.end() )
		{
			if( (result = clReleaseContext( (*it) )) != CL_SUCCESS )
			{
				printf("Release context failed %d\n", result);
			}
			++it;
		}
	}

	return 0;
}
