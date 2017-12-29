#include<stdio.h>
#include <string.h>

#include "TABELA_HASH.h"

typedef struct tagEstrela {

    char * nome ;
        /* String com nome da estrela */

    char * classe;
        /* String com classe da estrela */

    char * velocidade;
        /* String com velocidade da estrela */

} tpEstrela ;

void excluirEstrela ( tpEstrela * estrela );
unsigned int HashFunction ( char * strChaveElemento );
static FILE * abrirArquivo( const char * nomeArquivo );
int lerEntrada( TAH_tppTabelaHash tabelaHash, char * nomeArquivo  );

int main ( void )
{
    TAH_tppTabelaHash tabelaHash;
    int choice;
    char nomeArquivo[81], chave[81];

    printf("\n\n\n--Tabela Hash para armazenar estrelas--\n\n");

    tabelaHash = TAH_CriarTabelaHash(excluirEstrela, HashFunction);
    while (1)
    {
        printf("\n\n\nOpcoes:\n\n");
        printf("1 - Inserir a partir de arquivo\n");
        printf("2 - Inserir\n");
        printf("3 - Excluir\n");
        printf("4 - Buscar\n");
        printf("5 - Sair\n");
        scanf("%d", &choice);

        switch ( choice )
        {
            TAH_tpCondRet tabHashCondRetAux;
            int condRetInsertAux;

            char * nomeEstrela, * classeEstrela, * velocidadeEstrela;
            tpEstrela * pNovaEstrela, * pEstrelaBusca;

            case 1:
                printf("Nome do arquivo: ");
                scanf("%s", nomeArquivo );
                condRetInsertAux = lerEntrada(tabelaHash, nomeArquivo);
                if ( condRetInsertAux == 1 )
                {
                    return 1;
                }
                TAH_ImprimirTabelaHash(tabelaHash);
                break;

            case 2:
                nomeEstrela = (char *) malloc( sizeof(char) * 80);
                classeEstrela = (char *) malloc( sizeof(char) * 80);
                velocidadeEstrela = (char *) malloc( sizeof(char) * 80);

                printf("Nome da estrela:");
                scanf(" %[^\n]", nomeEstrela );
                printf("Classe da estrela:");
                scanf(" %[^\n]", classeEstrela );
                printf("Velocidade da estrela:");
                scanf("%s", velocidadeEstrela );

                pNovaEstrela = ( tpEstrela * ) malloc( sizeof( tpEstrela ));
            
                pNovaEstrela->nome = nomeEstrela;
                pNovaEstrela->classe = classeEstrela;
                pNovaEstrela->velocidade = velocidadeEstrela;

                tabHashCondRetAux = TAH_InserirEmTabelaHash(tabelaHash,nomeEstrela,pNovaEstrela);
                if ( tabHashCondRetAux == TAH_CondRetErro )
                {
                    printf("Erro ao inserir\n");
                    return 1;
                }
                else if ( tabHashCondRetAux == TAH_CondRetElementoInserido)
                {
                    printf("Aviso: Estrela %s ja esta inserida.\n", nomeEstrela);
                }
                else
                {
                    printf("Estrela %s inserida\n", nomeEstrela);
                }
                TAH_ImprimirTabelaHash(tabelaHash);
                break;

            case 3:
                printf("Nome estrela: ");
                scanf(" %[^\n]", chave );
                tabHashCondRetAux = TAH_ExcluirEmTabelaHash(tabelaHash,chave);
                if ( tabHashCondRetAux == TAH_CondRetNaoAchou )
                {
                    printf("Elemento nao encontrado.\n");
                }
                else if ( tabHashCondRetAux == TAH_CondRetErro)
                {
                    printf("Erro!\n");
                    return 1;
                }
                else
                {
                    printf("Elemento excluido.\n");
                }
                break;

            case 4:
                printf("Nome estrela: ");
                scanf(" %[^\n]", chave );
                pEstrelaBusca = ( tpEstrela * ) TAH_BuscarEmTabelaHash(tabelaHash,chave);
                if ( pEstrelaBusca == NULL )
                {
                    printf("Elemento nao encontrado.\n");
                }
                else
                {
                    printf("Estrela %s encontrada.\n", pEstrelaBusca->nome );
                    printf("Classe da estrela: %s\n",pEstrelaBusca->classe);
                    printf("Velocidade da estrela: %s\n",pEstrelaBusca->velocidade);
                }

                break;
            
            case 5:
                return 0;
            
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
    return 0;
}

FILE * abrirArquivo( const char * nomeArquivo )
{
	    FILE * arquivo;

		arquivo = fopen( nomeArquivo, "rt") ;

		if( arquivo != NULL )
		{
			return arquivo;
		}

		return NULL;

}

void excluirEstrela ( tpEstrela * estrela )
{
    free(estrela->nome);
    free(estrela->classe);
    free(estrela->velocidade);
    free(estrela);
}

unsigned int HashFunction ( char * strChaveElemento )
{
    int inxAux,total=0;
    int modulo;
    unsigned int returnValue;

    modulo = 684476527;


	for ( inxAux=0 ; strChaveElemento[inxAux]!='\0' ; inxAux++) 
    {
		total += strChaveElemento[inxAux]*(inxAux + 1);
	}

	returnValue =  total % 6548447613527;

    printf("Obtendo hash para a chave %s: %u\n", strChaveElemento, returnValue );

    return returnValue;
}

int lerEntrada( TAH_tppTabelaHash tabelaHash, char * nomeArquivo  )
{
    FILE * arquivo;
    char linha[121];
    
    arquivo = abrirArquivo( nomeArquivo );
    if ( arquivo != NULL )
    {
        //le linha a linha arquivo de entrada
        while(fgets(linha,121,arquivo) != NULL )
        {
            char * nomeEstrela, * classeEstrela, * velocidadeEstrela, * strToken;
            tpEstrela * pNovaEstrela;
            TAH_tpCondRet tabHashCondRetAux;

            nomeEstrela = (char *) malloc( sizeof(char) * 80);
            classeEstrela = (char *) malloc( sizeof(char) * 80);
            velocidadeEstrela = (char *) malloc( sizeof(char) * 80);

            strToken = strtok(linha,",");
            if( strToken == NULL )
            {
                printf("Erro ao ler linha do arquivo - nome estrela\n");
                return 1;
            }
            strcpy(nomeEstrela, strToken );

            strToken = strtok(NULL,",");
            if( strToken == NULL )
            {
                printf("Erro ao ler linha do arquivo - classe estrela\n");
                return 1;
            }
            strcpy(classeEstrela, strToken );

            strToken = strtok(NULL,",");
            if( strToken == NULL )
            {
                printf("Erro ao ler linha do arquivo - velocidade estrela\n");
                return 1;
            }
            strcpy(velocidadeEstrela, strToken );

            pNovaEstrela = ( tpEstrela * ) malloc( sizeof( tpEstrela ));
            
            pNovaEstrela->nome = nomeEstrela;
            pNovaEstrela->classe = classeEstrela;
            pNovaEstrela->velocidade = velocidadeEstrela;

            printf("Inserindo estrela %s, classe %s, velocidade %s km\\h.\n", nomeEstrela, classeEstrela, velocidadeEstrela );

            tabHashCondRetAux = TAH_InserirEmTabelaHash(tabelaHash,nomeEstrela,pNovaEstrela);
            if ( tabHashCondRetAux == TAH_CondRetErro )
            {
                printf("Erro ao inserir\n");
                return 1;
            }
            else if ( tabHashCondRetAux == TAH_CondRetElementoInserido)
            {
                printf("Aviso: Estrela %s ja esta inserida.\n", nomeEstrela);
            }
        }

        return 0;
    }//if
    else
    {
        printf("Erro - Arquivo invalido\n");
        return 1;
    }
}
