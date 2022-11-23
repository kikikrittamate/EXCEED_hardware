#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Kiki";
const char* password = "27042544";
const char* url_post = "https://ecourse.cpe.ku.ac.th/exceed02/api/hard/sensor/post";

char str[20];
static int s;

const  int _size = 2*JSON_OBJECT_SIZE(20);

StaticJsonDocument<_size> JSONPost;

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



void _post(){
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    
    http.begin(url_post);
    http.addHeader("Content-Type", "application/json");

    JSONPost["s"] = s;
    Serial.print(s);
    
    serializeJson(JSONPost, str);
    int httpCode = http.POST(str);

    if(httpCode == HTTP_CODE_OK){
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println("POST result");
      Serial.println(payload);
    } else{
      Serial.println(httpCode);
      Serial.println("ERROR on HTTP Request");
    }
  } else{
    WiFi_Connect();
  }
  delay(100);
}


int sensor1 = 27;
int sensor2 = 33;
int sensor3 = 32;
int laser1 = 18;
int laser2 = 19;
int laser3 = 21;





void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(laser1, OUTPUT);
  pinMode(laser2, OUTPUT);
  pinMode(laser3, OUTPUT);
  digitalWrite(laser1, HIGH);
  digitalWrite(laser2, HIGH);
  digitalWrite(laser3, HIGH);
  Serial.begin(9600);
  //WiFi_Connect();

  //xTaskCreatePinnedToCore(Task1,"Task 1",1024*32,NULL,1,NULL,1);
  xTaskCreatePinnedToCore(Task2,"Task 2",1024*32,NULL,1,NULL,1);
  xTaskCreatePinnedToCore(Task3,"Task 3",1024*32,NULL,1,NULL,1);
}


void Task1(void *parameter){
  while(1){
  if((analogRead(sensor3) > 200) && s == 2){
    s = 3;
    _post();
    Serial.println(s);
  }
  if((analogRead(sensor2) > 150) && s == 1){
    s = 2;
    _post();
    Serial.println(s);
  }
  if((analogRead(sensor1) > 150) && s == 1){
    s = 1;
    }
  else if(analogRead(sensor1) > 150){
    s = 1;
    _post();
    Serial.println(s);
    }
    delay(150);
  }
  delay(500);
}


void Task2(void *parameter){
  while(1){
  if((analogRead(sensor2) > 300) && s == 2){
    s = 2;
    }
  else if(analogRead(sensor2) > 200){
    s = 2;
    _post();
    //Serial.println(s);
    }
    delay(200);
  }
  delay(500);
}

void Task3(void *parameter){
  while(1){
  if((analogRead(sensor3) > 390) && s == 2){
    s = 3;
    _post();
    //Serial.println(s);
    }
    delay(200);
  }
delay(500);
}


void post_func(){
  int n=0;
  if((s == 1) && n == 0){
    _post();
    Serial.println(s);
    delay(500);
    n++;
  }
  if((s == 2) && n == 1){
   // _post();
    Serial.println(s);
    delay(500);
    n++;
  }
  if((s == 3) && n == 2){
    //_post();
    Serial.println(s);
    delay(500);
    n++;
    n=n%3;
  }
  delay(100);
}*/



void loop() {
  //Serial.print("ldr2: ");
  //Serial.println(analogRead(sensor2));
  //Serial.print("ldr3: ");
  //Serial.println(analogRead(sensor3));
  //post_func();
  delay(100);
}
