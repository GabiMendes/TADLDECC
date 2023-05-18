//Código desenvolvido por Gabriela Marques Mendes

//Inclusão de bibliotecas necessárias
#include "LDECC.h"
#include <stdio.h>
#include <stdlib.h>

//Tipagem do nó, struct nó
struct Node {
    int valor;
    struct Node* prox;
    struct Node* ant;
};

//Tipagem da lista, struct lista
struct LDECC {
  tNode* no_cabeca;
  int qtdNos;
  int isClassif, comRepet;
  int maximo;
};

//O uso de funções auxiliares foi pensado em função da organização do código para demais programadores. O uso de funções auxiliares torna o código mais modular, o que também o torna mais fácil para percepção de erros e posteriores refatorações, caso sejam necessárias.

//O uso do nó cabeça permitiu que o "struct Node" fosse o suficiente, sem necessitar do "struct LISTA" (armazenando primeiro e último nós; quantidade de nós e se é classificada ou não) para manipulação da lista.

//==================================================================

/*FUNÇÕES AUXILIARES*/

//Função auxiliar dedicada à inserção de elementos na lista. Utilizada em casos de lista Classificada. Retorna se inserção ordenada foi bem sucedida ou não.
int insertInOrder(tLDECC* pL, int valorfuncao) {
    tNode* newNode = malloc(sizeof(tNode));

    if (newNode == NULL) {
        return -1; // erro na alocação de memória
    }

    newNode->valor = valorfuncao;

    // busca o local correto para inserir o novo nó
    tNode* no_parametro = pL->no_cabeca->prox;
    while (no_parametro != pL->no_cabeca && no_parametro->valor < valorfuncao) {
        no_parametro = no_parametro->prox;
    }

    // insere o novo nó na posição correta
    newNode->prox = no_parametro;
    newNode->ant = no_parametro->ant;
    no_parametro->ant->prox = newNode;
    no_parametro->ant = newNode;

    pL->qtdNos++; // incrementa a quantidade de nós

    return 0;
}


//Função auxiliar dedicada à alteração de elementos na lista. Utilizada em casos de lista Não Classificada.
void changeValueNoClassif(tLDECC* pL, int valorAntigo, int valorNovo){
  int contador=0; 
  tNode* no_parametro = pL->no_cabeca->prox;

    while (no_parametro != pL->no_cabeca) {  //Enquanto atual não for igual ao nó cabeça
  if (no_parametro->valor == valorAntigo) {  //Se o valor do atual for igual ao do antigo
      no_parametro->valor = valorNovo;  //Atual recebe novo (substituição simples)
      contador=1;  //Contador simplificado é atualizado
  }
  no_parametro = no_parametro->prox;  //Se o valor atual não for igual ao ser substituído, lista continua a ser percorrida
  }
  if(contador==1)
  {
  changeValueNoClassif(pL, no_parametro->valor, valorNovo);
  }
  else
  {
    return;
  }
}


//Função auxiliar dedicada à alteração na lista. Utilizada em casos de lista Claasificada.
void changeValueClassif(tLDECC* pL, int valorAntigo, int valorNovo)
{
  tNode* no_parametro = pL->no_cabeca->prox;
  int contador=0;
  
  if (valorAntigo == valorNovo) {
        return; // não faz nada se o valor antigo e novo forem iguais
    }

    // busca o nó com o valor antigo
    while (no_parametro != pL->no_cabeca && no_parametro->valor != valorAntigo) {
        no_parametro = no_parametro->prox;
    }

    if (no_parametro != pL->no_cabeca)
    {
      // remove o nó com o valor antigo
    no_parametro->ant->prox = no_parametro->prox;
    no_parametro->prox->ant = no_parametro->ant;
    free(no_parametro);

    //insere o novo valor em ordem
    insertInOrder(pL, valorNovo);

    contador=1;

    if((contador)==1)
    {
      changeValueClassif(pL, valorAntigo, valorNovo);
    }
  } 
}

//==================================================================

/*FUNÇÕES PRINCIPAIS*/

//Função dedicada a verificar se lista é classificada ou não. Retorna 1 se for classificada e 0 se não for.
int lstLDECC_isClassif(tLDECC* pL)
{
  return pL->isClassif;
}

//Função dedicada a verificar se lista possui repetição ou não. Retorna 1se possuir e 0 se não possuir.
int lstLDECC_comRepet(tLDECC* pL){
  return pL->comRepet;
}

//Função dedicada a verificar qtd de nós da lista. Retorna quantidade de nós se possuir e 0 se não possuir.
int lstLDECC_verificarQtdNos(tLDECC* pL)
{
  return pL->qtdNos;
}

//Função dedidaca a verificar se lista está cheia ou não. Retorno 1 se estiver, retorna 0 se não estiver.
int lstLDECC_isFull(tLDECC* pL)
{
  return pL->qtdNos==pL->maximo;
}

//Função dedicada à verificação se lista está vazia. Retorna 1 se não estiver vazia e 0 se estiver vazia.
int lstLDECC_isEmpty(tLDECC* pL){
    if (pL->no_cabeca->prox == pL->no_cabeca) {
        return 0; // lista vazia
    } else {
        return 1; // lista não vazia
    }
}

//Função dedicada à criação de listas. Retorna nó cabeça (ou bobo, como preferir) que será ferramenta para manipulação da lista
tLDECC* lstLDECC_create(int Classif, int Repet, int maximo) {
    tLDECC* pL = malloc(sizeof(tLDECC));
    pL->no_cabeca = malloc(sizeof(tNode));
    pL->no_cabeca->valor = -1;
    pL->no_cabeca->prox = pL->no_cabeca;
    pL->no_cabeca->ant = pL->no_cabeca;
    pL->qtdNos = 0;
    pL->isClassif = Classif;
    pL->comRepet = Repet;
    pL->maximo = maximo;
  
    return pL;
}


//Função dedicada à inserção de elementos na lista de acordo com os parâmetros "classif" e "repet" fornecidos. Retorna se elemento foi inserido adequadamente ou não.
int lstLDECC_insert(tLDECC* pL, int valorfuncao){
struct Node* newNode = malloc(sizeof(struct Node));
  int retorno_insertInOrder = 0;
    if ((pL->comRepet) == 0 && (lstLDECC_search(pL, valorfuncao) != 0)) {
        return -1; // não insere elementos repetidos
    }

    if(lstLDECC_isFull(pL))
    {
      return -1; // não insere novos elementos
    }

      if (pL->isClassif) {
        retorno_insertInOrder=insertInOrder(pL, valorfuncao);
//        printf("retorno_insertInOrder %d", retorno_insertInOrder);
        if (retorno_insertInOrder == 0) {
            return 0; // Inserção realizada corretamente
        } else {
            return 12346891; // Falha na inserção. Valor SIMBÓLICO para usuário também poder inserir -1
        }
    }
    
    
    newNode->valor = valorfuncao;
    // insere o novo nó no início da lista
    newNode->prox = pL->no_cabeca->prox;
    newNode->ant = pL->no_cabeca;
    pL->no_cabeca->prox->ant = newNode;
    pL->no_cabeca->prox = newNode;
    
    // se a lista era vazia, o novo nó passa a ser o último
    if (newNode->prox == pL->no_cabeca) {
        pL->no_cabeca->prox->prox = pL->no_cabeca;
        pL->no_cabeca->ant = newNode;
    }
  pL->qtdNos=pL->qtdNos+1;
  return 0;
}


//Função dedicada à remoção de elementos da lista. Retorna a quantidade de vezes que elemento foi removido da lista.
int lstLDECC_deleteNode(tLDECC* pL, int valorfuncao){
    tNode* no_parametro = pL->no_cabeca->prox;
    struct Node* temp;
    int found = 0, qtddelet = 0;
    
    while (no_parametro != pL->no_cabeca) {
        if (no_parametro->valor == valorfuncao) {
            no_parametro->ant->prox = no_parametro->prox;
            no_parametro->prox->ant = no_parametro->ant;
            temp = no_parametro;
            no_parametro = no_parametro->prox;
            free(temp);
            found = 1;
            qtddelet++;
        }
        else {
            no_parametro = no_parametro->prox;
        }
    }

    if (found == 1) {
        pL->qtdNos=pL->qtdNos-1;
        return qtddelet;
    }
    else {
        return -1;
    }
}


//Função principal dedicada à alteração de elementos na lista. Irá definir, a partir da classificação da lista, como serão alterados os elementos (mantendo a ordenação proposta).
int lstLDECC_changeValue(tLDECC* pL, int valorAntigo, int valorNovo){
  tNode* no_parametro = pL->no_cabeca->prox;

    if (!lstLDECC_search(pL, valorAntigo)) {
        return -1;  //Valor não encontrado
    }

  if (pL == NULL) {
        return -2; // Lista não existe
    }

  if((pL->comRepet)==0)
  {
     while (no_parametro != pL->no_cabeca) {
                if (no_parametro->valor == valorNovo) {
                    printf("Erro: Novo valor já existe na lista!\n");
                    return;
                }
                no_parametro = no_parametro->prox;
            }
  }
  
  if ((pL->isClassif)==1)
  {
    changeValueClassif(pL, valorAntigo, valorNovo);
  }
  else
  {
    if((pL->isClassif)==0)
    {
      changeValueNoClassif(pL, valorAntigo, valorNovo);
    }
  }
}


//Função dedicada à "liberar" lista e reservada, nesse contexto, para o encerramento do programa. Poderia ser utilizada para outros fins.
void lstLDECC_freeList(tLDECC* pL){
    struct Node* no_parametro = pL->no_cabeca->prox;
    while (no_parametro != pL->no_cabeca) {
        struct Node* prox = no_parametro->prox;
        free(no_parametro);
        no_parametro = prox;
    }
    free(pL->no_cabeca);
}


//Função dedicada à exibição de elementos da lista um por um.
int lstLDECC_printList(tLDECC* pL){
    if (pL->no_cabeca->prox == pL->no_cabeca) {
        return -1;
    }
    
    struct Node* no_parametro = pL->no_cabeca->prox;

    while (no_parametro != pL->no_cabeca) {
        printf("\n\n");
        printf("Valor: %d\n", no_parametro->valor);
        printf("Valor anterior: %d\n", no_parametro->ant->valor);
        printf("Valor posterior: %d\n", no_parametro->prox->valor);
        no_parametro = no_parametro->prox;
    }
    printf("\n");
}


//Função dedicada à busca de elementos em uma lista de acordo com o nó cabeça (ou bobo) e a chave fornecida. Retorna a quantidade de vezes que o elemento chave foi encontrado.
int lstLDECC_search(tLDECC* pL, int valorfuncao)
{
    tNode* no_parametro = pL->no_cabeca->prox;
    int quantidade = 0;

    while (no_parametro != pL->no_cabeca) {
        if (no_parametro->valor == valorfuncao) {
            quantidade++;
        }
        no_parametro = no_parametro->prox;
    }

    return quantidade;
}