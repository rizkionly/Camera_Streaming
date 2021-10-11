#include "esp_camera.h"
#include <WiFi.h>
#include <ESP32_FTPClient.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>  


#define CAMERA_MODEL_AI_THINKER 
#include "camera_pins.h"
#define PushButton 14
#define Buzzer 15
#define Merah 13
#define LED 4
#define Hijau 12

// isi guid disini, guid baru bisa digenerate di guidgenerator.com atau situs guid generator lainnya. 
const char* guid = "89680d3f-644d-4de1-b0bf-154e7669aa48";

const char* ssid = "ESP32CAM_3D";
const char* password = "12345678";

const char *TOPIC = "report_pkl_online";  // Topic to publish
const char *TOPIC_Report = "pkl_online";  // Topic to subcribe 
const char* mqtt_server = "rmq1.pptik.id"; 
const char* mqtt_user = "/tmdgdai:tmdgdai";
const char* mqtt_pass= "tmdgdai";
const char* CL = guid;

char ftp_server[] = "ftp5.pptik.id";
char ftp_user[]   = "pkl_espcam";
char ftp_pass[]   = "p3K4lespcam!";


ESP32_FTPClient ftp (ftp_server,ftp_user,ftp_pass, 5000, 2);


//void startCameraServer();
WiFiClient espClient;
PubSubClient client(espClient);

// ATUR IP STATIC (OPTIONAL)
//IPAddress local_IP(192, 168, 6, 201);
//IPAddress gateway(192, 168, 6, 1);
//IPAddress subnet(255, 255, 255, 0);
//IPAddress primaryDNS(8, 8, 8, 8);   //optional


int FTP_uploadImage(int64_t t , unsigned char * pdata, unsigned int size, String namefile)
{
//  char* filename;
  String nama = namefile;
//  int filename_len = namefile.length() + 1;
//  char filename_array[filename_len];
//  filename = namefile.toCharArray(filename_array, filename_len);
//  String analog = String (dataAnalog);
  String dataRM = String (nama+".jpg");
  char filename[150];
  dataRM.toCharArray(filename,sizeof(filename));
  Serial.print("FTP_uploadImage=");
  Serial.println(size);
  char loc[100] = "/test/";
  int port = 2121;
  ftp.OpenConnection(port);
  bool check = ftp.isConnected();
  Serial.print("cek koneksi: ");
  Serial.println(check);
  Serial.println(namefile);
  
  if (check == 1){
    digitalWrite(Merah, LOW);
    delay (500);
    digitalWrite(Merah, HIGH);
    delay(500);
    digitalWrite(Merah, LOW);
    delay(500);
    digitalWrite(Buzzer, HIGH);
    delay (500);
    digitalWrite(Buzzer, LOW);
    delay(500);
    digitalWrite(Buzzer, HIGH);
    delay(500);
    digitalWrite(Buzzer, LOW);
    delay(500);
    digitalWrite(Buzzer, HIGH);
    delay(500);
    digitalWrite(Buzzer, LOW);
    }
  else if (check == 0){
    digitalWrite(Merah, LOW);
    delay (500);
    digitalWrite(Merah, HIGH);
    delay(500);
    digitalWrite(Merah, LOW);
    delay(500);
    digitalWrite(Merah, HIGH);
    delay (500);
    digitalWrite(Merah, LOW);
    delay(500);
    digitalWrite(Merah, HIGH);
    delay(500);
    digitalWrite(Merah, LOW);
    delay (500);
    digitalWrite(Buzzer, HIGH);
    delay(3000);
    digitalWrite(Buzzer, LOW);
    delay(500);
    }
    

//  sprintf(filename,"%s.jpg",
//    filename
//    );

  //ftp.InitFile("Type A");
  ftp.ChangeWorkDir(loc);
  ftp.InitFile("Type I");
  ftp.NewFile(filename); 
  ftp.WriteData( pdata, size );
  ftp.CloseFile();
  
  ftp.CloseConnection();
  Serial.println("[INFO] Upload Image Success");
  client.publish(TOPIC_Report, filename);     

  
  return 0;
}
extern void capture_ftpupload(String);


void callback(char* topic, byte* payload, unsigned int length) {
  String response;
  int Push_button_state = digitalRead(PushButton);
  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }
  response.replace(" ","");
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println('\n'); 
  Serial.print("] ");
  Serial.println(response);
    capture_ftpupload(response);
    Serial.println("[INFO] Sukses Upload FTP!");
    Serial.println("Sudah Memotret");
 
}
void reconnect() {
  // Loop until we're reconnected
  Serial.println("In reconnect...");
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if(client.connect(CL, mqtt_user, mqtt_pass)) {
      client.subscribe(TOPIC);
      Serial.println("connected");
      Serial.print("Subcribed to: ");
      Serial.println(TOPIC);
      Serial.println('\n');

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  
  pinMode(PushButton, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(Merah, OUTPUT);
  pinMode(Hijau, OUTPUT);
  
  digitalWrite(Merah, LOW);
  digitalWrite(Hijau, HIGH);
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
 
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

//FRAMESIZE_UXGA (1600 x 1200)
//FRAMESIZE_QVGA (320 x 240)
//FRAMESIZE_CIF (352 x 288)
//FRAMESIZE_VGA (640 x 480)
//FRAMESIZE_SVGA (800 x 600)
//FRAMESIZE_XGA (1024 x 768)
//FRAMESIZE_SXGA (1280 x 1024)
  
  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1); // flip it back
    s->set_brightness(s, 1); // up the brightness just a bit
    s->set_saturation(s, -2); // lower the saturation
  }
  // drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_SXGA);

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
    digitalWrite(Merah, HIGH);
    delay(500);
    digitalWrite(Merah, LOW);
    delay(500);
  }
    Serial.println("");
    Serial.println("WiFi connected");
    digitalWrite(Merah, HIGH);
    delay(250);
    digitalWrite(Merah, LOW);
    delay(250);
  
//  startCameraServer();
//  Serial.print("Camera Ready! Use 'http://");
//  Serial.print(WiFi.localIP());
//  Serial.println("' to connect");

  client.setServer(mqtt_server,1883);
  client.setCallback(callback);
}
int timeout = 0;
void loop() {
  if (!client.connected()){
  reconnect();
  }
  client.loop();
//  digitalWrite(Hijau, HIGH);
//  digitalWrite(Merah, LOW);

//  if(digitalRead(PushButton)==HIGH)
//    {
//      capture_ftpupload();
//      Serial.println("[INFO] Sukses Upload FTP!");
//      Serial.println("Sudah Memotret");
//      digitalWrite(Buzzer, HIGH);
//      delay(1000);
//      digitalWrite(Buzzer, LOW);
//      delay(1000);
//      }

// timeout += 1;
// delay(100);  
// if(timeout % (10 * 10) == 0) { // capture & upload per 1 min
//   capture_ftpupload();
//  }
  
}
