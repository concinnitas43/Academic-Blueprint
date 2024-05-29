#include <stdio.h>
#include "main.h"


// enum STATE {MAIN, INPUT, SEARCH, SELECT, INFO, FOLLOW, SAVELOAD};


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


// *****************
// jiyeon 

// RELATED TO MAIN
void main_screen()
{
    return INPUT;
    return SEARCH;
    return SAVELOAD;
}




// RELATED TO INPUT
void input_screen(); // use create_subject, append_subject

// RELATED TO SEARCH
Subject** search_screen(); // SEARCH -> SELECT -> INFO
// > select_screen
char* search_interface();
int select_interface(char* search); // RETURNS THE ID

// RELATED TO SELECT
Subject* select_screen(Subject** subject_array);
// > info_screen

// RELATED TO INFO
void info_screen(Subject* subject); // use delete, change, follow
void add_prereq_interface(Subject* child); // select parent using search & select interface, then add prereq
void delete_prereq_interface(Subject* child); // select parent using search & select interface, then delete prereq
void add_to_timetable(Subject* subject, Timetable* timetable, int semester); // add to timetable

// interface of INFO
// void free_subject(Subject* subject); (in // Subjects)
void change_subject_interface(Subject* subject); // changes info or parents
Subject** follow_parent_screen(Subject* subject) // return array of parent pointer to SELECT
{
    
    state = SELECT;
}
Subject** follow_child_screen(Subject* subject); // return array of child pointer to SELECT

// RELATED TO SAVELOAD AND SETTINGS
void saveload_screen(); // SAVEs and LOADs file
