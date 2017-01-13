/*
 *
 *
 *  Copyright (c) 2016 PEZY Computing, K.K.
 */

#include "../common/pzclutil.h" // PZCL utilities

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <string.h>
#include <string>

///////////////////////////////////////////////////////////////
void FillRandData( float* pData, size_t count )
{
	const float fRandMax = RAND_MAX;
	for( size_t i = 0; i < count; i++)
	{
		pData[i] = rand() / fRandMax;
	}
}

///////////////////////////////////////////////////////////////
void ComputeAdd_CPU( const float* a, const float* b, float* c, size_t count )
{
	for( size_t i = 0; i < count; i++)
	{
		c[i] = a[i] + b[i];
	}
}

bool Compare( const float* pExp, const float* pValue, size_t count )
{
	//  compare result
	int err_count = 0;
	for( size_t i = 0; i < count; i++)
	{
		if( fabs( pExp[i] - pValue[i]) > 1e-8 )
		{
			if(err_count < 32)
			{
				printf("ADDR:0x%08X, DATA:%f EXPECTED:%f\n", i, pValue[i], pExp[i]);
			}
			++err_count;
		}
	}
	if(err_count)
	{
		printf(" ERROR %d / %d\n", err_count, count);
	}
	return (err_count==0);
}


//////////////////////////////////////////////////////////////////
bool ComputeAdd2D_PZ(
		cl_kernel        kernel,
		cl_command_queue command_queue,
		cl_mem           memA,
		cl_mem           memB,
		cl_mem           memC,
		float            *pDstC,
		size_t           row_count,
		size_t           column_count
	)
{
	cl_int result;
	{
		// Setup Kernel argument
		std::vector<PZCLUtil::KernelArg> vArg;
		int m = row_count;
		int n = column_count;
		vArg.push_back( PZCLUtil::KernelArg(  sizeof(cl_mem), (void*)&memA ) ); // ARG0
		vArg.push_back( PZCLUtil::KernelArg(  sizeof(cl_mem), (void*)&memB ) ); // ARG1
		vArg.push_back( PZCLUtil::KernelArg(  sizeof(cl_mem), (void*)&memC ) ); // ARG2
		vArg.push_back( PZCLUtil::KernelArg(  sizeof(int)   , (void*)&m) ); // ARG3
		vArg.push_back( PZCLUtil::KernelArg(  sizeof(int)   , (void*)&n) ); // ARG4
		
		
		if( (result = PZCLUtil::SetKernelArgs( kernel, vArg) ) != CL_SUCCESS)
		{
			printf("PZCLUtil::SetKernelArgs failed, %d", result);
			return false;
		}
	}
	int count = row_count * column_count;
	// global_work_size must be multiple of 128.
	size_t global_work_size = PZSDK_RoundUpMultipleOfN(count, 8192);

	if( (result = clEnqueueNDRangeKernel(command_queue, kernel, 1 /* must be 1D*/, NULL, &global_work_size, NULL, 0, NULL, NULL ) ) != CL_SUCCESS )
	{
		printf("clEnqueueNDRangeKernel failed, %d", result);
			return false;
	}

	{
		// Read from device memory
		size_t size = count * sizeof(float);
		result = clEnqueueReadBuffer( command_queue, memC, CL_TRUE, 0, size, pDstC, 0, NULL, NULL); 
		if( result != CL_SUCCESS)
		{
			printf("clEnqueueReadBuffer failed %d\n", result);
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
int main( int argc, char* argv[])
{
	cl_platform_id platform_id = NULL;
	cl_uint numPlatforms = 0;
	cl_program program = NULL;
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_kernel kernel = NULL;
	cl_mem memA = NULL;
	cl_mem memB = NULL;
	cl_mem memC = NULL;

	cl_int result = 0;
	
	size_t row_count = 64;
	size_t column_count = 128;
	size_t count = row_count * column_count;
	size_t size  = count * sizeof(float);

	float *pSrcA = new float[ count ];
	float *pSrcB = new float[ count ];
	float *pDstC = new float[ count ];
	float *pCPURef = new float[ count ];


	const char* bin_name = "./kernel.sc1/kernel.pz";

	printf("%s\n", bin_name);

	if(pSrcA == NULL || pSrcB == NULL || pDstC == NULL || pCPURef == NULL)
	{
		printf("out of host memory\n");
		goto leaving;
	}

	{
		// Fill Host memory
		FillRandData(pSrcA, count );
		FillRandData(pSrcB, count );

		memset(pDstC  , 0, size);
		memset(pCPURef, 0, size);
	}

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
	if( (command_queue = clCreateCommandQueue( context, device_id, 0, &result)) == NULL)
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

	if( (kernel = clCreateKernel(program, "Add2D", &result)) == NULL)
	{
		printf("clCreateKernel failed, %d\n", result);
		goto leaving;
	}

	{
		// Create Device Memory object
		memA = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &result );
		if( memA == NULL)
		{
			printf("clCreateBuffer failed, %d", result);
			goto leaving;
		}

		memB = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &result );
		if( memB == NULL)
		{
			printf("clCreateBuffer failed, %d", result);
			goto leaving;
		}

		memC = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &result );
		if( memC == NULL)
		{
			printf("clCreateBuffer failed, %d", result);
			goto leaving;
		}
	}

	{
		// Write to Device Memory
		result = clEnqueueWriteBuffer ( command_queue, memA,  CL_TRUE, 0, size, pSrcA, 0, NULL, NULL); 
		if( result != CL_SUCCESS)
		{
			printf("clEnqueueWriteBuffer failed %d\n", result);
			goto leaving;
		}

		result = clEnqueueWriteBuffer ( command_queue, memB,  CL_TRUE, 0, size, pSrcB, 0, NULL, NULL); 
		if( result != CL_SUCCESS)
		{
			printf("clEnqueueWriteBuffer failed %d\n", result);
			goto leaving;
		}

	}

	if( !ComputeAdd2D_PZ(kernel, command_queue, memA, memB, memC, pDstC, row_count, column_count))
	{
		goto leaving;
	}

	// Compute by CPU
	ComputeAdd_CPU( pSrcA, pSrcB, pCPURef, count );
	
	{
		printf("Comparing CPU and PEZY\n");
		if( Compare( pCPURef, pDstC, count ) )
		{
			printf("PASS\n");
		}
	}

	//////////////////////////////////////////////////////////////////
leaving:
	if( kernel )
	{
		if((result = clReleaseKernel(kernel)) != CL_SUCCESS)
		{
			printf("clReleaseKernel failed %d\n", result);
		}
	}

	if( program )
	{
		if( (result = clReleaseProgram(program) ) != CL_SUCCESS)
		{
			printf("clReleaseProgram failed %d\n", result);
		}
	}

	if( memA )
	{
		if( (result = clReleaseMemObject(memA)) != CL_SUCCESS )
		{
			printf("clReleaseMemObject failed %d\n", result);
		}
	}

	if( memB )
	{
		if( (result = clReleaseMemObject(memB)) != CL_SUCCESS )
		{
			printf("clReleaseMemObject failed %d\n", result);
		}
	}

	if( memC )
	{
		if( (result = clReleaseMemObject(memC)) != CL_SUCCESS )
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

	if( pSrcA ) delete [] pSrcA;
	if( pSrcB ) delete [] pSrcB;
	if( pDstC ) delete [] pDstC;

	if( pCPURef ) delete [] pCPURef;

	return 0;
}
