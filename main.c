#include <stdio.h>
#include <string.h>
#include "main.h"


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



Subject* create_subject(char* name, int id) // Implement using malloc
{
    Subject* new_subject = (Subject*)malloc(sizeof(Subject));
    if (new_subject == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    strcpy(new_subject->name, name);
    strcpy(new_subject->tag, "");
    new_subject->id = id;
    new_subject->childs = NULL;
    new_subject->child_count = 0;
    new_subject->parents = NULL;
    new_subject->parent_count = 0;
    return new_subject;
}

void append_subject(Map* map, Subject* subject) // Implement using realloc
{
    map->size++;
    map->subjects = (Subject*)realloc(map->subjects, sizeof(Subject)*map->size);
    map->subjects[map->size-1] = *subject;
}

void free_subject(Subject* subject)
{
    free(subject);
}

void free_map(Map* map)
{
    free(map->subjects);
}

Timetable* create_timetable()
{
    Timetable* new_timetable = (Timetable*)malloc(sizeof(Timetable));
    if (new_timetable == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    for (int i=0; i<6; i++)
    {
        new_timetable->semesters[i] = NULL;
    }
    return new_timetable;
}

void append_to_timetable(Timetable* timetable, Subject* subject, int semester) // Implement using malloc
{

}
void remove_from_timetable(Timetable* timetable, Subject* subject, int semester); // Implement using free
void free_timetable(Timetable* timetable);

void print_map(Map* map, int depth); // depth is needed for recursion
void delete_node(Subject* subject, Map* map); // Need to Free!

int name_search(char* name, Map* map, int * search_result); //Returns the number of search results, might need another function to define this one recursively
void load_map(Map* map, char* filename);
void save_map(Map* map, char* filename);
