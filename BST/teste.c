#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(int argc, char *argv[]) {
    tabela tab;
    int opcao;
	int n;
    inicializarTabela(&tab);

    while (1) {
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("%d\n", altura(tab.indices));
                break;
            case 2:
                adicionarJogador(&tab, ler_dados());
                break;
            case 3:
                printf("%d\n", maior_elemento(tab.indices)->chave);
                break;
            case 4:
                printf("%d\n", menor_elemento(tab.indices)->chave);
                break;
            case 5:
                pre_order(tab.indices, &tab);
                printf("\n");
                break;
            case 6:
                in_order(tab.indices, &tab);
                printf("\n");
                break;
            case 7:
                pos_order(tab.indices, &tab);
                printf("\n");
                break;
            case 8:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &n);
                tab.indices = remover(n, tab.indices);
                printf("\n");
                break;

             case 9:
                printf("Digite o indice a ser buscado: ");
                scanf("%d", &n);
                imprimirElementoPorIndice(tab.indices, &tab, n);
                printf("\n");
                break;
                
            case 99:
                finalizar(&tab);
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}