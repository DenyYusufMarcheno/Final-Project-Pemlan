#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int nisn;
    char nama[100];
    char alamat[100];
    char jenisKelamin;
    float nilai;
} siswa;

int ValidasiNISN(int nisn, siswa sk[], int jumlah)
{
    if (nisn <= 0)
    {
        printf("NISN harus berupa angka positif.\n");
    }
    for (int i = 0; i < jumlah; i++)
    {
        if (sk[i].nisn == nisn)
        {
            printf("NISN sudah terdaftar.\n");
            return 0;
        }
    }
    return 1;
}

int ValidasiJenisKelamin(char jk)
{
    if (toupper(jk) != 'L' && toupper(jk) != 'P')
    {
        printf("Jenis kelamin harus 'L' (Laki-laki) atau 'P' (Perempuan).\n");
        return 0;
    }
    return 1;
}

int ValidasiNilai(float nilai)
{
    if (nilai < 0 || nilai > 100)
    {
        printf("Nilai harus berada di antara 0 dan 100.\n");
        return 0;
    }
    return 1;
}

void CetakData(siswa sk)
{
    printf("NISN: %d\n", sk.nisn);
    printf("Nama: %s\n", sk.nama);
    printf("Alamat: %s\n", sk.alamat);
    printf("Jenis Kelamin: %c\n", sk.jenisKelamin);
    printf("Nilai: %.2f\n", sk.nilai);
}

void Tukar(siswa *a, siswa *b)
{
    siswa temp = *a;
    *a = *b;
    *b = temp;
}

int Bandingkan(siswa *a, siswa *b, int pilihan)
{
    switch (pilihan)
    {
    case 1:
        return (a->nisn < b->nisn ? -1 : a->nisn > b->nisn);
    case 2:
        return strcmp(a->nama, b->nama);
    case 3:
        return strcmp(a->alamat, b->alamat);
    case 4:
        return (a->nilai < b->nilai ? -1 : a->nilai > b->nilai);
    default:
        return 0;
    }
}

void SelectionSort(siswa arr[], int jumlah, int pilihan, int urutan)
{
    for (int i = 0; i < jumlah - 1; i++)
    {
        int pos = i;
        for (int j = i + 1; j < jumlah; j++)
        {
            if (Bandingkan(&arr[j], &arr[pos], pilihan) * urutan < 0)
            {
                pos = j;
            }
        }
        if (pos != i)
        {
            Tukar(&arr[pos], &arr[i]);
        }
    }
}

void MasukkanDataSiswa(siswa daftarSiswa[], int index, int jumlahSiswa)
{
    int valid;
    do
    {
        printf("Masukkan NISN Siswa %d: ", index + 1);
        scanf("%d", &daftarSiswa[index].nisn);
        valid = ValidasiNISN(daftarSiswa[index].nisn, daftarSiswa, index);
    } while (!valid);

    printf("Masukkan Nama Siswa %d: ", index + 1);
    scanf(" %[^\n]", daftarSiswa[index].nama);

    printf("Masukkan Alamat Siswa %d: ", index + 1);
    scanf(" %[^\n]", daftarSiswa[index].alamat);

    do
    {
        printf("Masukkan Jenis Kelamin Siswa (L/P) %d: ", index + 1);
        scanf(" %c", &daftarSiswa[index].jenisKelamin);
        valid = ValidasiJenisKelamin(daftarSiswa[index].jenisKelamin);
    } while (!valid);

    do
    {
        printf("Masukkan Nilai Siswa %d: ", index + 1);
        scanf("%f", &daftarSiswa[index].nilai);
        valid = ValidasiNilai(daftarSiswa[index].nilai);
    } while (!valid);
}

void TampilkanDataTabel(siswa daftarSiswa[], int jumlah)
{
    printf("\n===================================================================\n");
    printf("| %-5s | %-20s | %-15s | %-6s | %-6s |\n", "NISN", "Nama", "Alamat", "JK", "Nilai");
    printf("===================================================================\n");

    for (int i = 0; i < jumlah; i++)
    {
        printf("| %-5d | %-20s | %-15s | %-6c | %-6.2f |\n",
               daftarSiswa[i].nisn, daftarSiswa[i].nama, daftarSiswa[i].alamat,
               daftarSiswa[i].jenisKelamin, daftarSiswa[i].nilai);
    }

    printf("===================================================================\n");
}

void TampilkanSiswaLolos(siswa daftarSiswa[], int jumlah)
{
    printf("\n=== Data Siswa dengan Nilai di Atas 75 ===\n");
    printf("===================================================================\n");
    printf("| %-5s | %-20s | %-15s | %-6s | %-6s |\n", "NISN", "Nama", "Alamat", "JK", "Nilai");
    printf("===================================================================\n");
    int adaSiswaLolos = 0;

    for (int i = 0; i < jumlah; i++)
    {
        if (daftarSiswa[i].nilai > 75)
        {
            printf("| %-5d | %-20s | %-15s | %-6c | %-6.2f |\n",
                   daftarSiswa[i].nisn, daftarSiswa[i].nama, daftarSiswa[i].alamat,
                   daftarSiswa[i].jenisKelamin, daftarSiswa[i].nilai);
            adaSiswaLolos = 1;
        }
    }

    if (!adaSiswaLolos)
    {
        printf("| %-60s |\n", "Tidak ada siswa yang lolos.");
    }

    printf("===================================================================\n");
}

int main()
{
    int jumlahSiswa;

    printf("Masukkan jumlah siswa: ");
    scanf("%d", &jumlahSiswa);

    if (jumlahSiswa <= 0)
    {
        printf("Jumlah siswa harus lebih dari 0.\n");
        return 1;
    }

    siswa daftarSiswa[jumlahSiswa];

    for (int i = 0; i < jumlahSiswa; i++)
    {
        printf("\n=== Input Data Siswa %d ===\n", i + 1);
        MasukkanDataSiswa(daftarSiswa, i, jumlahSiswa);
    }

    printf("\n=== Data Siswa yang Terdaftar ===\n");
    TampilkanDataTabel(daftarSiswa, jumlahSiswa);

    TampilkanSiswaLolos(daftarSiswa, jumlahSiswa);

    int pilihanSort;
    printf("Pilih kriteria pengurutan (1: NISN\n2: Nama\n3: Alamat\n4: Nilai): \n");
    scanf("%d", &pilihanSort);
    int urutan;
    printf("Pilih urutan (1: ascending\n-1: descending): ");
    scanf("%d", &urutan);

    SelectionSort(daftarSiswa, jumlahSiswa, pilihanSort, urutan);

    printf("\nData Siswa Setelah Diurutkan:\n");
    for (int i = 0; i < jumlahSiswa; i++)
    {
        CetakData(daftarSiswa[i]);
        printf("\n");
    }

    return 0;
}
