/* подключение основных используемых в программе библиотек*/
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
	Nbegin, 			//Левая граница интервала
	Nend, 				//Правая граница интервала
	step, 				//Шаг изменения аргумента
	phi, 				//Значение угла
	k, 					//Коэффициент кратности
	Delta, 				//Оценка «Дельта»
	Theta, 				//Оценка «Тетта»
	O_large, 			//Оценка «О-большое»
	ii; 				//Значение аргумента функций трудоемкости
	FILE *stream;		//Указатель на файл, в который осуществляется ввод-вывод расчетов
	stream = fopen("Example_TA.TXT", "w+"); // открытие файла для записи
	
	/*Ввод значений границ интервалов, шага изменения
	аргумента внутри интервала, коэффициента кратности*/
	
	cout<<"Input Nbegin "; 			cin >> Nbegin; 	//Левая граница, ввод значения
	cout<<"Input Nend "; 			cin >> Nend; 	//Правая граница, ввод значения
	cout<<"Input step "; 			cin >> step; 	//Шаг изменения аргумента
	cout<<"Input koefficient "; 	cin >> k; 		//Коэффициент кратности
	phi = M_PI/k; 			/*Определили угол изменения как pi/k, M_Pi – встроенная константа яз.С, число pi = 3.1415...*/
	ii=Nbegin;				//Аргумент функций равен левой границе интервала
	while (ii<=Nend)
	{ 
		Fn = 17*ii*ii*ii+19*ii*ii*log(ii); 		//Расчет значения функции F(n)
		Gn = 3*ii*ii*ii*ii-24*ii*ii*sqrt(ii); 	//Расчет значения функции G(n)
		ATg_FG = atan(Fn/Gn);
		ATg_GF = atan(Gn/Fn);
		pi = ATg_FG - ATg_GF;
		Delta = phi - pi;
		Theta = fabs(pi) - phi;
		O_large = pi + phi;
		fprintf(stream, "%f %f %f %f %f %f %f %f %f\n", ii, Fn, Gn, ATg_FG, ATg_GF, pi, Delta, Theta, O_large);
		//Запись расчетов в файл
		ii=ii+step; //Получение следующего значения аргумента
	}
	fclose(stream); //Закрыли файл
}


