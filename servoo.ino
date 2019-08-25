#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>  
#include <WiFiManager.h>
#include <Servo.h> 
int servoPin = 5;    
const int resetConfigPin = 3;

char ssid[] = "SSID";     // 
char password[] = "PASSWORDNYA"; // 


#define BOTtoken "650962166:AAGo4zmbxua8bp0Cm7jalTRD-YiNOKtkeLI" //api token 
SoftwareSerial cameraconnection = SoftwareSerial(2, 0);
Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);
File myFile;
File imgFile;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
static bool hasSD = false;
byte getNextByte();
bool isMoreDataAvailable();

int Bot_mtbs = 1000; 
long Bot_lasttime;  
bool Start = false;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/send_test_action") {
        bot.sendChatAction(chat_id, "typing");
        delay(4000);
        bot.sendMessage(chat_id, "Did you see the action message?");

    }

    if (text == "/start") {
      String welcome = "Koneksi Berhasil..";
      welcome += "\n\n";
      bot.sendMessage(chat_id, welcome);
    }
  }
}
void loop() {
  
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
bool isMoreDataAvailable(){
  return myFile.available();
}

byte getNextByte(){
  return myFile.read();
}
Servo Servo1; 
void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
}
void loop(){ 
   // Make servo go to 0 degrees 
   Servo1.write(0); 
   delay(1000); 
   // Make servo go to 90 degrees 
   Servo1.write(90); 
   delay(1000); 
   // Make servo go to 180 degrees 
   Servo1.write(180); 
   delay(1000); 
}
