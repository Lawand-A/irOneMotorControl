#include <IRremote.h>

//Those codes must be found out from the remote control
#define CLOCKWISE 0xE0E046B9
#define ANTICLOCKWISE 0xE0E0A659
#define STOP 0xE0E040BF
#define INCREASE 0xE0E006F9
#define DECREASE 0xE0E08679

//See the circuit schematic Pictures
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;


int motorPin1 = 9;
int motorPin2 = 10;
bool currentStatus = 0;   //This variable tells us if we move clockwise or anticlockwise

//The values of the speed (Max. is 255)
int normalSpeed = 225;
int decreaseSpeed = 200;
int increaseSpeed = 255;


void motorForward(){
    // motor forward
    analogWrite( motorPin1, normalSpeed );
    analogWrite( motorPin2, LOW );
    currentStatus = 1;
}


void motorBackward(){
    // motor backward
    analogWrite( motorPin1, LOW );
    analogWrite( motorPin2, normalSpeed );
    currentStatus = 0;
}


void increaseMotorSpeed(){
    // increase Motor Speed
    if(currentStatus){
          analogWrite( motorPin1, increaseSpeed );
          analogWrite( motorPin2, LOW );
    } else{
          analogWrite( motorPin1, LOW );
          analogWrite( motorPin2, increaseSpeed );
    }
}


void decreaseMotorSpeed(){
  // decrease Motor Speed
    if(currentStatus){
        analogWrite( motorPin1, decreaseSpeed );
        analogWrite( motorPin2, LOW );
    } else {
        analogWrite( motorPin1, LOW );
        analogWrite( motorPin2, decreaseSpeed );
    }
}


void motorStop(){
    // motor stop
    analogWrite( motorPin1, LOW );
    analogWrite( motorPin2, LOW );
}


void setup(){
    Serial.begin(9600);
  
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
  
    irrecv.enableIRIn();
}


void loop(){

    if (irrecv.decode(&results)){
        unsigned int value = results.value;
        switch( value ){
            case CLOCKWISE:
                motorForward();
                break;
        
            case ANTICLOCKWISE:
                motorBackward();
                break;
        
            case STOP:
                motorStop();
                break;
        
            case INCREASE:
                increaseMotorSpeed();
                break;
        
            case DECREASE:
                decreaseMotorSpeed();
                break;
        }
        irrecv.resume();
    }
}
