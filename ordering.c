/*any code related to sorting the spreadsheet*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calc.h"
#include "ordering.h"

//prototypes
int compare_by_id(const void *a, const void *b);
int compare_by_last_name(const void *a, const void *b);
int compare_by_exam(const void *a, const void *b) ;

int compare_by_id(const void *a, const void *b) {
    student *studentA = (student *)a;
    student *studentB = (student *)b;

    if (studentA->id < studentB->id) return -1;
    if (studentA->id > studentB->id) return 1;
    return 0;
}

int compare_by_last_name(const void *a, const void *b) {
    student *studentA = (student *)a;
    student *studentB = (student *)b;

    // Compare last names using strcmp
    return strcmp(studentA->lastName, studentB->lastName);
}

int compare_by_exam(const void *a, const void *b) {
    student *studentA = (student *)a;
    student *studentB = (student *)b;

    if (studentA->final < studentB->final) return 1;
    if (studentA->final > studentB->final) return -1;
    return 0;
}

int compare_by_total(const void *a, const void *b) {
    student *studentA = (student *)a;
    student *studentB = (student *)b;

    float totalA = calculate_total(*studentA);
    float totalB = calculate_total(*studentB);

    if (totalA < totalB) return 1;
    if (totalA > totalB) return -1;
    return 0;
}




