#include<iostream>
#include<string>
#include<clocale>
#include<fstream>
using namespace std;

int main() 
{
    setlocale(LC_ALL, "rus");
    int n = 0;
    char* a = new char[100];
    ifstream F;
    F.open("C:\\lr8.txt", ios::in); // открываем файл
    if (F) //цикл для чтения значений из файла; выполнение цикла прервется, когда достигнем конца файла
    {
        cout << "Слова, длина которых меньше чем 4 буквы.\n";
        while (!F.eof())
        {
            F >> a; // чтение очередного значения из потока F в переменную a
            if (strlen(a) <= 4)
            {
                cout << a << "\t";
                n++; // увеличение количества считанных чисел
            }
        }
        F.close(); // закрытие потока
        cout << "\n";
        cout << "Количество слов: " << n-1 << "\n"; //вывод на экран количества считанных чисел
    }
    else cout << " Файл не существует\n"; // если открытие файла прошло некорректно, то вывод сообщения об отсутствии такого файла
    system("pause");
    return 0;
}
