/*
 * Project: gps collector
 * Compiler: CCS PIC C Compiler
 * Version: 4.057
 */
 
 
/**
 *
 * @file variables.h
 *
 * @author Thiago Esteves
 * @date 07/2008
 */
 
//************************************** Definições de Constantes *******************************//

// Variáveis do GPS

uchar i;
uchar buffer_uart[50], buffer_temp[7];
uchar rx_count, flag_chegou;
uchar buff_comp[]= "GPGGA";

int8 latitude;
int16 longetude;
