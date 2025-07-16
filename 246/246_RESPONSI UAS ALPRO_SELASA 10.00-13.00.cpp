#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int MAX_BARANG = 999;

struct Transaksi {
    string kodeProduk;
    string namaProduk;
    int jumlahDibeli;
    double harga;
};

Transaksi transaksi[MAX_BARANG];
int jumlahTransaksi = 0;

void inputTransaksi() {
    ifstream file("transaksi.txt");
    if (!file) {
        cout << "File tidak dapat dibaca!" << endl;
        return;
    }

    string baris;
    while (getline(file, baris)) {
        if (jumlahTransaksi >= MAX_BARANG) break;

        stringstream ss(baris);
        getline(ss, transaksi[jumlahTransaksi].kodeProduk, ',');
        getline(ss, transaksi[jumlahTransaksi].namaProduk, ',');
        ss >> transaksi[jumlahTransaksi].jumlahDibeli;
        ss.ignore(); // untuk melewati koma
        ss >> transaksi[jumlahTransaksi].harga;

        jumlahTransaksi++;
    }

    file.close();
}

void cariBarangByKode(string kode) {
    bool ketemu = false;
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (transaksi[i].kodeProduk == kode) {
            cout << "Kode Produk: " << transaksi[i].kodeProduk
                 << ", Nama Produk: " << transaksi[i].namaProduk
                 << ", Jumlah: " << transaksi[i].jumlahDibeli
                 << ", Harga: " << transaksi[i].harga << endl;
            ketemu = true;
            break;
        }
    }
    if (!ketemu) {
        cout << "Produk dengan kode " << kode << " tidak ditemukan!" << endl;
    }
}

void cariBarangTermurah() {
    double hargaTermurah = transaksi[0].harga;
    int indexTermurah = 0;

    for (int i = 1; i < jumlahTransaksi; i++) {
        if (transaksi[i].harga < hargaTermurah) {
            hargaTermurah = transaksi[i].harga;
            indexTermurah = i;
        }
    }

    cout << "Barang termurah: " << transaksi[indexTermurah].namaProduk
         << ", Harga: " << transaksi[indexTermurah].harga << endl;
}

void sortirHargaDesc() {
    for (int i = 0; i < jumlahTransaksi - 1; i++) {
        for (int j = 0; j < jumlahTransaksi - i - 1; j++) {
            if (transaksi[j].harga < transaksi[j + 1].harga) {
                swap(transaksi[j], transaksi[j + 1]);
            }
        }
    }

    cout << "Produk termahal ke termurah: " << endl;
    for (int i = 0; i < jumlahTransaksi; i++) {
        cout << transaksi[i].namaProduk << " - " << transaksi[i].harga << endl;
    }
}

void sortirHargaAsc() {
    for (int i = 0; i < jumlahTransaksi - 1; i++) {
        for (int j = 0; j < jumlahTransaksi - i - 1; j++) {
            if (transaksi[j].harga > transaksi[j + 1].harga) {
                swap(transaksi[j], transaksi[j + 1]);
            }
        }
    }

    cout << "Produk termurah ke termahal: " << endl;
    for (int i = 0; i < jumlahTransaksi; i++) {
        cout << transaksi[i].namaProduk << " - " << transaksi[i].harga << endl;
    }
}

void totalPendapatanPerProduk() {
    cout << "Total Pendapatan per Produk: " << endl;
    for (int i = 0; i < jumlahTransaksi; i++) {
        double totalPendapatan = transaksi[i].jumlahDibeli * transaksi[i].harga;
        cout << "Produk: " << transaksi[i].namaProduk
             << ", Total Pendapatan: " << totalPendapatan << endl;
    }
}

void totalPendapatanToko() {
    double totalPendapatan = 0;
    for (int i = 0; i < jumlahTransaksi; i++) {
        totalPendapatan += transaksi[i].jumlahDibeli * transaksi[i].harga;
    }
    cout << "Total Pendapatan Toko: " << totalPendapatan << endl;
}

void simpanAnalisis() {
    ofstream file("hasil_analisis_penjualan.txt");
    for (int i = 0; i < jumlahTransaksi; i++) {
        double totalPendapatan = transaksi[i].jumlahDibeli * transaksi[i].harga;
        file << transaksi[i].kodeProduk << ", "
             << transaksi[i].namaProduk << ", "
             << transaksi[i].jumlahDibeli << ", "
             << transaksi[i].harga << ", "
             << totalPendapatan << endl;
    }
    file.close();
    cout << "Hasil analisis disimpan di hasil_analisis_penjualan.txt" << endl;
}

void menu() {
    int pilihan;
    do {
        cout << "===== MENU PROGRAM =====" << endl;
        cout << "1. Input Data Transaksi" << endl;
        cout << "2. Cari Barang Berdasarkan Kode Produk" << endl;
        cout << "3. Cari Barang Termurah" << endl;
        cout << "4. Urutkan Produk Termahal ke Termurah" << endl;
        cout << "5. Urutkan Produk Termurah ke Termahal" << endl;
        cout << "6. Hitung Total Pendapatan per Produk" << endl;
        cout << "7. Hitung Total Pendapatan Toko" << endl;
        cout << "8. Simpan Hasil Analisis" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilihan anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                inputTransaksi();
                break;
            case 2:
                {
                    string kode;
                    cout << "Masukkan kode produk: ";
                    cin >> kode;
                    cariBarangByKode(kode);
                    break;
                }
            case 3:
                cariBarangTermurah();
                break;
            case 4:
                sortirHargaDesc();
                break;
            case 5:
                sortirHargaAsc();
                break;
            case 6:
                totalPendapatanPerProduk();
                break;
            case 7:
                totalPendapatanToko();
                break;
            case 8:
                simpanAnalisis();
                break;
            case 9:
                exit(0);
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    } while (true);
}

int main() {
    menu();
    return 0;
}

