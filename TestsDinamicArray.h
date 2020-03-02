#pragma once
#include"Headers.h"

void TestIntArray()
{
    printf("%sTest IntArray:%s\n", YELLOW, RESET);

    //Test Create and Get
    bool right = true;
    int result_arr[5] = { 1, 2, 3, 0, 5 };
    Array* arr = CreateInt(4);
    for (size_t i = 0; i < Size(arr); i++)
    {
        right = *GetIntElement(arr, i) ? false : true;
    }
    if (right)
        Success("CreateInt"), Success("GetIntElement");
    else
        Error("During init the array isn't filled zeros");

    //Test Set and PushBack
    for (size_t i = 0; i < Size(arr)-1; i++)
    {
        SetElement(arr, i, &i);
    }
    int a = 5;
    PushBack(arr, &a);
    for (size_t i = 0; i < Size(arr); i++)
    {
        right = *GetIntElement(arr, i)==result_arr[i] ? true : false;
    }
    if (right)
        Success("SetElement"), Success("PushBack");
    else
        Error("Array filling fails");
    DeleteArray(arr);
}

void TestString()
{
    printf("%sTest String:%s\n", YELLOW, RESET);

    //Test Get and Create
    bool right = true;
    char result_str[] = "Hello world hello";
    Array* str = CreateEmptyString();
    if (GetCharElement(str, 0))
        right = false;
    if (right)
        Success("CreateEmptyString"), Success("GetCharElement");
    else
        Error("During init the empty string, it isn't empty");

    //Test Set and PushBack
    PushBackChar(str, 'H');
    PushBackChar(str, '-');
    char e = 'e';
    SetElement(str, 1, &e);
    for (size_t i = 0; i < Size(str); i++)
    {
        right = GetCharElement(str, i) == result_str[i] ? true : false;
    }
    if (right)
        Success("SetElement"), Success("PushBakChar");
    else
        Error("String filling fails");

    //Test CharInString
    DeleteArray(str);
    str = CreateString(result_str);
    Array* separators = CreateString(" ");
    if (!CharInString(str, e))
        right = false;
    if (right)
        Success("CharInString");
    else
        Error("CharInString - Failed");

    //Test NumberWords
    size_t number_words = 3;
    size_t number_different_words = 2;
    if (NumberWords(str, separators) != number_words)
        right = false;
    if (right)
        Success("NumberWords");
    else
        Error("NumberWords - Failed");

    //Test EqualStrings and FindWord
    Array* first_word = FindWord(str, 0, separators);
    Array* last_word = FindWord(str, 2, separators);
    if (!EqualStrings(first_word, last_word))
        right = false;
    if (right)
        Success("FindWord"), Success("EqualStrings");
    else
        Error("The EqualString function does not work correctly, or the parameters in it from the FindWord function are incorrect");
    
    //Test WordInString
    if (!WordInString(str, first_word, separators))
        right = false;
    if (right)
        Success("WordInString");
    else
        Error("WordInString - Faild");
    DeleteArray(first_word);
    DeleteArray(last_word);

    //Test NumberDifferentWords
    if (NumberDifferentWords(str, separators) != number_different_words)
        right = false;
    if (right)
        Success("NumberDifferentWords");
    else
        Error("NumberDifferentWords - Failed");
    DeleteArray(str);
    DeleteArray(separators);
}

void TestList()
{
    printf("%sTest List:%s\n", YELLOW, RESET);

    //Test Get and Create
    bool right = true;
    Array* list = CreateWordList(1);
    if (GetCharElement(GetWordStr(GetWord(list, 0)), 0) || GetIntElement(GetWordPositions(GetWord(list, 0)), 0))
        right = false;
    if (right)
        Success("GetWord"), Success("GetWordStr"), Success("GetWordPositions"), Success("CreateWordList");
    else
        Error("During init the word list isn't filled empty words");
   
    //Test WordInList and FillWordList
    DeleteList(list);
    Array* str = CreateString("Hello world");
    Array* separators = CreateString(" ");
    Array* ban_dict = CreateEmptyString();
    Array* result_word = CreateString("world");
    size_t result_position = 1;
    size_t position;
    list = FillWordList(str, separators, ban_dict);
    if (!WordInList(list, result_word, &position))
        right = false;
    else
        if (position != result_position)
            right = false;
    if (right)
        Success("FillWordList"), Success("WordInList");
    else
        Error("The word list isn't filled or WordInList failed");
    DeleteArray(str);
    DeleteArray(separators);
    DeleteArray(ban_dict);
    DeleteArray(result_word);
    DeleteList(list);
}
