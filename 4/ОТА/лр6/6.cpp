#include <iostream>
#include <string>

using namespace std;

const int n = 10;

struct tovar {
	char* name[n] = {"a","ma","klass","guchi","flip","flap","boop","door","soojin","leto"};
	float price[n] = {1234,134,1,4232,545234,423,77,12,875,12356};
	int id[n] = {3,6,1,7,9,8,2,4,5,10};
};

//Сортировка посредством выбора
void VuborSort(int a[], int n){
	int counter = 0;
	int reassign = 0;
	for (int i=n, imax; i>1; i--){
		imax = 1;
		counter++;
		for (int j=1; j<=i; j++){
			counter++;
			if (a[j] < a[imax]){
				imax = j;
				reassign++;
			}
		}
		swap(a[i],a[imax]);
	}
	cout << "Количество итераций: " << counter << endl;
	cout << "Количество переприсваиваний: " << reassign << endl;
}

//Сортировка массива пузырьком
void bubbleSort(int a[], int n){
	int counter = 0;
	int reassign = 0;
	for (int i=0; i<n-1; i++){
		counter++;
		for (int j=i+1; j<n; j++){
			counter++;
			if (a[i] < a[j]){
				reassign++;
				swap(a[i],a[j]);
			}
		}	
	}
	cout << "Количество итераций: " << counter << endl;
	cout << "Количество переприсваиваний: " << reassign << endl;
}

//Сортировка Шелла
void shellSort(int a[], int n) {  
	int i, j, temp, step = n/2;
	int counter = 0;
	int reassign = 0;
	while (step > 0) {  
		counter++;  
		for (i=0; i<(n-step); i++){    
			j = i;   
			counter++;
			while (j>=0 && a[j] > a[j+step]) {    
    			reassign++;
				swap(a[j],a[j+step]);     
				j--;     
			} 
 		}         
		step = step/2;
	}
	cout << "Количество итераций: " << counter << endl;
	cout << "Количество переприсваиваний: " << reassign << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	tovar a;

	cout << "Сортировка выбором\n";
	VuborSort(a.id, n);

	cout << endl << "Сортировка пузырьком\n";
	bubbleSort(a.id, n);

	cout << endl << "Сортировка Шелла\n";
	shellSort(a.id, n);
}
