#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "smartdoor-bbb34.firebaseio.com"
#define FIREBASE_AUTH "gm1QMY8AeIn4MgeAxgLnnpZxvT2KlWiY68Nqf4jo"
#define WIFI_SSID "Galaxy Note10 5G3332"
#define WIFI_PASSWORD "20190217"

void setup() {
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
  
  //check firebase
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;  
  } 
  if (Serial.available()){
    Serial.write(Serial.read());
    char data=Serial.read();
    if(data=='1')
    {
      Firebase.setInt("alarm", 1);
    }
    else
    {
      Firebase.setInt("alarm", 0);
    }
  }
}
  
