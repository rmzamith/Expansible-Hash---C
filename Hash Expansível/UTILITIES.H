#if ! defined( UTILITIES_ )
#define UTILITIES_
/***************************************************************************
*
*  $MCD Módulo de definição: UTI  Utilities
*
*  Arquivo gerado:              UTILITIES.h
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
*  $ED Descrição do módulo
*     Funções auxiliares.
*
***************************************************************************/
 
#if defined( UTILITIES_OWN )
   #define UTILITIES_EXT
#else
   #define UTILITIES_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: UTI Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
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
*  $FC Função: UTI  &Comparar faixa de bits
*
*  $ED Descrição da função
*     Compara faixa de bits entre 0 e 31 de dois inteiros de 32 bits.
*
*  $EP Parâmetros
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

/********** Fim do módulo de definição: BUC  Bucket para Hash Expansível **********/

#else
#endif
