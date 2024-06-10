#ifndef MAIN_H
#define MAIN_H

#define MAX_SUBJECTS 100
#define MAX_CHILDREN 100
#define MAX_PARENTS 100

enum STATE {MAIN, INPUT, INFO, SAVELOAD, TIMETABLE};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subject.h"
#include "timetable.h"
#include "prereq.h"

// MAIN
void main_screen();
// MAIN > INPUT
void input_screen(); // use create_subject, append_subject

// > info_screen
Subject* select_in_array(Subject** subject_array, int count); // used to delete parent, child

// MAIN > INFO
// info_screen < select_screen() < search_screen()
void info_screen(); // use delete, change, follow
Subject* select_screen();
Subject** search_screen(Map* map);

void info_print(Subject* subject);
void info_interface(Subject* subject);
int select_interface(int index); // RETURNS THE ID

void delete_subject(Subject *subject);
// void free_subject(Subject* subject); (in // Subjects)
void change_subject_screen(Subject* subject); // changes info or parents

void change_name(Subject* subject); // change subject name
void change_tag(Subject* subject); // change subject tag
void add_parent(Subject* subject); // add parent in subject
void add_child(Subject* subject); // add child in subject
void delete_parent(Subject* subject); // delete parent
void delete_child(Subject* subject); // delete child

void follow_screen(Subject* subject);

// RELATED TO SAVELOAD AND SETTINGS
void saveload_screen(); // SAVEs and LOADs file

void timetable_screen();

#endif