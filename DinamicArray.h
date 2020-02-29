#pragma once
#include"Headers.h"

#define DEFAULT_BUFFER_SIZE 8

/*���������:*/

//��������� ������������� �������
typedef struct Array
{
	void* data;
	size_t count;
	size_t capacity;
	size_t elem_size;
} Array;
//��������� ����� � ������������ �������� �������
typedef struct Word
{
	Array* word_str;
	Array* positions;
} Word;

/*����������� �������:*/

//������� ������ ����� Stdin �� ��������
void ClearStdin()
{
	while (getchar() != '\n');
}

/*������� ����������� �������:*/

//���������� ��������� ������������� ������� arr
size_t Size(Array* arr)
{
	return arr->count;
}
//���������� �������� � ������ str ���� char*
size_t CharPointerSize(char* str)
{
	size_t size = 0;
	char* ptr = str;
	while (*ptr++)
		size++;
	return size;
}

/*������� ��������� ��������:*/

//���������� ��������� �� �����, ����������� ��� ������� index � ������ ���� list
Word* GetWord(Array* list, size_t index)
{
	return index < Size(list) ? (Word*)list->data + index : NULL;
}
//���������� ������ ��� ������� index �� ������ str
char GetCharElement(Array* str, size_t index)
{
	return index < Size(str) ? *((char*)str->data + index) : 0;
}
//���������� ����� ����� ��� ������� index � ������������ ������� arr
int GetIntElement(Array* arr, size_t index)
{
	return index < Size(arr) ? *((int*)arr->data + index) : 0;
}

/*�����������:*/

//������������ ������ ��������� ptr
void Delete(void* ptr)
{
	if (!ptr) return;
	free(ptr);
}
//������������ ������ ������������� ������� arr
void DeleteArray(Array* arr)
{
	if (!arr) return;
	Delete(arr->data);
	Delete(arr);
}
//������������ ������ ����� word
void DeleteWord(Word* word)
{
	if (!word) return;
	DeleteArray(word->word_str);
	DeleteArray(word->positions);
	Delete(word);
}
//������������ ������ ������ ���� list
void DeleteList(Array* list)
{
	if (!list) return;
	for (size_t i = 0; i < Size(list); i++)
	{
		DeleteArray(GetWord(list, i)->word_str);
		DeleteArray(GetWord(list, i)->positions);
	}
	Delete(list->data);
	Delete(list);
}

/*������� ���������/���������� ��������:*/

//�������� �������� value � ������� ������������� ������� arr ��� ������� index
void SetElement(Array* arr, size_t index, void* value)
{
	void* ptr = (char*)arr->data + index * arr->elem_size;
	memmove(ptr, value, arr->elem_size);
}
//�������� ������� � ����� ������
void PushBackChar(Array* str, char simbol)
{
	char t_zero = '\0';
	if (str->capacity <= str->count)
	{
		str->capacity += str->capacity ? str->capacity : DEFAULT_BUFFER_SIZE;
		void* ptr = realloc(str->data, sizeof(char) * str->capacity + sizeof('\0'));
		if (!ptr)
			system("cls"), printf("Out of memmory"), exit(0);
		str->data = (char*)ptr;
	}
	SetElement(str, str->count, &simbol);
	SetElement(str, str->count + 1, &t_zero);
	str->count++;
}
//��������� ������� � ����� ������� (�� �������� �� ��������, ��� ��� ����������� ��������� PushBackChar)
void PushBack(Array* arr, void* value)
{
	if (arr->capacity <= arr->count)
	{
		arr->capacity += arr->capacity ? arr->capacity : DEFAULT_BUFFER_SIZE;
		void* ptr = realloc(arr->data, arr->elem_size * arr->capacity);
		if (!ptr)
			system("cls"), printf("Out of memmory"), exit(0);
		arr->data = (Array*)ptr;
	}
	SetElement(arr, arr->count, value);
	arr->count++;
}

/*������������:*/

//�������� ������������� ������� ������� count � � ���������� ������� elem_size
Array* Create(size_t count, size_t elem_size)
{
	Array* arr = (Array*)malloc(sizeof(Array));
	if (!arr)
		system("cls"), printf("Out of memmory"), exit(0);
	arr->capacity = count;
	arr->count = count;
	arr->elem_size = elem_size;
	arr->data = malloc(arr->capacity * elem_size);
	if (!arr->data)
		system("cls"), printf("Out of memmory"), exit(0);
	return arr;
}
//�������� ������������� ������� ������� count � � ���������� ������� elem_size � ���������� ��� ���������� ���������� default_element 
Array* CreateDefault(size_t count, size_t elem_size, void* default_element)
{
	Array* arr = Create(count, elem_size);
	for (size_t i = 0; i < Size(arr); i++)
		SetElement(arr, i, default_element);
	return arr;
}
//�������� ������ ������
Array* CreateEmptyString()
{
	char default_element = '\0';
	Array* arr = CreateDefault(1, sizeof(char), &default_element);
	arr->count--;
	arr->capacity--;
	return arr;
}
//�������� ������ ���� Array* �� ������ str ���� char*
Array* CreateString(char* str)
{
	size_t length = CharPointerSize(str);
	Array* arr = Create(length + 1, sizeof(char));
	for (size_t i = 0; i < length + 1; i++)
		SetElement(arr, i, &str[i]);
	arr->count--;
	arr->capacity--;
	return arr;
}
//�������� ������������� ������� ����� ����� ������� count (��� �������� �� ��������� 0)
Array* CreateInt(size_t count)
{
	int default_element = 0;
	return CreateDefault(count, sizeof(int), &default_element);
}
//�������� ������ ���� ������� count (��� �������� �� ��������� ��� ������ �����)
Array* CreateWordList(size_t count)
{
	Word* word = (Word*)malloc(sizeof(Word));
	if (!word)
		system("cls"), printf("Out of memmory"), exit(0);
	word->word_str = CreateEmptyString();
	word->positions = CreateInt(0);
	Array* list = CreateDefault(count, sizeof(Word), word);
	Delete(word);
	return list;
}
//�������� ������ �� �������
Array* InputString()
{
	Array* str = CreateEmptyString();
	if (!str)
		system("cls"), printf("Out of memmory"), exit(0);
	char simbol;
	for (size_t i = 0; (simbol = (char)getchar()) != '\n'; i++)
		PushBackChar(str, simbol);
	return str;
}

/*������� ������:*/

//����� ������
void OutString(Array* str)
{
	for (size_t i = 0; i < Size(str); i++)
		printf("%c", tolower(GetCharElement(str, i)));
}
//����� �������������� ������������� �������
void OutIntArray(Array* arr)
{
	for (size_t i = 0; i < Size(arr); i++)
		printf("%d ", GetIntElement(arr, i));
	printf("\n");
}
//����� ������ ���� � �� ���������
void OutWordList(Array* list)
{
	for (size_t i = 0; i < list->count; i++)
	{
		printf("Word %d: ", i);
		OutString(GetWord(list, i)->word_str);
		printf("\t\t\tPositions: ");
		OutIntArray(GetWord(list, i)->positions);
	}
}

/*��������� � ������� �������*/

//���������� true, ���� � ������ str ������ ������ simbol, � ��������� ������ ���������� false
bool CharInString(Array* str, char simbol)
{
	for (size_t i = 0; i < Size(str); i++)
		if (GetCharElement(str, i) == simbol)
			return true;
	return false;
}
//���������� ���������� ���� ���� � ������ str � �������������, ������������ � ������ separators
size_t NumberWords(Array* str, Array* separators)
{
	size_t count = 0;
	char* ptr = (char*)str->data;
	while (*ptr++)
		if (!CharInString(separators, *(ptr - 1)) && CharInString(separators, *ptr))
			count++;
	return !CharInString(separators, *(ptr - 2)) ? ++count : count;
}
//������ � ���������� ������ � ������� �������� �����, ����������� �� ������ number_word (������� � 0), � ������ str
Array* FindWord(Array* str, size_t number_word, Array* separators)
{
	size_t number = 0; //����� �������� ����� 
	char* ptr = (char*)str->data; //������������ ����������, �������� ����� ������������ ������
	while (number != number_word)  //����, ������� ����������� ptr �� ������ �������� ����� 
	{
		while (CharInString(separators, *ptr)) //���� ���������� ptr �� ������� �������, ������� �� �������� ������������ (��������, ���� ptr="  abcd  efg  " � ����������� ��� " ", �� ����� ���������� ����� ptr="abcd  efg  ")
			ptr++;
		while (!CharInString(separators, *ptr)) //���� ���������� ptr �� ������� �������, ������� �������� ������������ (��������, ���� ptr="abcd  efg  " � ����������� ��� " ", �� ����� ���������� ����� ptr="  efg  ")
			ptr++;
		while (CharInString(separators, *ptr)) //�� ��, ��� � ������ ����
			ptr++;
		//��� ��� ����� �������� ptr �� ������ ���������� ����� (��������, ���� ptr="  abcd  efg  " � ����������� ��� " ", �� ����� ���������� ��� ������ ptr="efg  ")
		number++; //����������� ����� �������� ����� �� �������
	}
	char* buff = ptr; //�������� ������, ������������ � �������� ����� � buff
	size_t size_word = 0; //������ �����
	while (!CharInString(separators, *ptr++)) //����, � ������� ������� ������ ������ ����� 
		size_word++;
	ptr = buff; //���������� � ptr ���������� ������
	char* word = (char*)malloc(sizeof(char) * size_word + sizeof('\0')); //�������� ������ ��� ������� �����
	if (!word) //�������� �� ������, ���� word=NULL
		system("cls"), printf("Out of memmory"), exit(0);
	buff = word; //� buff ���������� �����, ��� ����� �������� �����
	while (!CharInString(separators, *ptr)) //����, � ������� ���������� �����
		*buff++ = *ptr++;
	*buff = '\0'; //� ����� ����� ������ '\0'
	Array* word_str = CreateString(word); //���������� ������� �����, ��� ������
	Delete(word);
	return word_str;
}
//���������� true, ���� ������ str1 � str2 �����, ��� ����� ��������, � ��������� ������ ���������� false
bool EqualStrings(Array* str1, Array* str2)
{
	if (Size(str1) != Size(str2))
		return false;
	for (size_t i = 0; i < Size(str1); i++)
		if (tolower(GetCharElement(str1, i)) != tolower(GetCharElement(str2, i)))
			return false;
	return true;
}
//���������� true, ���� ����� word ���� Array* ��������� � ������ list � ��������� ����� ������� � position_in_list, � ��������� ������ ���������� false � position_in_list �� ��������
bool WordInList(Array* list, Array* word, size_t* position_in_list)
{
	for (size_t i = 0; i < Size(list); i++)
		if (EqualStrings(GetWord(list, i)->word_str, word))
		{
			*position_in_list = i;
			return true;
		}
	return false;
}
//���������� true, ���� ����� word ���� Array* ��������� � ������ str � �������������, ������������ � ������ separators, � ��������� ������ ���������� false
bool WordInString(Array* str, Array* word, Array* separators)
{
	for (size_t i = 0; i < NumberWords(str, separators); i++)
	{
		Array* word_in_str = FindWord(str, i, separators);
		if (!word_in_str)
			system("cls"), printf("Out of memmory"), exit(0);
		if (EqualStrings(word_in_str, word))
		{
			DeleteArray(word_in_str);
			return true;
		}
		DeleteArray(word_in_str);
	}
	return false;
}
//���������� ���������� ��������� ���� � ������ str � �������������, ������������ � ������ separators
size_t NumberDifferentWords(Array* str, Array* separators)
{
	size_t count_repeat = 0;
	size_t number_words = NumberWords(str, separators);
	for (size_t i = 0; i < number_words; i++)
	{
		for (size_t j = i + 1; j < number_words; j++)
		{
			Array* word1 = FindWord(str, i, separators);
			Array* word2 = FindWord(str, j, separators);
			if (EqualStrings(word1, word2))
			{
				count_repeat++;
				break;
			}
			DeleteArray(word1);
			DeleteArray(word2);
		}
	}
	return number_words - count_repeat;
}
//������ � ���������� ������ ��������� �� ������ str � �������������, ������������ � ������ separators, �� ����������� ���� ����������� � ������ ban_dictionary
Array* FillWordList(Array* str, Array* separators, Array* ban_dictionary)
{
	Array* list = CreateWordList(0);
	size_t number_words = NumberWords(str, separators);
	size_t position_in_list;
	for (size_t i = 0; i < number_words; i++)
	{
		Array* this_word = FindWord(str, i, separators);
		if (WordInString(ban_dictionary, this_word, separators))
		{
			DeleteArray(this_word);
			continue;
		}
		if (WordInList(list, this_word, &position_in_list))
		{
			PushBack(GetWord(list, position_in_list)->positions, &i);
			DeleteArray(this_word);
		}
		else
		{
			Word* word = (Word*)malloc(sizeof(Word));
			if (!word)
				system("cls"), printf("Out of memmory"), exit(0);
			word->word_str = this_word;
			word->positions = CreateInt(1);
			SetElement(word->positions, 0, &i);
			PushBack(list, word);
			Delete(word);
		}
	}
	return list;
}

