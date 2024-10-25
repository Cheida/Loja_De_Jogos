#include "biblioteca.h"

// Função que atualiza as carteiras com o saldo atual
void atualizacao_das_carteiras(float *carteira){
    FILE *carteirafile;

    carteirafile = fopen("creditos.bin", "wb"); // Abre o arquivo
    // Verifica se o arquivo foi aberto com sucesso
    if (carteirafile == NULL) {
        printf("Erro ao abrir o arquivo de créditos para escrita.\n");
        return;
    }

    size_t escrevendo = fwrite(carteira, sizeof(float), 10, carteirafile); // Escreve os 10 valores de carteira
    // Verifica se os valores são diferentes de 10
    if (escrevendo != 10) {
        printf("Erro ao salvar os créditos no arquivo.\n");
    }
    fclose(carteirafile); // Fecha o arquivo
}