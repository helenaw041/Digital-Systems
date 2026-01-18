#include "state_machine_logic.h"
#include "initialize_leds.h"
#include <ti/devices/msp/msp.h>

static const int LEDA_bits[] = {
    LED12A_bit, LED1A_bit,  LED2A_bit,  LED3A_bit,
    LED4A_bit,  LED5A_bit,  LED6A_bit,  LED7A_bit,
    LED8A_bit,  LED9A_bit,  LED10A_bit, LED11A_bit
};

static const int LEDB_bits[] = {
    LED12B_bit, LED1B_bit,  LED2B_bit,  LED3B_bit,
    LED4B_bit,  LED5B_bit,  LED6B_bit,  LED7B_bit,
    LED8B_bit,  LED9B_bit,  LED10B_bit, LED11B_bit
};

void InitializeStates() {
    for (int i=0; i<12; i++) {
        LEDA_states[i].next_state = (i+1) % 12;
        LEDA_states[i].output = LEDA_bits[i];
    }
    
    for (int i=0; i<12; i++) {
        LEDB_states[i].next_state = (i+1) % 12;
        LEDB_states[i].output = LEDB_bits[i];
    }
}

// // int GetNextState(int current_state)
// // {
    
// //     if (current_state == OFF) {
// //         return ON1; // If the LED is off -> on
// //     }
// //     else {
// //         if (current_state == ON1)
// //             return ON2;
// //         else
// //             return OFF; // If the LED is on -> off
// //     }
// // }

// int GetStateOutputGPIOA(int current_state, int index, int aorb) {
//     if (!aorb) {
//         return LEDA_bits[index];
//     } else {
//         return LEDB_bits[index];
//     }
//     // if ((current_state == ON1) || (current_state == ON2)) {
//     //     return 0x00000000;
//     // }
//     // else {
//     //     return 0x00000001;
//     // }
// }

// int GetStateOutputGPIOB(int current_state, int index, int aorb) {
//     return 0;
// };
