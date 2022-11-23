#include<WiFi.h>
#include<HTTPClient.h>
#include<ArduinoJson.h>

const char* ssid="Kiki";
const char* password = "27042544";
const char* get_url = "https://ecourse.cpe.ku.ac.th/exceed02/api/hard/alarm/get";

int alert;
char str[50];

const int _size = 2*JSON_OBJECT_SIZE(3);

StaticJsonDocument<_size> JSONGet;

void WiFi_Connect(){
  WiFi.disconnect();
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
}


void _get(){
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;

    http.begin(get_url);

    int httpCode = http.GET();

    if(httpCode == HTTP_CODE_OK){
      String payload = http.getString();
      DeserializationError err = deserializeJson(JSONGet, payload);
      if(err){
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(err.c_str());
      }else{
        Serial.println(httpCode);
        Serial.print("alarm: ");
        Serial.println((int)JSONGet["alarm"]);
        alert = (int)JSONGet["alarm"];
      }
    }else{
      Serial.println(httpCode);
      Serial.println("ERROR on HTTP Request");
    }
  }else{
    WiFi_Connect();
  }
}






int red = 25;
int green = 33;
int blue = 32;
int buzzer = 19;


void setup(){
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(buzzer, LOW);
  Serial.begin(115200);
  WiFi_Connect();
}

void if_alert(){
  if (alert == 1){
    digitalWrite(red, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  if (alert == 0){
    delay(1000);
    digitalWrite(red, LOW);
    digitalWrite(buzzer, LOW);
  }
}

void loop(){
  _get();
  if_alert();
  delay(1);

}
