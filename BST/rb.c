#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>

arvorerb no_null;

void inicializarRb(arvorerb *raiz) {
	*raiz = NULL;
	no_null = (arvorerb) malloc(sizeof(struct no_rb));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = NULL;
    no_null->esq = NULL;
    no_null->dir = NULL;
    no_null->pai = NULL;
}

void salvar_arquivoRb(char *nome, arvorerb a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliarRb(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliarRb(arvorerb raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->dado, sizeof(tipo_dadorb), 1, arq);
		salvar_auxiliarRb(raiz->esq, arq);
		salvar_auxiliarRb(raiz->dir, arq);
	}

}

arvorerb carregar_arquivoRb(char *nome, arvorerb a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_dadorb * temp;
	if(arq != NULL) {
		temp = (tipo_dadorb *) malloc(sizeof(tipo_dadorb));
		while(fread(temp, sizeof(tipo_dadorb), 1, arq)) {
			
			adicionarRb(temp, &a);			
			temp = (tipo_dadorb *) malloc(sizeof(tipo_dadorb));

		}
		fclose(arq);

	}
	return a;
}

void adicionarRb( tipo_dadorb *valor, arvorerb *raiz) {
    arvorerb posicao = *raiz;
    arvorerb pai = NULL;

    while(posicao != NULL) {
        pai = posicao;
        if(strcmp(valor->chave, posicao->dado->chave) > 0)
            posicao = posicao->dir;
        else
            posicao = posicao->esq;
    }

    arvorerb novo = (arvorerb) malloc(sizeof(struct no_rb));
    novo->dado = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = pai;
    novo->cor = VERMELHO;

    if(eh_raiz(novo))
        *raiz = novo;
    else {
        if(strcmp(valor->chave, pai->dado->chave) > 0)
            pai->dir = novo;
        else
            pai->esq = novo;
    }

    ajustar(raiz, novo);
}


void ajustar(arvorerb *raiz, arvorerb elemento){

	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {

			if(cor(tio(elemento)) == VERMELHO) {
				tio(elemento)->cor = PRETO;
				elemento->pai->cor = PRETO;
				elemento->pai->pai->cor = VERMELHO;
		
				elemento = elemento->pai->pai;
				continue;
			} 
			if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
					rotacao_simples_direita(raiz, elemento->pai->pai);
					elemento->pai->cor = PRETO;
					elemento->pai->dir->cor = VERMELHO;
					continue;
			}
			if(eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)) {
					rotacao_simples_esquerda(raiz, elemento->pai->pai);
					elemento->pai->cor = PRETO;
					elemento->pai->esq->cor = VERMELHO;
					continue;
			}
			if(eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai)) {
					rotacao_dupla_direita(raiz, elemento->pai->pai);
					elemento->cor = PRETO;
					elemento->dir->cor = VERMELHO;
					continue;
			}
			if(eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai)){
					rotacao_dupla_esquerda(raiz, elemento->pai->pai);
					elemento->cor = PRETO;
					elemento->esq->cor = VERMELHO;
					continue;
			}

	}
	(*raiz)->cor = PRETO;
}

void rotacao_simples_direita(arvorerb *raiz, arvorerb pivo){
			arvorerb u, t1;
			u = pivo->esq;
            t1 = u->dir;
			int posicao_pivo_esq = eh_filho_esquerdo(pivo);

			pivo->esq = t1;
            if(t1 != NULL)
				t1->pai = pivo;

			u->dir = pivo;

			u->pai = pivo->pai;
			pivo->pai = u;

			if(eh_raiz(u))
				*raiz = u;
			else {
					if(posicao_pivo_esq)
							u->pai->esq = u;
					else
							u->pai->dir = u;
			}
}

void rotacao_simples_esquerda(arvorerb *raiz, arvorerb pivo) {
				arvorerb u, t1;
			u = pivo->dir;
            t1 = u->esq;

			int posicao_pivo_dir = eh_filho_direito(pivo);
			
			pivo->dir = t1;
            if(t1 != NULL)
				t1->pai = pivo;

			u->esq = pivo;

			u->pai = pivo->pai;
			pivo->pai = u;

			if(eh_raiz(u))
				*raiz = u;
			else {
					if(posicao_pivo_dir)
							u->pai->dir = u;
					else
							u->pai->esq = u;
			}
}

void rotacao_dupla_direita(arvorerb *raiz, arvorerb pivo) {
    rotacao_simples_esquerda (raiz, pivo->esq);
    rotacao_simples_direita(raiz, pivo);
}

void rotacao_dupla_esquerda(arvorerb *raiz, arvorerb pivo) {
    rotacao_simples_direita(raiz, pivo->dir);
    rotacao_simples_esquerda(raiz, pivo);
}

enum cor cor(arvorerb elemento) {
	enum cor c;
	if(elemento==NULL)
		return PRETO;
	else
		return elemento->cor;
	return c;
}

int eh_raiz(arvorerb elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvorerb elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

int eh_filho_direito(arvorerb elemento){
	return (elemento->pai != NULL && elemento == elemento->pai->dir);
}

arvorerb tio(arvorerb elemento) {
	return irmao(elemento->pai);
}

arvorerb irmao(arvorerb elemento) {
	if(eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}


void imprimirRb(arvorerb raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elementoRb(raiz);
		imprimirRb(raiz->esq);
		imprimirRb(raiz->dir);
	}
	printf(")");
}

tipo_dadorb * maior_elementoRb(arvorerb raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elementoRb(raiz->dir);
}

void pre_orderRb(arvorerb raiz, tabela *tab) {
	if(raiz != NULL) {
		imprimir_elementoRbtabela(raiz, tab);
		pre_orderRb(raiz->esq, tab);
		pre_orderRb(raiz->dir, tab);
	}
}

void pos_orderRb(arvorerb raiz, tabela *tab) {
	if(raiz != NULL) {
		pos_orderRb(raiz->esq, tab);
		pos_orderRb(raiz->dir, tab);
		imprimir_elementoRbtabela(raiz, tab);
	}
}

void in_orderRb(arvorerb raiz, tabela *tab) {
	if(raiz != NULL) {
		in_orderRb(raiz->esq, tab);
		imprimir_elementoRbtabela(raiz, tab);
		in_orderRb(raiz->dir, tab);
	}
}

void imprimir_elementoRb(arvorerb raiz) {
	switch(raiz->cor){
		case PRETO:
			printf("\x1b[30m[%d]\x1b[0m", raiz->dado);
			break;
		case VERMELHO:
			printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%d]\x1b[0m", raiz->dado);
			break;
	}
}

arvorerb removerRb (char *valor, arvorerb *raiz) {
	arvorerb posicao;
	posicao = *raiz;

	while(posicao != NULL) {
		if(strcmp(valor, posicao->dado->chave) == 0) {

            if(posicao->esq != NULL && posicao->dir != NULL) { 
    			posicao->dado = maior_elementoRb(posicao->esq);   
	    		strcpy(valor, posicao->dado->chave);
            }

			if(posicao->esq == NULL && posicao->dir != NULL) {
				posicao->dir->cor = PRETO;
                posicao->dir->pai = posicao->pai;

				if(eh_raiz(posicao)) {
					*raiz = posicao->dir;
				} else {
					if(eh_filho_esquerdo(posicao)) {
    					posicao->pai->esq = posicao->dir;
					} else {
						posicao->pai->dir = posicao->dir;
    				}      
				}
                free(posicao);   
				break;
			}


			if(posicao->dir == NULL && posicao->esq != NULL) {
				posicao->esq->cor = PRETO;
				posicao->esq->pai = posicao->pai;

				if(eh_raiz(posicao)){
					*raiz = posicao->esq;
				} else {
					if(eh_filho_direito(posicao)){
						posicao->pai->dir = posicao->esq;
					} else{
						posicao->pai->esq = posicao->esq;
					}
				
				}
				free(posicao);
				break;	
			}

			if(posicao->esq == NULL && posicao->dir == NULL) {
				
				if(eh_raiz(posicao)) {
					*raiz = NULL;
                    free(posicao);
					break;
				}

				if(posicao->cor == VERMELHO) {
					if(eh_filho_esquerdo(posicao))
						posicao->pai->esq = NULL;
					else
						posicao->pai->dir = NULL;
                    free(posicao);
					break;
				} else {

                no_null->cor = DUPLO_PRETO;
				no_null->pai = posicao->pai;
				if(eh_filho_esquerdo(posicao))
					posicao->pai->esq = no_null;
				else
					posicao->pai->dir = no_null;
				free(posicao);
                reajustar(raiz, no_null);
				break;
				}
			}
		}	
		if(strcmp(valor, posicao->dado->chave) > 0) 
				posicao = posicao->dir;
		else 
				posicao = posicao->esq;
	}
}


void reajustar(arvorerb *raiz, arvorerb elemento){

	if(eh_raiz(elemento)) {
		elemento->cor = PRETO;
        if(elemento == no_null) {
            *raiz = NULL;
		}
		return;
	}

	if(  cor(elemento->pai) == PRETO &&
		 cor(irmao(elemento)) == VERMELHO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == PRETO ) {
				if(eh_filho_esquerdo(elemento))
						rotacao_simples_esquerda(raiz, elemento->pai);
				else
						rotacao_simples_direita(raiz, elemento->pai);	
				
                elemento->pai->pai->cor = PRETO;
				elemento->pai->cor = VERMELHO;
				
                reajustar(raiz, elemento);
				return;
	}

	if(cor(elemento->pai) == PRETO &&
		 cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == PRETO) {

			elemento->pai->cor = DUPLO_PRETO;
			irmao(elemento)->cor = VERMELHO;
			retira_duplo_preto(raiz, elemento);

			reajustar(raiz, elemento->pai);

			return ;
	}	

	if(cor(elemento->pai) == VERMELHO &&
		 cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == PRETO) {	
		
		elemento->pai->cor = PRETO;
		irmao(elemento)->cor = VERMELHO;

		retira_duplo_preto(raiz, elemento);	

			return;
	}

	if(	 eh_filho_esquerdo(elemento) &&
		 cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == PRETO &&
		 cor(irmao(elemento)->esq) == VERMELHO) {	

			rotacao_simples_direita(raiz, irmao(elemento));
			irmao(elemento)->cor = PRETO;
			irmao(elemento)->dir->cor = VERMELHO;

			reajustar(raiz, elemento);


			return;
	}

	//caso 5b
	if(	eh_filho_direito(elemento) &&
		 cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == VERMELHO &&
		 cor(irmao(elemento)->esq) == PRETO) {	

			rotacao_simples_esquerda(raiz, irmao(elemento));
			irmao(elemento)->cor = PRETO;
			irmao(elemento)->esq->cor = VERMELHO;

			reajustar(raiz, elemento);

				return;
	}

	//caso 6a
	if(	 eh_filho_esquerdo(elemento) &&
		 cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->dir) == VERMELHO) {

			rotacao_simples_esquerda(raiz, irmao(elemento)->pai);
			elemento->pai->pai->cor = elemento->pai->cor;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->dir->cor = PRETO;
			retira_duplo_preto(raiz, elemento);

				return;
	}

	//caso 6b
	if(	 eh_filho_direito(elemento) &&
		 cor(irmao(elemento)) == PRETO &&
		 cor(irmao(elemento)->esq) == VERMELHO) {	
			
			rotacao_simples_direita(raiz, irmao(elemento)->pai);
			elemento->pai->pai->cor = elemento->pai->cor;
			elemento->pai->cor = PRETO;
			elemento->pai->pai->esq->cor = PRETO;
			retira_duplo_preto(raiz, elemento);

				return;
	}
}

void retira_duplo_preto(arvorerb *raiz, arvorerb elemento) {
			if(elemento == no_null)
				if(eh_filho_esquerdo(elemento))
						elemento->pai->esq = NULL;
				else
						elemento->pai->dir = NULL;
			else
				elemento->cor = PRETO;
}

void imprimir_elementoRbtabela(arvorerb raiz, tabela * tab) {
	dado * temp = (dado *) malloc (sizeof(dado));
    temp->numero = 1000;
    printf("indice: %d\n", raiz->dado->indice);

   	fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
	//
	int r = fread(temp, sizeof(dado), 1, tab->arquivo_dados);

	printf("[%s, %d, %d, %s, %s, %d ]\n",temp->nome,r, temp->numero, temp->posicao, temp->nacionalidade, temp->idade);
	free(temp);
}