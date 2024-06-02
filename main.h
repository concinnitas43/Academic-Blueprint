enum STATE {MAIN, INPUT, INFO, SAVELOAD};

typedef struct subject
{
    char name[50]; // 삭제되면 ""
    char tag[50]; // 삭제되면 ""
    int id; // subject_map의 subjects 배열 index와 일치, 삭제되면 -1
    struct subject ** parents;
    int parent_count;
    struct subject ** childs;
    int child_count;
} Subject;

typedef struct map
{
    Subject* subjects; // subjects가 
    int size; // 1개가 1개 (index는 -1 해아함)
} Map;

typedef struct timetable
{
    Subject* semesters[6];
} Timetable;

// Subjects

Subject* create_subject(char* name, char* tag, int id); // Implement using malloc
void append_subject(Map* map, Subject* subject); // Implement using realloc
// > 함수 안에서 map.size ++; 해줘야함
// void free_subject(Subject* subject);
void free_map(Map* map);
void append_to_timetable(Timetable* timetable, Subject* subject, int semester); // Implement using malloc
void remove_from_timetable(Timetable* timetable, Subject* subject, int semester); // Implement using free
void free_timetable(Timetable* timetable);

void print_map(Map* map); // depth is needed for recursion
void print_subject_map(Subject* subject, int depth); // subject 내의 Subject ** parents, childs 이용하여 재귀적으로?
// void delete_node(Subject* subject, Map* map); // Need to Free!

int name_search(char* name, Map* map, int * search_result); //Returns the number of search results, might need another function to define this one recursively

int check_cycle(Subject* subject); // after connect Parent subject with Child subject, Returns 1 if there is a cycle start with parent subject, 0 if not(by dfs)
int add_prereq(Subject* parent, Subject* child); // add them both ways (return 0), if already exists (return 1), do nothing. if there is a cycle, return 2
int remove_prereq(Subject* parent, Subject* child); // remove them both ways(return 0), if not exists(return -1), do nothing

void load_map(Map* map, char* filename);
void save_map(Map* map, char* filename);

int is_valid(int type1, Subject** subject); // Check if the timetable is valid(return 0) if not(return all error semesters(ex 2345))
int exceed_subjects(Timetable* timetable); //check if the timetable exceed the maximum number of subjects each semester(return 0) if not (return all exceeding semesters(ex 125))
Subject** possible_semester(Timetable* timetable); // check if all subjects are possible to register at that semester(return None) if not (return the array of impossible subjects)


// *****************

// RELATED TO MAIN
void main_screen();

// RELATED TO INPUT
void input_screen(); // use create_subject, append_subject

// RELATED TO SEARCH
Subject** search_screen(Map* map); // SEARCH -> SELECT -> INFO
// > select_screen
// char* search_interface();
int select_interface(int index); // RETURNS THE ID

// RELATED TO SELECT
Subject* select_screen();
// > info_screen
Subject* select_in_array(Subject** subject_array, int count); // used to delete parent, child

// RELATED TO INFO
void info_screen(); // use delete, change, follow
// void add_prereq_interface(Subject* child); // select parent using search & select interface, then add prereq
// void delete_prereq_interface(Subject* child); // select parent using search & select interface, then delete prereq

void info_print(Subject* subject);
void info_interface(Subject* subject);

// >> add_parent, child / delete_parent, child 로 구현

void add_to_timetable(Subject* subject, Timetable* timetable, int semester); // add to timetable

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
// Subject** follow_parent_screen(Subject* subject); // return array of parent pointer to SELECT
// Subject** follow_child_screen(Subject* subject); // return array of child pointer to SELECT

// RELATED TO SAVELOAD AND SETTINGS
void saveload_screen(); // SAVEs and LOADs file
