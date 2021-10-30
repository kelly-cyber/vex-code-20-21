#include "vex.h"
#include "Definitions.h"
#include <cmath> 

double xStore;
double yStore;
double inertStore;
double cyrot;
double cxrot;

void OdomRun(){

  // cyrot = yRot.position(degrees) - (Inertial16.rotation(degrees) * inertError)*0.65;
  // cxrot = xRot.position(degrees) - (Inertial16.rotation(degrees) * inertError)*4.45277;
  
  double sx = xStore -(xRot.position(degrees));//stores rotational sensor inputs
  double sy = yStore -(yRot.position(degrees));
  float si = (inertStore - inert)*(3.141592653589/180);
  
  xStore = xRot.position(degrees);// sets stored values to encoder values
  yStore = yRot.position(degrees);
  inertStore = inert;

  double lx;
  double ly;

  if (si != 0){
    lx = 2*sin((si/2)) * (sx/si+0);
    ly = 2*sin((si/2)) * (sy/si+0);// replace + 0 with 
  }else
  {
    lx = sx;
    ly = sy;
  }

if (std::isnan (ly)){
  ly = 0;
}
if (std::isnan (lx)){
  lx = 0;
}

double th = inert*(3.14159265358979/180)+ si;

double h = hypot(ly,lx);
//finds distance traveled by finding hypotenuse of local x and y values. 


double t = atan2(ly,lx)-th;

double ay = h*sin(t);
// usese some trig to find the global x position by using the bots heading and the distance it traveled. 
double ax = h*cos(t);

if (std::isnan (ay)){
  ay = 0;
}
if (std::isnan (ax)){
  ax = 0;
}

yPos -= ay;
xPos += ax;
inertStore = inert;

}