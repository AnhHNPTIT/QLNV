#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee
{
    int EmployeeID;
    char FirstName[255];
    char LastName[255];
    char Gender[255];
    char DOB[255];
    int Department;
    char Country[255];
};

struct Project
{
    int ProjectID;
    char ProjectName[255];
    int Week;
};

struct Progress
{
    int EmployeeID;
    int ProjectID;
    float Progress;
};

int readFileEmployee(struct Employee emp[1000], char fileName[]) {
    FILE * fp;
    int i = 0;
    fp = fopen (fileName, "r"); 
    if (fp != NULL) {
        // doc thong tin sinh vien
        char tmp[255];
        fgets(tmp, 255, fp);
        while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d,%s", &emp[i].EmployeeID, &emp[i].FirstName, &emp[i].LastName, &emp[i].Gender, &emp[i].DOB, &emp[i].Department, &emp[i].Country) != EOF)
        {
            i++;  
        }
    }
    // tra ve so luong sinh vien duoc doc tu file
    return i;
    fclose (fp);
}

int readFileProject(struct Project pj[1000], char fileName[]) {
    FILE * fp;
    int i = 0;
    fp = fopen (fileName, "r"); 
    if (fp != NULL) {
        // doc thong tin du an
        char tmp[255];
        fgets(tmp, 255, fp);
        while (fscanf(fp, "%d,%[^,],%d", &pj[i].ProjectID, &pj[i].ProjectName, &pj[i].Week) != EOF)
        {
            i++;  
        }
    }
    // tra ve so luong du an duoc doc tu file
    return i;
    fclose (fp);
}

int readFileProgress(struct Progress pg[1000], char fileName[]) {
    FILE * fp;
    int i = 0;
    fp = fopen (fileName, "r"); 
    if (fp != NULL) {
        // doc thong tin sinh vien
        char tmp[255];
        fgets(tmp, 255, fp);
        while (fscanf(fp, "%d,%d,%f", &pg[i].EmployeeID, &pg[i].ProjectID, &pg[i].Progress) != EOF)
        {
            i++;  
        }
    }
    // tra ve so luong sinh vien duoc doc tu file
    return i;
    fclose (fp);
}

void writeEmployee(struct Employee emp[], int n, char fileName[]) {
    FILE * fp;
    fp = fopen (fileName, "w");  
    if (fp != NULL) {
        for(int i = 0;i < n;i++){
            fprintf(fp, "%d,%s,%s,%s,%s,%d,%s", emp[i].EmployeeID, emp[i].FirstName, emp[i].LastName, emp[i].Gender, emp[i].DOB, emp[i].Department, emp[i].Country);
        }
    }
    fclose (fp);
}

int countDepartment(struct Employee emp[], int n, int dep) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (emp[i].Department == dep) {
            cnt++;
        }
    }
    return cnt;
}

void listEmp(struct Employee emp[], int n, char gen[7]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(emp[i].Gender, gen) == 0) {
            printf("%d,%s,%s,%s,%s,%d,%s\n", emp[i].EmployeeID, emp[i].FirstName, emp[i].LastName, emp[i].Gender, emp[i].DOB, emp[i].Department, emp[i].Country);
        }
    }
}

void reportN(struct Progress pg[], int numPg, float n) {
    for (int i = 0; i < numPg; i++) {
        if (pg[i].Progress == n) {
            printf("%d\n", pg[i].EmployeeID);
        }
    }
}

void averageX(struct Progress pg[], int numPg, int x) {
    float sum = 0;
    int cnt = 0;
    float result = 0;
    for (int i = 0; i < numPg; i++) {
        if (pg[i].ProjectID == x) {
            sum += pg[i].Progress;
            cnt++;
        }
    }    
    result = sum/cnt;
    printf("%.3f\n", result);
}

int main()
{
    struct Employee emp[1000];
    struct Project pj[1000];
    struct Progress pg[1000];
    int numEmp = readFileEmployee(emp, "Employee.csv");
    // int numPj = readFileProject(pj, "Project.csv");
    // int numPg = readFileProgress(pg, "Progress.csv");
    // printf("%s\n", emp[0].EmployeeID);

    // int result = countDepartment(emp, numEmp, 12549);
    // printf("%d\n", result);

    listEmp(emp, numEmp, "Male");

    // int key;
    // int result;
    // scanf("%d",&key);

    // switch(key) {
    //     case 1:
    //         printf("aaaa");
    //         result = countDepartment(emp, numEmp, 12549);
    //         printf("%d", result);
    //         exit;
    //     case 2:
    //         exit;
    // }
    
    return 0;
}