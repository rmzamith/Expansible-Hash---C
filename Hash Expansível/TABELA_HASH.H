#if ! defined( TABELA_HASH_ )
#define TABELA_HASH_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: TAH  Tabela para Hash Expans�vel
*
*  Arquivo gerado:              TABELA_HASH.c
*  Letras identificadoras:      TAH
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
*     Implementa estrutura da tabela que armazena a refer�ncia para os diversos 
*     buckets que comp�es o hash.
*
***************************************************************************/
 
#if defined( TABELA_HASH_OWN )
   #define TABELA_HASH_EXT
#else
   #define TABELA_HASH_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct TAH_tagTabelaHash * TAH_tppTabelaHash ;


/***********************************************************************
*
*  $TC Tipo de dados: TAH Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da tabela hash
*
***********************************************************************/

   typedef enum {

         TAH_CondRetOK ,
               /* Concluiu corretamente */

         TAH_CondRetErro ,
               /* Ocorreu Erro */

         TAH_CondRetNaoAchou ,
               /* N�o encontrou a chave procurada */

         TAH_CondRetElementoInserido ,
               /* Elemento j� esta inserido na tabela */

         TAH_CondRetFaltouMemoria
               /* Faltou mem�ria ao tentar criar um elemento da tabela */

   } TAH_tpCondRet ;


   TAH_tppTabelaHash TAH_CriarTabelaHash( void   ( * ExcluirValor ) ( void * pDado ), unsigned int ( * HashFunction ) ( char * strChaveElemento ));

   TAH_tpCondRet TAH_InserirEmTabelaHash ( TAH_tppTabelaHash pTabelaHash, char * strChaveElemento, void * pValor );

   void * TAH_BuscarEmTabelaHash ( TAH_tppTabelaHash pTabelaHash, char * strChaveElemento );

   TAH_tpCondRet TAH_ExcluirEmTabelaHash ( TAH_tppTabelaHash pTabelaHash, char * strChaveElemento );

   void TAH_ImprimirTabelaHash( TAH_tppTabelaHash pTabelaHash );


#undef TABELA_HASH_EXT

/********** Fim do m�dulo de defini��o: BUC  Bucket para Hash Expans�vel **********/

#else
#endif
