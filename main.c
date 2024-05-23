#include <stdio.h>
#include "main.h"

typedef struct {
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
        case MAIN: main_screen(); break;
        case INPUT: input_screen(); break;
        case SEARCH: search_screen(); break;
        case SELECT: select_screen(); break;
        case INFO: info_screen(); break;
        case SAVELOAD: saveload_screen(); break;

        default: return 1;

    }

}

void main_screen() {



}

