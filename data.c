/*any code used to read the input file and extract the fields from each row*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "calc.h"

// Constants
#define ROW_LENGTH 1024
#define INITIAL_CAPACITY 10


// Prototypes
student* input_student_data(const char *filename, int *student_count);
void process_student_row(const char *row, student *students, int index);
student* resize_student_array(student *students, int *capacity);
void display_spreadsheet(int student_count, student *students, gradeMapping gradeMapping);

student* input_student_data(const char *filename, int *student_count) {
    FILE *file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) {
        perror("Unable to open file!");
        return NULL;
    }

    // Allocate initial memory for the dynamic student array
    int capacity = INITIAL_CAPACITY;
    student *students = malloc(capacity * sizeof(student));
    if (students == NULL) {
        perror("Failed to allocate memory for students");
        fclose(file_ptr);
        return NULL;
    }

    char row_buffer[ROW_LENGTH];
    *student_count = 0;  // Initialize student count to 0

    // Read each line and process it
    while (fgets(row_buffer, ROW_LENGTH, file_ptr) != NULL) {
        row_buffer[strcspn(row_buffer, "\n")] = '\0'; // Remove newline character if present

        // Resize the array if we exceed the current capacity
        if (*student_count >= capacity) {
            students = resize_student_array(students, &capacity);
            if (students == NULL) {
                perror("Failed to resize student array");
                fclose(file_ptr);
                return NULL;
            }
        }

        // Process the line and store the data in the array
        process_student_row(row_buffer, students, *student_count);
        (*student_count)++;  // Increase the count of students
    }

    fclose(file_ptr);  // Close the file
    return students;    // Return the dynamic array of students
}

// Function to resize the dynamic student array
student* resize_student_array(student *students, int *capacity) {
    *capacity *= 2;  // Double the capacity
    student *new_students = realloc(students, *capacity * sizeof(student));
    if (new_students == NULL) {
        free(students);  // Free the old memory if realloc fails
        return NULL;
    }
    return new_students;
}

void process_student_row(const char *row,student *students, int index) {
    char *token;
    int column = 0;

    char row_copy[ROW_LENGTH];
    strncpy(row_copy, row, ROW_LENGTH);

    // Split the row by '|'
    token = strtok(row_copy, "|");
    while (token != NULL) {
        switch (column) {
            case 0: students[index].id = atol(token); break;               // ID
            case 1: strncpy(students[index].lastName, token, 30); break;   // Last name
            case 2: strncpy(students[index].firstName, token, 30); break;  // First name
            case 3: students[index].a1 = atoi(token); break;          // a1 score
            case 4: students[index].a2 = atoi(token); break;            // a2 score
            case 5: students[index].a3 = atoi(token); break;               // a3 score
            case 6: students[index].midterm = atoi(token); break;               // mt score
            case 7: students[index].final = atoi(token); break;               // final score
        }
        token = strtok(NULL, "|");  // Get next token
        column++;
    }
}

