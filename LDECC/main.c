#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "LDECC.h"

int main()
{
    int opcao, valor, maximo, novo_valor, retorno_busca = 0, classif, permite_repet, retorno_insert = 0, retorno_delete = 0, retorno_qtdnos = 0, retorno_change = 0, retorno_print = 0, inicializacao = -1;
    tLDECC* lista = NULL;

    do {
        printf("\nDeseja criar a lista classificada (1) ou nao classificada (0)? ");
        scanf("%d", &classif);

        printf("Deseja permitir repeticao de valores (1) ou nao (0)? ");
        scanf("%d", &permite_repet);

        printf("Qual será o tamanho máximo reservado para sua lista?");
        scanf("%d", &maximo);

        if (((classif == 1) || (classif == 0)) && ((permite_repet == 1) || (permite_repet == 0))) {
            lista = lstLDECC_create(classif, permite_repet, maximo);

            printf("1 - Inserir valor.\n2 - Buscar valor.\n3 - Alterar valor.\n4 - Deletar valor.\n5 - Imprimir lista.\n6 - Verificar quantidade de nós.\n7 - Encerrar programa.\n");

            do {
                printf("\nEscolha uma acao:  ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        printf("Inserir valor:  ");
                        scanf("%d", &valor);
                        retorno_insert = lstLDECC_insert(lista, valor);
                        if (retorno_insert == 0) {
                            printf("\nValor %d inserido corretamente\n", valor);
                        } else {
                            printf("\nFalha na insercao do valor %d\n", valor);
                        }
                        break;

                    case 2:
                        printf("Buscar valor:  ");
                        scanf("%d", &valor);
                        retorno_busca = lstLDECC_search(lista, valor);
                        if (retorno_busca == -1) {
                            printf("\nValor nao encontrado!\n");
                        } else {
                            printf("\nValor encontrado %d vezes na lista!\n", retorno_busca);
                        }
                        break;

                    case 3:
                        printf("Alterar valor:  ");
                        scanf("%d", &valor);
                        printf("\nNovo valor:  ");
                        scanf("%d", &novo_valor);
                        retorno_change = lstLDECC_changeValue(lista, valor, novo_valor);
                      if(retorno_change==(-1))
                      {
                        printf("Valor a ser alterado nao encontrado na lista");
                      }
                      if(retorno_change==(-2))
                      {
                        printf("Erro na consulta à lista");
                      }
                      break;

                    case 4:
                        printf("Deletar valor:  ");
                        scanf("%d", &valor);
                        retorno_delete = lstLDECC_deleteNode(lista, valor);
                        if (retorno_delete == -1) {
                            printf("\nValor %d nao encontrado\n", valor);
                        } else {
                            printf("\nValor %d removido %d vezes\n", valor, retorno_delete);
                        }
                        break;

                    case 5:
                        retorno_print = lstLDECC_printList(lista);
                        if(retorno_print==-1)
                        {
                          printf("Lista vazia");
                        }
                        break;

                  case 6:
                        retorno_qtdnos = lstLDECC_verificarQtdNos(lista);
                        if(retorno_qtdnos==0)
                        {
                          printf("Lista vazia.");
                        }
                        else
                        {
                          printf("A lista possui %d nos", retorno_qtdnos);
                        }
                        break;
                        
                    case 7:
                        printf("Encerrando o programa...");
                        lstLDECC_freeList(lista);
                        break;

                    default:
                        printf("Opcao invalida!");
                        break;
                }
            } while (opcao != 7);
    inicializacao=0;
    return 0;
    }
    else
  {
    printf("\nInicializacao incorreta. Reiniciar programa?\nDigite (QUALQUER NUMERO) para continuar.\nDigite (0) para sair.\n");
    scanf("%d", &inicializacao);
  }
}while(inicializacao!=0);
}