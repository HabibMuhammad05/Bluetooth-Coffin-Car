<p align="center">
  <img src="SmartCar_Logo.png" alt="Bluetooth Coffin Car" width="140">
</p>

<h1 align="center">Bluetooth Coffin Car</h1>

<p align="center">
  Kendali kendaraan roda dua motor DC lewat Bluetooth menggunakan Arduino dan driver motor L298N.
</p>

---

## Ringkasan

Repositori ini berisi firmware Arduino untuk kendaraan dua motor DC yang dikendalikan dari ponsel melalui modul Bluetooth serial. Perintah dikirim sebagai teks (`MAJU`, `KIRI`, dan seterusnya), kemudian diterjemahkan menjadi sinyal arah dan PWM ke driver L298N.

Ada empat sketch dengan tujuan berbeda. Firmware utama berada di `L298N_Coffin_Remote_Full`, sedangkan sketch lain dipakai untuk pengujian dan sebagai arsip.

## Komponen

| Komponen | Keterangan |
|---|---|
| Mikrokontroler | Arduino berbasis ATmega328P (Uno/Nano) |
| Driver motor | L298N |
| Motor | 2 motor DC (kiri dan kanan) |
| Komunikasi | Modul Bluetooth serial (HC-05/HC-06), 9600 baud |
| Catu daya | Baterai terpisah untuk motor, ground dihubungkan dengan Arduino |

Modul Bluetooth biasanya bekerja pada logika 3,3 V. Gunakan pembagi tegangan pada jalur Arduino TX ke pin RX modul.

## Pemetaan Pin

Berlaku untuk `L298N_Coffin_Remote_Full`, `Tes_Keranda`, dan `Achive_l298n`.

| Fungsi | Pin Arduino | Pin L298N |
|---|---|---|
| PWM motor 1 | D11 | ENA |
| Arah motor 1 | D13, D12 | IN1, IN2 |
| Arah motor 2 | D8, D10 | IN3, IN4 |
| PWM motor 2 | D9 | ENB |

Bluetooth pada firmware utama memakai `SoftwareSerial` dengan RX di D6 dan TX di D7. Sambungkan TX modul ke D6 dan RX modul ke D7.

Pemetaan pin sketch `l298n_Bluetooth.ino` berbeda:

| Fungsi | Pin Arduino |
|---|---|
| IN1 - IN4 | D2 - D5 |
| ENA, ENB | D6, D7 |
| Bluetooth RX, TX | D8, D9 |

## Struktur Repositori

```
Bluetooth-Coffin-Car/
├── L298N_Coffin_Remote_Full/
│   └── L298N_Coffin_Remote_Full.ino   # Firmware utama
├── Tes_Keranda/
│   └── Tes_Keranda.ino                # Uji gerak motor tanpa Bluetooth
├── Achive_l298n/
│   └── Achive_l298n.ino               # Arsip: eksperimen line follower 3 sensor
├── l298n_Bluetooth.ino                # Versi awal kendali Bluetooth
└── *.png                              # Logo dan ikon panah diagonal
```

## Protokol Perintah

Firmware utama membaca satu string per perintah dan membandingkannya persis, sehingga huruf besar dan kecil berpengaruh.

| Perintah | Aksi | Kecepatan PWM | Durasi |
|---|---|---|---|
| `MAJU` | Maju lurus | 200 | Terus berjalan sampai `STOP` |
| `MUNDUR` | Mundur lurus | 200 | 400 ms lalu berhenti |
| `KANAN` | Belok kanan (hanya motor kiri berputar) | 200 | 250 ms lalu berhenti |
| `KIRI` | Belok kiri (hanya motor kanan berputar) | 200 | 250 ms lalu berhenti |
| `Skan` | Serong kanan (motor kiri 255, kanan 100) | 255 / 100 | 1000 ms lalu berhenti |
| `Skir` | Serong kiri (motor kiri 100, kanan 255) | 100 / 255 | 1000 ms lalu berhenti |
| `STOP` | Berhenti | 0 | - |

Perintah harus dikirim tanpa karakter tambahan di akhir. Jika aplikasi ponsel menambahkan `\n` atau `\r\n`, nonaktifkan opsi tersebut karena string tidak akan cocok.

## Sketch

### L298N_Coffin_Remote_Full

Firmware utama. Gerak maju bersifat kontinu, sedangkan mundur dan belok berupa pulsa pendek agar kendaraan tidak melaju terus setelah satu ketukan tombol. Setiap gerakan dipisah dalam fungsi (`maju`, `mundur`, `kanan`, `kiri`, `serongkanan`, `serongkiri`, `berhenti`) sehingga mudah disesuaikan.

### l298n_Bluetooth

Versi awal dengan lima perintah (`MAJU`, `MUNDUR`, `KANAN`, `KIRI`, `STOP`) pada kecepatan tetap 255. `KANAN` dan `KIRI` memutar kedua motor berlawanan arah sehingga kendaraan berputar di tempat. Semua gerakan kontinu sampai perintah `STOP`.

### Tes_Keranda

Uji motor tanpa Bluetooth. Sketch menjalankan urutan maju, mundur, kanan, kiri, serong kiri, dan serong kanan secara berulang. Gunakan untuk memastikan arah putar dan pemetaan pin benar sebelum memasang modul Bluetooth. Jika arah motor terbalik, tukar kabel motor pada terminal L298N.

### Achive_l298n

Arsip eksperimen line follower dengan tiga sensor digital pada D5 (kanan), D3 (tengah), dan D4 (kiri), memakai `INPUT_PULLUP`. Kecepatan motor 95 sampai 100. Tidak dipakai pada firmware utama.

## Penggunaan

1. Rangkai komponen sesuai pemetaan pin di atas.
2. Buka `Tes_Keranda.ino`, upload, lalu pastikan kedua motor berputar sesuai arah gerak.
3. Upload `L298N_Coffin_Remote_Full.ino`. Lepas sementara kabel modul Bluetooth bila terjadi kegagalan upload.
4. Pasangkan ponsel dengan modul Bluetooth, lalu buka aplikasi terminal Bluetooth serial.
5. Kirim perintah dari tabel protokol. Pantau respons di Serial Monitor pada 9600 baud.

## Keterbatasan

- `readString()` menunggu hingga batas waktu serial (default 1 detik) sebelum perintah diproses, sehingga respons terasa tertunda. Menyetel `bt.setTimeout()` ke nilai kecil, atau membaca per karakter, akan mempercepat respons.
- Mundur dan belok memakai `delay()`, jadi perintah baru tidak terbaca selama gerakan berlangsung.
- Pada `l298n_Bluetooth.ino`, ENB berada di D7 yang bukan pin PWM pada Uno/Nano sehingga motor 2 selalu berjalan penuh.
- Tidak ada pengaman koneksi: bila Bluetooth terputus saat `MAJU`, kendaraan tetap melaju sampai catu daya dimatikan.
