/*
 * 
 *
 *	Copyright (c) 2016 PEZY Computing, K.K.
 */

#include "../common/pzclutil.h" // PZCL utilities

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <string.h>
#include <string>

///////////////////////////////////////////////////////////////
void FillRandData( float** pData, int row, int col )
{
	const float fRandMax = RAND_MAX;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			pData[i] = rand() / fRandMax;
		}
	}
}

float **make_matrix(int row, int col)
{
	float **a;

	a = new float*[row];

	for(int i = 0; i < col; i++){
		a[i] = new float[col];
	}

	return a;
}

void del_matrix(float **a, int row, int col)
{
	for(int i = 0; i < row; i++){
		delete a[i];
	}

	delete a;
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
bool ComputeAdd_PZ(
    cl_kernel        kernel,
    cl_command_queue command_queue,
	cl_mem           *memA,
	cl_mem           *memB,
	cl_mem           *memC,
	float            **pDstC,
	size_t           count
	)
{
	cl_int result;
	{
		// Setup Kernel argument
		std::vector<PZCLUtil::KernelArg> vArg;
		int iCount = count;

		vArg.push_back( PZCLUtil::KernelArg(  sizeof(cl_mem), (void*)&memA ) ); // ARG0
		vArg.push_back( PZCLUtil::KernelArg(  sizeof(cl_mem), (void*)&memB ) ); // ARG1
		vArg.push_back( PZCLUtil::KernelArg(  sizeof(cl_mem), (void*)&memC ) ); // ARG2
		vArg.push_back( PZCLUtil::KernelArg(  sizeof(int)   , (void*)&iCount) ); // ARG3
		
		
		if( (result = PZCLUtil::SetKernelArgs( kernel, vArg) ) != CL_SUCCESS)
		{
			printf("PZCLUtil::SetKernelArgs failed, %d", result);
			return false;
		}
	}

	// global_work_size must be multiple of 128.
	size_t global_work_size = PZSDK_RoundUpMultipleOfN(count, 128);

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
	cl_mem *memA = NULL;
	cl_mem *memB = NULL;
	cl_mem *memC = NULL;

    cl_int result = 0;
	
	int row = 50;
	int col = 50;
	size_t size  = row * col * sizeof(float);

	memA = new cl_mem[count];
	memB = new cl_mem[count];
	memC = new cl_mem[count];

	float **pSrcA = make_matrix(row, col);
	float **pSrcB = make_matrix(row, col);
	float **pDstC = make_matrix(row, col);
	float **pCPURef = make_matrix(row, col);


	const char* bin_name = "./kernel.sc1/kernel.pz";

	printf("%s\n", bin_name);

	if(pSrcA == NULL || pSrcB == NULL || pDstC == NULL || pCPURef == NULL)
	{
		printf("out of host memory\n");
		goto leaving;
	}

	{
		// Fill Host memory
		FillRandData(pSrcA, row, col );
		FillRandData(pSrcB, row, col );
		FillRandData(pSrcC, row, col );

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

	if( (kernel = clCreateKernel(program, "Add", &result)) == NULL)
	{
		printf("clCreateKernel failed, %d\n", result);
		goto leaving;
	}

	{
		// Create Device Memory object
		for(int i = 0; i < row; i++){
			memA[i] = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &result );
			if( memA == NULL)
			{
				printf("clCreateBuffer failed, %d", result);
				goto leaving;
			}

			memB[i] = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &result );
			if( memB == NULL)
			{
				printf("clCreateBuffer failed, %d", result);
				goto leaving;
			}

			memC[i] = clCreateBuffer(context, CL_MEM_READ_WRITE, size, NULL, &result );
			if( memC == NULL)
			{
				printf("clCreateBuffer failed, %d", result);
				goto leaving;
			}
		}
	}

	{
		for(int i = 0; i < row; i++){
			// Write to Device Memory
			result = clEnqueueWriteBuffer ( command_queue, memA[i],  CL_TRUE, 0, size, pSrcA[i], 0, NULL, NULL); 
			if( result != CL_SUCCESS)
			{
				printf("clEnqueueWriteBuffer failed %d\n", result);
				goto leaving;
			}

			result = clEnqueueWriteBuffer ( command_queue, memB[i],  CL_TRUE, 0, size, pSrcB[i], 0, NULL, NULL); 
			if( result != CL_SUCCESS)
			{
				printf("clEnqueueWriteBuffer failed %d\n", result);
				goto leaving;
			}
		}

	}

	if( !ComputeAdd_PZ(kernel, command_queue, memA, memB, memC, pDstC, count))
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

	if( pSrcA ) del_matrix(pSrcA, row);
	if( pSrcB ) del_matrix(pSrcB, row);
	if( pDstC ) del_matrix(pSrcC, row);
	if( pCPURef ) del_matrix(pCPURef, row);

	return 0;
}
