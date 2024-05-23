enum STATE {MAIN, INPUT, SEARCH, SELECT, INFO, SAVELOAD};

typedef struct subject
{
    char name[50];
    int id;
    Subject** childs;
    int child_count;
    Subject** parents;
    int parent_count;
} Subject;

typedef struct map
{
    Subject* subjects;
    int size;
} Map;

typedef struct timetable
{
    Subject* semesters[6];
} Timetable;

// Subjects

Subject* create_subject(char* name, int id); // Implement using malloc
void append_subject(Map* map, Subject* subject); // Implement using realloc
void free_subject(Subject* subject);
void free_map(Map* map);
void append_to_timetable(Timetable* timetable, Subject* subject, int semester); // Implement using malloc
void remove_from_timetable(Timetable* timetable, Subject* subject, int semester); // Implement using free
void free_timetable(Timetable* timetable);

void print_map(Map* map, int depth); // depth is needed for recursion
void delete_node(Subject* subject, Map* map); // Need to Free!

int name_search(char* name, Map* map, int * search_result); //Returns the number of search results, might need another function to define this one recursively

int check_cycle(Subject* parent, Subject* child); // Parent, Child를 서로 연결을 했을 때 Returns 1 if there is a cycle, 0 if not
int add_prereq(Subject* parent, Subject* child); // add them both ways (return 0), if already exists (return 1), do nothing. if there is a cycle, return 2
int remove_prereq(Subject* parent, Subject* child); // remove them both ways, if not exists, do nothing

void load_map(Map* map, char* filename);
void save_map(Map* map, char* filename);

int is_valid(Timetable* timetable); // Check if the timetable is valid


// RELATED TO MAIN
int main_screen();

// RELATED TO INPUT
int input_screen(); // use create_subject, append_subject

// RELATED TO SEARCH
int search_screen(); // SEARCH -> SELECT -> INFO
char* search_interface();
int select_interface(char* search); // RETURNS THE ID

// RELATED TO INFO
int info_screen(Subject* subject);
void add_prereq_interface(Subject* child); // select parent using search & select interface, then add prereq
void delete_prereq_interface(Subject* child); // select parent using search & select interface, then delete prereq
void add_to_timetable(Subject* subject, Timetable* timetable, int semester); // add to timetable

// RELATED TO SAVELOAD AND SETTINGS
int saveload_screen();