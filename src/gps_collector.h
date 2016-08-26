


#include <16F88.h>

#include "typedefs.h"

#device adc=8

#fuses INTRC_IO , NOWDT , NOPUT, NOPROTECT, NOBROWNOUT, NOLVP, MCLR
#use delay( clock = 8000000 )
#use rs232( baud = 9600, xmit=PIN_B5, rcv=PIN_A3, stream = PEN_BS)
#use rs232( baud = 9600, xmit=PIN_A6, rcv=PIN_A7, stream = HOSTPC)
#use rs232( baud = 4800, xmit=pin_A1, rcv=pin_A0, stream = GPS)


