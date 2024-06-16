#include "timetable.h"

// typedef struct timetable 
// {
//     Map semesters[NUM_SEMESTERS];
// } Timetable;

Timetable* create_timetable()
{
    Timetable* timetable = (Timetable*)malloc(sizeof(Timetable));

    for (int i = 0; i < NUM_SEMESTERS; i++)
    {
        timetable->semesters[i].subjects = NULL;
        timetable->semesters[i].size = 0;
    }
    return timetable;
}

void append_to_timetable(Timetable* timetable, Subject* subject, int semester)
{
    // append the subject to the end of the subjects array
    timetable->semesters[semester].size++;
    timetable->semesters[semester].subjects = (Subject*)realloc(timetable->semesters[semester].subjects, 
                                                                sizeof(Subject) * timetable->semesters[semester].size);

    // increase the size of the subjects array
    timetable->semesters[semester].subjects[timetable->semesters[semester].size - 1] = *subject;
}

void remove_from_timetable(Timetable* timetable, Subject* subject, int semester)
{
    // if (semester < 0 || semester >= NUM_SEMESTERS)
    // {
    //     printf("Invalid semester\n");
    //     return;
    // }

    // search for the subject in the subjects array
    for (int i = 0; i < timetable->semesters[semester].size; i++)
    {
        if (&(timetable->semesters[semester].subjects[i]) == subject)
        {
            // remove the subject by shifting the subsequent subjects
            for (int j = i; j < timetable->semesters[semester].size - 1; j++)
            {
                timetable->semesters[semester].subjects[j] = timetable->semesters[semester].subjects[j + 1];
            }
            // decrease the size of the subjects array
            timetable->semesters[semester].size--;
            timetable->semesters[semester].subjects = (Subject*)realloc(timetable->semesters[semester].subjects, 
                                                                        sizeof(Subject) * timetable->semesters[semester].size);
            return;
        }
    }
}

void free_timetable(Timetable* timetable)
{
    // free the subjects arrays
    for (int i = 0; i < NUM_SEMESTERS; i++)
    {
        free(timetable->semesters[i].subjects);
    }
    free(timetable);
}

// prints subjects corresponding to the entered semester
void print_subjects_in_semester(Timetable* timetable, int semester) 
{
    int a = (semester + 2) / 2;
    int b = 2 - (semester + 1) % 2;
    printf("Subjects in %d-%d: \n", a, b);
    int tmp = 0;
    for (int i = 0; i < timetable->semesters[semester].size; i++) {
        if (strcmp(timetable->semesters[semester].subjects[i].name, "") != 0)
        {
            printf("%s\n", timetable->semesters[semester].subjects[i].name);
            tmp = 1;
        }
    }

    if (tmp == 0)
    {
        printf("\n");
    }
}