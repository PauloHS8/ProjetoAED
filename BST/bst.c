#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>


void inicializar(arvore *raiz) {
	*raiz = NULL;
}

int inicializarTabela(tabela *tab) {
	inicializar(&tab->indices);	
	tab->arquivo_dados = fopen("dados.dat", "a+b");
	tab->indices = carregar_arquivo("indices.dat", tab->indices);
	if(tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}

void finalizar (tabela *tab) {
	fclose(tab->arquivo_dados);
	salvar_arquivo("indices.dat", tab->indices);
}

void adicionarLivro(tabela *tab, dado *jogadores){
	if(tab->arquivo_dados != NULL) {
			tipo_dado * novo = (tipo_dado *) malloc(sizeof(tipo_dado));

			novo->chave = jogadores->numero;

			fseek(tab->arquivo_dados, 0L, SEEK_END);
			novo->indice = ftell(tab->arquivo_dados);

			fwrite(jogadores, sizeof(dado), 1, tab->arquivo_dados);
			tab->indices = adicionar(novo, tab->indices);
	}
}


arvore adicionar (tipo_dado *valor, arvore raiz) {
	if(raiz == NULL) {
		arvore novo = (arvore) malloc(sizeof(struct no_bst));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}

	if(valor->chave > raiz->dado->chave) {
		raiz->dir = adicionar(valor, raiz->dir);
	} else {
		raiz->esq = adicionar(valor, raiz->esq);
	}
	return raiz;
}

int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

tipo_dado * maior_elemento(arvore raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

tipo_dado * menor_elemento(arvore raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->esq);
}

void pre_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		imprimir_elemento(raiz, tab);
		pre_order(raiz->esq, tab);
		pre_order(raiz->dir, tab);
	}
}

void pos_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		pos_order(raiz->esq, tab);
		pos_order(raiz->dir, tab);
		imprimir_elemento(raiz, tab);
	}
}

void in_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		in_order(raiz->esq, tab);
		imprimir_elemento(raiz, tab);
		in_order(raiz->dir, tab);
	}
}

void imprimir_elemento(arvore raiz, tabela * tab) {
	dado * temp = (dado *) malloc (sizeof(dado));
    temp->numero = 1000;
    printf("indice: %d\n", raiz->dado->indice);

   	fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
	//
	int r = fread(temp, sizeof(dado), 1, tab->arquivo_dados);

	printf("[%d, %d, %s, %s, %s, %d ]\n", raiz->dado->chave,r, temp->nome, temp->posicao, temp->nacionalidade, temp->idade);
	free(temp);
}

arvore remover (int valor, arvore raiz) {
	if(raiz == NULL) 
		return NULL;
	
	if(raiz->dado->indice == valor) {		
		if(raiz->esq == NULL) {
			return raiz->dir;
		}
		if(raiz->dir == NULL) {
			return raiz->esq;
		}
		raiz->dado = maior_elemento(raiz->esq);
		raiz->esq = remover(raiz->dado->indice, raiz->esq);
		return raiz;
	}	
	if(valor > raiz->dado->indice) {
			raiz->dir = remover(valor, raiz->dir);
	} else {
			raiz->esq = remover(valor, raiz->esq);
	}
	return raiz;
}

dado * ler_dados() {
	dado *novo = (dado *) malloc(sizeof(dado));
	//__fpurge(stdin);
	getchar();
	printf("Nome: ");
	fgets(novo->nome, 25,  stdin);
	tirar_enter(novo->nome);
	printf("Posicao: ");
	fgets(novo->posicao, 20,  stdin);
	tirar_enter(novo->posicao);
	printf("Nacionalidade: ");
	fgets(novo->nacionalidade, 20,  stdin);
	tirar_enter(novo->nacionalidade);
	printf("idade: ");
	scanf("%d", &novo->idade);
	printf("numero: ");
	scanf("%d", &novo->numero);
	return novo;
}

void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}

void salvar_arquivo(char *nome, arvore a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar(arvore raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->esq, arq);
		salvar_auxiliar(raiz->dir, arq);
	}

}

arvore carregar_arquivo(char *nome, arvore a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_dado * temp;
	if(arq != NULL) {
		temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		while(fread(temp, sizeof(tipo_dado), 1, arq)) {
			
			a = adicionar(temp, a);			
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));

		}
		fclose(arq);

	}
	return a;
}

void imprimirElementoPorIndice(arvore raiz, tabela *tab, int indiceBuscado) {
    dado *temp = (dado *)malloc(sizeof(dado));
    temp->numero = 1000;
	
    arvore elemento = buscarElementoPorIndice(raiz, indiceBuscado);

    if (elemento != NULL) {
        printf("indice: %d\n", elemento->dado->indice);

        fseek(tab->arquivo_dados, elemento->dado->indice, SEEK_SET);

        int r = fread(temp, sizeof(dado), 1, tab->arquivo_dados);

        printf("[%d, %d, %s, %s, %s, %d ]\n", elemento->dado->chave, r, temp->nome, temp->posicao, temp->nacionalidade, temp->idade);
    } else {
        printf("Elemento com índice %d não encontrado.\n", indiceBuscado);
    }

    free(temp);
}

arvore buscarElementoPorIndice(arvore raiz, int indice) {
    if (raiz == NULL) {
        return NULL;
    }

    if (indice == raiz->dado->indice) {
        return raiz;
    }
    if (indice < raiz->dado->indice) {
        return buscarElementoPorIndice(raiz->esq, indice);
    } else {
        return buscarElementoPorIndice(raiz->dir, indice);
    }
}
