using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern drivetrain Drivetrain;
extern digital_out Pneumatic;
extern digital_out PneumaticBack;
extern digital_out RedLED;
extern digital_out YellowLED;
extern digital_out GreenLED;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );