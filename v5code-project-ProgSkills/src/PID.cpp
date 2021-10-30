#include "vex.h"
#include "Util.h"
#include "Definitions.h"
#include "PID.h"

void inertTurnPID(float Deg, double KP, double KI, double KD){ //guess and check KP, KI, KD start w 1

  //initialize variables
  int Error = Deg; //Error is Deg - inert sensor value
  int Integral = 0; //curve to reach target
  int Deriv = 0; //Error - prevError. How quickly reach target
  int prevError = 0;
  double motorPower; //what we want to find

  while(Error != 0){
    Error = Deg - Inertial16.rotation(degrees);

    if(Error == 0){ //position reached
      Integral = 0;
    }

    if(abs(Error) > 40){ //error too big (avoids issues)
      Integral = 0;
    }

    motorPower = Error*KP + Integral*KI + Deriv*KD; //need minSpeed?

    TR.spin(forward, -motorPower, dps);// fires up motors
    TL.spin(forward, motorPower, dps);
    BR.spin(forward, -motorPower, dps);
    BL.spin(forward, motorPower, dps);

    prevError = Error;

    vex::task::sleep(20); //20 milliseconds, frees up CPU
  }
}


void fwdPID(int setPt){
  int Error = setPt;
  //int Dist = 0; //UNUSED?
  double KP = 1;

  TR.resetPosition();
  TL.resetPosition();
  BR.resetPosition();
  BL.resetPosition();

  while(Error != 0){
    Error = setPt - (TR.position(degrees) + BR.position(degrees))/2 - (TL.position(degrees) + BL.position(degrees))/2; //estimate center by /2

    double powerDif = (TR.position(degrees) + BR.position(degrees))/2 - (TL.position(degrees) + BL.position(degrees))/2;
    powerDif *= KP;

    TR.spinFor(forward, 50+powerDif, seconds);
    TL.spinFor(forward, 50+powerDif, seconds);
    BR.spinFor(forward, 50-powerDif, seconds);
    BL.spinFor(forward, 50-powerDif, seconds);
  }
}