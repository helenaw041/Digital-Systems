#ifndef initialize_leds_include
#define initialize_leds_include

#define LED12A_bit   (1U << 0)   // PA0
#define LED11B_bit   (1U << 1)   // PA1

#define LED10B_bit   (1U << 5)   // PA5
#define LED10A_bit   (1U << 6)   // PA6
#define LED9B_bit    (1U << 7)   // PA7
#define LED9A_bit    (1U << 8)   // PA8
#define LED8B_bit    (1U << 9)   // PA9
#define LED8A_bit    (1U << 10)  // PA10
#define LED7B_bit    (1U << 11)  // PA11
#define LED7A_bit    (1U << 12)  // PA12
#define LED6B_bit    (1U << 13)  // PA13
#define LED6A_bit    (1U << 14)  // PA14
#define LED5B_bit    (1U << 15)  // PA15
#define LED5A_bit    (1U << 16)  // PA16
#define LED4B_bit    (1U << 17)  // PA17
#define LED4A_bit    (1U << 18)  // PA18

#define LED3B_bit    (1U << 21)  // PA21
#define LED3A_bit    (1U << 22)  // PA22
#define LED2B_bit    (1U << 23)  // PA23
#define LED2A_bit    (1U << 24)  // PA24
#define LED1B_bit    (1U << 25)  // PA25
#define LED1A_bit    (1U << 26)  // PA26
#define LED12B_bit   (1U << 27)  // PA27
#define LED11A_bit   (1U << 28)  // PA28

void InitializeGPIO();

#endif /* initialize_leds_include */
