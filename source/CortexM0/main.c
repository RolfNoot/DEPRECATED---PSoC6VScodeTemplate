
#include "cy_device_headers.h"
#include "cy_syslib.h"
#include "cy_syspm.h"

int main(void)
{
    /* enable interrupts, and the CM4 */
    __enable_irq();
    Cy_SysEnableCM4(0x10080000);        // CY_CORTEX_M4_APPL_ADDR as defined by the CM4 linker 0x10080000 

    for (;;)
    {
        Cy_SysPm_DeepSleep( CY_SYSPM_WAIT_FOR_INTERRUPT );
    }
}