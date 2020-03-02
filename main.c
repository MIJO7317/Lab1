#include"Headers.h"
#include"TestsDinamicArray.h"


#define _CRTDBG_MAP_ALLOC
//Подключение библиотеки на проверку утечки памяти:
#include <crtdbg.h>

#define COUNT_ITEMS 5 //Количество пунктов меню

typedef enum MenuItems
{
	Input_String = 1,
	Add_BanDictionary,
	Show_PositionsOfWords,
	Test,
	Exit
} MenuItems;

void Menu()
{
	system("cls");
	printf("%s1)%s Input string\n", YELLOW, RESET);
	printf("%s2)%s Add ban dictionary\n", YELLOW, RESET);
	printf("%s3)%s Show positions of words\n", YELLOW, RESET);
	printf("%s4)%s Test\n", YELLOW, RESET);
	printf("%s5)%s Exit\n", YELLOW, RESET);
}

int SelectedMenuItem()
{
	int number_item; //Пункт меню, который выбирает пользователь
	int result; //Результат работы функции scanf_s()
	do
	{
		Menu();
		printf("%sPlease, input number item: %s", CYAN, RESET);
		result = scanf_s("%d", &number_item);
		!result ? scanf_s("%*s") : 0;
	} while (!result || number_item>COUNT_ITEMS || number_item<=0);
	ClearStdin();
	return number_item;
}

int main()
{
	setlocale(LC_ALL,"Russian_Russia.866");
	Array* str = CreateEmptyString();
	Array* separators = CreateString("<>;, ./|()!?\"\\");
	Array* ban_dictionary = CreateEmptyString();
	int item; //Выбранный пункт меню
	do
	{
		item = SelectedMenuItem();
		system("cls");
		switch (item)
		{
			case Input_String:
			{
				printf("%sSeparators: %s", YELLOW, RESET);
				OutString(separators);
				printf("\n");
				printf("%sInput string with words:%s\n", CYAN, RESET);
				DeleteArray(str);
				str = InputString();
				system("pause");
				break;
			}
			case Add_BanDictionary:
			{
				printf("%sSeparators: %s", YELLOW, RESET);
				OutString(separators);
				printf("\n");
				DeleteArray(ban_dictionary);
				printf("%sInput ban dictionary:%s\n", CYAN, RESET);
				ban_dictionary = InputString();
				system("pause");
				break;
			}
			case Show_PositionsOfWords:
			{
				Array* list = FillWordList(str, separators, ban_dictionary);
				printf("%sYour string: %s", YELLOW, RESET);
				OutString(str);
				printf("\n");
				printf("%sYour ban dictionary: %s", YELLOW, RESET);
				OutString(ban_dictionary);
				printf("\n");
				OutWordList(list);
				DeleteList(list);
				system("pause");
				break;
			}
			case Test:
			{
				_CrtMemState ms;
				_CrtMemCheckpoint(&ms);
				TestIntArray();
				printf("\n");
				TestString();
				printf("\n");
				TestList();
				printf("\n");
				_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
				_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
				printf(YELLOW);
				_CrtMemDumpAllObjectsSince(&ms);
				printf(RESET);
				system("pause");
				break;
			}
			default:
				break;
		}
	} while (item != COUNT_ITEMS);
	DeleteArray(str);
	DeleteArray(separators);
	DeleteArray(ban_dictionary);
}