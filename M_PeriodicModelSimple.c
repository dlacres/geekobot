// Periodic Model used to read sensors and control the motors on a NXT brick
//
// As a software programmer, I want my tasks to run at a periodic rate. A periodic rate makes control, filtering,
//    and counting much easier.
//
#pragma DebuggerWindows ("debugStream")// Bring up the debug stream window

int count=0;
int timeLeft=0; // A global variable that sticks around each frame

// ------------------------Foreground Task -----------------------------//
// Run every second
#define FOREGROUND_MS 1000 //I change this to 50 when I control the robot. 1000 is good for testing.
task main(){
	while(true){
		ClearTimer(T1);
		hogCPU(); //Prevent other tasks from running when this one is.

		for(long i=0; i<30000; ++i){} //Add some code to see the time used in the foreground. This takes about 0.5 seconds

		writeDebugStreamLine("Foreground\n"); //Let me know when the foreground runs

	  count=count+1; // Count the number of times the foreground runs.

	  timeLeft=FOREGROUND_MS-time1[T1]; // Calculate the time used in the foreground
	  releaseCPU(); // Let other tasks run now.
	  wait1Msec(timeLeft);// The time other tasks have to run before foreground takes control.
	 	writeDebugStreamLine("Count=[%2i] Time Left = %i\n",count,timeLeft);

	  }// While Loop
}// Foreground Task
