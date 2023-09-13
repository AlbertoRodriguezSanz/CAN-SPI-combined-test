 /**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F26K83
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */

const unsigned long canId = 3; 

static void SPI1_Receive_InterruptHandler(void);

static void SPI1_Receive_InterruptHandler(void){  //Lets try making it work with a SPI1RXIF interrupt since IOC isn't working for some reason
   LATCbits.LC2 = 1;
   

}
/*
static void SS_InterruptHandler(void){
    LATCbits.LC2 = 1;
    if(!PORTAbits.RA5){
        LATCbits.LC2 = 1;
        
        uint8_t data_RX = 0x00;
        SPI1_WriteByte(0xFF);
        //data_RX = SPI1_ExchangeByte(0xFF);

        if(data_RX == 0x33){
            LATCbits.LC2 = 1;               //2
            __delay_ms(1000);
            LATCbits.LC2 = 0;
            __delay_ms(1000);
        }    

        //Lo ponemos de nuevo en modo de Operacion Normal el CAN
        //CANCON = 0x00;
        //while (0x00 != (CANSTAT & 0xE0)); // wait until ECAN is in Normal mode 
    }
}

 * */
void main(void)
{
    
    // Initialize the device
    SYSTEM_Initialize();
    SPI1_SetRxInterruptHandler(SPI1_Receive_InterruptHandler);
    //TRISCbits.TRISC2 = 0;
    //LATCbits.LC2 = 1;
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();       
    
    
    SPI1INTEbits.RXOIE = 1;
    
    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    uCAN_MSG ReceiveMsg;
    uCAN_MSG SendMsg;
    SendMsg.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
    SendMsg.frame.id = canId; 
    SendMsg.frame.dlc = 1; 
    SendMsg.frame.data0 = 0x33;     //Message to enable SPI
    
    bool spi_RX = false;
    uint8_t data_RX = 0x00;
    //LATCbits.LC2 = 1;
    //__delay_ms(1000);
    //LATCbits.LC2 = 0;
    //__delay_ms(1000);
    //uint8_t data_RX = 0x00;
    
    //__delay_ms(1000);
    PIR5bits.TXB0IF = 0;
    PIR5bits.TXB1IF = 0;
    PIR5bits.TXB2IF = 0;
    
    CAN_transmit(&SendMsg); //This on its own will return '1' when the buffer is loaded, this doesn't mean that the message is received on the other node  
    //while(PIR5bits.TXB0IF!=1 || PIR5bits.TXB1IF!=1 || PIR5bits.TXB2IF!=1);        //POR ALGUN MOTIVO AQUI NO FUNCIONA PERO EN EL WHILE(1) SI QUE FUNCIONA
/*
    if(PIR5bits.TXB0IF){
        PIR5bits.TXB0IF = 0;
    }
    else if(PIR5bits.TXB1IF){
        PIR5bits.TXB1IF = 0;
    } 
    else if(PIR5bits.TXB2IF){
        PIR5bits.TXB2IF = 0;
    }
    */
    //LATCbits.LC2 = 1;
    //__delay_ms(1000);
    //LATCbits.LC2 = 0;
    //__delay_ms(1000);
    //SPI1CON0bits.EN = 1;
    while (1)
    {
        
        //LATCbits.LC2 = 1;
        //__delay_ms(1000);
        //LATCbits.LC2 = 0;
        //__delay_ms(1000);
        
        
        if(CAN_receive(&ReceiveMsg)){
           LATCbits.LC2 = 1;                                    //1
           __delay_ms(1000);
           LATCbits.LC2 = 0;
           __delay_ms(1000);
           
           
           
           if(ReceiveMsg.frame.data0 == 0x33){
                //CAN_sleep();         //Probar para ver si es por imcompatibilidad de dos modulos activos a la vez
                //LATCbits.LC2 = 1;
                SPI1_Open(SLAVE0_CONFIG);
                LATCbits.LC2 = 1;
                __delay_ms(1000);
                LATCbits.LC2 = 0;
                __delay_ms(1000);
                //Send message to enable SPI bus on the other node
                
                while(data_RX == 0x00){
                    /*
                    if(PIR2bits.SPI1RXIF){
                        data_RX = SPI1RXB;
                        LATCbits.LC2 = 1;
                        SPI1TCNTL = 1;
                        SPI1_WriteByte(0x55);
                        spi_RX = true;
                    }
                     * */
                    data_RX = SPI1_ExchangeByte(0x55);
                }
                //LATCbits.LC2 = 1;
                
                if(data_RX == 0x13){        
                  LATCbits.LC2 = 1;  
                }
                
  
           }
           
           
           
        }
        
        //if(SPI1INTFbits.RXOIF){     //This is happening since the SS interrupt isnt taking place (it isnt entering)
          //  SPI1INTFbits.RXOIF = 0;
//            data_RX = SPI1RXB;
            //LATCbits.LC2 = 1;
        //}
         
       
    }
}
/**
 End of File
*/