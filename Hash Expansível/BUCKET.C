/***************************************************************************
*  $MCI Módulo de implementação: BUC  Bucket para Hash Expansível
*
*  Arquivo gerado:              BUCKET.c
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
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <malloc.h>

#include "LISTA.h"
#include "UTILITIES.h"

#define BUCKET_OWN
#include "BUCKET.h"
#undef BUCKET_OWN

// Tamanho do bucket
#define BUCKET_SIZE 3

#define IVALID_BUCKET_ENTRY 0xFFFFFFFF

/***********************************************************************
*
*  $TC Tipo de dados: BUC Elemento de um Bucket
*
*
***********************************************************************/

   typedef struct tagElemBucket {

         unsigned int chaveElemento ;
               /* Chave que representa o elemento */
         
         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

   } tpElemBucket ;

/***********************************************************************
*
*  $TC Tipo de dados: BUC Bucket
*
*
***********************************************************************/

   typedef struct BUC_tagBucket {

         tpElemBucket * pBucketData ;
               /* Ponteiro para vetor com os dados do bucket */

         int bucketSensitiveBits;
               /* Bits relevantes para o bucket, começando do menos significativo */

         unsigned int bucketID ;
               /* Número identificador do bucket */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   } BUC_tpBucket ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( BUC_tppBucket pBucket ,
                         tpElemBucket * pElemBucket   );

   static void  LiberarElementoTemporario ( void * elemBucket );


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: BUC &Criar Bucket
*  ****/

   BUC_tppBucket BUC_CriarBucket( int bucketSensitiveBits, int bucketID,
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      tpElemBucket * pBucketData; 
      BUC_tpBucket * pBucket = NULL ;
      int inxAuxBucketDataInitialization;

      pBucketData = ( tpElemBucket * ) malloc ( sizeof ( tpElemBucket ) * BUCKET_SIZE );
      if ( pBucketData == NULL )
      {
          return NULL;
      }
      for(inxAuxBucketDataInitialization = 0; inxAuxBucketDataInitialization < BUCKET_SIZE; inxAuxBucketDataInitialization++ )
      {
          pBucketData[inxAuxBucketDataInitialization].chaveElemento = IVALID_BUCKET_ENTRY;
          pBucketData[inxAuxBucketDataInitialization].pValor = NULL;
      }
      
      pBucket = ( BUC_tpBucket * ) malloc( sizeof( BUC_tpBucket )) ;
      if ( pBucket == NULL )
      {
         return NULL ;
      } /* if */

      pBucket->pBucketData = pBucketData;
      pBucket->ExcluirValor = ExcluirValor ;
      BUC_DefinirBucketID( pBucket, bucketID );
      BUC_DefinirBucketSensitiveBits( pBucket, bucketSensitiveBits );

      return pBucket ;

   } /* Fim função: BUC  &Criar bucket */



/***************************************************************************
*
*  Função: BUC &Criar Elemento do Bucket
*  ****/

   BUC_tppElemenBucket BUC_CriarElementoDoBucket( unsigned int chaveElemento, void * pValor )
   {
       BUC_tppElemenBucket novoElem;

       novoElem = ( tpElemBucket * ) malloc( sizeof( tpElemBucket ));

       novoElem->chaveElemento = chaveElemento;
       novoElem->pValor = pValor;

       return novoElem;
   }

/***************************************************************************
*
*  Função: BUC &Obter tamanho do bucket 
*  ****/

    int BUC_ObterTamanhoMaximoBucket(  )
    {
        return BUCKET_SIZE;
    }

/***************************************************************************
*
*  Função: BUC &Definir Bucket bucketID
*  ****/

    void BUC_DefinirBucketID( BUC_tppBucket pBucket, unsigned int bucketID )
    {
        pBucket->bucketID = bucketID;
    }

/***************************************************************************
*
*  Função: BUC &Definir Bucket bucketSensitiveBits
*  ****/

    void BUC_DefinirBucketSensitiveBits( BUC_tppBucket pBucket, int bucketSensitiveBits )
    {
        pBucket->bucketSensitiveBits = bucketSensitiveBits;
    }

/***************************************************************************
*
*  Função: BUC &Obter Bucket bucketID
*  ****/

    unsigned int BUC_ObterBucketID( BUC_tppBucket pBucket )
    {
        return pBucket->bucketID;
    }

/***************************************************************************
*
*  Função: BUC &Obter Bucket bucketSensitiveBits
*  ****/

    int BUC_ObterBucketSensitiveBits( BUC_tppBucket pBucket )
    {
        return pBucket->bucketSensitiveBits;
    }

/***************************************************************************
*
*  Função: BUC &Obter chave de elemento do bucket
*  ****/

    unsigned int BUC_ObterBucketElementoChave( BUC_tppElemenBucket pBucketElem )
    {
        return pBucketElem->chaveElemento;
    }

/***************************************************************************
*
*  Função: BUC &Obter valor de elemento do bucket
*  ****/

    void * BUC_ObterBucketElementoValor( BUC_tppElemenBucket pBucketElem )
    {
        return pBucketElem->pValor;
    }


/***************************************************************************
*
*  Função: BUC &Obter número de elementos do bucket
*  ****/

    int BUC_ObterNumElementosBucket( BUC_tppBucket pBucket )
    {
        tpElemBucket * pArrayBucketData;
        int inxAuxCountBucket;
        int bucketCounter;

        if ( pBucket == NULL )
        {
             return BUC_CondRetInvalido;
        }

        pArrayBucketData = pBucket->pBucketData;

        if ( pArrayBucketData == NULL )
        {
             return BUC_CondRetInvalido;
        }

        bucketCounter = 0;

        for (inxAuxCountBucket = 0; inxAuxCountBucket < BUCKET_SIZE; inxAuxCountBucket++  )
        {
            tpElemBucket currBucketElement;

            currBucketElement = pArrayBucketData[inxAuxCountBucket];
            if ( currBucketElement.chaveElemento == IVALID_BUCKET_ENTRY )
            {
                continue;
            }

            bucketCounter++;
        }

        return bucketCounter;
    }

/***************************************************************************
*
*  Função: BUC &Inserir em Bucket
*  ****/

   BUC_tpCondRet BUC_InserirEmBucket( unsigned int chaveElemento, void * pValor, BUC_tppBucket pBucket  )
   {

      int inxAuxCheckBucketEntrys;
      tpElemBucket bucketDataToInsert, * pArrayBucketData;

      if ( pBucket == NULL )
      {
          return BUC_CondRetInvalido;
      }

      pArrayBucketData = pBucket->pBucketData;

      if ( pArrayBucketData == NULL )
      {
          return BUC_CondRetInvalido;
      }

      for ( inxAuxCheckBucketEntrys = 0; inxAuxCheckBucketEntrys < BUCKET_SIZE; inxAuxCheckBucketEntrys++ )
      {
          tpElemBucket currBucketData;
          int currKey;

          currBucketData = pArrayBucketData[inxAuxCheckBucketEntrys];

          if ( currBucketData.chaveElemento == IVALID_BUCKET_ENTRY )
          {
              continue;
          }

          currKey = currBucketData.chaveElemento;

          if ( currKey == chaveElemento )
          {
              return BUC_CondRetElementoInserido;
          }
      }

      bucketDataToInsert.chaveElemento = chaveElemento;
      bucketDataToInsert.pValor = pValor;
     
      for ( inxAuxCheckBucketEntrys = 0; inxAuxCheckBucketEntrys < BUCKET_SIZE; inxAuxCheckBucketEntrys++ )
      {
          tpElemBucket currBucketData;

          currBucketData = pArrayBucketData[inxAuxCheckBucketEntrys];
          if ( currBucketData.chaveElemento == IVALID_BUCKET_ENTRY )
          {
              pArrayBucketData[inxAuxCheckBucketEntrys] = bucketDataToInsert;
              
              return BUC_CondRetOK;
          }
      }
      return BUC_CondRetBucketCheio;

   } /* Fim função: BUC  &Inserir em bucket */

/***************************************************************************
*
*  Função: BUC &Remover do Bucket
*  ****/

   BUC_tpCondRet BUC_RemoverElementoDoBucket( unsigned int chaveElemento, BUC_tppBucket pBucket, int booleanExcluirElemento  )
   {

      int inxAuxCheckBucketEntrys;
      tpElemBucket * pArrayBucketData;

      if ( pBucket == NULL )
      {
          return BUC_CondRetInvalido;
      }

      pArrayBucketData = pBucket->pBucketData;

      if ( pArrayBucketData == NULL )
      {
          return BUC_CondRetInvalido;
      }

      for ( inxAuxCheckBucketEntrys = 0; inxAuxCheckBucketEntrys < BUCKET_SIZE; inxAuxCheckBucketEntrys++ )
      {
          tpElemBucket currBucketData;
          int currKey;

          currBucketData = pArrayBucketData[inxAuxCheckBucketEntrys];
          currKey = currBucketData.chaveElemento;

          if ( currKey == chaveElemento )
          {
              if ( booleanExcluirElemento == 1)
              {
                  LiberarElemento( pBucket, &currBucketData );
              }
              else
              {
                currBucketData.chaveElemento = IVALID_BUCKET_ENTRY;
                currBucketData.pValor = NULL;
              }

              pArrayBucketData[inxAuxCheckBucketEntrys] = currBucketData;

              return BUC_CondRetOK;
          }
      }
      return BUC_CondRetNaoAchou;

   } /* Fim função: BUC  &Remover do bucket */

/***************************************************************************
*
*  Função: BUC &Buscar chave no Bucket
*  ****/

   void * BUC_BuscarChaveNoBucket( unsigned int chaveElemento, BUC_tppBucket pBucket  )
   {

      int inxAuxCheckBucketEntrys;
      tpElemBucket * pArrayBucketData;

      if ( pBucket == NULL )
      {
          return NULL;
      }

      pArrayBucketData = pBucket->pBucketData;

      if ( pArrayBucketData == NULL )
      {
          return NULL;
      }

      for ( inxAuxCheckBucketEntrys = 0; inxAuxCheckBucketEntrys < BUCKET_SIZE; inxAuxCheckBucketEntrys++ )
      {
          tpElemBucket currBucketData;
          int currKey;

          currBucketData = pArrayBucketData[inxAuxCheckBucketEntrys];

          if ( currBucketData.chaveElemento == IVALID_BUCKET_ENTRY )
          {
              continue;
          }

          currKey = currBucketData.chaveElemento;

          if ( currKey == chaveElemento )
          {
              return currBucketData.pValor;
          }
      }

      return NULL;

   } /* Fim função: BUC  &Remover do bucket */

/***************************************************************************
*
*  Função: BUC &Excluir Bucket
*  ****/

   void * BUC_ExcluirBucket( BUC_tppBucket pBucket )
   {

      int inxAuxCheckBucketEntrys;
      tpElemBucket * pArrayBucketData;

      if ( pBucket == NULL )
      {
          return NULL;
      }

      pArrayBucketData = pBucket->pBucketData;

      if ( pArrayBucketData == NULL )
      {
          return NULL;
      }

      for ( inxAuxCheckBucketEntrys = 0; inxAuxCheckBucketEntrys < BUCKET_SIZE; inxAuxCheckBucketEntrys++ )
      {
          tpElemBucket currBucketData;

          currBucketData = pArrayBucketData[inxAuxCheckBucketEntrys];

          if ( currBucketData.chaveElemento == IVALID_BUCKET_ENTRY )
          {
              continue;
          }

          LiberarElemento(pBucket, &currBucketData );
      }

      free ( pBucket );

      return NULL;

   } /* Fim função: BUC  &Excluir bucket */

/***************************************************************************
*
*  Função: BUC &Obter Elementos Irmaos
*  ****/

    LIS_tppLista BUC_BuscarElementosIrmaos( int bitFinal, unsigned int chaveAComparar, BUC_tppBucket pBucket )
    {
       int inxAuxCheckBucketEntrys;
       tpElemBucket * pArrayBucketData;
       LIS_tppLista returnList;

       returnList = LIS_CriarLista( LiberarElementoTemporario );
       if ( returnList == NULL )
       {
           return NULL;
       }

       pArrayBucketData = pBucket->pBucketData;

       for ( inxAuxCheckBucketEntrys = 0; inxAuxCheckBucketEntrys < BUCKET_SIZE; inxAuxCheckBucketEntrys++ )
       {
           int resultCompare = -2;
           tpElemBucket currElemBucket;
           unsigned int currElemChave; 

           currElemBucket = pArrayBucketData[inxAuxCheckBucketEntrys];
           currElemChave = currElemBucket.chaveElemento;

           resultCompare = UTI_CompararFaixaDeBitsInt(chaveAComparar, currElemChave, 0, bitFinal );
           
           if ( resultCompare == 0 )
           {
               tpElemBucket * newTempElemBucket;

               newTempElemBucket = ( tpElemBucket * ) malloc ( sizeof( tpElemBucket ));
               newTempElemBucket->chaveElemento = currElemBucket.chaveElemento;
               newTempElemBucket->pValor = currElemBucket.pValor;

               LIS_InserirElementoApos( returnList, newTempElemBucket);
           }
       }

       return returnList;
    }

/***************************************************************************
*
*  Função: BUC &Obter nivel de distinção
*  ****/

    int BUC_ObterDistincao ( BUC_tppBucket pBucket, unsigned int chave, int bitsSensibilidade )
    {

      int inxAuxCheckBucketEntrys;
      tpElemBucket * pArrayBucketData;

      if ( pBucket == NULL )
      {
          return NULL;
      }

      pArrayBucketData = pBucket->pBucketData;

      if ( pArrayBucketData == NULL )
      {
          return NULL;
      }

      for ( inxAuxCheckBucketEntrys = 0; inxAuxCheckBucketEntrys < BUCKET_SIZE; inxAuxCheckBucketEntrys++ )
      {
          int resultadoComparacao;
          tpElemBucket currBucketData, bucketAnterior;
          unsigned int currDataChave, antDataChave;

          if( inxAuxCheckBucketEntrys == 0 )
          {
              antDataChave = chave; 
          }
          else
          {
              bucketAnterior = pArrayBucketData[inxAuxCheckBucketEntrys - 1];
              antDataChave = bucketAnterior.chaveElemento;
          }
          
          currBucketData = pArrayBucketData[inxAuxCheckBucketEntrys];
          currDataChave = currBucketData.chaveElemento;       

          resultadoComparacao = UTI_CompararFaixaDeBitsInt(currDataChave, antDataChave, 0, bitsSensibilidade );

          if ( resultadoComparacao != 0 )
          {
              return 1;
          }
      }
      return 0;

   }

/***************************************************************************
*
*  Função: BUC &Obter id distinto
*  ****/

    unsigned int BUC_ObterIdDistinto ( BUC_tppBucket pBucket, unsigned int chave, int bitsSensibilidade )
    {
        BUC_tppElemenBucket bucketData;
        int inxAux;
        unsigned int bucketId, comparadorChave, resultComparaChaveParam;
        
        
        bucketId = pBucket->bucketID;
        bucketData = pBucket->pBucketData;

        comparadorChave = UTI_ConstruirComparadorSequencial( bitsSensibilidade );

        resultComparaChaveParam = chave & comparadorChave;

        if ( resultComparaChaveParam !=  bucketId )
        {
            return resultComparaChaveParam;
        }

        for ( inxAux = 0; inxAux < BUCKET_SIZE; inxAux++ )
        {
            tpElemBucket currElemBucket;
            unsigned int resultComparaChaveCurrElem, currElemId;

            currElemBucket = bucketData[inxAux];
            currElemId = currElemBucket.chaveElemento;

            resultComparaChaveCurrElem = currElemId & comparadorChave;

            if ( resultComparaChaveCurrElem != bucketId )
            {
                return resultComparaChaveCurrElem;
            }
        }

        return 0xFFFFFFFF;
    }

/***************************************************************************
*
*  Função: BUC &Migrar Buckets
*  ****/
    
    BUC_tpCondRet BUC_MigrarBuckets ( BUC_tppBucket bucketDestino, BUC_tppBucket bucketOrigem, LIS_tppLista elementosIrmaos )
    {
        int numIrmaosBucketAntigo, inxAuxMigracaoIrmao;
  
        numIrmaosBucketAntigo = LIS_ObterNumElem(elementosIrmaos);

        IrInicioLista(elementosIrmaos);
        for ( inxAuxMigracaoIrmao = 0; inxAuxMigracaoIrmao < numIrmaosBucketAntigo; inxAuxMigracaoIrmao++ )
        {
            BUC_tppElemenBucket pCurrIrmao;
            unsigned int currIrmaoChave;
            void * pCurrIrmaoValor;
            BUC_tpCondRet bucketCondRetAux;
            LIS_tpCondRet lisCondRetAux;

            pCurrIrmao = LIS_ObterValor( elementosIrmaos );
            currIrmaoChave = BUC_ObterBucketElementoChave(pCurrIrmao);
            pCurrIrmaoValor = BUC_ObterBucketElementoValor(pCurrIrmao);

            bucketCondRetAux = BUC_InserirEmBucket(currIrmaoChave,pCurrIrmaoValor,bucketDestino);
            if ( bucketCondRetAux != BUC_CondRetOK )
            {
               return BUC_CondRetErro;
            }

            bucketCondRetAux = BUC_RemoverElementoDoBucket(currIrmaoChave,bucketOrigem, 0);
            if ( bucketCondRetAux != BUC_CondRetOK )
            {
               return BUC_CondRetErro;
            }

            lisCondRetAux = LIS_AvancarElementoCorrente(elementosIrmaos,1);
            if ( lisCondRetAux != LIS_CondRetOK && (inxAuxMigracaoIrmao < numIrmaosBucketAntigo - 1) )
            {
                return BUC_CondRetErro;
            }
        }
        return BUC_CondRetOK;
    }

/***************************************************************************
*
*  Função: BUC &ImprimirBucket
*  ****/

    void BUC_ImprimirBucket( BUC_tppBucket pBucket )
    {
        int inxAux;
        tpElemBucket * pArrayBucketData;

        pArrayBucketData = pBucket->pBucketData;

        printf("*** Bucket ID: %d ***\n", pBucket->bucketID );
        printf("#Bits Relevantes: %d\n", pBucket->bucketSensitiveBits );
        printf("#Elementos inseridos: %d\n", BUC_ObterNumElementosBucket(pBucket));
        for (inxAux = 0; inxAux < BUCKET_SIZE; inxAux++)
        {
            tpElemBucket pCurrBucketData;
            unsigned int chaveElemento;

            pCurrBucketData = pArrayBucketData[inxAux];
            chaveElemento = pCurrBucketData.chaveElemento;

            if ( chaveElemento == IVALID_BUCKET_ENTRY )
            {
                printf("    - Chave: Vazia\n" );
            }
            else
            {
                printf("    - Chave: %d\n", chaveElemento );
            }
        }
        printf("\n");
    }

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: BUC  -Liberar elemento do bucket
*
*  $ED Descrição da função
*     Exclui elemento do bucket.
*
***********************************************************************/

   void LiberarElemento( BUC_tppBucket pBucket ,
                         tpElemBucket * pElemBucket   )
   {

      if (( pBucket != NULL )  
        && ( pBucket->ExcluirValor != NULL ))
      {
         void * pValor;
         

         pBucket->ExcluirValor( pElemBucket->pValor ) ;

         pElemBucket->pValor = NULL;
         pElemBucket->chaveElemento = IVALID_BUCKET_ENTRY;
         

         pElemBucket = ( tpElemBucket * ) malloc ( sizeof(tpElemBucket) );

         pElemBucket->chaveElemento = IVALID_BUCKET_ENTRY;
         pElemBucket->pValor = NULL;

      } /* if */

   } /* Fim função: BUC  -Liberar elemento do bucket */

/***************************************************************************
*
*  Função: BUC &Liberar Elemento Temporário
*  ****/

   void LiberarElementoTemporario ( void * elemBucket )
   {
       free(elemBucket);
   }


/********** Fim do módulo de implementação: BUC  Bucket para Hash Expansível **********/

