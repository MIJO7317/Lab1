#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdbool.h>
#include<ctype.h>
//#include<vld.h>

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

void Delete(void* ptr)
{
	free(ptr);
}

void DeleteArray(Array* arr)
{
	Delete(arr->data);
	Delete(arr);
}

Word* GetWord(Array* list, size_t index)
{
	return index < list->count ? (Word*)list->data + index : NULL;
}

void DeleteList(Array* list)
{
	for (size_t i = 0; i < list->count; i++)
	{
		DeleteArray(GetWord(list, i)->word_str);
		DeleteArray(GetWord(list, i)->positions);
	}
	DeleteArray(list);
}

char GetCharElement(Array* str, size_t index)
{
	return index<str->count ? *((char*)str->data + index) : 0;
}

int GetIntElement(Array* arr, size_t index)
{
	return index < arr->count ? *((int*)arr->data + index) : 0;
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

//Ввод строки с консоли
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

void OutWordList(Array* list)
{
	for (size_t i = 0; i < list->count; i++)
	{
		printf("Word %d: ", i);
		OutString(GetWord(list,i)->word_str);
		printf("\t\t\t\t\tPositions: ");
		OutIntArray(GetWord(list,i)->positions);
	}
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
	Array* list = CreateDefault(count, sizeof(Word), word);
	DeleteArray(word->word_str);
	DeleteArray(word->positions);
	Delete(word);
	return list;
}

bool CharInString(Array* str, char simbol)
{
	for (size_t i = 0; i < Size(str); i++)
		if (GetCharElement(str, i) == simbol)
			return true;
	return false;
}

size_t NumberWords(Array* str, Array* separators)
{
	size_t count = 0;
	char* ptr = (char*)str->data;
	while (*ptr++)
		if (!CharInString(separators, *(ptr - 1)) && CharInString(separators, *ptr))
			count++;
	return !CharInString(separators, *(ptr - 2)) ? ++count : count;
}

//Добавляет элемент в конец массива (не работает со строками, для них используйте процедуру PushBackChar)
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

//Добаляет элемент в конец строки
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

//Функция нахождения слова, находящегося по номеру number_word (начиная с 0), в строке str. Строка str не изменяется.
Array* FindWord(Array* str, size_t number_word, Array* separators)
{
	size_t number = 0; //Номер текущего слова 
	char* ptr = (char*)str->data; //Изменяющаяся переменная, хранящяя копию передаваемой строки
	while (number != number_word)  //Цикл, который передвигает ptr до начала текущего слова 
	{
		while (CharInString(separators, *ptr)) //Цикл сдвигающий ptr до первого символа, который не является разделителем (Например, если ptr="  abcd  efg  " и разделитель это " ", то после выполнения цикла ptr="abcd  efg  ")
			ptr++;
		while (!CharInString(separators, *ptr)) //Цикл сдвигающий ptr до первого символа, который является разделителем (Например, если ptr="abcd  efg  " и разделитель это " ", то после выполнения цикла ptr="  efg  ")
			ptr++;
		while (CharInString(separators, *ptr)) //То же, что и первый цикл
			ptr++;
		//Все три цикла сдвигают ptr до начала следующего слова (Например, если ptr="  abcd  efg  " и разделитель это " ", то после выполнения трёх циклов ptr="efg  ")
		number++; //Увеличиваем номер текущего слова на единицу
	}
	char* buff = ptr; //Сохраняе строку, начинающююся с искомого слова в buff
	size_t size_word = 0; //Размер слова
	while (!CharInString(separators, *ptr++)) //Цикл, в котором находим размер нашего слова 
		size_word++;
	ptr = buff; //Возвращаем в ptr сохранённую строку
	char* word = (char*)malloc(sizeof(char)*size_word+sizeof('\0')); //Выделяем память под искомое слово
	if (!word) //Сообщаем об ошибке, если word=NULL
		system("cls"), printf("Out of memmory"), exit(0);
	buff=word; //В buff записываем адрес, где будет хранится слово
	while (!CharInString(separators, *ptr)) //Цикл, в котором записываем слово
		*buff++ = *ptr++;
	*buff = '\0'; //В конце слова ставим '\0'
	Array* word_str = CreateString(word); //Возвращаем искомое слово, как строку
	Delete(word);
	return word_str;
}

//Функция проверки равенства двух строк без учета регистра
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

Array* FillWordList(Array* str, Array* separators)
{
	Array* list = CreateWordList(NumberDifferentWords(str, separators));
	list->count = 0;
	size_t number_words = NumberWords(str, separators);
	size_t position_in_list;
	for (size_t i = 0; i < number_words; i++)
	{
		Array* this_word = FindWord(str, i, separators);
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
			SetElement(list, list->count, word);
			list->count++;
		}
	}
	return list;
}
