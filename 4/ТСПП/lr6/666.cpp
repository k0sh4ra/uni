#include <iostream>
#include <locale>
#include <iomanip>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

class Student;
class Educator;
class Record;
class Journal;

class Journal{
		Educator *educators[3];
		Student *students[15];
		int S_count,
			E_count;
	public:
		Record *records[45];
		int	R_count;
		Journal(){ this->E_count = 0; this->S_count = 0; this->R_count = 0; }
		void addStud();
		void addStudent(Student &s);
		void getStudentDOLG(int id);
		void getStudent(int id, int disC);
		void addEducator(Educator &e);
		void addRec(int disCipher, int grCipher, int num, char* type);
		void addRecord(Record &r);
		void getRecords(int disCipher, int grCipher);
};

class Record{
		int grC;
		int s_id;
		char* SFIO;
		int disCiph;
		int num;
		int mark = 0; 
		bool pos = 0;
		char* type;
	public:
		Record(){};
		Record(int s_id, int grC, int num, int disCiph, char* type, char* SFIO, int mark, bool pos);
		void showRec();
		void showRecGR();
		void showRecDIS();
		void showRecPOT();
		void showRecDOP();
		int get_grC(){ return this->grC; }
		int get_s_id(){ return this->s_id; }
		int get_mark(){ return this->mark; }
		char* get_SFIO(){ return this->SFIO; }
		int get_disCiph(){ return this->disCiph; }
		void fillRec(int r_Sid, int grC, char* SFIOS, int disCipher, int num, char* type);
};

class Student{
		int id;
		char* FIO;
		int grCipher; 	
	public:
		Student(){};
		Student(int id, int grCipher, char* FIO);
		void fillStud();
		void showInfo();
		int getId(){ return this->id; }
		char* get_FIO(){ return this->FIO; }
		int get_grCipher(){ return this->grCipher; }
};

class Educator{
		string FIO;
		int disCipher;
	public:
		Educator(string FIO, int disCipher);
		void addStud(Journal &j, int disCipher);
		int get_disCipher(){ return this->disCipher; }
};

class Dekan{
	public:
		void viewJournal(Journal *j);
		void get_Stud_dop(Journal *j);
		void get_Stud_otch(Journal *j);
};

void Student::fillStud(){
	cout << "Id: "; cin >> this->id;
	cout << "Группа: "; cin >> this->grCipher;
	cout << "ФИО: "; 
	this->FIO = new char[50];
	cin.clear(); cin.sync(); 
	//cin.ignore(INT_MAX, '\n');
	cin.getline(this->FIO, 50);
}

Student::Student(int id, int grCipher, char* FIO){
	this->id = id;
	this->grCipher = grCipher;
	this->FIO = new char[50];
	for (int i = 0; i < 50; i++)
		this->FIO[i] = FIO[i];
}

void Student::showInfo(){
	cout << this->id << " " << this->FIO 
		 << " " << this->grCipher << '\n';
}

Educator::Educator(string FIO, int disCipher){
	this->FIO = FIO;
	this->disCipher = disCipher;
}

Record::Record(int s_id, int grC, int num, int disCiph, char* type, char* SFIO, int mark, bool pos){
	this->num = num;
	this->grC = grC;
	this->s_id = s_id;
	this->disCiph = disCiph;
	this->type = new char[3];
	for (int i = 0; i < 3; i++)
		this->type[i] = type[i];
	this->SFIO = new char[50];
	for (int i = 0; i < 50; i++)
		this->SFIO[i] = SFIO[i];
	this->mark = mark;
	this->pos = pos;
}

void Record::fillRec(int r_Sid, int grC, char* SFIOS, int disCipher, int num, char* type){
	this->num = num;
	this->s_id = r_Sid;
	this->grC = grC;
	this->SFIO = new char[50];
	for(int i = 0; i < 50; i++)
		this->SFIO[i] = SFIOS[i];
	this->disCiph = disCipher;
	this->type = new char[3];
	for(int i = 0; i < 3; i++)
		this->type[i] = type[i];
	cout << "Посещаемость: "; cin >> this->pos;
	cout << "Оценка: "; cin >> this->mark;
}

void Record::showRec(){
	cout << this->get_disCiph() << " " << this->num 
		 << " " << this->type << " " << this->SFIO 
		 << " " << this->pos << " " << this->mark << '\n';
}

void Record::showRecDIS(){
	cout << this->num << " " << this->type 
		 << " " << this->get_grC() << " " << this->SFIO 
		 << " " << this->pos << " " << this->mark << '\n';
} 

void Record::showRecGR(){
	cout << this->num << " " << this->get_disCiph() 
	 	 << " " << this->type << " " << this->SFIO 
		 << " " << this->pos << " " << this->mark << '\n';
}

void Record::showRecPOT(){
	cout << this->num  << " " << this->get_disCiph() 
	 	 << " " << this->type << " " << this->get_grC() 
		 << " " << this->SFIO << " " << this->pos 
		 << " " << this->mark << '\n';
}

void Record::showRecDOP(){
	cout << this->s_id << " " << this->grC 
		 << " "  << this->SFIO << '\n';
}


void Journal::addEducator(Educator &e){
	if(this->E_count == 3){
		cout << "Максимальное количество преподавателей\n";
	} else {
		this->educators[E_count++] = &e;
	}
}

void Journal::addRecord(Record &r){
	if(this->R_count == 45){
		cout << "Максимальное количество записей\n";
	} else {
		this->records[R_count++] = &r;
	}
}

void Journal::addRec(int disCipher, int grCipher, int num, char* type){
	if(this->R_count == 45){
		cout << "Максимальное количество записей\n";
	}else{
		for(int i = 0; i < this->S_count; i++)
			if(students[i]->get_grCipher() == grCipher){
				
				cout << "Студент: " << students[i]->get_FIO() << endl;
				char* SFIOS = new char[50];
				SFIOS = students[i]->get_FIO();
				int r_Sid, grC;
				r_Sid = students[i]->getId();
				grC = students[i]->get_grCipher();
				this->records[this->R_count] = new Record();
				this->records[R_count++]->fillRec(r_Sid, grC, SFIOS, disCipher, num, type);
				
			}
	}
}


void Journal::getRecords(int disCipher, int grCipher){
	int q = 0;	
	for(int i = 0; i < this->R_count; i++){
		if((records[i]->get_disCiph() == disCipher) && (records[i]->get_grC() == grCipher)){
			records[i]->showRec();
			q = 1;
		}
	}
	
	if (q == 0) cout << "Записей нет\n";
}

void Journal::getStudent(int id, int disC){
	bool f = 1;
	for(int i = 0; i < this->R_count; i++)
		if((records[i]->get_s_id() == id) && (records[i]->get_disCiph() == disC)){
				records[i]->showRec();
				f = 0;	
		}
	if(f) cout << "Записей нет\n";
}

void Journal::getStudentDOLG(int id){
	bool f = 1;
	for(int i = 0; i < this->R_count; i++)
		if((records[i]->get_s_id() == id) && (records[i]->get_mark() == 0)){
				records[i]->showRec();
				f = 0;	
		}
	if(f) cout << "Записей нет\n";
}

void Journal::addStudent(Student &s){
	if(this->S_count == 15){
		cout << "Максимальное количество студентов\n";
	} else {
		this->students[S_count++] = &s;
	}
}

void Journal::addStud(){
	if(this->S_count == 15){
		cout << "Максимальное количество студентов\n";
	} else {
		this->students[this->S_count] = new Student();
		this->students[S_count++]->fillStud();
	}
}

void Dekan::viewJournal(Journal *j){
	bool t1 = 1;
	while(t1){
		system("cls");
		cout << " Веберите пунк меню  \n"
			 << "1 Вывод по группе    \n"
			 << "2 Вывод по дисциплине\n"
			 << "3 Вывод потока       \n"
			 << "0 Выход в меню декана\n";
		switch(getch()){
			case '1':{
				system("cls");
				int grD = 0;
				cout << "Введите шифр группы: "; cin >> grD;
				for(int i = 0; i < j->R_count; i++){
					if(j->records[i]->get_grC() == grD){
						j->records[i]->showRecGR();
					}
				}
				system("pause");
				break;
			}
			case '2':{
				system("cls");
				int disD = 0;
				cout << "Введите шифр дисциплины: "; cin >> disD;
				for(int i = 0; i < j->R_count; i++){
					if(j->records[i]->get_disCiph() == disD){
						j->records[i]->showRecDIS();
					}
				}
				system("pause");
				break;
			}
			case '3':{
				system("cls");
				for(int i = 0; i < j->R_count; i++)
						j->records[i]->showRecPOT();
					
				system("pause");
				break;
			}
			case '0':{
				system("cls");
				t1 = 0;
				break;
			}
		}
	}
}

void Dekan::get_Stud_otch(Journal *j){
	system("cls");
	int k = 0, t = 0, p = 0, q = 0;
	for(p = 0; p < j->R_count; p++)
		for(q = p+1; q < j->R_count; q++)
			if(j->records[p]->get_s_id() > j->records[q]->get_s_id())
				swap(j->records[p], j->records[q]);
	
	p = 0; k = 0;
	Record *a[45];
	for(p = 0; p < j->R_count; p++)
		if(j->records[p]->get_mark() == 0){
			a[k] = j->records[p];
			k++;
		}
		
	p = 0; q = 0; t = 0;
	Record *b[45];
	b[t] = a[1];
	for(p = 0; p < k; p++)
		if(a[p]->get_s_id() != b[t]->get_s_id()){
			t++;
			b[t] = a[p];
		}

	
	for(int i = 0; i <= t; i++)
		b[i]->showRecDOP();
	system("pause");
	system("cls");
}

void Dekan::get_Stud_dop(Journal *j){
	system("cls");
	int k = 0, t = 0, p = 0, q = 0;
	for(p = 0; p < j->R_count; p++)
		for(q = p+1; q < j->R_count; q++)
			if(j->records[p]->get_s_id() > j->records[q]->get_s_id())
				swap(j->records[p], j->records[q]);
	
	p = 0; k = 0;
	Record *a[45];
	for(p = 0; p < j->R_count; p++)
		if(j->records[p]->get_mark() == 0){
			a[k] = j->records[p];
			k++;
		}
		
	p = 0; q = 0; t = 0;
	Record *b[45];
	b[t] = a[1];
	for(p = 0; p < k; p++)
		if(a[p]->get_s_id() != b[t]->get_s_id()){
			t++;
			b[t] = a[p];
		}

	int l = 0;
	Record *c[45];
	for(int i = 0; i < j->R_count; i++)
		if(j->records[i]->get_mark() != 0){
			c[l] = j->records[i];
			l++;
		}
	
	int m = 0;
	Record *d[45];
	d[m] = c[1]; 
	for(int i = 0; i < l; i++)
		if(c[i]->get_s_id() != d[m]->get_s_id()){
			m++;
			d[m] = c[i];
		}
		
	int h = 0;
	Record *f[45];
	for(int i = 0; i <= t-1; i++)
		for(int j = i+1; j <= m; j++)
			if(b[i]->get_s_id() != d[j]->get_s_id()){
				f[h] = d[j];
				h++;
			}
	
	
	for(int i = 0; i < h; i++)
		f[i]->showRecDOP();
	system("pause");
	system("cls");
}



main(){
	setlocale(LC_ALL, "rus");
	Journal j;
	Educator e1("Ландышев", 12);
	Educator e2("Боярышев", 92);	
	Educator e3("Лопастев", 32);
	
	Student s1(1, 3, "Jora");
	Student s2(2, 3, "Sasha");
	Student s3(3, 2, "Igor");
	Student s4(4, 2, "Vova");
	
	//int s_id, int grC, int num, int disCiph, char* type, char* SFIO, int mark, bool pos
	Record r1(1, 3, 1, 12, "L", "Jora", 5, 1);
	Record r2(4, 2, 1, 92, "L", "Vova", 4, 1);
	Record r3(2, 3, 1, 12, "L", "Sasha", 0, 0);
	Record r4(3, 2, 1, 12, "L", "Igor", 5, 1);
	Record r5(1, 3, 1, 92, "L", "Jora", 0, 0);
	Record r6(1, 3, 2, 92, "L", "Jora", 1, 1);
	Record r7(3, 2, 2, 12, "L", "Igor", 5, 1);
	Record r8(1, 3, 1, 32, "L", "Jora", 0, 0);
	Record r9(3, 2, 1, 32, "L", "Igor", 5, 1);
	Record r10(2, 3, 1, 32, "L", "Sasha", 0, 0);
	
	
	j.addEducator(e1);j.addEducator(e2);
	j.addEducator(e3);
	
	j.addStudent(s1);j.addStudent(s2);
	j.addStudent(s3);j.addStudent(s4);
	
	j.addRecord(r1);j.addRecord(r2);
	j.addRecord(r3);j.addRecord(r4);
	j.addRecord(r5);j.addRecord(r6);
	j.addRecord(r7);j.addRecord(r8);
	j.addRecord(r9);j.addRecord(r10);
	
	
	while(1){
		system("cls");
		cout << "  Главное меню  \n";
		cout << "     Кто вы?    \n"
			 << "1 Студент       \n"
			 << "2 Преподаватель \n"
			 << "3 Декан         \n"
			 << "0 Выход         \n";
		switch(getch()){
			case '1':{
				system("cls");
				int stID = 0;
				cout << "Введите свой id: "; cin >> stID;
				system("cls");
				bool f = 1;
				while(f){
				system("cls");
				cout << "    Меню студента     \n";
				cout << "Выберите пункт меню   \n"
					 << "1 Вывод оценок        \n"
					 << "2 Просмотр долгов     \n"
					 << "0 Выйти в главное меню\n";
					switch(getch()){
						case '1':{
							system("cls");
							int disC = 0;
							cout << "Введите шифр предмета: "; cin >> disC;
							j.getStudent(stID, disC);
							system("pause");
							break;
						}
						case '2':{
							system("cls");
							j.getStudentDOLG(stID);
							system("pause");
							break;
						}
						case '0':{
							f = 0;
							break;
						}
					}
				}
				break;
			}
			case '2':{
				system("cls");
				int dis = 0;
				cout << "Введите шифр вашей дисциплины: "; cin >> dis;
				system("cls");
				bool s = 1;
				while(s){
					system("cls");
					cout << "    Меню преподавателя      \n";
					cout << "    Выберите пункт меню     \n"
						 << "1 Добавить запись           \n"
						 << "2 Добавить ученика          \n"
						 << "3 Просмотр журнала 		 \n"
						 << "0 Выход в главное меню      \n";
					switch(getch()){
						case '1':{
							system("cls");
							int grC = 0, n = 0;
							char* ty;
							cout << "Введите шифр группы: "; 	cin >> grC;
							cout << "Введите номер занятия: ";	cin >> n;									
							cout << "Введите тип занятия: "; 	ty = new char[3];
															 	cin.clear(); cin.sync();
															 	cin.getline(ty, 3);
							cout << endl;
							j.addRec(dis, grC, n, ty);
							system("pause");
							break;
						}
						case '2': {
							system("cls");
							j.addStud();
							system("pause");
							break;
						}
						case '3':{
							system("cls");
							int gr = 0;
							cout << "Введите шифр группы: "; cin >> gr;
							j.getRecords(dis,gr);
							system("pause");
							break;
						}
						case '0':{
							s = 0;
							break;
						}
					}
				}
				break;
			}
			case '3':{
				system("cls");
				Dekan d;
				bool t = 1;
				while(t){
					cout << "              Меню декана               \n";
					cout << "          Веберите пунк меню            \n"
						 << "1 Посмотеть журнал						 \n"
						 << "2 Вывести студентов, допущенных к сессии\n"
						 << "3 Вывести студентов, с долгами          \n"
						 << "0 Выход в главное меню                  \n";
					switch(getch()){
						case '1':{
							system("cls");
							d.viewJournal(&j);
							break;
						}
						case '2':{
							system("cls");
							d.get_Stud_dop(&j);
							break;
						}
						case '3':{
							system("cls");
							d.get_Stud_otch(&j);
							break;
						}
						case '0':{
							t = 0;
							break;
						}
					}
				}
				break;
			}
			case '0':{
				return 0;
				break;
			}
		}
	}			 
}
