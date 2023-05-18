//Código desenvolvido por Gabriela Marques Mendes

//Tipagem do nó, struct nó
typedef struct Node tNode;

//Tipagem da lista, struct lista
typedef struct LDECC tLDECC;

//O uso de funções auxiliares foi pensado em função da organização do código para demais programadores. O uso de funções auxiliares torna o código mais modular, o que também o torna mais fácil para percepção de erros e posteriores refatorações, caso sejam necessárias.

//==================================================================

/*FUNÇÕES AUXILIARES*/

//Função auxiliar dedicada à inserção de elementos na lista. Utilizada em casos de lista Classificada. Retorna se inserção ordenada foi bem sucedida ou não.
int insertInOrder(tLDECC* pL, int valorfuncao);

//Função auxiliar dedicada à alteração de eleementos na lista. Utilizada em casos de lista Claasificada. 
//FUNÇÃO DO TIPO VOID, NÃO HÁ RETORNO.
void changeValueClassif(tLDECC* pL, int valorAntigo, int valorNovo);

//Função auxiliar dedicada à alteração de elementos na lista. Utilizada em casos de lista Não Classificada.
//FUNÇÃO DO TIPO VOID, NÃO HÁ RETORNO.
void changeValueNoClassif(tLDECC* pL, int valorAntigo, int valorNovo);

//==================================================================

/*FUNÇÕES PRINCIPAIS*/

//Função dedicada à verificar se lista é classificada ou não. Retorna 1 se for classificada e 0 se não for.
int lstLDECC_isClassif(tLDECC* pL);

//Função dedicada à verificar se lista possui repetição ou não. Retorna 1se possuir e 0 se não possuir.
int lstLDECC_comRepet(tLDECC* pL);

//Função dedicada à verificar qtd de nós da lista. Retorna quantidade de nós.
int lstLDECC_verificarQtdNos(tLDECC* pL);

//Função dedidaca a verificar se lista está cheia ou não. Retorno 1 se estiver, retorna 0 se não estiver.
int lstLDECC_isFull(tLDECC* pL);

//Função dedicada à verificação se lista está vazia. Retorna 1 se não estiver vazia e 0 se estiver vazia.
int lstLDECC_isEmpty(tLDECC* pL);

//Função dedicada à criação de listas. Retorna nó cabeça (ou bobo, como preferir) que será ferramenta para manipulação da lista. Importante associá-la a uma estrutura de nó sentinela em seu programa principal.
tLDECC* lstLDECC_create(int Classif, int Repet, int maximo);

//Função dedicada à inserção de elementos na lista de acordo com os parâmetros "classif" e "repet" fornecidos. Retorna se elemento foi inserido adequadamente ou não.
int lstLDECC_insert(tLDECC* pL, int valorfuncao);

//Função dedicada à remoção de elementos da lista. Retorna a quantidade de vezes que elemento foi removido da lista.
int lstLDECC_deleteNode(tLDECC* pL, int valorfuncao);

//Função principal dedicada à alteração de elementos na lista. Irá definir, a partir da classificação da lista, como serão alterados os elementos (mantendo a ordenação proposta). Isto é, caso a lista seja classificada, a função changeValue "puxará" a função "changeValueClassif", caso a lista não seja classificada, a função changeValue "puxará" a função "changeValueNoClassif"
//FUNÇÃO DO TIPO VOID, NÃO HÁ RETORNO.
int lstLDECC_changeValue(tLDECC* pL, int valorAntigo, int valorNovo);

//Função dedicada à liberação da lista e reservada, nesse contexto, para o encerramento do programa. Poderia ser utilizada para outros fins.
//FUNÇÃO DO TIPO VOID, NÃO HÁ RETORNO.
void lstLDECC_freeList(tLDECC* pL);

//Função dedicada à exibição de elementos da lista um por um.
//FUNÇÃO DO TIPO VOID, NÃO HÁ RETORNO.
int lstLDECC_printList(tLDECC* pL);

//Função dedicada à busca de elementos em uma lista de acordo com o nó cabeça (ou bobo) e a chave fornecida. Retorna a quantidade de vezes que o elemento chave foi encontrado.
int lstLDECC_search(tLDECC* pL, int valorfuncao);