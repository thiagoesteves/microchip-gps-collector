/*
 * Project: gps collector
 * Compiler: CCS PIC C Compiler
 * Version: 4.057
 */

/**
 *
 * @file main.c
 *
 * @author Thiago Esteves
 * @date 09/2008
 */ 

// Inclui o arquivo com as configurações do microcontrolador
#include <gps_collector.h>

// Inclui  os módulos que irá utilizar
#include "config.h"
#include "constants.h"
#include "variables.h"
#include "functions.h"

//*********************************** Programa Principal *****************************//

void main(void){

	uchar i, config;
	
	init_device();                   // Inicializa as configurações do PIC.
	
	pisca_led(); 
	fprintf (HOSTPC, "\n\r Incializando \n\r");
	
	rx_count = 0;
	config = 0;                           // Flag responsável pela gravação no PEN DRIVE
	
	
	
	fprintf (HOSTPC, "\n\r Detectando USB e Versao:.... \n\r");
	
	// Flag indicativo de inicialização de Pen Drive
	flag_chegou = 0;
	while (!kbhit(PEN_BS)){};             // Aguarda viniculum envar versão
	
	while (flag_chegou == 0)
	{
		if (kbhit(PEN_BS))
		{
			buffer_uart[rx_count] = getc(PEN_BS);
			rx_count++;
			if (rx_count == 50)
				rx_count = 0;
			if (buffer_uart[rx_count] == 0x0D)
				flag_chegou = 1;
		}
	}
	
	for (i = 0; i < rx_count ; i++)
	{
		fputc (buffer_uart[i], HOSTPC);
	}
	fprintf (HOSTPC, "\r\n");
	
	// Acende o LED indicando que tudo ocorreu bem
	output_high ( PIN_B0 );

	while (TRUE){
		
		// Se chegou dado na serial
		if (kbhit(GPS)== 1)
			buffer_uart[0] = fgetc(GPS);
		
		// Caso tenha o valor inicial Válido
		if ( buffer_uart[0] == '$' )
		{
			
			for (i=0;i<5;i++)
			{                                                // Captura a palavra de comando
				while (kbhit(GPS)==0){}
				buffer_uart[i] = fgetc(GPS);                 // Armazena no buffer
			}
			
			if (compara_chars (buff_comp, buffer_uart, 5))   // Confere com o comando solicitado
			{
				
				
				for (i=0; i<50; i++)
				{                                            // captura os proximos 40 bytes
					while (kbhit(GPS)==0){}
					buffer_uart[i] = fgetc(GPS);             // armazena no buffer
				}
				
				Analise_buff_gps(buffer_uart, config);
			}
		}
		
		// Faz a Análise do Botão
		if (!input(PIN_A2))
		{
			config ^= 0xFF;
			delay_ms(100);
			while (!input(PIN_A2)){};
			delay_ms(200);
			
			// Configura Viniculum
			if (config)
				fprintf (PEN_BS, "IPA\r");
		}
	}
}
