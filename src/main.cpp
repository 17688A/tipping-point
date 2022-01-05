/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Carter                                                    */
/*    Created:      Tue Dec 14 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 2            
// Pneumatic            digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

  int pneumaticStatus = 0;
  int powerStatus = 0;
  int actPowerStatus = 0;
  int driveDirection = 0;

  // Functions
  
  void PneumaticSwitch()
  {
    switch(pneumaticStatus)
    {
      case 0:
      {
        pneumaticStatus = 1;
        Pneumatic.set(true);
        break;
      }
      case 1:
      {
        pneumaticStatus = 0;
        Pneumatic.set(false);
        break;
      }
    }
  }

void Power()
  {
    switch(powerStatus)
    {
      case 0:
      {
        powerStatus = 1;
        Controller1.Screen.clearLine(3); 
        Controller1.Screen.print("Default Speed");
        Drivetrain.setDriveVelocity(75, percent);
        actPowerStatus = 75;
        break;
      }
      case 1:
      {
        powerStatus = 0;
        Controller1.Screen.clearLine(3); 
        Controller1.Screen.print("Speed");
        Drivetrain.setDriveVelocity(100, percent);
        actPowerStatus = 75;
        break;
      }
    }
  }

//launch via the main class 
int main() 
{
  Brain.Screen.clearScreen();
  Brain.Screen.print("DEBUG: Teleop\n");
  Drivetrain.setDriveVelocity(75, percent);  
  Controller1.ButtonX.pressed(PneumaticSwitch);
  Controller1.ButtonUp.pressed(Power);

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}
