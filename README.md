farmingIoT
Proyek Smart Farming berbasis IoT menggunakan ESP8266, sensor cahaya (LDR), LED, dan buzzer.

Komponen yang Digunakan:
- ESP8266 (NodeMCU)
- Sensor LDR
- LED
- Buzzer
- Koneksi WiFi (Wokwi-GUEST)
- Aplikasi Blynk IoT

Fungsi Utama:
- Membaca intensitas cahaya menggunakan LDR.
- Menampilkan nilai sensor di aplikasi Blynk (Virtual Pin V1).
- Menyalakan LED secara manual dari Blynk (Virtual Pin V0).
- Menyalakan buzzer otomatis jika cahaya terlalu rendah (< 250) dan LED tidak aktif.

File:
- `smart_farming.ino`: Source code utama Arduino.

Cara Pakai:
1. Upload code ke ESP8266 melalui Arduino IDE.
2. Gunakan Blynk dengan token yang sesuai.
3. Monitor sensor dan kontrol LED dari aplikasi.

