#include <Arduino.h>
#include <RotaryEncoder.h>
#include <Main/config.h> 

#define CANAL_A  0

//set encoder
// RotaryEncoder encoderRight(ENCODER1A, ENCODER1B);
RotaryEncoder encoderRight(ENCODERRA, ENCODERRB);


int valorR = 0;
int newPosR = 0;

int target = 40;

int i = 500;

void setup()
{ //-------------PWM---------------------
  //define PWM
  pinMode(PWMA, OUTPUT);//Definimos os pinos  como saída.

  ledcAttachPin(PWMA, CANAL_A);//Atribuimos o pino PWMA ao canal 0.
  ledcSetup(CANAL_A, 1000, 10);//Atribuimos ao canal 0 a frequencia de 1000Hz com resolucao de 10bits.
  
  //-------------DIGITAL------------------

  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
 
  Serial.begin(SERIAL_RATE);
  Serial.println("-----INIT-------");
  
}

void loop()
{

 digitalWrite(AIN2,LOW);
 digitalWrite(AIN1,HIGH);

 ledcWrite(CANAL_A, i);
 delay(10);
   
  static int posR = 0;
  encoderRight.tick();
  int newPosR = encoderRight.getPosition();
  
  if (posR != newPosR)
  { Serial.print("|| RIGHT| ");
    Serial.print(newPosR);
    Serial.println();
    posR = newPosR;
  }

    if(newPosR>target){
        Serial.println("------------TARGET-------------");
        //reset target 
        newPosR = 0 ;
        i = 0;
        
        
    }
  
 

 
}

