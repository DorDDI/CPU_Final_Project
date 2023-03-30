#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer
#include  <stdio.h>
#include  <math.h>




//---------------------------------------------------------------------
//            stepper spinning counter
//            spin the stepper motor stepNum steps with or against clock direction
//---------------------------------------------------------------------

void stepperSpin(int stepNum, int spinDirection){   //spinDirection = 1 for against clock direction
    if(spinDirection == 1){                         //spinDirection = -1 for clock direction
        for (i = 0; i<stepNum;i++){
                PBOUT &= ~0x0F;
                PBOUT |= 1;
                TimerWait(150);
                PBOUT&= ~0x0F;
                PBOUT |= 8;
                TimerWait(150);
                PBOUT &= ~0x0F;
                PBOUT |= 4;
                TimerWait(150);
                PBOUT &= ~0x0F;
                PBOUT |= 2;
                TimerWait(150);
            }
    }
    else{
        for (i = 0; i<stepNum;i++){
                PBOUT &= ~0x0F;
                PBOUT |= 8;
                TimerWait(150);
                PBOUT&= ~0x0F;
                PBOUT |= 1;
                TimerWait(150);
                PBOUT &= ~0x0F;
                PBOUT |= 2;
                TimerWait(150);
                PBOUT &= ~0x0F;
                PBOUT |= 4;
                TimerWait(150);
            }
    }
    TACCTL0 &=~ CCIE ;
}

