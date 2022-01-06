#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int EmployeeID;
    char FirstName[10];
    char LastName[10];
    char Gender[6];
    char DOB[10];
    int Department;
    char Country[10];
};

struct Project{
    int ProjectID;
    char ProjectName[50];
    int Week;
};

struct Progress{
    int EmployeeID;
    int ProjectID;
    float Progress;
};

int docFile(struct Employee emp[1000000], char fileName[]) {
    FILE * fp;
    int i = 0;
    fp = fopen (fileName, "r");
    // doc thong tin sinh vien
    int id;
    char first_name[10];
    char last_name[10];
    char gen[6];
    char dob[10];
    int dep;
    char cnt[10];
    fscanf(fp, "%d,%s,%s,%s,%s,%d,%s", &id, first_name, last_name, gen, dob, &dep, cnt);
    while (fscanf(fp, "%d,%s,%s,%s,%s,%d,%s", &id, first_name, last_name, gen, dob, &dep, cnt) != EOF)
    {
        // emp[i].EmployeeID = id;
        // emp[i].FirstName[10] = first_name;
        // emp[i].LastName[10] = last_name;
        // emp[i].Gender[6] = gen;
        // emp[i].DOB[10] = dob;
        // emp[i].Department = dep;
        // emp[i].Country[10] = cnt;
        // i++;
        printf("%d \n", id);
    }
    // char str[1000];
    // fgets(str, 1000, fp);
    // while(fgets(str, 1000, fp) != NULL) {
    //     emp[i].EmployeeID = atoi(strtok(str, ","));
    //     emp[i].FirstName[10] = strtok(NULL, ",");
    //     emp[i].LastName[10] = strtok(NULL, ",");
    //     emp[i].Gender[6] = strtok(NULL, ",");
    //     emp[i].DOB[10] = strtok(NULL, ",");
    //     emp[i].Department = atoi(strtok(NULL, ","));
    //     emp[i].Country[10] = strtok(NULL, ",");
    //     i++;
    //     printf("%d", emp[i].EmployeeID);
        
    // }
    // tra ve so luong sinh vien duoc doc tu file
    return i;
    fclose (fp);
}

void main()
{
    struct Employee emp[100000];
    docFile(emp, "Employee.csv");
    // printf("%d", atoi("42"));
}