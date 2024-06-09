#include "main.h"

enum STATE state = MAIN; // 실행 화면 결정 변수
Map subject_map = {NULL, 0}; // 과목 정보 저장할 Map 변수

int main(void)
{
    printf("\n\nHello! This is the ACADEMIC BLUEPRINT.\n");
    printf("We manage subjects and their hierarchy!\n\n");
    printf("Please keep in mind that user input should be in integer form.\n");
    while(1)
    {
        switch (state)
        {
            case MAIN: // main_screen() 호출
                main_screen(); break;
            case INPUT: // input_screen() 호출
                input_screen(); break;
            case INFO: // info_screen() 호출
                info_screen(); break;

            default:
                printf("ending program...\n");
                return 0;
        }
    }
}

/*
MAIN main_screen()
    INPUT input_screen()

    INFO info_screen() < select_screen() < search_screen(_) - select_interface(_)
        info_interface(_)
            > info_print(_)
            delete_subject(_) -> MAIN
            change_subject_screen(_) -> MAIN
                >info_print(_)
                change_name(_)
                change_tag(_)
                add_parent(_)
                add_child(_)
                delete_parent(_)
                delete_child(_)
                -> MAIN
            follow_screen(_)
                -> INFO
                    info_interface(select_in_array(_, _))
                    -> MAIN
    SAVELOAD
*/

// MAIN
void main_screen()
{
    printf("\nhi, this is the main screen.\n"); // main screen 안내
    printf("main screen menu:\n"); // menu 안내
    printf("\tinput subject: 0\n");
    printf("\tsearch subject: 1\n");
    printf("\tsave & load: 2\n");
    printf("\tend program: -1\n");
    printf("user input: ");
    int st=-1; // variable for menu select
    scanf("%d", &st);
    switch(st)
    {
        case 0: // input
            state = INPUT;
            break;
        case 1: // info
            state = INFO;
            break;
        case 2: // save & load
            state = SAVELOAD;
            break;
        case -1: // end program
            state = -1;
            break;
        default: // error
            printf("input ERROR. loading main screen again...\n");
            break;
    }
    return;
}

// MAIN > INPUT
void input_screen()
{
    printf("\nhi, this is the input screen.\n");
    printf("input screen menu:\n\tinput subject: 0\n\tgo back to main screen: else\n");
    printf("user input: ");
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


// MAIN > INFO
void info_screen() // screen
{
    Subject* subject = select_screen(); // subject to deliver to info_interface
    if(subject == NULL)
    {
        return;
    } // if error on selecting subject, select again (comes back by main while(1) loop)

    info_interface(subject); // calls info_interface()
    return;
} // use select_screen() which uses search_screen()
// calls info_interface()

void info_interface(Subject* subject) // called from info_screen(), follow_screen()
{
    info_print(subject);
    printf("\ninfo screen menu:\n");
    printf("\tdelete: 0\n\tchange: 1\n\tfollow: 2\n\tgo back to main screen: else\n");
    printf("user input: ");
    int st=-1; // variable for menu select
    scanf("%d", &st);
    switch(st)
    {
        case 0: // delete
            delete_subject(subject);
            if(subject->id!=-1 || strcmp(subject->name, "")!=0 || strcmp(subject->tag, "")!=0)
            {
                printf("ERROR. loading info screen again...\n");
                break;
            } // case of error
            printf("subject deleted. loading main screen...\n"); // succes
            state = MAIN; // back to main
            break;
        case 1: // change
            change_subject_screen(subject);
            if(state == INFO) // info succesfully changed
            {
                printf("changed info\n");
                info_print(subject);
            }
            state = MAIN; // back to main
            break;
        case 2: // follow
            follow_screen(subject);
            break;
        default: // back to main screen
            printf("loading main screen...\n");
            state = MAIN; // back to main
    }
    return;
}

void info_print(Subject* subject) // prints info of subject
{
    printf("\nsubject info:\n");
    printf("name: %s tag: %s\n", subject->name, subject->tag); // info
    print_subject_map(subject, 1); // 부모과목 print
    print_subject_hierarchy(subject, 0, 1); // 자식과목 print
}


// MAIN > INFO
// info_screen < select_screen() < search_screen()
Subject* select_screen()
{
    Subject** subject_array = search_screen(&subject_map); // calles search_screen()
    if(subject_array==NULL)
    {
        return NULL;
    } // returns NULL if search_screen() returns NULL

    int index=0;

    printf("\n");
    while(subject_array[index]!=NULL) // before NULL (마지막을 NULL로 표시하여 리턴함)
    {
        printf("index %d: ", index);
        printf("name: %s tag: %s\n", subject_array[index]->name, subject_array[index]->tag); // info
        print_subject_map(subject_array[index], 1); // 부모과목 print
        print_subject_hierarchy(subject_array[index], 0, 1); // 자식과목 print
        index++; // 다음 index로
    }

    if(index==0){
        printf("search ERROR.\n");
        state = MAIN; // MAIN으로
        return NULL;
    } // returns NULL if index is 0

    // printf("\nhi, this is the select screen.\n");
    int sel_index = select_interface(index); // select_interface()를 호출하여 index select

    printf("%s selected.\n", subject_array[sel_index]->name);
    state = INFO; // INFO로
    return subject_array[sel_index]; // 선택한 subject 리턴
} // > used in info_screen

// MAIN > INFO
// info_screen < select_screen() < search_screen()
Subject** search_screen(Map* map)
{
    Map s_map = *map; // search screen의 map
    int s_size = s_map.size; // search screen의 map size
    Subject *s_subjects = s_map.subjects; // search screen의 subjects 배열

    // printf("\nhi, this is the search screen.\n");
    printf("search screen menu:\n\tsearch subject: 0\n\tgo back to main screen: else\n");
    printf("user input: ");
    int st=-1; // select screen
    scanf("%d", &st);
    if(st!=0) // back to main
    {
        state = MAIN;
        return NULL;
    }

    Subject **pointers = (Subject **) malloc(sizeof(Subject *)); // 찾은 Subject 주소 저장을 위한 동적할당 배열
    int searched_size=0; // 동적할당을 위한 크기 변수
    printf("word to search? "); // search by name
    char word[50]; // 입력을 위한 변수
    scanf("%s", word);
    for(int i=0; i<s_size; i++) // map size까지 탐색
    {
        if(strstr(s_subjects[i].name, word) != NULL) // 포함된다면
        {
            pointers[searched_size]=&(s_subjects[i]); // 배열에 주소 저장
            searched_size++; // 크기 증가
            pointers = (Subject **) realloc(pointers, (searched_size+1) * sizeof(Subject *)); // 메모리 추가 할당
        }
    }
    pointers[searched_size]=NULL; // 마지막에 NULL 저장 (끝 표시 위함)
    
    return pointers;
} // search -> select -> INFO
// > used in select_screen

int select_interface(int index) // index 선택을 위한 함수
{
    printf("\nselect index. (range %d to %d) ", 0, index-1);
    int sel_index=-1; // select index
    scanf("%d", &sel_index);

    if(sel_index>=index || sel_index<0) // 입력 오류 시
    {
        printf("ERROR. select again.\n");
        select_interface(index); // 다시 호출
    }

    return sel_index;
} // RETURNS THE ID


// interface of INFO
void delete_subject(Subject *subject)
{
    subject->id=-1;
    strcpy(subject->name, "");
    strcpy(subject->tag, "");
    for(int i=0; i<(subject->parent_count); i++)
    {
        remove_prereq((subject->parents)[i], subject);
    }
    for(int i=0; i<(subject->child_count); i++)
    {
        remove_prereq(subject, (subject->childs)[i]);
    }
    return;
}

void change_subject_screen(Subject* subject)
{
    printf("\nhi, this is the change subject screen.\n");
    printf("change subject screen menu:\n\tchange name: 0\n\tchange tag: 1\n\tadd parents: 2\n\tadd childs: 3\n\tchange parents: 4\n\tchange childs: 5\n\tgo back to main screen: else\n");
    printf("user input: ");
    int st=-1; // menu select
    scanf("%d", &st);

    switch(st)
    {
        case 0: // change name
            change_name(subject);
            printf("name changed to %s\n", subject->name);
            break;
        case 1: // change tag
            change_tag(subject);
            printf("tag changed to %s\n", subject->tag);
            break;
        case 2: // add parents
            add_parent(subject);
            break;
        case 3: // add childs
            add_child(subject);
            break;
        case 4: // delete parent
            delete_parent(subject);
            break;
        case 5: // delete child
            delete_child(subject);
            break;
        default: // input error
            printf("loading main screen...");
            state = MAIN;
    }
    return;
} // changes info or parents


void follow_screen(Subject* subject)
{
    printf("\nhi, this is the follow screen.\n");
    printf("follow screen menu:\n\tfollow parent: 0\n\tfollow child: 1\n\tgo back to main screen: else\n");
    int st=-1; // menu select
    printf("user input: ");
    scanf("%d", &st);

    switch(st)
    {
        case 0: // follow parent
            state = INFO;
            if((subject->parent_count)<=0) // no parent to follow
            {
                printf("No parent to follow\n");
                state = MAIN; // to main
                break;
            }
            info_interface(select_in_array(subject->parents, subject->parent_count));
            break;
        case 1: // follow child
            state = INFO;
            if((subject->child_count)<=0) // no child to follow
            {
                printf("No child to follow\n");
                state = MAIN; // to main
                break;
            }
            info_interface(select_in_array(subject->childs, subject->child_count)); // info_interface에 select_in_array()를 이용하여 선택한 과목 전달하여 호출
            break;
        default: // go back to main screen
            printf("loading main screen...\n");
            state = MAIN; // to main
    }
    return;
}


void change_name(Subject* subject) // change subject name
{
    char name[50]; // for input
    printf("\nnew name for subject %s? ", subject->name);
    scanf("%s", name);
    strcpy(subject->name, name); // change
    return;
}

void change_tag(Subject* subject) // change subject tag
{
    char tag[50]; // for input
    printf("\nnew tag for subject %s?(existing tag %s) ", subject->name, subject->tag);
    scanf("%s", tag);
    strcpy(subject->tag, tag); // change
    return;
}

void add_parent(Subject* subject) // add parent in subject
{
    Subject* subject_add = select_screen(); // selct subject
    if(subject_add == NULL)
    {
        return;
    } // if error in select

    add_prereq(subject_add, subject); // add parent
    return;
}

void add_child(Subject* subject) // add child in subject
{
    Subject* subject_add = select_screen(); // select subject
    if(subject_add == NULL)
    {
        return;
    } // if error in select

    add_prereq(subject, subject_add); // add child
    return;
}

void delete_parent(Subject* subject) // delete parent
{
    Subject* subject_delete = select_in_array(subject->parents, subject->parent_count); // select parent subject to delete
    if(subject_delete == NULL)
    {
        return;
    } // if error in select

    remove_prereq(subject_delete, subject); // delete parent
    return;
}

void delete_child(Subject* subject) // delete child
{
    Subject* subject_delete = select_in_array(subject->parents, subject->parent_count); // select child subject to delete
    if(subject_delete == NULL)
    {
        return;
    } // if error in select

    remove_prereq(subject, subject_delete); // delete child
    return;
}

Subject* select_in_array(Subject** subject_array, int count) // selecting subject in array
{
    int index=0; // index for printing subject in subject_array

    printf("\n");
    while(index<count) // printing
    {
        printf("index %d: ", index);
        printf("name: %s tag: %s\n", subject_array[index]->name, subject_array[index]->tag);
        index++;
    }

    int sel_index = select_interface(index); // select index
    printf("%s selected.\n", subject_array[sel_index]->name);

    return subject_array[sel_index]; // 선택된 subject 주소 리턴
}

