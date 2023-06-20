#include <iostream>
#include <cmath>
using namespace std;

float calc(float a, float b, float c, float xn, float xk, float dx) {
	float y = 0;
	cout << "x\ty\n";
	for (xn; xn <= xk; xn = xn + dx) { // создаём цикл для решения системы
		if (xn < 5 && c != 0) {
			y = -a * pow(xn, 2) - b;
		}
		if (xn < 5 && c == 0) {
			cout << xn << "\t" << "Нет решения\n";
			break;
		}
		if (xn == 5 && c != 0) {
			y = -xn / c;
		}
		if (xn == 5 && c == 0) {
			cout << xn << "\t" << "Нет решения\n";
			break;
		}
		if (xn > 5 && c == 0) {
			y = (xn - a) / xn;
		}
		if (xn > 5 && c != 0) {
			y = -xn / c;
		}
		cout << xn << "\t" << y << "\n";
	}
	return y;
}

int main()
{
	setlocale(LC_ALL, "rus");
	float a = 0, b = 0, c = 0, y, xn = 0, xk = 0, dx = 0; // задаём нужные нам переменные 
	cout << "Введите числа a, b и c\n"; // просим ввести нужные переменные
	cin >> a >> b >> c;
	cout << "Введите начало, конец промежутка и шаг\n";
	cin >> xn >> xk >> dx;
	if (xn < xk && dx < abs(xk - xn)) { // проверка на корректность ввода данных
		y = calc(a, b, c, xn, xk, dx);
	}
	else
		cout << "Некорректный ввод данных";
	return 0;
}
