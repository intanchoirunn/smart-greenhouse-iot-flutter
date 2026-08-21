# 🌱 Smart Plant Monitoring & Automatic Watering System

Sistem cerdas berbasis IoT dan Aplikasi Mobile untuk memantau kondisi lingkungan serta mengatur penyiraman tanaman secara otomatis.

Alat ini membaca suhu udara, kelembaban udara, dan tingkat kebasahan tanah, lalu dapat mengaktifkan pompa penyiraman secara otomatis jika kondisi tanah mulai mengering.

---

## 📌 Fitur Utama

- **Pemantauan Lingkungan Real-Time:** Menampilkan data suhu udara, kelembaban udara, dan kelembaban tanah secara langsung di layar smartphone atau komputer.
- **Dua Mode Kendali:**
  - **Mode Manual:** Menyalakan dan mematikan pompa penyiraman kapan saja melalui antarmuka aplikasi/web.
  - **Mode Otomatis:** Pompa otomatis menyala saat tanah kering (<= 30%) dan otomatis mati saat tanah sudah cukup basah (>= 80%).
- **Simulasi Respon Lingkungan:** Pemodelan perubahan suhu dan kelembaban udara sekitar saat kondisi tanah basah setelah penyiraman.
- **Indikator Peringatan:** Indikator visual menyala saat kondisi kelembaban tanah mencapai level kritis (< 15%).

---

## 🏗️ Cara Kerja Sistem

1. **ESP32 & Sensor:** Mengambil data parameter lingkungan dan mengontrol aktif/tidaknya pompa penyiram.
2. **Blynk Cloud Platform:** Mengalirkan data sensor dan menerima perintah kontrol melalui jaringan internet.
3. **Aplikasi Mobile (Flutter):** Antarmuka pengguna untuk melihat visualisasi data sensor dan tombol kontrol pompa.

---

## 🔌 Daftar Saluran Data (Virtual Pin Blynk)

| Pin | Data Parameter | Fungsi |
| :---: | :--- | :--- |
| **V0** | Suhu Udara (°C) | Menampilkan suhu lingkungan tanaman |
| **V1** | Kelembaban Udara (%) | Menampilkan tingkat kelembaban udara |
| **V2** | Kelembaban Tanah (%) | Menampilkan persentase kadar air dalam tanah |
| **V3** | Saklar Pompa | Perintah manual menyalakan/mematikan pompa |
| **V4** | Mode Otomatis | Mengaktifkan/menonaktifkan logika penyiraman otomatis |
| **V5** | Status Pompa | Konfirmasi status aktual pompa (menyala/mati) |

---

## 🛠️ Teknologi yang Digunakan

- **Mikrokontroler & Firmware:** ESP32, C++ / Arduino Framework
- **Simulasi Perangkat:** Wokwi Electronic Simulator
- **Platform Cloud IoT:** Blynk 2.0
- **Pengembangan Aplikasi:** Flutter & Dart
