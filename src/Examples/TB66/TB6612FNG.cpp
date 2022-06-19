#include <Arduino.h>

#include <Main/config.h> 

#define CANAL_A  0
#define CANAL_B  1

#define SerialMode 0 




void setup()
{ //-------------PWM---------------------
  //define PWM
  pinMode(PWMA, OUTPUT);//Definimos os pinos  como saída.
  pinMode(PWMB, OUTPUT);
  
  ledcAttachPin(PWMA, CANAL_A);//Atribuimos o pino PWMA ao canal 0.
  ledcAttachPin(PWMB, CANAL_B);//Atribuimos o pino PWMB ao canal 1.
  ledcSetup(CANAL_A, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.
  ledcSetup(CANAL_B, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.

  //-------------DIGITAL------------------

  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);


  Serial.begin(SERIAL_RATE);
  
}

void loop()
{


 Serial.println("--------------------A-----------------------");
  delay(5000);

  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);

  for (int i = 0; i < 1024; i++)
  {
    ledcWrite(CANAL_A, i);//Escrevemos no canal 0, o duty cycle "i".
    Serial.print("A: ");
    Serial.println(i);
    delay(10);
  }
  digitalWrite(AIN2,HIGH);
  digitalWrite(AIN1,LOW);

  for (int i = 1023; i > 0; i--)
  { 
    Serial.print("A: ");
    Serial.println(i);
    ledcWrite(CANAL_A, i);
    delay(10);
  }
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);

  Serial.println("--------------------B-----------------------");
  delay(5000);

  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);

  for (int i = 0; i < 1024; i++)
  {
    ledcWrite(CANAL_B, i);//Escrevemos no canal 0, o duty cycle "i".
    Serial.print("B: ");
    Serial.println(i);
    delay(10);
  }
  digitalWrite(BIN2,HIGH);
  digitalWrite(BIN1,LOW);

  for (int i = 1023; i > 0; i--)
  { 
    Serial.print("B: ");
    Serial.println(i);
    ledcWrite(CANAL_B, i);
    delay(10);
  }
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);
}