#define _GNU_SOURCE

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/times.h>

long double Leibniz(long num)
{
	register long i;
	register long double polynomial;
	register long double pi = 0.0;

	for (i = 0; i < num; ++i)
	{
		polynomial = (long double)1. / (i * 2 + 1);
		pi += polynomial;

		++i;

		polynomial = (long double)1. / (i * 2 + 1);
		pi -= polynomial;
	}
	return 4. * pi;
}

long double Euler(long num)
{
	register int i;
	register long double polynomial;
	register long double pi = 0.0;

	for (i = 1; i < num; ++i)
	{
		polynomial = 1. / ((long double)i * i);
		pi += polynomial;
	}
	return sqrt(pi * 6.);
}

int main(int argc, char *argv[], char **envp)
{
	if (argc != 2)
	{
		printf("%s [number of polynomials]\n", argv[0]);
		return 0;
	}

	char buf[257] = {
		0,
	};
	int numberOfPolynomials = atoi(argv[1]);
	char output[] = "%Gyear %mmonth %dday %Hhour %Mminute %Ssecond";

	struct tm *tm;
	struct tms mytms;

	time_t t;

	time(&t);
	tm = localtime(&t);

	strftime(buf, sizeof(buf), output, tm);
	printf("start time: %s\n\n", buf);

	printf("Number of polynomials = %d\n\n", numberOfPolynomials);

	{
		clock_t t1, t2;

		if ((t1 = times(&mytms)) == -1)
		{
			perror("times 1");
			exit(1);
		}

		long double pi1 = Leibniz(numberOfPolynomials);

		if ((t2 = times(&mytms)) == -1)
		{
			perror("times 2");
			exit(1);
		}

		printf("Leibniz formula for PI(to 20 decimal place): %.20Lf\nprocessing time: %.2lfs\n", pi1, (double)(t2 - t1) / sysconf(_SC_CLK_TCK));
	}

	{
		clock_t t1, t2;

		if ((t1 = times(&mytms)) == -1)
		{
			perror("times 1");
			exit(1);
		}

		long double pi2 = Euler(numberOfPolynomials);

		if ((t2 = times(&mytms)) == -1)
		{
			perror("times 2");
			exit(1);
		}

		printf("Euler formula for PI(to 20 decimal place): %.20Lf\nprocessing time: %.2lfs\n\n", pi2, (double)(double)(t2 - t1) / sysconf(_SC_CLK_TCK));
	}

	time(&t);
	tm = localtime(&t);

	strftime(buf, sizeof(buf), output, tm);
	printf("end time: %s\n", buf);

	return 0;
}