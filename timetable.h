#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <stdlib.h>
#include <string.h>
#include "subject.h"

// typedef struct timetable 
// {
//     Map semesters[NUM_SEMESTERS];
// } Timetable;

Timetable* create_timetable();

void append_to_timetable(Timetable* timetable, Subject* subject, int semester);

void remove_from_timetable(Timetable* timetable, Subject* subject, int semester);

void free_timetable(Timetable* timetable);

void print_subjects_in_semester(Timetable* timetable, int semester);

int is_valid(int type1, Subject** subject); // Check if the timetable is valid(return 0) if not(return all error semesters(ex 2345))
int exceed_subjects(Timetable* timetable); //check if the timetable exceed the maximum number of subjects each semester(return 0) if not (return all exceeding semesters(ex 125))
Subject** possible_semester(Timetable* timetable); // check if all subjects are possible to register at that semester(return None) if not (return the array of impossible subjects)


#endif
