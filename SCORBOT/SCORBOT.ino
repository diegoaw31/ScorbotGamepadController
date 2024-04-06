#include <String.h>

#define DRIVERUSB 1

#if DRIVERUSB == 1

#define LADO 'L'
#define XYSW1 'X'   //driver motor 1,2  L,X,Y
#define XYSW2 'Y'   //driver motor 3,4, R,Y,X

#else

#define LADO 'R'
#define XYSW1 'Y'   //driver motor 1,2  L,X,Y
#define XYSW2 'X'   //driver motor 3,4, R,Y,X

#endif

#define LED 13 // LED_BUILTIN
#define EN_1 9
#define CW_1 2//revisar este pin
#define CCW_1 3
#define EN_2 10
#define CW_2 4
#define CCW_2 5
#define EN_3 0//11
#define CW_3 0//6
#define CCW_3 0//7

#define EN_4 0
#define CW_4 0
#define CCW_4 0
#define EN_5 0
#define CW_5 0
#define CCW_5 0

int EN_n[] = {0, EN_1, EN_2};
int CW_n[] = {0, CW_1, CW_2};
int CCW_n[] = {0, CCW_1, CCW_2};

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

    void setSpeed(signed short int velocidad) //+-255
    {
        velocidad = (velocidad>-1000&&velocidad<1000)?0:velocidad;
        velocidad/=128;
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

union Mensaje
{
    char bytes[4];
    struct
    {
        char hCode;
        char lCode;
        int16_t Value;
    };
};

void setup()
{
    // LED de control
    pinMode(LED, OUTPUT);
    pinMode(0,INPUT);
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

    Serial.begin(115200);
    digitalWrite(LED, HIGH);
}

Eje_n eje1(EN_1, CW_1, CCW_1, false); //driver motor 1,2 true false 
Eje_n eje2(EN_2, CW_2, CCW_2, false); //driver motor 3,4 false false
//Eje_n eje3(EN_3, CW_3, CCW_3, false);

void loop()
{
    if (Serial.available() >= 4)
    { // Check if data is available to read
        // Read the incoming string
        Mensaje mando;
        Serial.readBytes(mando.bytes, 4);
        //Serial.write(mando.bytes, 4);

        //asm("nop");
        switch (mando.hCode)
        {
        case LADO:
            switch (mando.lCode)
            {
            case XYSW1:
                eje1.setSpeed((signed short int)mando.Value);
                //Serial.write("EX");
                //Serial.write(mando.Value);
                break;
            case XYSW2:
                eje2.setSpeed((signed short int)mando.Value);
                //Serial.write("EY");
                ////Serial.write(mando.Value);
                break;
            // case '1':
            //     eje3.setSpeed((signed short int)mando.Value*32760);
            //     break;
            // case '2':
            //     eje3.setSpeed((signed short int)mando.Value*-32760);
            //     break;
            // default:
            //   eje1.setSpeed(0);
            //   eje2.setSpeed(0);
            }
        /*case 'G':
            switch (mando.lCode)
            {
            case 'X':
                break;
            case 'Y':
                break;
            case 'Z':
                break;
            default:
              delay(1);
            }
        case 'B':
            switch (mando.lCode)
            {
            case 'X':
                break;
            case 'Y':
                break;
            case 'Z':
                break;
            case 'W':
                break;
            default:
              delay(1);
            }*/

        default:
          delay(1);
            // mando.value = mando.value>100?255:(mando.value<-100)?-255:0;
            //eje1.setSpeed(mando.hValue);
        }
    }
}
