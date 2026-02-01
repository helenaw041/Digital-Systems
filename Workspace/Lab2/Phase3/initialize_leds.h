#ifndef initialize_leds_include
#define initialize_leds_include

#define POWER_STARTUP_DELAY (16)

#define ALL_PINS (LED12A_bit | LED12B_bit | LED1A_bit | LED1B_bit |\
                    LED2A_bit  | LED2B_bit  | LED3A_bit | LED3B_bit |\
                    LED4A_bit  | LED4B_bit  | LED5A_bit | LED5B_bit |\
                    LED6A_bit  | LED6B_bit  | LED7A_bit | LED7B_bit |\
                    LED8A_bit  | LED8B_bit  | LED9A_bit | LED9B_bit |\
                    LED10A_bit | LED10B_bit | LED11A_bit | LED11B_bit)

#define LED12A_bit   (1U << 0)   // PA0: left shift bits = pin numbers
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

void Initialize_GPIO();
void Initialize_Timer();
void TIMG0_IRQHandler(void);

#define UPLCK_DELAY (32000/320)

#endif /* initialize_leds_include */
