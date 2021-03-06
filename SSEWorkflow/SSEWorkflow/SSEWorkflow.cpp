#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>

extern "C" void SseSfpArithmeticFloat_(float a, float b, float c[8]);
extern "C" void SseSfpArithmeticDouble_(double a, double b, double c[8]);

void SseSpfArithmeticFloat(void)
{
	float a = 2.5f;
	float b = -7.625f;
	float c[8];

	SseSfpArithmeticFloat_(a, b, c);
	printf("\nResults for SseSfpArithmeticFloat_()\n");
	printf("  a:             %.6f\n", a);
	printf("  b:             %.6f\n", b);
	printf("  add:           %.6f\n", c[0]);
	printf("  sub:           %.6f\n", c[1]);
	printf("  mul:           %.6f\n", c[2]);
	printf("  div:           %.6f\n", c[3]);
	printf("  min:           %.6f\n", c[4]);
	printf("  max:           %.6f\n", c[5]);
	printf("  fabs(b):       %.6f\n", c[6]);
	printf("  sqrt(fabs(b)): %.6f\n", c[7]);
}

void SseSpfArithmeticDouble(void)
{
	double a = M_PI;
	double b = M_E;
	double c[8];

	SseSfpArithmeticDouble_(a, b, c);
	printf("\nResults for SseSfpArithmeticDouble_()\n");
	printf("  a:             %.14f\n", a);
	printf("  b:             %.14f\n", b);
	printf("  add:           %.14f\n", c[0]);
	printf("  sub:           %.14f\n", c[1]);
	printf("  mul:           %.14f\n", c[2]);
	printf("  div:           %.14f\n", c[3]);
	printf("  min:           %.14f\n", c[4]);
	printf("  max:           %.14f\n", c[5]);
	printf("  fabs(b):       %.14f\n", c[6]);
	printf("  sqrt(fabs(b)): %.14f\n", c[7]);
}

#include <limits>

using namespace std;

extern "C" void SseSfpCompareFloat_(float a, float b, bool* results);
extern "C" void SseSfpCompareDouble_(double a, double b, bool* results);

const int m = 7;
const char* OpStrings[m] = { "UO", "LT", "LE", "EQ", "NE", "GT", "GE" };

void SseSfpCompareFloat()
{
	const int n = 4;
	float a[n] = { 120.0, 250.0, 300.0, 42.0 };
	float b[n] = { 130.0, 240.0, 300.0, 0.0 };

	// Set NAN test value
	b[n - 1] = numeric_limits<float>::quiet_NaN();

	printf("Results for SseSfpCompareFloat()\n");
	for (int i = 0; i < n; i++)
	{
		bool results[m];

		SseSfpCompareFloat_(a[i], b[i], results);
		printf("a: %8f b: %8f\n", a[i], b[i]);

		for (int j = 0; j < m; j++)
			printf("  %s=%d", OpStrings[j], results[j]);
		printf("\n");
	}
}

void SseSfpCompareDouble(void)
{
	const int n = 4;
	double a[n] = { 120.0, 250.0, 300.0, 42.0 };
	double b[n] = { 130.0, 240.0, 300.0, 0.0 };

	// Set NAN test value
	b[n - 1] = numeric_limits<double>::quiet_NaN();

	printf("\nResults for SseSfpCompareDouble()\n");
	for (int i = 0; i < n; i++)
	{
		bool results[m];

		SseSfpCompareDouble_(a[i], b[i], results);
		printf("a: %8lf b: %8lf\n", a[i], b[i]);

		for (int j = 0; j < m; j++)
			printf("  %s=%d", OpStrings[j], results[j]);
		printf("\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	SseSfpCompareFloat();
	SseSfpCompareDouble();
	return 0;
}

