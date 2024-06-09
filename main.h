#ifndef MAIN_H
#define MAIN_H

#define MAX_SUBJECTS 100
#define MAX_CHILDREN 100
#define MAX_PARENTS 100

enum STATE {MAIN, INPUT, INFO, SAVELOAD};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "subject.h"
#include "timetable.h"
#include "prereq.h"

// RELATED TO MAIN
void main_screen();
// RELATED TO INPUT
void input_screen(); // use create_subject, append_subject
// RELATED TO SEARCH
Subject** search_screen(Map* map); // SEARCH -> SELECT -> INFO
// > select_screen
int select_interface(int index); // RETURNS THE ID

// RELATED TO SELECT
Subject* select_screen();
// > info_screen
Subject* select_in_array(Subject** subject_array, int count); // used to delete parent, child

// RELATED TO INFO
void info_screen(); // use delete, change, follow
void info_print(Subject* subject);
void info_interface(Subject* subject);

// interface of INFO
void delete_subject(Subject *subject);
// void free_subject(Subject* subject); (in // Subjects)
void change_subject_screen(Subject* subject); // changes info or parents

void change_name(Subject* subject);
void change_tag(Subject* subject);
void add_parent(Subject* subject);
void add_child(Subject* subject);
void delete_parent(Subject* subject);
void delete_child(Subject* subject);

void follow_screen(Subject* subject);

// RELATED TO SAVELOAD AND SETTINGS
void saveload_screen(); // SAVEs and LOADs file

#endif