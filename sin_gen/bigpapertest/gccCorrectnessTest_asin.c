#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <mpfr.h>
#include "myhead.h"

struct test_data {
	double sum;
	double max;
	_UL max_times;
	double average;
};

double asin_gen(double);
void getbinary(_UL, int *);
_UL getUL(int *);
void printbinary(int *);
int computeAccurateBit(double, double);
void binaryshow(double);
double itofd(_UL);
double computeULP(double);
//_UL computeULPDiff(double, double);

struct test_data test(void)
{
	struct test_data correctness_result;
	char temp_c;
	FILE *inputData;
	double y1, y2, ulp, reUlp, input;
	int i, j, result[64];
	_UL max_times;
	_UL temp_ul;
	double ulpdiff_max, ulpdiff, ulpdiff_sum, temp;
	mpfr_t mpfr_mine, mpfr_ulpdiff, mpfr_temp, mpfr_result;

	correctness_result.sum = 0.0;
	correctness_result.max = 0.0;
	correctness_result.max_times = 0;
	ulpdiff_sum = 0.0;
	ulpdiff_max = 0.0;
	max_times = 0;
	
	mpfr_init2(mpfr_temp, 128);
	mpfr_init2(mpfr_result, 128);
	mpfr_init2(mpfr_mine, 128);
	mpfr_init2(mpfr_ulpdiff, 128);

	inputData = fopen("data.txt", "r");

	if (inputData == (FILE *)0) {
		printf("open error!!!\n");
		exit(1);
	}

	for (i = 0; i < RUN_COUNT; i++) {
	//for (i = 0; i < 1; i++) {
		for (j = 63; j >= 0; j--) {
			temp_c = getc(inputData);
			result[j] = temp_c - '0';
		}
		getc(inputData); // pass the "\n"
		temp_ul = getUL(result);
		input = itofd(temp_ul);

		y1 = asin_gen(input);
		mpfr_set_d(mpfr_temp, input, MPFR_RNDN);
		mpfr_asin(mpfr_result, mpfr_temp, MPFR_RNDN);
		y2 = mpfr_get_d(mpfr_result, MPFR_RNDN);

		mpfr_set_d(mpfr_mine, y1, MPFR_RNDN);
		mpfr_sub(mpfr_temp, mpfr_result, mpfr_mine, MPFR_RNDN);
		
		//temp = mpfr_get_d(mpfr_temp, MPFR_RNDN);
		//printf("diff is %e\n", temp);
		//printf("binary of diff  is ");
		//binaryshow(temp);
		
		reUlp = computeULP(y2);
		//printf("reUlp is %e\n", reUlp);
		//printf("binary of reUlp is ");
		//binaryshow(reUlp);
		
		if(reUlp != 0) {
			mpfr_div_d(mpfr_ulpdiff, mpfr_temp, reUlp, GMP_RNDN);
			ulpdiff = mpfr_get_d(mpfr_ulpdiff, GMP_RNDN);
			//ulpdiff = fabs(ulpdiff);
			if(ulpdiff < 0.0) ulpdiff = -ulpdiff;
		} else {
			ulpdiff = 128;
			printf("reUlp = 0\n");
		}
		
		//ulpdiff = computeULPDiff(y1, y2);

		//printf("for x = %.17e:\n", input);
		//printf("\tasin_gen = %.17e\n\tasin     = %.17e\n", y1, y2);
		//printf("binary of asin_gen is ");
		//binaryshow(y1);
		//printf("binary of asin     is ");
		//binaryshow(y2);

		if (ulpdiff_max < ulpdiff) {
			ulpdiff_max = ulpdiff;
			max_times = 1;
		}
		else if (ulpdiff_max == ulpdiff) {
			max_times++;
		}
		ulpdiff_sum += ulpdiff;
		//printf("The ULPDiff is %lu\n", ulpdiff);
		//printf("The ULPDiff is %le\n", ulpdiff);
		//printf("The ULPDiff is 0x%lx\n\n", ulpdiff);
	}
	
	fclose(inputData);
	correctness_result.sum = ulpdiff_sum;
	correctness_result.max = ulpdiff_max;
	correctness_result.max_times = max_times;
	correctness_result.average = (double)ulpdiff_sum / RUN_COUNT;
	return correctness_result;
}

int main(int argc, char *argv[]) {
	struct test_data correctness_result;
	correctness_result = test();
	//printf("%d %d %d\n", p->max, p->max_times, p->sum);
	printf("%le\n", correctness_result.max);
	printf("%lu\n", correctness_result.max_times);
	printf("%le\n", correctness_result.sum);
	printf("%le\n", correctness_result.average);
	return 0;
}
