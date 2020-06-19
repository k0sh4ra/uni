#include<iostream>
#include<conio.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#include <time.h>

using namespace std;

int vector[8];
int counter[8];
int flag;
FILE* stream;


void create_arr(int N){
	int i, q = 0;
	FILE* stream;
	srand(time(NULL));
	printf("\n%d%s\n", N, " random numbers from 0 to 100");
	for (i = 0; i < N; i++){
		vector[i] = rand() % 100; 
		printf("%d ", vector[i]);
	}
	for (i = 0; i < N; i++){
		if (vector[i] > q) q = vector[i];
	}
	cout << endl << endl << "Maximal integer ";
	cout << q << endl;
}

void TaskSum(int N, int vector[]){
	int counter = 0, 
		V = 17,	
		* Cnt, 
		i = 0;
	Cnt = (int*)malloc(N * sizeof(int));
	counter += 3;
	do{
		Cnt[i] = 0;
		i += 1;
	} while (i < N);
	
	counter += 5 * N;
	do{
		int Sum = 0;
		for (int i = 0; i < N; i++)
			Sum = Sum + vector[i] * Cnt[N - i];
		
		counter += 1 * 8 * N;
		if (Sum == V)
			counter += 2;
		
		counter += 1 + 4 * N;
		int j = N;
		while (Cnt[j] == 1){
			Cnt[j] = 0;
			j = j - 1;
			counter += 6 * N;
		}
		Cnt[j] = 1;
		counter += 6;
	} while (Cnt[0] != 1);
	cout << endl << "number of operations: " << counter << endl;
}

int main(){
	int N = 8;
	cout << "dimension = 8";
	cout << "Max diapasone = 100" << endl;
	cout << "V = 17" << endl;
	create_arr(N);
	cout << endl;
	TaskSum(N, vector);
	system("pause");
	return 0;
}
