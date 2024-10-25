#include "biblioteca.h"

// Funçaõ que mostra as avaliações dos jogos
void mostrar_avaliacao(){
    FILE *arquivo;
    char linhas[255];

    arquivo = fopen("jogos_avaliacao.txt", "r"); // Abre o arquivo para ler

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    while (fgets(linhas, sizeof(linhas), arquivo)){ // Ele vai ler o arquivo linha por linha e vai mostrar no console
        printf("%s", linhas);
    }
    fclose(arquivo);
}