/*
    Movement are directed as:
        10: Forward
        5 : Backward
        9 : Right
        6 : Left
    For speed you can provide any data greater than 10 and less than 255
*/

#define en0 6
#define t0 7
#define t1 8
#define t2 9
#define t3 10
#define en1 11

bool t[4] = {0, 0, 0, 0};
unsigned int spd = 0, k = 8, data=0, i, j;

void setup()
{
    for (i = 6; i <= 11; i++)
    {
        pinMode(i, OUTPUT);
    }
    Serial.begin(9600);
}

inline void get_data()
{
    if (Serial.available() > 0)
        data = Serial.read();
    else
        data = 0;
}

void manipulate(unsigned int data)
{
    if (data <= 10)
    {
        for (i = 0; i < 4; i++)
        {
            t[i] = k >> i & data;
            Serial.print(t[i]);
        }
        Serial.print("  ");
        Serial.println(spd);
    }
    else
    {
        spd=data;
        Serial.println(spd);
    }
}

void mobilize(bool t[], unsigned int spd)
{
    for (i = 6; i <= 11; i+6)
        analogWrite(i, spd);

    for (i = 0, j = 7; i < 4; i++, j++)
        digitalWrite(j, t[i]);
}

void loop()
{
    get_data();
    manipulate(data);
    mobilize(t,spd);
    delay(1000);
}
