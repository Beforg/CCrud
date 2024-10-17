#include <stdio.h>
#include "nav.h"

int main(void) {
    printf("#### Bem vindo ao Sistema  CCrud ####\n");
    int option = 0;
    do {
        showOptions();
        scanf("%d", &option);
        switch (option) {
            case 1:
                registerProduct();
                break;
            case 2:
                listProducts();
                break;
            case 3:
                update();
                break;
            case 4:
                delete();
                break;
            case 5:
                about();
                break;
            case 6:
            printf("Saindo do sistema\n");
            break;
            default:
                printf("Opçao invalida\n");
        }
    } while (option!= 6);

}
