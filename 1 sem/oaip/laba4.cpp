#include <iostream>
#include <cmath>
using namespace std;


int main()
{
    setlocale(LC_ALL, "RUS");
    double y, c, d, x, z, phi;
    int choice_phi;
    cout << "Введите c" << endl;
    if (!(cin >> c))
    {
        cout << "Некорректный ввод " << endl;
        return 0;
    }
    cout << "Введите d" << endl;
    if (!(cin >> d))
    {
        cout << "Некорректный ввод" << endl;
        return 0;
    }
    cout << "Введите z" << endl;
    if (!(cin >> z))
    {
        cout << "Некорректный ввод" << endl;
        return 0;
    }
    if (z < 0)    
    {
        x = pow(z, 2) - z;
    }
    else
    {
        x = pow(z, 3);
    }
    cout << "Выберете вариант phi" << endl;
    cout << "1. phi= 2 * x  " << endl;
    cout << "2. phi = pow(x,2)" << endl;
    cout << "3. phi = x/3" << endl;
    if (!(cin >> choice_phi))
    {
        cout << "Некорректный ввод" << endl;
        return 0;
    }
    switch (choice_phi)
    {
    case 1:
        cout << "Вы выбрали phi= 2*x" << endl;
        phi = 2 * x;
        break;
    case 2:
        cout << "Вы выбрали phi=pow(x,2)" << endl;
        phi = pow(x, 2);
        break;
    case 3:
        if (x == 0) {
            cout << "Ошибка" << endl;
            return 0;
        }
        cout << "Вы выбрали phi=x/3" << endl;
        phi = x / 3;
        break;
    default:
        cout << "Некорректный ввод" << endl;
        return 0;

    }
    y = pow(sin(c * phi + pow(d, 2) + pow(x, 2)), 3);
    cout << "y = " << y << endl;
    return 0;
}

// a>b? f=fghj:f=0

