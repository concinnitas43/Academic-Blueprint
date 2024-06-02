#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
                select_array = search_screen(&subject_map); break;
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


// Subjects

Subject* create_subject(char* name, char* tag, int id)
{
    return NULL;
} // Implement using malloc
void append_subject(Map* map, Subject* subject)
{
    return;
} // Implement using realloc
// > 함수 안에서 map.size ++; 해줘야함
void free_subject(Subject* subject)
{
    return;
}
void free_map(Map* map)
{
    return;
}
void append_to_timetable(Timetable* timetable, Subject* subject, int semester)
{
    return;
} // Implement using malloc
void remove_from_timetable(Timetable* timetable, Subject* subject, int semester)
{
    return;
} // Implement using free
void free_timetable(Timetable* timetable)
{
    return;
}

void print_map(Map* map, int depth)
{
    return;
} // depth is needed for recursion
void delete_node(Subject* subject, Map* map)
{
    return;
} // Need to Free!

int name_search(char* name, Map* map, int * search_result)
{
    return 0;
} //Returns the number of search results, might need another function to define this one recursively

int check_cycle(Subject* subject)
{
    return 0;
} // after connect Parent subject with Child subject, Returns 1 if there is a cycle start with parent subject, 0 if not(by dfs)
int add_prereq(Subject* parent, Subject* child)
{
    return 0;
} // add them both ways (return 0), if already exists (return 1), do nothing. if there is a cycle, return 2
int remove_prereq(Subject* parent, Subject* child)
{
    return 0;
} // remove them both ways(return 0), if not exists(return -1), do nothing

void load_map(Map* map, char* filename)
{
    return;
}
void save_map(Map* map, char* filename)
{
    return;
}

int is_valid(int type1, Subject** subject)
{
    return 0;
} // Check if the timetable is valid(return 0) if not(return all error semesters(ex 2345))
int exceed_subjects(Timetable* timetable)
{
    return 0;
} //check if the timetable exceed the maximum number of subjects each semester(return 0) if not (return all exceeding semesters(ex 125))
Subject** possible_semester(Timetable* timetable)
{
    return NULL;
} // check if all subjects are possible to register at that semester(return None) if not (return the array of impossible subjects)



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
    printf("menu:\n\tinput subject: 0\n\tgo back to main screen: else\n");
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
Subject** search_screen(Map* map)
{
    Map s_map = *map; // search screen의 map
    int s_size = s_map.size; // search screen의 map size
    Subject *s_subjects = s_map.subjects; // search screen의 subjects 배열

    printf("hi, this is the search screen.\n");
    printf("menu:\n\tsearch subject: 0\n\tgo back to main screen: else\n");
    printf("input: ");
    int st=-1; // select screen
    scanf("%d", &st);
    if(st!=0) // back to main
    {
        state = MAIN;
        return NULL;
    }

    Subject **pointers = (Subject **) malloc(sizeof(Subject *));
    int searched_size=0;
    printf("word to search? "); // search by name (tag 할수도)
    char word[50];
    scanf("%s", word);
    for(int i=0; i<s_size; i++)
    {
        if(strstr(s_subjects[i].name, word) != NULL)
        {
            pointers[searched_size]=&(s_subjects[i]);
            searched_size++;
            pointers = (Subject **) realloc(pointers, (searched_size+1) * sizeof(Subject *));
        }
    }
    pointers[searched_size]=NULL;

    state = SELECT;
    return pointers;
} // SEARCH -> SELECT -> INFO
// > select_screen
// char* search_interface()
// {
//     return NULL;
// }
int select_interface(int index)
{
    printf("select index. ");
    int sel_index=-1; // select index
    scanf("%d", &sel_index);

    if(sel_index>=index || sel_index<0)
    {
        printf("ERROR. select again.\n");
        select_interface(index);
    }

    return sel_index;
} // RETURNS THE ID

// RELATED TO SELECT
Subject* select_screen(Subject** subject_array)
{
    int index=0;
    printf("hi, this is the select screen.\n");

    while(subject_array[index]!=NULL)
    {
        printf("index %d: ", index);
        printf("name: %s tag: %s\n", subject_array[index]->name, subject_array[index]->tag);
        index++;
    }

    int sel_index = select_interface(index);

    printf("%s selected.\n", subject_array[sel_index]->name);
    return subject_array[sel_index];
}
// > info_screen

// RELATED TO INFO
void info_screen(Subject* subject)
{
    printf("subject info:\n");
    printf("name: %s tag: %s\n", subject->name, subject->tag);
    
    // delete, change, follow

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
