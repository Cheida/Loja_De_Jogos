#include "biblioteca.h"

// Menu
void menu(cadastro *p, int indice) {
    int escolha;
    char escolha_str[10];
    float carteira[10];

    iniciacao_arquivos(carteira);

    while (1) {
        printf("|-----------------------------------|\n");
        printf("|         Bem-Vindo a Loja          |\n");
        printf("|-----------------------------------|\n");
        printf("| 1 - Comprar Jogo                  |\n");
        printf("| 2 - Vender Jogo                   |\n");
        printf("| 3 - Adicionar Avaliação do Jogo   |\n");
        printf("| 4 - Mostrar Avaliações dos Jogos  |\n");
        printf("| 5 - Consultar Biblioteca de Jogos |\n");
        printf("| 6 - Depositar Crédito             |\n");
        printf("| 7 - Sair                          |\n");
        printf("|-----------------------------------|\n");
        printf("Qual escolha você deseja: ");
        fgets(escolha_str, sizeof(escolha_str), stdin);
        escolha = atoi(escolha_str); // Converte a string para inteiro

        switch (escolha) {
            case 1:
                comprar_jogo(carteira, p, indice);
                break;
            case 2:
                vender_jogo(p, indice, carteira);
                break;
            case 3:
                adicionar_avaliacao();
                break;
            case 4:
                 mostrar_avaliacao();
                 break;
            case 5:
                consultar_biblioteca_de_jogos(p, indice);
                break;
            case 6:
                depositar_credito(carteira, indice);
                break;
            case 7:
                atualizacao_das_carteiras(carteira);
                printf("Ficando OFF...\n");
                system("pause");
                exit(0);
            default:
                printf("Essa opção não é válida!!\n");
        }
    }
}
