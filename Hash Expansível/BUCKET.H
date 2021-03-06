#if ! defined( BUCKET_ )
#define BUCKET_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: BUC  Bucket para Hash Expans�vel
*
*  Arquivo gerado:              BUCKET.h
*  Letras identificadoras:      BUC
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
*     Implementa estrutura de bucket para hash expans�vel.
*
***************************************************************************/
 
#if defined( BUCKET_OWN )
   #define BUCKET_EXT
#else
   #define BUCKET_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct BUC_tagBucket * BUC_tppBucket ;

typedef struct tagElemBucket * BUC_tppElemenBucket ;


/***********************************************************************
*
*  $TC Tipo de dados: BUC Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da bucket
*
***********************************************************************/

   typedef enum {

         BUC_CondRetOK ,
               /* Concluiu corretamente */

         BUC_CondRetInvalido ,
               /* O bucket esta inv�lido ou nulo */

         BUC_CondRetBucketCheio ,
               /* Foi atingido o m�ximo numero de elementos de armazenagem do bucket */

         BUC_CondRetNaoAchou ,
               /* N�o encontrou a chave procurada */

         BUC_CondRetElementoInserido ,
               /* Elemento j� esta inserido no bucket */

         BUC_CondRetFaltouMemoria,
               /* Faltou mem�ria ao tentar criar um elemento do bucket */
         
         BUC_CondRetErro
               /* Ocorreu erro em alguma opera��o */

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

/********** Fim do m�dulo de defini��o: BUC  Bucket para Hash Expans�vel **********/

#else
#endif
