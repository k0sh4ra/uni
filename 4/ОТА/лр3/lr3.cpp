#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
#include <iostream>
#define SIZE ;

using namespace std;

int N = 8;
int vector[8];
int counter[8];
int V = 17; 
int flag = 0;
int countOp = 0;

void TaskSum(){
	int i,j,sum,cnt,MaxN; 
	flag = 0;
	MaxN = int(pow(2,N)-1);
	i = 0;
	cnt = 1;
	countOp += 6;
	while(i < N){
	  	counter[i] = 0;
	  	i++;
	  	countOp =+ 3;
	}

	do{
	 	sum = 0;
	 	i = 0;
	 	j = N - 1;
	 	countOp += 4;
	 	while(i < N){
			sum = sum+counter[i]*vector[i];
			i++;
			countOp += 5;
		}
		if(sum == V){
			flag = 1;
			countOp += 2;
			cout << endl;
			return;
		}
	 	
	 	while((counter[j]==1)&&(j!=0)){
			counter[j] = 0;
			j = j - 1;
			countOp += 6;
	  	}
	 	counter[j] = 1;
	 	cnt = cnt + 1;
		countOp += 3;
	}
	while(cnt <= MaxN);countOp++;
}


int main(){
	srand(time(0));
	int min,cnt,power,sum,j,temp,c;
	double result;
	cout << "dimension = 8\n"
		 << "max number = 100\n"
		 << "V = 17\n";
	for(int i = 0; i < N; i++){
		fscanf(stdin, "%d", &temp);
		//temp = rand() % 100 + 1;
		vector[i] = temp;
	}
	
	TaskSum();
	if(flag == 1) cout << "OK\n";
	else cout << "NO elements giving the sum\n";
	
	for(int k = 0; k < N; k++) printf("%d%s",counter[k]," ");
	printf("%s\n"," ");
	
	for(int k = 0; k < N; k++) printf("%d%s",vector[k]," ");
	cout << endl << "Count elementary operations = " << countOp << endl;
}
