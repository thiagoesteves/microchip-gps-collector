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


//******** Funções disponibilizadas para outros módulos**********************//

// Função que acende e apaga um led por 100ms
void pisca_led();

// Função que compara dois vetores conforme a quantidade requerida

uchar compara_chars (uchar *tmp1_buff, uchar *tmp2_buff, uchar num_caracteres);

// Função que analisa o buffer recebido do gps

void Analise_buff_gps (uchar *buff, uchar armazena_cartao_sd);

//***************************************************************************//
