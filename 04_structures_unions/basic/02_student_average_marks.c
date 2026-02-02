#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>

typedef struct Student
{
    char *name;
    uint16_t roll;
    uint8_t marks[5];
}Student;

void computeAverage(Student student[], int number){
    float avg = 0;
    for(int i = 0; i < number; i++){
        for(int j =0; j < 5; j++){
            avg += student[i].marks[j];
        }
        printf("Name : %s, Roll No : %d, Avg Marks : %.1f", student[i].name, student[i].roll, avg/5); 
    }
    
}

int main(){
    Student student[1];
    
    student[0].name = strdup("Alex");
    if (student[0].name == NULL) {
        fprintf(stderr, "Memory allocation failed for name\n");
        return 1;
    }
    student[0].roll = 10;
    student[0].marks[0] = 82;
    student[0].marks[1] = 77;
    student[0].marks[2] = 67;
    student[0].marks[3] = 85;
    student[0].marks[4] = 87;

    computeAverage(student, 1);
    
    free(student[0].name);

    return 0;
}