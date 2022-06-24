// Include Libraries
#include <esp_now.h>
#include <WiFi.h>
 
// Define a data structure
#define relay_pin1 14

typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;
 
// Create a structured object
struct_message myData;
 
 
// Callback function executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  
  pinMode(relay_pin1, OUTPUT);
  //pinMode(relay_pin2, OUTPUT);
  
  Serial.print("Data received: ");
  Serial.println(len);
  Serial.print("Character Value: ");
  Serial.println(myData.a);
  Serial.print("Integer Value: ");
  Serial.println(myData.b);
  Serial.print("Float Value: ");
  Serial.println(myData.c);
  Serial.print("Boolean Value: ");
  Serial.println(myData.d);
  Serial.println();

  if (myData.b >= 3) {
      digitalWrite(relay_pin1, LOW);
    }
    else {
      digitalWrite(relay_pin1, HIGH);
      } 
}
 
void setup() {
  // Set up Serial Monitor
  
  
  Serial.begin(115200);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
 
}
