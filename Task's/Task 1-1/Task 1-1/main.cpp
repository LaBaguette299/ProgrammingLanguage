#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <iostream>

using namespace std;

/**
 * \brief Функция расчёта значения "a" по заданной формуле.
 * \param x Первый параметр функции.
 * \param y Второй параметр функции.
 * \param z Третий параметр функции.
 */
double searchA(const double x, const double y, const double z);

/**
 * \brief Функция расчёта значения "b" по заданной формуле.
 * \param y Первый параметр функции.
 * \param z Второй параметр функции.
 * \param a Третий параметр функции.
 */
double searchB(const double y, const double z, const double a);

/**
 * \brief Точка входа в программу.
 * \return Возвращает 0 в случае успеха.
 */
int main()
{
    const double x = -0.5;
    const double y = 1.7;
    const double z = 0.44;

    double a = searchA(x, y, z);
    double b = searchB(y, z, a);

    cout << "Given: " << endl << "X = " << x << endl << "Y = " << y << endl << "Z = " << z << endl;
    cout << "Answer: " << endl << "A = " << a << endl << "B = " << b << endl;

    return 0;
}

double searchA(const double x, const double y, const double z)
{
    return exp(-y * z) * sin(x * y - z) - sqrt( abs(y * z + x) );
}

double searchB(const double y, const double z, const double a)
{
    return y * sin(a * pow(z, 2) * cos(2.0 * z) - 1.0);
}
