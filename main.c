#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int op;
    char r;
    while (op != 4 && r != 'n') {
        do {
            printf("==================================\n   Controle de Estoque\n==================================\n1. Adicionar Item\n2. Remover Item\n3. Listar Estoque\n4. Sair\nOpcao:"); scanf("%d", &op);
            if (op < 1 || op > 4) printf("Opcao invalida! Tente novamente.\n");
        } while (op < 1 || op > 4);
        if (op == 1) {
            char item[100];
            int qtd;
            printf("Digite o nome do item: "); scanf(" %[^\n]s", item);
            printf("Digite a quantidade: "); scanf("%d", &qtd);
            FILE *p = fopen("estoque.txt", "a");
            if (p != NULL) {
                if (fprintf(p, "%s\n%d\n", item, qtd) != -1) printf("Item adicionado com sucesso!\n");
            }
            fclose(p);
        } else if (op == 2) {
            char item[100];
            int qtd;
            printf("Digite o nome do item: "); scanf(" %[^\n]s", item);
            printf("Digite a quantidade a ser removida: "); scanf("%d", &qtd);
            FILE *p = fopen("estoque.txt", "r");
            if (p != NULL) {
                FILE *a = fopen("aux.txt", "w");
                if (a != NULL) {
                    bool encontrado = false;
                    while (!feof(p)) {
                        char str[100];
                        int qtr;
                        if (fscanf(p, " %[^\n]s", str) != -1 && fscanf(p, "%d", &qtr) != -1) {
                            if (!strcmp(str, item)) {
                                encontrado = true;
                                if (qtd > qtr) {
                                    printf("Estoque insuficiente! Quantidade disponivel: %d\n", qtr);
                                    fprintf(a, "%s\n%d\n", item, qtr);
                                } else if ( qtd < qtr) {
                                    fprintf(a, "%s\n%d\n", item, qtr-qtd);
                                    printf("Quantidade atualizada com sucesso!\n");
                                } else printf("Item removido do estoque!\n");
                            } else fprintf(a, "%s\n%d\n", str, qtr);
                        }
                    }
                    fclose(p); fclose(a);
                    if (encontrado) {
                        FILE *a = fopen("aux.txt", "r"), *p = fopen("estoque.txt", "w");
                        while(!feof(a)) {
                            char str[100];
                            int qtr;
                            if (fscanf(a, " %[^\n]s", str) != -1 && fscanf(a, "%d", &qtr) != -1) fprintf(p, "%s\n%d\n", str, qtr);
                        }
                    } else printf("Item nao encontrado.\n");
                }
                fclose(a);
            }
            fclose(p);
        } else if (op == 3) {
            FILE *p = fopen("estoque.txt", "r");
            int c = 0;
            if (p != NULL) {
                while (!feof(p)) {
                    if (!c)printf("=============================\n        Estoque Atual\n=============================");
                    char item[100];
                    int qtd;
                    if (fscanf(p, " %[^\n]s", item) != -1 && fscanf(p, "%d", &qtd) != -1) printf("\nNome: %s\nQuantidade: %d\n", item, qtd);
                    c++;
                }
            }
            if (!c) printf("\nO estoque esta vazio.\n");
            fclose(p);
        }
        if (op != 4)printf("Deseja realizar outra operacao? (s/n):"); scanf(" %c", &r);
    }
    printf("Obrigado por usar o Controle de Estoques! Ate a proxima.\n");



    return 0;
}
