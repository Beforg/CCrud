#include "service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeProduct(const char *fileName, int productCode, const char *productName, double productPrice) {
    FILE *file = fopen(fileName, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", fileName);
        return;
    }

    fprintf(file, "%d,%s,%.2f\n", productCode, productName, productPrice);
    fclose(file);
}

void readProduct() {
    FILE *file = fopen("products.csv", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("%-10s %-20s %-10s\n", "Codigo", "Nome", "Preco");
    printf("---------------------------------------------\n");

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        int productCode;
        char productName[50];
        double productPrice;

        // Dividir a linha em componentes
        char *token = strtok(line, ",");
        if (token != NULL) productCode = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(productName, token, sizeof(productName));

        token = strtok(NULL, ",");
        if (token != NULL) productPrice = atof(token);

        // Remover o caractere de nova linha do nome do produto, se presente
        size_t len = strlen(productName);
        if (len > 0 && productName[len-1] == '\n') {
            productName[len-1] = '\0';
        }

        // Exibir os dados em formato de tabela
        printf("%-10d %-20s %-10.2f\n", productCode, productName, productPrice);
    }

    fclose(file);
}

void updateProduct(int productCode) {
    FILE *file = fopen("products.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");
    if (file == NULL || tempFile == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        int code = 0;
        char name[50];
        double price;

        char *token = strtok(line, ",");
        if (token != NULL) code = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(name, token, sizeof(name));

        token = strtok(NULL, ",");
        if (token != NULL) price = atof(token);

        if (code == productCode) {
            found = 1;
            printf("Informe o novo nome do produto:\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            fgets(name, sizeof(name), stdin);
            size_t len = strlen(name);
            if (len > 0 && name[len-1] == '\n') {
                name[len-1] = '\0';
            }

            printf("Informe o novo preco do produto:\n");
            scanf("%lf", &price);
        }

        fprintf(tempFile, "%d,%s,%.2f\n", code, name, price);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("products.csv");
        rename("temp.csv", "products.csv");
        printf("Produto atualizado com sucesso.\n");
    } else {
        remove("temp.csv");
        printf("Produto nao encontrado.\n");
    }
}

void deleteProduct(int productCode) {
    FILE *file = fopen("products.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");
    if (file == NULL || tempFile == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        int code = 0;
        char name[50];
        double price;

        char *token = strtok(line, ",");
        if (token != NULL) code = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(name, token, sizeof(name));

        token = strtok(NULL, ",");
        if (token != NULL) price = atof(token);

        if (code != productCode) {
            fprintf(tempFile, "%d,%s,%.2f\n", code, name, price);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        printf("Tem certeza que deseja excluir o produto?\n");
        printf("1 - Sim\n");
        printf("2 - Nao\n");
        int option;
        scanf("%d", &option);
        if (option != 1) {
            remove("temp.csv");
            return;
        }
        remove("products.csv");
        rename("temp.csv", "products.csv");
        printf("Produto excluido com sucesso.\n");
    } else {
        remove("temp.csv");
        printf("Produto nao encontrado.\n");
    }
}