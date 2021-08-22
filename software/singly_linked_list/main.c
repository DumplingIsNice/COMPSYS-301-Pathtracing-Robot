/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

#include "linkedlist.h"

int main()
{
    printf("Hello World\n");
    
    int value = 10;
    struct Singlylinkedlist* list = NewSinglylinkedlistElement();
    ChangeSinglylinkedlistElementValue(list, value);
    
    int value2 = 20;
    AppendSinglylinkedlist(list, value2);
    value2 = 30;
    AppendSinglylinkedlist(list, value2);
    value2 = 12;
    AppendSinglylinkedlist(list, value2);
    
    
    PrintAllSinglylinkedlistElementValues(list);
    printf("\n");
    
    struct Singlylinkedlist* elementToRemove = (list->tail)->tail;
    list = RemoveSinglylinkedlistElement(list, elementToRemove);
    
    PrintAllSinglylinkedlistElementValues(list);

    return 0;
}
