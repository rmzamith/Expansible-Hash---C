/***************************************************************************
*  $MCI Módulo de implementação: UTI  Utilities
*
*  Arquivo gerado:              UTILITIES.c
*  Letras identificadoras:      UTI
*
*
*  Projeto: INF 1010 Hash Expansível
*  Autores: rmz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       rmz    17/set/2012 inicio do desenvolvimento
*
***************************************************************************/

#include <stdio.h>

#define UTILITIES_OWN
#include "UTILITIES.h"
#undef UTILITIES_OWN

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: UTI  &Comparar faixa de bits
*  ****/

   int UTI_CompararFaixaDeBitsInt( unsigned int valor1, unsigned int valor2, int bitInicio, int bitFim  )
   {
       int valor1Aux, valor2Aux;
       int inxAux;

       if ( bitInicio > bitFim || bitInicio < 0 || bitFim > 31 )
       {
           return -2;
       }

       valor1Aux = valor1 >> bitInicio;
       valor2Aux = valor2 >> bitInicio;

       for (inxAux = bitInicio; inxAux < bitFim; inxAux++  )
       {
           int currBitValue1;
           int currBitValue2;

           currBitValue1 = valor1Aux & 1;
           currBitValue2 = valor2Aux & 1;

           if ( currBitValue1 < currBitValue2 )
           {
               return -1;
           }
           else if ( currBitValue1 > currBitValue2 )
           {
               return 1;
           }

           valor1Aux = valor1Aux >> 1;
           valor2Aux = valor2Aux >> 1;
       }
       return 0;

   }

/***************************************************************************
*
*  Função: UTI  &Alterar bit
*  ****/

   unsigned int UTI_AlterarBit( unsigned int valor, int bit )
   {
       unsigned int valorAux;
       int comparatorAux, comparator;

       if ( bit < 0 || bit > 31 )
       {
           return -2;
       }

       valorAux = 1 << bit;

       if ( ( valorAux & valor ) == 0)
       {
           return valor + valorAux;
       }
       else
       {
           comparatorAux = -1;
           comparator = comparatorAux ^ valorAux;

           return comparator & valor;
       }
   }

/***************************************************************************
*
*  Função: UTI  &Construir Comparador
*  ****/

   int UTI_ConstruirComparadorSequencial( int numBits  )
   {
       int returnValue;
       int inxAux;

       returnValue = 0;

       for ( inxAux = 0; inxAux < numBits; inxAux++ )
       {
           returnValue = returnValue << 1;
           returnValue = ( returnValue | 1 );
       }

       return returnValue;

   }

/********** Fim do módulo de implementação: UTI  Utilities **********/