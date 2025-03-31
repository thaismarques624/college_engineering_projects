//versão 1, reproduz apenas uma rodada.

#define NOTE1 1000//definindo a frequência que o buzzer tocará


int buzzer = 11;//porta onde está o buzzer.
int led1 = 4;//porta onde está a led
int led2 = 3;//porta onde está a led
int bot1 = 10;//porta onde está o primeiro  botão.
int bot2 = 9;//porta onde está o segundo botão.
int bot3 = 8;//porta onde está o terceiro botão.
int bot4 = 7;//porta onde está o quarto botão.

void setup() {

  pinMode(bot1, INPUT);//designando o botão como entrada.
  pinMode(bot2, INPUT);//designando o botão como entrada.
  pinMode(bot3, INPUT);//designando o botão como entrada.
  pinMode(bot4, INPUT);//designando o botão como entrada.
  pinMode(led1, OUTPUT);//designando a led como saida.
  pinMode(led2, OUTPUT);//designando a led como saida.
  pinMode(buzzer, OUTPUT);//designando o buzzer como saida.
 
  noTone(buzzer);//Tira a interferencia
}
void loop() {
   digitalWrite(led1, LOW);// mantendo a led desligada.
   digitalWrite(led2, LOW);// mantendo a led desligada.
   
   if(digitalRead(bot1) == HIGH){//se o botão 1 estiver ligado faça
    digitalWrite(led1, HIGH);//mantenha a led ligada. 
    for(int i = 0; i <= 3; i ++)//contagem para controlar o som de "certo"
    {
      tone(buzzer, NOTE1);//toque a nota 
      delay(100);//espere 100 milisegundos
      tone(buzzer, NOTE1 - 100);//toque a nota -100(no caso a nota abaixa a frequência para 900)
      delay(100);//espere 100 milisegundos
    }
    noTone(buzzer);//Tira a interferencia
   }
   
   if(digitalRead(bot2) == HIGH){//se botão 2 estiver ligado
    digitalWrite(led2, HIGH);// mantenha a led ligada
    tone(buzzer, NOTE1 -200);//toque a nota -200(no caso a nota abaixa a frequência para 800)
   
   }
   if(digitalRead(bot3) == HIGH){//se botão 3 estiver ligado
    digitalWrite(led2, HIGH);// mantenha a led ligada
    tone(buzzer, NOTE1 -200);//toque a nota -200(no caso a nota abaixa a frequência para 800)
 
   } 
    if(digitalRead(bot4) == HIGH){//se botão 4 estiver ligado
    digitalWrite(led2, HIGH);// mantenha a led ligada
    tone(buzzer, NOTE1 -200);//toque a nota -200(no caso a nota abaixa a frequência para 800)
 
   } 
   noTone(buzzer);
}

//futuras melhorias:
//Criar um jeito em que o código embaralhe as alternativas criando novas rodadas aleatórias. Ou optar por um leitor que funcione, totalmente autônomo.  
//Talvez isso pode servir de base para um jogo didático para crianças cegas, se guiando pelo som e por rodadas. 
