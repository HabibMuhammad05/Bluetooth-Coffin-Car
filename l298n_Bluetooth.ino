#include <SoftwareSerial.h>
SoftwareSerial bt (8,9);
#define in1 2
#define in2 3
#define in3 4
#define in4 5
#define enA 6
#define enB 7
int motorspeedA = 255;
int motorspeedB = 255;


void setup(){
    Serial.begin(9600);
    bt.begin(9600);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
    pinMode(enA,OUTPUT);
    pinMode(enB,OUTPUT);
}

void loop(){
    String perintah;
    analogWrite(enA,motorspeedA);
    analogWrite(enB,motorspeedB);
    
    if(bt.available()!=0){
        perintah = bt.readString();
        Serial.println(perintah);
    }
    
    if (perintah == "MAJU"){
       digitalWrite(in1,HIGH);
       digitalWrite(in2,LOW);
       digitalWrite(in3,HIGH);
       digitalWrite(in4,LOW);
       }
    
    if (perintah == "MUNDUR"){
       digitalWrite(in1,LOW);
       digitalWrite(in2,HIGH);
       digitalWrite(in3,LOW);
       digitalWrite(in4,HIGH);
       }
    
    if (perintah == "KANAN"){
       digitalWrite(in1,HIGH);
       digitalWrite(in2,LOW);
       digitalWrite(in3,LOW);
       digitalWrite(in4,HIGH);
       }
    
    if (perintah == "KIRI"){
       digitalWrite(in1,LOW);
       digitalWrite(in2,HIGH);
       digitalWrite(in3,HIGH);
       digitalWrite(in4,LOW);
       }
    
    if (perintah == "STOP"){
       digitalWrite(in1,LOW);
       digitalWrite(in2,LOW);
       digitalWrite(in3,LOW);
       digitalWrite(in4,LOW);
       }
    
}