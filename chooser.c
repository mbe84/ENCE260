/** @file   chooser.c
    @author D. Carlyle, M. Belworthy Lewthwaite, UCECE
    @date   17 Octbober 2017
    @brief  the chooser module holds all decision making and LED display prompts
*/

#include "system.h"
#include "ir_uart.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "timer.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

char choices[3] = {'P', 'S', 'R'};

void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


char selection (void)
{
    int i = 0;
    char character = choices[i];

    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    ir_uart_init ();
    pacer_init (PACER_RATE);
    navswitch_init ();

    while(1)
    {
        pacer_wait ();
        tinygl_update ();
        display_character (character);
        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_NORTH))
        {
            i = (i+1) % 3;
            character = choices[i];
        }
        if (navswitch_push_event_p (NAVSWITCH_SOUTH))
        {
            i = (i+1) % 3;
            character = choices[i];
        }
        if(navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ir_uart_putc(character);
            tinygl_clear();
            break;

        }
    }
    char winning;
    while(1)
    {
        pacer_wait ();
        tinygl_update ();
        display_character (winning);
        navswitch_init ();

        if (ir_uart_read_ready_p ())
        {
            char opponent = ir_uart_getc ();

            if(character == 'P') {
                if(opponent == 'S') {
                    winning = 'A'; // L
                } else {
                    winning = 'B'; // W
                }
            } else if(character == 'S') {
                if(opponent == 'R') {
                    winning = 'C'; //L
                }  else {
                    winning = 'X'; //W
                }
            } else if(character =='R') {
                if(opponent == 'P') {
                    winning = 'E'; //L
                } else {
                    winning = 'F'; //W
                }

            }

       // }
    }
    return character;
}
