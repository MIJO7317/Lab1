#pragma once
#include"DinamicArray.h"

/*Технические функции:*/

//Очистка потока ввода Stdin от символов
void ClearStdin();

/*Функции определения размера:*/

//Количество элементов динамического массива arr
size_t Size(Array* arr);

/*Функции получения элемента:*/

//Возвращает указатель на слово, находящееся под номером index в списке слов list
Word* GetWord(Array* list, size_t index);
//Возвращает символ под номером index из строки str
char GetCharElement(Array* str, size_t index);
//Возвращает целое число под номером index в динамическом массиве arr
int GetIntElement(Array* arr, size_t index);

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
//Возвращает true, если слово word типа Array* находится в строке str с разделителями, находящимися в строке separators, в противном случае возвращает false
bool WordInString(Array* str, Array* word, Array* separators);
//Возвращает количество различных слов в строке str с разделителями, находящимися в строке separators
size_t NumberDifferentWords(Array* str, Array* separators);
//Создаёт и возвращает список созданный из строки str с разделителями, находящимися в строке separators, за исключением слов находящихся в строке ban_dictionary
Array* FillWordList(Array* str, Array* separators, Array* ban_dictionary);
