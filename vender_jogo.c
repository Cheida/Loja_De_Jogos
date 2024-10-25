#include "biblioteca.h"

// Função que vende um jogo
void vender_jogo(cadastro *p, int indice, float *carteira) {
    char nome_jogo[50];
    int venda = 1;
    float valor_jogo;

    while(1){
        int cont = 1;
        consultar_biblioteca_de_jogos(p, indice);  // Consulta a biblioteca
        printf("Digite um nome dos jogo acima que deseja vender (ou '0' para voltar ao menu): ");
        scanf("%s", nome_jogo);

        // Se o usuário digitar 0 ele será direcionado para o menu
        if (strcmp(nome_jogo, "0") == 0){
            getchar();  // Absorve o '\n'
            break;
        } else if (strcmp(nome_jogo, "Fort") == 0) {
            valor_jogo = 100.0; // Valor do jogo Fort
        } else if (strcmp(nome_jogo, "Hallo") == 0) {
            valor_jogo = 46.0; // Valor do jogo Hallo
        } else if (strcmp(nome_jogo, "The_Last_Of_Us") == 0) {
            valor_jogo = 149.0; // Valor do jogo The_Last_Of_Us
        } else if (strcmp(nome_jogo, "Minecraft") == 0) {
            valor_jogo = 200.0; // Valor do jogo Minecraft
        } else if (strcmp(nome_jogo, "Baldur's_Gate") == 0) {
            valor_jogo = 247.27; // Valor do jogo Baldur's_Gate
        } else if (strcmp(nome_jogo, "GTA_V") == 0) {
            valor_jogo = 149.95; // Valor do jogo GTA_V
        } else if (strcmp(nome_jogo, "Cyberpunk_2077") == 0) {
            valor_jogo = 129.99; // Valor do jogo Cyberpunk_2077
        } else if (strcmp(nome_jogo, "Rainbow_Six_Siege") == 0) {
            valor_jogo = 38.50; // Valor do jogo Rainbow_Six_Siege
        } else if (strcmp(nome_jogo, "Enigma_do_Medo") == 0) {
            valor_jogo = 49.99; // Valor do jogo Enigma_do_Medo
        } else if (strcmp(nome_jogo, "Borderlands_3") == 0) {
            valor_jogo = 122.89; // Valor do jogo Borderlands_3
        }
        else{
            printf("Jogo não encontrado!!\n");  // Mensagem de jogo não encontrado
            cont = 0;
        }
        if (cont != 0){
            cont = salvar_biblioteca(p[indice].cpf, nome_jogo, venda);
        }
        // Se o contador for diferente de 0, sai do loop
        if (cont != 0){
            carteira[indice] += valor_jogo;
            printf("Venda realizada com sucesso!!\n");
            printf("Saldo de sua conta: R$%.2f\n", carteira[indice]);
            getchar();  // Absorve o '\n'
            break;
        }
    }
}