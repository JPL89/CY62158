/**********************************************************************
*	@File       MAIN.C	 		
*	@Author		JOSIMAR PEREIRA LEITE
*	@Country	Brazil
*	@Date		18/10/2025
*
*	Copyright (C) 2024  JOSIMAR PEREIRA LEITE
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
************************************************************************/
#include "main.h"

#define CY62158H_CE1_TRIS TRISAbits.RA0
#define CY62158H_CE2_TRIS TRISAbits.RA1
#define CY62158H_WE_TRIS TRISAbits.RA2
#define CY62158H_OE_TRIS TRISAbits.RA3

#define CY62158H_CE1 PORTAbits.RA0
#define CY62158H_CE2 PORTAbits.RA1
#define CY62158H_WE PORTAbits.RA2
#define CY62158H_OE PORTAbits.RA3

void CY62158H_init(void)
{
    CY62158H_CE1_TRIS = 0;
    CY62158H_CE2_TRIS = 0;
    CY62158H_WE_TRIS = 0;
    CY62158H_OE_TRIS = 0;
    
    // IO PORT //
    TRISC = 0x00;
    
    // ADDR PORT // 
    TRISB = 0x00;
}

void CY62158H_write(unsigned char addr, unsigned char data)
{
    PORTB = addr;
    
    TRISC = 0x00;

//  Write to the device is performed 
//  by taking Chip Enable 1 (CE1)
//  LOW and Chip Enable 2 (CE2) HIGH and 
//  the Write Enable (WE) input LOW.    
    CY62158H_CE1 = 0;
    CY62158H_CE2 = 1;
    
    CY62158H_WE = 0;
    
    PORTC = data;
    
    CY62158H_WE = 1;
    
    CY62158H_CE1 = 1;
    CY62158H_CE2 = 1;
    
    PORTC = 0x00;
}

void CY62158H_read(unsigned char addr)
{
    PORTB = addr;
    
    TRISC = 0xFF;
    
//  Read from the device is performed 
//  by taking Chip Enable 1 (CE1)
//  and Output Enable (OE) LOW    
    CY62158H_CE1 = 0;
    CY62158H_OE = 0;  
    
    
    CY62158H_CE2 = 1;
    CY62158H_WE = 1;
}

void main(void)
{
    Pic18f2520_init();     
    
    CY62158H_init();
    
    // WRITE ADDR 3 DATA 0x0F
    CY62158H_write(3, 0x0F);
    
    // WRITE ADDR 7 DATA 0xF0
    CY62158H_write(7, 0xF0);
    
    // READ ADDR FROM 0 TO 7
    for(unsigned char i = 0; i < 8; i++)
    {
        __delay_ms(500);    
        CY62158H_read( i );
    }
    
    
    while(1)
    {      
        
    }
    
    return;
}
