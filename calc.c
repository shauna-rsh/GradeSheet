/*the code used to carry out the logic of the menu options – this will definitely be the biggest file*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calc.h"
#include "data.h"
#include "ordering.h"

//Constants

//Prototypes
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

//Functions

void display_menu(int student_count, student* students, gradeMapping gradeMapping) {
    system("clear");
    int userSelection;
    printf("Spreadsheet menu \n");
    printf("---------------- \n");
    printf("1. Display Spreadsheet \n");
    printf("2. Display Histogram \n");
    printf("3. Set sort column\n");
    printf("4. Update Last Name \n");
    printf("5. Update Exam Grade\n");
    printf("6. Update Grade Mapping \n");
    printf("7. Delete Student \n");
    printf("8. Exit \n");
    printf("Selection: ");
    scanf("%d", &userSelection);
    menu_operations(userSelection, student_count, students, gradeMapping);
}

int menu_operations(int userSelection, int student_count, student* students, gradeMapping gradeMapping){
    switch (userSelection){
        case 1: //Display Spreadsheet
            display_spreadsheet(student_count, students, gradeMapping);
            proceed(student_count, students, gradeMapping);
            break;
        case 2: //grade distribution
            create_histogram(student_count, students, gradeMapping);
            proceed(student_count, students, gradeMapping);
            break;
        
        case 3: // sorting
            sorting_menu(student_count, students);
            proceed(student_count, students, gradeMapping);
            break;
       case 4: // change last name
            change_last_name(student_count, students, gradeMapping);
            proceed(student_count, students, gradeMapping);
            break;
         case 5: // change exam grade
            update_exam(student_count,students,gradeMapping);
            proceed(student_count,students,gradeMapping);
            break;
        case 6: // change grade mapping
            proceed(student_count, students, change_grade_mapping(student_count,students,gradeMapping));
            break;
        case 7: //remove student
            proceed((student_count-1), delete_student(student_count, students,gradeMapping), gradeMapping);
            break;
       case 8: // exit
            printf("Goodbye and thanks for using our spreadsheet app");
            break;
        default:
            printf("Goodbye and thanks for using our spreadsheet app");
    }
    return 0;
}

void proceed(int student_count, student* students, gradeMapping gradeMapping){
    char proceed;
    printf("\nPress 'c' or 'C' to continue ");
    do{
        scanf("%c", &proceed);
    } while ( (proceed != 'c') && (proceed != 'C'));

    display_menu(student_count, students, gradeMapping);

}

float calculate_total(student student){
    float total;
    float assignments_percent = (float)(student.a1 + student.a2 + student.a3)/120;
    float midterm_percent= (float)student.midterm/25; 
    float final_percent = (float)student.final/40;

    total = (25.00*assignments_percent)+(25.00*midterm_percent)+(50.00*final_percent);
    return total;
}

char calculate_grade(float total, gradeMapping gradeMapping){
    char grade;
    if(total>=gradeMapping.baseline_A) grade='A';
    else if(total>=gradeMapping.baseline_B) grade='B';
    else if(total>=gradeMapping.baseline_C) grade='C';
    else if(total>=gradeMapping.baseline_D) grade='D';
    else if(total<gradeMapping.baseline_F) grade='F';
    return grade;
}

void display_spreadsheet(int student_count, student *students, gradeMapping gradeMapping){
    printf("COMP348 GRADE SHEET\n");
    printf("ID\tLast\t\t\tFirst\t\t\tA1\tA2\tA3\tMidterm\t\tExam\t\tTotal\t\tGrade\n");
    printf("---\t----\t\t\t-----\t\t\t--\t--\t--\t-------\t\t----\t\t-----\t\t-----\n");
    for (int i = 0; i < student_count; i++) {
        float total = calculate_total(students[i]);
        printf("%ld\t", students[i].id);
        printf("%s\t\t\t%s\t\t\t", students[i].lastName, students[i].firstName);
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%.2f\t\t%c\n",
               students[i].a1, students[i].a2, students[i].a3,students[i].midterm, students[i].final, total, calculate_grade(total, gradeMapping));
    }

}

void create_histogram(int student_count, student *students, gradeMapping gradeMapping){
    printf("\n\nCOMP 348 GRADE DISTRIBUTION\n");
    int number_of_a = 0;
    int number_of_b= 0;
    int number_of_c= 0;
    int number_of_d= 0;
    int number_of_f= 0;
    char grade;
    
    for (int i = 0; i < student_count; i++) {
        grade = calculate_grade(calculate_total(students[i]),gradeMapping);
        switch(grade){
            case 'A':
                number_of_a++;
                break;
            case 'B':
                number_of_b++;
                break;
            case 'C':
                number_of_c++;
                break;
            case 'D':
                number_of_d++;
                break;
            case 'F':
                number_of_f++;
                break;
            default:
                printf("Grades seem incorrect...");
        }
    }

    printf("\nA: ");
    for(int i = 0;i<number_of_a;i++){
        printf("* ");
    }
    printf("\nB: ");
    for(int i = 0;i<number_of_b;i++){
        printf("* ");
    }
    printf("\nC: ");
    for(int i = 0;i<number_of_c;i++){
        printf("* ");
    }
    printf("\nD: ");
    for(int i = 0;i<number_of_d;i++){
        printf("* ");
    }
    printf("\nF: ");
    for(int i = 0;i<number_of_f;i++){
        printf("* ");
    }

}

void sorting_menu(int student_count, student* students){

    int userSelection;
    printf("\n\nColumn Options \n");
    printf("---------------- \n");
    printf("1. Student ID \n");
    printf("2. Last Name \n");
    printf("3. Exam \n");
    printf("4. Total \n");
    printf("Sort Column: ");
    scanf("%d", &userSelection);
    switch(userSelection){
        case 1:
            qsort(students, student_count, sizeof(student), compare_by_id);
            break;
        case 2:
            qsort(students, student_count, sizeof(student), compare_by_last_name);
            break;
        case 3:
            qsort(students, student_count, sizeof(student), compare_by_exam);
            break;
        case 4:
            qsort(students, student_count, sizeof(student), compare_by_total);
            break;
        default:
            printf("Sort unchanged.");
    }
    printf("Sort column updated.");
}

void change_last_name(int student_count, student* students, gradeMapping gradeMapping){

    display_spreadsheet(student_count, students, gradeMapping);
    long ID;
    printf("\nEnter Student ID: ");
    scanf("%ld", &ID);    

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { // Discard remaining characters in the input buffer
    }

    int i=0;
    for(; i<student_count; i++){
        if(students[i].id == ID){
            printf("\n\nEnter updated last name: ");
            scanf("%s",students->lastName);
            printf("\nLast name updated: %s", students[i].lastName);
            break;
        }
        
    };
    if((i==student_count)){
            printf("ID not found.");
    }

}

void update_exam(int student_count, student* students, gradeMapping gradeMapping){

    display_spreadsheet(student_count, students, gradeMapping);
    long ID;
    printf("\nEnter Student ID: ");
    scanf("%ld", &ID);

    int newExam;
    printf("\n\nEnter updated exam grade: ");
    scanf("%d", &newExam);
    if(newExam>40 || newExam<0){
        printf("Please enter the correct grade");
    }
    else{
        int i=0;
        for(; i<student_count; i++){
            if(students[i].id == ID){
                students[i].final = newExam;
                printf("\nExam grade updated");
                break;
            }
            
        };
        if((i==student_count)){
                printf("ID not found.");
        }

    }
    

}

gradeMapping change_grade_mapping(int student_count, student* students, gradeMapping gradeMapping){
    printf("Current Grade Mapping:\n");
    printf("A: >=%d\n", gradeMapping.baseline_A);
    printf("B: >=%d\n", gradeMapping.baseline_B);
    printf("C: >=%d\n", gradeMapping.baseline_C);
    printf("D: >=%d\n", gradeMapping.baseline_D);
    printf("F: <=%d\n", gradeMapping.baseline_F);

    int newbaseline_A;
    int newbaseline_B;
    int newbaseline_C;
    int newbaseline_D;

    printf("Enter new A baseline: ");
    scanf("%d", &newbaseline_A);
    gradeMapping.baseline_A = newbaseline_A;

    printf("Enter new B baseline: ");
    scanf("%d", &newbaseline_B);
    gradeMapping.baseline_B = newbaseline_B;

    printf("Enter new C baseline: ");
    scanf("%d", &newbaseline_C);
    gradeMapping.baseline_C = newbaseline_C;

    printf("Enter new D baseline: ");
    scanf("%d", &newbaseline_D);
    gradeMapping.baseline_D= newbaseline_D;
    gradeMapping.baseline_F= newbaseline_D;

    printf("New Grade Mapping:\n");
    printf("A: >=%d\n", gradeMapping.baseline_A);
    printf("B: >=%d\n", gradeMapping.baseline_B);
    printf("C: >=%d\n", gradeMapping.baseline_C);
    printf("D: >=%d\n", gradeMapping.baseline_D);
    printf("F: <=%d\n", gradeMapping.baseline_F);

    return gradeMapping;
}

student* delete_student(int student_count, student* students, gradeMapping gradeMapping){
    long ID;

    display_spreadsheet(student_count, students, gradeMapping);
    printf("\n\nEnter Student ID: ");
    scanf("%ld", &ID);

    int i=0;
    for(; i<student_count; i++){
        if(students[i].id == ID){
            for (int j = i; j < (student_count) - 1; j++) {
                students[j] = students[j + 1];
            }
            (student_count)--; 
            student* new_students = realloc(students, (student_count) * sizeof(student));
            if (new_students == NULL) {
                printf("Memory reallocation failed.\n");
                return students;
            }
            printf("\nStudent successfully deleted.");
            return new_students;
        }
            
    };
    if((i==student_count)){
         printf("ID not found.");
         return students;
    } else{
       return  students;
    }
    
    

}