#define F_CPU 2000000UL  // Define CPU clock frequency
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    PORTA.DIR |= PIN6_bm;  // Set pin 5 of PORTA as output

    while (1) {
        PORTA.OUT ^= PIN6_bm;  // Toggle pin 5 of PORTA
        _delay_ms(500);        // Delay 500 ms
    }
    return 0;
}
