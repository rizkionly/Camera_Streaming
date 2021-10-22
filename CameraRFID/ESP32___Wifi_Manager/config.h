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
char ftp_server[40] = "ftp5.pptik.id";
char ftp_user[40]   = "pkl_espcam";
char ftp_pass[40]   = "p3K4lespcam!";
const long interval = 2000;
uint8_t MAC_array[6];
char MAC_char[18];  
WiFiClient espClient;
PubSubClient client(espClient);                   
#define Buzzer 15
#define Merah 13
#define Hijau 12
//#define PushButton 14
//#define LED 4
void SaveConfigCallback ();
void ReadConfigFile();

#endif
