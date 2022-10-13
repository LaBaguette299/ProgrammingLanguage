#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <sstream>
#include <iostream>

using namespace std;

/**
* \brief Возможные варианты ответа пользователя
* \yes Если пользователь ввёл "1"
* \no Если пользователь ввёл "2"
 */
enum class ansv
{
    yes = 1,
    no = 2
};

/**
* \brief Функция удаления массива "array"
* \param m Количество строк в массиве
* \param array Заполненный массив
*/
int **deletingArray (const size_t m, int **array);

/**
* \brief Функция заполнения массива "array"
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \param checkAns Выбор пользователем варианта заполнения массива
* \return array Возвращение заполненного массива
*/
int **fillingTheArray (const size_t m, const size_t n, const int checkAns);

/**
* \brief Функция автоматического заполнения массива "array"
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \param array Заполненный массив
* \return array Возвращение заполненного массива
*/
int **autoFilling (const size_t m, const size_t n, int **array);

/**
* \brief Функция ручного заполнения массива "array"
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \param array Заполненный массив
* \return array Возвращение заполненного массива
*/
int **manualFilling (const size_t m, const size_t n, int **array);

/**
* \brief Функция выводит массив "array" на экран
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \param array Заполненный массив
* \return Возвращает ноль в случае успеха
*/
string toString (const size_t m, const size_t n, int **array);

/**
* \brief Функция меняет местами минимальные элементы столбцов на противоположные
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \param array Заполненный массив
* \return Возвращение преобразованного массива
*/
int **actOne (const size_t m, const size_t n, int **array);

/**
* \brief Функция удаляет все строки массива "array" содержащие максимальные эллементы
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \param array Заполненный массив
* \return Возвращение преобразованного массива
*/
int **actTwo (size_t m, const size_t n, int **array);

/**
* \brief Функция ищет количство строк которые надо удалить
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \param maxM Массив с координатами максимальных элементов столбцов
* \return Возвращение количества удаляемых строк
*/
size_t countingDeletedRows (const size_t m, const size_t n, size_t *maxM);

/**
* \brief Функция ищет координату "m" максимальных элементов столбцов
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \param array Заполненный массив
* \return Возвращение массива с искомыми координатами
*/
size_t *arrSearchMaxMCoord (const size_t m, const size_t n, int **array);

/**
* \brief Функция ищет координату "m" минимальных по модулю элементов столбцов
* \param m Количество строк в массиве
* \param n Количество столбцов в массиве
* \param array Заполненный массив
* \param minM Массив с координатами минимальных элементов столбцов
* \return Возвращение массива с искомыми координатами
*/
size_t *arrSearchMinMCoord (const size_t m, const size_t n, int **array, size_t *minM);

/**
* \brief Точка входа в программу
* \return Возвращает ноль в случае успеха или один если некорректный ввод
*/
int main()
{
    int **array;
    int sizeString = -1;
    int sizeColumn = -1;
    int checkAns;
    size_t m, n;
    string arrayOutput;

    cout << "Введите размерность массива: (Кол-во строк <пробел> Кол-во столбцов) ";
    cin >> sizeString >> sizeColumn;
    
    if (sizeString < 0 or sizeColumn < 0)
    {
        cout << "Ошибка! Некорректный ввод! \n";
        return 1;
    }
    
    else
    {
        m = sizeString;
        n = sizeColumn;
    }
    
    cout << "Заполнить массив автоматически? \n 1 - да \n 2 - нет \n";
    cin >> checkAns;
    
    array = fillingTheArray (m, n, checkAns);
    
    cout << endl << "Массив: \n";
    arrayOutput = toString (m, n, array);
    cout << arrayOutput;
    
    array = actOne (m, n, array);
    
    cout << endl << "Массив по итогу первого задания: \n";
    arrayOutput = toString (m, n, array);
    cout << arrayOutput;
    
    size_t *maxM = new size_t [n];
    maxM = arrSearchMaxMCoord(m, n, array);
    size_t numberOfDeletedRows = countingDeletedRows (m, n, maxM);
    array = actTwo (m, n, array);

    cout << endl << "Массив по итогу второго задания: \n";
    arrayOutput = toString (m - numberOfDeletedRows, n, array);
    cout << arrayOutput;
    
    if (array != NULL)
        array = deletingArray(m - numberOfDeletedRows, array);
    
    return 0;
}

size_t *arrSearchMaxMCoord (const size_t m, const size_t n, int **array)
{
    size_t *maxM = new size_t [n];
    
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
                if (abs (array [numM][numN]) <= abs (min [numN]))
                {
                    min [numN] = array [numM][numN];
                    minM [numN] = numM;
                }
            }
        }
    }
    
    return  minM;
}

int **actTwo (size_t m, const size_t n, int **array)
{
    size_t *maxM = new size_t [n];
    bool checkingForDeletingRows[m];
    
    maxM = arrSearchMaxMCoord(m, n, array);
    
    for (size_t num = 0; num < n; num++)
        checkingForDeletingRows [maxM [num]] = true;

    size_t numberOfDeletedRows = countingDeletedRows (m, n, maxM);
    
    if (numberOfDeletedRows == m)
        array = deletingArray(m, array);
    
    else
    {
        int **arrayClon;
        
        arrayClon = new int* [m - numberOfDeletedRows];
        
        for (size_t numM = 0; numM < m - numberOfDeletedRows; numM++)
            arrayClon [numM] = new int [n];
        
        size_t roadForArrayClon = 0;
        
        for (size_t numM = 0; numM < m; numM++)
        {
            if (checkingForDeletingRows[numM] != true)
            {
                for (size_t numN = 0; numN < n; numN++)
                {
                    arrayClon [roadForArrayClon][numN] = array [numM][numN];
                }
                roadForArrayClon++;
            }
        }
        
        array = deletingArray(m, array);
        array = arrayClon;
    }

    return array;
}

size_t countingDeletedRows (const size_t m, const size_t n, size_t *maxM)
{
    size_t numberOfDeletedRows = 0;
    bool checkingForRepetition = true;
    
    for (size_t row = 0; row < m; row++)
    {
        for (size_t colum = 0; colum < n; colum++)
        {
            if (maxM [colum] == row and checkingForRepetition == true)
            {
                numberOfDeletedRows++;
                checkingForRepetition = false;
            }
        }
        checkingForRepetition = true;
    }
    
    return numberOfDeletedRows;
}

int **actOne (const size_t m, const size_t n, int **array)
{
    size_t *maxM = new size_t [n];
    size_t *minM = new size_t [n];
    
    maxM = arrSearchMaxMCoord(m, n, array);
    minM = arrSearchMinMCoord(m, n, array, minM);
    
    for (size_t numN = 0; numN < n; numN++)
    {
        int buf = array [maxM [numN]] [numN];
        array [maxM [numN]] [numN] = array [minM [numN]] [numN];
        array [minM [numN]] [numN] = buf;
    }
    
    return array;
}

int **fillingTheArray (const size_t m, const size_t n, const int checkAns)
{
    int **array;
    array = new int* [m];
    for (size_t numM = 0; numM < m; numM++)
        array [numM] = new int [n];
    
    int ansYes = 1;
    
    if (checkAns == ansYes)
    {
        array = autoFilling (m, n, array);
    }
    
    else
    {
        array = manualFilling (m, n, array);
    }
    
    return array;
}

int **autoFilling (const size_t m, const size_t n, int **array)
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

int **manualFilling (const size_t m, const size_t n, int **array)
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

string toString (const size_t m, const size_t n, int **array)
{
    stringstream buffer;
    string deletedArray = "Массив удалён. \n";

    if (array != NULL)
    {
        for (size_t numM = 0; numM < m; numM++)
            {
                for (size_t numN = 0; numN < n; numN++)
                {
                    buffer << array [numM][numN] << "; ";
                }
                buffer << "\n";
            }
        return buffer.str();
    }
    else
        return deletedArray;
}

int **deletingArray (const size_t m, int **arr)
{
    for (size_t index = 0; index < m; index++)
    {
        if (arr[index] != NULL)
        {
            delete[] arr[index];
            arr[index] = nullptr;
        }
    }
    
    delete[] arr;
    return arr = nullptr;
}
