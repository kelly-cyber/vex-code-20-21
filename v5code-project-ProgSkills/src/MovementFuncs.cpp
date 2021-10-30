#include "vex.h"
#include "Util.h"
#include "Definitions.h"
#include "MovementFuncs.h"


void timeFwdRev(int motorPower, float sec){ //both neg to rev

  //set velocities for drivetrain motors
  TR.setVelocity(motorPower, pct);
  TL.setVelocity(motorPower, pct);
  BR.setVelocity(motorPower, pct);
  BL.setVelocity(motorPower, pct);

  //int Degrees = inches/13*360; //convert inches to degrees

  //spin until reached seconds
  TR.spin(forward);
  TL.spin(forward);
  BR.spin(forward);
  BL.spin(forward);
  
  wait(sec, seconds);

  StopMotorsEnd(); //instead of stopping motors, wait(delay in seconds, seconds)?

}


void moveFwdRev(double motorPower, int Degrees){ //neg degrees to move rev

  yRot.setPosition(0, degrees); //set y encoder to 0
  double KP = 1;
  motorPower = motorPower*0.01; //pct

  //set velocities for drivetrain motors
  TR.setVelocity(motorPower, pct);
  TL.setVelocity(motorPower, pct);
  BR.setVelocity(motorPower, pct);
  BL.setVelocity(motorPower, pct);

  //int Degrees = inches/13*360; //convert inches to degrees
  int Error = Degrees;

  TR.spin(forward);
  TL.spin(forward);
  BR.spin(forward);
  BL.spin(forward);

  while(Error != 0){
    Error = Degrees - yRot.position(degrees); //(TR.position(degrees) + BR.position(degrees))/2 - (TL.position(degrees) + BL.position(degrees))/2; //estimate center by /2

    double powerDif = Error/6; //if we're 120 deg from target, speed is 20pct
    if(powerDif>100){
      powerDif=100;
    }
     if(powerDif<-100){
      powerDif=-100;
    }
    powerDif *= KP;

    if(Error > 3){
      TR.setVelocity(motorPower*powerDif + 3, pct);
      TL.setVelocity(motorPower*powerDif + 3, pct);
      BR.setVelocity(motorPower*powerDif + 3, pct);
      BL.setVelocity(motorPower*powerDif + 3, pct);
    } else if(Error < -3){
      TR.setVelocity(motorPower*powerDif - 3, pct);
      TL.setVelocity(motorPower*powerDif - 3, pct);
      BR.setVelocity(motorPower*powerDif - 3, pct);
      BL.setVelocity(motorPower*powerDif - 3, pct);
    }

    vex::task::sleep(20); // sleep to not overload the system
  }

  StopMotorsEnd(); //instead of stopping motors, wait(delay in seconds, seconds)?

}

// void moveFwdRev(int motorPower, int Degrees){ //both neg to rev

//   yRot.setPosition(0, degrees); //set y encoder to 0

//   //set velocities for drivetrain motors
//   TR.setVelocity(motorPower, pct);
//   TL.setVelocity(motorPower, pct);
//   BR.setVelocity(motorPower, pct);
//   BL.setVelocity(motorPower, pct);

//   //int Degrees = inches/13*360; //convert inches to degrees

//   while(yRot.position(degrees) < Degrees){ //spin until reached degrees
//     TR.spin(forward);
//     TL.spin(forward);
//     BR.spin(forward);
//     BL.spin(forward);
//   }

//   StopMotorsEnd(); //instead of stopping motors, wait(delay in seconds, seconds)?

// }

void TurnInPlace(float Deg, double slowDown, int minSpeed){ 
  //Deg desired degrees
  //inert current degress

  float inertDif = Deg-inert; //degrees need to turn

  TR.spin(forward);// fires up motors
  TL.spin(forward);
  BR.spin(forward);
  BL.spin(forward);
   
   /* in the case of when a robot turns from 1 degree to 360
      it only really turns 1 degree, but it will read as -359 degrees, 
      that's why this loop is here. */

  while (inertDif*inertDif > 0.5){ // why squared? 
      inertDif =  Deg-inert; //constantly check
   
    if(inertDif > 180){ //can turn the other direction faster
      inertDif -=360;
    }
     if(inertDif < -180){ //can turn the other direction faster
      inertDif +=360;
    }
  
    //set speed depending on distance away 
    //fabs = float abs value
    double inertDifSquared = inertDif* fabs(inertDif); //keeps its original direction (+ or -)
    double fracOfInertDif = slowDown * fabs(inertDif); //PID quadratic part-- goes in denominator, if slowDown was 1 would be linear
    double speedNeeded = inertDifSquared/fracOfInertDif;
    if (inertDif>0){  

      TR.setVelocity(-speedNeeded - minSpeed ,pct);//right ones need to be reversed
      TL.setVelocity(speedNeeded + minSpeed ,pct); //minspeed prevents not moving when really close to target
      BR.setVelocity(-speedNeeded - minSpeed ,pct); 
      BL.setVelocity(speedNeeded + minSpeed ,pct);

      //original long code
      // TR.setVelocity(((-inertDif)* fabs( inertDif))/(slowDown * abs((int) inertDif))-minSpeed,pct);// fun pid stuff
      // TL.setVelocity(((inertDif)* fabs( inertDif))/(slowDown * abs((int) inertDif))+minSpeed,pct); //fabs = float abs value
      // BR.setVelocity(((-inertDif)* fabs( inertDif))/(slowDown * abs((int) inertDif))-minSpeed,pct); //quadratic
      // BL.setVelocity(((inertDif)* fabs( inertDif))/(slowDown * abs((int) inertDif))+minSpeed,pct);
    }else{
      TR.setVelocity(-speedNeeded + minSpeed ,pct);// same idea as above, but +minSpeed bc inertDif is neg
      TL.setVelocity(speedNeeded - minSpeed ,pct);
      BR.setVelocity(-speedNeeded + minSpeed, pct);
      BL.setVelocity(speedNeeded -minSpeed, pct);
    }
      //linear version for understanding
      // TR.setVelocity(-inertDif+minSpeed,pct);
      // TL.setVelocity(inertDif-minSpeed,pct);
      // BR.setVelocity(-inertDif+minSpeed,pct);
      // BL.setVelocity(inertDif-minSpeed,pct);

    vex::task::sleep(20); // sleep to not overload the system
  }


  StopMotorsEnd();// stops all motors
}

void intakeFunc(float sec, std::string type){

  RIntake.setVelocity(100,pct);
  LIntake.setVelocity(100,pct);
  
  if(type == "in"){
  RIntake.spin(forward);
  LIntake.spin(forward);
  }else{
  RIntake.spin(reverse);
  LIntake.spin(reverse);
  }


  wait(sec, seconds);

  RIntake.stop();
  LIntake.stop();
}

void indexerFunc(float sec, std::string type){

  topIndexer.setVelocity(100, pct);
  bottomIndexer.setVelocity(100, pct);

  if(type == "in"){
    topIndexer.spin(forward);
    bottomIndexer.spin(forward);
  } else{
    topIndexer.spin(reverse);
    bottomIndexer.spin(forward);
  }

  wait(sec, seconds);

  topIndexer.stop();
  bottomIndexer.stop();
}



/*

Cartesian Strafe Function

*/


void StrafeXY(double x, double y, int speed, double decel){

double th = 90 - atan2(y,x)*(180/3.14159265);

double xst = xRot.position(degrees);
double yst = yRot.position(degrees);


TL.spin(forward);
TR.spin(forward);
BL.spin(forward);
BR.spin(forward);


if (th-inert<0){
  th = (3.14159265/180) * (450-(th-inert+360));
}else{

th = (3.14159265/180) * (450-(th-inert));
}


double px = -cos(th + 3.14159265/4);
double py = sin(th + 3.14159265/4);

double sp = (std::max(fabs(py),fabs(px)))/(speed*0.01);

double xDis = (xst+x)-xRot.position(degrees);
double yDis = (yst+y)-yRot.position(degrees);
double yVel = 1;
double xVel = 1;

while (fabs(xDis)>5 or fabs(yDis)>5){

xDis = (xst+x)-xRot.position(degrees);
yDis = (yst+y)-yRot.position(degrees);

yVel -= 0.01;
xVel -= 0.01;

TL.setVelocity(((py*yVel)/sp)*100,pct);
TR.setVelocity(((px*xVel)/sp)*100,pct);
BL.setVelocity(((px*xVel)/sp)*100,pct);
BR.setVelocity(((py*yVel)/sp)*100,pct);

vex::task::sleep(20);

}
StopMotorsEnd();
}



// different strafe function using polar instead of cartisean plane



void SetVelocityTheta(double th, double speed, std::string state){
TL.spin(forward);
TR.spin(forward);
BL.spin(forward);
BR.spin(forward);

if (state == "local"){
  th = (3.14159265/180) * (450-(th));
}else{
if (th-inert<0){
  th = (3.14159265/180) * (450-(th-inert+360));
}else{

th = (3.14159265/180) * (450-(th-inert));
}
}

double px = -cos(th + 3.14159265/4);
double py = sin(th + 3.14159265/4);

double sp = (std::max(fabs(py),fabs(px)))/(speed);

TL.setVelocity((py/sp)*100,pct);
TR.setVelocity((px/sp)*100,pct);
BL.setVelocity((px/sp)*100,pct);
BR.setVelocity((py/sp)*100,pct);
























}