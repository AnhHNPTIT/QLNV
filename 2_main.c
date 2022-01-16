#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct NhanVien {
    char maNV[100];
    char ho[100];
    char ten[100];
    char gioiTinh[100];
    char ngaySinh[100];
    char phongBan[100];
    char quocTich[100];
};

struct TienDo {
    char maNV[100];
    char maDA[100];
    float tienDo;
};

struct NhanVien nv[10000];
struct TienDo td[10000];
int slNV;
int slTD;

char * xoaXuongDong(char str[]) {
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '\n') {
            str[i] = '\0';
        }
    }
    return str;
}

char * chuoiVietThuong(char str[]) {
    for(int i = 0; i < strlen(str); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

int docDSNV() {
    FILE * file = fopen("Employee.csv", "r");
    int soLuong = 0;
    char str[100];
    fgets(str, 100, file);
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", nv[soLuong].maNV, nv[soLuong].ho, nv[soLuong].ten, nv[soLuong].gioiTinh, nv[soLuong].ngaySinh, nv[soLuong].phongBan, nv[soLuong].quocTich) != EOF) {
        soLuong += 1;
    }
    fclose (file);
    return soLuong;
}

int docDSTD() {
    FILE * file = fopen("Progress.csv", "r");
    int soLuong = 0;
    char str[100];
    fgets(str, 100, file);
    while (fscanf(file, "%[^,],%[^,],%f\n", td[soLuong].maNV, td[soLuong].maDA, &td[soLuong].tienDo) != EOF) {
        soLuong += 1;
    }
    fclose (file);
    return soLuong;    
}

int demNV(char str[]) {
    FILE * file = fopen ("result.csv", "w");  
    int kq = 0;
    for (int i = 0; i < slNV; i++) {
        if (strcmp(nv[i].phongBan,str) == 0) {
            kq += 1;
        }
    }
    fprintf(file, "%d", kq);
    fclose (file);
    return 1;    
}

int dsNVTheoGioiTinh(char str[]) {
    FILE * file = fopen ("result.csv", "w");  
    if (strcmp(str, "female") == 0) {
        for (int i = 0; i < slNV; i++) {
            if (strcmp(nv[i].gioiTinh, "Female") == 0) {
                fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", nv[i].maNV, nv[i].ho, nv[i].ten, nv[i].gioiTinh, nv[i].ngaySinh, nv[i].phongBan, nv[i].quocTich);
            }
        }
    }
    else if (strcmp(str, "male") == 0) {
        for (int i = 0; i < slNV; i++) {
            if (strcmp(nv[i].gioiTinh, "Male") == 0) {
                fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", nv[i].maNV, nv[i].ho, nv[i].ten, nv[i].gioiTinh, nv[i].ngaySinh, nv[i].phongBan, nv[i].quocTich);
            }
        }
    }
    fclose (file);
    return 1;     
}

int kiemTra(int mang[], int sl, int ma) {
    for (int i = 0; i < sl; i++) {
        if (mang[i] == ma) {
            return 0;
        }
    }
    return 1;
}

int baoCao(float str) {
    FILE * file = fopen ("result.csv", "w");  
    int mang[1000];
    int dem = 0;
    for (int i = 0; i < slTD; i++) {
        if (td[i].tienDo == str) {
            if (dem != 0) {
                if (kiemTra(mang, dem, atoi(td[i].maNV)) == 1) {
                    mang[dem++] = atoi(td[i].maNV);
                    fprintf(file, "%s\n", td[i].maNV);
                }
            }
            else {
                mang[dem++] = atoi(td[i].maNV);
                fprintf(file, "%s\n", td[i].maNV);
            }
        }
    }
    fclose (file);
    return 1;     
}

int trungBinh(char str[]) {
    float tong = 0;
    int dem = 0;
    float kq = 0;
    FILE * file = fopen ("result.csv", "w");  
    for (int i = 0; i < slTD; i++) {
        if (strcmp(td[i].maDA, str) == 0) {
            tong += td[i].tienDo;
            dem += 1;
        }
    }
    if (dem != 0) {
      kq = tong/dem;
    }
    fprintf(file, "%.3f", kq);
    fclose (file);
    return 1;  
}

int sapXep(char str[]) {
    FILE * file = fopen ("result.csv", "w"); 
    struct NhanVien tam; 
    
    if (strcmp(str, "asc") == 0) {
        for (int i = 0; i < slNV - 1; i++) {
            for (int j = i + 1; j < slNV; j++) {
                if (strcmp(nv[i].ten, nv[j].ten) > 0) {
                    tam = nv[i];
                    nv[i] = nv[j];
                    nv[j] = tam;
                }
                else if (strcmp(nv[i].ten, nv[j].ten) == 0 && strcmp(nv[i].ho, nv[j].ho) > 0) {
                    tam = nv[i];
                    nv[i] = nv[j];
                    nv[j] = tam; 
                }
            }
        }

        for (int i = 0; i < slNV; i++) {
            fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", nv[i].maNV, nv[i].ho, nv[i].ten, nv[i].gioiTinh, nv[i].ngaySinh, nv[i].phongBan, nv[i].quocTich);
        }
    }
    else if (strcmp(str, "desc") == 0) {
        for (int i = 0; i < slNV - 1; i++) {
            for (int j = i + 1; j < slNV; j++) {
                if (strcmp(nv[i].ten, nv[j].ten) < 0) {
                    tam = nv[i];
                    nv[i] = nv[j];
                    nv[j] = tam;
                }
                else if (strcmp(nv[i].ten, nv[j].ten) == 0 && strcmp(nv[i].ho, nv[j].ho) > 0) {
                    tam = nv[i];
                    nv[i] = nv[j];
                    nv[j] = tam; 
                }
            }
        }

        for (int i = 0; i < slNV; i++) {
            fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", nv[i].maNV, nv[i].ho, nv[i].ten, nv[i].gioiTinh, nv[i].ngaySinh, nv[i].phongBan, nv[i].quocTich);
        }
    }

    fclose (file);
    return 1;     
}

int dsNVTheoQuocTich(char str[]) {
    FILE * file = fopen ("result.csv", "w");  
    for (int i = 0; i < slNV; i++) {
        char tam[100]; 
        strcpy(tam, nv[i].quocTich);
        if (strcmp(chuoiVietThuong(tam), str) == 0) {
            fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", nv[i].maNV, nv[i].ho, nv[i].ten, nv[i].gioiTinh, nv[i].ngaySinh, nv[i].phongBan, nv[i].quocTich);
        }
    }
    fclose (file);
    return 1;     
}

void ghiLoiVaoFile() {
    FILE * file = fopen ("check.txt", "w");
    fprintf(file, "%s", "wrong syntax");
    fclose(file);
}

int demKhoangTrang(char str[]) {
    int dem = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ') {
            dem += 1;
        }
    }
    return dem;
}

int kiemTraChu(char str[]) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i]) && str[i] != '.') {
            return 1;
        }
    }
    return 0;
}

int main() {
    slNV = docDSNV();
    slTD = docDSTD();
    char str[255];
    fgets(str, 255, stdin);
    xoaXuongDong(str);
    chuoiVietThuong(str);

    if (demKhoangTrang(str) == 1) {
        char khoangTrang[2] = " ";
        char * cauLenh = strtok(str, khoangTrang);
        if (cauLenh != NULL) {
            char * thamSo = strtok(NULL, khoangTrang);
            if (thamSo != NULL) {
                char * thua = strtok(NULL, khoangTrang);
                if (thua == NULL) {
                    if (strcmp(cauLenh, "count") == 0) {
                        demNV(thamSo);
                    }
                    else if (strcmp(cauLenh, "list") == 0) {
                        if (strcmp(thamSo, "female") == 0 || strcmp(thamSo, "male") == 0) {
                            dsNVTheoGioiTinh(thamSo);
                        }
                        else {
                            ghiLoiVaoFile();
                        }
                    }
                    else if (strcmp(cauLenh, "report") == 0) {
                        
                        if (kiemTraChu(thamSo) == 1) {
                            ghiLoiVaoFile();
                        }
                        else {
                            float chuyenDoi = atof(thamSo);
                            if (chuyenDoi < 0 || chuyenDoi > 1) {
                                ghiLoiVaoFile();
                            }
                            else {
                                baoCao(chuyenDoi);
                            }
                        }
                    }
                    else if (strcmp(cauLenh, "average") == 0) {
                        trungBinh(thamSo);
                    }
                    else if (strcmp(cauLenh, "sort") == 0) {
                        if (strcmp(thamSo, "asc") == 0 || strcmp(thamSo, "desc") == 0) {
                            sapXep(thamSo);
                        }
                        else {
                            ghiLoiVaoFile();
                        }
                    }
                    else if (strcmp(cauLenh, "country") == 0) {
                        dsNVTheoQuocTich(thamSo);
                    }
                    else {
                        ghiLoiVaoFile();
                    }
                }
                else {
                    ghiLoiVaoFile();
                }
            }
            else {
                ghiLoiVaoFile();
            }
        }
        else {
            ghiLoiVaoFile();
        }
    }
    else {
        ghiLoiVaoFile();
    }
  
    return 0;
}


