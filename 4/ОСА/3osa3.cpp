#include <iostream>
using namespace std;

int main(){
	setlocale(LC_ALL, "Rus");
	int cA = 0, cB = 0, cC = 0, cD = 0;
	float Bsum = 0, Csum = 0, Dsum = 0;

	/*----------���� ���������� ��������� �� �������----------*/
	cout << "������� ���������� ��������� �� ������ �: ";
	cin >> cA;
	cout << "������� ���������� ��������� �� ������ �: ";
	cin >> cB;
	cout << "������� ���������� ��������� �� ������ �: ";
	cin >> cC;
	cout << "������� ���������� ��������� �� ������ D: ";
	cin >> cD;

	/*--------------��������� ������ ��� �������--------------*/
	float* al = new float[cA];	

	float** BxA = new float* [cB];
	for (int i = 0; i < cB; i++) BxA[i] = new float[cA];

	float** CxB = new float* [cC];
	for (int i = 0; i < cC; i++) CxB[i] = new float[cB];

	float** DxC = new float* [cD];
	for (int i = 0; i < cD; i++) DxC[i] = new float[cC];

	float* B = new float [cB];
	for(int i = 0; i < cB; i++) B[i] = 0;
	
	float* C = new float [cC];
	for(int i = 0; i < cC; i++) C[i] = 0;
	
	float* D = new float [cD];
	for(int i = 0; i < cD; i++) D[i] = 0;
	
	
	/*----------------------���� ������-----------------------*/
	cout << "������� ������� �:" << endl;
	for(int i = 0; i < cA; i++) cin >> al[i];

	cout << "������� ������� BxA:" << endl;
	for(int i = 0; i < cB; i++)
		for(int j = 0; j < cA; j++)
			cin >> BxA[i][j];

	cout << "������� ������� CxB:" << endl;
	for(int i = 0; i < cC; i++)
		for(int j = 0; j < cB; j++)
			cin >> CxB[i][j];

	cout << "������� ������� DxC:" << endl;
	for(int i = 0; i < cD; i++)
		for(int j = 0; j < cC; j++)
			cin >> DxC[i][j];
			
			
	/*------------------------�������-------------------------*/		
	//����������� �������������� ���� ������� ������
	for(int i = 0; i < cB; i++)
		for(int j = 0; j < cA; j++)
			if(BxA[i][j] != 0)
				B[i] += BxA[i][j]*al[j];
	for(int i = 0; i < cB; i++) Bsum += B[i];
		
	//������������ ��������� bi
	for(int i = 0; i < cB; i++) B[i] = B[i]/Bsum;

	//����������� �������������� ���� �������� ������
	for(int i = 0; i < cC; i++)
		for(int j=0; j < cB; j++)
			if(CxB[i][j] != 0)
				C[i] += CxB[i][j]*B[j];
	for(int i = 0; i < cC; i++) Csum += C[i];

	//������������ ��������� ci
	for(int i = 0; i < cC; i++) C[i] = C[i]/Csum;
		
	//����������� �������������� ���� ���������� ������
	for(int i = 0; i < cD; i++)
		for(int j=0; j < cC; j++)
			if(DxC[i][j] != 0)
				D[i] += DxC[i][j]*C[j];
	for(int i = 0; i < cD; i++) Dsum += D[i];

	//������������ ��������� di
	for (int i = 0; i < cD; i++) D[i] = D[i]/Dsum;


	/*---------------------����� ��������---------------------*/
	cout << endl << "������� �:" << endl;
	for (int i = 0; i < cA; i++) cout << al[i] << ' ';
	cout << endl << endl;

	cout << "������� B:" << endl;
	for (int i = 0; i < cB; i++) cout << B[i] << ' ';
	cout << endl << endl;

	cout << "������� C:" << endl;
	for (int i = 0; i < cC; i++) cout << C[i] << ' ';
	cout << endl << endl;

	cout << "������� D:" << endl;
	for (int i = 0; i < cD; i++) cout << D[i] << ' ';
	cout << endl;

	/*---------------------������� ������---------------------*/
	delete[] al;
	for (int i = 0; i < cB; i++) delete[] BxA[i];
	delete[] BxA;
	for (int i = 0; i < cC; i++) delete[] CxB[i];
	delete[] CxB;
	for (int i = 0; i < cD; i++) delete[] DxC[i];
	delete[] DxC;
	delete[] B; delete[] C; delete[] D;
}
