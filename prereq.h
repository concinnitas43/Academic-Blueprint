#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "subject.h"

typedef struct Queue {
    Subject** subjects;
    int front;
    int rear;
    int capacity;
} Queue;

// int check_cycle(Subject* subject); // after connect Parent subject with Child subject, Returns 1 if there is a cycle start with parent subject, 0 if not(by dfs)
// int add_prereq(Subject* parent, Subject* child); // add them both ways (return 0), if already exists (return 1), do nothing. if there is a cycle, return 2
// int remove_prereq(Subject* parent, Subject* child); // remove them both ways(return 0), if not exists(return -1), do nothing

// 함수 정의 부분
// Subject* create_subject(int id, const char* name, const char* tag);
void print_map(Map* map);
int compare_subjects(const void* a, const void* b);
Map* create_map(Subject** subjects, int num_subjects);
int subject_exists(Map* map, Subject* subject);
int add_prereq(Map* map, Subject* child, Subject* parent);
int remove_prereq(Subject* child, Subject* parent);
void free_subject(Subject* subject);
Queue* create_queue(int capacity);
Subject* dequeue(Queue* queue);
int is_empty(Queue* queue);
int check_cycle(Subject* subject);
void enqueue(Queue* queue, Subject* subject);
void print_subject_map(Subject* subject, int depth, int is_first);
void print_subject_hierarchy(Subject* subject, int level, int depth);
int is_prerequisite(Subject* subject, Subject* potential_prereq);
Subject** find_common_prerequisites(Subject* subject1, Subject* subject2, int* common_count);
int find_path(Subject* current, Subject* target, Subject** path, int* path_index, int* visited, int visited_size);
void print_path(Subject* subject1, Subject* subject2);
void find_longest_path(Subject* start, Subject* end, int* visited, Subject** path, int path_index, Subject** longest_path, int* longest_path_index);
void print_longest_path(Map* map, Subject* start, Subject* end);
void print_shortest_path(Map* map, Subject* start, Subject* end);
void create_tree(Subject* subject, int level, int is_last, int* parent_levels);
void print_tree(Map* map);
int has_tagged_child(Subject* subject, const char* filter_tag);
void create_tag_tree(Subject* subject, int level, int is_last, int* parent_levels, const char* filter_tag);
void print_tag_tree(Map* map, const char* filter_tag);
void remove_cycle(Map* map);
void handle_inconsistent_prereq(Map* map);
void remove_redundant_prereqs(Map* map);
