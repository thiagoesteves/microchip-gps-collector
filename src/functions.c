/*
 * Project: gps collector
 * Compiler: CCS PIC C Compiler
 * Version: 4.057
 */
 
 
/**
 *
 * @file functions.c
 *
 * @author Thiago Esteves
 * @date 07/2008
 */
   
///********************* Includes para o arquivo *****************************//

#include "gps_collector.h"
#include "functions.h"
#include "variables.h"

///******************* Protótipos de funções internas ************************//

uchar conv_ascii_uchar (uchar tmp);
void capture_float (void);

///***************************************************************************//

/**
 *
 * Esta função é responsável por piscar o led.
 *
 */
void pisca_led(void){

	output_high ( PIN_B0 );
	delay_ms ( 100 );
	output_low ( PIN_B0 );
	delay_ms ( 100 );

}

//***************************************************************************//

/**
 *
 * @param *tmp1_buff endereço do primeiro buffer
 * @param *tmp2_buff endereço do segundo buffer
 * @param num_caracteres numero de caracteres a serem comparados
 * @return  TRUE/FALSE
 *
 */

uchar compara_chars (uchar *tmp1_buff, uchar *tmp2_buff, uchar num_caracteres)
{

	uchar j;
	
	for (j=0; j<num_caracteres; j++)
	{
		if( tmp1_buff [j]!= tmp2_buff[j] )
			return FALSE;
	}
	return TRUE;
}

//***************************************************************************//

/**
 *
 * @param *buff endereço do primeiro buffer
 * @return TRUE/FALSE se existe ou não dados no gps
 *
 */

void Analise_buff_gps (uchar *buff, uchar armazena_cartao_sd)
{
	uchar hora, indice, j, tmp;
	
	indice = 0;     // Inicializa indice de varredura
	
	// Primera parte, impressão da hora
	fprintf (HOSTPC, "\r HORA: ");
	
	// Converte hora para um número inteiro
	hora = (conv_ascii_uchar(buff[++indice])* 10)+ conv_ascii_uchar(buff[++indice]);
	
	// Ajusta para a hora do Brasil
	if (hora < 3)
		hora += 21;
	else 
		hora -= 3;

	fprintf (HOSTPC, "%u",hora);                                // Imprime a hora
	fprintf (HOSTPC, ":");
	fputc (buff[++indice], HOSTPC);                             // Imprime os minutos
	fputc (buff[++indice], HOSTPC);
	fprintf (HOSTPC, ":");
	fputc (buff[++indice], HOSTPC);                             // Imprime os segundos
	fputc (buff[++indice], HOSTPC);
	
	indice = 11;
	tmp = buff[indice+1];
	if (tmp != ',')                                             // Verifica se há uma leitura válida
	{
		// Impressão da Latitude
		fprintf (HOSTPC, " LAT: ");
		fputc (buff[12], HOSTPC);                         // Imprime os graus
		fputc (buff[13], HOSTPC);
		
		fprintf (HOSTPC, "d ");
		fputc (buff[14], HOSTPC);                         // Imprime os minutos
		fputc (buff[15], HOSTPC);
		
		
		
		fprintf (HOSTPC, "' ");
		fprintf (HOSTPC, " DIR: ");   // Imprime a segundos
		
		fputc (buff[22], HOSTPC);                         // Imprime a direção
		
		
		
		// Impressão da longetude
		fprintf (HOSTPC, " LONG: ");
		tmp = buff[24];
		if (tmp != '0')
		{
			fputc (buff[24], HOSTPC);                     // Imprime os graus
			fputc (buff[25], HOSTPC);
			fputc (buff[26], HOSTPC);
			if (armazena_cartao_sd)
			{
				longetude = conv_ascii_uchar(buff[24]);
				longetude *= 100;
				longetude += conv_ascii_uchar(buff[25]);
				longetude *= 10;
				longetude += conv_ascii_uchar(buff[26]);
				if (buff[35] == 'W')
					longetude = -longetude;
			}
		}
		else
		{
			fputc (buff[25], HOSTPC);
			fputc (buff[26], HOSTPC);
			if (armazena_cartao_sd)
			{
				longetude = conv_ascii_uchar(buff[25]);
				longetude *= 10;
				longetude += conv_ascii_uchar(buff[26]);
				if (buff[35] == 'W')
					longetude = -longetude;
			}
		}
		
		
		fprintf (HOSTPC, "d ");
		fputc (buff[27], HOSTPC);                         // Imprime os minutos
		fputc (buff[28], HOSTPC);
		
		fprintf (HOSTPC, "' ");
		fprintf (HOSTPC, " DIR: ");                       // Imprime a segundos
		fputc (buff[35], HOSTPC);                         // Imprime a direção
		
		
		
		indice = 38;
		// Impressão do número de satélites
		fprintf (HOSTPC, " SATELITES: ");
		fputc (buff[++indice], HOSTPC);                   // Imprime a quantidade de satélites
		fputc (buff[++indice], HOSTPC);
		
		indice = 45;
		// Impressão da Altitude
		fprintf (HOSTPC, " Altitude: ");
		while ((buff[indice + 1] != '.') && (buff[indice + 1] != ','))
		{
			fputc (buff[++indice], HOSTPC);
		}
		
		fprintf (HOSTPC, " metros");
		
		// Caso o Pen Drive esteja selecionado para gravação
		if (armazena_cartao_sd)
		{
			// Apaga o LED
			output_low ( PIN_B0 );
			
			// Escreve dados apenas para evitar erros
			for (i = 0; i < 10; i++)
			{
				fprintf (PEN_BS, "\r");
				delay_ms(100);
			}
			
			// Abre o arquivo
			fprintf (PEN_BS, "OPW gps_file.txt\r");
			delay_ms (10);
			
			// Informa quantidade de bytes que serão enviados
			fprintf (PEN_BS, "WRF 33\r");
			delay_ms (10);
			
			fprintf (PEN_BS, "\n\r %4ld.", longetude);
			for (i = 0; i< 7; i++)
				buffer_temp[i] = buff[27+i];
			capture_float ();
			
			// Converte Latitude para número
			latitude = conv_ascii_uchar(buff[12]);
			latitude *= 10;
			latitude += conv_ascii_uchar(buff[13]);
			
			if (buff[22] == 'S')
				latitude = -latitude;
			
			fprintf (PEN_BS, "%3d.", latitude);
			
			for (i = 0; i< 7; i++)
				buffer_temp[i] = buff[14+i];
			capture_float ();
			
			indice = 45;
			// Impressão da Altitude
			while ((buff[indice + 1] != '.') && (buff[indice + 1] != ','))
			{
				fputc (buff[++indice], PEN_BS);
			}
			
			// Alimenta Linha 
			fprintf (PEN_BS, "\n");
			
			// Finaliza escrita
			for (i = 0; i < 5; i++)
				fprintf (PEN_BS, "\r");
			delay_ms (10);
			
			// Fecha o Arquivo
			fprintf (PEN_BS, "CLF gps_file.txt\r");
			delay_ms (100);
			
			// Acende o LED
			output_high ( PIN_B0 );
		}
		return;
	}
	else
	{
		fprintf (HOSTPC, "...................PROCURANDO SATELITE.................");
		return;
	}
	
}

//***************************************************************************//

/**
 *
 * @param tmp caracter a ser convertido 
 * @return tmp caracter convertido
 *
 */

uchar conv_ascii_uchar (uchar tmp)
{
	return (tmp -= 0x30);
}

//***************************************************************************//

/**
 *
 * @param tmp caracter a ser convertido 
 * @return tmp caracter convertido
 *
 */

void capture_float ()
{
	float teste;
	uchar i,j;
	
	teste = 0;
	for (i = 0; i < 7; i++)
	{
		if (i == 2)
			i++;
		teste = teste* 10.0;
		j = conv_ascii_uchar(buffer_temp[i]);
		teste = teste + j;
	}
	teste = teste * 10.0;
	teste = teste / 6.0;
	
	if (teste < 100000)
		fprintf (PEN_BS, "0%5.0f, ", teste);
	else
		fprintf (PEN_BS, "%5.0f, ", teste);	
}

//***************************************************************************//






