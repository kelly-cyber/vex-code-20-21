#include "vex.h"
#include "Definitions.h"
#include "Odom.h"

void StopMotorsEnd(){

  TR.stop(brake);
  TL.stop(brake);
  BR.stop(brake);
  BL.stop(brake);
}

void Clear(){
  Brain.Screen.clearScreen();
}
void Correct(){
    
inert =  Inertial16.heading(degrees) + Inertial16.rotation(degrees) * inertError;// corrects the heading
if (inert<0){
  inert+=360;
}
}

void Print (int col, int row, char text){ // a print function so we dont have to write all this stuff every time
   Brain.Screen.setCursor(col,row);
  Brain.Screen.print(text);

}

void BckGround(){ // background operations
  Clear(); // clears the brain screen
  Correct(); // corrects the inertial sensor
  OdomRun(); // calculators Odometry
  Print(1,1,xPos); // prints stuff
  Print(2,1,yPos);
  Print(4,1,inert);
  vex::task::sleep (20); // sleeps to not overload the system
}