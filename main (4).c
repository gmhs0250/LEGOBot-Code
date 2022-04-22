#include <kipr/wombat.h>

// when placing the robot in the starting box, make sure the edge of the wheel
// (from the top view) is touching the edge of the black tape, and the rocking edge
// of the ring stand faces the robot

// lego functions >:)

// DECLARATION OF VARIABLES
int rmPort = 0; // MOTOR PORTS 
int lmPort = 3;
int rmSpeed = 900; // MOTOR SPEEDS
int lmSpeed = 900;
int lightPort = 5; // SERVO PORTS
int leverPort = 3;
int liftPort = 0;
int liftUp = 1700; // LIFT POSITIONS
int liftDown = 700;
int lBump = 9; // DIGITAL PORTS
int rBump = 0;
int ticksNinety = 1100;



   // note(s) make sure to ALWAYS check the 
   // ports & move as needed

float cm = 81; // converts ticks to cm

// DECLARATION OF FUNCTIONS
void Forward(int ticks);
void ForwardFast(int ticks);
void Backward(int ticks);
void BackwardFast(int ticks);
void LTurn(int ticks);
void RTurn(int ticks);
void Servo(int port, int position);
void RPivot(int ticks);
void Pause();

// MAIN CODE
int main()
{
 //   wait_for_light(lightPort);      							//triggers the rest of the code
    
    shut_down_in(115);            								//shuts down code (in seconds)
    msleep(3000);
    
    enable_servos();        							        //enables any servos used
    
    printf("Check your codes!\n");
        
    shut_down_in(115);      						            //shuts down code (in seconds)
    
    // START GAME HERE ---------------------------------------------------------------------------------
    
    Servo(liftPort, liftUp);
    msleep(100);
    Servo(leverPort, 600);   								    // 0-15 secs
    msleep(1000); 												// wait time for backwards momentum
                   									            // starts at 1430, then moves to 300
    Backward(22 * cm);											
    
    LTurn(ticksNinety);											// turn sequence to line up with stand
    Forward(10 * cm);											// this should allow the bar piece
    RTurn(ticksNinety);											// sticking out to line up with the 
    Forward(22 * cm);								     		// edge of the ring closest to the 
    RTurn(ticksNinety);											// ringstand 
    Forward(28 * cm);
    
    
    LTurn(ticksNinety / 2);       							    // take out ring stand
    RTurn(ticksNinety);										    // wiggles the rings off
    LTurn(ticksNinety / 2);
    
    Backward(15 * cm);											// backs up to the left side of the board
    LTurn(ticksNinety);       									// faces the right side of the board
    
    
    while(digital(lBump) == 0 || digital(rBump) == 0)           // 15-30 secs
    {															// loop for straightening path
        mav(rmPort, -rmSpeed);									// faces the right of the board
        mav(lmPort, -lmSpeed);
    }
    
    ForwardFast(105 * cm);           								// forward to the seam of board
    LTurn(ticksNinety);											// turns left & faces PCR machine
        
    while(digital(lBump) == 0 || digital(rBump) == 0)			// loop for straightening path
    {															// faces the PCR machine (still)
        mav(rmPort, -rmSpeed);
        mav(lmPort, -lmSpeed);
    }
    
    ForwardFast(85 * cm);								  		    // moves up to PCR machine
    ao();  
    
    msleep(1000);
    
    RTurn(2 * ticksNinety); 									// Knock botguy
    
    Backward(35 * cm);											// backs up with botguy
    RTurn(ticksNinety);											// turns to face the right side of the board
    Forward(100 * cm);											// goes up to the ridge edge of the board
    LTurn(ticksNinety);											// turns to face the dividing edge of the board
    
    while(digital(lBump) == 0 || digital(rBump) == 0)			// loop for straightening path
    {															// faces the dividing edge of the board
        mav(rmPort, -rmSpeed);
        mav(lmPort, -lmSpeed);
    }
    Forward(35 * cm);											// moves to where bot guy will be placed
    
    
    ao();
    disable_servos();
    
    return 0;
}
    // END GAME HERE ----------------------------------------------------------------------------------
    // note(s) 

// FORWARD FUNCTION -----------------------------------------------------------------------------------
void Forward(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort,rmSpeed);
        mav(lmPort,lmSpeed);
    }
}
void ForwardFast(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort,1.5 * rmSpeed);
        mav(lmPort,1.5 * lmSpeed);
    }
    
}
// BACKWARD FUNCTION ----------------------------------------------------------------------------------
void Backward(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort, 1.5 * -rmSpeed);
        mav(lmPort, 1.5 * -lmSpeed);
    }
    
}
    
void BackwardFast(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort,1.5 * -rmSpeed);
        mav(lmPort,1.5 * -lmSpeed);
    }
    
}
// LEFT TURN FUNCTION ---------------------------------------------------------------------------------
void LTurn(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort, rmSpeed);
        mav(lmPort, -lmSpeed);
    }
}
// RIGHT TURN FUNCTION --------------------------------------------------------------------------------
void RTurn(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort, -rmSpeed);
        mav(lmPort, lmSpeed);
    }
}
// RIGHT PIVOT (FIRST 15 SECS) ------------------------------------------------------------------------
void RPivot(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort, -rmSpeed);
        mav(lmPort, 0);
    }
}

// SERVO FUNCTION -------------------------------------------------------------------------------------
void Servo(int port, int position)
{
    set_servo_position(port, position);
}

// PAUSE FUNCTION -------------------------------------------------------------------------------------
void Pause()
{
    while(digital(0) == 0)
    {
        mav(rmPort,0);
        mav(lmPort,0);
    }
 
}

// note(s): make sure to narrate the code as you go along to avoid
// confusion and getting functuons mixed up. 