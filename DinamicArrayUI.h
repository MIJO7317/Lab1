#pragma once

#define RESET   "\033[0m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[1;33m"
#define CYAN	"\033[0;36m"

/*Структуры:*/

//Структура динамического массива
typedef struct Array Array;
//Структура слова с динамическим массивом позиций
typedef struct Word Word;

/*Технические функции:*/

//Очистка потока ввода Stdin от символов
void ClearStdin();
//Вывод сообщения об ошибке
void Error(const char* msg);
//Вывод об успешном выполнении
void Success(const char* msg);

/*Функции определения размера:*/

//Количество элементов динамического массива arr
size_t Size(Array* arr);

/*Функции получения элемента:*/

//Возвращает указатель на слово, находящееся под номером index в списке слов list, если index выходит за пределы списка list, то возвращает NULL
Word* GetWord(Array* list, size_t index);
//Возвращает строку из данного слова, если word это NULL, то вернет NULL
Array* GetWordStr(Word* word);
//Возвращает массив позиций из данного слова, если word это NULL, то вернет NULL
Array* GetWordPositions(Word* word);
//Возвращает символ под номером index из строки str, если index выходит за пределы строки str, то возвращает '\0'
char GetCharElement(Array* str, size_t index);
//Возвращает указатель на целое число под номером index в динамическом массиве arr, если index выходит за пределы массива arr, то возвращает NULL
int* GetIntElement(Array* arr, size_t index);

/*Деструкторы:*/

//Освобождение памяти указателя ptr
void Delete(void* ptr);
//Освобождение памяти динамического массива arr
void DeleteArray(Array* arr);
//Освобождение памяти слова word
void DeleteWord(Word* word);
//Освобождение памяти списка слов list
void DeleteList(Array* list);

/*Функции изменения/добавления элемента:*/

//Копирует значение value в элемент динамического массива arr под номером index
void SetElement(Array* arr, size_t index, void* value);
//Добаляет элемент в конец строки
void PushBackChar(Array* str, char simbol);
//Добавляет элемент в конец массива (не работает со строками, для них используйте процедуру PushBackChar)
void PushBack(Array* arr, void* value);

/*Конструкторы:*/

//Создание пустой строки
Array* CreateEmptyString();
//Создание строки типа Array* из строки str типа char*
Array* CreateString(char* str);
//Создание динамического массива целых чисел размера count (все элементы по умолчанию 0)
Array* CreateInt(size_t count);
//Создание списка слов размера count (все элементы по умолчанию это пустые слова)
Array* CreateWordList(size_t count);
//Создание строки из консоли
Array* InputString();

/*Функции вывода:*/

//Вывод строки
void OutString(Array* str);
//Вывод целочисленного динамического массива
void OutIntArray(Array* arr);
//Вывод списка слов с их позициями
void OutWordList(Array* list);

/*Предикаты и сложные функции*/

//Возвращает true, если в строке str найден символ simbol, в противном случае возвращает false
bool CharInString(Array* str, char simbol);
//Возвращает количество всех слов в строке str с разделителями, находящимися в строке separators
size_t NumberWords(Array* str, Array* separators);
//Создаёт и возвращает строку в которой записано слово, находящееся по номеру number_word (начиная с 0), в строке str
Array* FindWord(Array* str, size_t number_word, Array* separators);
//Возвращает true, если строки str1 и str2 равны, без учета регистра, в противном случае возвращает false
bool EqualStrings(Array* str1, Array* str2);
//Возвращает true, если слово word типа Array* находится в списке list и записывет номер позиции в position_in_list, в противном случае возвращает false и position_in_list не меняется
bool WordInList(Array* list, Array* word, size_t* position_in_list);
//Возвращает true, если слово word типа Array* находится в строке str с разделителями, находящимися в строке separators, в противном случае возвращает false
bool WordInString(Array* str, Array* word, Array* separators);
//Возвращает количество различных слов в строке str с разделителями, находящимися в строке separators
size_t NumberDifferentWords(Array* str, Array* separators);
//Создаёт и возвращает список созданный из строки str с разделителями, находящимися в строке separators, за исключением слов находящихся в строке ban_dictionary
Array* FillWordList(Array* str, Array* separators, Array* ban_dictionary);