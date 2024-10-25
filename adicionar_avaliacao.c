#include "biblioteca.h"

// Função que adiciona avaliações
void adicionar_avaliacao() {
    FILE *arquivo;


    char nome[255];
    char comentario[255];
    float nota;

    arquivo = fopen("jogos_avaliacao.txt", "a"); // Abre o arquivo jogos.txt para atualizar

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    printf("|Qual é o nome do jogo: ");
    scanf("%s", nome);

    printf("|Como foi a sua experiência: ");
    scanf("%s", comentario);

    printf("|Qual é a nota do jogo(0 - 10): ");
    scanf("%f", &nota);

    getchar(); // Tirar o '\n'

    fprintf(arquivo, "Nome: %s; Comentario: %s; Nota: %.2f\n", nome, comentario, nota); // Salva no arquivo, com esse formato escrito

    fclose(arquivo);
    printf("Atualização feita com sucesso!!\n");


}