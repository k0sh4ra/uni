/* ����������� �������� ������������ � ��������� ���������*/
#include <conio.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

main()
{
	double
	Fn, 		//F(n)
	Gn, 		//G(n)
	ATg_FG,
	ATg_GF,
	pi,
	Nbegin, 			//����� ������� ���������
	Nend, 				//������ ������� ���������
	step, 				//��� ��������� ���������
	phi, 				//�������� ����
	k, 					//����������� ���������
	Delta, 				//������ �������
	Theta, 				//������ ������
	O_large, 			//������ ��-�������
	ii; 				//�������� ��������� ������� ������������
	FILE *stream;		//��������� �� ����, � ������� �������������� ����-����� ��������
	stream = fopen("Example_TA.TXT", "w+"); // �������� ����� ��� ������
	
	/*���� �������� ������ ����������, ���� ���������
	��������� ������ ���������, ������������ ���������*/
	
	cout<<"Input Nbegin "; 			cin >> Nbegin; 	//����� �������, ���� ��������
	cout<<"Input Nend "; 			cin >> Nend; 	//������ �������, ���� ��������
	cout<<"Input step "; 			cin >> step; 	//��� ��������� ���������
	cout<<"Input koefficient "; 	cin >> k; 		//����������� ���������
	phi = M_PI/k; 			/*���������� ���� ��������� ��� pi/k, M_Pi � ���������� ��������� ��.�, ����� pi = 3.1415...*/
	ii=Nbegin;				//�������� ������� ����� ����� ������� ���������
	while (ii<=Nend)
	{ 
		Fn = 17*ii*ii*ii+19*ii*ii*log(ii); 		//������ �������� ������� F(n)
		Gn = 3*ii*ii*ii*ii-24*ii*ii*sqrt(ii); 	//������ �������� ������� G(n)
		ATg_FG = atan(Fn/Gn);
		ATg_GF = atan(Gn/Fn);
		pi = ATg_FG - ATg_GF;
		Delta = phi - pi;
		Theta = fabs(pi) - phi;
		O_large = pi + phi;
		fprintf(stream, "%f %f %f %f %f %f %f %f %f\n", ii, Fn, Gn, ATg_FG, ATg_GF, pi, Delta, Theta, O_large);
		//������ �������� � ����
		ii=ii+step; //��������� ���������� �������� ���������
	}
	fclose(stream); //������� ����
}


