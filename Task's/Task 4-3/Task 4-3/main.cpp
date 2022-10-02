#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <iostream>

using namespace std;

/**
* \brief Функция заполнения массива "array"
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \param checkAns Выбор пользователем варианта заполнения массива
* \return array Возвращение преобразованного массива
*/
int **arrFill (size_t m, size_t n, string checkAns);

/**
* \brief Функция выводит массив "array" на экран
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \*array Заполненный массив
* \return Возвращает ноль в случае успеха
*/
int **arrOutput (size_t m, size_t n, int **array);

/**
* \brief Функция меняет местами минимальные элементы столбцов на противоположные
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \*array Заполненный массив
* \return Возвращение преобразованного массива
*/
int **arrActOne (size_t m, size_t n, int **array);

/**
* \brief Функция удаляет все строки массива "array" содержащие максимальные эллементы
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \*array Заполненный массив
* \return Возвращение преобразованного массива
*/
int **arrActTwo (size_t m, size_t n, int **array);

/**
* \brief Точка входа в программу
* \return Возвращает ноль в случае успеха
*/
int main()
{
    int numN, **array;
    size_t m, n;
    numN = 0;
    
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
    
    return 0;
}
//
//
//
//
//
int **arrActTwo (size_t m, size_t n, int **array)
{
    int *max = new int [n];
    size_t *maxM = new size_t [n];
    
    int numM = 0;
    for (int numN = 0; numN < n; numN++)
    {
        max [numN] = array [0][numN];
        if (numM < m)
        {
            for (int numM = 0; numM < m; numM++)
            {
                if (array [numM][numN] >= max [numN])
                {
                    max [numN] = array [numM][numN];
                    maxM [numN] = numM;
                }
            }
        }
    }
    
    size_t *checkStr = new size_t [m];

    for (int numN = 0; numN < n; numN++)
    {
        checkStr [maxM [numN]] = 1;
    }
    
    for (int numN = 0; numN < n; numN++)
    {
        if (m != 0)
            for (int numM = 0; numM < m; numM++)
            {
                if (maxM [numN] == numM and checkStr [numM] == 1)
                {
                    int **arrClon = new int* [m - 1];
                    int numNforArrClon = 0;
                    
                    for(int numN = 0; numN < m; numN++)
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
//
//
//
//
//
int **arrActOne (size_t m, size_t n, int **array)
{
    int *min = new int [m];
    int *max = new int [m];
    size_t *maxN = new size_t [m], *minN = new size_t [m];
    size_t *maxM = new size_t [n], *minM = new size_t[n];
    
    int numM = 0;
    for (int numN = 0; numN < n; numN++)
    {
        max [numN] = array [0][numN];
        min [numN] = array [0][numN];
        if (numM < m)
        {
            for (int numM = 0; numM < m;)
            {
                if (abs(array [numM][numN]) >= abs(max [numN]))
                {
                    max [numN] = array [numM][numN];
                    maxN [numN] = numN;
                    maxM [numN] = numM;
                }
                
                if (abs(array [numM][numN]) <= abs(min [numN]))
                {
                    min [numN] = array [numM][numN];
                    minN [numN] = numN;
                    minM [numN] = numM;
                }
                numM++;
            }
        }
    }
    
    for (int numN = 0; numN < n; numN++)
    {
        array [maxM [numN]] [maxN [numN]] = min [numN];
        array [minM [numN]] [minN [numN]] = max [numN];
    }
    
    return array;
}
//
//
//
//
//
int **arrFill (size_t m, size_t n, string checkAns)
{
    int **array;
    array = new int* [m];
    for (int numM = 0; numM < m; numM++)
        array [numM] = new int [n];
    
    srand(time(NULL));
    
    string ansYes = "Yes";
    string ansyes = "yes";
    string ansNo = "No";
    
    if (checkAns == ansYes or checkAns == ansyes)
    {
        int numN = 0;
        for (int numM = 0; numM < m;)
        {
            if (numN <= n)
            {
                for (int numN = 0; numN < n;)
                {
                    array [numM][numN] = 100 - rand() %200;
                    numN++;
                }
            }
            numM++;
        }
    }
    
    else
    {
        int numN = 0;
        int var;
        
        for (int numM = 0; numM < m;)
        {
            if (numN <= n)
            {
                for (int numN = 0; numN < n;)
                {
                    cout << "Элемент " << numM << "." << numN << ": ";
                    cin >> var;
                    
                    array [numM][numN] = var;
                    numN++;
                }
            }
            numM++;
        }
    }
    
    return array;
}
//
//
//
//
//
int **arrOutput (size_t m, size_t n, int **array)
{
    int numN = 0;
    if (m != 0)
        for (int numM = 0; numM < m;)
        {
            cout << endl;
            if (numN <= n)
            {
                for (int numN = 0; numN < n;)
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
