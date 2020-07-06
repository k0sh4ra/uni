#include <iostream>
#include <math.h>
using namespace std;

/*------------------------------������ �������� �������--------------------------------*/
float **createMatrix(int row, int col){
	float** m = new float* [row];
	for (int i = 0; i < row; i++) m[i] = new float[col];
	
	cout << "������� " << row * col << " ��������� �������: " << endl;
	for(int i = 0; i < row; i++) 
		for(int j = 0; j < col; j++) 
			cin >> m[i][j];
	
	return m;
}

/*-------------------------������� �������� ������� ���������--------------------------*/
float **priorityCriteria(float **matr, int quant_alt, int curr_crit){
	float** m = new float* [quant_alt];
	for(int i = 0; i < quant_alt; i++) m[i] = new float[quant_alt];

	for(int i = 0; i < quant_alt; i++)
		for(int j = 0; j < quant_alt; j++) 
			m[i][j] = matr[curr_crit][i]/matr[curr_crit][j];
	
	return m;
}

/*--------------------------������� �������� �����������-------------------------------*/
float *calcultPriority(float **m, int quant_alt){
	float sum = 0;						
	float* vec = new float[quant_alt];	
	for(int i = 0; i < quant_alt; i++){
		float proizv = 1;				
		
		for(int j = 0; j < quant_alt; j++) 
			proizv = proizv*m[i][j];
		
		vec[i] = pow(proizv,(1.0/quant_alt));
		sum += vec[i];
	}
	for(int i = 0; i < quant_alt; i++)
		vec[i] = vec[i] / sum;	//������������
	return vec;
}

/*-----------------------������� ������� ���������� �����������------------------------*/
float* calcultGlobalPriority(float** m, float* v, int quant_crit, int quant_alt){
	float* global_prior = new float[quant_alt];
	for (int i = 0; i < quant_alt; i++) global_prior[i] = 0;
	
	for (int i = 0; i < quant_alt; i++) 
		for (int j = 0; j < quant_crit; j++) 
			global_prior[i] += m[j][i]*v[j];
		
	cout << "��� ����������� �, � � � ��������������: ";
	for (int i = 0; i < quant_alt; i++) 
		cout << *&global_prior[i] << ' ';

	return global_prior;
}

/*---------------------------------�������� ���������----------------------------------*/
int main(){
	setlocale(LC_ALL, "Rus");
	int quant_crit;					//���������� ���������
	int quant_alt;					//���������� �����������
	cout << "������� ���������� ���������: "; cin >> quant_crit;
	cout << "������� ���������� �����������: "; cin >> quant_alt;
	float** crit_alt;				//������� ��������� �����������
	float** eval_crit;				//������� ������ ���������
	float** cost, ** efficiency, 
	     ** reliability, ** guarantee,
		 **	durability;				//������� ��������� ���������
	float** priority;				//������� �����������
	float* prioir_eval;				//������ ����������� ������
	float* global_crit;				//������ ���������� �����������
	
	cout << "������� ������� ���������" << endl;
	crit_alt = createMatrix(quant_crit, quant_alt);
	
	cout << "������� ������� ������" << endl;
	eval_crit = createMatrix(quant_crit, quant_crit);
	
	//������� ����������� ���������
	cost = priorityCriteria(crit_alt, quant_alt, 0);
	efficiency = priorityCriteria(crit_alt, quant_alt, 1);
	reliability = priorityCriteria(crit_alt, quant_alt, 2);
	guarantee = priorityCriteria(crit_alt, quant_alt, 3);
	durability = priorityCriteria(crit_alt, quant_alt, 4);
	prioir_eval = calcultPriority(eval_crit, quant_crit);
	priority = new float* [quant_crit];
	priority[0] = calcultPriority(cost, quant_alt);
	priority[1] = calcultPriority(efficiency, quant_alt);
	priority[2] = calcultPriority(reliability, quant_alt);
	priority[3] = calcultPriority(guarantee, quant_alt);
	priority[4] = calcultPriority(durability, quant_alt);
	
	//����
	global_crit = calcultGlobalPriority(priority, prioir_eval, quant_crit, quant_alt); 
	
	/*-------------------------------������� ������------------------------------------*/
	for (int i = 0; i < quant_crit; i++) delete[] crit_alt[i];
	delete[] crit_alt;
	
	for (int i = 0; i < quant_crit; i++) delete[] eval_crit[i];
	delete[] eval_crit;
	
	for (int i = 0; i < quant_alt; i++) delete[] cost[i];
	delete[] cost;
	
	for (int i = 0; i < quant_alt; i++)	delete[] efficiency[i];
	delete[] efficiency;
	
	for (int i = 0; i < quant_alt; i++) delete[] reliability[i];
	delete[] reliability;
	
	for (int i = 0; i < quant_alt; i++) delete[] guarantee[i];
	delete[] guarantee;
	
	for (int i = 0; i < quant_alt; i++)	delete[] durability[i];
	delete[] durability;
	
	for (int i = 0; i < quant_crit; i++) delete[] priority[i];
	delete[] priority;
	
	delete[] prioir_eval;
	delete[] global_crit;
	return 0;
}

