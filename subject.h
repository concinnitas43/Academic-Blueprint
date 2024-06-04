#ifndef SUBJECT_H
#define SUBJECT_H

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

// Subjects

Subject* create_subject(char* name, char* tag, int id); // Implement using malloc
void append_subject(Map* map, Subject* subject); // Implement using realloc
// > 함수 안에서 map.size ++; 해줘야함
// void free_subject(Subject* subject);
void free_map(Map* map);

void print_map(Map* map); // depth is needed for recursion
void print_subject_map(Subject* subject, int depth); // subject 내의 Subject ** parents, childs 이용하여 재귀적으로?
// void delete_node(Subject* subject, Map* map); // Need to Free!

void load_map(Map* map, char* filename);
void save_map(Map* map, char* filename);


#endif