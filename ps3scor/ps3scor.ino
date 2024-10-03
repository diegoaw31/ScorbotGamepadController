#include <Ps3Controller.h>

#define LED 2 // LED_BUILTIN
#define EN_1 26
#define CW_1 25
#define CCW_1 33
#define EN_2 21
#define CW_2 19
#define CCW_2 18
#define EN_3 27
#define CW_3 14
#define CCW_3 12

#define EN_4 4
#define CW_4 15
#define CCW_4 5
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
        invertir = invertir_;
    }

    void setSpeed(signed short int velocidad) //+-127
    {
        velocidad = (velocidad>-20&&velocidad<20)?0:velocidad;
        velocidad*=2;
        velocidad = constrain(velocidad, -255, 255);
        velocidad = invertir ? -velocidad : velocidad;

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



void setup()
{
    // LED de control
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    // Declarar las salidas:
    for (int i : EN_n)
    {
        pinMode(i, OUTPUT);
    }
    for (int i : CW_n)
    {
        pinMode(i, OUTPUT);
    }
    for (int i : CCW_n)
    {
        pinMode(i, OUTPUT);
    }

    Ps3.begin("38:3c:4a:4f:26:22");

    digitalWrite(LED, HIGH);
}

Eje_n eje1(EN_1, CW_1, CCW_1, false); //driver motor 1,2 true false 
Eje_n eje2(EN_2, CW_2, CCW_2, false); //driver motor 3,4 false false
Eje_n eje3(EN_3, CW_3, CCW_3, false);
Eje_n eje4(EN_4, CW_4, CCW_4, false);

void loop()
{
    //---------------- Analog stick value events ---------------
   if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
        eje1.setSpeed(Ps3.data.analog.stick.lx);
        eje2.setSpeed(Ps3.data.analog.stick.ly);
    }

   if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
        eje3.setSpeed(Ps3.data.analog.stick.ry);
        eje4.setSpeed(Ps3.data.analog.stick.rx);
   }
}
