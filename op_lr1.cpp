#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	const double pi = std::atan(1.0) * 4;
	double x, z1, z2, a;
	cout << "Введите число в градусах" << endl;
	cin >> x;
	a = x * pi/180;
		z1 =pow(( cos(3 * pi / 8 - a / 4)),2) -pow (( cos(11 * pi / 8 + a / 4)),2);
		z2 = sqrt(2) * sin(a / 2)/2;
		cout << "z1= " << z1 << ", z2= " << z2 << endl;
	
}
