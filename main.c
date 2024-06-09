#include "main.h"

enum STATE state = MAIN; // 실행 화면 결정 변수
Map subject_map = {NULL, 0}; // 과목 정보 저장할 Map 변수

int main(void)
{
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


// RELATED TO SELECT
Subject* select_screen()
{
    Subject** subject_array = search_screen(&subject_map);
    if(subject_array==NULL)
    {
        return NULL;
    }

    int index=0;

    printf("\n");
    while(subject_array[index]!=NULL)
    {
        printf("index %d: ", index);
        printf("name: %s tag: %s\n", subject_array[index]->name, subject_array[index]->tag);
        index++;
    }

    if(index==0){
        printf("search ERROR.\n");
        state = MAIN;
        return NULL;
    }

    printf("\nhi, this is the select screen.\n");
    int sel_index = select_interface(index);

    printf("%s selected.\n", subject_array[sel_index]->name);
    state = INFO;
    return subject_array[sel_index];
}
// > used in info_screen

// RELATED TO SEARCH
Subject** search_screen(Map* map)
{
    Map s_map = *map; // search screen의 map
    int s_size = s_map.size; // search screen의 map size
    Subject *s_subjects = s_map.subjects; // search screen의 subjects 배열

    printf("\nhi, this is the search screen.\n");
    printf("search screen menu:\n\tsearch subject: 0\n\tgo back to main screen: else\n");
    printf("user input: ");
    int st=-1; // select screen
    scanf("%d", &st);
    if(st!=0) // back to main
    {
        state = MAIN;
        return NULL;
    }

    Subject **pointers = (Subject **) malloc(sizeof(Subject *));
    int searched_size=0;
    printf("word to search? "); // search by name (tag 할수도)
    char word[50];
    scanf("%s", word);
    for(int i=0; i<s_size; i++)
    {
        if(strstr(s_subjects[i].name, word) != NULL)
        {
            pointers[searched_size]=&(s_subjects[i]);
            searched_size++;
            pointers = (Subject **) realloc(pointers, (searched_size+1) * sizeof(Subject *));
        }
    }
    pointers[searched_size]=NULL;
    
    return pointers;
} // search -> select -> INFO
// > used in select_screen

int select_interface(int index)
{
    printf("\nselect index. (range %d to %d) ", 0, index-1);
    int sel_index=-1; // select index
    scanf("%d", &sel_index);

    if(sel_index>=index || sel_index<0)
    {
        printf("ERROR. select again.\n");
        select_interface(index);
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

// void free_subject(Subject* subject); (in // Subjects)
void change_subject_screen(Subject* subject)
{
    printf("\nhi, this is the change subject screen.\n");
    printf("change subject screen menu:\n\tchange name: 0\n\tchange tag: 1\n\tadd parents: 2\n\tadd childs: 3\n\tchange parents: 4\n\tchange childs: 5\n\tgo back to main screen: else\n");
    printf("user input: ");
    int st=-1;
    scanf("%d", &st);

    switch(st)
    {
        case 0:
            change_name(subject);
            printf("name changed to %s\n", subject->name);
            break;
        case 1:
            change_tag(subject);
            printf("tag changed to %s\n", subject->tag);
            break;
        case 2:
            add_parent(subject);
            break;
        case 3:
            add_child(subject);
            break;
        case 4:
            delete_parent(subject);
            break;
        case 5:
            delete_child(subject);
            break;
        default:
            printf("loading main screen...");
            state = MAIN;
    }
    return;
} // changes info or parents


void follow_screen(Subject* subject)
{
    printf("\nhi, this is the follow screen.\n");
    printf("follow screen menu:\n\tfollow parent: 0\n\tfollow child: 1\n\tgo back to main screen: else\n");
    int st=-1;
    printf("user input: ");
    scanf("%d", &st);

    switch(st)
    {
        case 0:
            state = INFO;
            if((subject->parent_count)<=0)
            {
                printf("No parent to follow\n");
                state = MAIN;
                break;
            }
            info_interface(select_in_array(subject->parents, subject->parent_count));
            break;
        case 1:
            state = INFO;
            if((subject->child_count)<=0)
            {
                printf("No child to follow\n");
                state = MAIN;
                break;
            }
            info_interface(select_in_array(subject->childs, subject->child_count));
            break;
        default:
            printf("loading main screen...\n");
            state = MAIN;
    }
    return;
}


void change_name(Subject* subject)
{
    char name[50];
    printf("\nnew name for subject %s? ", subject->name);
    scanf("%s", name);
    strcpy(subject->name, name);
    return;
}

void change_tag(Subject* subject)
{
    char tag[50];
    printf("\nnew tag for subject %s?(existing tag %s) ", subject->name, subject->tag);
    scanf("%s", tag);
    strcpy(subject->tag, tag);
    return;
}

void add_parent(Subject* subject)
{
    Subject* subject_add = select_screen();
    if(subject_add == NULL)
    {
        return;
    }

    add_prereq(subject_add, subject);
    return;
}

void add_child(Subject* subject)
{
    Subject* subject_add = select_screen();
    if(subject_add == NULL)
    {
        return;
    }

    add_prereq(subject, subject_add);
    return;
}

void delete_parent(Subject* subject)
{
    Subject* subject_delete = select_in_array(subject->parents, subject->parent_count);
    if(subject_delete == NULL)
    {
        return;
    }

    remove_prereq(subject_delete, subject);
    return;
}

void delete_child(Subject* subject)
{
    Subject* subject_delete = select_in_array(subject->parents, subject->parent_count);
    if(subject_delete == NULL)
    {
        return;
    }

    remove_prereq(subject, subject_delete);
    return;
}

Subject* select_in_array(Subject** subject_array, int count)
{
    int index=0;

    printf("\n");
    while(index<count)
    {
        printf("index %d: ", index);
        printf("name: %s tag: %s\n", subject_array[index]->name, subject_array[index]->tag);
        index++;
    }

    int sel_index = select_interface(index);
    printf("%s selected.\n", subject_array[sel_index]->name);

    return subject_array[sel_index];
}

