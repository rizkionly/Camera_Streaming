#include "config.h"
#include "FS.h"
#include "SPIFFS.h"

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void ReadConfigFile()
{
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");

          strcpy(mqtt_server, json["mqtt_server"]);
          String port = json["mqtt_port"];
          mqtt_port = port.toInt();
          strcpy(mqtt_user, json["mqtt_user"]);
          strcpy(mqtt_password, json["mqtt_password"]);
          strcpy(mqtt_keywords1, json["mqtt_keywords1"]);
          strcpy(mqtt_keywords2, json["mqtt_keywords2"]);
          strcpy(ftp_server, json["ftp_server"]);
          strcpy(ftp_user, json["ftp_user"]);
          strcpy(ftp_pass, json["ftp_pass"]);
        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
}

String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ; 
}

void SaveConfigFile()
{
  
  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"] = mqtt_server;
    json["mqtt_port"] = String(mqtt_port);
    json["mqtt_user"] = mqtt_user;
    json["mqtt_password"] = mqtt_password;
    json["mqtt_keywords1"] = mqtt_keywords1;
    json["mqtt_keywords2"] = mqtt_keywords2;
    json["ftp_server"] = ftp_server;
    json["ftp_user"] = ftp_user;
    json["ftp_pass"] = ftp_pass;
    
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }
}

void ResetSettings()
{
   WiFiManager wifiManager;
   wifiManager.resetSettings();
   delay(2000);
   ESP.restart();
}
