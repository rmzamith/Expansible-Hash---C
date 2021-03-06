#if ! defined( UTILITIES_ )
#define UTILITIES_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: UTI  Utilities
*
*  Arquivo gerado:              UTILITIES.h
*  Letras identificadoras:      UTI
*
*
*  Projeto: INF 1010 Hash Expans�vel
*  Autores: rmz
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       rmz    17/set/2012 inicio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Fun��es auxiliares.
*
***************************************************************************/
 
#if defined( UTILITIES_OWN )
   #define UTILITIES_EXT
#else
   #define UTILITIES_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: UTI Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         UTI_CondRetOK ,
               /* Concluiu corretamente */

         UTI_CondRetErro
               /* Concluiu com erro */

   } UTI_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: UTI  &Comparar faixa de bits
*
*  $ED Descri��o da fun��o
*     Compara faixa de bits entre 0 e 31 de dois inteiros de 32 bits.
*
*  $EP Par�metros
*     valor1  - valor a ser comparado.
*     valor2  - valor a ser comparado.
*     bitInicio  - bit inicial a ser comparado.
*     bitFim  - bit final a ser comparado.
*
*  $FV Valor retornado
*     -1 se valor1 < valor2, 0 se valor 1 == valor2, 1 se valor1 > valor2 , -2 erro.
*
***********************************************************************/

   int UTI_CompararFaixaDeBitsInt( unsigned int valor1, unsigned int valor2, int bitInicio, int bitFim  );

   unsigned int UTI_AlterarBit( unsigned int valor, int bit );

   int UTI_ConstruirComparadorSequencial( int numBits );


#undef UTILITIES_EXT

/********** Fim do m�dulo de defini��o: BUC  Bucket para Hash Expans�vel **********/

#else
#endif
