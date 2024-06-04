#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Subject 구조체 정의
typedef struct Subject {
    int id;                  
    char name[50];
    char tag[50];                
    struct Subject **parents;
    struct Subject **childs;
    int parent_count;
    int child_count;
} Subject;

// Map 구조체 정의
typedef struct {
    Subject** subjects;
    int size;
} Map;

// Subject 초기화 함수
Subject* create_subject(int id, const char* name, const char* tag) {
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
        printf("ID: %d, Name: %s, Tag: %s\n", map->subjects[i]->id, map->subjects[i]->name, map->subjects[i]->tag);
    }
}

// 비교 함수
int compare_subjects(const void* a, const void* b) {
    Subject* subjectA = *(Subject**)a;
    Subject* subjectB = *(Subject**)b;
    return (subjectA->id - subjectB->id);
}

// Map 생성 함수
Map* create_map(Subject** subjects, int num_subjects) {
    Map* map = (Map*)malloc(sizeof(Map));
    map->subjects = (Subject**)malloc(num_subjects * sizeof(Subject*));
    memcpy(map->subjects, subjects, num_subjects * sizeof(Subject*));
    map->size = num_subjects;
    qsort(map->subjects, num_subjects, sizeof(Subject*), compare_subjects);
    return map;
}

// 선행 과목 추가 함수
int add_prereq(Subject* child, Subject* parent) {
    // 이미 선행 과목 관계가 존재하는지 확인
    for (int i = 0; i < child->parent_count; i++) {
        if (child->parents[i] == parent) {
            return 1; // 이미 존재하는 관계
        }
    }

    child->parent_count++;
    child->parents = (Subject**)realloc(child->parents, child->parent_count * sizeof(Subject*));
    child->parents[child->parent_count - 1] = parent;

    parent->child_count++;
    parent->childs = (Subject**)realloc(parent->childs, parent->child_count * sizeof(Subject*));
    parent->childs[parent->child_count - 1] = child;

    // 사이클 발생 여부 확인
    if (check_cycle(parent)) {
        // 추가한 관계를 원복
        child->parent_count--;
        parent->child_count--;

        // 부모에서 마지막 추가된 자식 제거
        child->parents = (Subject**)realloc(child->parents, child->parent_count * sizeof(Subject*));
        parent->childs = (Subject**)realloc(parent->childs, parent->child_count * sizeof(Subject*));

        return 2; // 사이클 발생
    }

    return 0; // 성공적으로 추가됨
}

// 선행 과목 제거 함수
int remove_prereq(Subject* child, Subject* parent) {
    int parent_found = 0;
    int child_found = 0;

    // 부모에서 자식 제거
    for (int i = 0; i < parent->child_count; i++) {
        if (parent->childs[i] == child) {
            parent_found = 1;
            for (int j = i; j < parent->child_count - 1; j++) {
                parent->childs[j] = parent->childs[j + 1];
            }
            parent->child_count--;
            parent->childs = (Subject**)realloc(parent->childs, parent->child_count * sizeof(Subject*));
            break;
        }
    }

    // 자식에서 부모 제거
    for (int i = 0; i < child->parent_count; i++) {
        if (child->parents[i] == parent) {
            child_found = 1;
            for (int j = i; j < child->parent_count - 1; j++) {
                child->parents[j] = child->parents[j + 1];
            }
            child->parent_count--;
            child->parents = (Subject**)realloc(child->parents, child->parent_count * sizeof(Subject*));
            break;
        }
    }

    return (parent_found && child_found) ? 0 : -1; // 성공적으로 제거됨
}

// 구조체 해제 함수
void free_subject(Subject* subject) {
    free(subject->parents);
    free(subject->childs);
    free(subject);
}

// 큐 정의
typedef struct Queue {
    Subject **subjects;
    int front;
    int rear;
    int capacity;
} Queue;

// 큐 초기화 함수
Queue* create_queue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->subjects = (Subject**)malloc(capacity * sizeof(Subject*));
    queue->front = 0;
    queue->rear = 0;
    queue->capacity = capacity;
    return queue;
}

// 큐 삽입 함수
void enqueue(Queue* queue, Subject* subject) {
    if (queue->rear == queue->capacity) {
        queue->capacity *= 2;
        queue->subjects = (Subject**)realloc(queue->subjects, queue->capacity * sizeof(Subject*));
    }
    queue->subjects[queue->rear++] = subject;
}

// 큐 삭제 함수
Subject* dequeue(Queue* queue) {
    if (queue->front == queue->rear) {
        return NULL;
    }
    return queue->subjects[queue->front++];
}

// 큐가 비어있는지 확인하는 함수
int is_empty(Queue* queue) {
    return queue->front == queue->rear;
}

// 사이클 감지 함수
int check_cycle(Subject* subject) {
    Queue* queue = create_queue(10); // 큐 초기화
    enqueue(queue, subject); // 초기 과목을 큐에 추가

    // 방문 여부를 추적하기 위한 해시 테이블 크기
    int visited_size = 100;
    Subject** visited = (Subject**)calloc(visited_size, sizeof(Subject*));

    while (!is_empty(queue)) {
        Subject* current = dequeue(queue); // 큐에서 과목을 하나 꺼냄

        // 이미 방문한 노드인지 확인
        for (int i = 0; i < visited_size; i++) {
            if (visited[i] == current) { // 현재 과목이 이미 방문한 과목이라면
                if (current == subject) { // 그리고 그 과목이 시작 과목이라면
                    free(queue->subjects); // 메모리 해제
                    free(queue);
                    free(visited);
                    return 1; // 사이클이 발견됨
                }
                break;
            }
        }

        // 방문하지 않은 노드라면 방문 표시
        for (int i = 0; i < visited_size; i++) {
            if (visited[i] == NULL) {
                visited[i] = current; // 방문한 과목 배열에 추가
                break;
            }
        }

        // 부모 과목을 큐에 추가
        for (int i = 0; i < current->parent_count; i++) {
            enqueue(queue, current->parents[i]);
        }
    }

    free(queue->subjects); // 메모리 해제
    free(queue);
    free(visited);
    return 0; // 사이클이 발견되지 않음
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