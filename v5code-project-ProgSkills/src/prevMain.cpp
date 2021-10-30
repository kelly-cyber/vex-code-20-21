#include "vex.h"
#include "Util.h"
#include "MovementFuncs.h"
#include "Definitions.h"
#include "Odom.h"
#include <PID.h>
#include <cmath>


//code from comp 1/23
// int main() {
  
//   vexcodeInit();// Initializing Robot Configuration.
//   Init(); // initializes Inertial sensor and variables
//   Threads();// starts inertial correction thread
//   // StrafeXY(360, 360, 100, 5);

//   //1 rotation = 13 inches
//   //starting pos 25 deg

//   //timeFwdRev(-60, 0.55) == moveFwdRev(60, -360);

//   indexerFunc(1.5, "in"); //ball 0 scored
//   moveFwdRev(60, -390);
//   TurnInPlace(180, 0.7, 10);
//   timeFwdRev(60, 0.3);
//   intakeFunc(2, "in"); //ball 1 acquired (middle home row)

//   TurnInPlace(140, 0.7, 10); //global degrees with respect to starting position
//   timeFwdRev(60, 1.8);
//   //intakev = true; //descore blue balls
//   indexerFunc(1.5, "in"); //ball 2 scored (right home row)
//   TurnInPlace(145, 0.7, 10); //correct angle on tower

//   moveFwdRev(60, -400);
//   TurnInPlace(200, 0.7, 10); 
//   intakev = true;
//   timeFwdRev(60, 1.5);
//   indexerFunc(0.2, "in"); //ball 3 accquired 

//   TurnInPlace(240, 0.7, 10); 
//   moveFwdRev(60, 520);
//   TurnInPlace(270, 0.7, 10); 
//   intakeFunc(0.3, "out");
//   timeFwdRev(60, 0.7);
//   intakev = true; //ball 4 accquired 
//   indexerFunc(0.3, "in");
//   moveFwdRev(60, 200);
//   TurnInPlace(180, 0.7, 10);
//   timeFwdRev(60, 0.3);
//   intakev = true;
//   indexerFunc(1, "in"); //ball 3 + 4 scored (right side middle)

//   intakeFunc(0.5, "out");
//   TurnInPlace(-30, 0.7, 10); //correct angle on tower

//   moveFwdRev(60, 400);
//   TurnInPlace(315, 0.7, 10); 
//   intakev = true;
//   moveFwdRev(60, 400); //ball 5 accquired
//   timeFwdRev(60, 1.4);
//   intakev = true;
//   indexerFunc(3, "in");//ball 5 scored (middle) descore?
//   moveFwdRev(60, -400);


//   StopMotorsEnd();// turns off motors
//   return 0; 

// }


// //competition code from 1/16 


// bool intakev;
// int intake(){ //thread
  
//   while (true){
//   if (intakev == true){
//   intakeFunc(3,"in");
//   intakev= false;
//   }
//   vex::task::sleep(20);
//   }
  
//   return(0);
// }
// vex::thread t( intake );

// int main(){
//   indexerFunc(1.5, "in"); //ball 0 scored
//   moveFwdRev(60, -390);
//   TurnInPlace(180, 0.7, 10);
//   moveFwdRev(60, 140);
//   intakeFunc(2, "in"); //ball 1 acquired (middle home row)

//   return 0;

//   TurnInPlace(138, 0.7, 10); //global degrees with respect to starting position
//   moveFwdRev(60, 1200);
//   //intakev = true; //descore blue balls
//   indexerFunc(1.5, "in"); //ball 2 scored (right home row)

//   moveFwdRev(60, -400);
//   TurnInPlace(190, 0.7, 10); 
//   intakeFunc(0.5, "out");
//   intakev = true;
//   moveFwdRev(60, 1100);
//   indexerFunc(0.2, "in"); //ball 3 accquired 

//   TurnInPlace(240, 0.7, 10); 
//   moveFwdRev(60, 720);
//   intakeFunc(0.5, "out");
//   TurnInPlace(280, 0.7, 10); 
//   moveFwdRev(60, 300);
//   intakev = true; //ball 4 accquired 
//   indexerFunc(0.3, "in");
//   moveFwdRev(60, 200);
//   TurnInPlace(180, 0.7, 10);
//   moveFwdRev(60, 100);
//   intakev = true;
//   indexerFunc(1, "in"); //ball 3 + 4 scored (right side middle)

//   moveFwdRev(60, -400);
//   TurnInPlace(315, 0.7, 10); 
//   intakev = true;
//   moveFwdRev(60, 400); //ball 5 accquired
//   moveFwdRev(60, 900);
//   intakev = true;
//   indexerFunc(3, "in");//ball 5 scored (middle) descore?
//   moveFwdRev(60, -400);

//   intakeFunc(0.5, "out");

//   intakeFunc(1, "in");
//   moveFwdRev(60, -720);

//   moveFwdRev(60, 720);

//   StopMotorsEnd();// turns off motors
//   return 0; 
// }
