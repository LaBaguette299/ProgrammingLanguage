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
    yes,
    no
};

/**
 * \brief Проверка корректности ввода размерности массива
 * \param size Размер строки/столбца для проверки на корректность
 * \return false Если ввод некорректен
 */
size_t getSize(const int size);

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
 */
void manualFillingArray(int** array, const size_t rows, const size_t colums);

/**
 * \brief Автоматическое заполнение массива
 * \param rows Количество строк
 * \param colums Количество столбцов
 */
void autoFillingArray(int** array, const size_t rows, const size_t colums);

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
 */
void actOne(const size_t rows, const size_t colums, int** array); // !

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
 */
void deletingArray(const size_t rows, int**& arr);

/**
 * \brief Функция выполняет задание 2 (удалить строки содержащие максимальные элементы столбцов)
 * \param rows Количество строк
 * \param colums Количество столбцов
 * \param array Массив
 */
void actTwo(const size_t rows, const size_t colums, int**& array);

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

    try
    {
        getSize(checkRows);
    }
    catch (std::out_of_range)
    {
        std::cout << "Вы ввели неправильный ответ!\n";
        return 1;
    }
    
    const size_t rows = getSize(checkRows);
    
    std::cout << " Количество столбцов: ";
    int checkColums;
    std::cin >> checkColums;
    
    try
    {
        getSize(checkColums);
    }
    catch (std::out_of_range)
    {
        std::cout << "Вы ввели неправильный ответ!\n";
        return 1;
    }
    
    const size_t colums = getSize(checkColums);
    
    std::cout << "Выберите способ заполнения массива:\n "
    << static_cast<int>(answer::yes) << " - Ручное\n "
    << static_cast<int>(answer::no) << " - Автоматическое\n ";
    
    int ans;
    std::cin >> ans;
        
    int** array = creatingArray(rows, colums);

    try
    {
        const auto chosen = static_cast<answer>(ans);

        switch (chosen)
        {
            case answer::no:
            {
                autoFillingArray(array, rows, colums);
                break;
            }
            case answer::yes:
            {
                manualFillingArray(array, rows, colums);
                break;
            }
            default :
                std::cout << "Вы ввели неправильный ответ!\n";
                return 1;
        }
    }
    catch (std::out_of_range&)
    {
        std::cout << "Вы ввели неправильный ответ!\n";
        return 1;
    }

    std::cout << "Массив:\n" << toString(rows, colums, array) << "\n";
    
    actOne(rows, colums, array);
    std::cout << "Массив по итогу первого задания:\n" << toString(rows, colums, array) << std::endl;
    
    size_t numOfDelletedRows = findNumOfDelletedRows(rows, colums, array);
    
    actTwo(rows, colums, array);
    std::cout << "Массив по итогу второго задания:\n" << toString(rows - numOfDelletedRows, colums, array) << std::endl;
    
    if(array != nullptr)
    {
        deletingArray(rows - numOfDelletedRows, array);
    }
    
    return 0;
}

size_t getSize(const int size)
{
    if (size < 0)
    {
        throw std::out_of_range("Некорректный размер. Значение меньше либо равно 0.");
    }
    
    return size;
}

int** creatingArray(const size_t rows, const size_t colums)
{
    int** array = new int* [rows];
    for (size_t numRows = 0; numRows < rows; numRows++)
        array [numRows] = new int [colums];
    return array;
}

void manualFillingArray(int** array, const size_t rows, const size_t colums)
{
    for(size_t numRows = 0; numRows < rows; numRows++)
    {
        for(size_t numColums = 0; numColums < colums; numColums++)
        {
            std::cout << "Элемент " << numRows + 1 << "." << numColums + 1 << ": ";
            std::cin >> array[numRows][numColums];
        }
    }
}

void autoFillingArray(int** array, const size_t rows, const size_t colums)
{
    std::random_device rd;
    std::mt19937_64 mt_rand(rd());
    std::uniform_int_distribution<int> dist(-100, 100);
        
    for(size_t numRows = 0; numRows < rows; numRows++)
    {
        for(size_t numColums = 0; numColums < colums; numColums++)
        {
            array[numRows][numColums] = dist(mt_rand);
        }
    }
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

void actOne(const size_t rows, const size_t colums, int** array)
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

void deletingArray(const size_t rows, int**& arr)
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
    arr = nullptr;
}

void actTwo(const size_t rows, const size_t colums, int**& array)
{
    bool* rowsToDell = findRowsToDell(rows, colums, array);
    size_t numOfDelletedRows = findNumOfDelletedRows(rows, colums, array);
    
    if(rows - numOfDelletedRows == 0)
    {
        return deletingArray(rows, array);
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
    
    array = arrayClon;
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
