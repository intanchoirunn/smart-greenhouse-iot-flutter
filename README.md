# 🌿 Smart Greenhouse - IoT & Mobile Monitoring System

Sistem pemantauan dan pengendalian mikroklimat smart greenhouse berbasis **Internet of Things (IoT)** dan **Aplikasi Mobile**[cite: 1, 2]. Proyek ini mengintegrasikan mikrokontroler ESP32, pemodelan dinamis mikroklimat tanah (*evaporative cooling*), platform cloud Blynk IoT, serta aplikasi Flutter berbasis arsitektur 3-Layer[cite: 1, 2].

---

## 📌 Fitur Utama

- **Real-Time Environmental Monitoring:** Pemantauan parameter suhu udara (°C), kelembaban udara (%RH), dan kelembaban tanah (%) secara berkala[cite: 1, 2].
- **Dual Control Mode:**
  - **Mode Manual:** Kontrol on/off aktuator pompa penyiraman secara langsung via antarmuka pengguna[cite: 1, 2].
  - **Mode Otomatis (Threshold-Based):** Pompa aktif otomatis saat kelembaban tanah <= 30% dan mati saat kelembaban >= 80%[cite: 1, 2].
- **Evaporative Cooling Simulation:** Simulasi dinamika fisika tanah di mana kelembaban memengaruhi suhu dan kelembaban udara sekitar[cite: 1].
- **Alert System:** Notifikasi visual status darurat saat tingkat kelembaban tanah kritis (< 15%)[cite: 1, 2].

---

## 🏗️ Arsitektur Sistem

- **Hardware Layer (Wokwi):** ESP32, Sensor DHT22, LED Indikator Pompa & Alert[cite: 1].
- **Cloud Layer (Blynk 2.0):** Datastream Virtual Pin (V0–V5), Web Dashboard, dan HTTP REST API[cite: 1, 2].
- **Application Layer (Flutter):** Implementasi 3-Layer Architecture (UI Layer -> State Layer -> Service Layer)[cite: 2].

---

## 🔌 Pemetaan Datastream (Virtual Pin)

| Pin | Parameter | Tipe Data | Rentang / Nilai | Fungsi |
| :---: | :--- | :---: | :---: | :--- |
| **V0** | Suhu Udara | Double | 0 - 50 °C | Telemetri suhu lingkungan[cite: 1] |
| **V1** | Kelembaban Udara | Double | 0 - 100 % | Telemetri kelembaban udara[cite: 1] |
| **V2** | Kelembaban Tanah | Double | 0 - 100 % | Estimasi tingkat kebasahan tanah[cite: 1] |
| **V3** | Kontrol Pompa | Integer | 0 (OFF) / 1 (ON) | Perintah manual saklar pompa[cite: 1] |
| **V4** | Mode Otomatis | Integer | 0 (Manual) / 1 (Auto) | Toggle sistem otomasi[cite: 1] |
| **V5** | Status Pompa | Integer | 0 (Mati) / 1 (Aktif) | Umpan balik status aktual pompa[cite: 1] |

---

## 🛠️ Tech Stack & Tools

- **Firmware:** C++ / Arduino Framework, Blynk Library, DHTesp[cite: 1]
- **Simulator:** Wokwi Electronic Simulator[cite: 1]
- **Cloud IoT:** Blynk 2.0 Cloud Platform[cite: 1]
- **Mobile Development:** Flutter, Dart, http package[cite: 2]
- **Architecture Pattern:** 3-Layer Separation of Concerns (Service, State, UI)[cite: 2]
