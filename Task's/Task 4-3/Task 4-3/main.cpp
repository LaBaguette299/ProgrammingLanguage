#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <iostream>

using namespace std;

/**
* \brief Функция заполнения массива "array"
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \param checkAns Выбор пользователем варианта заполнения массива
* \return array Возвращение заполненного массива
*/
int **arrFill (const size_t m, const size_t n, const string checkAns);

/**
* \brief Функция автоматического заполнения массива "array"
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \return array Возвращение заполненного массива
*/
int **arrFillAuto (const size_t m, const size_t n, int **array);

/**
* \brief Функция ручного заполнения массива "array"
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \return array Возвращение заполненного массива
*/
int **arrFillManually (const size_t m, const size_t n, int **array);

/**
* \brief Функция выводит массив "array" на экран
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \*array Заполненный массив
* \return Возвращает ноль в случае успеха
*/
int **arrOutput (const size_t m, const size_t n, int **array);

/**
* \brief Функция меняет местами минимальные элементы столбцов на противоположные
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \*array Заполненный массив
* \return Возвращение преобразованного массива
*/
int **arrActOne (const size_t m, const size_t n, int **array);

/**
* \brief Функция удаляет все строки массива "array" содержащие максимальные эллементы
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \*array Заполненный массив
* \return Возвращение преобразованного массива
*/
int **arrActTwo (size_t m, const size_t n, int **array);

/**
* \brief Функция ищет координату "m" максимальных элементов столбцов
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \*array Заполненный массив
*\*maxM Массив с координатами
* \return Возвращение массива с искомыми координатами
*/
size_t *arrSearchMaxMCoord (const size_t m, const size_t n, int **array, size_t *maxM);

/**
* \brief Функция ищет координату "m" минимальных элементов столбцов
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \*array Заполненный массив
*\*minM Массив с координатами
* \return Возвращение массива с искомыми координатами
*/
size_t *arrSearchMinMCoord (const size_t m, const size_t n, int **array, size_t *minM);

/**
* \brief Точка входа в программу
* \return Возвращает ноль в случае успеха
*/
int main()
{
    int **array;
    size_t m, n;
    
    string checkAns;
    
    cout << "Введите размерность массива: (Кол-во строк <пробел> Кол-во столбцов) ";
    cin >> m >> n;
    
    cout << "Заполнить массив автоматически? (Yes/No) ";
    cin >> checkAns;
    
    array = arrFill(m, n, checkAns);
    
    cout << endl << "Массив: ";
    arrOutput(m, n, array);
    
    array = arrActOne(m, n, array);
    
    cout << endl << "Массив по итогу первого задания:";
    arrOutput(m, n, array);
    
    array = arrActTwo(m, n, array);
    
    delete [] array;
    
    return 0;
}

size_t *arrSearchMaxMCoord (const size_t m, const size_t n, int **array, size_t *maxM)
{
    int *max = new int [n];
    
    size_t numM = 0;
    for (size_t numN = 0; numN < n; numN++)
    {
        max [numN] = array [0][numN];
        if (numM < m)
        {
            for (size_t numM = 0; numM < m; numM++)
            {
                if (array [numM][numN] >= max [numN])
                {
                    max [numN] = array [numM][numN];
                    maxM [numN] = numM;
                }
            }
        }
    }
    
    return  maxM;
}

size_t *arrSearchMinMCoord (const size_t m, const size_t n, int **array,  size_t *minM)
{
    int *min = new int [n];
    
    size_t numM = 0;
    for (size_t numN = 0; numN < n; numN++)
    {
        min [numN] = array [0][numN];
        if (numM < m)
        {
            for (size_t numM = 0; numM < m; numM++)
            {
                if (array [numM][numN] <= min [numN])
                {
                    min [numN] = array [numM][numN];
                    minM [numN] = numM;
                }
            }
        }
    }
    
    return  minM;
}

int **arrActTwo (size_t m, const size_t n, int **array)
{
    size_t *maxM = new size_t [n];
    
    maxM = arrSearchMaxMCoord(m, n, array, maxM);
    
    size_t *checkStr = new size_t [m];

    for (size_t numN = 0; numN < n; numN++)
    {
        checkStr [maxM [numN]] = 1;
    }
    
    for (size_t numN = 0; numN < n; numN++)
    {
        if (m != 0)
            for (size_t numM = 0; numM < m; numM++)
            {
                if (maxM [numN] == numM and checkStr [numM] == 1)
                {
                    int **arrClon = new int* [m - 1];
                    size_t numNforArrClon = 0;
                    
                    for(size_t numN = 0; numN < m; numN++)
                        if(numN != numM)
                        {
                            arrClon [numNforArrClon] = array [numN];
                            numNforArrClon++;
                        }
                    
                    delete [] array;
                    checkStr[numM] = 0;
                    array = arrClon;
                    m = m - 1;
                }
            }
        else
            delete [] array;
    }
    
    cout << endl << "Массив по итогу второго задания: ";
    arrOutput(m, n, array);

    return array;
}

int **arrActOne (const size_t m, const size_t n, int **array)
{
    size_t *maxM = new size_t [n], *minM = new size_t[n];
    
    maxM = arrSearchMaxMCoord(m, n, array, maxM);
    minM = arrSearchMinMCoord(m, n, array, minM);
    
    for (size_t numN = 0; numN < n; numN++)
    {
        int buf = array [maxM [numN]] [numN];
        array [maxM [numN]] [numN] = array [minM [numN]] [numN];
        array [minM [numN]] [numN] = buf;
    }
    
    return array;
}

int **arrFill (const size_t m, const size_t n, const string checkAns)
{
    int **array;
    array = new int* [m];
    for (size_t numM = 0; numM < m; numM++)
        array [numM] = new int [n];
    
    string ansYes = "Yes";
    string ansyes = "yes";
    string ansNo = "No";
    
    if (checkAns == ansYes or checkAns == ansyes)
    {
        array = arrFillAuto (m, n, array);
    }
    
    else
    {
        array = arrFillManually (m, n, array);
    }
    
    return array;
}

int **arrFillAuto (const size_t m, const size_t n, int **array)
{
    srand(time(NULL));
    
    size_t numN = 0;
    for (size_t numM = 0; numM < m;)
    {
        if (numN <= n)
        {
            for (size_t numN = 0; numN < n;)
            {
                array [numM][numN] = 100 - rand() %200;
                numN++;
            }
        }
        numM++;
    }
    return array;
}

int **arrFillManually (const size_t m, const size_t n, int **array)
{
    size_t numN = 0;
    int var;
    
    for (size_t numM = 0; numM < m;)
    {
        if (numN <= n)
        {
            for (size_t numN = 0; numN < n;)
            {
                cout << "Элемент " << numM << "." << numN << ": ";
                cin >> var;
                
                array [numM][numN] = var;
                numN++;
            }
        }
        numM++;
    }
    
    return array;
}

int **arrOutput (const size_t m, const size_t n, int **array)
{
    size_t numN = 0;
    if (m != 0)
        for (size_t numM = 0; numM < m;)
        {
            cout << endl;
            if (numN <= n)
            {
                for (size_t numN = 0; numN < n;)
                {
                    cout << array [numM][numN] << "; ";
                    numN++;
                }
            }
            numM++;
        }
    
    else
        cout << "Массив удалён." ;
    
    cout << endl;
    return 0;
}
