#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdbool.h>

typedef struct Array
{
	void* data;
	size_t count;
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
	arr->count = count;
	arr->elem_size = elem_size;
	arr->data = malloc(count * elem_size);
	for (size_t i = 0; i < arr->count; i++)
		SetElement(arr, i, default_element);
	return arr;
}

Array* Create(size_t count, size_t elem_size)
{
	Array* arr = (Array*)malloc(sizeof(Array));
	if (!arr)
		system("cls"), printf("Out of memmory"), exit(0);
	arr->count = count;
	arr->elem_size = elem_size;
	arr->data = malloc(count * elem_size);
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
	return arr;
}

Array* CreateString(char* str)
{
	size_t length = CharPointerSize(str);
	Array* arr = Create(length+1, sizeof(char));
	for (size_t i = 0; i < length + 1; i++)
		SetElement(arr, i, &str[i]);
	arr->count--;
	return arr;
}

//Buffer ���������� 1000 ��������
Array* InputString()
{
	int buffer_size = 1001;
	char* str = (char*)malloc(sizeof(char) * buffer_size);
	if (!str)
		system("cls"), printf("Out of memmory"), exit(0);
	fgets(str, buffer_size, stdin);
	str[CharPointerSize(str) - 1] = '\0';
	Array* arr = CreateString(str);
	free(str);
	return arr;
}

void OutString(Array* str)
{
	for (size_t i = 0; i < str->count; i++)
		printf("%c",GetCharElement(str, i));
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

//������� ���������� �����, ������������ �� ������ number_word, � ������ str. ������ str �� ����������.
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

size_t FindSpace(char* str)
{
	size_t position = 0;
	char* ptr = str;
	while (*ptr++ != ' ')
		position++;
	return position;
}

size_t FindNoSpace(char* str)
{
	size_t position=0;
	char* ptr = str;
	while (*ptr++ == ' ')
		position++;
	return position;
}

bool EqualStrings(Array* str1, Array* str2)
{
	if (Size(str1) != Size(str2))
		return false;
	for (size_t i = 0; i < Size(str1); i++)
		if (GetCharElement(str1,i) != GetCharElement(str2,i))
			return false;
	return true;
}

bool WordInList(Array* list, Array* word)
{
	for (size_t i = 0; i < Size(list); i++)
		if (EqualStrings(GetWord(list, i)->word_str, word))
			return true;
	return false;
}

Array* FillWordList(Array* str)
{
	size_t number_words = NumberWords(str);
	char* ptr = (char*)str->data;
	ptr+=FindNoSpace(ptr);
	for(size_t i=0; i<FindSpace(ptr); i++)
		
	return str;
}

/*Array* StringCut(Array* str)
{
	char* ptr = (char*)str->data;
	while (*ptr++==' ');
	for(size_t i=0; GetCharElement(str,i) != ' '; i++)

}*/
