#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Employee 
{
    char employee_id[8];
    char first_name[20];
    char last_name[20];
    char gender[8];
    char date_of_birth[11];
    char department[20];
    char country[20];
} Emp;

typedef struct Progress 
{
    char employee_id[8];
    char project_id[8];
    float progress;
} Pro;

const char file_employee[] = "Employee.csv";
const char file_progress[] = "Progress.csv";
const char file_result[] = "result.csv";
const char file_check[] = "check.txt";
const char space_char = ' ';
const char space[2] = " ";
const char new_line = '\n';
const char remove_char = '\0';
Emp list_emp[1500];
int num_emp = 0;
Pro list_pro[1500];
int num_pro = 0;

void read_list_employee()
{
    FILE *f_read = fopen(file_employee, "r");
    int i = 0;
	if(f_read) 
    {
		for(;;) 
        {
			Emp emp;
			fscanf(f_read, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", emp.employee_id, emp.first_name, emp.last_name, emp.gender, emp.date_of_birth, emp.department, emp.country);
			list_emp[i++] = emp;
			if(feof(f_read)) 
            {
				break;
			}
		}
	}
    fclose(f_read);
    num_emp = i;
}

void read_list_progress()
{
    FILE *f_read = fopen(file_progress, "r");
    int i = 0;
	if(f_read) 
    {
		for(;;) 
        {
			Pro pro;
			fscanf(f_read, "%[^,],%[^,],%f\n", pro.employee_id, pro.project_id, &pro.progress);
			list_pro[i++] = pro;
			if(feof(f_read)) 
            {
				break;
			}
		}
	}
    fclose(f_read);
    num_pro = i;
}

bool compare_two_strings(char string1[], char string2[])
{
    if (strlen(string1) == strlen(string2))
    {
        int i;
        for (i = 0; i <= strlen(string1) - 1; i++)
        {
            if (tolower(string1[i]) != tolower(string2[i]))
            {
                return false;
            }
        }
        return true;
    } 
    else
    {
        return false;
    }
}

void count_department(char input_data[]) 
{
    int i;
    int count = 0;
    for (i = 1; i <= num_emp - 1; i++)
    {
        if (compare_two_strings(list_emp[i].department, input_data))
        {
            count = count + 1;
        }
    }

    FILE *f_write = fopen(file_result, "w");
    if(f_write)
    {
        fprintf(f_write, "%d", count);
    }
    fclose(f_write);
}

void write_error_message()
{
    FILE *f_write = fopen(file_check, "w");
    if(f_write)
    {
        fprintf(f_write, "%s", "wrong syntax");
    }
    fclose(f_write);
}

void list_employee_by_gender(char input_data[])
{
    FILE *f_write = fopen(file_result, "w");
    int i;
    for (i = 1; i <= num_emp; i++)
    {
        if (compare_two_strings(input_data, "Female") || compare_two_strings(input_data, "Male"))
        {
            if (compare_two_strings(list_emp[i].gender, input_data))
            {
                fprintf(f_write, "%s,%s,%s,%s,%s,%s,%s\n", list_emp[i].employee_id, list_emp[i].first_name, list_emp[i].last_name, list_emp[i].gender, list_emp[i].date_of_birth, list_emp[i].department, list_emp[i].country);
            }
        }
        else
        {
            write_error_message();
        }
    }
    fclose(f_write);
}

void average_x(char input_data[])
{
    int i;
    float tong = 0;
    int count = 0;
    float kq = 0;
    for (i = 1; i <= num_pro - 1; i++)
    {
        if (compare_two_strings(list_pro[i].project_id, input_data))
        {
            tong = tong + list_pro[i].progress;
            count = count + 1;
        }
    }

    if (count != 0)
    {
        kq = tong/count;
    }

    FILE *f_write = fopen(file_result, "w");
    if(f_write)
    {
        fprintf(f_write, "%.3f", kq);
    }
    fclose(f_write);
}

void swap(Emp *emp1, Emp *emp2)
{
    Emp tmp;
    tmp = *emp1;
    *emp1 = *emp2;
    *emp2 = tmp;
}

void sort_employee(char input_data[])
{
    int i, j;
    for (i = 1; i <= num_emp - 2; i++)
    {
        for (j = i + 1; j <= num_emp - 1; j++)
        {
            if (compare_two_strings(input_data, "asc"))
            {
                if (strcmp(list_emp[i].last_name, list_emp[j].last_name) > 0)
                {
                    swap(&list_emp[i], &list_emp[j]);
                }
                else if (compare_two_strings(list_emp[i].last_name, list_emp[j].last_name) && strcmp(list_emp[i].first_name, list_emp[j].first_name) > 0)
                {
                    swap(&list_emp[i], &list_emp[j]);
                }
            }
            else if (compare_two_strings(input_data, "desc"))
            {
                if (strcmp(list_emp[i].last_name, list_emp[j].last_name) < 0)
                {
                    swap(&list_emp[i], &list_emp[j]);
                }
                else if (compare_two_strings(list_emp[i].last_name, list_emp[j].last_name) && strcmp(list_emp[i].first_name, list_emp[j].first_name) > 0)
                {
                    swap(&list_emp[i], &list_emp[j]);
                }
            }
            else
            {
                write_error_message();
            }
        }
    }

    FILE *f_write = fopen(file_result, "w");
    if (f_write)
    {
        for (i = 1; i <= num_emp - 1; i++)
        {
            fprintf(f_write, "%s,%s,%s,%s,%s,%s,%s\n", list_emp[i].employee_id, list_emp[i].first_name, list_emp[i].last_name, list_emp[i].gender, list_emp[i].date_of_birth, list_emp[i].department, list_emp[i].country);
        }
    }
    fclose(f_write);
}

void list_employee_by_country(char input_data[])
{
    FILE *f_write = fopen(file_result, "w");
    int i;
    for (i = 1; i <= num_emp; i++)
    {
        if (compare_two_strings(list_emp[i].country, input_data))
        {
            fprintf(f_write, "%s,%s,%s,%s,%s,%s,%s\n", list_emp[i].employee_id, list_emp[i].first_name, list_emp[i].last_name, list_emp[i].gender, list_emp[i].date_of_birth, list_emp[i].department, list_emp[i].country);
        }
    }
    fclose(f_write);
}

bool check_command(char intput_data[])
{
    int count = 0;
    int i;
    for (i = 0; i <= strlen(intput_data) - 1; i++)
    {
        if (intput_data[i] == space_char)
        {
            count = count + 1;
        }
    }

    if (count == 1)
    {
        for (i = 0; i <= strlen(intput_data) - 1; i++)
        {
            if (intput_data[i] == new_line)
            {
                intput_data[i] = remove_char;
            }
        }
        return true;
    }

    return false;
}

int main() 
{
    read_list_employee();
    read_list_progress();

    char command[100];
    fflush(stdin);
    fgets(command, sizeof(command), stdin);

    if (!check_command(command))
    {
        write_error_message();
    }
    else
    {
        char *cmd = strtok(command, space);
        char *parameter = strtok(NULL, space);

        if (parameter != NULL)
        {
            if (compare_two_strings(cmd, "count"))
            {
                count_department(parameter);
            }
            else if (compare_two_strings(cmd, "list"))
            {
                list_employee_by_gender(parameter);
            }
            else if (compare_two_strings(cmd, "average"))
            {
                average_x(parameter);
            }
            else if (compare_two_strings(cmd, "sort"))
            {
                sort_employee(parameter);
            }
            else if (compare_two_strings(cmd, "country"))
            {
                list_employee_by_country(parameter);
            }
            else
            {
                write_error_message();
            }
        }
        else
        {
            write_error_message();
        }
    }
    
    return 0;
}