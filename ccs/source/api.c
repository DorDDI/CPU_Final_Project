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


//---------------------------------------------------------------------
//            run script
//            run the selected script saved in the flash
//---------------------------------------------------------------------

void runScript(int scriptnumber){
    char chartask = "";
    int checkscript = scriptnumber;
    int endtask = 0;
    int first_argument;
    int second_argument;

    char* ptr = (char *) (0x1080 - (scriptnumber-1)*0x40);

    while ((endtask==0)&&(state = state4)&&(checkscript == scriptnumber))
    {
        *ptr++;
        chartask = *ptr;
        *ptr++;
        char temp1;
        char temp2;

        switch(chartask){

        case '1':
            temp1 = *ptr;
            *ptr++;
            temp2 = *ptr;
            *ptr++;
            first_argument = hex_to_int(temp1, temp2);
            blink_rgb(first_argument);
            break;

        case '2':
            temp1 = *ptr;
            *ptr++;
            temp2 = *ptr;
            *ptr++;
            first_argument = hex_to_int(temp1, temp2);
            rlc_leds(first_argument);

            break;

        case '3':

            temp1 = *ptr;
            *ptr++;
            temp2 = *ptr;
            *ptr++;
            first_argument = hex_to_int(temp1, temp2);
            rrc_leds(first_argument);

            break;

        case '4':

            temp1 = *ptr;
            *ptr++;
            temp2 = *ptr;
            *ptr++;
            first_argument = hex_to_int(temp1, temp2);
            set_delay(first_argument);

            break;

        case '5':

            clear_all_leds();

            break;

        case '6':
            temp1 = *ptr;
            *ptr++;
            temp2 = *ptr;
            *ptr++;
            first_argument = hex_to_int(temp1, temp2);
            stepper_deg(first_argument);

            break;

        case '7':
            temp1 = *ptr;
            *ptr++;
            temp2 = *ptr;
            *ptr++;
            first_argument = hex_to_int(temp1, temp2);

            temp1 = *ptr;
            *ptr++;
            temp2 = *ptr;
            *ptr++;
            second_argument = hex_to_int(temp1, temp2);

            stepper_scan(first_argument,second_argument);
            break;

        case '8':
            endtask = 1;
            bool = 4;
            IE2 |= UCA0TXIE;
            TimerWait(3250);


            break;
        }
        *ptr++;
    }
}

