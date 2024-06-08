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

// Subject Map 출력 함수
void print_subject_map(Subject* subject, int depth) {
    if (depth < 0 || subject == NULL) {
        return;
    }
    
    // 출력 들여쓰기
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    // 현재 과목 출력
    printf("ID: %d, Name: %s, Tag: %s\n", subject->id, subject->name, subject->tag);
    
    // 모든 부모 과목에 대해 재귀 호출
    for (int i = 0; i < subject->parent_count; i++) {
        print_subject_map(subject->parents[i], depth - 1);
    }
}

