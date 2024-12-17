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
        return 0;
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

int BinarySearchNISN(siswa sk[], int jumlah, int target)
{
    int l = 0, r = jumlah - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (sk[m].nisn == target)
            return m;
        if (sk[m].nisn < target)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

int LinearSearchNama(siswa sk[], int jumlah, char *target)
{
    for (int i = 0; i < jumlah; i++)
    {
        if (strcmp(sk[i].nama, target) == 0)
            return i;
    }
    return -1;
}

int LinearSearchAlamat(siswa sk[], int jumlah, char *target)
{
    for (int i = 0; i < jumlah; i++)
    {
        if (strcmp(sk[i].alamat, target) == 0)
            return i;
    }
    return -1;
}

int LinearSearchNilai(siswa sk[], int jumlah, float target)
{
    for (int i = 0; i < jumlah; i++)
    {
        if (sk[i].nilai == target)
            return i;
    }
    return -1;
}

// Fungsi untuk menginput data siswa dengan validasi
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

// Fungsi untuk menampilkan data siswa dalam bentuk tabel
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

int main()
{
    int jumlahSiswa;

    // Input jumlah siswa
    printf("Masukkan jumlah siswa: ");
    scanf("%d", &jumlahSiswa);

    if (jumlahSiswa <= 0)
    {
        printf("Jumlah siswa harus lebih dari 0.\n");
        return 1;
    }

    siswa daftarSiswa[jumlahSiswa];

    // Input data siswa
    for (int i = 0; i < jumlahSiswa; i++)
    {
        printf("\n=== Input Data Siswa %d ===\n", i + 1);
        MasukkanDataSiswa(daftarSiswa, i, jumlahSiswa);
    }

    // Output data siswa
    printf("\n=== Data Siswa yang Terdaftar ===\n");
    for (int i = 0; i < jumlahSiswa; i++)
    {
        TampilkanDataTabel(daftarSiswa, jumlahSiswa);
    }

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

    int pilihanCari;
    printf("Pilih kriteria pencarian (1: NISN\n2: Nama\n3: Alamat\n4: Nilai): \n");
    scanf("%d", &pilihanCari);

    int posisi = -1;
    if (pilihanCari == 1)
    {
        int nisnDicari;
        printf("Masukkan NISN siswa yang ingin dicari: ");
        scanf("%d", &nisnDicari);
        posisi = BinarySearchNISN(daftarSiswa, jumlahSiswa, nisnDicari);
    }
    else if (pilihanCari == 2)
    {
        char namaDicari[100];
        printf("Masukkan Nama siswa yang ingin dicari: ");
        scanf(" %[^\n]", namaDicari);
        posisi = LinearSearchNama(daftarSiswa, jumlahSiswa, namaDicari);
    }
    else if (pilihanCari == 3)
    {
        char alamatDicari[100];
        printf("Masukkan Alamat siswa yang ingin dicari: ");
        scanf(" %[^\n]", alamatDicari);
        posisi = LinearSearchAlamat(daftarSiswa, jumlahSiswa, alamatDicari);
    }
    else if (pilihanCari == 4)
    {
        float nilaiDicari;
        printf("Masukkan Nilai siswa yang ingin dicari: ");
        scanf("%f", &nilaiDicari);
        posisi = LinearSearchNilai(daftarSiswa, jumlahSiswa, nilaiDicari);
    }

    if (posisi != -1)
    {
        printf("\nSiswa ditemukan:\n");
        CetakData(daftarSiswa[posisi]);
    }
    else
    {
        printf("\nSiswa tidak ditemukan.\n");
    }

    return 0;
}
