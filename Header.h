#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>

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

char GetCharElement(Array* arr, size_t index)
{
	return (index>=0 && index<arr->count) ? *((char*)arr->data + index) : 0;
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

Array* CreateEmptyString()
{
	int default_element = '\0';
	Array* arr = CreateDefault(1, sizeof(char), &default_element);
	arr->count--;
	return arr;
}

Array* CreateString(char* str)
{
	Array* arr = Create(strlen(str)+1, sizeof(char));
	for (size_t i = 0; i < strlen(str)+1; i++)
		SetElement(arr, i, &str[i]);
	arr->count--;
	return arr;
}

//Buffer составляет 1000 символов
Array* InputString()
{
	int buffer_size = 1001;
	char* str = (char*)malloc(sizeof(char) * buffer_size);
	if (!str)
		system("cls"), printf("Out of memmory"), exit(0);
	fgets(str, buffer_size, stdin);
	str[strlen(str) - 1] = '\0';
	Array* arr = CreateString(str);
	free(str);
	return arr;
}

void OutString(Array* str)
{
	for (size_t i = 0; i < str->count; i++)
		printf("%c",GetCharElement(str,i));
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

//Array* FillWordList(Array* str)
//{
//	size_t number_words = NumberWords(str);
//	char* ptr = (char*)str->data;
//	ptr+=FindNoSpace(ptr);
//	for(size_t i=0; i<FindSpace(ptr); i++)
//		
//	return str;
//}

/*Array* StringCut(Array* str)
{
	char* ptr = (char*)str->data;
	while (*ptr++==' ');
	for(size_t i=0; GetCharElement(str,i) != ' '; i++)

}*/
