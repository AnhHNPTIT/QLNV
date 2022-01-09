#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Employee
{
    char EmployeeID[255];
    char FirstName[255];
    char LastName[255];
    char Gender[255];
    char DOB[255];
    char Department[255];
    char Country[255];
};

struct Project
{
    char ProjectID[255];
    char ProjectName[255];
    int Week;
};

struct Progress
{
    char EmployeeID[255];
    char ProjectID[255];
    float Progress;
};

int readFileEmployee(struct Employee emp[]) {
    FILE * fp;
    int i = 0;
    fp = fopen ("Employee.csv", "r"); 
    if (fp != NULL) {
        // doc thong tin sinh vien
        char tmp[255];
        fgets(tmp, 255, fp);
        while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", &emp[i].EmployeeID, &emp[i].FirstName, &emp[i].LastName, &emp[i].Gender, &emp[i].DOB, &emp[i].Department, &emp[i].Country) != EOF)
        {
            i++;  
        }
    }
    // tra ve so luong sinh vien duoc doc tu file
    return i;
    fclose (fp);
}

int readFileProject(struct Project pj[]) {
    FILE * fp;
    int i = 0;
    fp = fopen ("Project.csv", "r"); 
    if (fp != NULL) {
        // doc thong tin du an
        char tmp[255];
        fgets(tmp, 255, fp);
        while (fscanf(fp, "%[^,],%[^,],%d", &pj[i].ProjectID, &pj[i].ProjectName, &pj[i].Week) != EOF)
        {
            i++;  
        }
    }
    // tra ve so luong du an duoc doc tu file
    return i;
    fclose (fp);
}

int readFileProgress(struct Progress pg[]) {
    FILE * fp;
    int i = 0;
    fp = fopen ("Progress.csv", "r"); 
    if (fp != NULL) {
        // doc thong tin sinh vien
        char tmp[255];
        fgets(tmp, 255, fp);
        while (fscanf(fp, "%[^,],%[^,],%f", &pg[i].EmployeeID, &pg[i].ProjectID, &pg[i].Progress) != EOF)
        {
            i++;  
        }
    }
    // tra ve so luong sinh vien duoc doc tu file
    return i;
    fclose (fp);
}

int countDepartment(struct Employee emp[], int n, char dep[]) {
    FILE * fp;
    fp = fopen ("result.csv", "w");  
    
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(emp[i].Department,dep) == 0) {
            cnt++;
        }
    }

    fprintf(fp, "%d", cnt);
    fclose (fp);
    return 1;
}

int listEmp(struct Employee emp[], int numEmp, char gen[7]) 
{
    if (strcmp(gen, "Female") != 0 && strcmp(gen, "Male") != 0) {
        return 0;
    }

    FILE * fp;
    fp = fopen ("result.csv", "w");  

    for (int i = 0; i < numEmp; i++) {
        if (strcmp(gen, "Female") == 0) {
            if (strcmp(emp[i].Gender, gen) == 0) {
                fprintf(fp, "%s,%s,%s,%s,%s,%s,%s", emp[i].EmployeeID, emp[i].FirstName, emp[i].LastName, emp[i].Gender, emp[i].DOB, emp[i].Department, emp[i].Country);
            }
        }
        else if (strcmp(gen, "Male") == 0) {
            if (strcmp(emp[i].Gender, gen) == 0) {
                fprintf(fp, "%s,%s,%s,%s,%s,%s,%s", emp[i].EmployeeID, emp[i].FirstName, emp[i].LastName, emp[i].Gender, emp[i].DOB, emp[i].Department, emp[i].Country);
            }
        }
    }

    fclose (fp);
    return 1;
}

char * replaceChars(char str[]) 
{
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] == '.' || str[i] == '-') {
            str[i] = '\0';
        }
        i++;
    }
    return str;
}

int isDigitChar(char str[])
{
    replaceChars(str);
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int reportN(struct Progress pg[], int numPg, char n[]) 
{
    float tmp;
    if (!isDigitChar(n)) {
        return 0;
    }
    else {
        tmp = atoi(n);
        if (tmp < 0 || tmp > 1) {
            return 0;
        }
    }

    FILE * fp;
    fp = fopen ("result.csv", "w");  

    for (int i = 0; i < numPg; i++) {
        if (pg[i].Progress == tmp) {
            fprintf(fp, "%s\n", pg[i].EmployeeID);
        }
    }

    fclose (fp);
    return 1;
}

int averageX(struct Progress pg[], int numPg, char x[]) 
{
    FILE * fp;
    fp = fopen ("result.csv", "w");  

    float sum = 0;
    int cnt = 0;
    float result = 0;
    for (int i = 0; i < numPg; i++) {
        if (strcmp(pg[i].ProjectID,x) == 0) {
            sum += pg[i].Progress;
            cnt++;
        }
    }    
    result = sum/cnt;
    fprintf(fp, "%.3f\n", result);
    fclose (fp);
    return 1;
}

int sort(struct Employee emp[], int numEmp, char order[])
{
    if (strcmp(order, "asc") != 0 && strcmp(order, "desc") != 0) {
        return 0;
    }

    FILE * fp;
    fp = fopen ("result.csv", "w");  

    struct Employee tmp;
    for (int i = 0; i < numEmp - 1; i++) {
        for (int j = i + 1; j < numEmp; j++) {
            if (strcmp(order, "asc") == 0) {
                if ((strcmp(emp[i].LastName, emp[j].LastName) > 0) || 
                    (strcmp(emp[i].LastName, emp[j].LastName) == 0 && strcmp(emp[i].FirstName, emp[j].FirstName) > 0)) {
                    tmp = emp[i];
                    emp[i] = emp[j];
                    emp[j] = tmp;
                }
            }
            else if(strcmp(order, "desc") == 0) {
                if ((strcmp(emp[i].LastName, emp[j].LastName) < 0) || 
                    (strcmp(emp[i].LastName, emp[j].LastName) == 0 && strcmp(emp[i].FirstName, emp[j].FirstName) > 0)) {
                    tmp = emp[i];
                    emp[i] = emp[j];
                    emp[j] = tmp;
                }
            }
        }
    }

    for (int i = 0; i < numEmp; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", emp[i].EmployeeID, emp[i].FirstName, emp[i].LastName, emp[i].Gender, emp[i].DOB, emp[i].Department, emp[i].Country);
    }

    fclose (fp);
    return 1;
}

int countryName(struct Employee emp[], int numEmp, char name[]) 
{
    FILE * fp;
    fp = fopen ("result.csv", "w");  

    for (int i = 0; i < numEmp; i++) {
        if (strcmp(emp[i].Country, name) == 0) {
            fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", emp[i].EmployeeID, emp[i].FirstName, emp[i].LastName, emp[i].Gender, emp[i].DOB, emp[i].Department, emp[i].Country);
        }
    }   

    fclose (fp);
    return 1;
}

char * convertToLowercase(char str[]) 
{
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

int checkNumberParameter(char str[]) {
    int cnt = 0;
    for(int i = 0; str[i]; i++){
        if (str[i] == ' ') {
            cnt++;
        }
    }
    if (cnt == 1) {
        return 1;
    }
    return 0;
}

int execute(struct Employee emp[], int numEmp, struct Project pj[], int numPj, struct Progress pg[], int numPg, char str[]) {   
    if (checkNumberParameter(str) == 0) {
        return 0;
    }
    char s[2] = " ";
    // get 1st word
    char *token1 = strtok(str, s);
    // fprintf("token1 %s\n", token1);
    // convert to lowercase 
    convertToLowercase(token1);
    // get 2nd word
    char *token2 = strtok(NULL, s);
    // fprintf("token2 %s\n", token2);
    if (token2 != NULL) {
        // compare with all command to execute
        if (strcmp(token1, "count") == 0) {
            return countDepartment(emp, numEmp, token2);
        }
        else if (strcmp(token1, "list") == 0) {
            return listEmp(emp, numEmp, token2);
        }
        else if (strcmp(token1, "report") == 0) {
            return reportN(pg, numPg, token2);
        }
        else if(strcmp(token1, "average") == 0) {
            return averageX(pg, numPg, token2);
        }
        else if(strcmp(token1, "sort") == 0) {
            return sort(emp, numEmp, token2);
        }
        else if(strcmp(token1, "country") == 0) {
            return countryName(emp, numEmp, token2);
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

void removeNewLineChar(char x[]){
	size_t len = strlen(x);
	if(x[len-1]=='\n'){
		x[len-1]='\0';
	}
}

int main()
{
    struct Employee emp[1000];
    struct Project pj[1000];
    struct Progress pg[1000];
    int numEmp = readFileEmployee(emp);
    int numPj = readFileProject(pj);
    int numPg = readFileProgress(pg);
    char str[255];
    fflush(stdin);
    fgets(str, sizeof(str), stdin);
    removeNewLineChar(str);

    int result = execute(emp, numEmp, pj, numPj, pg, numPg, str);
    if (result == 0) {
        FILE * fp;
        fp = fopen ("check.txt", "w");  
        if (fp != NULL) {    
            fprintf(fp, "%s", "wrong syntax");
        }
        fclose (fp);
    }
    return 0;
}