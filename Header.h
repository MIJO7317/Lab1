#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdbool.h>
#include<ctype.h>

#define DEFAULT_BUFFER_SIZE 8

typedef struct Array
{
	void* data;
	size_t count;
	size_t capacity;
	size_t elem_size;
} Array; 

typedef struct Word
{
	Array* word_str;
	Array* positions;
} Word;

void ClearStdin()
{
	while (getchar()!='\n');
}

char GetCharElement(Array* str, size_t index)
{
	return index<str->count ? *((char*)str->data + index) : 0;
}

int GetIntElement(Array* arr, size_t index)
{
	return index < arr->count ? *((int*)arr->data + index) : 0;
}

Word* GetWord(Array* list, size_t index)
{
	return index < list->count ? (Word*)list->data + index : NULL;
}

void SetElement(Array* arr, size_t index, void* value)
{
	void* ptr = (char*)arr->data + index * arr->elem_size;
	memcpy(ptr,value,arr->elem_size);
}

Array* CreateDefault(size_t count, size_t elem_size, void* default_element)
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
	for (size_t i = 0; i < arr->count; i++)
		SetElement(arr, i, default_element);
	return arr;
}

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

size_t CharPointerSize(char* str)
{
	size_t size = 0;
	char* ptr = str;
	while (*ptr++)
		size++;
	return size;
}

size_t Size(Array* arr)
{
	return arr->count;
}

Array* CreateEmptyString()
{
	int default_element = '\0';
	Array* arr = CreateDefault(1, sizeof(char), &default_element);
	arr->count--;
	arr->capacity--;
	return arr;
}

Array* CreateString(char* str)
{
	size_t length = CharPointerSize(str);
	Array* arr = Create(length+1, sizeof(char));
	for (size_t i = 0; i < length + 1; i++)
		SetElement(arr, i, &str[i]);
	arr->count--;
	arr->capacity--;
	return arr;
}

//���� ������ � �������
Array* InputString()
{
	size_t buffer_size = 256;
	char* str = (char*)malloc(sizeof(char) * buffer_size + sizeof('\0'));
	if (!str)
		system("cls"), printf("Out of memmory"), exit(0);
	char simbol;
	size_t i;
	for (i = 0; (simbol = (char)getchar()) != '\n'; i++)
	{
		if (i > buffer_size-1)
		{
			buffer_size *= 2;
			char* ptr = (char*)realloc(str, sizeof(char) * buffer_size + sizeof('\0'));
			if(!ptr)
				system("cls"), printf("Out of memmory"), exit(0);
			str = ptr;
		}
		str[i] = simbol;
	}
	str[i] = '\0';
	Array* arr = CreateString(str);
	free(str);
	return arr;
}

void OutString(Array* str)
{
	for (size_t i = 0; i < str->count; i++)
		printf("%c",GetCharElement(str, i));
}

void OutIntArray(Array* arr)
{
	for (size_t i = 0; i < arr->count; i++)
		printf("%d ", GetIntElement(arr,i));
	printf("\n");
}

void Delete(Array* arr)
{
	free(arr);
}

Array* CreateInt(size_t count)
{
	int default_element = 0;
	return CreateDefault(count, sizeof(int), &default_element);
}

Array* CreateWordList(size_t count)
{
	Word* word = (Word*)malloc(sizeof(Word));
	if (!word)
		system("cls"), printf("Out of memmory"), exit(0);
	word->word_str = CreateEmptyString();
	word->positions = CreateInt(0);
	return CreateDefault(count, sizeof(Word), word);
}

size_t NumberWords(Array* str)
{
	size_t count = 0;
	char* ptr = (char*)str->data;
	while (*ptr++)
		if (*(ptr - 1) != ' ' && *ptr == ' ')
			count++;
	return *(ptr - 2) != ' ' ? ++count : count;
}

//��������� ������� � ����� ������� (�� �������� �� ��������, ��� ��� ����������� ��������� PushBackChar)
void PushBack(Array* arr, void* value)
{
	if (arr->capacity < arr->count + 1)
	{
		arr->capacity += arr->capacity ? arr->capacity : DEFAULT_BUFFER_SIZE;
		void* ptr = realloc(arr->data, arr->elem_size * arr->capacity);
		if (!ptr)
			system("cls"), printf("Out of memmory"), exit(0);
		arr->data = ptr;
	}
	SetElement(arr, arr->count, value);
	arr->count++;
}

//�������� ������� � ����� ������
void PushBackChar(Array* str, char simbol)
{
	char t_zero = '\0';
	if (str->capacity < str->count + 1)
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

//������� ���������� �����, ������������ �� ������ number_word (������� � 0), � ������ str. ������ str �� ����������.
Array* FindWord(Array* str, size_t number_word)
{
	size_t number = 0; //����� �������� ����� 
	char* ptr = (char*)str->data; //������������ ����������, �������� ����� ������������ ������
	while (number != number_word)  //����, ������� ����������� ptr �� ������ �������� ����� 
	{
		while (*ptr == ' ') //���� ���������� ptr �� ������� �������, ������� �� �������� ������������ (��������, ���� ptr="  abcd  efg  " � ����������� ��� " ", �� ����� ���������� ����� ptr="abcd  efg  ")
			ptr++;
		while (*ptr != ' ') //���� ���������� ptr �� ������� �������, ������� �������� ������������ (��������, ���� ptr="abcd  efg  " � ����������� ��� " ", �� ����� ���������� ����� ptr="  efg  ")
			ptr++;
		while (*ptr == ' ') //�� ��, ��� � ������ ����
			ptr++;
		//��� ��� ����� �������� ptr �� ������ ���������� ����� (��������, ���� ptr="  abcd  efg  " � ����������� ��� " ", �� ����� ���������� ��� ������ ptr="efg  ")
		number++; //����������� ����� �������� ����� �� �������
	}
	char* buff = ptr; //�������� ������, ������������ � �������� ����� � buff
	size_t size_word = 0; //������ �����
	while (*ptr++ != ' ') //����, � ������� ������� ������ ������ ����� 
		size_word++;
	ptr = buff; //���������� � ptr ���������� ������
	char* word = (char*)malloc(sizeof(char)*size_word+sizeof('\0')); //�������� ������ ��� ������� �����
	if (!word) //�������� �� ������, ���� word=NULL
		system("cls"), printf("Out of memmory"), exit(0);
	buff=word; //� buff ���������� �����, ��� ����� �������� �����
	while (*ptr != ' ') //����, � ������� ���������� �����
		*buff++ = *ptr++;
	*buff = '\0'; //� ����� ����� ������ '\0'
	return CreateString(word); //���������� ������� �����, ��� ������
}

//������� �������� ��������� ���� ����� ��� ����� ��������
bool EqualStrings(Array* str1, Array* str2)
{
	if (Size(str1) != Size(str2))
		return false;
	for (size_t i = 0; i < Size(str1); i++)
		if (toupper(GetCharElement(str1,i)) != toupper(GetCharElement(str2,i)))
			return false;
	return true;
}

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

size_t NumberDifferentWords(Array* str)
{
	size_t count_repeat = 0;
	size_t number_words = NumberWords(str);
	for (size_t i = 0; i < number_words; i++)
	{
		for (size_t j = i + 1; j < number_words; j++)
			if (EqualStrings(FindWord(str, i), FindWord(str, j)))
			{
				count_repeat++;
				break;
			}
	}
	return number_words - count_repeat;
}

Array* FillWordList(Array* str)
{
	Array* list = CreateWordList(NumberDifferentWords(str));
	size_t number_words = NumberWords(str);
	size_t position_in_list;
	for (size_t i = 0; i < number_words; i++)
	{
		Array* this_word = FindWord(str,i);
		if (WordInList(list, this_word, &position_in_list))
		{
			PushBack(GetWord(list, position_in_list)->positions, &i);
			Delete(this_word);
		}
		else
		{
			Word* word = (Word*)malloc(sizeof(Word));
			if (!word)
				system("cls"), printf("Out of memmory"), exit(0);
			word->word_str = this_word;
			word->positions = CreateInt(1);
			SetElement(word->positions, 0, &i);
		}
	}
	return list;
}
