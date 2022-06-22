int pwm1 = 11;
int in1 = 13;
int in2 = 12;
int in3 = 8;
int in4 = 10;
int pwm2 = 9;

int Skanan = 5;
int Stengah = 3;
int SKiri = 4;
void setup() {
  Serial.begin(9600);
  pinMode(pwm1,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(pwm2,OUTPUT);
  
  pinMode(Skanan, INPUT_PULLUP);
  pinMode(Stengah, INPUT_PULLUP);
  pinMode(SKiri, INPUT_PULLUP);
}

void loop(){
 linefollower();
 }

// maju2(100);
// delay(500);
// berhenti();
// delay(1000);
// kiri2(100,130);
// delay(500);
// berhenti();
// delay(1000);
// kanan2(130,100);
// delay(500);
// berhenti();
// delay(1500);
void linefollower(){
    if ((digitalRead(SKiri)== 0 )&&(digitalRead(Stengah)== 1 )&&(digitalRead(Skanan)== 0 ))  {Serial.println("Maju"); maju2(100);}
 
    if ((digitalRead(SKiri)== 1 )&&(digitalRead(Stengah)== 1 )&&(digitalRead(Skanan)== 0 ))  {Serial.println("Kiri"); kiri2(95,100);}
    if ((digitalRead(SKiri)== 1 )&&(digitalRead(Stengah)== 0 )&&(digitalRead(Skanan)== 0 ))  {Serial.println("Kiri"); kiri2(95,100);}
 
    if ((digitalRead(SKiri)== 0 )&&(digitalRead(Stengah)== 1 )&&(digitalRead(Skanan)== 1 ))  {Serial.println("Kanan");kanan2(100,95);}
    if ((digitalRead(SKiri)== 0 )&&(digitalRead(Stengah)== 0 )&&(digitalRead(Skanan)== 1 ))  {Serial.println("Kanan");kanan2(100,95);}
 
    if ((digitalRead(SKiri)== 1 )&&(digitalRead(Stengah)== 1 )&&(digitalRead(Skanan)== 1 ))  {Serial.println("Stop"); berhenti();}
}

void maju2(int spdmaju){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  
  analogWrite(pwm1, spdmaju);
  analogWrite(pwm2, spdmaju);
}

void kiri2(int spdkiri, int spdkanan){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  
  digitalWrite(in4,LOW);
  digitalWrite(in3,LOW);
  
  analogWrite(pwm1, spdkiri);
  analogWrite(pwm2, spdkanan);
}

void kanan2 (int spdkiri2, int spdkanan2){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  
  analogWrite(pwm1, spdkiri2);
  analogWrite(pwm2, spdkanan2);
}

void berhenti(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in3,LOW);

  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
}
