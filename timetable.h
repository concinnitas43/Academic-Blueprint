#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "subject.h"

Timetable* create_timetable();
void append_to_timetable(Timetable* timetable, Subject* subject, int semester); // Implement using malloc
void remove_from_timetable(Timetable* timetable, Subject* subject, int semester); // Implement using free
void free_timetable(Timetable* timetable);


#endif