#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

WebServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "A05";
const char* password = "vb181107";

const int pinEspLed = 2;
const int pinLedMerah = 4;
const int pinLedKuning = 5;
const int pinLedHijau = 19;
const int pinLedKedapKedip1 = 15;
const int pinLedKedapKedip2 = 18;
const int pinServo = 33;
const int pinPotensiometer = 34;  // Pin untuk potensiometer (A0)

Servo servoSatu;

bool statusLedMerah = false;
bool statusLedKuning = false;
bool statusLedHijau = false;
bool statusKedip = false;
bool statusServo = false;

unsigned long waktuSebelumnya = 0;
const long intervalKedip = 500;

// Function declarations
void getMerahLed();
void getKuningLed();
void getHijauLed();
void setMerahLed();
void setKuningLed();
void setHijauLed();
void setServo();
void toggleBlinkLed();
void getBlinkLed();

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  pinMode(pinEspLed, OUTPUT);
  pinMode(pinLedMerah, OUTPUT);
  pinMode(pinLedKuning, OUTPUT);
  pinMode(pinLedHijau, OUTPUT);
  pinMode(pinLedKedapKedip1, OUTPUT);
  pinMode(pinLedKedapKedip2, OUTPUT);

  digitalWrite(pinLedMerah, LOW);
  digitalWrite(pinLedKuning, LOW);
  digitalWrite(pinLedHijau, LOW);
  digitalWrite(pinLedKedapKedip1, LOW);
  digitalWrite(pinLedKedapKedip2, LOW);

  WiFi.begin(ssid, password);
  lcd.setCursor(0, 0);
  lcd.print("Menghubungkan");

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(pinEspLed, LOW);
    delay(1000);
    lcd.print(".");
  }

  digitalWrite(pinEspLed, HIGH);
  Serial.println("");
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Terhubung");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  server.on("/merah", HTTP_GET, getMerahLed);
  server.on("/kuning", HTTP_GET, getKuningLed);
  server.on("/hijau", HTTP_GET, getHijauLed);

  server.on("/merah", HTTP_POST, setMerahLed);
  server.on("/kuning", HTTP_POST, setKuningLed);
  server.on("/hijau", HTTP_POST, setHijauLed);

  server.on("/servo", HTTP_POST, setServo);
  server.on("/kedip", HTTP_POST, toggleBlinkLed);
  server.on("/kedip", HTTP_GET, getBlinkLed);

  server.begin();
  Serial.println("Server dimulai");

  servoSatu.attach(pinServo);
  servoSatu.write(180);  // Default posisi tertutup
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sampah Tertutup");
}

void setMerahLed() {
  statusLedMerah = !statusLedMerah;
  digitalWrite(pinLedMerah, statusLedMerah ? HIGH : LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", statusLedMerah ? "ON" : "OFF");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(statusLedMerah ? "Red Led On" : "Red Led Off");
}

void setKuningLed() {
  statusLedKuning = !statusLedKuning;
  digitalWrite(pinLedKuning, statusLedKuning ? HIGH : LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", statusLedKuning ? "ON" : "OFF");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(statusLedKuning ? "Yellow Led On" : "Yellow Led Off");
}

void setHijauLed() {
  statusLedHijau = !statusLedHijau;
  digitalWrite(pinLedHijau, statusLedHijau ? HIGH : LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", statusLedHijau ? "ON" : "OFF");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(statusLedHijau ? "Green Led On" : "Green Led Off");
}

void setServo() {
  statusServo = !statusServo;
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", statusServo ? "BUKA" : "TUTUP");

  if (statusServo) {
    servoSatu.write(0); // Buka
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sampah Terbuka");
  } else {
    servoSatu.write(180); // Tutup
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sampah Tertutup");
  }
}

void toggleBlinkLed() {
  statusKedip = !statusKedip;
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", statusKedip ? "ON" : "OFF");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(statusKedip ? "Blink Led On" : "Blink Led Off");
}

void getMerahLed() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", statusLedMerah ? "ON" : "OFF");
}

void getKuningLed() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", statusLedKuning ? "ON" : "OFF");
}

void getHijauLed() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", statusLedHijau ? "ON" : "OFF");
}

void getBlinkLed() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", statusKedip ? "ON" : "OFF");
}

void loop() {
  server.handleClient();

  if (statusKedip) {
    unsigned long waktuSaatIni = millis();
    if (waktuSaatIni - waktuSebelumnya >= intervalKedip) {
      waktuSebelumnya = waktuSaatIni;
      digitalWrite(pinLedKedapKedip1, !digitalRead(pinLedKedapKedip1));
      digitalWrite(pinLedKedapKedip2, !digitalRead(pinLedKedapKedip1));
    }
  } else {
    digitalWrite(pinLedKedapKedip1, LOW);
    digitalWrite(pinLedKedapKedip2, LOW);
  }

  // Baca nilai potensiometer dan atur posisi servo
  int nilaiPotensiometer = analogRead(pinPotensiometer);
  int posisiServo = map(nilaiPotensiometer, 0, 4095, 0, 180); // Konversi nilai ke sudut 0-180
  servoSatu.write(posisiServo);

  // Tampilkan informasi pada LCD berdasarkan posisi servo
  lcd.clear();
  lcd.setCursor(0, 0);
  if (posisiServo == 0) {
    lcd.print("Sampah Terbuka");
    digitalWrite(pinLedHijau, HIGH);
    digitalWrite(pinLedMerah, LOW);
    digitalWrite(pinLedKuning, LOW);
  } else if (posisiServo == 180) {
    lcd.print("Sampah Tertutup");
    digitalWrite(pinLedMerah, HIGH);
    digitalWrite(pinLedHijau, LOW);
    digitalWrite(pinLedKuning, LOW);
  } else {
    lcd.print("Sampah ");
    lcd.print(posisiServo);
    lcd.print((char)223); // Karakter derajat
    digitalWrite(pinLedKuning, HIGH);
    digitalWrite(pinLedMerah, LOW);
    digitalWrite(pinLedHijau, LOW);
  }
}
