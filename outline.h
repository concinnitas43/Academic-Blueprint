enum STATE {MAIN, INPUT, SEARCH, SELECT, INFO, SAVELOAD};

typedef struct subject
{
    char name[50];
    char tag[50];
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

Subject* create_subject(char* name, int id); 
void append_subject(Map* map, Subject* subject); 
void free_subject(Subject* subject);
void free_map(Map* map);
void append_to_timetable(Timetable* timetable, Subject* subject, int semester); 
void remove_from_timetable(Timetable* timetable, Subject* subject, int semester); 
void free_timetable(Timetable* timetable);

void print_map(Map* map, int depth); 
void delete_node(Subject* subject, Map* map); 

int name_search(char* name, Map* map, int * search_result); 

int check_cycle(Subject* parent, Subject* child); 
int add_prereq(Subject* parent, Subject* child); 
int remove_prereq(Subject* parent, Subject* child); 

void load_map(Map* map, char* filename);
void save_map(Map* map, char* filename);

int is_valid(int type1, Subject** subject);  // timetable 입력 안받아도 됨??
int exceed_subjects(Timetable* timetable); 
Subject** possible_semester(Timetable* timetable);  // 나중에 free 어떻게 할거임??
// RELATED TO MAIN
void main_screen();

// RELATED TO INPUT
void input_screen(); 

// RELATED TO SEARCH
Subject** search_screen();  // 왜 Subject**로 반환??
// > select_screen
char* search_interface();
int select_interface(char* search); 

// RELATED TO SELECT
Subject* select_screen(Subject** subject_array);
// > info_screen

// RELATED TO INFO
void info_screen(Subject* subject); 
void add_prereq_interface(Subject* child); 
void delete_prereq_interface(Subject* child); 
void add_to_timetable(Subject* subject, Timetable* timetable, int semester); 

// interface of INFO
// void free_subject(Subject* subject); (in // Subjects)
void change_subject_interface(Subject* subject); 
Subject** follow_parent_screen(Subject* subject); 
Subject** follow_child_screen(Subject* subject); 

// RELATED TO SAVELOAD AND SETTINGS
void saveload_screen(); 
