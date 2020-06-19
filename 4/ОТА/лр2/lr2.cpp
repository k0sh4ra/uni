#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
#include <iostream>

using namespace std;

const int N = 550;
int vector[1000];

void create_array(int Nmax) {
	int i;
	FILE* stream;
	stream = fopen("Example_TA2.TXT", "w+");
	cout << "Maximal integer "; cout << RAND_MAX;
	printf("\n%d%s\n", Nmax, " random numbers from 1 to 200");
	for (i = 0; i < Nmax; i++) {
		vector[i] = rand() % 200 + 1;
		fprintf(stream, "%d\n", vector[i]);
	}
	fclose(stream);
}

double harmonic(int N) {
	double Sum = 0;
	for (int i = 1; i <= N; i++) { Sum += 1. / i; }	
	return Sum;
}

int main() {
	int i,min,cnt;	
	double result;
	srand(time(0));
	result = harmonic(N);
	cout << "Garmon = " << result << endl;
	create_array(N);
	min = vector[0];
	cnt = 0;
	for (i = 1; i < N; i++) {
		if (vector[i] < min) { min = vector[i]; cnt++; }
	}
	printf("%s%d%s%d\n", "Minimal ", min, " Num oper ", cnt);
}

