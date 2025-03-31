#define NOTE_C 262

#define ON LOW 

const int Buzzer = 11;
const int LED1 = 0;

const int DO = 10; 

void setup()
{                    
  pinMode(DO, INPUT);
  digitalWrite(DO,HIGH);

  pinMode(LED1, OUTPUT);
  
  digitalWrite(LED1,HIGH);
   delay(1000);
}

void loop()
{
  
    while(digitalRead(DO) == ON)
    { tone(11,NOTE_C);
      digitalWrite(LED1,HIGH);}
 
     noTone(11);
  //noTone(12); 
  
  digitalWrite(LED1,LOW);
  
}
