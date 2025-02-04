#include "HX711.h"

const int LOADCELL_DOUT_PIN = 21;  // Data pin untuk ESP32
const int LOADCELL_SCK_PIN = 22;   // Clock pin untuk ESP32

HX711 scale;
int reading;
int lastReading;
int read_button;

#define CALIBRATION_FACTOR 450.753
const int BUTTON_PIN = 4;  // Pin button untuk ESP32

void setup() {
  Serial.begin(115200);  // ESP32 lebih umum menggunakan 115200 baud rate
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("Inisialisasi timbangan");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(CALIBRATION_FACTOR);   
  scale.tare();               
}

void loop() {
  read_button = digitalRead(BUTTON_PIN);
  
  if(read_button == LOW){
    if (scale.wait_ready_timeout(200)) {
      reading = round(scale.get_units());
      
      Serial.print("Berat: ");
      Serial.print(reading);
      Serial.println(" gram");
      
      if (reading != lastReading) {
        Serial.println(reading);
      }
      lastReading = reading;
    }
    else {
      Serial.println("HX711 Tidak Ditemukan");
    }
  }
}