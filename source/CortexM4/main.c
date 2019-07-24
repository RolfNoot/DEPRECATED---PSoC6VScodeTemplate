#include "cy_pdl.h"
#include "cycfg.h"

int main(void)
{
    /* Set up internal routing, pins, and clock-to-peripheral connections */
    init_cycfg_all();
    
    /* enable interrupts */
    __enable_irq();

    for (;;)
    {
        Cy_GPIO_Inv(LED_RED_PORT, LED_RED_PIN); /* toggle the pin */
        Cy_SysLib_Delay(1000/*msec*/);
    }
}