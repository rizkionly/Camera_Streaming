
#ifndef __CONFIGFILE__
#define __CONFIGFILE__
//flag for saving data
bool shouldSaveConfig = true;
char wifi_ssid[34] = "ESP32CAM_3D";
char wifi_password[34] = "12345678";
char mqtt_server[40] = "rmq1.pptik.id";
int   mqtt_port = 1883;
char smqtt_port[5] = "1883";
char mqtt_user[40] = "/tmdgdai:tmdgdai";
char mqtt_password[40] = "tmdgdai";
char mqtt_keywords1[40] = "pkl_online";
char mqtt_keywords2[40] = "report_pkl_online";
const long interval = 2000;
uint8_t MAC_array[6];
char MAC_char[18];  
WiFiClient espClient;
PubSubClient client(espClient);                   
#define RST_PIN  5  // RST-PIN für RC522 - RFID - SPI - Modul GPIO5 
#define SS_PIN  4  // SDA-PIN für RC522 - RFID - SPI - Modul GPIO4 
#define BUZZER  D3 // pcb merah (D3) (kalau hijau, biru D8) 
#define LED1 D8// pcb merah (kalau hijau,biru d4)
#define LED2 D4 
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
void SaveConfigCallback ();
void ReadConfigFile();

#endif
