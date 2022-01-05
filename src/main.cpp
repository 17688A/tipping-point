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
// PneumaticBack        digital_out   B               
// RedLED               digital_out   H               
// YellowLED            digital_out   G               
// GreenLED             digital_out   F               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

  int pneumaticStatus = 0;
  int pneumaticStatusBack = 0;
  int powerStatus = 0;
  int actPowerStatus = 0;
  int driveDirection = 0;

void pre_auton(void){
}
// Battery Percent LED Code
  int BatteryPercent(){
    int currentPercent = Brain.Battery.capacity();
      if (currentPercent > 51 ) {
      RedLED.set(true);
      YellowLED.set(true);
      RedLED.set(true);
      }
      else if(currentPercent > 25) {
      YellowLED.set(true);
      RedLED.set(true);
      }
      else if(currentPercent > 10){
      RedLED.set(true);
      }
      vex::task::sleep(20);
    return 1;
  }



void autonomous(void){
  vex::task Battery(BatteryPercent);
}
// Start of usercontrol code

  int CustumController(){
  // MAX (X,Y) = (479,239)
    return 1;
  }
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
    void PneumaticSwitchBack()
    {
      switch(pneumaticStatusBack)
      {
        case 0:
        {
          pneumaticStatusBack = 1;
          PneumaticBack.set(true);
          break;
        }
        case 1:
        {
          pneumaticStatusBack = 0;
          PneumaticBack.set(false);
          break;
        }
      }
    }
    // End of usercontrol code
void usercontrol(void){
  Controller1.ButtonX.pressed(PneumaticSwitch);
  Controller1.ButtonA.pressed(PneumaticSwitchBack);
}
//launch via the main class 
int main() {
  // Set up callbacks for autonomous and driver control periods.
  competition.autonomous(autonomous);
  competition.drivercontrol(usercontrol); 
  // Run the preautonomous function
  pre_auton();
  // Never ending timer
  waitUntil(false);
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}
