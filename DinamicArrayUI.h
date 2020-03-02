#pragma once

#define RESET   "\033[0m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[1;33m"
#define CYAN	"\033[0;36m"

/*���������:*/

//��������� ������������� �������
typedef struct Array Array;
//��������� ����� � ������������ �������� �������
typedef struct Word Word;

/*����������� �������:*/

//������� ������ ����� Stdin �� ��������
void ClearStdin();
//����� ��������� �� ������
void Error(const char* msg);
//����� �� �������� ����������
void Success(const char* msg);

/*������� ����������� �������:*/

//���������� ��������� ������������� ������� arr
size_t Size(Array* arr);

/*������� ��������� ��������:*/

//���������� ��������� �� �����, ����������� ��� ������� index � ������ ���� list, ���� index ������� �� ������� ������ list, �� ���������� NULL
Word* GetWord(Array* list, size_t index);
//���������� ������ �� ������� �����, ���� word ��� NULL, �� ������ NULL
Array* GetWordStr(Word* word);
//���������� ������ ������� �� ������� �����, ���� word ��� NULL, �� ������ NULL
Array* GetWordPositions(Word* word);
//���������� ������ ��� ������� index �� ������ str, ���� index ������� �� ������� ������ str, �� ���������� '\0'
char GetCharElement(Array* str, size_t index);
//���������� ��������� �� ����� ����� ��� ������� index � ������������ ������� arr, ���� index ������� �� ������� ������� arr, �� ���������� NULL
int* GetIntElement(Array* arr, size_t index);

/*�����������:*/

//������������ ������ ��������� ptr
void Delete(void* ptr);
//������������ ������ ������������� ������� arr
void DeleteArray(Array* arr);
//������������ ������ ����� word
void DeleteWord(Word* word);
//������������ ������ ������ ���� list
void DeleteList(Array* list);

/*������� ���������/���������� ��������:*/

//�������� �������� value � ������� ������������� ������� arr ��� ������� index
void SetElement(Array* arr, size_t index, void* value);
//�������� ������� � ����� ������
void PushBackChar(Array* str, char simbol);
//��������� ������� � ����� ������� (�� �������� �� ��������, ��� ��� ����������� ��������� PushBackChar)
void PushBack(Array* arr, void* value);

/*������������:*/

//�������� ������ ������
Array* CreateEmptyString();
//�������� ������ ���� Array* �� ������ str ���� char*
Array* CreateString(char* str);
//�������� ������������� ������� ����� ����� ������� count (��� �������� �� ��������� 0)
Array* CreateInt(size_t count);
//�������� ������ ���� ������� count (��� �������� �� ��������� ��� ������ �����)
Array* CreateWordList(size_t count);
//�������� ������ �� �������
Array* InputString();

/*������� ������:*/

//����� ������
void OutString(Array* str);
//����� �������������� ������������� �������
void OutIntArray(Array* arr);
//����� ������ ���� � �� ���������
void OutWordList(Array* list);

/*��������� � ������� �������*/

//���������� true, ���� � ������ str ������ ������ simbol, � ��������� ������ ���������� false
bool CharInString(Array* str, char simbol);
//���������� ���������� ���� ���� � ������ str � �������������, ������������ � ������ separators
size_t NumberWords(Array* str, Array* separators);
//������ � ���������� ������ � ������� �������� �����, ����������� �� ������ number_word (������� � 0), � ������ str
Array* FindWord(Array* str, size_t number_word, Array* separators);
//���������� true, ���� ������ str1 � str2 �����, ��� ����� ��������, � ��������� ������ ���������� false
bool EqualStrings(Array* str1, Array* str2);
//���������� true, ���� ����� word ���� Array* ��������� � ������ list � ��������� ����� ������� � position_in_list, � ��������� ������ ���������� false � position_in_list �� ��������
bool WordInList(Array* list, Array* word, size_t* position_in_list);
//���������� true, ���� ����� word ���� Array* ��������� � ������ str � �������������, ������������ � ������ separators, � ��������� ������ ���������� false
bool WordInString(Array* str, Array* word, Array* separators);
//���������� ���������� ��������� ���� � ������ str � �������������, ������������ � ������ separators
size_t NumberDifferentWords(Array* str, Array* separators);
//������ � ���������� ������ ��������� �� ������ str � �������������, ������������ � ������ separators, �� ����������� ���� ����������� � ������ ban_dictionary
Array* FillWordList(Array* str, Array* separators, Array* ban_dictionary);