//Programa : Teste basico encoder Arduino
//Autor : Arduino e Cia

//Carrega a biblioteca do encoder
#include <RotaryEncoder.h>
#include <Arduino.h>
//Pinos de ligacao do encoder
RotaryEncoder encoderRight(16, 17);
RotaryEncoder encoderLeft(23, 15);


//Variavel para o botao do encoder
int valorR = 0;
int newPosR = 0;

int valorL = 0;
int newPosL = 0;

void setup()
{
  
  Serial.begin(115200);
  Serial.println("Gire o encoder....");
}

void loop()
{
  

  //Le as informacoes do encoder
  static int posR = 0;
  encoderRight.tick();
  int newPosR = encoderRight.getPosition();
  //Se a posicao foi alterada, mostra o valor
  //no Serial Monitor
  if (posR != newPosR)
  { Serial.print("|| RIGHT| ");
    Serial.print(newPosR);
    Serial.print(" || LEFT| ");
    Serial.print(newPosL);
    Serial.println();
    posR = newPosR;
  }

  //Le as informacoes do encoder
  static int posL = 0;
  encoderLeft.tick();
  int newPosL = encoderLeft.getPosition();
  //Se a posicao foi alterada, mostra o valor
  //no Serial Monitor
  if (posL != newPosL)
  { Serial.print("|| RIGHT| ");
    Serial.print(newPosR);
    Serial.print(" || LEFT| ");
    Serial.print(newPosL);
    Serial.println();
    posL = newPosL;
  }
}