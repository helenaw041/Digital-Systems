#include "initialize_leds.h"
#include <ti/devices/msp/msp.h>
#include "delay.h"

static const uint32_t pins[] = {
    IOMUX_PINCM1, // PA0 12A
    IOMUX_PINCM60, // PA27 12B
    IOMUX_PINCM59, // PA26 1A
    IOMUX_PINCM55, // PA25 1B
    IOMUX_PINCM54, // PA24 2A
    IOMUX_PINCM53, // PA23 2B
    IOMUX_PINCM47, // PA22 3A
    IOMUX_PINCM46, // PA21 3B
    IOMUX_PINCM40, // PA18 4A
    IOMUX_PINCM39, // PA17 4B
    IOMUX_PINCM38, // PA16 5A
    IOMUX_PINCM37, // PA15 5B
    IOMUX_PINCM36, // PA14 6A
    IOMUX_PINCM35, // PA13 6B
    IOMUX_PINCM34, // PA12 7A
    IOMUX_PINCM22, // PA11 7B
    IOMUX_PINCM21, // PA10 8A
    IOMUX_PINCM20, // PA9 8B
    IOMUX_PINCM19, // PA8 9A
    IOMUX_PINCM14, // PA7 9B
    IOMUX_PINCM11, // PA6 10A
    IOMUX_PINCM10, // PA5 10B
    IOMUX_PINCM3, // PA28 11A
    IOMUX_PINCM2, // PA1 11B
};

void Initialize_GPIO() {
    // 1. Reset GPIO port (the one(s) for pins that you will use)
    GPIOA->GPRCM.RSTCTL |= (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR | GPIO_RSTCTL_RESETASSERT_ASSERT);

    // 2. Enable power on LED GPIO port
    GPIOA->GPRCM.PWREN |= (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_ENABLE);

    delay_cycles(POWER_STARTUP_DELAY); // delay to enable GPIO to turn on and reset

    // IOMUX_PINCMx found in datasheet Table 6-2; iomux enables pin and sets function
    for (int i = 0; i < 24; i++){
        IOMUX->SECCFG.PINCM[pins[i]] |= (IOMUX_PINCM_PC_CONNECTED | ((uint32_t) 0x00000001));    
    }
    
    GPIOA->DOUTSET31_0 |= ALL_PINS; // Initialize LEDs OFF (active LOW)
    GPIOA->DOESET31_0 |= ALL_PINS; // Enable output drivers
}

void Initialize_Timer() {
    /* Timer module Initialization */
    // 1. Step 1 is always to reset and enable
    TIMG0->GPRCM.RSTCTL = (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR | GPIO_RSTCTL_RESETASSERT_ASSERT);
    TIMG0->GPRCM.PWREN = (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_ENABLE);
    delay_cycles(16); // delay to enable module to turn on and reset

    // 2. Step 2 is to choose the desired clock. We want UPCLK (LFCLK) so we can use a LPM
    TIMG0->CLKSEL = GPTIMER_CLKSEL_LFCLK_SEL_ENABLE;

    // 3. By default, the timer counts down to zero and then stops. Configure it to repeat.
    TIMG0->COUNTERREGS.CTRCTL = GPTIMER_CTRCTL_REPEAT_REPEAT_1;

    // 4. Enable timer interrupt when we reach 0
    TIMG0->CPU_INT.IMASK |= GPTIMER_CPU_INT_IMASK_Z_SET;

    // 5. Enable the clock input to the timer. (The timer itself is still not enabled!)
    TIMG0->COMMONREGS.CCLKCTL = GPTIMER_CCLKCTL_CLKEN_ENABLED;
    /* --------------------------------------------------------------------- */

    TIMG0->COUNTERREGS.LOAD = UPLCK_DELAY; // This will load as soon as timer is enabled
    TIMG0->COUNTERREGS.CTRCTL |= (GPTIMER_CTRCTL_EN_ENABLED);

    // Set sleep to be STANDBY (Rev 2025 TRM p. 227, also 2.4.2 Operating Mode Selection)
    SYSCTL->SOCLOCK.PMODECFG = SYSCTL_PMODECFG_DSLEEP_STANDBY;
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    // Set sleep to be STANDBY1 (Rev 2025 TRM Table 2-9. MSPM0Gxx ULPCLK by Operating Mode)
    SYSCTL->SOCLOCK.MCLKCFG |= SYSCTL_MCLKCFG_STOPCLKSTBY_ENABLE;

    NVIC_EnableIRQ(TIMG0_INT_IRQn); // Enable the timer interrupt
}

void TIMG0_IRQHandler(void)
{
    // This wakes up the processor!
    switch (TIMG0->CPU_INT.IIDX) {
        case GPTIMER_CPU_INT_IIDX_STAT_Z: // Counted down to zero event.
            // If we wanted to execute code in the ISR, it would go here.
            break;
        default:
            break;
    }
}
