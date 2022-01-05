/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------*/
/*Refrences for Carter                                                                 */
/*https://api.vexcode.cloud/v5/                                                        */
/*https://content.vexrobotics.com/docs/21-22/tipping-point/2021-VRC-GameManual-2.3.pdf */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/*-------------------------------------------------------------------------------------*/

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

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  }
// Battery Percent LED Code
  int BatteryPercent(){
    while(true){
      int currentPercent = Brain.Battery.capacity();
        if (currentPercent > 51 ) {
        RedLED.set(true);
        YellowLED.set(true);
        RedLED.set(true);
        }
        else if(currentPercent > 25) {
        RedLED.set(false);
        YellowLED.set(true);
        RedLED.set(true);
        }
        else if(currentPercent > 10){
        RedLED.set(false);
        YellowLED.set(false);
        RedLED.set(true);
        }
        vex::task::sleep(20);
    }
    return 1;
  }




void autonomous(void) {
  vex::task Battery(BatteryPercent);
  }
// Start of usercontrol code
  // Start of CustumController code
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

void usercontrol(void) {
  // User control code here, inside the loop
  while (true) {
    Controller1.ButtonX.pressed(PneumaticSwitch);
    Controller1.ButtonA.pressed(PneumaticSwitchBack);
    vex::task Battery(BatteryPercent);
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
