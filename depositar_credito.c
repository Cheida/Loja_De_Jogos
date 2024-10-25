#include "biblioteca.h"

// Função que deposita créditos na carteira do jogo
void depositar_credito(float *carteira, int indice){
    float valor; // Variável para receber o deposito de créditos

    while(1){
        printf("Quanto deseja depositar (ou 0 para não depositar): ");
        scanf("%f", &valor); // Recebe o valor e armazena na variável

        // Verifica se o valor é menor que 0
        if (valor < 0){
            printf("Valor inválido!!\n");
        }
        // Se for igual a 0, volta para o menu
        else if(valor == 0){
            getchar(); // Para absorver o '\n' que resta no buffer
            break;
        }
        // Se não, realiza o deposito
        else{
            carteira[indice] += valor; // Deposita o valor inserido na carteira
            printf("Depósito realizado com sucesso!!\n");
            getchar(); // Para absorver o '\n' que resta no buffer
            break;
        }
    }

}