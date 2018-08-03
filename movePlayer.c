#include "system.h"
#include "pio.h"

void player1 (void)
{
    system_init ();

    /* TODO: Initialise the pins of the LED matrix.  */
    pio_config_set(PB1_PIO , PIO_OUTPUT_HIGH);
    pio_config_set(PB2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(PB3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(PB4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(PB5_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(PB6_PIO, PIO_OUTPUT_HIGH);

    pio_config_set(PC4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(PC7_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(PC5_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(PB0_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(PC6_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(PB7_PIO, PIO_OUTPUT_HIGH);

    /* Set up pacer with a frequency of 50 Hz.  */
    pacer_init (200);

    while (1)
    {
        /* Pace the loop.  */
        pacer_wait ();

        /* TODO: Drive the LED matrix using the pio functions,
           displaying only three corner LEDs.  */
        pacer_wait ();

        /* TODO: Drive the LED matrix using the pio functions,
           displaying only three corner LEDs.  */
        tinygl_draw_point(1,1,1);

    }
}
