#include "nav.h"
#include "service.h"
#include <stdio.h>
#include <string.h>

// pra limpar o buffer do teclado, pois estava pegando o enter

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// removendo o \n do final da string

void removeNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

void continueRegister(int *opcao) {
    printf("Deseja continuar cadastrando produtos?\n");
    printf("1. Sim\n");
    printf("2. Nao\n");
    scanf("%d", opcao);

    if (*opcao != 1 && *opcao != 2) {
        printf("Opcao invalida\n");
    }
}
// mostrando as opcoes do menu
void showOptions() {
    printf("========================================\n");
    printf("1. Cadastrar produto\n");
    printf("2. Listar produtos\n");
    printf("3. Atualizar produto\n");
    printf("4. Excluir produto\n");
    printf("5. Sobre\n");
    printf("6. Sair\n");
    printf("========================================\n");
}

// registro do produto

void registerProduct() {
    int opcao = -1;

    while (opcao != 2) {
        printf("========== Cadastro de Produtos ==========\n");
        printf("Informe o codigo do produto (apenas numeros):\n");

        int productCode;
        scanf("%d", &productCode);
        clearBuffer();

        printf("Informe o nome do produto:\n");
        char productName[50];
        fgets(productName, sizeof(productName), stdin);
        removeNewline(productName);

        printf("Informe o preco do produto:\n");
        double productPrice;
        scanf("%lf", &productPrice);

        writeProduct("products.csv", productCode, productName, productPrice);
        continueRegister(&opcao);

    }
}

void listProducts() {
    printf("========== Listando Produtos ==========\n");
    readProduct();
}

void update() {
    printf("Informe o codigo do produto que deseja alterar:\n");
    int productCode;
    scanf("%d", &productCode);
    updateProduct(productCode);
}

void delete() {
    printf("Informe o codigo do produto que deseja excluir:\n");
    int productCode;
    scanf("%d", &productCode);
    deleteProduct(productCode);
}

void about() {
    printf("========== Sobre o Sistema ==========\n");
    printf("Crud de produtos\n");
    printf("Desenvolvido por: Bruno Forgiarini | Engenharia de Computacao - BAGE-RS\n");
    printf("Versao: 0.1.0\n");
    printf("Data: 17 out. 2024\n");
}