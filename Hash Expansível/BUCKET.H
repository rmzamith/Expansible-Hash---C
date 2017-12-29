#if ! defined( BUCKET_ )
#define BUCKET_
/***************************************************************************
*
*  $MCD Módulo de definição: BUC  Bucket para Hash Expansível
*
*  Arquivo gerado:              BUCKET.h
*  Letras identificadoras:      BUC
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
*     Implementa estrutura de bucket para hash expansível.
*
***************************************************************************/
 
#if defined( BUCKET_OWN )
   #define BUCKET_EXT
#else
   #define BUCKET_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct BUC_tagBucket * BUC_tppBucket ;

typedef struct tagElemBucket * BUC_tppElemenBucket ;


/***********************************************************************
*
*  $TC Tipo de dados: BUC Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da bucket
*
***********************************************************************/

   typedef enum {

         BUC_CondRetOK ,
               /* Concluiu corretamente */

         BUC_CondRetInvalido ,
               /* O bucket esta inválido ou nulo */

         BUC_CondRetBucketCheio ,
               /* Foi atingido o máximo numero de elementos de armazenagem do bucket */

         BUC_CondRetNaoAchou ,
               /* Não encontrou a chave procurada */

         BUC_CondRetElementoInserido ,
               /* Elemento já esta inserido no bucket */

         BUC_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um elemento do bucket */
         
         BUC_CondRetErro
               /* Ocorreu erro em alguma operação */

   } BUC_tpCondRet ;


   BUC_tppBucket BUC_CriarBucket( int bucketSensitiveBits, int bucketID , void ( * ExcluirValor ) ( void * pDado ) ) ;

   BUC_tppElemenBucket BUC_CriarElementoDoBucket( unsigned int chaveElemento, void * pValor );

   int BUC_ObterTamanhoMaximoBucket( void );

   void BUC_DefinirBucketID( BUC_tppBucket pBucket, unsigned int bucketID );

   void BUC_DefinirBucketSensitiveBits( BUC_tppBucket pBucket, int bucketSensitiveBits );

   unsigned int BUC_ObterBucketID( BUC_tppBucket pBucket );

   int BUC_ObterBucketSensitiveBits( BUC_tppBucket pBucket );

   int BUC_ObterNumElementosBucket( BUC_tppBucket pBucket );

   unsigned int BUC_ObterBucketElementoChave( BUC_tppElemenBucket pBucketElem );

   void * BUC_ObterBucketElementoValor( BUC_tppElemenBucket pBucketElem );

   BUC_tpCondRet BUC_InserirEmBucket( unsigned int chaveElemento, void * pValor, BUC_tppBucket pBucket );

   BUC_tpCondRet BUC_RemoverElementoDoBucket( unsigned int chaveElemento, BUC_tppBucket pBucket, int booleanExcluirElem ) ;

   void * BUC_BuscarChaveNoBucket( unsigned int chaveElemento, BUC_tppBucket pBucket  );

   void * BUC_ExcluirBucket( BUC_tppBucket pBucket );

   LIS_tppLista BUC_BuscarElementosIrmaos( int bitFinal, unsigned int chaveAComparar, BUC_tppBucket pBucket );

   int BUC_ObterDistincao ( BUC_tppBucket pBucket, unsigned int chave,int bitsSensibilidade  );

   unsigned int BUC_ObterIdDistinto ( BUC_tppBucket pBucket, unsigned int chave, int bitsSensibilidade );

   BUC_tpCondRet BUC_MigrarBuckets ( BUC_tppBucket bucketDestino, BUC_tppBucket bucketOrigem, LIS_tppLista elementosIrmaos );

   void BUC_ImprimirBucket( BUC_tppBucket pBucket );


#undef BUCKET_EXT

/********** Fim do módulo de definição: BUC  Bucket para Hash Expansível **********/

#else
#endif
