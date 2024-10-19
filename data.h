#ifndef MY_DATA
#define MY_DATA

#include "calc.h"

//Public functions available in data.c
student* input_student_data(const char *filename, int *student_count);
void process_student_row(const char *row, student *students, int index);
student* resize_student_array(student *students, int *capacity);


#endif /*MY_DATA*/