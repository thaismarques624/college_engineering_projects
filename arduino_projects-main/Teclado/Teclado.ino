// Declarando cada nota e sua frequência
#define NOTE_C 262 //Dó
#define NOTE_D 294 //Ré
#define NOTE_E 330 //Mi
#define NOTE_F 349 //Fá
#define NOTE_G 392 //Sol
#define NOTE_A 440 //Lá
#define NOTE_B 493 //Si
#define NOTE_C2 523 //Dó
#define ON LOW

const int Buzzer = 11; // Atribuição de pino ao buzzer para emitir o som do piano

//Cada LED representa uma tecla do teclado
const int LED1 = 0;
const int LED2 = 1;
const int LED3 = 2;
const int LED4 = 14;
const int LED5 = 15;
const int LED6 = 16;
const int LED7 = 17;
const int LED8 = 18;

const int DO = 10; // Atribuição de pinos para cada tecla
const int RE = 9;
const int MI = 8;
const int FA = 7;
const int SO = 6;
const int LA = 5;
const int SI = 4;
const int DO2 = 3;

void setup(){   
                 
  pinMode(DO, INPUT);
  digitalWrite(DO,HIGH);
   pinMode(RE, INPUT);
  digitalWrite(RE,HIGH);
   pinMode(MI, INPUT);
  digitalWrite(MI,HIGH);
  pinMode(FA, INPUT);
  digitalWrite(FA,HIGH);
   pinMode(SO,INPUT);
  digitalWrite(SO,HIGH);
   pinMode(LA, INPUT);
  digitalWrite(LA,HIGH);
   pinMode(SI,INPUT);
  digitalWrite(SI,HIGH);
   pinMode(DO2, INPUT);
  digitalWrite(DO2,HIGH);

 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
 pinMode(LED3, OUTPUT);
 pinMode(LED4, OUTPUT);
 pinMode(LED5, OUTPUT);
 pinMode(LED6, OUTPUT);
 pinMode(LED7, OUTPUT);
 pinMode(LED8,OUTPUT);
 
 digitalWrite(LED1,HIGH);
 delay(1000);
 digitalWrite(LED2,HIGH);
  delay(1000);
 digitalWrite(LED3,HIGH);
  delay(1000);
 digitalWrite(LED4,HIGH);
  delay(1000);
 digitalWrite(LED5,HIGH);
  delay(1000);
 digitalWrite(LED6,HIGH);
  delay(1000);
 digitalWrite(LED7,HIGH);
  delay(1000);
 digitalWrite(LED8,HIGH);
 delay(1000);
 
 digitalWrite(LED1,LOW);
 digitalWrite(LED2,LOW);
 digitalWrite(LED3,LOW);
 digitalWrite(LED4,LOW);
 digitalWrite(LED5,LOW);
 digitalWrite(LED6,LOW);
 digitalWrite(LED7,LOW);
 digitalWrite(LED8,LOW);
}
void loop(){ // Determinado que enquanto a tecla estiver ON, fazer o buzzer tocar uma nota e também acender a
             //LED correspondente

while(digitalRead(DO) == ON)
{ tone(11,NOTE_C); digitalWrite(LED1,HIGH);}
while(digitalRead(RE) == ON)
{ tone(11,NOTE_D);
digitalWrite(LED2,HIGH);}
while(digitalRead(MI) == ON)
{ tone(11,NOTE_E); digitalWrite(LED3,HIGH);}
while(digitalRead(FA) == ON)
{ tone(11,NOTE_F); digitalWrite(LED4,HIGH);}
while(digitalRead(SO) == ON)
{ tone(11,NOTE_G); digitalWrite(LED5,HIGH);}
while(digitalRead(LA) == ON)
{ tone(11,NOTE_A); digitalWrite(LED6,HIGH);}
while(digitalRead(SI) == ON)
{ tone(11,NOTE_B); digitalWrite(LED7,HIGH);}
while(digitalRead(DO2) == ON)
{ tone(11, NOTE_C2); digitalWrite(LED8,HIGH);}

noTone(11); //Desligar o Buzzer

//Manter as led’s desligadas
digitalWrite(LED1,LOW);
digitalWrite(LED2,LOW);
digitalWrite(LED3,LOW);
digitalWrite(LED4,LOW);
digitalWrite(LED5,LOW);
digitalWrite(LED6,LOW);
digitalWrite(LED7,LOW);
digitalWrite(LED8,LOW);
}

//contexto: Piano eletrico feito com materias de baixo custo.
//O teclado foi planejado a partir da ideia do alarme de placa de pressão. Utilizando a mesma dinâmica de abrir/fechar o circuito foi feita a adaptação para as teclas.
