int pwm1 = 11;
int in1 = 13;
int in2 = 12;
int in3 = 8;
int in4 = 10;
int pwm2 = 9;

void setup() {
  pinMode(pwm1,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(pwm2,OUTPUT);
}

void loop() {
 maju(255);
 delay(1000);
 berhenti();
 delay(500);
 mundur(255);
 delay(1000);
 berhenti();
 delay(500);
 kanan(255, 0);
 delay(1000);
 berhenti();
 delay(500);
 kiri(0, 255);
 delay(500);
 berhenti();
 delay(1000);
 serongkiri(100, 255);
 delay(500);
 berhenti();
 delay(500);
 serongkanan(255, 100);
 delay(500);
 berhenti();
 delay(1500);
}

void maju(int spdmaju){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  
  analogWrite(pwm1, spdmaju);
  analogWrite(pwm2, spdmaju);
}

void mundur(int spdmundur){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in4,LOW);
  digitalWrite(in3,HIGH);
  analogWrite(pwm1, spdmundur);
  analogWrite(pwm2, spdmundur);
}

void kanan(int spdkiri, int spdkanan){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in3,LOW);
  analogWrite(pwm1, spdkiri);
  analogWrite(pwm2, spdkanan);
}

void serongkanan(int spdkiri, int spdkanan){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  analogWrite(pwm1, spdkiri);
  analogWrite(pwm2, spdkanan);
}

void kiri(int spdkiri2, int spdkanan2){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW); 
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  analogWrite(pwm1, spdkiri2);
  analogWrite(pwm2, spdkanan2);
  delay(500);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in3,LOW);
}

void serongkiri(int spdkiri2, int spdkanan2){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  analogWrite(pwm1, spdkiri2);
  analogWrite(pwm2, spdkanan2);
  delay(500);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in3,LOW);
}

void berhenti(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in3,LOW);

  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
}
