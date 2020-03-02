#include"Headers.h"

#define DEFAULT_BUFFER_SIZE 8

/*Структуры:*/

//Структура динамического массива
typedef struct Array
{
	void* data;
	size_t count;
	size_t capacity;
	size_t elem_size;
} Array;
//Структура слова с динамическим массивом позиций
typedef struct Word
{
	Array* word_str;
	Array* positions;
} Word;

/*Технические функции:*/

//Очистка потока ввода Stdin от символов
void ClearStdin()
{
	while (getchar() != '\n');
}
//Вывод сообщения об ошибке
void Error(const char* msg)
{
	printf(RED);
	printf(msg);
	printf(RESET);
	printf("\n");
	system("pause");
	exit(0);
}
//Вывод об успешном выполнении
void Success(const char* msg)
{
	printf(msg);
	printf(" - %sSuccess%s\n", GREEN, RESET);
}


/*Функции определения размера:*/

//Количество элементов динамического массива arr
size_t Size(Array* arr)
{
	return arr->count;
}
//Количество символов в строке str типа char*
size_t CharPointerSize(char* str)
{
	size_t size = 0;
	char* ptr = str;
	while (*ptr++)
		size++;
	return size;
}

/*Функции получения элемента:*/

//Возвращает указатель на слово, находящееся под номером index в списке слов list, если index выходит за пределы списка list, то возвращает NULL
Word* GetWord(Array* list, size_t index)
{
	return index < Size(list) ? (Word*)list->data + index : NULL;
}
//Возвращает строку из данного слова, если word это NULL, то вернет NULL
Array* GetWordStr(Word* word) 
{
	return word ? word->word_str : NULL;
}
//Возвращает массив позиций из данного слова, если word это NULL, то вернет NULL
Array* GetWordPositions(Word* word)
{
	return word ? word->positions : NULL;
}
//Возвращает символ под номером index из строки str, если index выходит за пределы строки str, то возвращает '\0'
char GetCharElement(Array* str, size_t index)
{
	return index < Size(str) ? *((char*)str->data + index) : 0;
}
//Возвращает указатель на целое число под номером index в динамическом массиве arr, если index выходит за пределы массива arr, то возвращает NULL
int* GetIntElement(Array* arr, size_t index)
{
	return index < Size(arr) ? (int*)arr->data + index : NULL;
}

/*Деструкторы:*/

//Освобождение памяти указателя ptr
void Delete(void* ptr)
{
	if (!ptr)
		system("cls"), Error("Attempt to free null pointer");
	free(ptr);
	ptr = NULL;
}
//Освобождение памяти динамического массива arr
void DeleteArray(Array* arr)
{
	if (!arr)
		system("cls"), Error("Attempt to free null pointer");
	Delete(arr->data);
	Delete(arr);
	arr = NULL;
}
//Освобождение памяти слова word
void DeleteWord(Word* word)
{
	if (!word)
		system("cls"), Error("Attempt to free null pointer");
	DeleteArray(word->word_str);
	DeleteArray(word->positions);
	Delete(word);
	word = NULL;
}
//Освобождение памяти списка слов list
void DeleteList(Array* list)
{
	if (!list)
		system("cls"), Error("Attempt to free null pointer");
	for (size_t i = 0; i < Size(list); i++)
	{
		DeleteArray(GetWord(list, i)->word_str);
		DeleteArray(GetWord(list, i)->positions);
	}
	Delete(list->data);
	Delete(list);
	list = NULL;
}

/*Функции изменения/добавления элемента:*/

//Копирует значение value в элемент динамического массива arr под номером index
void SetElement(Array* arr, size_t index, void* value)
{
	if (index >= arr->capacity)
		system("cls"), Error("Buffer Overflow");
	void* ptr = (char*)arr->data + index * arr->elem_size;
	memmove(ptr, value, arr->elem_size);
}
//Добаляет элемент в конец строки
void PushBackChar(Array* str, char simbol)
{
	char t_zero = '\0';
	if (str->capacity <= str->count+1)
	{
		str->capacity += str->capacity ? str->capacity : DEFAULT_BUFFER_SIZE;
		void* ptr = realloc(str->data, sizeof(char) * str->capacity + sizeof('\0'));
		if (!ptr)
			system("cls"), Error("Out of memmory");
		str->data = (char*)ptr;
	}
	SetElement(str, str->count, &simbol);
	SetElement(str, str->count + 1, &t_zero);
	str->count++;
}
//Добавляет элемент в конец массива (не работает со строками, для них используйте процедуру PushBackChar)
void PushBack(Array* arr, void* value)
{
	if (arr->capacity <= arr->count)
	{
		arr->capacity += arr->capacity ? arr->capacity : DEFAULT_BUFFER_SIZE;
		void* ptr = realloc(arr->data, arr->elem_size * arr->capacity);
		if (!ptr)
			system("cls"), Error("Out of memmory");
		arr->data = (Array*)ptr;
	}
	SetElement(arr, arr->count, value);
	arr->count++;
}

/*Конструкторы:*/

//Создание динамического массива размера count и с элементами размера elem_size
Array* Create(size_t count, size_t elem_size)
{
	Array* arr = (Array*)malloc(sizeof(Array));
	if (!arr)
		system("cls"), Error("Out of memmory");
	arr->capacity = count;
	arr->count = count;
	arr->elem_size = elem_size;
	arr->data = malloc(arr->capacity * elem_size);
	if (!arr->data)
		system("cls"), Error("Out of memmory");
	return arr;
}
//Создание динамического массива размера count и с элементами размера elem_size и заполнение его начальными значениями default_element 
Array* CreateDefault(size_t count, size_t elem_size, void* default_element)
{
	Array* arr = Create(count, elem_size);
	for (size_t i = 0; i < Size(arr); i++)
		SetElement(arr, i, default_element);
	return arr;
}
//Создание пустой строки
Array* CreateEmptyString()
{
	char default_element = '\0';
	Array* arr = CreateDefault(1, sizeof(char), &default_element);
	arr->count--;
	arr->capacity--;
	return arr;
}
//Создание строки типа Array* из строки str типа char*
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
//Создание динамического массива целых чисел размера count (все элементы по умолчанию 0)
Array* CreateInt(size_t count)
{
	int default_element = 0;
	return CreateDefault(count, sizeof(int), &default_element);
}
//Создание списка слов размера count (все элементы по умолчанию это пустые слова)
Array* CreateWordList(size_t count)
{
	Array* list = Create(count, sizeof(Word));
	for (size_t i = 0; i < Size(list); i++)
	{
		Word* word = (Word*)malloc(sizeof(Word));
		if (!word)
			system("cls"), Error("Out of memmory");
		word->word_str = CreateEmptyString();
		word->positions = CreateInt(0);
		SetElement(list, i, word);
		Delete(word);
	}
	return list;
}
//Создание строки из консоли
Array* InputString()
{
	Array* str = CreateEmptyString();
	if (!str)
		system("cls"), Error("Out of memmory");
	char simbol;
	for (size_t i = 0; (simbol = (char)getchar()) != '\n'; i++)
		PushBackChar(str, simbol);
	return str;
}

/*Функции вывода:*/

//Вывод строки
void OutString(Array* str)
{
	for (size_t i = 0; i < Size(str); i++)
		printf("%c", tolower(GetCharElement(str, i)));
}
//Вывод целочисленного динамического массива
void OutIntArray(Array* arr)
{
	for (size_t i = 0; i < Size(arr); i++)
		printf("%d ", *GetIntElement(arr, i));
	printf("\n");
}
//Вывод списка слов с их позициями
void OutWordList(Array* list)
{
	for (size_t i = 0; i < list->count; i++)
	{
		printf("%sWord %s", YELLOW, RESET);
		printf("%s%d%s", CYAN, i, RESET);
		printf("%s: %s", YELLOW, RESET);
		OutString(GetWord(list, i)->word_str);
		printf("\t\t\t%sPositions: %s", YELLOW, RESET);
		OutIntArray(GetWord(list, i)->positions);
	}
}

/*Предикаты и сложные функции*/

//Возвращает true, если в строке str найден символ simbol, в противном случае возвращает false
bool CharInString(Array* str, char simbol)
{
	for (size_t i = 0; i < Size(str); i++)
		if (GetCharElement(str, i) == simbol)
			return true;
	return false;
}
//Возвращает количество всех слов в строке str с разделителями, находящимися в строке separators
size_t NumberWords(Array* str, Array* separators)
{
	size_t count = 0;
	char* ptr = (char*)str->data;
	while (*ptr++)
		if (!CharInString(separators, *(ptr - 1)) && CharInString(separators, *ptr))
			count++;
	return !CharInString(separators, *(ptr - 2)) ? ++count : count;
}
//Создаёт и возвращает строку в которой записано слово, находящееся по номеру number_word (начиная с 0), в строке str
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
	char* word = (char*)malloc(sizeof(char) * size_word + sizeof('\0')); //Выделяем память под искомое слово
	if (!word) //Сообщаем об ошибке, если word=NULL
		system("cls"), Error("Out of memmory");
	buff = word; //В buff записываем адрес, где будет хранится слово
	while (!CharInString(separators, *ptr)) //Цикл, в котором записываем слово
		*buff++ = *ptr++;
	*buff = '\0'; //В конце слова ставим '\0'
	Array* word_str = CreateString(word); //Возвращаем искомое слово, как строку
	Delete(word);
	return word_str;
}
//Возвращает true, если строки str1 и str2 равны, без учета регистра, в противном случае возвращает false
bool EqualStrings(Array* str1, Array* str2)
{
	if (Size(str1) != Size(str2))
		return false;
	for (size_t i = 0; i < Size(str1); i++)
		if (tolower(GetCharElement(str1, i)) != tolower(GetCharElement(str2, i)))
			return false;
	return true;
}
//Возвращает true, если слово word типа Array* находится в списке list и записывет номер позиции в position_in_list, в противном случае возвращает false и position_in_list не меняется
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
//Возвращает true, если слово word типа Array* находится в строке str с разделителями, находящимися в строке separators, в противном случае возвращает false
bool WordInString(Array* str, Array* word, Array* separators)
{
	for (size_t i = 0; i < NumberWords(str, separators); i++)
	{
		Array* word_in_str = FindWord(str, i, separators);
		if (!word_in_str)
			system("cls"), Error("Out of memmory");
		if (EqualStrings(word_in_str, word))
		{
			DeleteArray(word_in_str);
			return true;
		}
		DeleteArray(word_in_str);
	}
	return false;
}
//Возвращает количество различных слов в строке str с разделителями, находящимися в строке separators
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
				DeleteArray(word1);
				DeleteArray(word2);
				break;
			}
			DeleteArray(word1);
			DeleteArray(word2);
		}
	}
	return number_words - count_repeat;
}
//Создаёт и возвращает список созданный из строки str с разделителями, находящимися в строке separators, за исключением слов находящихся в строке ban_dictionary
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
				system("cls"), Error("Out of memmory");
			word->word_str = this_word;
			word->positions = CreateInt(1);
			SetElement(word->positions, 0, &i);
			PushBack(list, word);
			Delete(word);
		}
	}
	return list;
}
