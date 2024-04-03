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
#define CW_1 2  //revisar este pin
#define CCW_1 3
#define EN_2 10
#define CW_2 4
#define CCW_2 5
#define EN_3 0
#define CW_3 0
#define CCW_3 0

#define EN_4 0
#define CW_4 0
#define CCW_4 0
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

Eje_n eje1(EN_1, CW_1, CCW_1, false); //driver motor 1,2 
Eje_n eje2(EN_2, CW_2, CCW_2, false); //driver motor 3,4 false false

void loop()
{
    if (Serial.available() >= 4)
    { // Check if data is available to read
        // Read the incoming string
        Mensaje mando;
        Serial.readBytes(mando.bytes, 4);
        //Serial.write(mando.bytes, 4);

        switch (mando.hCode)
        {
        case LADO:
            switch (mando.lCode)
            {
            case XYSW1:
                eje1.setSpeed(mando.Value);
                //Serial.write("EX");
                //Serial.write(mando.Value);
                break;
            case XYSW2:
                eje2.setSpeed((signed short int)mando.Value);
                //Serial.write("EY");
                ////Serial.write(mando.Value);
                break;
            default:
              eje1.setSpeed(0);
              eje2.setSpeed(0);
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
