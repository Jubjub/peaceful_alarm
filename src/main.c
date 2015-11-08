#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>

#define PRESCALE0_1 _BV(CS00)
#define PRESCALE0_8 _BV(CS01)
#define PRESCALE0_64 (_BV(CS00) | _BV(CS01))
#define PRESCALE0_256 _BV(CS02)
#define PRESCALE0_1024 (_BV(CS02) | _BV(CS00))

void interrupt_setup() {
    /* enable timer interrupts */
    TIMSK0 |= 1 << TOIE0;
    /* enable interrupts */
    sei();
    /* prescale timer interrupt */
    TCCR0B |= PRESCALE0_1;
}

void io_setup() {
    /* set port 0 to output */
    DDRB = 1 << DDB0;
    PORTB = 0;  
}

unsigned int overrun = 2;
unsigned int acc = 0;

ISR(TIM0_OVF_vect) {
    if (++acc > (overrun / 10)) {
        acc = 0;
        PORTB ^= 1 << PB0;
    }
    overrun += 1;
    if (overrun > 8000) {
        //overrun = 0;
    }
}

int main(void) {
    io_setup();
    interrupt_setup();
    const int msecsDelayPost = 300;
    while (1) {
        _delay_ms (msecsDelayPost);
        overrun++;
    }
    return 0;
}
