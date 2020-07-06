#include <iostream>
#include <cmath>
#include <ctime>
#include <Windows.h>

using namespace std;

int main(){
	setlocale(LC_ALL, "RUSSIAN");
	double n;
	cout << "Введите количество испытаний: "; cin >> n;
	double startX = 0, startY = 0, 
		   endX = 2, endY = sqrt(endX),
		   S_square = endX * endY;
	cout << "Площать квадрата: " << S_square << endl;
	system("pause");
	system("cls");

	float x;
	HDC hDC = GetDC(GetConsoleWindow());
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hDC, Pen);
	int graph_x = 800, graph_y = 500, scale = 40;
	MoveToEx(hDC, 0, graph_y/2, NULL);
	LineTo(hDC, graph_x, graph_y/2);
	MoveToEx(hDC, graph_x/2, 0, NULL);
	LineTo(hDC, graph_x/2, graph_y);

	for(x = float(0); x <= float(n)/100; x += 0.01f){
		double m = 0;
		srand(time(0));
		for (int i = 0; i < int(x * 100); i++){
			double dotX = (double)rand() / (double)RAND_MAX * (endX - startX) + startX;
			double dotY = (double)rand() / (double)RAND_MAX * (endY - startY) + startY;
			if (dotY < sqrt(dotX)) m++;
		}
		double S = S_square * (m / int(x * 100));
		MoveToEx(hDC, scale * x + (graph_x/2), -scale * S + (graph_y/2), NULL);
		LineTo(hDC, scale * x + (graph_x/2), -scale * S + (graph_y/2));
	}
	while(1) {}
	system("pause>>void");
}

