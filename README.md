# Sisop-5-2025-IT-Template

## Kelompok

Nama | NRP
--- | ---
Theodorus Aaron Ugraha | 5027241056
Muhammad Afrizan Rasya | 5027241048
Salomo | 5027221063

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

8. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/0f580958-16d7-4322-8a09-98f521d21135

## Laporan

> Isi sesuai pengerjaan.

Disini kami akan memaparkan pengerjaan soal SISOP modul 5, di bawah adalah penjelasannya :

### shell.h

Jadi di file ini kami menambahkan 3 fungsi yaitu :
- void running : bertanggung jawab untuk mengeksekusi perintah yang diterima dari input shell.
- void userName : digunakan untuk mengelola nama pengguna (username) dalam shell.
- void generateRsponse : bertugas untuk menghasilkan respons atau umpan balik dari shell setelah suatu perintah dijalankan.

### kernel.c

1. Fungsi main

Fungsi:
* Membersihkan layar (clearScreen) dengan skema warna putih (0x0F).
* Memanggil fungsi shell() untuk menjalankan shell interaktif.

2. Fungsi printString

Fungsi: Mencetak string ke layar menggunakan interrupt BIOS 0x10 (servis video).
* Cara Kerja:
  * Loop melalui setiap karakter hingga menemukan null terminator (\0).
  * Menggunakan interrupt 0x10 dengan kode 0x0E00 (cetak karakter dalam mode teks).

3. Fungsi readString

Fungsi: Membaca input dari keyboard dan menyimpannya ke buffer.
* Fitur:
  * Mendukung backspace (0x08) untuk menghapus karakter.
  * Mengabaikan karakter non-ASCII (hanya menerima 32-126).
  * Menambahkan \r\n (Enter) dan null terminator (\0) di akhir string.
  * Input maksimal 126 karakter (untuk mencegah overflow).

4. Fungsi clearScreen

Fungsi: Membersihkan layar dan mengatur skema warna.
* Cara Kerja:
  * Menulis spasi (' ') ke seluruh memori video 0xB800 (mode teks 80x25).
  * Setiap karakter diikuti byte atribut warna (colorScheme).
  * Menggunakan interrupt 0x10 servis 0x0200 untuk memindahkan cursor ke awal.

### shell.c

1. Variabel Global
* currentUser[64]: Menyimpan nama pengguna (default: "user").
* serverName[64]: Menyimpan suffix server (kosong default).
* displayColor: Skema warna tampilan (default: 0x0F/putih).

2. Fungsi shell()
* Fungsi Utama: Loop tak terbatas untuk menerima input pengguna.
* Alur:
1. Tampilkan prompt (userName).
2. Baca input (readString).
3. Parsing input (parseCommand).
4. Eksekusi perintah (running).

3. Fungsi userName()
* Tugas: Menampilkan prompt shell (format: username@serverName$ ).
* Contoh Output:
  * user$ (jika serverName kosong).
  * user@Storm$ (jika serverName diisi).

4. Fungsi parseCommand()
* Tugas: Memisahkan input menjadi:
  * command: Perintah utama (kata pertama).
  * params[2][64]: Dua parameter (opsional).
* Contoh:
  Input "add 5 3" →
  command = "add", params[0] = "5", params[1] = "3".

5. Fungsi running()
* Tugas: Mengeksekusi perintah yang di-parsing.
* Daftar Perintah:
  * yo/gurt: Menampilkan pesan balik ("yo" ↔ "gurt").
  * user <name>: Mengganti currentUser.
  * grandcompany <nama>
* clear: Reset serverName dan warna ke default.
* Operasi Aritmetika:
  * add/sub/mul/div <n1> <n2>: Menghitung hasil operasi.
  * Validasi pembagian oleh nol (div).
* info: Menampilkan informasi sistem (termasuk currentUser).
* yogurt: Memanggil generateResponse() untuk respons acak.
* help: Menampilkan daftar perintah.

6. Fungsi generateResponse()

Tugas: Menampilkan pesan acak berdasarkan nilai tick BIOS:
* Contoh output: "yo", "sygau", atau "ts unami gng </3".

### std_lib.c

1. Fungsi Matematika

` div(int dividend, int divisor) `
* Fungsi: Membagi dua bilangan integer (pembagian lantai).
* Fitur:
  * Menangani pembagian oleh nol (return 0).
  * Mendukung bilangan negatif (hasil sesuai tanda).
  * Menggunakan loop pengurangan untuk menghitung hasil.

` mod(int dividend, int divisor) `
* Fungsi: Menghitung modulus menggunakan div().
* Perbedaan dari safe_mod:
  * Lebih efisien dan menangani divisor 0 (return 0).

2. Fungsi String

` strcmp(char *firstStr, char *secondStr) `
* Fungsi: Membandingkan dua string.
` strcpy(char *destination, char *source) `
* Fungsi: Menyalin string dari source ke destination.
` clear(byte *buffer, unsigned int bufferSize) `
* Fungsi: Mengosongkan buffer dengan mengisi 0.

3. Konversi Tipe

` atoi(char *inputStr, int *resultNum) `
Fungsi: Konversi string ke integer.

` itoa(int inputNum, char *outputStr) `
Fungsi: Konversi integer ke string.

### MAKEFILE

1. prepare
* Membuat direktori bin/ jika belum ada
* Membuat image floppy disk kosong (floppy.img) berukuran 1.44MB (2880 sector × 512 byte)

2. bootloader
* Mengompilasi bootloader (Assembly) dengan NASM ke bootloader.bin
* Menulis bootloader ke sector pertama floppy image

3. stdlib
* Mengompilasi library standar (C) dengan BCC (Bruce's C Compiler)

4. shell
* Mengompilasi shell (C) dengan BCC

5. kernel
* Mengompilasi kernel (C + Assembly) dengan BCC dan NASM

6. link
* Melakukan linking semua komponen kernel (kernel.o, shell.o, std_lib.o) menjadi kernel.bin
* Menulis kernel ke floppy image mulai dari sector kedua (seek=1)
