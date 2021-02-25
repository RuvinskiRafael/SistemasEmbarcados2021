//Rafael Ruvinski Sist.Embarcados s11
// Prática 1:

#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

uint8_t LED_D4 = 0;

void main(void){

    SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_320, 24000000); // 24MHz
//  SysCtlClockFreqSet(SYSCTL_OSC_INT | SYSCTL_USE_PLL | SYSB9DCTL_CFG_VCO_320, 120000000); // 120MHz

// Com o delay em 24Mhz  não necessários 8M ciclos para conseguismos um segundo.
  
//// 1/24MHz = 41.7ns (4.17*10^-8) x(3 instruções/loop) = 125ns   1/125nS = 8M CICLOS.
  
////// com 120MHz:
//////  1/120M = 8.33ns X 3 ciclos/loop: 25.0ns >> 1/25n = 4*10^7 ciclos (menos ciclos para 1 segundo)
  
//////// Nesse caso não percebi alteração na otimização.
    
    
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D3 = PF4, LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilitaçã   
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); // LED D4 como saída
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); // LED D4 apagado
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
  SysTickIntEnable();
  SysTickEnable();

  while(1){
    
      SysCtlDelay(8000000);

  LED_D4 ^= GPIO_PIN_0; // Inversora de estado do LED D4
  
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, LED_D4); // Acende ou apaga LED D4

  } // while
} // main
