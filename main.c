#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include"Header.h"

#define COUNT_ITEMS 5 //Количество пунктов меню

void Menu()
{
	system("cls");
	printf("1) Input string\n");
	printf("2) Add ban dictionary\n");
	printf("3) Show positions of words\n");
	printf("4) Test\n");
	printf("5) Exit\n");
}

int SelectedMenuItem()
{
	int number_item; //Пункт меню, который выбирает пользователь
	int result; //Результат работы функции scanf_s()
	do
	{
		Menu();
		printf("Please, input number item: ");
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
	Array* separators = CreateString(" ;,./|()!?\"\\");
	Array* ban_dictionary = CreateEmptyString();
	int item; //Выбранный пункт меню
	do
	{
		item = SelectedMenuItem();
		system("cls");
		switch (item)
		{
			case 1:
			{
				printf("Input string with words:\n");
				DeleteArray(str);
				str = InputString();
				system("pause");
				break;
			}
			case 2:
			{
				DeleteArray(ban_dictionary);
				printf("Input ban dictionary:\n");
				ban_dictionary = InputString();
				system("pause");
				break;
			}
			case 3:
			{
				Array* list = FillWordList(str, separators, ban_dictionary);
				printf("Your string: ");
				OutString(str);
				printf("\n");
				printf("Your ban dictionary: ");
				OutString(ban_dictionary);
				printf("\n");
				OutWordList(list);
				DeleteList(list);
				system("pause");
				break;
			}
			default:
				break;
		}
	} while (item != COUNT_ITEMS);
	DeleteArray(str);
	DeleteArray(separators);
}