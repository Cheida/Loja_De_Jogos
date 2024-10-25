#include "biblioteca.h"

// Função que salva os jogos comprados na biblioteca
int salvar_biblioteca(const char *cpf, const char *nome_jogo, int trasacao) {

    if (trasacao == 0){
        FILE *arquivo_bib = fopen("biblioteca_jogos.txt", "a");

        if (arquivo_bib == NULL) {
            printf("Erro ao abrir o arquivo de biblioteca!\n");
            return 0;
        }
        // Grava o CPF do usuário e o nome do jogo no arquivo
        fprintf(arquivo_bib, "%s;%s\n", cpf, nome_jogo);

        fclose(arquivo_bib);
        return 1;
    } else{
        FILE *arquivo, *temp;
        char linha[255];
        char arquivo_cpf[12], arquivo_nome_jogo[50];
        int encontrou = 0, cont;

        // Abre o arquivo original para leitura e o temporário para escrita
        arquivo = fopen("biblioteca_jogos.txt", "r");
        temp = fopen("temp.txt", "w");

        if (arquivo == NULL || temp == NULL) {
            printf("Erro ao abrir o arquivo!\n");
            return 0;
        }

        // Lê cada linha do arquivo original
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            // Divide a linha em partes (CPF e nome do jogo)
            sscanf(linha, "%[^;];%[^\n]", arquivo_cpf, arquivo_nome_jogo);

            // Se o CPF e nome do jogo da linha não forem iguais aos que queremos excluir, escreve no arquivo temporário
            if (strcmp(arquivo_cpf, cpf) != 0 || strcmp(arquivo_nome_jogo, nome_jogo) != 0) {
                fputs(linha, temp);
            } else {
                encontrou = 1;
            }
        }

        fclose(arquivo);
        fclose(temp);

        // Se encontrou a linha, renomeia o arquivo temporário para substituir o original
        if (encontrou) {
            remove("biblioteca_jogos.txt");       // Remove o arquivo original
            rename("temp.txt", "biblioteca_jogos.txt"); // Renomeia o temporário para o original
            return cont = 1;
        } else {
            printf("CPF ou jogo não encontrado.\n");
            remove("temp.txt"); // Exclui o arquivo temporário se nada foi removido
            return cont = 0;
        }
        }
}
