/*
 * 
 *
 *	Copyright (c) 2016 PEZY Computing, K.K.
 */

#include "../common/pzclutil.h" // PZCL utilities

#include <string.h>

/**
 * NOTE:
 *  For using EventProfiling muset set CL_QUEUE_PROFILING_ENABLE at clCreateCommandQueue
 * 
 */
cl_ulong getTime( cl_event event )
{
	cl_ulong start = 0;
	cl_ulong end   = 0;

	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END,   sizeof(cl_ulong), &end,   NULL);

	return (end - start);
}

int main( int argc, char* argv[])
{
	cl_platform_id platform_id = NULL;
	cl_uint numPlatforms = 0;
	cl_program program = NULL;
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_kernel kernel = NULL;
	cl_int result = CL_SUCCESS;
	cl_mem mem = NULL;

	int width = 1024;
	int height = 4096;
	int count = width*height;
	int size = count * sizeof(int);

	int* pHost = new int [ count ];

	const char* bin_name = "./kernel.sc1/kernel.pz";

	if( pHost == NULL )
	{
		printf("out of memory");
		goto leaving;
	}

	memset(pHost, 0, size);

	// Get Platform IDs
	if ((result = clGetPlatformIDs(1, &platform_id, &numPlatforms)) != CL_SUCCESS)
	{
		printf("clGetPlatformIDs() failed : %dn", result);
		goto leaving;
	}
	
	// Get Device ID
	cl_uint numDevices;
	if ((result = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &numDevices)) != CL_SUCCESS)
	{
		printf("clGetDeviceIDs() failed : %d\n", result);
		goto leaving;
	}

	// Create Context
	if( (context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &result)) == NULL )
	{
		printf("Create context failed %d\n", result);
		goto leaving;
	}

	// Create Command Queue
	// Set CL_QUEUE_PROFILING_ENABLE
	if( (command_queue = clCreateCommandQueue( context, device_id, CL_QUEUE_PROFILING_ENABLE, &result)) == NULL)
	{
		printf("clCreateCommandQueue failed, %d", result);
		goto leaving;
	}

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
	}

	if( (kernel = clCreateKernel(program, "Fill2D", &result)) == NULL)
	{
		printf("clCreateKernel failed, %d\n", result);
		goto leaving;
	}

	{
		// Create Device Memory object
		mem = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &result );
		if( mem == NULL)
		{
			printf("clCreateBuffer failed, %d", result);
			goto leaving;
		}
	}	

	{
		int clrValue = 1;
		// clear memory
		if((result = clEnqueueFillBuffer( command_queue, mem, &clrValue, sizeof(int), 0, size, 0, NULL, NULL)) != CL_SUCCESS)
		{
			printf("clEnqueueFillBuffer failed, %d", result);
			goto leaving;
		}
	}

	{
		// Setup arguments
		std::vector<PZCLUtil::KernelArg> vArg;
		int iCount = count;

		vArg.push_back( PZCLUtil::KernelArg(  sizeof(cl_mem), (void*)&mem ) ); // ARG0
		vArg.push_back( PZCLUtil::KernelArg(  sizeof(int)   , (void*)&width) ); // ARG1
		vArg.push_back( PZCLUtil::KernelArg(  sizeof(int)   , (void*)&height) ); // ARG2
		
		if( (result = PZCLUtil::SetKernelArgs( kernel, vArg) ) != CL_SUCCESS)
		{
			printf("PZCLUtil::SetKernelArgs failed, %d", result);
			return false;
		}
	}


	clFinish(command_queue);
	{
		size_t global_work_size = 8192;
		size_t local_work_size  = global_work_size;

		cl_event event = NULL;
		if( (result = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_work_size, &local_work_size, 0, NULL, &event ) ) != CL_SUCCESS )
		{
			printf("clEnqueueNDRangeKernel failed, %d", result);
			goto leaving;
		}

		if( event )
		{
			clFinish( command_queue );
			double usec = getTime( event ) / 1000.0;
			printf("Exec      :%10.3f [us]\n", usec);
		}


		if( event )
		{
			if((result = clReleaseEvent(event)) != CL_SUCCESS)
			{
				printf("clReleaseEvent failed %d\n", result);
			}
		}
	}

	{
		
		cl_event event = NULL;
		size_t size = count * sizeof(int);
		result = clEnqueueReadBuffer( command_queue, mem, CL_TRUE, 0, size, pHost, 0, NULL, &event); 
		if( result != CL_SUCCESS)
		{
			printf("clEnqueueReadBuffer failed %d\n", result);
			return false;
		}

		if( event )
		{
			clFinish( command_queue );
			double usec = getTime( event ) / 1000.0;
			printf("ReadBuffer:%10.3f [us] (%6.1f MB/sec)\n", usec, size*1000000.0/usec/1000.0/1000.0);
		}

		if( event )
		{
			if((result = clReleaseEvent(event)) != CL_SUCCESS)
			{
				printf("clReleaseEvent failed %d\n", result);
			}
		}
	}

	{
		int error=0;
		// Compare
		for( int y = 0; y < height; y++)
		{
			int* pLine = &pHost[y*width];
			for(int x = 0; x < width; x++)
			{
				int expected = ((y & 0xFFFF)<<16) | (x & 0xFFFF);
				int data = pLine[x];

				if(expected != data)
				{
					if(error < 32 )
					{
						printf("x:%d y:%d DATA=%08X EXPECTED:%08X\n", x, y, data, expected);
					}
					++error;
				}
			}
		}

		if(error)
		{
			printf("error = %d", error);
		}
	}

leaving:
	if( mem )
	{
		if( (result = clReleaseMemObject(mem)) != CL_SUCCESS )
		{
			printf("clReleaseMemObject failed %d\n", result);
		}
	}


	if( command_queue )
	{
		if( (result = clReleaseCommandQueue(command_queue)) != CL_SUCCESS )
		{
			printf("Release command queue failed %d\n", result);
		}
	}

	if(context)
	{
		if( (result = clReleaseContext(context)) != CL_SUCCESS )
		{
			printf("Release context failed %d\n", result);
		}
	}

	if(pHost) delete [] pHost;

	return 0;
}




