int main(void)
{

    while(1) // 메인 루프
    {
        switch (state)
        {
            case MAIN: // main_screen() 호출
                main_screen(); break;
            case INPUT: // input_screen() 호출
                input_screen(); break;
            case INFO: // info_screen() 호출
                info_screen(); break;
            case SAVELOAD: // SAVELOAD 화면
                saveload_screen(); break;
            case TIMETABLE: // TIMETABLE 화면
                timetable_screen(); break;
            default:
                printf("ending program...\n");
                return 0;
        }
    }
}



#define MAX_SUBJECTS 100
#define MAX_CHILDREN 100
#define MAX_PARENTS 100

enum STATE {MAIN, INPUT, INFO, SAVELOAD, TIMETABLE};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subject.h"
#include "timetable.h"
#include "prereq.h"

// MAIN
void main_screen();
// MAIN > INPUT
void input_screen(); // use create_subject, append_subject

// > info_screen
Subject* select_in_array(Subject** subject_array, int count); // used to delete parent, child

// MAIN > INFO
// info_screen < select_screen() < search_screen()
void info_screen(); // use delete, change, follow
Subject* select_screen();
Subject** search_screen(Map* map);

void info_print(Subject* subject);
void info_interface(Subject* subject);
int select_interface(int index); // RETURNS THE ID

void delete_subject(Subject *subject);
// void free_subject(Subject* subject); (in // Subjects)
void change_subject_screen(Subject* subject); // changes info or parents


void follow_screen(Subject* subject);

// RELATED TO SAVELOAD AND SETTINGS
void saveload_screen(); // SAVEs and LOADs file

void timetable_screen();








#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SEMESTERS 9

typedef struct subject
{
    char name[50]; // 삭제되면 ""
    char tag[50]; // 삭제되면 ""
    int id; // subject_map의 subjects 배열 index와 일치, 삭제되면 -1
    struct subject ** parents;
    int parent_count;
    struct subject ** childs;
    int child_count;
} Subject;

typedef struct map
{
    Subject* subjects; // subjects가 
    int size; // 1개가 1개 (index는 -1 해아함)
} Map;

typedef struct timetable
{
    Map semesters[NUM_SEMESTERS];
} Timetable;

// Basic Functions

Subject* create_subject(char* name, char* tag, int id); // Implement using malloc
void print_map(Map* map); // depth is needed for recursion

// ********** NOT IMPLEMENTED ********** 
void append_subject(Map* map, Subject* subject); // Implement using realloc
// > 함수 안에서 map.size ++; 해줘야함
// void free_subject(Subject* subject);
void free_map(Map* map);

// ********** SEARCH RELATED ********** 
int name_search(char* name, Map* map, int * search_result); //Returns the number of search results, might need another function to define this one recursively

// ********** SAVE LOAD RELATED ********** 
void load_map(Map* map, char* filename);
void save_map(Map* map, char* filename);



Subject* create_subject(char* name, char * tag, int id) { // 이름, 태그, id를 바탕으로 동적할당하여 Subject 생성 , 포인터 반환
    Subject* new_subject = (Subject*)malloc(sizeof(Subject));
    new_subject->id = id;
    // 이름, 태그 복사
    strcpy(new_subject->name, name);
    strcpy(new_subject->tag, tag);
    new_subject->parents = NULL;
    new_subject->childs = NULL;
    new_subject->parent_count = 0;
    new_subject->child_count = 0;
    return new_subject;
}


void append_subject(Map* map, Subject* subject)
{
    map->size++;
    map->subjects = (Subject*)realloc(map->subjects, sizeof(Subject) * map->size);
    map->subjects[map->size - 1] = *subject;
}

void free_map(Map* map)
{
    free(map->subjects);
    free(map);
}


// LOAD AND SAVE
void load_map(Map* map, char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }

    int num_subjects;
    fscanf(file, "%d", &num_subjects);
    map->size = num_subjects;
    map->subjects = (Subject*)malloc(num_subjects * sizeof(Subject));

    for (int i = 0; i < num_subjects; i++)
    {
        char name[50];
        char tag[50];
        int id;
        fscanf(file, "%d %s %s", &id, name, tag);
        map->subjects[i] = *create_subject(name, tag, id);

        int parent_count;
        int child_count;
        fscanf(file, "%d %d", &parent_count, &child_count);
        map->subjects[i].parent_count = parent_count;
        map->subjects[i].child_count = child_count;

        map->subjects[i].parents = (Subject**)malloc(parent_count * sizeof(Subject*));
        map->subjects[i].childs = (Subject**)malloc(child_count * sizeof(Subject*));

        for (int j = 0; j < parent_count; j++)
        {
            int parent_id;
            fscanf(file, "%d", &parent_id);
            map->subjects[i].parents[j] = &map->subjects[parent_id];
        }

        for (int j = 0; j < child_count; j++)
        {
            int child_id;
            fscanf(file, "%d", &child_id);
            map->subjects[i].childs[j] = &map->subjects[child_id];
        }
    }

    fclose(file);
}

void save_map(Map* map, char* filename)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("File not found\n");
        return;
    }

    fprintf(file, "%d\n", map->size);

    for (int i = 0; i < map->size; i++)
    {
        // fprintf(file, "%d %s %s\n", map->subjects[i].id, map->subjects[i].name, map->subjects[i].tag);
        // save id, tag, name and the id of parents and children
        fprintf(file, "%d %s %s %d %d", map->subjects[i].id, map->subjects[i].name, map->subjects[i].tag, map->subjects[i].parent_count, map->subjects[i].child_count);
        for (int j = 0; j < map->subjects[i].parent_count; j++)
        {
            fprintf(file, " %d", map->subjects[i].parents[j]->id);
        }
        for (int j = 0; j < map->subjects[i].child_count; j++)
        {
            fprintf(file, " %d", map->subjects[i].childs[j]->id);
        }
    }

    fclose(file);
}