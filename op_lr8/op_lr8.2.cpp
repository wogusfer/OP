#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <clocale>
#include <cstdio>
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    int n = 0;
    char* a = new char[100];
    FILE* F = fopen("C:\\lr8.txt", "r"); // открываем файл
    if (F == NULL)
    {
        printf("He удается открыть файл.\n"); // если открытие файла прошло некорректно, то вывод сообщения об отсутствии такого файла
        exit(1);
    }
    cout << "Слова, длина которых меньше чем 4 буквы.\n";
    while (!feof(F))
    {
        fgets(a, 100, F); // чтение очередного значения из потока F в переменную a
        if (strlen(a) <= 5)
        {
            cout << a;
            n++; //увеличение количества слов
        }
    }
    fclose(F); // закрытие потока
    cout << "\n";
    cout << "Количество слов: " << n << "\n"; // вывод на экран количества слов
    system("Pause");
    return 0;
}
