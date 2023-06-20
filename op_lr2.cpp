#include<cmath>
#include<iostream>
#include<stdio.h>
#include<clocale>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    double x, y;
    cout << "Введите координаты точки.Если будут введены не числовые значения, то значения координат будут приравнены к нулю\n";
    cout << "Введите абсциссу точки: ";
    cin >> x;
    cout << "Введите ординату точки: ";
    cin >> y;
    if ((((x <= 0) && (x >= -1)) && ((y <= 0) && (y >= -1))) || (((x >= 0) && (x <= 1)) && ((y >= 0) && (y <= 1)) && ((x * x + y * y) <= 1)))
    {
        cout << "Точка находится в области";
    }
    else
    {
        cout << "Точка находится вне области\n";
    }
    for (y = 2; y > -2; y -= 0.1) {
        for (x = -2; x < 2; x += 0.1) {
            if ((((x <= 0) && (x >= -1)) && ((y <= 0) && (y >= -1))) || (((x >= 0) && (x <= 1)) && ((y >= 0) && (y <= 1)) && ((x * x + y * y) <= 1)))
                cout << "x";
            else
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}
