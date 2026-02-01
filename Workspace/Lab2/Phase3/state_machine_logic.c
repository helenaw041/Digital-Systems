#include "state_machine_logic.h"
#include <ti/devices/msp/msp.h>
#include "initialize_leds.h"

#define PWM_TICKS_PER_SECOND 80   // ticks per second
#define PWM_TICKS_PER_CYCLE 4     // 25% duty cycle

static const uint32_t hour_leds[12] = {
    LED12A_bit, LED1A_bit, LED2A_bit, LED3A_bit, LED4A_bit, LED5A_bit,
    LED6A_bit,  LED7A_bit, LED8A_bit, LED9A_bit, LED10A_bit, LED11A_bit
};

static const uint32_t minute_leds[12] = {
    LED12B_bit, LED1B_bit, LED2B_bit, LED3B_bit, LED4B_bit, LED5B_bit,
    LED6B_bit,  LED7B_bit, LED8B_bit, LED9B_bit, LED10B_bit, LED11B_bit
};

uint32_t curr_leds;

typedef struct {
    uint16_t hour_idx;       
    uint16_t minute_idx;     
    uint16_t pwm_tick_counter;   // 25% duty cycle
    uint16_t ticks_since_last_minute;  // counts up to PWM_TICKS_PER_SECOND
    bool leds_on;
} clock_state;

clock_state state = {
    .hour_idx = 0,
    .minute_idx = 0,
    .pwm_tick_counter = 0,
    .ticks_since_last_minute = 0,
    .leds_on = true,
};

inline void Refresh_Curr_LEDs() {
    // Updates which LEDs are to be 
    curr_leds = hour_leds[state.hour_idx] | minute_leds[state.minute_idx];
}

void Get_Next_State()
{
    // Increment PWM tick counter
    state.pwm_tick_counter = (state.pwm_tick_counter + 1) % PWM_TICKS_PER_CYCLE;

    // LED ON only on first tick of PWM cycle
    state.leds_on = (state.pwm_tick_counter == 0);

    // Only count logical ticks once per full PWM cycle
    if (state.pwm_tick_counter == 0) {
        state.ticks_since_last_minute++; // every 4 ticks
        
        if (state.ticks_since_last_minute >= PWM_TICKS_PER_SECOND) { // every 320 ticks, state changes
            state.ticks_since_last_minute = 0;

            // Baseline clock state machine: Advance minute/hour only once per second
            state.minute_idx++;
            if (state.minute_idx == 12) {
                state.minute_idx = 0;
                state.hour_idx++;
                if (state.hour_idx == 12) {
                    state.hour_idx = 0;
                }
            }
            Refresh_Curr_LEDs();
        }
    }
}

void led_off(){
    GPIOA->DOUTSET31_0 = ALL_PINS;
}

void led_on(){
    GPIOA->DOUTCLR31_0 = curr_leds;
}

void Update_Output()
{
    if (state.leds_on) {
        led_on();
    } else {
        led_off();
    }

    __WFI();  // wait for next tick
}
