#include <RASLib/inc/common.h>
#include <RASLib/inc/gpio.h>
#include <RASLib/inc/time.h>
#include <RASLib/inc/motor.h>
#include <RASLib/inc/linesensor.h>
#include <RASLib/inc/adc.h>

// Blink the LED to show we're on
tBoolean blink_on = true;

void blink(void) {
    SetPin(PIN_F3, blink_on);
    blink_on = !blink_on;
}

void clockwisemode(void){
  if(distvalcw<=0.35)
  {
    SetMotor(left, 1.0);
    SetMotor(right, -0.55);
  }
  else if(0.35<distvalcw<=0.4)
  {
    SetMotor(left, 1.0);
    SetMotor(right, -0.75);
  }
  else if(0.4<distvalcw<=0.45)
  {
    SetMotor(left, 1.0);
    SetMotor(right, -0.85);
  }
  else if(0.6>distvalcw>=0.55)
  {
    SetMotor(left, 0.85);
    SetMotor(right, -1.0);
  }
  else if(0.65>distvalcw>=0.6)
  {
    SetMotor(left, 0.75);
    SetMotor(right, -1.0);
  }
  else if(distvalcw>=0.65)
  {
    SetMotor(left, 0.55);
    SetMotor(right, -1.0);
  }
  else
  {
    SetMotor(left, 1.0);
    SetMotor(right, -1.0);
  }
}
void counterclockwisemode(void){
  if(distvalccw<=0.35)
  {
    SetMotor(left, 0.55);
    SetMotor(right, -1.0);
  }
  else if(0.35<distvalccw<=0.4)
  {
    SetMotor(left, 0.75);
    SetMotor(right, -1.0);
  }
  else if(0.4<distvalccw<=0.45)
  {
    SetMotor(left, 0.85);
    SetMotor(right, -1.0);
  }
  else if(0.6>distvalccw>=0.55)
  {
    SetMotor(left, 1.0);
    SetMotor(right, -0.85);
  }
  else if(0.65>distvalccw>=0.6)
  {
    SetMotor(left, 1.0);
    SetMotor(right, -0.75);
  }
  else if(distvalccw>=0.65)
  {
    SetMotor(left, 1.0);
    SetMotor(right, -0.55);
  }
  else
  {
    SetMotor(left, 1.0);
    SetMotor(right, -1.0);
  }
}
// The 'main' function is the entry point of the program
int main(void) {
    // Initialization code can go here
    CallEvery(blink, 0, 0.5);
    tMotor *left = InitializeServoMotor(PIN_D0, true);
    tMotor *right = InitializeServoMotor(PIN_D1, false);
    /*tLineSensor *line = InitializeGPIOLineSensor(PIN_D0, PIN_D1, PIN_D2, PIN_D3, PIN_D4, PIN_E1, PIN_E2, PIN_E1);
    float linevals[8];*/
    tADC *dist = InitializeADC(PIN_B0);
    float distvalcw;
    tADC *dist2 = InitializeADC(PIN_B1);
    float distvalccw;
    while (1) {
        // Runtime code can go here
        //SetMotor(left, 1.0);
        //SetMotor(right, -1.0);
        /*LineSensorReadArray(line, linevals);
        Printf(“%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t”, value[0], value[1], value[2],
          value[3], value[4], value[5], value[6], value[7]);*/
        distvalcw = ADCRead(dist);
        //Printf("IR sensor value is %f\n", distvalcw);
        distvalccw = ADCRead(dist2);
        //Printf("IR sensor value is %f\n", distvalccw);
        if(0.55>=distvalcw>=0.45)
        {
          //CallEvery(blink, 0, 1.5); //determine if robot is in right spot??
          clockwisemode();
        }
        else if(0.55>=distvalccw>=0.45)
        {
          counterclockwisemode();
        }
        else
        {
          return;
        }
        /*if(0.8>distval>0.5)
        {SetMotor(left, 1.0);
        SetMotor(right, -0.8);}
        else if (0.95<distval)
        {SetMotor(left, 0.5);
        SetMotor(right, -1.0);}
        else if (0.5>distval>0)
        {SetMotor(left,1.0);
        SetMotor(right,-0.5);}*/



    }
}