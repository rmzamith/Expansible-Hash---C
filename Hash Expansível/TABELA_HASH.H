#if ! defined( TABELA_HASH_ )
#define TABELA_HASH_
/***************************************************************************
*
*  $MCD Módulo de definição: TAH  Tabela para Hash Expansível
*
*  Arquivo gerado:              TABELA_HASH.c
*  Letras identificadoras:      TAH
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
*     Implementa estrutura da tabela que armazena a referência para os diversos 
*     buckets que compões o hash.
*
***************************************************************************/
 
#if defined( TABELA_HASH_OWN )
   #define TABELA_HASH_EXT
#else
   #define TABELA_HASH_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct TAH_tagTabelaHash * TAH_tppTabelaHash ;


/***********************************************************************
*
*  $TC Tipo de dados: TAH Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da tabela hash
*
***********************************************************************/

   typedef enum {

         TAH_CondRetOK ,
               /* Concluiu corretamente */

         TAH_CondRetErro ,
               /* Ocorreu Erro */

         TAH_CondRetNaoAchou ,
               /* Não encontrou a chave procurada */

         TAH_CondRetElementoInserido ,
               /* Elemento já esta inserido na tabela */

         TAH_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento da tabela */

   } TAH_tpCondRet ;


   TAH_tppTabelaHash TAH_CriarTabelaHash( void   ( * ExcluirValor ) ( void * pDado ), unsigned int ( * HashFunction ) ( char * strChaveElemento ));

   TAH_tpCondRet TAH_InserirEmTabelaHash ( TAH_tppTabelaHash pTabelaHash, char * strChaveElemento, void * pValor );

   void * TAH_BuscarEmTabelaHash ( TAH_tppTabelaHash pTabelaHash, char * strChaveElemento );

   TAH_tpCondRet TAH_ExcluirEmTabelaHash ( TAH_tppTabelaHash pTabelaHash, char * strChaveElemento );

   void TAH_ImprimirTabelaHash( TAH_tppTabelaHash pTabelaHash );


#undef TABELA_HASH_EXT

/********** Fim do módulo de definição: BUC  Bucket para Hash Expansível **********/

#else
#endif
