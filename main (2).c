#include <kipr/wombat.h>

// when placing the robot in the starting box, make sure the edge of the wheel
// (from the top view) is touching the edge of the black tape, and the rocking edge
// of the ring stand faces the robot

// lego functions >:)

// DECLARATION OF VARIABLES
int rmPort = 0; // MOTOR PORTS 
int lmPort = 3;
int rmSpeed = 700; // MOTOR SPEEDS
int lmSpeed = 700;
int lightPort = 5; // SERVO PORTS
int leverPort = 3;
int lBump = 9; // DIGITAL PORTS
int rBump = 0;
int ticksNinety = 1100;



   // note(s) make sure to ALWAYS check the 
   // ports & move as needed

float cm = 81; // converts ticks to cm

// DECLARATION OF FUNCTIONS
void Forward(int ticks);
void Backward(int ticks);
void LTurn(int ticks);
void RTurn(int ticks);
void Servo(int port, int position);
void RPivot(int ticks);

// MAIN CODE
int main()
{
    //wait_for_light(lightPort);      							//triggers the rest of the code
    
    shut_down_in(115);            								//shuts down code (in seconds)
    
    enable_servos();        							        //enables any servos used
    
    printf("Check your codes!\n");
        
    shut_down_in(115);      						            //shuts down code (in seconds)
    
    // START GAME HERE ---------------------------------------------------------------------------------
    
    Servo(leverPort, 530);   								    // 0-15 secs
    msleep(1000);										        // starts at 1430, then moves to 300
    Backward(35 * cm);
    
    RPivot(450);  
    Forward(30 * cm);
    RTurn(740);
    Forward(28 * cm);
    
    LTurn(ticksNinety / 2);       							    // take out ring stand
    RTurn(ticksNinety / 2);										// 'wiggles' the rings off
    
    Backward(15 * cm);
    RTurn(ticksNinety);       
    
    
    while(digital(lBump) == 0 || digital(rBump) == 0)           // 15-30 secs
    {															// loop for straightening path
        mav(rmPort, -rmSpeed);									// faces the right of the board
        mav(lmPort, -lmSpeed);
    }
    
    Forward(100 * cm);           								// forward to the seam of board
    LTurn(ticksNinety);											// turns left & faces PCR machine
        
    while(digital(lBump) == 0 || digital(rBump) == 0)			// loop for straightening path
    {															// faces the PCR machine (still)
        mav(rmPort, -rmSpeed);
        mav(lmPort, -lmSpeed);
    }
    
    Forward(95 * cm); 											// moves up to PCR machine
        
    ao();
    disable_servos();
    
    return 0;
}
    // END GAME HERE ----------------------------------------------------------------------------------
    // note(s) 

// FORWARD FUNCTION
void Forward(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort,rmSpeed);
        mav(lmPort,lmSpeed);
    }
    
}
// BACKWARD FUNCTION
void Backward(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort,-rmSpeed);
        mav(lmPort,-lmSpeed);
    }
    
}
// LEFT TURN FUNCTION
void LTurn(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort, rmSpeed);
        mav(lmPort, -lmSpeed);
    }
}
// RIGHT TURN FUNCTION
void RTurn(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort, -rmSpeed);
        mav(lmPort, lmSpeed);
    }
}
// RIGHT PIVOT (FIRST 15 SECS)
void RPivot(int ticks)
{
    cmpc(0);
    while(abs(gmpc(rmPort)) < ticks)
    {
        mav(rmPort, -rmSpeed);
        mav(lmPort, 0);
    }
}

// SERVO FUNCTION
void Servo(int port, int position)
{
    set_servo_position(port, position);
}

// note(s): make sure to narrate the code as you go along to avoid
// confusion and getting functuons mixed up. 