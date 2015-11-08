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
    TCCR0B |= PRESCALE0_256;
}

void io_setup() {
    /* set port 0 to output */
    DDRB = 1 << DDB0;
    PORTB = 0;  
}

int note_change = 0;

ISR(TIM0_OVF_vect) {
    PORTB ^= 1 << PB0;
    if (++note_change > 20) {
        TCCR0B = 0;
        TCCR0B |= PRESCALE0_64;
    }
    if (note_change > 50) {
        TCCR0B = 0;
        TCCR0B |= PRESCALE0_256;
        note_change = 0;
    }
}

int main(void) {
    io_setup();
    interrupt_setup();
    const int msecsDelayPost = 300;
    while (1) {
        /*
        PORTB ^= 1 << PB0;
        _delay_ms (msecsDelayPost);
        */
    }
    return 0;
}
