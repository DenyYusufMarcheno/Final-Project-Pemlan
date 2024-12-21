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

void editSiswa(siswa *s)
{
    printf("Mengedit data siswa dengan NISN: %d\n", s->nisn);
    printf("Nama baru: ");
    scanf(" %[^\n]", s->nama);
    printf("Alamat baru: ");
    scanf(" %[^\n]", s->alamat);
    printf("Jenis kelamin baru (L/P): ");
    scanf(" %c", &s->jenisKelamin);
    printf("Nilai baru: ");
    scanf("%f", &s->nilai);
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

int BinarySearch(siswa arr[], int jumlah, void *key, int pilihan)
{
    int kiri = 0, kanan = jumlah - 1, tengah;
    while (kiri <= kanan)
    {
        tengah = (kiri + kanan) / 2;
        int hasilBanding = 0;

        switch (pilihan)
        {
        case 1:
            hasilBanding = (*(int *)key - arr[tengah].nisn);
            break;

        case 2:
            hasilBanding = strcmp((char *)key, arr[tengah].nama);
            break;

        case 3:
            if (*(float *)key < arr[tengah].nilai)
                hasilBanding = -1;
            else if (*(float *)key > arr[tengah].nilai)
                hasilBanding = 1;
            else
                hasilBanding = 0;
            break;

        default:
            return -1;
        }

        if (hasilBanding == 0)
            return tengah;
        else if (hasilBanding < 0)
            kanan = tengah - 1;
        else
            kiri = tengah + 1;
    }
    return -1;
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

void HapusSiswa(siswa daftarSiswa[], int *jumlah)
{
    if (*jumlah == 0)
    {
        printf("Tidak ada data siswa untuk dihapus.\n");
        return;
    }

    int nisn;
    printf("Masukkan NISN siswa yang akan dihapus: ");
    scanf("%d", &nisn);

    int indeks = -1;
    for (int i = 0; i < *jumlah; i++)
    {
        if (daftarSiswa[i].nisn == nisn)
        {
            indeks = i;
            break;
        }
    }

    if (indeks == -1)
    {
        printf("Siswa dengan NISN %d tidak ditemukan.\n", nisn);
        return;
    }

    // Menghapus dengan menggeser elemen
    for (int i = indeks; i < *jumlah - 1; i++)
    {
        daftarSiswa[i] = daftarSiswa[i + 1];
    }
    (*jumlah)--;

    printf("Siswa dengan NISN %d berhasil dihapus.\n", nisn);
}


void SimpanKeFile(siswa daftarSiswa[], int jumlah)
{
    FILE *file = fopen("data_siswa.txt", "w");
    if (file == NULL)
    {
        printf("Gagal membuka file untuk menyimpan data.\n");
        return;
    }

    fprintf(file, "%d\n", jumlah); // Simpan jumlah siswa
    for (int i = 0; i < jumlah; i++)
    {
        fprintf(file, "%d|%s|%s|%c|%.2f\n",
                daftarSiswa[i].nisn, daftarSiswa[i].nama,
                daftarSiswa[i].alamat, daftarSiswa[i].jenisKelamin,
                daftarSiswa[i].nilai);
    }

    fclose(file);
    printf("Data berhasil disimpan ke file.\n");
}

int MuatDariFile(siswa daftarSiswa[], int *jumlah)
{
    FILE *file = fopen("data_siswa.txt", "r");
    if (file == NULL)
    {
        printf("Tidak ada file data sebelumnya. Memulai dengan data kosong.\n");
        *jumlah = 0;
        return 0;
    }

    fscanf(file, "%d\n", jumlah); // Baca jumlah siswa
    for (int i = 0; i < *jumlah; i++)
    {
        fscanf(file, "%d|%[^|]|%[^|]|%c|%f\n",
               &daftarSiswa[i].nisn, daftarSiswa[i].nama,
               daftarSiswa[i].alamat, &daftarSiswa[i].jenisKelamin,
               &daftarSiswa[i].nilai);
    }

    fclose(file);
    printf("Data berhasil dimuat dari file.\n");
    return 1;
}

int main()
{
    int jumlahSiswa = 0;
    siswa daftarSiswa[100];

    // Memuat data dari file
    MuatDariFile(daftarSiswa, &jumlahSiswa);

    int pilihanMenu;
    do
    {
        printf("\n=== Menu Utama ===\n");
        printf("1. Tampilkan Data Siswa\n");
        printf("2. Tambahkan Data Siswa Baru\n");
        printf("3. Edit Data Siswa\n");
        printf("4. Urutkan Data Siswa\n");
        printf("5. Cari Siswa\n");
        printf("6. Tampilkan Siswa yang Lolos\n");
        printf("7. Simpan dan Keluar\n");
        printf("8. Hapus Data Siswa\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihanMenu);

        switch (pilihanMenu)
        {
        case 1:
            printf("\n=== Data Siswa yang Terdaftar ===\n");
            TampilkanDataTabel(daftarSiswa, jumlahSiswa);
            break;

        case 2:
            if (jumlahSiswa < 100)
            {
                jumlahSiswa++;
                printf("\n=== Input Data Siswa Baru ===\n");
                MasukkanDataSiswa(daftarSiswa, jumlahSiswa - 1, jumlahSiswa);
            }
            else
            {
                printf("Kapasitas maksimum data siswa tercapai.\n");
            }
            break;

        case 3:
            if (jumlahSiswa == 0)
            {
                printf("Tidak ada data siswa yang dapat diedit.\n");
                break;
            }
            int nisn;
            printf("Masukkan NISN siswa yang ingin diedit: ");
            scanf("%d", &nisn);
            int indeks = -1;
            for (int i = 0; i < jumlahSiswa; i++)
            {
                if (daftarSiswa[i].nisn == nisn)
                {
                    indeks = i;
                    break;
                }
            }
            if (indeks != -1)
            {
                printf("\n=== Edit Data Siswa ===\n");
                editSiswa(&daftarSiswa[indeks]); // Panggil fungsi editSiswa
            }
            else
            {
                printf("Siswa dengan NISN %d tidak ditemukan.\n", nisn);
            }
            break;

        case 4:
        {
            int pilihanSort, urutan;
            printf("Pilih kriteria pengurutan (1: NISN, 2: Nama, 3: Alamat, 4: Nilai): ");
            scanf("%d", &pilihanSort);
            printf("Pilih urutan (1: ascending, -1: descending): ");
            scanf("%d", &urutan);

            SelectionSort(daftarSiswa, jumlahSiswa, pilihanSort, urutan);
            printf("\n=== Data Siswa Setelah Diurutkan ===\n");
            TampilkanDataTabel(daftarSiswa, jumlahSiswa);
            break;
        }

        case 5:
        {
            if (jumlahSiswa == 0)
            {
                printf("Tidak ada data siswa yang dapat dicari.\n");
                break;
            }
            int kriteria;
            printf("\nPilih kriteria pencarian (1: NISN, 2:Nama, 3:Nilai): ");
            scanf("%d", &kriteria);

            if (kriteria == 1)
            {
                int cariNISN;
                printf("Masukkan NISN yang ingin dicari: ");
                scanf("%d", &cariNISN);

                SelectionSort(daftarSiswa, jumlahSiswa, 1, 1);

                int hasilCari = BinarySearch(daftarSiswa, jumlahSiswa, &cariNISN, 1);
                if (hasilCari != -1)
                {
                    printf("\nSiswa ditemukan:\n");
                    CetakData(daftarSiswa[hasilCari]);
                }
                else
                {
                    printf("Siswa dengan NISN %d tidak ditemukan.\n", cariNISN);
                }
            }
            else if (kriteria == 2)
            {
                char cariNama[100];
                printf("Masukkan Nama yang ingin dicari: ");

                while (getchar() != '\n')
                    ; // Membersihkan buffer input

                fgets(cariNama, sizeof(cariNama), stdin);
                cariNama[strcspn(cariNama, "\n")] = '\0'; // Menghapus newline di akhir input

                SelectionSort(daftarSiswa, jumlahSiswa, 2, 1);

                int hasilCari = BinarySearch(daftarSiswa, jumlahSiswa, cariNama, 2);
                if (hasilCari != -1)
                {
                    printf("\nSiswa ditemukan:\n");
                    CetakData(daftarSiswa[hasilCari]);
                }
                else
                {
                    printf("Siswa dengan nama \"%s\" tidak ditemukan.\n", cariNama);
                }
            }

            else if (kriteria == 3)
            {
                float cariNilai;
                printf("Masukkan nilai yang ingin dicari: ");
                scanf("%f", &cariNilai);

                SelectionSort(daftarSiswa, jumlahSiswa, 4, 1);

                int hasilCari = BinarySearch(daftarSiswa, jumlahSiswa, &cariNilai, 3);
                if (hasilCari != -1)
                {
                    printf("\nSiswa ditemukan:\n");
                    CetakData(daftarSiswa[hasilCari]);
                }
                else
                {
                    printf("Siswa dengan nilai %.2f tidak ditemukan.\n", cariNilai);
                }
            }

            break;
        }

        case 6:
            TampilkanSiswaLolos(daftarSiswa, jumlahSiswa);
            break;
        
        case 7:
            printf("\n=== Hapus Data Siswa ===\n");
            HapusSiswa(daftarSiswa, &jumlahSiswa);
            break;
            
        case 8:
            SimpanKeFile(daftarSiswa, jumlahSiswa);
            printf("Keluar dari program.\n");
            break;

        default:
            printf("Pilihan tidak valid. Silakan pilih lagi.\n");
        }
    } while (pilihanMenu != 8);

    return 0;
}
