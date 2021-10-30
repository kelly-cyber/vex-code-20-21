#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor TR = motor(PORT1, ratio18_1, true);
motor TL = motor(PORT2, ratio18_1, false);
motor BR = motor(PORT3, ratio18_1, true);
motor BL = motor(PORT4, ratio18_1, false);
motor RIntake = motor(PORT5, ratio18_1, false);
motor LIntake = motor(PORT6, ratio18_1, true);
rotation yRot = rotation(PORT14, true);
inertial Inertial16 = inertial(PORT17);
rotation xRot = rotation(PORT15, false);
motor topIndexer = motor(PORT8, ratio18_1, true);
motor bottomIndexer = motor(PORT7, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}