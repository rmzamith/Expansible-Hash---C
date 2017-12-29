/***************************************************************************
*  $MCI Módulo de implementação: TAH  Tabela para Hash Expansível
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
***************************************************************************/

#include   <stdio.h>
#include   <math.h>
#include   <malloc.h>

#include "LISTA.h"
#include "BUCKET.h"
#include "UTILITIES.h"

#define TABELA_HASH_OWN
#include "TABELA_HASH.h"
#undef TABELA_HASH_OWN

/***********************************************************************
*
*  $TC Tipo de dados: TAH Entrada na Tabela de Hash
*
*
***********************************************************************/

   typedef struct tagElemTabela {

         unsigned int idEntrada ;
               /* Identificador de entrada na tabela */
         
         BUC_tppBucket pBucket ;
               /* Ponteiro para o bucket apontado pela entrada */

   } tpElemTabela ;

/***********************************************************************
*
*  $TC Tipo de dados: TAH Tabela Hash
*
*
***********************************************************************/

   typedef struct TAH_tagTabelaHash {

         LIS_tppLista pListaTabelaHash ;
               /* Ponteiro para vetor com os dados do bucket */

         int TabelaBitsRelevantes;
               /* Bits relevantes para as chaves da tabela, começando do menos significativo */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

         unsigned int ( * HashFunction ) ( char * strChaveElemento ) ;
               /* Ponteiro para a função de hash */

   } TAH_tpTabelaHash ;

/***** Protótipos das funções encapuladas no módulo *****/

   static unsigned int  ObterChave( TAH_tppTabelaHash pTabelaHash, char * strChave );

   static void LiberarElementoTabela( tpElemTabela * pElemTabela );

   static tpElemTabela * TAH_CriarEntradaTabelaHash( unsigned int idEntrada, BUC_tppBucket pBucket );

   static void * TAH_DefinirBucketDeEntrada( tpElemTabela * entradaTabela, BUC_tppBucket pBucket );

   static int TAH_ObterIdEntrada( tpElemTabela * entradaTabela );

   static unsigned int TAH_ObterEntradaParaChave( unsigned int  chaveElemento, int bitsRelevantes );

   static void TAH_ConsistirElementosTabela( TAH_tppTabelaHash pTabelaHash );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAH &Criar Tabela Hash
*  ****/

   TAH_tppTabelaHash TAH_CriarTabelaHash( void   ( * ExcluirValor ) ( void * pDado ),  unsigned int ( * HashFunction ) ( char * strChaveElemento ))
    {
        TAH_tppTabelaHash pTabelaHash;
        LIS_tppLista pListaTabelaHash;
        LIS_tpCondRet lisTpCondRetAux;
        BUC_tppBucket firstBucket;
        tpElemTabela * elementoTabela;

        pTabelaHash = ( TAH_tpTabelaHash * ) malloc ( sizeof ( TAH_tpTabelaHash ) );
        if ( pTabelaHash == NULL )
        {
            return NULL;
        }
        
        pListaTabelaHash = LIS_CriarLista( LiberarElementoTabela );
        if ( pListaTabelaHash == NULL )
        {
            return NULL;
        }

        firstBucket = BUC_CriarBucket(0,0, ExcluirValor);
        if ( firstBucket == NULL )
        {
            return NULL;
        }

        elementoTabela = TAH_CriarEntradaTabelaHash( 0,  firstBucket );
        if ( elementoTabela == NULL )
        {
            return NULL;
        }

        lisTpCondRetAux = LIS_InserirElementoApos( pListaTabelaHash, elementoTabela);
        if (lisTpCondRetAux != LIS_CondRetOK )
        {
            return NULL;
        }

        pTabelaHash->pListaTabelaHash = pListaTabelaHash;
        pTabelaHash->ExcluirValor = ExcluirValor;
        pTabelaHash->TabelaBitsRelevantes = 0;
        pTabelaHash->HashFunction = HashFunction;

        return pTabelaHash;
    }



/***************************************************************************
*
*  Função: TAH &Inserir em Tabela Hash
*  ****/

   TAH_tpCondRet TAH_InserirEmTabelaHash ( TAH_tppTabelaHash pTabelaHash, char * strChaveElemento, void * pValor )
   {
       int bitsRelevantes;
       int tamanhoBucket, tamanhoMaximoBucket;
       unsigned int entradaParaChave, chaveElemento;
       LIS_tppLista pListaTabelaHash;
       BUC_tppBucket bucketParaInserir;
       tpElemTabela * elementoTabela;
       void * bucketElemenValue;

       if ( pTabelaHash == NULL )
       {
           return TAH_CondRetErro;
       }

       chaveElemento = ObterChave( pTabelaHash, strChaveElemento );

       bitsRelevantes = pTabelaHash->TabelaBitsRelevantes;

       entradaParaChave = TAH_ObterEntradaParaChave ( chaveElemento, bitsRelevantes );

       if ( entradaParaChave > pow ( 2, bitsRelevantes) )
       {
           return TAH_CondRetErro;
       }

       pListaTabelaHash = pTabelaHash->pListaTabelaHash;

       IrInicioLista(pListaTabelaHash);
       LIS_AvancarElementoCorrente( pListaTabelaHash, entradaParaChave );
       
       elementoTabela = ( tpElemTabela * ) LIS_ObterValor( pListaTabelaHash );
       if ( elementoTabela == NULL )
       {
           return TAH_CondRetErro;
       }

       bucketParaInserir = elementoTabela->pBucket;
       if ( bucketParaInserir == NULL )
       {
           return TAH_CondRetErro;
       }

       tamanhoMaximoBucket = BUC_ObterTamanhoMaximoBucket();

       tamanhoBucket = BUC_ObterNumElementosBucket( bucketParaInserir );

       bucketElemenValue = BUC_BuscarChaveNoBucket(chaveElemento, bucketParaInserir );
       if( bucketElemenValue != NULL)
       {
           //elemento já inserido
           return TAH_CondRetOK;
       }

       if ( tamanhoBucket < tamanhoMaximoBucket )
       {
           BUC_tpCondRet bucCondRetAux;

           BUC_BuscarChaveNoBucket(chaveElemento, bucketParaInserir );
           bucCondRetAux = BUC_InserirEmBucket( chaveElemento, pValor, bucketParaInserir );
           if ( bucCondRetAux == BUC_CondRetOK )
           {
               TAH_ConsistirElementosTabela(pTabelaHash);
               // unica saida boa
               return TAH_CondRetOK;
           }
           else if ( bucCondRetAux == BUC_CondRetElementoInserido )
           {
               return TAH_CondRetElementoInserido; 
           }
           else
           {
               return TAH_CondRetErro;
           }
       }
       else if ( tamanhoBucket == tamanhoMaximoBucket )
       {
           int bitsRelevantesBucketInserir, idBucketInserir;

           bitsRelevantesBucketInserir = BUC_ObterBucketSensitiveBits( bucketParaInserir );
           idBucketInserir = BUC_ObterBucketID( bucketParaInserir );
           
           if ( bitsRelevantesBucketInserir > bitsRelevantes )
           {
               return TAH_CondRetErro;
           }
           else if( bitsRelevantesBucketInserir < bitsRelevantes )
           {
               BUC_tppBucket novoBucket;
               LIS_tppLista elementosIrmaos;
               BUC_tpCondRet bucketCondRetAux;
               int novoBucketId;
               tpElemTabela * elementoAlterar;

               novoBucketId = BUC_ObterIdDistinto( bucketParaInserir, entradaParaChave ,bitsRelevantes );

               if ( novoBucketId == 0xFFFFFFFF )
               {
                   int antigoBucketSensibilidade;
                   
                   antigoBucketSensibilidade = BUC_ObterBucketSensitiveBits( bucketParaInserir );
                   antigoBucketSensibilidade++;
                   BUC_DefinirBucketSensitiveBits( bucketParaInserir, antigoBucketSensibilidade );
               }

               IrInicioLista(pListaTabelaHash);
               LIS_AvancarElementoCorrente(pListaTabelaHash, novoBucketId);
               elementoAlterar = LIS_ObterValor(pListaTabelaHash);

               novoBucket = BUC_CriarBucket(bitsRelevantes, novoBucketId, pTabelaHash->ExcluirValor );
               if ( novoBucket == NULL )
               {
                   return TAH_CondRetErro;
               }

               elementoAlterar->pBucket = novoBucket;

               elementosIrmaos = BUC_BuscarElementosIrmaos( bitsRelevantes, novoBucketId, bucketParaInserir );

               if( elementosIrmaos == NULL )
               {
                   return TAH_CondRetErro;
               }

               bucketCondRetAux = BUC_MigrarBuckets( novoBucket, bucketParaInserir, elementosIrmaos );
               if ( bucketCondRetAux != BUC_CondRetOK )
               {
                   return TAH_CondRetErro;
               }
               
               return TAH_InserirEmTabelaHash( pTabelaHash, strChaveElemento, pValor );
           }
           else
           {
               int preCond, posCond, inxAuxCriacaoBuckets , verificadorBucket;

               preCond = pow( 2, bitsRelevantes );
               posCond = pow( 2, bitsRelevantes + 1);

               for (inxAuxCriacaoBuckets = preCond; inxAuxCriacaoBuckets < posCond; inxAuxCriacaoBuckets++ )
               {
                   LIS_tpCondRet condRetListaAux;
                   unsigned int currNewElemOldKey ;
                   tpElemTabela * entradaReferente, * novaEntrada;

                   currNewElemOldKey = TAH_ObterEntradaParaChave(inxAuxCriacaoBuckets,bitsRelevantes);
                   
                   IrInicioLista(pListaTabelaHash);
                   LIS_AvancarElementoCorrente( pListaTabelaHash, currNewElemOldKey );
                   entradaReferente = LIS_ObterValor( pListaTabelaHash );
                   if ( entradaReferente == NULL )
                   {
                       return TAH_CondRetErro;
                   }

                   novaEntrada = ( tpElemTabela * ) malloc ( sizeof( tpElemTabela ) );
                   novaEntrada->idEntrada = inxAuxCriacaoBuckets;
                   novaEntrada->pBucket = entradaReferente->pBucket;                   

                   IrFinalLista(pListaTabelaHash);
                   condRetListaAux = LIS_InserirElementoApos( pListaTabelaHash, novaEntrada );

                   if ( condRetListaAux != LIS_CondRetOK )
                   {
                       return TAH_CondRetErro;
                   }
               }

               bitsRelevantes++;

               pTabelaHash->TabelaBitsRelevantes = bitsRelevantes;

               verificadorBucket = BUC_ObterDistincao( bucketParaInserir, chaveElemento, bitsRelevantes );
               if ( verificadorBucket == 0 )
               {
                   BUC_DefinirBucketSensitiveBits( bucketParaInserir, bitsRelevantes );
               }

               return TAH_InserirEmTabelaHash( pTabelaHash, strChaveElemento, pValor );
           }
        }
    }

/***************************************************************************
*
*  Função: TAH &Buscar em Tabela Hash
*  ****/

    void * TAH_BuscarEmTabelaHash ( TAH_tppTabelaHash pTabelaHash, char * strChaveElemento )
    {
        unsigned int chaveElemento, entradaParaChave;
        int bitsRelevantes;
        LIS_tppLista pListaTabelaHash;
        BUC_tppBucket bucketParaBuscar;
        tpElemTabela * elementoTabela;

        if ( pTabelaHash == NULL )
        {
           return NULL;
        }

        chaveElemento = ObterChave( pTabelaHash, strChaveElemento );

        bitsRelevantes = pTabelaHash->TabelaBitsRelevantes;

        entradaParaChave = TAH_ObterEntradaParaChave ( chaveElemento, bitsRelevantes );

        if ( entradaParaChave > pow ( 2, bitsRelevantes) )
        {
           return NULL;
        }

        pListaTabelaHash = pTabelaHash->pListaTabelaHash;

        IrInicioLista(pListaTabelaHash);
        LIS_AvancarElementoCorrente( pListaTabelaHash, entradaParaChave );

        elementoTabela = ( tpElemTabela * ) LIS_ObterValor( pListaTabelaHash );
        if ( elementoTabela == NULL )
        {
           return NULL;
        }

        bucketParaBuscar = elementoTabela->pBucket;
        if ( bucketParaBuscar == NULL )
        {
           return NULL;
        }

        return BUC_BuscarChaveNoBucket(chaveElemento, bucketParaBuscar);
    }

/***************************************************************************
*
*  Função: TAH &Excluir em Tabela Hash
*  ****/

    TAH_tpCondRet TAH_ExcluirEmTabelaHash ( TAH_tppTabelaHash pTabelaHash, char * strChaveElemento )
    {
        unsigned int chaveElemento, entradaParaChave;
        int bitsRelevantes, numElemBucketAposExclusao;
        unsigned int bucketIdMaisAlto, menorElementoTabelaRelevante, maiorElementoTabelaRelevante, inxAux;
        BUC_tpCondRet bucketCondRetAux;
        LIS_tppLista pListaTabelaHash;
        BUC_tppBucket bucketParaRemoverElem;
        tpElemTabela * elementoTabela;

        if ( pTabelaHash == NULL )
        {
           return TAH_CondRetErro;
        }

        chaveElemento = ObterChave( pTabelaHash, strChaveElemento );

        bitsRelevantes = pTabelaHash->TabelaBitsRelevantes;

        entradaParaChave = TAH_ObterEntradaParaChave ( chaveElemento, bitsRelevantes );

        if ( entradaParaChave > pow ( 2, bitsRelevantes) )
        {
           return TAH_CondRetErro;
        }

        pListaTabelaHash = pTabelaHash->pListaTabelaHash;

        IrInicioLista(pListaTabelaHash);
        LIS_AvancarElementoCorrente( pListaTabelaHash, entradaParaChave );

        elementoTabela = ( tpElemTabela * ) LIS_ObterValor( pListaTabelaHash );
        if ( elementoTabela == NULL )
        {
           return TAH_CondRetErro;
        }

        bucketParaRemoverElem = elementoTabela->pBucket;
        if ( bucketParaRemoverElem == NULL )
        {
           return TAH_CondRetErro;
        }

        bucketCondRetAux = BUC_RemoverElementoDoBucket(chaveElemento, bucketParaRemoverElem, 1);
        if ( bucketCondRetAux == BUC_CondRetNaoAchou )
        {
            return TAH_CondRetNaoAchou;
        }
        else if( bucketCondRetAux == BUC_CondRetInvalido )
        {
            return TAH_CondRetErro;
        }

        numElemBucketAposExclusao = BUC_ObterNumElementosBucket(bucketParaRemoverElem);

        //alterar referencia ponteiro de elem tabela c bucket vazio
        if ( numElemBucketAposExclusao == 0 )
        {
            tpElemTabela * elementoTabelaReferente;
            int elementoTabelaReferenteNovoId, inxElemTabela, numElemTabela;
            BUC_tppBucket novoBucketReferente;
            unsigned int oldBucketId, menorBucketId;

            elementoTabelaReferenteNovoId = UTI_AlterarBit( entradaParaChave ,bitsRelevantes - 1 );

            IrInicioLista(pListaTabelaHash);
            LIS_AvancarElementoCorrente( pListaTabelaHash, elementoTabelaReferenteNovoId );

            elementoTabelaReferente = ( tpElemTabela * ) LIS_ObterValor( pListaTabelaHash );

            novoBucketReferente = elementoTabelaReferente->pBucket;
            
            numElemTabela = LIS_ObterNumElem( pListaTabelaHash );

            oldBucketId = BUC_ObterBucketID(bucketParaRemoverElem);
            menorBucketId = 0xFFFFFFFF;

            IrInicioLista(pListaTabelaHash);
            for( inxElemTabela = 0; inxElemTabela < numElemTabela; inxElemTabela++)
            {
                tpElemTabela * currentElemTabela;
                BUC_tppBucket currentBucket;
                unsigned int currentBucketId;

                currentElemTabela = ( tpElemTabela * ) LIS_ObterValor( pListaTabelaHash );

                currentBucket = currentElemTabela->pBucket;
                currentBucketId = BUC_ObterBucketID(currentBucket);

                if ( currentBucketId == oldBucketId )
                {
                    currentElemTabela->pBucket = novoBucketReferente;
                }
                if ( currentBucketId < menorBucketId )
                {
                    menorBucketId = currentBucketId;
                }
                LIS_AvancarElementoCorrente( pListaTabelaHash, 1 );
            }

            BUC_DefinirBucketID(novoBucketReferente,menorBucketId);
            BUC_ExcluirBucket( bucketParaRemoverElem );

            TAH_ConsistirElementosTabela(pTabelaHash);
        }

        //merge
        bucketIdMaisAlto = 0;
        menorElementoTabelaRelevante = pow(2,bitsRelevantes -1);
        maiorElementoTabelaRelevante = pow(2,bitsRelevantes);

        for( inxAux = menorElementoTabelaRelevante; inxAux < maiorElementoTabelaRelevante; inxAux++ )
        {
            unsigned int currId;
            tpElemTabela * currElementoTabela;
            BUC_tppBucket currElemBucket;
            
            IrInicioLista(pListaTabelaHash);
            LIS_AvancarElementoCorrente( pListaTabelaHash, inxAux );
            currElementoTabela =( tpElemTabela * ) LIS_ObterValor( pListaTabelaHash );
            currElemBucket = currElementoTabela->pBucket;

            currId = BUC_ObterBucketID( currElemBucket );

            if( currId >  bucketIdMaisAlto )
            {
                bucketIdMaisAlto = currId;
            }
        }

        menorElementoTabelaRelevante = pow(2,pTabelaHash->TabelaBitsRelevantes - 1);
        maiorElementoTabelaRelevante = pow(2,pTabelaHash->TabelaBitsRelevantes);

        while ( bucketIdMaisAlto < menorElementoTabelaRelevante)
        {


            for ( inxAux = menorElementoTabelaRelevante; inxAux < maiorElementoTabelaRelevante; inxAux++ )
            {
                tpElemTabela * currElementoTabelaAux;
                int idEntrada;


                IrFinalLista( pListaTabelaHash );
                currElementoTabelaAux =( tpElemTabela * ) LIS_ObterValor( pListaTabelaHash );
                idEntrada = currElementoTabelaAux->idEntrada;
                LIS_ExcluirElemento( pListaTabelaHash );

            }

            pTabelaHash->TabelaBitsRelevantes = pTabelaHash->TabelaBitsRelevantes - 1;

            menorElementoTabelaRelevante = pow(2,pTabelaHash->TabelaBitsRelevantes - 1);
            maiorElementoTabelaRelevante = pow(2,pTabelaHash->TabelaBitsRelevantes);
        }
        return TAH_CondRetOK;

    }

/***************************************************************************
*
*  Função: BUC &Imprimir Tabela de Hash
*  ****/

    void TAH_ImprimirTabelaHash( TAH_tppTabelaHash pTabelaHash )
    {
        LIS_tppLista elementosTabela;
        int inxAuxPrint, numElem, bitsRelevantesTabela;

        printf("&&&&&&&& Tebela Hash &&&&&&&&\n" );

        elementosTabela = pTabelaHash->pListaTabelaHash;
        bitsRelevantesTabela = pTabelaHash->TabelaBitsRelevantes;

        numElem = LIS_ObterNumElem(elementosTabela);
        printf("&&&&&&&& %d Entradas &&&&&&&&\n\n", numElem );
        printf("&&&&&&&& %d Bits relevantes &&&&&&&&\n\n", bitsRelevantesTabela );
        IrInicioLista( elementosTabela );
        for ( inxAuxPrint = 0; inxAuxPrint < numElem; inxAuxPrint++ )
        {
            tpElemTabela * currElemTabela;

            currElemTabela = LIS_ObterValor(elementosTabela);
            printf("@@@@Elemento Tabela ID: %d\n",currElemTabela->idEntrada);
            BUC_ImprimirBucket(currElemTabela->pBucket);
            LIS_AvancarElementoCorrente(elementosTabela, 1);
        }
    }

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TAH  -Obter chave
*
*  $ED Descrição da função
*     Obtem chave a apartir de função de hash.
*
***********************************************************************/

   unsigned int ObterChave( TAH_tppTabelaHash pTabelaHash, char * strChave )
   {

      if (( pTabelaHash != NULL )  
          && ( pTabelaHash->HashFunction != NULL ))
      {
         return pTabelaHash->HashFunction( strChave ) ;
      } /* if */

      return -1;

   } /* Fim função: TAH  -Obter chave a partir de função */

/***********************************************************************
*
*  $FC Função: TAH  -Liberar entrada da tabela de hash
*
*  $ED Descrição da função
*     Exclui elemento da tabela de hash.
*
***********************************************************************/

   void LiberarElementoTabela( tpElemTabela * pElemTabela )
   {
        free(pElemTabela);
   } /* Fim função: TAH  -Liberar elemento da tabela */

/***************************************************************************
*
*  Função: TAH &Criar elemento tabela
*  ****/

   tpElemTabela * TAH_CriarEntradaTabelaHash( unsigned int idEntrada, BUC_tppBucket pBucket )
   {

       tpElemTabela * entradaTabela;

       entradaTabela = ( tpElemTabela * ) malloc ( sizeof ( tpElemTabela ) );
       if ( entradaTabela == NULL )
       {
           return NULL;
       }

       entradaTabela->idEntrada = idEntrada;
       entradaTabela->pBucket = pBucket;

       return entradaTabela;

   }

/***************************************************************************
*
*  Função: TAH &Definir bucket entrada
*  ****/

   void * TAH_DefinirBucketDeEntrada( tpElemTabela * entradaTabela, BUC_tppBucket pBucket )
   {
       entradaTabela->pBucket = pBucket;
   }

/***************************************************************************
*
*  Função: TAH &Obter id da entrada
*  ****/

   int TAH_ObterIdEntrada( tpElemTabela * entradaTabela )
   {
       return entradaTabela->idEntrada;
   }

/***************************************************************************
*
*  Função: TAH &Obter id da entrada
*  ****/

   unsigned int TAH_ObterEntradaParaChave( unsigned int  chaveElemento, int bitsRelevantes )
   {
       unsigned int comparadorChave, resultComparaChave;
       comparadorChave = UTI_ConstruirComparadorSequencial( bitsRelevantes );
       resultComparaChave = chaveElemento & comparadorChave;

       return resultComparaChave;
   }

/***************************************************************************
*
*  Função: TAH &Consistir elementos Tabela
*  ****/

   void TAH_ConsistirElementosTabela( TAH_tppTabelaHash pTabelaHash )
   {
       LIS_tppLista pListaTabelaHash;
       int numElemTabela, inxAux, minimoBucketBitsSensiveis;

       pListaTabelaHash = pTabelaHash->pListaTabelaHash;

       numElemTabela = LIS_ObterNumElem(pListaTabelaHash);
	   
	   minimoBucketBitsSensiveis = pTabelaHash->TabelaBitsRelevantes;

       for ( inxAux = 0; inxAux < numElemTabela; inxAux++)
       {
           BUC_tppBucket currBucket;
           tpElemTabela * currElemTabela;
           int bucketID, elemTabelaId, bucketBitsSensiveis, tabelaBucketSensiveis, resultComp;

           IrInicioLista(pListaTabelaHash);
           LIS_AvancarElementoCorrente( pListaTabelaHash, inxAux);        

           currElemTabela = (tpElemTabela *) LIS_ObterValor(pListaTabelaHash);
           currBucket = currElemTabela->pBucket;

           tabelaBucketSensiveis = pTabelaHash->TabelaBitsRelevantes;
           bucketBitsSensiveis = tabelaBucketSensiveis;

           bucketID = BUC_ObterBucketID( currBucket );
           elemTabelaId = currElemTabela->idEntrada;
 
           do
           {
                resultComp = UTI_CompararFaixaDeBitsInt(bucketID,elemTabelaId,0, bucketBitsSensiveis );
                if( resultComp != 0 )
                {
                    bucketBitsSensiveis--;
                }
           }
           while(resultComp != 0);

           BUC_DefinirBucketSensitiveBits( currBucket, bucketBitsSensiveis );
       }

       return;
   }

/********** Fim do módulo de implementação: TAH  Tabela de Hash Expansível **********/

