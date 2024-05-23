#include <stdio.h>
#include "main.h"


enum STATE {MAIN, INPUT, SEARCH, SELECT, INFO, FOLLOW, SAVELOAD};


enum STATE state;
Map map={NULL, 0};

int main(void)
{



    Subject* subject_to_call;
    Subject** select_array;

    while(1)
    {
        switch (state)
        {
            case MAIN:
                main_screen(); break;
            case INPUT:
                input_screen(); break;
            case SEARCH:
                select_array = search_screen(); break;
            case SELECT:
                subject_to_call = select_screen(select_array); break;
            case INFO:
                info_screen(subject_to_call); break;
            case FOLLOW:
                select_array = follow_parent_screen(subject_to_call); break;
            case SAVELOAD:
                saveload_screen(); break;

            default: return 1;
        }
    }
    

}

/*
main_screen()
    input_screen()
    search_screen()  // strin 이용하여 pointer배열 반환?
        select_screen() // pointer배열에서 선택 (?번째)
            info_screen() // 선택한 Subject의 info
                free
                change
                follow_parent
    saveload_screen()
*/

void main_screen()
{
    return INPUT;
    return SEARCH;
    return SAVELOAD;
}

Subject** follow_parent_screen(Subject* subject)
{
    
    state = SELECT;
}
