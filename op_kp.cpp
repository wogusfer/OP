#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <clocale>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <cstring>
using namespace std;

bool checkNum(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] < 48 || str[i] > 57) return false;
	}
	return true;
}

bool checkTime(string str) {
	if (str.length() > 5 || str.length() < 5) return false;
	if (!isalpha(str[0]) && !isalpha(str[1]) && !isalpha(str[3]) && !isalpha(str[4]) && str[2] == ':') {
		if ((str[0] == 50 && str[1] >= 52) || (str[0] == 50 && str[3] == 54)) return false;
		else return true;
	}
	return false;
}

bool checkDest(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (i == 0) {
			if (!(str[i] <= 'Я' && str[i] >= 'А')) return false;
		}
		else {
			if (!((str[i] <= 'я' && str[i] >= 'а') || str[i] == 45)) return false;
		}
	}
	return true;
}

string tranTimeinStr(int x) {
	string str = "";
	str += to_string(x / 600);
	str += to_string((x / 60) % 10);
	str += ':';
	str += to_string((x % 60) / 10);
	str += to_string(x % 10);
	return str;
}

int tranTimeinInt(string str) {
	string b = "";
	b = str[0]; int a = atoi(b.c_str());
	b = str[1]; int c = atoi(b.c_str());
	b = str[3]; int d = atoi(b.c_str());
	b = str[4]; int e = atoi(b.c_str());
	int x = a * 600 + c * 60 + d * 10 + e;
	return x; // время в минутах
}

struct Train {
	string destination;
	unsigned short int numTr;
	unsigned int timeAr;
	Train* Next;
};

class List {
	Train* Head;
public:
	List() { Head = NULL; }
	~List() {
		while (Head != NULL) {
			Train* ptr = Head->Next;
			delete Head;
			Head = ptr;
		}
	}
	bool add() {
		Train* ptr = Head;
		Train* nnote = new Train;
		string dest = "";
		string num = "";
		string timeAr = "";
		bool d = true; bool n = true; bool t = true;
		bool wh = true;
		bool k = true;
		while (true) {
			cout << "Введите место назначения: "; 
			getline(std::cin, dest);
			if (checkDest(dest)) { nnote->destination = dest; break; }
			else cout << "Ошибка ввода, некорректые данные.\n\n";
		}
		while (true) {
			cout << "Введите номер поезда: "; 
			getline(std::cin, num);
			if (checkNum(num) && checkKey(atoi(num.c_str()))) {
				nnote->numTr = atoi(num.c_str()); break;
			}
			else {
				if (!checkNum(num)) cout << "Ошибка ввода, некорректые данные.\n\n"; 
			}
		}
		while (true) {
			cout << "Введите время отправления: "; 
			getline(std::cin, timeAr);
			if (checkTime(timeAr)) { nnote->timeAr = tranTimeinInt(timeAr); break; }
			else cout << "Ошибка ввода, некорректые данные.\n\n";
		}
		k = true;
		if (!ptr) {
			Head = nnote;
			nnote->Next = NULL;
			cout << "Запись успешно добавлена.\n";
			system("pause");
			return true;
		}
		if (ptr->timeAr > nnote->timeAr) {
			Head = nnote;
			nnote->Next = ptr;
			cout << "Запись успешно добавлена.\n";
			system("pause");
			return true;
		}
		if (!ptr->Next && k) k = false;
		while (k && ptr->Next && ptr->Next->timeAr < nnote->timeAr) {
			if (ptr->Next) ptr = ptr->Next;
			else k = false;
		}
		if (k) {
			nnote->Next = ptr->Next;
			ptr->Next = nnote;
		}
		else {
			ptr->Next = nnote;
			nnote->Next = NULL;
		}
		cout << "Запись успешно добавлена.\n";
		system("pause");
		return true;
	}

	bool remove() {
		if (!Head) {
			cout << "Таблица пуста.\n";
			system("pause");
			return false;
		}
		int nuT;
		string num;
		bool wh = true;
		while (wh) {
			cout << "Введите номер поезда: ";
			cin >> num;
			if (checkNum(num)) {
				nuT = atoi(num.c_str());
				wh = false;
			}
			else cout << "Некорректный номер поезда: " << num << "\n";
		}
		Train* ptr = Head;
		Train* dptr;
		if (ptr->numTr == nuT) {
			Head = ptr->Next;
			delete ptr;
			cout << "Запись успешно удалена.\n";
			system("pause");
			return 0;
		}
		while (ptr->Next != NULL) {
			if (ptr->Next->numTr == nuT) {
				dptr = ptr->Next;
				ptr->Next = dptr->Next;
				delete dptr;
				cout << "Запись успешно удалена.\n";
				system("pause");
				return 0;
			}
			ptr = ptr->Next;
		}
		cout << "Запись не найдена.\n";
		system("pause");
		return false;
	}

	bool show() {
		//string sss = "АБЯ абя";
		if (!Head) {
			cout << "Таблица пуста.\n";
			system("pause");
			return false;
		}
		Train* ptr = Head;
		cout << left << setw(20) << "Место назначения" << setw(18) << "Номер поезда"
			<< "Время отправления\n";
		while (ptr != NULL) {
			cout << left << setw(18) << ptr->destination.c_str() << '\t';
			cout << setw(10) << ptr->numTr << '\t';
			cout << setw(10) << tranTimeinStr(ptr->timeAr) << endl;
			ptr = ptr->Next;
		}
		cout << endl;
		system("pause");
		return true;
	}

	bool save() {
		Train* ptr = Head;
		ofstream fout;
		string str;
		cout << "Введите имя файла: ";
		cin >> str;
		str += ".txt";
		fout.open(str, ios_base::trunc); // создается и открывается новый файл
		while (ptr) {
			fout << left << setw(18) << ptr->destination << setw(10) << ptr->numTr <<
				tranTimeinStr(ptr->timeAr) << "\n";
			ptr = ptr->Next;
		}
		cout << "Таблица была сохранена.\n";
		system("pause");
		return true;
	}

	bool load(string str) {
		char buf[50];
		Train* ptr = Head;
		str += ".txt";
		ifstream fin(str);
		while (!fin.is_open()) {
			cout << "Вы ввели некорректное имя файла или такой файл не существует.\nПопробуйте снова или введите \"8\", чтобы перейти в главное меню.\n";
			cin >> str; 
			if (str == "8") {
				return false;
			}
			str += ".txt";
			fin.open(str);
		}
		string buff;
		while (!fin.eof()) {
			Train* tr = new Train;
			buff = "";
			fin.getline(buf, 50);
			for (int i = 0; i < 50; i++) {
				buff += buf[i];
			}
			addL(buff);
		}
		cout << "Таблица успешно загружена.\n";
		system("pause");
		return true;
	}

	bool checkKey(int x) {
		Train* ptr = Head;
		while (ptr != NULL) {
			if (ptr->numTr == x) {
				cout << "\nНомер поезда не уникален!\n";
				return false;
			}
			ptr = ptr->Next;
		}
		return true;
	}

	bool checkKeyM(int x) {
		Train* ptr = Head;
		while (ptr != NULL) {
			if (ptr->numTr == x) {
				return false;
			}
			ptr = ptr->Next;
		}
		return true;
	}

	bool task() {
		if (!Head) {
			cout << "Таблица пуста.\n";
			system("pause");
			return false;
		}
		string str;
		bool wh = true;
		int kr = 0;
		while (wh) {
			cout << "Введите место назначения: "; cin >> str;
			if (checkDest(str)) {
				wh = false;
			}
			else cout << "Некорректный ввод, проверьте.\n\n\n";
		}
		Train* ptr = Head;
		cout << left << setw(18) << "Место назначения" << setw(18) << "Номер поезда"
			<< "Время отправления\n";
		while (ptr != NULL) {
			if (str == ptr->destination) {
				cout << left << setw(18) << ptr->destination << '\t';
				cout << setw(10) << ptr->numTr << '\t';
				cout << setw(10) << tranTimeinStr(ptr->timeAr) << endl;
				kr = 1;
			}
			ptr = ptr->Next;
		}
		if (kr == 0) cout << "Поезда направляющиеся в этот пункт отсутствуют.\n\n";
		system("pause");
		return true;
	}

	bool addL(string buff) {
		Train* ptr = Head;
		Train* tr = new Train;
		string dest = "";
		string num = "";
		string timeAr = "";
		int k = 0;
		while (buff[k] != ' ') {
			dest += buff[k]; k++;
		}
		while (buff[k] == ' ') k++;
		while (buff[k] != ' ') {
			if (buff[k] != 32) num += buff[k]; k++;
		}
		while (buff[k] == ' ') k++;
		while (buff[k] != ' ') {
			if (buff[k] == 0) break;
			timeAr += buff[k]; k++;
		}
		if ( checkNum(num) && checkTime(timeAr) && checkDest(dest) && checkKey(atoi(num.c_str()))) {
			tr->numTr = atoi(num.c_str());
			tr->destination = dest;
			tr->timeAr = tranTimeinInt(timeAr);
		}
		else {
			cout << "Какая-то ошибка!\nМесто назначения: " << dest << "\tНомер поезда : " << num << "\tВремя отправления : " << timeAr << "\n";
			return false;
		}
		bool ko = true;
		if (!ptr) {
			Head = tr;
			tr->Next = NULL;
			return true;
		}
		if (ptr->timeAr > tr->timeAr) {
			Head = tr;
			tr->Next = ptr;
			return true;
		}
		if (!ptr->Next && k) k = false;
		while (k && ptr->Next && ptr->Next->timeAr < tr->timeAr) {
			if (ptr->Next) ptr = ptr->Next;
			else k = false;
		}
		if (k) {
			tr->Next = ptr->Next;
			ptr->Next = tr;
		}
		else {
			ptr->Next = tr;
			tr->Next = NULL;
		}
		return true;
	}

	bool mod() {
		if (!Head) {
			cout << "Таблица пуста.\n";
			return false;
		}
		string str;
		cout << "Введите номер поезда, запись о котором вы хотите изменить: ";
		getline(std::cin, str);
		while (!checkNum(str)) {
			cout << "Некорректный ввод.\n";
			cout << "Повторите ввод: ";
			getline(std::cin, str);
		}
		int x = atoi(str.c_str());
		if (!checkKeyM(x)) {
			Train* ptr = Head;
			if (!Head) return false;
			Train* dptr;
			bool k = true;
			if (ptr->numTr == x) {
				Head = ptr->Next;
				delete ptr;
				k = false;
				return true;
			}
			while (k && ptr->Next != NULL) {
				if (ptr->Next->numTr == x) {
					dptr = ptr->Next;
					ptr->Next = dptr->Next;
					delete dptr;
					k = false;
					return true;
				}
				ptr = ptr->Next;
			}
		}
		else {
			cout << "Поезд под таким номером не был найден.\n";
			system("pause");
			return false;
		}
		return false;
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	//string sss = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	List table;
	bool menu = true;
	string istr;
	char in;
	char ins[2];
	while (menu) {
		do {
		system("cls");
		cout << " Главное меню: \n";
		cout << " 1) добавить новую запись\n";
		cout << " 2) изменить запись\n";
		cout << " 3) вывести таблицу на экран\n";
		cout << " 4) отобразить поезда, отправляющиеся в указанный пункт\n";
		cout << " 5) удалить запись\n";
		cout << " 6) сохранить таблицу в файл\n";
		cout << " 7) загрузить таблицу из файла\n";
		cout << " 8) выход\n";
		cout << " ";
		if (!getline(std::cin, istr)) break;
		} while (istr[0] < 49 && istr[0] > 56);
		in = istr[0];
		switch (in)
		{
		case '1': {
			table.add();
			break;
		}
		case '2': {
			bool m = table.mod();
			if (m) table.add();
			system("pause");
			break;
		}
		case '3': {
			table.show();
			break;
		}
		case '4': {
			table.task();
			break;
		}
		case '5': {
			table.remove();
			break;
		}
		case '6': {
			table.save();
			break;
		}
		case '7': {
			string str;
			cout << "Введите имя файла: ";
			cin >> str;
			table.load(str);
			break;
		}		
		case '8': {
			string str;
			bool ex = true;
			while (ex) {
				cout << "Хотите сохранить текущую таблицу в файл?\nД/Н\n";
				getline(std::cin, str);
				if (str == "Д" || str == "д") {
					table.save();
					table.~List();
					ex = false;
				}
				else if (str == "Н" || str == "н") {
					ex = false;
					table.~List();
				}
				else cout << "Ошибка ввода. Введите 'Д' или 'Н'.\n";
			}
			menu = false;
			break;
		}
		default: {
			cout << "Ошибка ввода. Попытайтесь снова.";
			system("pause");
		}
	    break;
	    }	
	}
	return 0;
}
