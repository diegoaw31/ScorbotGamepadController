#include <String.h>

#define LED 13
#define EN_1 3
#define CW_1 4
#define CCW_1 5
#define EN_2 4
#define CW_2 16
#define CCW_2 17
#define EN_3 26
#define CW_3 25
#define CCW_3 33
#define EN_4 18
#define CW_4 19
#define CCW_4 21
#define EN_5 0
#define CW_5 0
#define CCW_5 0

int EN_n[] = {0, EN_1, EN_2, EN_3, EN_4};
int CW_n[] = {0, CW_1, CW_2, CW_3, CW_4};
int CCW_n[] = {0, CCW_1, CCW_2, CCW_3, CCW_4};

class Eje_n
{
    public:

    int EN = 0;
    int CW = 0;
    int CCW = 0;
    int vel = 0;
    int pwm = 0;
    bool invertir = false;

  Eje_n(int pin_EN, int pin_CW, int pin_CCW, bool invertir_ = false)
  {
      EN = pin_EN;
      CW = pin_CW;
      CCW = pin_CCW;
      vel = 0;
      pwm = 0;
      invertir = invertir;
  }
  
  void setSpeed(int velocidad) //+-255
  {
      velocidad = invertir?-velocidad:velocidad;

      if (velocidad == 0)
      {
          analogWrite(EN, 255);
          digitalWrite(CW, HIGH);
          digitalWrite(CCW, HIGH);
      }
      else if (velocidad > 0)
      {
          analogWrite(EN, velocidad);
          digitalWrite(CCW, LOW);
          digitalWrite(CW, HIGH); 
      }
      else if (velocidad < 0)
      {
          analogWrite(EN, -velocidad);
          digitalWrite(CW, LOW);
          digitalWrite(CCW, HIGH);
      }
      else
      {
          analogWrite(EN, 0);
          digitalWrite(CW, 0);
          digitalWrite(CCW, 0);
      }
  }
};

union Mensaje
{
  char bytes[4];
  struct
  {
    char code[2];
    signed short int value;
  };
};

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  // Declarar las salidas:
  for(int i: EN_n)
  {
    pinMode(i, OUTPUT);
  }
  for(int i: CW_n)
  {
    pinMode(i, OUTPUT);
  }
  for(int i: CCW_n)
  {
    pinMode(i, OUTPUT);
  }

  Serial.begin(115200);
  digitalWrite(LED, HIGH);
}

Eje_n eje1(EN_1, CW_1, CCW_1, false);
Eje_n eje2(EN_2, CW_2, CCW_2, false);
Eje_n eje3(EN_3, CW_3, CCW_3, false);
Eje_n eje4(EN_4, CW_4, CCW_4, false);

void loop() 
{
    if (Serial.available() >= 4) { // Check if data is available to read
      // Read the incoming string
      Mensaje mando;
      Serial.readBytes(mando.bytes, 4);
      Serial.write(mando.value);
      switch (mando.code[0])
      {
        default:
          mando.value = mando.value>>8;
          mando.value = mando.value>100?255:(mando.value<-100)?-255:0;
          eje1.setSpeed(mando.value);
      }
      }    /*
          if(mando.code[1] == 'Y')
            eje1.setSpeed(mando.value);
          else if (mando.code[1] == 'X')
            eje2.setSpeed(mando.value);
          break;

        case 'R':
          mando.value = mando.value>>8;
          if(mando.code[1] == 'Y')
            eje3.setSpeed(mando.value);
          else if (mando.code[1] == 'X')
            eje4.setSpeed(mando.value);
          break;
        default:
          break;
      }
    }
  //eje1.setSpeed(32000);
  digitalWrite(CW_1, HIGH);
  digitalWrite(CCW_1, LOW);
  analogWrite(EN_1, 255);
  delay(500);
  //eje1.setSpeed(0);
  digitalWrite(CW_1, LOW);
  digitalWrite(CCW_1, LOW);
  analogWrite(EN_1, 0);
  delay(500);
  //eje1.setSpeed(-32000);
  digitalWrite(CW_1, LOW);
  digitalWrite(CCW_1, HIGH);
  analogWrite(EN_1, 255);
  delay(500);
  //eje1.setSpeed(0);
  digitalWrite(CW_1, LOW);
  digitalWrite(CCW_1, LOW);
  analogWrite(EN_1, 0);
  delay(500);*/

  /*eje1.setSpeed(-255);
  delay(500);
  eje1.setSpeed(0);
  delay(500);
  eje1.setSpeed(+255);
  delay(500);
  eje1.setSpeed(0);
  delay(500);*/

}  
      /*if((char*)incomingString[4]=="R")
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
      }*/


