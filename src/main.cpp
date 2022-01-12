/*--------------------------------------------------------------------------------------*/
/*	   							Great Refrences                                                     */
/* https://api.vexcode.cloud/v5/                                                        */
/* https://content.vexrobotics.com/docs/21-22/tipping-point/2021-VRC-GameManual-2.3.pdf */
/* https://content.vexrobotics.com/docs/21-22/tipping-point/2021-VRC-AppendixA-2.2.pdf  */
/* https://kb.vex.com/hc/en-us/sections/360007402172-Programming                        */
/*                                                                                      */
/*--------------------------------------------------------------------------------------*/

#include "vex.h"
#include <string>
using namespace vex;

// Global variables
int pneumaticStatus = 0;
int pneumaticStatusBack = 0;
int powerStatus = 0;
int actPowerStatus = 0;
int driveDirection = 0;
bool FinishTF = true;
int instance = 0;
int ActiveTimerSetup = 0;
int ActiveTimerSetup1 = 0;
int ActiveTimerSetup2 = 0;
int ActiveTime = 0;

// A global instance of competition
competition Competition;

void pre_auton(void)
{
  	// Initializing Robot Configuration. DO NOT REMOVE!
  	vexcodeInit();
	instance = 1;
}

// Battery Percent LED Code
int BatteryPercent()
{
	while(true)
  	{
    	int currentPercent = Brain.Battery.capacity();

    	if(currentPercent > 51)
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

int AutonFinish()
{
	while(FinishTF)
	{
		Drivetrain.driveFor(reverse, 36, inches);
		Drivetrain.turnFor(left, 90, degrees);
		Drivetrain.driveFor(forward, 14, inches);
		Drivetrain.turnFor(left, 90, degrees);
		Drivetrain.driveFor(forward, 10, inches);
		Drivetrain.turnFor(left, 90, degrees);
		vex::task::sleep(25);
	}
  	return 1;
}

void autonomous(void)
{
	vex::task Battery(BatteryPercent);
	Drivetrain.driveFor(forward, 36, inches);
	Drivetrain.turnFor(right, 90, degrees);
	Drivetrain.driveFor(forward, 14, inches);
	Drivetrain.turnFor(right, 90, degrees);
	Drivetrain.driveFor(forward, 8, inches);
	Pneumatic.set(true);
	vex::task AutonFinishTF(AutonFinish);
	instance = 2;
}

int Timer()
{
	while(true)
	{
		ActiveTimerSetup = (vex::timer::system());
		ActiveTimerSetup1 = (ceil(ActiveTimerSetup / 60));  //secends
		rActiveTimerSetup2 = (ceil(ActiveTimerSetup1 / 60)); //Minuts
	}
  	return 1;
}

int LineTwoConfig()
{
  // MAX (X,Y) = (479,239)
	while(!(instance = 3))
	{
    	Controller1.Screen.clearLine(1);
    	Controller1.Screen.setCursor(2, 1);

    	if((instance = 1))
    	{
    		Controller1.Screen.print("Pre_auton");
    	}
		else if((instance = 2))
		{
			Controller1.Screen.print("Autonomous");
		}
		else if((instance = 3))
		{
			Controller1.Screen.print("User Control ");
		}

    	vex::task Time(Timer);
    	wait(10, msec);

		Controller1.Screen.print(ActiveTimerSetup2);
		Controller1.Screen.print(":");
		Controller1.Screen.print(ActiveTimerSetup1);

		vex::task::sleep(45);
	}
  	return 1;
}

int CustomController()
{
	// MAX (X,Y) = (479,239)
	while(true)
  	{
		Brain.Battery.capacity();
		Controller1.Screen.clearLine(1);
		Controller1.Screen.setCursor(1, 1);
		Controller1.Screen.print("Vex Tipping Point");
		Controller1.Screen.setCursor(1, 15);
		Controller1.Screen.print(Brain.Battery.capacity());
		Controller1.Screen.print("%");
		Controller1.Screen.clearLine(2);
		Controller1.Screen.setCursor(2, 1);
		vex::task LineTwoStart(LineTwoConfig);
		Controller1.Screen.clearLine(3);
		Controller1.Screen.setCursor(3, 1);
		Controller1.Screen.print("ControllerMessage");
		vex::task::sleep(9);
  	}
  	return 1;
}

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

void usercontrol(void)
{
	// User control code here, inside the loop
  	while (true)
  	{
    	Controller1.ButtonX.pressed(PneumaticSwitch);
    	Controller1.ButtonA.pressed(PneumaticSwitchBack);
    	vex::task Battery(BatteryPercent);
    	instance = 3;
    	wait(20, msec); // Sleep the task for a short amount of time to
        // prevent wasted resources.
  	}
}

int main()
{
	// Set up callbacks for autonomous and driver control periods.
	Competition.autonomous(autonomous);
	Competition.drivercontrol(usercontrol);
  	// Run the pre-autonomous function.
  	pre_auton();

  	// Prevent main from exiting with an infinite loop.
  	while (true)
  	{
    	wait(100, msec);
  	}
}