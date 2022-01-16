#include "vex.h"
#include <string>
using namespace vex;

// Global variables
int pneumaticStatus = 0;
int pneumaticStatusBack = 0;
int ActiveTimerSetup = 0;
int ActiveTimerSetup1 = 0;
int ActiveTimerSetup2 = 0;
int ActiveTime = 0;
int powerStatus = 0;
int actPowerStatus = 0;
int driveDirection = 0;
bool FinishTF = true;
int instance = 0;

// autonomous.cpp
int AutonFinish();
void autonomous(void);

// pneumatics.cpp
void PneumaticSwitch();
void PneumaticSwitchBack();

// controller.cpp
int Timer();
int LineTwoConfig();
int CustomController();

int matrix();

// teleop.cpp
void usercontrol(void);