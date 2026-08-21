//  Smart Greenhouse — Firmware ESP32 
//  Politeknik Negeri Banyuwangi - Teknologi Rekayasa Komputer 
// ============================================================ 
 
#define BLYNK_TEMPLATE_ID "TMPL68sEyKs6d"
#define BLYNK_TEMPLATE_NAME "Smart Green House"
#define BLYNK_AUTH_TOKEN "bn1R-hzgDylcjLEGhpDt84vnWABadRfk"
#define BLYNK_PRINT Serial 
 
#include <WiFi.h> 
#include <WiFiClient.h> 
#include <BlynkSimpleEsp32.h>    
#include <DHTesp.h> 
 
// WiFi Wokwi (tidak perlu diubah) 
char ssid[] = "Wokwi-GUEST"; 
char pass[] = ""; 

// Definisi Pin 
const int DHT_PIN       = 15; 
const int PUMP_LED_PIN  = 26; 
const int ALERT_LED_PIN = 33;   
 
DHTesp     dhtSensor; 
BlynkTimer timer; 
 
// Variabel simulasi dinamis 
float soilMoisture    = 25.0f;   // Mulai dari kondisi KERING 
float baseTemp        = 32.0f; 
float baseHumidity    = 55.0f; 
float displayTemp     = 32.0f; 
float displayHumidity = 55.0f; 
bool  pumpStatus      = false; 
bool  autoMode        = false; 
 
// Update simulasi setiap 1 detik 
void updateSimulation() { 
  // Update kelembaban tanah 
  if (pumpStatus) { 
    soilMoisture += 0.5f; 
    if (soilMoisture > 95.0f) soilMoisture = 95.0f; 
  } else { 
    soilMoisture -= 0.08f; 
    if (soilMoisture < 5.0f) soilMoisture = 5.0f; 
  } 
 
  // Logika Mode Auto (threshold-based) modifikasi latihan 1
  if (autoMode) { 
    if (soilMoisture <= 40.0f && !pumpStatus) {  // sebelumnya 30
      pumpStatus = true; 
      Serial.println("[AUTO] Pompa ON  <- Tanah kering (<=40%)"); 
    } else if (soilMoisture >= 70.0f && pumpStatus) {  // sebelumnya 80
      pumpStatus = false; 
      Serial.println("[AUTO] Pompa OFF <- Tanah lembab (>=70%)"); 
    } 
  } 
 
  // Efek Evaporative Cooling 
  float effect      = (soilMoisture - 50.0f) / 100.0f; 
  displayTemp       = baseTemp     - (effect * 8.0f); 
  displayHumidity   = baseHumidity + (effect * 30.0f); 
  displayTemp       = constrain(displayTemp,     20.0f, 45.0f); 
  displayHumidity   = constrain(displayHumidity, 30.0f, 99.0f); 
 
  // Kontrol LED fisik 
  digitalWrite(PUMP_LED_PIN,  pumpStatus           ? HIGH : LOW); 
  digitalWrite(ALERT_LED_PIN, soilMoisture < 15.0f ? HIGH : LOW); 
} 
 
// Kirim data ke Blynk setiap 2 detik  modifikasi latihan 3
void sendToBlynk() { 
  Blynk.virtualWrite(V0, displayTemp); 
  Blynk.virtualWrite(V1, displayHumidity); 
  Blynk.virtualWrite(V2, soilMoisture); 
  Blynk.virtualWrite(V5, pumpStatus ? 1 : 0);

  // implementasi latihan 3
  int alertStatus = (soilMoisture < 15.0f) ? 1 : 0;
  Blynk.virtualWrite(V6, alertStatus); // mengirim status alert ke datastream v6

  Serial.printf("[DATA] Suhu=%.1fC | Udara=%.1f%% | Tanah=%.1f%% | Pompa=%s | Alert=%d\n", 
  displayTemp, displayHumidity, soilMoisture, pumpStatus ? "ON" : "OFF", alertStatus);
} 
 
// Callback: menerima kontrol pompa dari Flutter (V3) 
BLYNK_WRITE(V3) { 
  if (!autoMode) { 
    pumpStatus = (param.asInt() == 1); 
    Serial.printf("[MANUAL] Pompa: %s\n", pumpStatus ? "ON" : "OFF"); 
  } else { 
    Serial.println("[MANUAL] Diabaikan — Mode Auto aktif"); 
  } 
} 
 
// Callback: menerima mode auto dari Flutter (V4) 
BLYNK_WRITE(V4) { 
  autoMode = (param.asInt() == 1); 
  Serial.printf("[CONFIG] Mode Auto: %s\n", autoMode ? "AKTIF" : "OFF"); 
} 
 
// Callback: saat koneksi Blynk berhasil/reconnect 
BLYNK_CONNECTED() { 
  Serial.println("[BLYNK] Terhubung ke Blynk Cloud!"); 
  Blynk.syncVirtual(V3);  
  Blynk.syncVirtual(V4);  
} 
 
void setup() { 
  Serial.begin(115200); 
  delay(500); 
  Serial.println("\n=== Smart Greenhouse Booting... ==="); 
 
  pinMode(PUMP_LED_PIN,  OUTPUT); 
  pinMode(ALERT_LED_PIN, OUTPUT); 
  digitalWrite(PUMP_LED_PIN,  LOW); 
  digitalWrite(ALERT_LED_PIN, LOW); 
  Serial.println("[OK] Pin LED diinisialisasi"); 
 
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22); 
  Serial.println("[OK] DHT22 diinisialisasi, menunggu 2 detik..."); 
  delay(2000); 
 
  TempAndHumidity data = dhtSensor.getTempAndHumidity(); 
  if (!isnan(data.temperature) && data.temperature > 0.0f) { 
    baseTemp     = data.temperature; 
    baseHumidity  = data.humidity; 
    Serial.printf("[OK] DHT22 terbaca: Suhu=%.1fC, Hum=%.1f%%\n", 
                  baseTemp, baseHumidity); 
  } else { 
    Serial.println("[WARN] DHT22 gagal dibaca, pakai nilai default"); 
  } 

  displayTemp     = baseTemp; 
  displayHumidity = baseHumidity; 
 
  Serial.printf("[WIFI] Menghubungkan ke '%s'", ssid); 
  WiFi.begin(ssid, pass); 
  int wifiTry = 0; 
  while (WiFi.status() != WL_CONNECTED && wifiTry < 20) { 
    delay(500); 
    Serial.print("."); 
    wifiTry++; 
  } 

  if (WiFi.status() == WL_CONNECTED) { 
    Serial.printf("\n[WIFI] Terhubung! IP: %s\n", 
                  WiFi.localIP().toString().c_str()); 
  } else { 
    Serial.println("\n[WIFI] Gagal, mencoba via Blynk..."); 
  } 
 
  Serial.println("[BLYNK] Menghubungkan ke Blynk Cloud..."); 
  Blynk.config(BLYNK_AUTH_TOKEN); 
  Blynk.connect(5000); 
 
  timer.setInterval(1000L, updateSimulation); // Update simulasi: 1 detik
  timer.setInterval(2000L, sendToBlynk); 
 
  Serial.println("=== Setup selesai! Simulasi berjalan... ===\n"); 
} 
 
void loop() { 
  Blynk.run(); 
  timer.run(); 
}
