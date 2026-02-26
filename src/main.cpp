
#include <Arduino.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "setup/helpers.h"
#include "setup/I2C.h" 
#include "setup/ssd1306.h" 
#include "setup/macros.h"
#include "setup/spi.h"

volatile uint8_t sw_flag = 0;

void hw_init(){

// init LED as output
    DIRBIT(DDRG, LED_PIN); 

// init BTN 
    CLRBIT(DDRE, BTN_PIN);
    SETBIT(PORTE, BTN_PIN);

  Serial.begin(9600);
}



int main(void) {  


    hw_init();
    I2C_Init();
    InitializeDisplay();
    clear_display();
    interrupt_init();
    spi_master_init();

    while(1) {

     _delay_ms(100);
     print_centered((unsigned char*)"Transmission:", 2);

     unsigned char data = putcSPI_master('a');

     char data_con[2];
     sprintf(data_con, "%c", data);
     sendStrXY(data_con, 4, 4);
   
    }
 }



 ISR(INT4_vect) {
    sw_flag = 1;
 }
