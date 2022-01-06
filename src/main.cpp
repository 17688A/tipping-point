/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Diego Casillas,Carter Blair,Michelle Chen                 */
/*    Created:      Wed Jan 05 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
/*Refrences for Carter                                                                 */
/*https://api.vexcode.cloud/v5/                                                        */
/*https://content.vexrobotics.com/docs/21-22/tipping-point/2021-VRC-GameManual-2.3.pdf */
/*https://content.vexrobotics.com/docs/21-22/tipping-point/2021-VRC-AppendixA-2.2.pdf  */ 
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
// Global variables
  int pneumaticStatus = 0;
  int pneumaticStatusBack = 0;
  int powerStatus = 0;
  int actPowerStatus = 0;
  int driveDirection = 0;
  bool FinnishTF = true;
  int AutonFinnishTF1 = false; 

// A global instance of competition
  competition Competition;
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  }
// Battery Percent LED Code
  int BatteryPercent(){
    while(true){
      int currentPercent = Brain.Battery.capacity();
        if (currentPercent > 51) 
        {
          RedLED.set(true);
          YellowLED.set(true);
          RedLED.set(true);
        }
        else if(currentPercent > 25) 
        {
          RedLED.set(false);
          YellowLED.set(true);
          RedLED.set(true);
        }
        else if(currentPercent > 10)
        {
          RedLED.set(false);
          YellowLED.set(false);
          RedLED.set(true);
        }
        vex::task::sleep(20);
    }
    return 1;
  }
// Autonomous Finnish
  int AutonFinnish(){
    while (FinnishTF){
      Drivetrain.driveFor(reverse,36, inches);
      Drivetrain.turnFor(left, 90, degrees);  
      Drivetrain.driveFor(forward, 14, inches); 
      Drivetrain.turnFor(left, 90, degrees); 
      Drivetrain.driveFor(forward, 10, inches); 
      Drivetrain.turnFor(left , 90, degrees); 
      vex::task::sleep(25);
    }
    return 1;
  }



void autonomous(void) {
  vex::task Battery(BatteryPercent);
  Drivetrain.driveFor(forward, 36, inches); 
  Drivetrain.turnFor(right, 90, degrees); 
  Drivetrain.driveFor(forward, 14, inches); 
  Drivetrain.turnFor(right, 90, degrees); 
  Drivetrain.driveFor(forward, 8, inches); 
  Pneumatic.set(true); 
  vex::task AutonFinnishTF(AutonFinnish);
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
