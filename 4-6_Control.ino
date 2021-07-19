/*
    Movement are directed as:
        10: Forward
        5 : Backward
        9 : Right
        6 : Left
    For speed you can provide any data greater than 10 and less than 255
*/
// listed numeric valued defines the pin in the arduino board
// they are defined but not used as the variable but as integer themself 
#define en0 6 // for PWM (speed) of motror 0
#define t0 7 // motor 0
#define t1 8
#define t2 9 // motro 
#define t3 10
#define en1 11 // for PWM (speed) of motor 1

bool t[4] = {0, 0, 0, 0}; // booleand array for motor driver terminals
unsigned int spd = 0, data=0; // variables for speed, serial data in interger
String temp_data; // variable for data to be sent via serial communication

void setup() // setup function
{
    pinMode(en0, OUTPUT);
    pinMode(t0, OUTPUT);
    pinMode(t1, OUTPUT);
    pinMode(t2, OUTPUT);
    pinMode(t3, OUTPUT);
    pinMode(en1, OUTPUT);
    
    Serial.begin(115200); // set serial communication at 115200bps
}

inline void get_data() // get data from serial communication
{
    data = 0; // set data to 0 by default 
    if (Serial.available() > 0) 
    {
    temp_data = Serial.read(); // read data from serial communication
    data = temp_data.toInt(); // convert data to integer
    Serial.println(data); // print data on serial communication
    }
}   

void manipulate(unsigned int data) // function to convert data to speed or motor direction control sginal
{
    if (data <= 10) // if data is less than 10, then use it as motor control signal
    {   int k = 8; // set k to 8 as refrence bit string of 00001000
        for (int i = 0; i < 4; i++)
        {
            // right shift the 00001000 by the i value and bitwise AND  it with serial data to get the bit value of lower nibble (4-i)th bit
            t[i] = (k >> i) & data;
            Serial.print(t[i]);
        }
        Serial.print("  ");
        Serial.println(spd);
    }
    else // if the data is greater than 10, then use it as speed (PWM) value
    {
        spd=data;
        for (int i = 0; i < 4; i++)
        {
            Serial.print(t[i]);
        }
        Serial.print("  ");
        Serial.println(spd);
    }
}

void mobilize(bool t[], unsigned int spd) // function to control the motor driver terminals
{
    // set = 8t PWM value for en0 and en1 pins
    analogWrite(en0, spd);
    analogWrite(en1, spd);

    // write t[i] to the pin j in motor driver
    digitalWrite(t0, t[0]);
    digitalWrite(t1, t[1]);
    digitalWrite(t2, t[2]);
    digitalWrite(t3, t[3]);
}

void loop()
{
    get_data(); // get data from serial communication
    manipulate(data); // convert data to speed or motor direction control sginal
    mobilize(t,spd); // control the motor driver terminals and as a whole the bot
    delay(1000); // read signal after every 1 second
}
