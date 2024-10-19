/*the main function and the basic GUI*/

//System Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ordering.c, calc.c, data.c -> header files
#include "data.h"
#include "calc.h"
#include "ordering.h"

// to compile: gcc spreadsheet.c data.c calc.c ordering.c
int main(void){
    int student_count = 0; 

    student *students = input_student_data("students.txt", &student_count);
    if (students == NULL) {
        fprintf(stderr, "Failed to load students.\n");
        return EXIT_FAILURE;
    }
    qsort(students, student_count, sizeof(student), compare_by_id); // initial sorting is by id
    gradeMapping defaultMapping = {80,70, 60, 50, 50};
    display_menu(student_count, students, defaultMapping);

    free(students);// Free dynamically allocated memory
    return EXIT_SUCCESS;
}
