#define EN_1 15
#define CK_1 2
#define EN_2 0
#define CK_2 4
#define EN_3 16
#define CK_3 17
#define EN_4 5
#define CK_4 18
#define EN_5 19
#define CK_5 21


int salidas[] = {EN_1, CK_1, EN_2, CK_2, EN_3, CK_3, EN_4, CK_4};
int entradas[] = {};

#include <String.h>

int EN_n[] = {0, EN_1, EN_2, EN_3, EN_4, EN_5};
int CK_n[] = {0, CK_1, CK_2, CK_3, CK_4, CK_5};
int velocidad[] = {0, 0, 0, 0, 0};

//class Motor(int pin_EN)

/*class Eje_n(int* v_motor, int pin_EN, int pin_CK)
{
  Eje_n()
  {

  }
  
  if(*v_motor == 0)
  {
    digitalWrite(pin_EN, LOW);
    digitalWrite(pin_)
  }
}*/


void controlar(int entrada, int salida_en, int salida_ck)
{
}

void setup() {
  // put your setup code here, to run once:
  for(int i: salidas)
  {
    pinMode(i, OUTPUT);
  }
  
  Serial.begin(115200);
}

int RZ=0;
int LZ=0;

void loop() {

    if (Serial.available() > 0) { // Check if data is available to read
      // Read the incoming string
      String incomingString = Serial.readStringUntil('\0');
      if((char*)incomingString[4]=="R")
      {
        incomingString = incomingString.substring(6, incomingString.length()-1);
        RZ = incomingString.toInt();
        Serial.print(RZ);
      }
      else
      {
        incomingString = incomingString.substring(5, incomingString.length()-1);
        LZ = incomingString.toInt();
        Serial.print(LZ);
      }

      // Process the incoming string as needed
      // Example: Print the incoming string
      //Serial.print("Rxvd: ");
      //Serial.print(incomingString);
    }

    //Serial.println("a");
    //delay(100);
}
