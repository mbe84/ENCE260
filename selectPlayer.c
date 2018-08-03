#include "system.h"
#include "ir_uart.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10


void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


int main (void)
{
    char character = '1';

    system_init ();

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    ir_uart_init ();

    /* TODO: Initialise navigation switch driver.  */

    pacer_init (PACER_RATE);
    navswitch_init ();

    while(1)
    {
        pacer_wait ();
        tinygl_update ();
        display_character (character);

        /* TODO: Call the navswitch update function.  */
        navswitch_update ();
        /* TODO: Increment character if NORTH is pressed.  */
        if (navswitch_push_event_p (NAVSWITCH_NORTH))
        {
            character++;
            if (character == '3')
            {
                    character = '1';
            }
        }
        /* TODO: Decrement character if SOUTH is pressed.  */
/*
        if (navswitch_push_event_p (NAVSWITCH_SOUTH))
        {
            if (character != 49) {
                character = 50;
            } else {
                character = 49;
            }
        }
*/
        /* TODO: Transmit the character over IR on a NAVSWITCH_PUSH
           event.  */
        if(navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ir_uart_putc(character);
        }
        if (ir_uart_read_ready_p ())
        {
        character = ir_uart_getc ();
        }
    }

    return character;
}
