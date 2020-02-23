#include<stdio.h>
#include<stdlib.h>
#include"Header.h"

#define COUNT_ITEMS 4 //Количество пунктов меню

void Menu()
{
	system("cls");
	printf("1) Input string\n");
	printf("2) Show positions of words\n");
	printf("3) Test\n");
	printf("4) Exit\n");
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
	Array* str = CreateEmptyString();
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
				printf("Your string: ");
				OutString(str);
				printf("\n");
				system("pause");
				break;
			}
			case 2:
			{
				Array* list = FillWordList(str);
				OutWordList(list);
				DeleteList(list);
				system("pause");
				break;
			}
			case 3:
			{
				break;
			}
			default:
				break;
		}
	} while (item != COUNT_ITEMS);
	DeleteArray(str);
}