#include <stdio.h>
#include "main.h"

typedef struct
{
    char name[50];
    char tag[50];
    int id;
} subject;

enum STATE {MAIN, INPUT, SEARCH, SELECT, INFO, SAVELOAD};

int main(void)
{

    enum STATE state;


    switch (state)
    {
        case MAIN:
            state = main_screen(); break;
        case INPUT:
            state = input_screen(); break;
        case SEARCH:
            state = search_screen(); break;
        case SELECT:
            state = select_screen(); break;
        case INFO:
            state = info_screen(); break;
        case SAVELOAD:
            state = saveload_screen(); break;

        default: return 1;

    }

}