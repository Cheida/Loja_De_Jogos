#include "biblioteca.h"

// Função que consulta a biblioteca de jogos
void consultar_biblioteca_de_jogos(cadastro *p, int indice) {
    FILE *arquivo_bib = fopen("biblioteca_jogos.txt", "r");

    if (arquivo_bib == NULL) {
        printf("Erro ao abrir o arquivo de biblioteca!\n");
        return;
    }

    char linha[255];
    char *token;
    char cpf[12];
    char nome_jogo[50];
    int encontrou = 0;

    printf("\nJogos de %s:\n", p[indice].nome);

    // Percorre cada linha do arquivo e exibe os jogos que pertencem ao usuário
    while (fgets(linha, sizeof(linha), arquivo_bib)) {
        token = strtok(linha, ";");
        strcpy(cpf, token);
        token = strtok(NULL, ";");
        strcpy(nome_jogo, token);

        // Se o CPF na linha coincidir com o CPF do usuário, exibe o jogo
        if (strcmp(cpf, p[indice].cpf) == 0) {
            printf("- %s", nome_jogo);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum jogo encontrado na biblioteca.\n");
    }

    fclose(arquivo_bib);
}