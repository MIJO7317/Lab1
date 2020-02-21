#include<stdio.h>
#include<stdlib.h>
#include"Header.h"

void Menu()
{
	system("cls");
	printf("1) Input string\n");
	printf("2) Show positions of words\n");
	printf("3) Test\n");
}

int SelectedMenuItem()
{
	int number_item; //Пункт меню, который выбирает пользователь
	int result; //Результат работы функции scanf_s()
	int count_items=3; //Количество пунктов меню
	do
	{
		Menu();
		printf("Please, input number item: ");
		result = scanf_s("%d", &number_item);
		!result ? scanf_s("%*s") : 0;
	} while (!result || number_item>count_items || number_item<=0);
	ClearStdin();
	return number_item;
}

int main()
{
	int item = SelectedMenuItem();//Выбранный пункт меню
	system("cls");
	switch (item)
	{
		case 1 :
		{
			printf("Input string with words(Max quantity of cymbols - 1000):\n");
			Array* str = InputString();
			printf("Your string: ");
			OutString(str);
			printf("\nNumber words:");
			printf("%d",NumberWords(str));
			break;
		}
		case 2 :
		{
			break;
		}
		case 3 :
		{
			break;
		}
	}
}