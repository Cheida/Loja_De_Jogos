#include "biblioteca.h"

// Função que lê o arquivo e armazena as carteiras em uma variável
void iniciacao_arquivos(float *carteira) {
    FILE *carteirafile;

    // Tenta abrir o arquivo binário
    carteirafile = fopen("creditos.bin", "rb");

    // Se o arquivo não for encontrado, inicializa com zero e cria o arquivo
    if (carteirafile == NULL) {
        printf("Arquivo de créditos não encontrado. Inicializando com valores zerados.\n");
        for (int i = 0; i < 10; i++) {
            carteira[i] = 0.0;  // Inicializa todas as carteiras com zero
        }

        // Cria o arquivo binário e salva os valores zerados
        carteirafile = fopen("creditos.bin", "wb");
        if (carteirafile != NULL) {
            size_t escrito = fwrite(carteira, sizeof(float), 10, carteirafile); // Escreve 10 valores de float
            if (escrito != 10) {
                printf("Erro ao escrever no arquivo de créditos.\n");
            }
            fclose(carteirafile);
        } else {
            printf("Erro ao criar o arquivo de créditos.\n");
        }
    } else {
        // Se o arquivo foi aberto corretamente, lê os valores da carteira
        size_t lendo = fread(carteira, sizeof(float), 10, carteirafile); // Lê os 10 valores de float
        if (lendo != 10) {
            for (int i = 0; i < 10; i++) {
                carteira[i] = 0.0; // Inicializa com zero caso a leitura falhe
            }
        }
        fclose(carteirafile);
    }
}