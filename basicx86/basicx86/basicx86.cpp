// basicx86.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>


extern "C" int CalcSum_(int a, int b, int c);

int test_CalcSum()
{
	int a = 17, b = 11, c = 14;
	int sum = CalcSum_(a, b, c);

	printf("  a:   %d\n", a);
	printf("  b:   %d\n", b);
	printf("  c:   %d\n", c);
	printf("  sum: %d\n", sum);
	return 0;
}

extern "C" int IntegerMulDiv_(int a, int b, int* prod, int* quo, int* rem);

int test_IntegerMulDiv()
{
	int a = 21, b = 9;
	int prod = 0, quo = 0, rem = 0;
	int rc;

	rc = IntegerMulDiv_(a, b, &prod, &quo, &rem);
	printf(" Input1 - a:   %4d  b:    %4d\n", a, b);
	printf("Output1 - rc:  %4d  prod: %4d\n", rc, prod);
	printf("          quo: %4d  rem:  %4d\n\n", quo, rem);

	a = -29;
	prod = quo = rem = 0;
	rc = IntegerMulDiv_(a, b, &prod, &quo, &rem);
	printf(" Input2 - a:   %4d  b:    %4d\n", a, b);
	printf("Output2 - rc:  %4d  prod: %4d\n", rc, prod);
	printf("          quo: %4d  rem:  %4d\n\n", quo, rem);

	b = 0;
	prod = quo = rem = 0;
	rc = IntegerMulDiv_(a, b, &prod, &quo, &rem);
	printf(" Input3 - a:   %4d  b:    %4d\n", a, b);
	printf("Output3 - rc:  %4d  prod: %4d\n", rc, prod);
	printf("          quo: %4d  rem:  %4d\n\n", quo, rem);
	return 0;
}


// The function PrintResults is defined in CalcMatrixRowColSumsMisc.cpp
void PrintResults(const int* x, int nrows, int ncols, int* row_sums, int* col_sums)
{
	for (int i = 0; i < nrows; i++)
	{
		for (int j = 0; j < ncols; j++)
			printf("%5d ", x[i* ncols + j]);
		printf(" -- %5d\n", row_sums[i]);
	}
	printf("\n");

	for (int i = 0; i < ncols; i++)
		printf("%5d ", col_sums[i]);
	printf("\n");
}

extern "C" int CalcMatrixRowColSums_(const int* x, int nrows, int ncols, int* row_sums, int* col_sums);

void CalcMatrixRowColSumsCpp(const int* x, int nrows, int ncols, int* row_sums, int* col_sums)
{
	for (int j = 0; j < ncols; j++)
		col_sums[j] = 0;

	for (int i = 0; i < nrows; i++)
	{
		row_sums[i] = 0;
		int k = i * ncols;

		for (int j = 0; j < ncols; j++)
		{
			int temp = x[k + j];
			row_sums[i] += temp;
			col_sums[j] += temp;
		}
	}
}

int test_CalcMatrixRowColSums()
{
	const int nrows = 7, ncols = 5;
	int x[nrows][ncols];

	// Initialize the test matrix
	srand(13);
	for (int i = 0; i < nrows; i++)
	{
		for (int j = 0; j < ncols; j++)
			x[i][j] = rand() % 100;
	}

	// Calculate the row and column sums
	int row_sums1[nrows], col_sums1[ncols];
	int row_sums2[nrows], col_sums2[ncols];

	CalcMatrixRowColSumsCpp((const int*)x, nrows, ncols, row_sums1, col_sums1);
	printf("\nResults using CalcMatrixRowColSumsCpp()\n");
	PrintResults((const int*)x, nrows, ncols, row_sums1, col_sums1);

	CalcMatrixRowColSums_((const int*)x, nrows, ncols, row_sums2, col_sums2);
	printf("\nResults using CalcMatrixRowColSums_()\n");
	PrintResults((const int*)x, nrows, ncols, row_sums2, col_sums2);

	return 0;
}

#include "TestStruct.h"

extern "C" __int64 CalcStructSum_(const TestStruct* ts);

__int64 CalcStructSumCpp(const TestStruct* ts)
{
	return ts->Val8 + ts->Val16 + ts->Val32 + ts->Val64;
}

int test_CalcStructSum()
{
	TestStruct ts;

	ts.Val8 = -100;
	ts.Val16 = 2000;
	ts.Val32 = -300000;
	ts.Val64 = 40000000000;

	__int64 sum1 = CalcStructSumCpp(&ts);
	__int64 sum2 = CalcStructSum_(&ts);

	printf("Input: %d  %d  %d  %lld\n", ts.Val8, ts.Val16, ts.Val32, ts.Val64);
	printf("sum1:  %lld\n", sum1);
	printf("sum2:  %lld\n", sum2);

	if (sum1 != sum2)
		printf("Sum verify check failed!\n");

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//test_CalcSum();
	//test_IntegerMulDiv();
	//test_CalcMatrixRowColSums();
	test_CalcStructSum();
	return 0;
}
