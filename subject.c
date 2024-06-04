#include <stdio.h>
#include "subject.h"
#include "timetable.h"

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
// void free_subject(Subject* subject);

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

// void print_map(Map* map)
// {
//     return;
// } // depth is needed for recursion
void print_subject_map(Subject* subject, int depth)
{
    return;
} // subject 내의 Subject ** parents, childs 이용하여 재귀적으로?

// void delete_node(Subject* subject, Map* map); // Need to Free!

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

// Timetable* create_timetable()
// {
//     Timetable* new_timetable = (Timetable*)malloc(sizeof(Timetable));
//     if (new_timetable == NULL)
//     {
//         printf("Memory allocation failed\n");
//         return NULL;
//     }
//     for (int i=0; i<6; i++)
//     {
//         new_timetable->semesters[i] = NULL;
//     }
//     return new_timetable;
// }

void append_to_timetable(Timetable* timetable, Subject* subject, int semester) // Implement using malloc
{

}
void remove_from_timetable(Timetable* timetable, Subject* subject, int semester); // Implement using free
void free_timetable(Timetable* timetable);

void print_map(Map* map); // depth is needed for recursion
void delete_node(Subject* subject, Map* map); // Need to Free!

int name_search(char* name, Map* map, int * search_result); //Returns the number of search results, might need another function to define this one recursively
void load_map(Map* map, char* filename);
void save_map(Map* map, char* filename);
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


