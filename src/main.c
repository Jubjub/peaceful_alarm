#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
    const int msecsDelayPost = 300;
    DDRB = 1<<DDB4;
    PORTB = 0;  
    while (1) {
        PORTB ^= 1<<PB4;
        _delay_ms (msecsDelayPost);
    }
    return 0;
}

