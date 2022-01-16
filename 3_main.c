#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct NhanVien
{
    char ma[8];
    char ho[20];
    char ten[20];
    char gioi_tinh[8];
    char ngay_sinh[11];
    char phong_ban[20];
    char noi_o[20];
} NV;

typedef struct TienDo
{
    char ma_nv[8];
    char ma_da[8];
    float tien_do;
} TD;

char file_result[] = "result.csv";
char file_check[] = "check.txt";
char file_nhan_vien[] = "Employee.csv";
char file_tien_do[] = "Progress.csv";

int doc_nhan_vien(NV ds[])
{
    int i = 0;
    FILE *file = fopen("Employee.csv", "r");
    if (file != NULL)
    {
        char tmp[100];
        fgets(tmp, 100, file);
        while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", ds[i].ma, ds[i].ho, ds[i].ten, ds[i].gioi_tinh, ds[i].ngay_sinh, ds[i].phong_ban, ds[i].noi_o) != EOF)
        {
            i++;
        }
    }
    fclose(file);
    return i;
}

int doc_tien_do(TD ds[])
{
    int i = 0;
    FILE *file = fopen(file_tien_do, "r");
    if (file != NULL)
    {
        char tmp[100];
        fgets(tmp, sizeof(tmp), file);
        while (fscanf(file, "%[^,],%[^,],%f\n", ds[i].ma_nv, ds[i].ma_da, &ds[i].tien_do) != EOF)
        {
            i++;
        }
    }
    fclose(file);
    return i;
}

void dem_nv_theo_phong_ban(NV ds[], int sl, char pb[])
{
    int kq = 0;
    int i;
    for (i = 0; i <= sl - 1; i++)
    {
        if (strcmp(ds[i].phong_ban, pb) == 0)
        {
            kq++;
        }
    }

    FILE *file = fopen(file_result, "w");
    fprintf(file, "%d", kq);
    fclose(file);
}

void ds_nhan_vien_nam(NV ds[], int sl)
{
    FILE *file = fopen(file_result, "w");
    int i;
    for (i = 0; i <= sl - 1; i++)
    {
        if (strcmp(ds[i].gioi_tinh, "Male") == 0)
        {
            fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", ds[i].ma, ds[i].ho, ds[i].ten, ds[i].gioi_tinh, ds[i].ngay_sinh, ds[i].phong_ban, ds[i].noi_o);
        }
    }
    fclose(file);
}

void ds_nhan_vien_nu(NV ds[], int sl)
{
    FILE *file = fopen(file_result, "w");
    int i;
    for (i = 0; i <= sl - 1; i++)
    {
        if (strcmp(ds[i].gioi_tinh, "Female") == 0)
        {
            fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", ds[i].ma, ds[i].ho, ds[i].ten, ds[i].gioi_tinh, ds[i].ngay_sinh, ds[i].phong_ban, ds[i].noi_o);
        }
    }
    fclose(file);
}

void ds_nhan_vien_cung_noi_o(NV ds[], int sl, char str[])
{
    FILE *file = fopen(file_result, "w");
    int i;
    for (i = 0; i <= sl - 1; i++)
    {
        if (strcmp(ds[i].noi_o, str) == 0)
        {
            fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", ds[i].ma, ds[i].ho, ds[i].ten, ds[i].gioi_tinh, ds[i].ngay_sinh, ds[i].phong_ban, ds[i].noi_o);
        }
    }
    fclose(file);
}

void sap_xep_tang_dan(NV ds[], int sl)
{
    int i, j;
    NV nv;
    for (i = 0; i <= sl - 2; i++)
    {
        for (j = i + 1; j <= sl - 1; j++)
        {
            if ((strcmp(ds[i].ten, ds[j].ten) > 0) ||
                (strcmp(ds[i].ten, ds[j].ten) == 0 && strcmp(ds[i].ho, ds[j].ho) > 0))
            {
                nv = ds[i];
                ds[i] = ds[j];
                ds[j] = nv;
            }
        }
    }

    FILE *file = fopen(file_result, "w");
    for (i = 0; i <= sl - 1; i++)
    {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", ds[i].ma, ds[i].ho, ds[i].ten, ds[i].gioi_tinh, ds[i].ngay_sinh, ds[i].phong_ban, ds[i].noi_o);
    }
    fclose(file);
}

void sap_xep_giam_dan(NV ds[], int sl)
{
    int i, j;
    NV nv;
    for (i = 0; i <= sl - 2; i++)
    {
        for (j = i + 1; j <= sl - 1; j++)
        {
            if ((strcmp(ds[i].ten, ds[j].ten) < 0) ||
                (strcmp(ds[i].ten, ds[j].ten) == 0 && strcmp(ds[i].ho, ds[j].ho) > 0))
            {
                nv = ds[i];
                ds[i] = ds[j];
                ds[j] = nv;
            }
        }
    }

    FILE *file = fopen(file_result, "w");
    for (i = 0; i <= sl - 1; i++)
    {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", ds[i].ma, ds[i].ho, ds[i].ten, ds[i].gioi_tinh, ds[i].ngay_sinh, ds[i].phong_ban, ds[i].noi_o);
    }
    fclose(file);
}

void bao_cao_tien_do(TD ds[], int sl, float tien_do)
{
    FILE *file = fopen(file_result, "w");
    int i;
    for (i = 0; i <= sl - 1; i++)
    {
        if (ds[i].tien_do == tien_do)
        {
            fprintf(file, "%s\n", ds[i].ma_nv);
        }
    }
    fclose(file);
}

void trung_binh_tien_do_du_an(TD ds[], int sl, char str[])
{
    float tong = 0;
    int so_nhan_vien = 0;
    int i;
    for (i = 0; i <= sl - 1; i++)
    {
        if (strcmp(ds[i].ma_da, str) == 0)
        {
            tong = tong + ds[i].tien_do;
            so_nhan_vien = so_nhan_vien + 1;
        }
    }

    float kq;
    if (so_nhan_vien == 0)
    {
        kq = 0;
    }
    else
    {
        kq = tong / so_nhan_vien;
    }

    FILE *file = fopen(file_result, "w");
    fprintf(file, "%.3f", kq);
    fclose(file);
}

int kiem_tra_chuoi_lenh(char str[])
{
    int dem = 0;
    int i;
    for (i = 0; i <= strlen(str) - 1; i++)
    {
        if (str[i] == ' ')
        {
            dem++;
        }
    }

    if (dem == 1)
    {
        return 1;
    }
    return 0;
}

char *chuan_hoa_chuoi_lenh(char str[])
{
    int i;
    for (i = 0; i <= strlen(str) - 1; i++)
    {
        str[i] = tolower(str[i]);
    }

    for (i = 0; i <= strlen(str) - 1; i++)
    {
        if (str[i] == ' ')
        {
            str[i + 1] = toupper(str[i + 1]);
        }
        else if (str[i] == '\n')
        {
            str[i] = '\0';
        }
    }
}

void viet_file_check()
{
    FILE *file = fopen(file_check, "w");
    if (file != NULL)
    {
        fprintf(file, "%s", "wrong syntax");
    }
    fclose(file);
}

void thuc_hien_cau_lenh(NV ds_nv[], TD ds_td[], int so_nv, int so_td, char lenh[])
{
    char dau_cach[] = " ";
    char *chuoi1 = strtok(lenh, dau_cach);
    char *chuoi2 = strtok(NULL, dau_cach);
    if (chuoi2 == NULL)
    {
        viet_file_check();
    }
    else
    {
        if (strcmp(chuoi1, "count") == 0)
        {
            dem_nv_theo_phong_ban(ds_nv, so_nv, chuoi2);
        }
        else if (strcmp(chuoi1, "list") == 0)
        {
            if (strcmp(chuoi2, "Male") == 0)
            {
                ds_nhan_vien_nam(ds_nv, so_nv);
            }
            else if (strcmp(chuoi2, "Female") == 0)
            {
                ds_nhan_vien_nu(ds_nv, so_nv);
            }
            else
            {
                viet_file_check();
            }
        }
        else if (strcmp(chuoi1, "report") == 0)
        {
            float doi_sang_float = atof(chuoi2);
            if (doi_sang_float > 0 && doi_sang_float <= 1)
            {
                bao_cao_tien_do(ds_td, so_td, doi_sang_float);
            }
            else
            {
                viet_file_check();
            }
        }
        else if (strcmp(chuoi1, "average") == 0)
        {
            trung_binh_tien_do_du_an(ds_td, so_td, chuoi2);
        }
        else if (strcmp(chuoi1, "sort") == 0)
        {
            if (strcmp(chuoi2, "Asc") == 0)
            {
                sap_xep_tang_dan(ds_nv, so_nv);
            }
            else if (strcmp(chuoi2, "Desc") == 0)
            {
                sap_xep_giam_dan(ds_nv, so_nv);
            }
            else
            {
                viet_file_check();
            }
        }
        else if (strcmp(chuoi1, "country") == 0)
        {
            ds_nhan_vien_cung_noi_o(ds_nv, so_nv, chuoi2);
        }
        else
        {
            viet_file_check();
        }
    }
}

int main()
{
    NV ds_nv[1500];
    TD ds_td[1500];
    int so_nhan_vien = doc_nhan_vien(ds_nv);
    int so_tien_do = doc_tien_do(ds_td);

    char chuoi_lenh[255];
    fflush(stdin);
    fgets(chuoi_lenh, sizeof(chuoi_lenh), stdin);
    if (kiem_tra_chuoi_lenh(chuoi_lenh) == 1)
    {
        chuan_hoa_chuoi_lenh(chuoi_lenh);
        thuc_hien_cau_lenh(ds_nv, ds_td, so_nhan_vien, so_tien_do, chuoi_lenh);
    }
    else
    {
        viet_file_check();
    }

    return 0;
}