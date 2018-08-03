/** @file   game.c
    @author D. Carlyle, M. Belworthy Lewthwaite, UCECE
    @date   17 Octbober 2017
    @brief  the games main file
*/
#include "system.h"
#include "tinygl.h"
#include "chooser.h"
#include "led.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"
#include "usart1.h"

#define LOOP_RATE 500
#define PACER_RATE 500
#define MESSAGE_RATE 10

int main (void)
{

    system_init ();
    tinygl_init (PACER_RATE);
    char character;
    while (1)
    {
        pacer_wait ();
        //tinygl_update ();
        character = selection ();
        led_set (LED1, 1);
    }
    return 1;
}

