#include "prereq.h"

// int main() {
//     // 과목 생성

//     Subject* subjects[] = { math, physics, chemistry, biology, english, history,
//                            advancedPhysics, advancedChemistry, advancedBiology, advancedMath,
//                            quantumPhysics, molecularBiology, test };
//     Map* map = create_map(subjects, 13);

//     // 선행 과목 관계 추가
//     add_prereq(map, physics, math);
//     add_prereq(map, chemistry, math);
//     add_prereq(map, biology, chemistry);
//     add_prereq(map, advancedPhysics, physics);
//     add_prereq(map, advancedChemistry, chemistry);
//     add_prereq(map, advancedBiology, biology);
//     add_prereq(map, advancedMath, math);
//     add_prereq(map, quantumPhysics, advancedPhysics);
//     add_prereq(map, quantumPhysics, advancedMath);
//     add_prereq(map, quantumPhysics, advancedBiology);
//     add_prereq(map, test, quantumPhysics);
//     add_prereq(map, advancedChemistry, biology);
//     add_prereq(map, test, biology);
//     add_prereq(map, math, advancedPhysics);

//     // 전체 과목 맵 출력
//     printf("All subjects in the map:\n");
//     print_map(map);  // ID 순으로 정렬하여 출력
//     print_tree(map); // map tree 출력
//     char my_tag[]="core"; 
//     print_tag_tree(map, my_tag); // core map tree 출력
    
//     //오류 확인 함수들
//     handle_inconsistent_prereq(map); // A->B에서 한방향만 존재하는 경우(후에 파일처리시 발생할 수 있는 오류) 
//     remove_redundant_prereqs(map); // A-B-C A-C 구조
//     remove_cycle(map); // cycle(후에 파일처리시 발생할 수 있는 오류)

//     // 특정 과목의 선행 과목 구조 출력
//     printf("\nSubject Map for Advanced Physics:\n");
//     print_subject_map(advancedPhysics, 2);

//     // 특정 과목의 계층 구조 출력
//     printf("\nSubject Hierarchy for Math:\n");
//     print_subject_hierarchy(math, 0);

//     // 선행 과목 관계 제거
//     printf("\nRemoving Math as a prerequisite for Physics:\n");
//     //remove_prereq(physics, math);
//     //remove_prereq(physics, math); // 없는 관계 제거 경우

//     // 제거 후 과목 맵 출력
//     printf("All subjects in the map after removal:\n");
//     print_map(map);  // ID 순으로 정렬하여 출력

//     // 특정 과목의 계층 구조 출력
//     printf("\nSubject Hierarchy for Math:\n");
//     print_subject_hierarchy(math, 0);

//     // 선행과목 관계 확인
//     printf("\nChecking if Math is a prerequisite for Advanced Physics:\n");
//     printf("%s\n", is_prerequisite(advancedPhysics, math) ? "Yes" : "No");

//     // 공통 직계 선행과목 확인
//     printf("\nFinding common prerequisites for advancedBiology and advancedChemistry:\n");
//     int common_count;
//     Subject** common_prereqs = find_common_prerequisites(advancedBiology, advancedChemistry, &common_count);
//     if (common_count > 0) {
//         for (int i = 0; i < common_count; i++) {
//             printf("%3d : %s (%s)\n\n", common_prereqs[i]->id, common_prereqs[i]->name, common_prereqs[i]->tag);
//         }
//     }
//     else {
//         printf("No common prerequisites found.\n\n");
//     }
//     free(common_prereqs);

//     // math - test 경로 출력
//     print_path(math, test);
//     print_longest_path(map, math, test);
//     print_shortest_path(map, math, test);
    
//     // tree 출력(제거 후)
//     print_tree(map);

//     // 메모리 해제
//     free_subject(math);
//     free_subject(physics);
//     free_subject(chemistry);
//     free_subject(advancedPhysics);
//     free(map->subjects);
//     free(map);

//     return 0;
// }


// Subject 초기화 함수
// // subject 비교 함수(qsort에 사용됨)
// int compare_subjects(const void* a, const void* b) {
//     Subject* subject1 = *(Subject**)a; // 첫 번째 Subject 포인터
//     Subject* subject2 = *(Subject**)b; // 두 번째 Subject 포인터
//     return (subject1->id - subject2->id); // ID를 기준으로 비교
// }

// // Map 생성 함수
// Map* create_map(Subject** subjects, int num_subjects) {
//     Map* map = (Map*)malloc(sizeof(Map)); // Map에 대한 메모리 할당
//     map->subjects = (Subject**)malloc(num_subjects * sizeof(Subject*)); // Subject 배열에 대한 메모리 할당
//     memcpy(map->subjects, subjects, num_subjects * sizeof(Subject*)); // Subject 배열 복사
//     map->size = num_subjects; // Map 크기 설정
//     qsort(map->subjects, num_subjects, sizeof(Subject*), compare_subjects); // Subject 배열 정렬
//     return map; // 생성된 Map 반환
// }

// 선행 과목 추가 함수
int add_prereq(Map* map, Subject* child, Subject* parent)
{
    // 부모와 자식 과목이 모두 Map에 존재하는지 확인
    if (!subject_exists(map, child))
    {
        printf("Error: Subject %s does not exist in the map.\n", child->name);
        return -1;
    }
    if (!subject_exists(map, parent))
    {
        printf("Error: Subject %s does not exist in the map.\n", parent->name);
        return -1;
    }

    // 이미 선행 과목 관계가 존재하는지 확인
    for (int i = 0; i < child->parent_count; i++)
    {
        if (child->parents[i] == parent)
        {
            return 1; // 이미 존재하는 관계
        }
    }

    // 선행 과목 관계 추가
    child->parent_count++; // 선행 과목 수 증가
    child->parents = (Subject**)realloc(child->parents, child->parent_count * sizeof(Subject*)); // 선행 과목 배열 재할당
    child->parents[child->parent_count - 1] = parent; // 선행 과목 배열에 부모 추가

    // 후속 과목 관계 추가
    parent->child_count++; // 후속 과목 수 증가
    parent->childs = (Subject**)realloc(parent->childs, parent->child_count * sizeof(Subject*)); // 후속 과목 배열 재할당
    parent->childs[parent->child_count - 1] = child; // 후속 과목 배열에 자식 추가

    // 사이클 발생 여부 확인
    if (check_cycle(parent)) // 사이클 발생 시
    {
        // 추가한 관계를 원복
        child->parent_count--; // 선행 과목 수 감소
        parent->child_count--; // 후속 과목 수 감소

        // 부모에서 마지막 추가된 자식 제거
        child->parents = (Subject**)realloc(child->parents, child->parent_count * sizeof(Subject*)); // 선행 과목 배열 재할당
        parent->childs = (Subject**)realloc(parent->childs, parent->child_count * sizeof(Subject*)); // 후속 과목 배열 재할당
        printf("Can't add the prerequisite between %s and %s since it creates a cycle\n", child->name, parent->name); // 사이클 발생 메시지 출력
        return 2; // 사이클 발생
    }
    printf("Successfully added the prerequisite relationship between %s and %s\n", parent->name, child->name); // 성공 메시지 출력
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



// // 큐 정의
// typedef struct Queue {
//     Subject **subjects;
//     int front;
//     int rear;
//     int capacity;
// } Queue;

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

// 선행 관계 확인 함수
int is_prerequisite(Subject* subject, Subject* potential_prereq) {
    if (subject == NULL) return 0; // Subject가 NULL인 경우 0 반환

    for (int i = 0; i < subject->parent_count; i++) {
        if (subject->parents[i] == potential_prereq) { // 직접적인 선행 과목 확인
            return 1; // 선행 과목이면 1 반환
        }
        if (is_prerequisite(subject->parents[i], potential_prereq)) { // 재귀적으로 선행 과목 확인
            return 1; // 선행 과목이면 1 반환
        }
    }
    return 0; // 선행 과목이 아닌 경우 0 반환
}

// 공통 선행 과목 찾기 함수
Subject** find_common_prerequisites(Subject* subject1, Subject* subject2, int* common_count) {
    int max_size = subject1->parent_count < subject2->parent_count ? subject1->parent_count : subject2->parent_count; // 공통 선행 과목 최대 크기 설정
    Subject** common_prereqs = (Subject**)malloc(max_size * sizeof(Subject*)); // 공통 선행 과목 배열 할당
    *common_count = 0; // 공통 선행 과목 수 초기화

    for (int i = 0; i < subject1->parent_count; i++) {
        for (int j = 0; j < subject2->parent_count; j++) {
            if (subject1->parents[i] == subject2->parents[j]) { // 공통 선행 과목 확인
                common_prereqs[(*common_count)++] = subject1->parents[i]; // 공통 선행 과목 배열에 추가
            }
        }
    }

    return common_prereqs; // 공통 선행 과목 배열 반환
}

// 일반적인 경로(시간 최적화 및 가장 기초)
// DFS를 이용해 subject1에서 subject2까지의 경로를 찾기
int find_path(Subject* current, Subject* target, Subject** path, int* path_index, int* visited, int visited_size) {
    if (current == target) { // 현재 과목이 목표 과목인 경우
        path[(*path_index)++] = current; // 경로 배열에 현재 과목 추가
        return 1; // 경로 찾음
    }

    // 현재 노드를 방문한 것으로 표시
    visited[current->id] = 1; // 현재 과목 방문 표시

    for (int i = 0; i < current->parent_count; i++) {
        Subject* parent = current->parents[i]; // 부모 과목 가져오기
        if (!visited[parent->id]) { // 부모 과목이 방문되지 않은 경우
            if (find_path(parent, target, path, path_index, visited, visited_size)) { // 재귀적으로 경로 찾기
                path[(*path_index)++] = current; // 경로 배열에 현재 과목 추가
                return 1; // 경로 찾음
            }
        }
    }
    return 0; // 경로를 찾지 못한 경우
}

// DFS를 이용해 subject1에서 subject2까지의 경로를 출력
void print_path(Subject* subject1, Subject* subject2) {
    int max_subjects = 100; // 임시로 설정한 최대 과목 수
    Subject** path = (Subject**)malloc(max_subjects * sizeof(Subject*)); // 경로 배열 할당
    int path_index = 0; // 경로 인덱스 초기화

    int visited_size = max_subjects; // 방문 배열 크기 설정
    int* visited = (int*)calloc(visited_size, sizeof(int)); // 방문 배열 초기화

    if (find_path(subject2, subject1, path, &path_index, visited, visited_size)) { // 경로 찾기
        printf("Path from %s to %s:\n", subject1->name, subject2->name); // 경로 시작 메시지 출력
        for (int i = 0; i <= path_index-1; i++) { // 경로 배열 역순으로 출력
            printf("%3d : %s (%s)\n", path[i]->id, path[i]->name, path[i]->tag); // 각 과목 출력
        }
    }
    else {
        printf("No path found from %s to %s.\n", subject1->name, subject2->name); // 경로를 찾지 못한 경우 메시지 출력
    }
    printf("\n");
    free(path);    // 경로 배열 메모리 해제
    free(visited); // 방문 배열 메모리 해제
}

// 가장 긴 경로(공부하는데 가장 수월함)
// 주어진 경로를 찾는 재귀 함수 (DFS 사용)
void find_longest_path(Subject* start, Subject* end, int* visited, Subject** path, int path_index, Subject** longest_path, int* longest_path_index) {
    visited[start->id] = 1; // 시작 노드를 방문한 것으로 표시
    path[path_index] = start; // 현재 경로에 시작 노드 추가
    path_index++; // 경로 인덱스 증가
    if (start == end) { // 시작 노드가 끝 노드와 동일한 경우
        if (path_index > *longest_path_index) { // 현재 경로가 가장 긴 경로보다 긴 경우
            *longest_path_index = path_index; // 가장 긴 경로 인덱스 갱신
            for (int i = 0; i < path_index; i++) {
                longest_path[i] = path[i]; // 가장 긴 경로 갱신
            }
        }
    }
    else {
        for (int i = 0; i < start->child_count; i++) { // 모든 자식 노드를 순회
            if (!visited[start->childs[i]->id]) { // 자식 노드를 방문하지 않은 경우
                find_longest_path(start->childs[i], end, visited, path, path_index, longest_path, longest_path_index); // 자식 노드에 대해 재귀 호출
            }
        }
    }

    path_index--; // 경로 인덱스 감소
    visited[start->id] = 0; // 시작 노드를 방문하지 않은 것으로 표시
}

// 두 노드 간의 가장 긴 경로를 출력하는 함수
void print_longest_path(Map* map, Subject* start, Subject* end) {
    int* visited = (int*)calloc(map->size+1, sizeof(int)); // 방문 배열 할당 및 초기화(+1은 ID가 1부터 시작해 크기를 넘지 않게 하기 위해 설정)
    Subject** path = (Subject**)malloc(map->size * sizeof(Subject*)); // 경로 배열 할당
    Subject** longest_path_result = (Subject**)malloc(map->size * sizeof(Subject*)); // 가장 긴 경로 배열 할당
    int path_index = 0; // 경로 인덱스 초기화
    int longest_path_index = 0; // 가장 긴 경로 인덱스 초기화

    find_longest_path(start, end, visited, path, path_index, longest_path_result, &longest_path_index); // 가장 긴 경로 찾기

    if (longest_path_index == 0) { // 경로를 찾지 못한 경우
        printf("No path found from %s to %s.\n", start->name, end->name);
    }
    else {
        printf("Longest path from %s to %s:\n", start->name, end->name); // 가장 긴 경로 출력
        for (int i = 0; i < longest_path_index; i++) {
            printf("%3d : %s (%s)\n", longest_path_result[i]->id, longest_path_result[i]->name, longest_path_result[i]->tag);
        }
    }
    printf("\n");
    free(visited); // 방문 배열 해제
    free(path); // 경로 배열 해제
    free(longest_path_result); // 가장 긴 경로 배열 해제
}

// 가장 짧은 경로(빠르게 공부하는데 효과적임)
// 두 노드 간의 최단 경로를 찾고 출력하는 함수 (BFS 사용)
void print_shortest_path(Map* map, Subject* start, Subject* end) {
    int* visited = (int*)calloc(map->size +1, sizeof(int)); // 방문 배열 할당 및 초기화 (+1은 위의 find_longest_path와 같은 이유)
    Subject** previous = (Subject**)malloc((map->size+1) * sizeof(Subject*)); // 이전 노드 배열 할당
    Queue* queue = create_queue(10); // 큐 생성

    enqueue(queue, start); // 시작 노드를 큐에 삽입
    visited[start->id] = 1; // 시작 노드를 방문한 것으로 표시
    previous[start->id] = NULL; // 시작 노드의 이전 노드는 없음

    while (!is_empty(queue)) { // 큐가 비어있지 않은 동안
        Subject* current = dequeue(queue); // 큐에서 현재 노드 가져오기

        if (current == end) { // 현재 노드가 끝 노드인 경우
            Subject** path = (Subject**)malloc(map->size * sizeof(Subject*)); // 경로 배열 할당
            int path_length = 0; // 경로 길이 초기화

            for (Subject* at = end; at != NULL; at = previous[at->id]) { // 끝 노드부터 시작 노드까지 경로 추적
                path[path_length++] = at;
            }

            printf("Shortest path from %s to %s:\n", start->name, end->name); // 최단 경로 출력
            for (int i = path_length - 1; i >= 0; i--) {
                printf("%3d : %s (%s)\n", path[i]->id, path[i]->name, path[i]->tag);
            }
            printf("\n");
            free(path); // 경로 배열 해제
            free(visited); // 방문 배열 해제
            free(previous); // 이전 노드 배열 해제
            free(queue->subjects); // 큐의 과목 배열 해제
            free(queue); // 큐 구조체 해제
            return;
        }

        for (int i = 0; i < current->child_count; i++) { // 현재 노드의 모든 자식 노드를 순회
            if (!visited[current->childs[i]->id]) { // 자식 노드를 방문하지 않은 경우
                enqueue(queue, current->childs[i]); // 자식 노드를 큐에 삽입
                visited[current->childs[i]->id] = 1; // 자식 노드를 방문한 것으로 표시
                previous[current->childs[i]->id] = current; // 자식 노드의 이전 노드를 현재 노드로 설정
            }
        }
    }

    printf("No path found from %s to %s.\n", start->name, end->name); // 경로를 찾지 못한 경우 출력
    printf("\n");
    free(visited); // 방문 배열 해제
    free(previous); // 이전 노드 배열 해제
    free(queue->subjects); // 큐의 과목 배열 해제
    free(queue); // 큐 구조체 해제
}

// 트리 구조를 만드는 함수
void create_tree(Subject* subject, int level, int is_last, int* parent_levels) {
    if (subject == NULL) { // subject가 NULL인 경우 반환
        return;
    }

    // 들여쓰기
    for (int i = 1; i < level; i++) {  // 현재 레벨까지 반복
        if (parent_levels[i]) {  // 부모 레벨이 존재하면
            printf("  │   ");  // '│' 출력
        }
        else {
            printf("      ");  // 아니면 공백 출력
        }
    }

    // 현재 과목 출력
    if (level > 0) {  // 루트 노드가 아닌 경우
        if (is_last) {  // 마지막 자식 노드인 경우
            printf("  └── ");  // '└──' 출력
        }
        else {
            printf("  ├── ");  // '├──' 출력
        }
    }
    printf("%3d: %s (%s)\n", subject->id, subject->name, subject->tag);  // 과목 정보 출력

    // 부모 레벨 설정
    parent_levels[level] = !is_last;  // 현재 레벨의 부모 상태 설정

    // 자식 과목들을 출력 (재귀적으로 호출)
    for (int i = 0; i < subject->child_count; i++) {  // 모든 자식 과목에 대해 반복
        create_tree(subject->childs[i], level + 1, i == subject->child_count - 1,  parent_levels);  // 자식 과목에 대해 재귀 호출
    }
}

// 전체 트리 구조를 출력하는 함수
void print_tree(Map* map) {
    printf("Subject Tree :\n"); // 트리 구조 시작 출력
    int parent_levels[100] = { 0 }; // parent_levels 배열 초기화
    for (int i = 0; i < map->size; i++) { // 모든 과목에 대해 반복
        if (map->subjects[i].parent_count == 0) { // 루트 노드인 경우
            create_tree(&(map->subjects[i]), 0, i == map->size - 1, parent_levels); // 트리 출력 함수 호출
            printf("\n"); // 루트 노드 사이에 빈 줄 추가
        }
    }
}

// 특정 태그를 가진 자식 과목이 있는지 확인하는 함수(tag_tree 출력을 위한 함수)
int has_tagged_child(Subject* subject, const char* filter_tag) {
    if (subject == NULL) { // subject가 NULL인 경우 반환
        return 0;
    }

    // 자신의 자식 과목들을 탐색
    for (int i = 0; i < subject->child_count; i++) {
        Subject* child = subject->childs[i];
        if (strcmp(child->tag, filter_tag) == 0) { // 자식 과목이 해당 태그를 가진 경우
            return 1; // 해당 태그를 가진 자식 과목이 있음
        }
        if (has_tagged_child(child, filter_tag)) { // 자식 과목의 자식들도 탐색
            return 1; // 자식 과목의 자식이 해당 태그를 가진 경우
        }
    }

    return 0; // 해당 태그를 가진 자식 과목이 없음
}

// 태그 트리 구조를 만드는 함수(특정 태그를 가진 모든 subject를 포함하는 최소의 tree 구조를 생성)
void create_tag_tree(Subject* subject, int level, int is_last, int* parent_levels, const char* filter_tag) {
    if (has_tagged_child(subject, filter_tag) || !strcmp(filter_tag, subject->tag)) { // subject의 n번째 하위과목에 filter_tag의 tag를 가진 subject가 있거나 지금 subject의 tag가 filter_tag임을 확인
        if (subject == NULL) { // subject가 NULL인 경우 반환
            return;
        }

        // 들여쓰기
        for (int i = 1; i < level; i++) {  // 현재 레벨까지 반복
            if (parent_levels[i]) {  // 부모 레벨이 존재하면
                printf("  │   ");  // '│' 출력
            }
            else {
                printf("      ");  // 아니면 공백 출력
            }
        }

        // 현재 과목 출력
        if (level > 0) {  // 루트 노드가 아닌 경우
            if (is_last) {  // 마지막 자식 노드인 경우
                printf("  └── ");  // '└──' 출력
            }
            else {
                printf("  ├── ");  // '├──' 출력
            }
        }
        printf("%3d: %s (%s)\n", subject->id, subject->name, subject->tag);  // 과목 정보 출력

        // 부모 레벨 설정
        parent_levels[level] = !is_last;  // 현재 레벨의 부모 상태 설정
    }
    // 자식 과목들을 출력 (재귀적으로 호출)
    for (int i = 0; i < subject->child_count; i++) {  // 모든 자식 과목에 대해 반복
        int child_tag_level = 2;
        if (has_tagged_child(subject->childs[i], filter_tag) || !strcmp(subject->childs[i]->tag, filter_tag)) {
            for (int j = i; j < subject->child_count; j++) {
                if (has_tagged_child(subject->childs[j], filter_tag) || !strcmp(subject->childs[j]->tag, filter_tag)) { // 뒤의 하위과목에 filter_tag를 가진 subject가 하나도 없는지 체크
                    child_tag_level--;
                    //printf("%s %d", subject->childs[j]->name, !strcmp(subject->childs[j]->tag, filter_tag));
                }
            }
            create_tag_tree(subject->childs[i], level + 1, child_tag_level >= 1, parent_levels, filter_tag);  // 자식 과목에 대해 재귀 호출
        }
    }
}

// 태그 트리 구조를 출력하는 함수
void print_tag_tree(Map* map, const char* filter_tag) {
    printf("%s Subject Tree :\n",filter_tag); // 트리 구조 시작 출력
    int parent_levels[100] = { 0 }; // parent_levels 배열 초기화
    for (int i = 0; i < map->size; i++) { // 모든 과목에 대해 반복
        if (map->subjects[i].parent_count == 0) { // 루트 노드인 경우
            int child_tag_level = 1;
            for (int j = 0; j < map->subjects[i].child_count; j++) {
                if (has_tagged_child(map->subjects[i].childs[j], filter_tag) || !strcmp(map->subjects[i].childs[j]->tag, filter_tag)) child_tag_level=0;
            }
            create_tag_tree(&(map->subjects[i]), 0, child_tag_level, parent_levels, filter_tag); // 트리 출력 함수 호출
            printf("\n"); // 루트 노드 사이에 빈 줄 추가
        }
    }
}

//후의 파일처리 시 원본 파일이 가지고 있을 오류를 해결하기 위한 함수들
// 사이클 감지 및 제거 함수 (트리의 변화를 최소화하며 사이클 제거)
void remove_cycle(Map* map) {
    for (int i = 0; i < map->size; i++) {
        if (check_cycle(&map->subjects[i])) {
            int min_child_count = map->subjects[i].child_count;
            int min_index = -1;

            // 가장 적은 자식 노드를 가진 부모를 찾음
            for (int j = 0; j < map->subjects[i].parent_count; j++) {
                if (map->subjects[i].parents[j]->child_count < min_child_count) {
                    min_child_count = map->subjects[i].parents[j]->child_count;
                    min_index = j;
                }
            }

            // 사이클을 제거
            if (min_index != -1) {
                remove_prereq(&map->subjects[i], map->subjects[i].parents[min_index]);
                printf("Removed cycle between %s and %s\n", map->subjects[i].name, map->subjects[i].parents[min_index]->name);
            }
        }
    }
}

// 선행 관계가 한 방향만 존재할 때를 위한 함수
void handle_inconsistent_prereq(Map* map) {
    for (int i = 0; i < map->size; i++) {
        Subject* subject = &map->subjects[i];

        // 각 과목의 자식 과목을 확인
        for (int j = 0; j < subject->child_count; j++) {
            Subject* child = subject->childs[j];
            int found = 0;

            // 자식 과목의 부모 리스트에서 현재 과목을 찾음
            for (int k = 0; k < child->parent_count; k++) {
                if (child->parents[k] == subject) {
                    found = 1;
                    break;
                }
            }

            // 현재 과목이 자식 과목의 부모 리스트에 없는 경우
            if (!found) {
                char choice;
                printf("Inconsistent prerequisite detected between %s and %s.\n", subject->name, child->name);
                printf("Would you like to add %s as a prerequisite to %s (A) or remove the existing relationship (R)? [A/R]: ", subject->name, child->name);
                scanf("%c", &choice);

                if (choice == 'A' || choice == 'a') {
                    // 자식 과목의 부모 리스트에 현재 과목을 추가
                    child->parent_count++;
                    child->parents = (Subject**)realloc(child->parents, child->parent_count * sizeof(Subject*));
                    child->parents[child->parent_count - 1] = subject;
                    printf("Added %s as a prerequisite to %s.\n", subject->name, child->name);
                }
                else if (choice == 'R' || choice == 'r') {
                    // 현재 과목의 자식 리스트에서 자식 과목을 제거
                    for (int k = 0; k < subject->child_count; k++) {
                        if (subject->childs[k] == child) {
                            for (int l = k; l < subject->child_count - 1; l++) {
                                subject->childs[l] = subject->childs[l + 1];
                            }
                            subject->child_count--;
                            subject->childs = (Subject**)realloc(subject->childs, subject->child_count * sizeof(Subject*));
                            break;
                        }
                    }
                    printf("Removed existing relationship between %s and %s.\n", subject->name, child->name);
                }
                else {
                    printf("Invalid choice. No changes made.\n");
                }
            }
        }
    }
}

// 중복 선행 과목 제거 함수(A-B-C-D A-D 구조)
void remove_redundant_prereqs(Map* map) {
    for (int i = 0; i < map->size; i++) { // 모든 과목에 대해 반복
        Subject* subject = &map->subjects[i]; // 현재 과목 설정
        for (int j = 0; j < subject->child_count; j++) { // 현재 과목의 모든 자식 과목에 대해 반복
            Subject* child = subject->childs[j]; // 현재 자식 과목 설정
            int* visited = (int*)calloc(map->size+1, sizeof(int)); // 방문 배열 할당 및 초기화(ID가 1부터 시작하므로 size+1로 배열 크기 설정)
            Subject** path = (Subject**)malloc(map->size * sizeof(Subject*)); // 경로 배열 할당
            int path_index = 0; // 경로 인덱스 초기화

            for (int k = 0; k < subject->child_count; k++) { // 현재 과목의 모든 자식 과목에 대해 반복
                if (k != j) { // 현재 자식 과목과 다른 자식 과목에 대해
                    path_index = 0; // 경로 인덱스 초기화
                    memset(visited, 0, (map->size +1) * sizeof(int)); // 방문 배열 초기화
                    if (find_path(child, subject->childs[k], path, &path_index, visited, map->size)) { // child에서 다른 자식 과목으로의 경로가 존재하는지 확인
                        // child가 다른 자식 노드를 통해 경로가 존재하면 현재 선행 관계를 제거
                        remove_prereq(child, subject);
                        //printf("Removed redundant prerequisite between %s and %s\n", subject->name, child->name); // 제거된 관계 출력(remove_prereq에서 출력)
                        break; // 루프 중단
                    }
                }
            }
            free(visited); // 방문 배열 해제
            free(path); // 경로 배열 해제
        }
    }
}
