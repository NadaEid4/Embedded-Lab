#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

int main(void)
{



    /*
    1-SYSCTL_SYSDIV_4: This sets the system divider, which divides the system clock by 4. You can adjust this value to get the desired clock frequency.
    2-SYSCTL_USE_OSC: This specifies that you want to use an oscillator as the clock source.
    3-SYSCTL_OSC_MAIN: This selects the main oscillator (crystal) as the clock source.
    4-SYSCTL_XTAL_16MHZ: This specifies that the crystal has a 16MHz frequency.


    The formula to calculate the system clock frequency is: (Input Frequency) / (2 * SYSDIV)

    */
    // Set the system clock to run at 50MHz
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Enable the GPIO port that is used for the onboard LED.
    //must be port F cause led build in board to change port use a external led
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Check if the peripheral access is enabled.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }
      // i can initialize the pin with 0 =turn off (optional)
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
    // Configure PF3 (green LED) as an output.
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

    while(1)
    {
        // Turn on the green LED (PF3)
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);

        // Delay for 0.5 seconds (assuming 50MHz clock).
        /*
         If your system clock is 50MHz, there are 50 million clock cycles per second (50,000,000 Hz).
       To delay for 0.5 seconds, you need half of that, which is 25 million clock cycles (50,000,000 / 2).
        */
        SysCtlDelay(50000000 / 2);

        // Turn off the green LED
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);

        // Delay for 0.5 seconds
        SysCtlDelay(50000000 / 2);
    }
}
