/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       kellyzhang                                                */
/*    Created:      Sat Jan 09 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// TR                   motor         1               
// TL                   motor         2               
// BR                   motor         3               
// BL                   motor         4               
// RIntake              motor         5               
// LIntake              motor         6               
// yRot                 rotation      14              
// Inertial16           inertial      17              
// xRot                 rotation      15              
// topIndexer           motor         8               
// bottomIndexer        motor         7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "Util.h"
#include "MovementFuncs.h"
#include "Definitions.h"
#include "Odom.h"
#include <PID.h>
#include <cmath>

using namespace vex;

// Variable Definitions//

float inert;
double yTurnOffset; 
double xTurnOffset; 
double inertError; 
double xPos; 
double yPos;
bool intakev;


int Async(){

while (true){
  BckGround(); // background operations; inertCorrection & odom
}

return(0);
}

void Threads(){
vex::thread t( Async );
}


int intake(){ //thread
  
  while (true){
  if (intakev == true){
  intakeFunc(3,"in");
  intakev= false;
  }
  vex::task::sleep(20);
  }
  
  return(0);
}
vex::thread t( intake );

/*---------------------------------------------\\
||                                             ||
||           KEEP  int main() CLEAN!!          ||
||                                             ||
\\---------------------------------------------*/
  
int main() {
  
  vexcodeInit();// Initializing Robot Configuration.
  Init(); // initializes Inertial sensor and variables
  Threads();// starts inertial correction thread
  // StrafeXY(360, 360, 100, 5);

  //1 rotation = 13 inches
  //starting pos 25 deg

  //timeFwdRev(-60, 0.55) == moveFwdRev(60, -360);

  indexerFunc(1.5, "in"); //ball 0 scored
  moveFwdRev(60, -390);
  TurnInPlace(180, 0.7, 10);
  timeFwdRev(60, 0.3);
  intakeFunc(2, "in"); //ball 1 acquired (middle home row)

  TurnInPlace(140, 0.7, 10); //global degrees with respect to starting position
  timeFwdRev(60, 1.8);
  //intakev = true; //descore blue balls
  indexerFunc(1.5, "in"); //ball 2 scored (right home row)
  TurnInPlace(145, 0.7, 10); //correct angle on tower

  moveFwdRev(60, -400);
  TurnInPlace(200, 0.7, 10); 
  intakev = true;
  timeFwdRev(60, 1.5);
  indexerFunc(0.2, "in"); //ball 3 accquired 

  TurnInPlace(240, 0.7, 10); 
  moveFwdRev(60, 520);
  TurnInPlace(270, 0.7, 10); 
  intakeFunc(0.3, "out");
  timeFwdRev(60, 0.7);
  intakev = true; //ball 4 accquired 
  indexerFunc(0.3, "in");
  moveFwdRev(60, 200);
  TurnInPlace(180, 0.7, 10);
  timeFwdRev(60, 0.3);
  intakev = true;
  indexerFunc(1, "in"); //ball 3 + 4 scored (right side middle)

  intakeFunc(0.5, "out");
  TurnInPlace(-30, 0.7, 10); //correct angle on tower

  moveFwdRev(60, 400);
  TurnInPlace(315, 0.7, 10); 
  intakev = true;
  moveFwdRev(60, 400); //ball 5 accquired
  timeFwdRev(60, 1.4);
  intakev = true;
  indexerFunc(3, "in");//ball 5 scored (middle) descore?
  moveFwdRev(60, -400);


  StopMotorsEnd();// turns off motors
  return 0; 

}
