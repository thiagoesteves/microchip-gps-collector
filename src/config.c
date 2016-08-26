/*
 * Project: gps collector
 * Compiler: CCS PIC C Compiler
 * Version: 4.057
 */
 
 
/**
 *
 * @file config.c
 *
 * @author Thiago Esteves
 * @date 07/2008
 */
   
//******************** Includes para o arquivo *****************************//

#include "gps_collector.h"
#include "config.h"

//******************* Funções deste Módulo *********************************//

void init_device(void)
{

// OSCILADOR INTERNO 4.0 Mhz ------------------------------------------------
	setup_oscillator( OSC_8MHZ );

// INTERRUPÇÕES GLOBAIS ------------------------------------------------------
	//enable_interrupts ( GLOBAL );

// Configura SPI  
//enable_interrupts (INT_SSP);
//setup_spi(spi_master |spi_l_to_h |spi_clk_div_16 );

// TIMER 0 -------------------------------------------------------------------
// [85,33 us] - overflow: 5,461 ms --------------------------------------------
//setup_timer_0(RTCC_DIV_64|RTCC_INTERNAL|RTCC_8_BIT);
//disable_interrupts ( INT_TIMER0 );

// TIMER 1 -------------------------------------------------------------------
// [1 us] - overflow: 21,626 ms ----------------------------------------------
//setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
//disable_interrupts ( INT_TIMER1 );

// TIMER 2 -------------------------------------------------------------------
// [1 us] - overflow: 10 ms --------------------------------------------------
//setup_timer_2 ( T2_DIV_BY_4 , 0xFA , 10);// Interrupçãoo a cada 10ms
//disable_interrupts ( INT_TIMER2 );

// TIMER 3 -------------------------------------------------------------------
// [1 us] - overflow: 65,536 ms ----------------------------------------------
//setup_timer_3(T3_INTERNAL | T3_DIV_BY_1);
//disable_interrupts ( INT_TIMER3 );

// CCP1 ----------------------------------------------------------------------
// CAPTURE MODE - FALLING EDGE -----------------------------------------------
//  setup_ccp1(CCP_CAPTURE_FE);
//  enable_interrupts ( INT_CCP1 );

// CCP2 ----------------------------------------------------------------------
// CAPTURE MODE - FALLING EDGE -----------------------------------------------
//setup_ccp2(CCP_CAPTURE_FE);
//enable_interrupts ( INT_CCP2 );

//enable_interrupts ( INT_RDA );

// INTERRUPÇÃO EXTERNA 1 RB0 -------------------------------------------------
// FALLING EDGE --------------------------------------------------------------
//ext_int_edge ( 0 , H_TO_L ); // Set up PIC18 EXT1
//disable_interrupts ( INT_EXT );

// INTERRUPÇÃO EXTERNA 2 RB1 -------------------------------------------------
// FALLING EDGE --------------------------------------------------------------
//ext_int_edge ( 1 , H_TO_L ); // Set up PIC18 EXT2
//disable_interrupts ( INT_EXT1 );

// INTERRUPÇÃO EXTERNA 3 RB2 -------------------------------------------------
// FALLING EDGE --------------------------------------------------------------
// ext_int_edge( 2 , L_TO_H); // Set up PIC18 EXT3
// disable_interrupts ( INT_EXT2 );

// INTERRUPÇÃO RB ------------------------------------------------------------

//clear_interrupt(INT_RB);      // Necess�rio para evitar reentrada
//enable_interrupts ( INT_RB );

// INTERRUPÇÕES GLOBAIS ------------------------------------------------------
//enable_interrupts ( GLOBAL );

// CONVERSOR AD --------------------------------------------------------------
//setup_adc ( ADC_CLOCK_INTERNAL );
//setup_adc_ports ( AN0_AN1_AN2_AN3_AN4 );


//***************************************************************************//


}

