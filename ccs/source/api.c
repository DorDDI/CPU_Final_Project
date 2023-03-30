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

//---------------------------------------------------------------------
//            hex_to_int
//            calculate the hex number into decimal
//---------------------------------------------------------------------

int hex_to_int(char hex_a, char hex_b){
    int calculated_hex = 0;
    if(hex_a >= 48 && hex_a <=57)
        {
        calculated_hex = ((int)hex_a -48)*16;

            if(hex_b >= 48 && hex_b <=57){
                calculated_hex = calculated_hex+(int)hex_b-48;
            }
            else
            {
                calculated_hex = calculated_hex+ ((int)hex_b -55);
            }

        }
    else
    {
        calculated_hex = ((int)hex_a -55)*16;

        if(hex_b >= 48 && hex_b <=57){
            calculated_hex = calculated_hex+(int)hex_b-48;
        }
        else
        {
            calculated_hex = calculated_hex+ ((int)hex_b -55);
        }
    }
    return calculated_hex;
}




//---------------------------------------------------------------------
//            Print RGB
//            Blink RGB LED in series x times with delay d
//---------------------------------------------------------------------

void blink_rgb(int x){
    RGBcolor = 0x20;
    for (i = 0; i<x; i++)
    {
        LEDsArrPort = RGBcolor;
        RGBcolor=RGBcolor+0x20;
        if (RGBcolor == 0x100)
            {
                RGBcolor=0x20;
            }
          TimerWait(deleyX);
    }
}


//---------------------------------------------------------------------
//            rotate rigth leds
//            Rotate right circularly a single lighted LED in 4-LED array x times with delay d
//---------------------------------------------------------------------

void rrc_leds(int x){
    int tempChar = 0x80;
    PBOUT &=~ 0xF0;
    for (i =0; i <x; i++)
    {
        PBOUT = tempChar;
        tempChar = tempChar / 2;
        if (tempChar == 0x08)
            tempChar = 0x80;
        TimerWait(deleyX);
    }
}

//---------------------------------------------------------------------
//            rotate left leds
//            Rotate left circularly a single lighted LED in 4-LED array x times with delay d
//---------------------------------------------------------------------

void rlc_leds(int x){

    int tempChar = 0x10;
    PBOUT &=~ 0xF0;
    for (i =0; i <x; i++)
    {
        PBOUT = tempChar;
        tempChar = tempChar * 2;
        if (tempChar == 0x100)
            tempChar = 0x10;
        TimerWait(deleyX);
        }
    }


//---------------------------------------------------------------------
//            Stepper Degree
//            run the stepper_deg1 for script task 6
//---------------------------------------------------------------------

