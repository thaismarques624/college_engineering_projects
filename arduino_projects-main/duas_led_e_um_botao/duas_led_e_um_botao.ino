#define NOTE_DO 262 //DO
#define NOTE_RE 294 // RE
#define NOTE_MI 330 //MI
//#define NOTE_F 349 //FA
#define NOTE_SO 392 //SO
#define NOTE_LA 440 //LÁ
#define NOTE_SI 493 // SI
#define NOTE_DO2 523 //DO 


void setup() {

  pinMode(1, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(10, INPUT);

  digitalWrite(1,HIGH);
  delay(500);
  digitalWrite(3,HIGH);
  delay(500);
  digitalWrite(1,LOW);
  delay(500);
  digitalWrite(3,LOW);
  
  
  
  
 
  digitalWrite(10, HIGH);
  
  
  
}

void loop() {
    while(digitalRead(10) == 1)
    {
    digitalWrite(1,LOW);
    digitalWrite(3,LOW);
    noTone(11);}

    while(digitalRead(10) == 0)
    { digitalWrite(1,HIGH);
      tone(11,NOTE_MI);
      delay(500);
      digitalWrite(1,LOW);
      digitalWrite(3,HIGH);
      tone(11,NOTE_LA);
      delay(450);
      digitalWrite(3,LOW);
      digitalWrite(1,HIGH);
      tone(11,NOTE_DO);
      delay(40);
      digitalWrite(1,LOW);
      digitalWrite(3,HIGH);
      tone(11,NOTE_SI);
      delay(1
      50);
      digitalWrite(3,LOW);
      digitalWrite(1,HIGH);
      tone(11,NOTE_LA);
      delay(250);
      digitalWrite(1,LOW);
      digitalWrite(3,HIGH);
      tone(11,NOTE_MI);
      delay(250);
      digitalWrite(3,LOW);
      digitalWrite(1,HIGH);
      tone(11,NOTE_RE);
      delay(500);
      digitalWrite(1,LOW);
      digitalWrite(3,HIGH);
      tone(11,NOTE_SI);
      delay(1000);
      digitalWrite(3,LOW);
      
      digitalWrite(1,HIGH);
      digitalWrite(3,HIGH);}

 }
