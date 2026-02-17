# Tucil1 - N-Queens Solver dengan Colored Board

Program ini menyelesaikan masalah **N-Queens** pada papan berwarna berukuran N×N, di mana setiap baris dan kolom memiliki warna yang unik.

## Deskripsi Masalah

Masalah N-Queens adalah masalah klasik dalam ilmu komputer di mana tujuannya adalah menempatkan N ratu pada papan catur N×N sedemikian rupa sehingga tidak ada dua ratu yang dapat saling menyerang. Dalam variasi ini, papan terdiri dari warna-warna berbeda (A-Z).

**Batasan:**
- Tidak ada dua ratu dalam baris yang sama
- Tidak ada dua ratu dalam kolom yang sama
- Tidak ada dua ratu yang saling bersebelahan (termasuk diagonal)
- Tidak ada dua ratu dengan warna papan yang sama

## Struktur Direktori

```
tucil1/
├── bin/              # Folder untuk executable (.exe)
├── docs/             # Dokumentasi
├── src/
│   └── queens.cpp    # Source code utama
└── test/
    ├── tc1.txt - tc5.txt     # Test case input
    └── solusitc1.txt - solusitc5.txt # Expected output
```

## Cara Kompilasi

Gunakan g++ dengan output ke folder `bin/`:

```bash
g++ -o bin/queens src/queens.cpp
```

Atau untuk Windows dengan ekstensi .exe:

```bash
g++ -o bin/queens.exe src/queens.cpp
```

## Cara Menjalankan

### Dari root folder:
```bash
./bin/queens
```

atau (Windows):
```bash
bin\queens.exe
```

### Program akan meminta:
1. **Input file**: Masukkan path ke file test case (contoh: `test/tc1.txt`)
2. **Opsi simpan**: Setelah solusi ditemukan, pilih untuk menyimpan ke file `.txt`

## Input Format

File input harus memenuhi kriteria:
- **Format**: File `.txt` dengan N baris dan N kolom
- **Karakter**: Uppercase letters (A-Z)
- **Ukuran**: Maks 26×26 (karena hanya ada 26 letter)
- **Validasi**:
  - Setiap baris harus memiliki panjang yang sama
  - Setiap warna harus muncul tepat N kali (sekali per baris dan kolom)
  - Tidak boleh ada spasi atau karakter tidak valid

### Contoh Input (`tc1.txt`):
```
AAABBCCCD
ABBBBCECD
ABBBDCECD
AAABDCCCD
BBBBDDDDD
FGGGDDHDD
FGIGDDHDD
FGIGDDHDD
FGGGDDHHH
```

## Output Format

Program akan mencari solusi dan menampilkan:

1. **Board dengan penempatan ratu** (ditandai dengan `#`)
2. **Jumlah iterasi** yang dilakukan
3. **Waktu eksekusi** dalam millisecond

### Contoh Output (disimpan ke file `.txt`):
```
A A B B C C C D
A B B B B C E C D
A B B B D C E C D
A A A B D C C C D
B B B B D D D D D
F G G G D D H D D
F G I G D D H D D
F G I G D D H D D
F G G G D D H # H

Iterasi: 362880
Waktu eksekusi: 1234.56 ms
```

## Validasi File Input

Program melakukan validasi berikut:

| Validasi | Error Message |
|----------|---------------|
| File tidak ditemukan | `File tidak ditemukan` |
| Format file bukan .txt | `Format file tidak valid` |
| File kosong | `File kosong!` |
| Baris dengan panjang berbeda | `Format input tidak valid` |
| Ukuran bukan square (N×N) | `Board tidak berbentuk persegi (n x n)!` |
| Ada spasi/tab dalam board | `Error: Format papan cacat!` |
| Karakter bukan A-Z | `Error: Karakter tidak valid ditemukan!` |
| Jumlah warna ≠ N | `Jumlah karakter/warna pada papan tidak sesuai dengan ukuran papan` |
| Ukuran melebihi 26×26 | `Ukuran papan melebihi batas maksimal` |

## Validasi Output

Program juga memastikan file output:
- **Hanya menerima ekstensi `.txt`**
- Jika user input tanpa `.txt`, program akan menolak dan meminta input ulang
- File berisi:
  - Board dengan penempatan ratu (`#`)
  - Jumlah iterasi
  - Waktu eksekusi dalam milidetik

## Algoritma

Program menggunakan **Brute Force dengan Backtracking**:

1. Mencoba semua kombinasi penempatan N ratu pada papan N×N
2. Untuk setiap konfigurasi, cek validitas:
   - Tidak ada ratu di kolom yang sama
   - Tidak ada ratu bersebelahan (L-shaped check)
   - Tidak ada ratu dengan warna sama
3. Jika valid, solusi ditemukan
4. Jika tidak, backtrack dan coba kombinasi berikutnya

## Complexity

- **Time Complexity**: O(N!) dalam worst case
- **Space Complexity**: O(N) untuk menyimpan posisi ratu

## Catatan

- Program menggunakan `system("cls")` untuk Windows dan `system("clear")` untuk Linux/Mac
- Setiap 1 juta iterasi, program menampilkan progress ke layar
- Board dari input dipertahankan dan ditampilkan di output (dengan ratu diganti `#`)

## Test Case

Tersedia 5 test case di folder `test/`:
- **tc1.txt**: Valid input 9×9
- **tc2.txt**: Error - jumlah kolom tidak sesuai
- **tc3.txt**: Error - jumlah warna tidak sesuai
- **tc4.txt**: Error - board tidak persegi (non-square)
- **tc5.txt**: Error - format papan cacat (ada spasi)

Jalankan dan bandingkan output dengan file `solusitc1.txt` - `solusitc5.txt`

## Author

Tugas Kecil 1 - IF2211 Strategi Algoritma
Semester 4, 2025/2026