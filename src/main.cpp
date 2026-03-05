
#include <Arduino.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "setup/helpers.h"
#include "setup/I2C.h" 
#include "setup/ssd1306.h" 
#include "setup/macros.h"
#include "setup/spi.h"
#include "setup/temp.h"
#include <string.h>

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

     
    print_centered("Temperatur:", 2);

    char temp_read[16];
        
    temp_convert(temp_read);
    print_centered(temp_read, 4);
    _delay_ms(500);
 }
}



 ISR(INT4_vect) {
    sw_flag = 1;
 }
