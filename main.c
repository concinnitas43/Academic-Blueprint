#include <stdio.h>
#include "main.h"


// enum STATE {MAIN, INPUT, SEARCH, SELECT, INFO, FOLLOW, SAVELOAD};


enum STATE state;
Map subject_map={NULL, 0};

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
    printf("hi, this is the main screen.\n");
    printf("menu:\n");
    printf("\tinput subject: 0\n");
    printf("\tsearch subject: 1\n");
    printf("\tsave & load: 2\n");
    printf("input: ");
    int st=-1;
    scanf("%d", &st);
    switch(st){
        case 0:
            state = INPUT;
            break;
        case 1:
            state = SEARCH;
            break;
        case 2:
            state = SAVELOAD;
            break;
        default:
            printf("input ERROR. loading main screen again...\n");
            state = MAIN;
    }
    return;
}




// RELATED TO INPUT
void input_screen()
{
    printf("hi, this is the input screen.\n");
    printf("menu:\n\tinput subject: 0\n\tgo back to main screen: -1\n");
    printf("input: ");
    int st=-1; // select screen
    scanf("%d", &st);
    if(st!=0) // back to main
    {
        state = MAIN;
        return;
    }
    char name[50], tag[50]; // input name, tag
    printf("name? ");
    scanf("%s", name);
    printf("tag? ");
    scanf("%s", tag);
    int osize = subject_map.size; // old size of subject map
    Subject *newsub = create_subject(name, tag, osize); // create new subject and get pointer
    append_subject(&subject_map, newsub); // append new subject in subject map
    state = MAIN; // go to MAIN next
    if(osize + 1 == subject_map.size){ // if size of map increased properly
        printf("subject successfully added.\n");
        return;
    }
    printf("ERROR on adding subject.\n"); // if else
    return;
} // use create_subject, append_subject

// RELATED TO SEARCH
Subject** search_screen()
{
    return NULL;
} // SEARCH -> SELECT -> INFO
// > select_screen
char* search_interface()
{
    return NULL;
}
int select_interface(char* search)
{
    return 0;
} // RETURNS THE ID

// RELATED TO SELECT
Subject* select_screen(Subject** subject_array)
{
    return NULL;
}
// > info_screen

// RELATED TO INFO
void info_screen(Subject* subject)
{
    return;
} // use delete, change, follow
void add_prereq_interface(Subject* child)
{
    return;
} // select parent using search & select interface, then add prereq
void delete_prereq_interface(Subject* child)
{
    return;
} // select parent using search & select interface, then delete prereq
void add_to_timetable(Subject* subject, Timetable* timetable, int semester)
{
    return;
} // add to timetable

// interface of INFO
// void free_subject(Subject* subject); (in // Subjects)
void change_subject_interface(Subject* subject)
{
    return;
} // changes info or parents
Subject** follow_parent_screen(Subject* subject)
{
    return NULL;    
    // state = SELECT;
} // return array of parent pointer to SELECT
Subject** follow_child_screen(Subject* subject)
{
    return NULL;
} // return array of child pointer to SELECT

// RELATED TO SAVELOAD AND SETTINGS
void saveload_screen()
{
    return;
} // SAVEs and LOADs file
