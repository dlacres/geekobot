//
// As a home owner, I want to turn a light on and off with my joystick so I can see where I am going when it is dark.
//
#include "JoystickDriver.c"
#include "i_fallEdge.c"

bool btn_z1=false;   // Used with FallEdge

// My states
#define LIGHT_ON 1
#define LIGHT_OFF 2
int sm_cmd = LIGHT_OFF; //The default state

task main(){
	while(true){

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
    wait1Msec(50);
	}// While Loop
}// Foreground Task
