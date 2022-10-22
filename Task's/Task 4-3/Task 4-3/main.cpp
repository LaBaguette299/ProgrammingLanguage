#include <iostream>
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <sstream>
#include <algorithm>
#include <array>
#include <random>
#include <ctime>

/**
* \brief Возможные варианты ответа пользователя
* \yes Если пользователь ввёл "1"
* \no Если пользователь ввёл "2"
 */
enum class answer
{
    yes = 1,
    no = 2
};

/**
 * \brief Проверка корректности ввода размерности массива
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \return true Если ввод корректен
 * \return false Если ввод некорректен
 */
bool ceckingInput(const int rows, const int colums);

/**
 * \brief Создание массива array
 * \param rows Количество строк
 * \param colums Количество столбцов
 */
int** creatingArray(const size_t rows, const size_t colums);

/**
 * \brief Ручное заполнение массива
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \return array Возвращение заполненного массива
 */
int** manualFillingArray(const size_t rows, const size_t colums);

/**
 * \brief Автоматическое заполнение массива
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \return array Возвращение заполненного массива
 */
int** autoFillingArray(const size_t rows, const size_t colums);

/**
 * \brief Функция преобразующая array в string для удобства вывода
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \param array Массив
 * \return buffer.str() Возвращение string с массивом
 * \return deletedArray Возвращает сообщение о том, что масств удалён
 */
std::string toString(const size_t rows, const size_t colums, int** array);

/**
 * \brief Функция выполняет задание 1 (поменять местами минимальный и максимальный по модулю элементы столбцов)
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \param array Массив
 * \return array Возвращает изменёный массив
 */
int** actOne(const size_t rows, const size_t colums, int** array);

/**
 * \brief Функция ищет максимальный по модулю элемент каждого столбца
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \param array Массив
 * \return max Возвращает список максимальных элементов
 */
int* findAbsMaxElements(const size_t rows, const size_t colums, int** array);

/**
 * \brief Функция ищет минимальный по модулю элемент каждого столбца
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \param array Массив
 * \return min Возвращает список минимальных элементов
 */
int* findAbsMinElements(const size_t rows, const size_t colums, int** array);

/**
 * \brief Функция удаляет массив
 * \param rows Количество строк
 * \param arr Удаляемый массив
 * \return Возвращает удалённый массив
 */
int **deletingArray(const size_t rows, int **arr);

/**
 * \brief Функция выполняет задание 2 (удалить строки содержащие максимальные элементы столбцов)
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \param array Массив
 * \return array Возвращает изменёный массив
 */
int** actTwo(const size_t rows, const size_t colums, int** array);

/**
 * \brief Функция ищет строки для удаления
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \param array Массив
 * \return rowsToDell Возвращает список строк для удаления
 */
bool* findRowsToDell(const size_t rows, const size_t colums, int** array);

/**
 * \brief Функция ищет максимальный элемент каждого столбца
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \param array Массив
 * \return max Возвращает список максимальных элементов
 */
int* findMaxElements(const size_t rows, const size_t colums, int** array);

/**
 * \brief Функция ищет количество удаляемых строк
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \param array Массив
 * \return max Возвращает список максимальных элементов
 */
size_t findNumOfDelletedRows(const size_t rows, const size_t colums, int** array);

/**
 * \brief Точка входа в программу
 * \return 0 Возвращает ноль в случае успеха
 * \return 1 Возвращает один если некорректный ввод размерности массива
 */
int main()
{
    std::cout << "Введите размерность массива:\n Количество строк: ";
    int checkRows;
    std::cin >> checkRows;
    
    std::cout << " Количество столбцов: ";
    int checkColums;
    std::cin >> checkColums;
    
    if (!ceckingInput(checkRows, checkColums))
    {
        std::cout << "Некорректный размер!\n";
        return 1;
    }
    
    const size_t rows = checkRows;
    const size_t colums = checkColums;
    
    std::cout << "Выберите способ заполнения массива:\n 1-Ручное\n 2-Автоматическое\n ";
    int ans;
    std::cin >> ans;
        
    answer castedAns = static_cast<answer>(ans);
    
    int** array;
        
    if (castedAns == answer::yes)
    {
        array = manualFillingArray(rows, colums);
        std::cout << toString(rows, colums, array);
    }
    else
    {
        array = autoFillingArray(rows, colums);
        std::cout << "Массив:\n" << toString(rows, colums, array) << std::endl;
    }
    
    array = actOne(rows, colums, array);
    std::cout << "Массив по итогу первого задания:\n" << toString(rows, colums, array) << std::endl;
    
    size_t numOfDelletedRows = findNumOfDelletedRows(rows, colums, array);
    
    array = actTwo(rows, colums, array);
    std::cout << "Массив по итогу второго задания:\n" << toString(rows - numOfDelletedRows, colums, array) << std::endl;
    
    if(array != nullptr)
    {
        array = deletingArray(rows - numOfDelletedRows, array);
    }
    
    return 0;
}

bool ceckingInput(const int rows, const int colums)
{
    if (rows > 0 && colums > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int** creatingArray(const size_t rows, const size_t colums)
{
    int** array = new int* [rows];
    for (size_t numRows = 0; numRows < rows; numRows++)
        array [numRows] = new int [colums];
    return array;
}

int** manualFillingArray(const size_t rows, const size_t colums)
{
    int** array = creatingArray(rows, colums);
    
    for(size_t numRows = 0; numRows < rows; numRows++)
    {
        for(size_t numColums = 0; numColums < colums; numColums++)
        {
            std::cout << "Элемент " << numRows + 1 << "." << numColums + 1 << ": ";
            std::cin >> array[numRows][numColums];
        }
    }
    
    return array;
}

int** autoFillingArray(const size_t rows, const size_t colums)
{
    int** array = creatingArray(rows, colums);
    
    srand(time(0));
    
    for(size_t numRows = 0; numRows < rows; numRows++)
    {
        for(size_t numColums = 0; numColums < colums; numColums++)
        {
            array[numRows][numColums] = 100 - rand() % 200;
        }
    }
    
    return array;
}

std::string toString(const size_t rows, const size_t colums, int** array)
{
    std::stringstream buffer;
    std::string deletedArray = "Массив удалён. \n";

    if (array != nullptr)
    {
        for (size_t numRows = 0; numRows < rows; numRows++)
        {
            for (size_t numColums = 0; numColums < colums; numColums++)
            {
                buffer << array [numRows][numColums] << "; ";
            }
            buffer << "\n";
        }
        return buffer.str();
    }
    else
        return deletedArray;
}

int** actOne(const size_t rows, const size_t colums, int** array)
{
    int* max = findAbsMaxElements(rows, colums, array);
    int* min = findAbsMinElements(rows, colums, array);
    size_t buffOfNumRowsForMin;
    size_t buffOfNumRowsForMax;
    
    for(size_t numColums = 0; numColums < colums; numColums++)
    {
        for(size_t numRows = 0; numRows < rows; numRows++)
        {
            if(array[numRows][numColums] == min[numColums])
            {
                buffOfNumRowsForMin = numRows;
            }
            
            if(array[numRows][numColums] == max[numColums])
            {
                buffOfNumRowsForMax = numRows;
            }
        }
        array[buffOfNumRowsForMax][numColums] = min[numColums];
        array[buffOfNumRowsForMin][numColums] = max[numColums];
    }
    
    return array;
}

int* findAbsMaxElements(const size_t rows, const size_t colums, int** array)
{
    int* max = new int [colums];

    for(size_t numColums = 0; numColums < colums; numColums++)
    {
        int buffMax = array[0][numColums];
        for(size_t numRows = 0; numRows < rows; numRows++)
        {
            if(abs(buffMax) < abs(array[numRows][numColums]))
            {
                buffMax = array[numRows][numColums];
            }
        }
        max[numColums] = buffMax;
    }
    
    return max;
}

int* findAbsMinElements(const size_t rows, const size_t colums, int** array)
{
    int* min = new int [colums];

    for(size_t numColums = 0; numColums < colums; numColums++)
    {
        int buffMin = array[0][numColums];
        for(size_t numRows = 0; numRows < rows; numRows++)
        {
            if(abs(buffMin) > abs(array[numRows][numColums]))
            {
                buffMin = array[numRows][numColums];
            }
        }
        min[numColums] = buffMin;
    }
    
    return min;
}

int **deletingArray(const size_t rows, int **arr)
{
    for (size_t index = 0; index < rows; index++)
    {
        if (arr[index] != nullptr)
        {
            delete[] arr[index];
            arr[index] = nullptr;
        }
    }
    
    delete[] arr;
    return arr = nullptr;
}

int** actTwo(const size_t rows, const size_t colums, int** array)
{
    bool* rowsToDell = findRowsToDell(rows, colums, array);
    size_t numOfDelletedRows = findNumOfDelletedRows(rows, colums, array);
    
    if(rows - numOfDelletedRows == 0)
    {
        return nullptr;
    }
    
    int** arrayClon = creatingArray(rows - numOfDelletedRows, colums);
    
    size_t numRowsForArrayClon = 0;
    
    for(size_t numRows = 0; numRows < rows; numRows++)
    {
        if(!rowsToDell[numRows])
        {
            for(size_t numColums = 0; numColums < colums; numColums++)
            {
                arrayClon[numRowsForArrayClon][numColums] = array[numRows][numColums];
            }
            numRowsForArrayClon++;
        }
    }
    
    return arrayClon;
}

bool* findRowsToDell(const size_t rows, const size_t colums, int** array)
{
    bool* rowsToDell = new bool [rows];
    int* max = findMaxElements(rows, colums, array);
    
    for(size_t numColums = 0; numColums < colums; numColums++)
    {
        for(size_t numRows = 0; numRows < rows; numRows++)
        {
            if(array[numRows][numColums] == max[numColums])
            {
                rowsToDell[numRows] = true;
            }
        }
    }
    
    return rowsToDell;
}

int* findMaxElements(const size_t rows, const size_t colums, int** array)
{
    int* max = new int [colums];

    for(size_t numColums = 0; numColums < colums; numColums++)
    {
        int buffMax = array[0][numColums];
        for(size_t numRows = 0; numRows < rows; numRows++)
        {
            if(buffMax < array[numRows][numColums])
            {
                buffMax = array[numRows][numColums];
            }
        }
        max[numColums] = buffMax;
    }
    
    return max;
}

size_t findNumOfDelletedRows(const size_t rows, const size_t colums, int** array)
{
    size_t numOfDelletedRows = 0;
    
    bool* rowsToDell = findRowsToDell(rows, colums, array);
    
    for(size_t index = 0; index < rows; index++)
    {
        if(rowsToDell[index])
        {
            numOfDelletedRows++;
        }
    }
    
    return numOfDelletedRows;
}
