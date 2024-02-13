#ifndef BST_H
#define BST_H

typedef struct jogadores {
	char nome[25];
	char posicao[20];
	char nacionalidade[20];
	int idade;
	int numero;
} dado;

typedef struct indice {
	int chave;
	int indice;
} tipo_dado;

typedef struct no_bst {
	tipo_dado *dado;
	struct no_bst *esq, *dir;
} no_bst;

typedef no_bst * arvore;

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef struct indicerb {
	char chave [25];
	int indice;
} tipo_dadorb;

typedef struct no_rb {
	tipo_dadorb *dado;
	enum cor cor;
	struct no_rb *esq, *dir, *pai;
} no_rb;

typedef no_rb * arvorerb;


typedef struct tabela {
	FILE *arquivo_dados;
	arvore indices;
	arvorerb indicerb;
} tabela;



int inicializarTabela(tabela *tab);
void finalizar (tabela *tab);
void adicionarJogador(tabela *tab, dado *livro);
	

void inicializar(arvore *raiz);
void inicializarRb(arvorerb *raiz);
arvore adicionar (tipo_dado *valor, arvore raiz);

int altura(arvore raiz);
int maior(int a, int b);
tipo_dado * maior_elemento(arvore raiz);
tipo_dado * menor_elemento(arvore raiz);
void pre_order(arvore raiz, tabela *tab);
void pos_order(arvore raiz, tabela *tab);
void in_order(arvore raiz, tabela *tab);
arvore remover (int valor, arvore raiz);
void imprimir_elemento(arvore raiz, tabela *tab);
dado * ler_dados();
void tirar_enter(char *string);

void salvar_arquivo(char *nome, arvore a);
void salvar_auxiliar(arvore raiz, FILE *arq);
arvore carregar_arquivo(char *nome, arvore a);
void imprimirElementoPorChave(arvore raiz, tabela *tab, int chaveBuscado);
arvore buscarElementoPorChave(arvore raiz, int chave);

int remover_jogador(tabela * tab, int numero);

void salvar_arquivoRb(char *nome, arvorerb a);
void salvar_auxiliarRb(arvorerb raiz, FILE *arq);
arvorerb carregar_arquivoRb(char *nome, arvorerb a);
void imprimir_elementoRbtabela(arvorerb raiz, tabela * tab);
void adicionarRb( tipo_dadorb *valor, arvorerb *raiz);
tipo_dadorb * maior_elementoRb(arvorerb raiz);
void pre_orderRb(arvorerb raiz, tabela *tab);
void pos_orderRb(arvorerb raiz, tabela *tab);
void in_orderRb(arvorerb raiz, tabela *tab);
void imprimir_elementoRb(arvorerb raiz);
arvorerb removerRb (char *valor, arvorerb *raiz);

void ajustar(arvorerb *raiz, arvorerb elemento);
void reajustar(arvorerb *raiz, arvorerb elemento);
void rotacao_simples_direita(arvorerb *raiz, arvorerb pivo);
void rotacao_simples_esquerda(arvorerb *raiz, arvorerb pivo);
void rotacao_dupla_direita(arvorerb *raiz, arvorerb pivo);
void rotacao_dupla_esquerda(arvorerb *raiz, arvorerb pivo);


enum cor cor(arvorerb elemento);
int eh_raiz(arvorerb elemento);
int eh_filho_esquerdo(arvorerb elemento);
int eh_filho_direito(arvorerb elemento);
arvorerb irmao(arvorerb elemento);
arvorerb tio(arvorerb elemento);
void retira_duplo_preto(arvorerb *raiz, arvorerb elemento);


#endif