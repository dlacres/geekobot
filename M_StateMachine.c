//
// As a home owner, I want to turn a light on and off with my joystick so I can see where I am going when it is dark.
//
#pragma DebuggerWindows ("debugStream")// Bring up the debug stream window
#include "JoystickDriver.c"
#include "i_fallEdge.c"

int count=0;
int timeLeft=0; // A global variable that sticks around each frame
bool btn_z1=false;   // Used with FallEdge

// My states
#define LIGHT_ON 1
#define LIGHT_OFF 2
int sm_cmd = LIGHT_OFF; //The default state

// ------------------------Foreground Task -----------------------------//
// Run every second
#define FOREGROUND_MS 1000 //I change this to 50 when I control the robot. 1000 is good for testing.
task main(){
	while(true){
		ClearTimer(T1);
		hogCPU(); //Prevent other tasks from running when this one is.

  	getJoystickSettings(joystick);     // update buttons and joysticks
  	eraseDisplay();

//-------------------------- Start of the State Machine ----------------//
		switch (sm_cmd) {
		case LIGHT_OFF:                     //State
      // Do this when the light is off
		  nxtDisplayString(2, "Light Off");
			if (FallEdge(joy1Btn(1),btn_z1)){ //Transition
				// Do this on a transition
				sm_cmd=LIGHT_ON;
			}

			break;
		case LIGHT_ON:                      //State
		  nxtDisplayString(2, "Light On");
			if (FallEdge(joy1Btn(1),btn_z1)){ //Transition
				// Do this on a transition
				sm_cmd=LIGHT_OFF;
			}
	  }
// ------------------------- End of the State Machine ------------------//

	  count=count+1; // Count the number of times the foreground runs.
	  timeLeft=FOREGROUND_MS-time1[T1]; // Calculate the time used in the foreground
	  releaseCPU(); // Let other tasks run now.
	  wait1Msec(timeLeft);// The time other tasks have to run before foreground takes control.
	 	writeDebugStreamLine("Count=[%2i] State[%2i]",count,sm_cmd);

	}// While Loop
}// Foreground Task
