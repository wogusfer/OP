#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	int n, t, a, xm, m, p, xw; // вводим потребующиеся переменные
	cout << "Введите количество элементов массива: "; // запрашиваем у пользователя количество элементов массива
	cin >> n;
	int* A = new int[n]; // образуем массив с n элементами
	for (t = 0; t < n; t++) { // создаём цикл для присваивания значений элементам массива
		cout << "Введите целочисленное значение элемента " << t << ":  ";
		cin >> a;
		A[t] = a;
	}
	xm = A[0]; // для нахождения максимального значения присваиваем Xmax значение первого элемента массива
	for (t = 1; t < n; t++) {
		if (A[t] > xm)
			xm = A[t];
	}
	cout << "Максимальное значение: " << xm << "\n"; // вывод получившегося максимального значения
	xw = 1; // переменная для нахождения произведения
	p = 0; // счётчик количества вхождений в цикл
	m = 0; // счётчик количества нулей
	for (t = 0; t < n; t++) // считаем количество нулей
		if (A[t] == 0)
			m = m + 1;
	if (m < 2)
		cout << "Элементов равных 0 нет в массиве или он один\n";
	else { // начинаем искать произведение
		for (t = 0; t < n; t++) {
			if (p < 1) { // проверка на поиск произведения именно между первым и вторым нулевыми элементами
				if (A[t] == 0) { // проверка на нулевое значение
					do {
						t = t + 1;
						xw = xw * A[t]; // считаем произведение
					} while (A[t + 1] != 0); // условие для умножения
					cout << "Произведение элементов, расположенных между первым и вторым нулевыми элементами массива, равно: " << xw << "\n";
					p = p + 1; // считаем число вхождений в if
				}
			}
		}
	}
	int* b = new int[n]; // создаём вспомогательным массив
	int k = 0;
	for (t = 1; t < n; t += 2) { // переписываем элементы с нечётным индексом в новый массив
		b[k] = A[t];
		k++;
	}
	for (t = 0; t < n; t += 2) { // переписываем элементы с чётным индексом в новый массив
		b[k] = A[t];
		k++;
	}
	cout << "Преобразованный массив: "; // вывод преобразованного массива
	for (t = 0; t < n; t++)
		cout << b[t] << "  ";
	delete A, b;
	return 0;
}
