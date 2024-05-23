#include <stdio.h>
#include "main.h"


enum STATE {MAIN, INPUT, SEARCH, SELECT, INFO, FOLLOW, SAVELOAD};

int main(void)
{

    enum STATE state;

    Subject* subject_to_call;
    Subject** select_array;

    while(1)
    {
        switch (state)
        {
            case MAIN:
                main_screen(&state); break;
            case INPUT:
                input_screen(&state); break;
            case SEARCH:
                search_screen(&state); break;
            case SELECT:
                select_screen(&state); break;
            case INFO:
                info_screen(subject_to_call, &state); break;
            case FOLLOW:
                select_array = follow_parent_screen(subject_to_call, &state); break;
            case SAVELOAD:
                saveload_screen(&state); break;

            default: return 1;
        }
    }
    

}

/*
main_screen()
    input_screen()
    search_screen()  // strin 이용하여 pointer배열 반환?
        select_screen() // pointer배열에서 선택 (?번째)
            info_screen() // 선택한 Subject
                delete
                change
                follow parent
    saveload_screen()
*/

void main_screen(enum STATE* pstate)
{
    return SELECT;
}