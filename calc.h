#ifndef MY_CALC
#define MY_CALC

typedef struct{
    int baseline_A;
    int baseline_B;
    int baseline_C;
    int baseline_D;
    int baseline_F;
}gradeMapping;

typedef struct {
    long id;
    char firstName[30];
    char lastName[30];
    int a1;
    int a2;
    int a3;
    int midterm;
    int final;
}student;

void display_menu(int student_count, student* students, gradeMapping gradeMapping);
int menu_operations(int userSelection, int student_count, student* students, gradeMapping gradeMapping);
void proceed(int student_count, student* students, gradeMapping gradeMapping);
float calculate_total(student student);
char calculate_grade(float total, gradeMapping gradeMapping);
void display_spreadsheet(int student_count, student *students, gradeMapping gradeMapping);
void create_histogram(int student_count, student *students, gradeMapping gradeMapping);
void sorting_menu(int student_count, student* students);
void change_last_name(int student_count, student* students, gradeMapping gradeMapping);
void update_exam(int student_count, student* students, gradeMapping gradeMapping);
gradeMapping change_grade_mapping(int student_count, student* students, gradeMapping gradeMapping);
student* delete_student(int student_count, student* students, gradeMapping gradeMapping);

#endif /*MY_ORDER*/