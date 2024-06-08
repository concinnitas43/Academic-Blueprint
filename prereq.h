#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "subject.h"


int check_cycle(Subject* subject); // after connect Parent subject with Child subject, Returns 1 if there is a cycle start with parent subject, 0 if not(by dfs)
int add_prereq(Subject* parent, Subject* child); // add them both ways (return 0), if already exists (return 1), do nothing. if there is a cycle, return 2
int remove_prereq(Subject* parent, Subject* child); // remove them both ways(return 0), if not exists(return -1), do nothing
