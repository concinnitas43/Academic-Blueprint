#include "subject.h"

// Subjects

// Subject 초기화 함수
Subject* create_subject(char* name, char * tag, int id) {
    Subject* new_subject = (Subject*)malloc(sizeof(Subject));
    new_subject->id = id;
    strcpy(new_subject->name, name);
    strcpy(new_subject->tag, tag);  // 태그 설정
    new_subject->parents = NULL;
    new_subject->childs = NULL;
    new_subject->parent_count = 0;
    new_subject->child_count = 0;
    return new_subject;
}

// Map 출력 함수
void print_map(Map* map) {
    for (int i = 0; i < map->size; i++) {
        printf("ID: %d, Name: %s, Tag: %s\n", map->subjects[i].id, map->subjects[i].name, map->subjects[i].tag);
    }
}

// 비교 함수
int compare_subjects(const void* a, const void* b) {
    Subject* subjectA = *(Subject**)a;
    Subject* subjectB = *(Subject**)b;
    return (subjectA->id - subjectB->id);
}

// 이거 왜 있는거임 ?? 헤더 파일에 정의된적도 없고 사용된적도 없음
// Map 생성 함수 
// Map* create_map(Subject* subjects, int num_subjects) {
//     Map* map = (Map*)malloc(sizeof(Map));
//     map->subjects = (Subject*)malloc(num_subjects * sizeof(Subject));
//     memcpy(map->subjects, subjects, num_subjects * sizeof(Subject));
//     map->size = num_subjects;
//     qsort(map->subjects, num_subjects, sizeof(Subject*), compare_subjects);
//     return map;
// }

// 구조체 해제 함수
void free_subject(Subject* subject) {
    free(subject->parents);
    free(subject->childs);
    free(subject);
}


// Subject Map 출력 함수 (선행 과목 출력)
void print_subject_map(Subject* subject, int depth) {
    if (depth < 0 || subject == NULL) { // 깊이가 0보다 작거나 Subject가 NULL인 경우
        return; // 함수 종료
    }

    // 출력 들여쓰기
    for (int i = 0; i < depth; i++) {
        printf("  "); // 깊이에 따라 들여쓰기
    }

    // 현재 과목 출력
    printf("%3d : %s (%s)\n", subject->id, subject->name, subject->tag);

    // 모든 부모 과목에 대해 재귀 호출
    for (int i = 0; i < subject->parent_count; i++) {
        print_subject_map(subject->parents[i], depth - 1); // 부모 과목에 대해 재귀 호출
    }
}

// Subject 계층 구조 출력 함수 (후속 과목 출력)
void print_subject_hierarchy(Subject* subject, int level) {
    if (subject == NULL) return; // Subject가 NULL인 경우 함수 종료
    for (int i = 0; i < level; i++) {
        printf("  "); // 레벨에 따라 들여쓰기
    }
    printf("%3d : %s (%s)\n", subject->id, subject->name, subject->tag); // 현재 과목 출력
    for (int i = 0; i < subject->child_count; i++) {
        print_subject_hierarchy(subject->childs[i], level + 1); // 자식 과목에 대해 재귀 호출
    }
}

// 과목이 Map에 존재하는지 확인하는 함수
int subject_exists(Map* map, Subject* subject) {
    for (int i = 0; i < map->size; i++) {
        if (&(map->subjects[i]) == subject) {
            return 1;
        }
    }
    return 0;
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
