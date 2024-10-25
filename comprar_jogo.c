#include "biblioteca.h"

// Função que compra os jogos
void comprar_jogo(float *carteira, cadastro *p, int indice) {
    int opcao, compra = 0; // Variável para armazenar a opção do usuário
    char senha_usuario[10];  // Ajustando para uma string de senha

    // Loop infinito para a compra
    while(1){
        int cont = 0; // Um contador para encerrar o loop infinito
        printf("\nJogos disponíveis:\n");
        mostrar_arquivo(); // Função que mostra todas as opções possíveis

        printf("\n\nEscolha o jogo que deseja comprar (ou 0 para voltar): ");
        scanf("%d", &opcao);

        // Compra conforme a opção escolhida
        switch(opcao){
            // Escolha que volta para o menu
            case 0:
                getchar();  // Para absorver o '\n' que resta no buffer
                cont++;  // Atualiza o contador para sair do loop
                break;

            // Compra do Jogo Fort
            case 1:
                printf("Jogo escolhido: Fort | Tipo: Fps\n");
                printf("Saldo de sua conta: R$%.2f\n", carteira[indice]);
                printf("Digite a sua senha para confirmar a compra (ou '0' para voltar ao menu): ");
                scanf("%s", senha_usuario);
                // Se o usuário digitar 0 ele será direcionado para o menu
                if (strcmp(senha_usuario, "0") == 0) {
                    getchar();  // Para absorver o '\n' restante no buffer
                    cont++;  // Incrementa para sair do loop
                    break;
                }
                // Verifica se o saldo é suficiente para a compra
                else if (100 > carteira[indice]) {
                    printf("Saldo insuficiente!!\n");  // Informa saldo insuficiente
                    break;
                }
                else {
                    // Valida a senha do usuário
                    if (strcmp(senha_usuario, p[indice].senha) == 0) {
                        carteira[indice] -= 100;  // Deduz o valor do jogo da carteira
                        printf("Compra realizada com sucesso!!\n");
                        salvar_biblioteca(p[indice].cpf, "Fort", compra);  // Salva a compra na biblioteca do usuário
                        getchar();  // Para absorver o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");  // Mensagem de senha incorreta
                        break;
                    }
                }

            // Compra do Jogo Hallo
            case 2:
                printf("Jogo escolhido: Hallo | Tipo: Tiro\n");
                printf("Saldo de sua conta: R$%.2f\n", carteira[indice]);
                printf("Digite a sua senha para confirmar a compra (ou '0' para voltar ao menu): ");
                scanf("%s", senha_usuario);
                // Se o usuário digitar 0 ele será direcionado para o menu
                if (strcmp(senha_usuario, "0") == 0) {
                    getchar();  // Absorve o '\n'
                    cont++;  // Incrementa para sair do loop
                    break;
                }
                // Verifica se o saldo é suficiente para a compra
                else if (46 > carteira[indice]) {
                    printf("Saldo insuficiente!!\n");
                    break;
                }
                else {
                    // Valida a senha do usuário
                    if (strcmp(senha_usuario, p[indice].senha) == 0) {
                        carteira[indice] -= 46;  // Deduz o valor do jogo
                        printf("Compra realizada com sucesso!!\n");
                        salvar_biblioteca(p[indice].cpf, "Hallo", compra);  // Salva o jogo na biblioteca do usuário
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo The_Last_Of_Us
            case 3:
                printf("Jogo escolhido: The_Last_Of_Us | Tipo: Adv\n");
                printf("Saldo de sua conta: R$%.2f\n", carteira[indice]);
                printf("Digite a sua senha para confirmar a compra (ou '0' para voltar ao menu): ");
                scanf("%s", senha_usuario);
                // Se o usuário digitar 0 ele será direcionado para o menu
                if (strcmp(senha_usuario, "0") == 0) {
                    getchar();  // Absorve o '\n'
                    cont++;  // Incrementa para sair do loop
                    break;
                }
                // Verifica se o saldo é suficiente para a compra
                else if (149 > carteira[indice]) {
                    printf("Saldo insuficiente!!\n");
                    break;
                }
                else {
                    // Valida a senha do usuário
                    if (strcmp(senha_usuario, p[indice].senha) == 0) {
                        carteira[indice] -= 149;  // Deduz o valor do jogo
                        printf("Compra realizada com sucesso!!\n");
                        salvar_biblioteca(p[indice].cpf, "The_Last_Of_Us", compra);  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo Minecraft
            case 4:
                printf("Jogo escolhido: Minecraft | Tipo: Sob\n");
                printf("Saldo de sua conta: R$%.2f\n", carteira[indice]);
                printf("Digite a sua senha para confirmar a compra (ou '0' para voltar ao menu): ");
                scanf("%s", senha_usuario);
                // Se o usuário digitar 0 ele será direcionado para o menu
                if (strcmp(senha_usuario, "0") == 0) {
                    getchar();  // Absorve o '\n'
                    cont++;  // Incrementa para sair do loop
                    break;
                }
                // Verifica se o saldo é suficiente para a compra
                else if (200 > carteira[indice]) {
                    printf("Saldo insuficiente!!\n");
                    break;
                }
                else {
                    // Valida a senha do usuário
                    if (strcmp(senha_usuario, p[indice].senha) == 0) {
                        carteira[indice] -= 200;  // Deduz o valor do jogo
                        printf("Compra realizada com sucesso!!\n");
                        salvar_biblioteca(p[indice].cpf, "Minecraft", compra);  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo Baldur's_Gate
            case 5:
                printf("Jogo escolhido: Baldur's_Gate | Tipo: RPG\n");
                printf("Saldo de sua conta: R$%.2f\n", carteira[indice]);
                printf("Digite a sua senha para confirmar a compra (ou '0' para voltar ao menu): ");
                scanf("%s", senha_usuario);
                // Se o usuário digitar 0 ele será direcionado para o menu
                if (strcmp(senha_usuario, "0") == 0) {
                    getchar();  // Absorve o '\n'
                    cont++;  // Incrementa para sair do loop
                    break;
                }
                // Verifica se o saldo é suficiente para a compra
                else if (247.27 > carteira[indice]) {
                    printf("Saldo insuficiente!!\n");
                    break;
                }
                else {
                    // Valida a senha do usuário
                    if (strcmp(senha_usuario, p[indice].senha) == 0) {
                        carteira[indice] -= 247.27;  // Deduz o valor do jogo
                        printf("Compra realizada com sucesso!!\n");
                        salvar_biblioteca(p[indice].cpf, "Baldur's_Gate", compra);  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo GTA_V
            case 6:
                printf("Jogo escolhido: GTA_V | Tipo: Ação\n");
                printf("Saldo de sua conta: R$%.2f\n", carteira[indice]);
                printf("Digite a sua senha para confirmar a compra (ou '0' para voltar ao menu): ");
                scanf("%s", senha_usuario);
                // Se o usuário digitar 0 ele será direcionado para o menu
                if (strcmp(senha_usuario, "0") == 0) {
                    getchar();  // Absorve o '\n'
                    cont++;  // Incrementa para sair do loop
                    break;
                }
                // Verifica se o saldo é suficiente para a compra
                else if (149.95 > carteira[indice]) {
                    printf("Saldo insuficiente!!\n");
                    break;
                }
                else {
                    // Valida a senha do usuário
                    if (strcmp(senha_usuario, p[indice].senha) == 0) {
                        carteira[indice] -= 149.95;  // Deduz o valor do jogo
                        printf("Compra realizada com sucesso!!\n");
                        salvar_biblioteca(p[indice].cpf, "GTA_V", compra);  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo Cyberpunk_2077
            case 7:
                printf("Jogo escolhido: Cyberpunk_2077 | Tipo: Ação\n");
                printf("Saldo de sua conta: R$%.2f\n", carteira[indice]);
                printf("Digite a sua senha para confirmar a compra (ou '0' para voltar ao menu): ");
                scanf("%s", senha_usuario);
                // Se o usuário digitar 0 ele será direcionado para o menu
                if (strcmp(senha_usuario, "0") == 0) {
                    getchar();  // Absorve o '\n'
                    cont++;  // Incrementa para sair do loop
                    break;
                }
                // Verifica se o saldo é suficiente para a compra
                else if (129.99 > carteira[indice]) {
                    printf("Saldo insuficiente!!\n");
                    break;
                }
                else {
                    // Valida a senha do usuário
                    if (strcmp(senha_usuario, p[indice].senha) == 0) {
                        carteira[indice] -= 129.99;  // Deduz o valor do jogo
                        printf("Compra realizada com sucesso!!\n");
                        salvar_biblioteca(p[indice].cpf, "Cyberpunk_2077", compra);  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo Rainbow_Six_Siege
            case 8:
                printf("Jogo escolhido: Rainbow_Six_Siege | Tipo: Tiro\n");
                printf("Saldo de sua conta: R$%.2f\n", carteira[indice]);
                printf("Digite a sua senha para confirmar a compra (ou '0' para voltar ao menu): ");
                scanf("%s", senha_usuario);
                // Se o usuário digitar 0 ele será direcionado para o menu
                if (strcmp(senha_usuario, "0") == 0) {
                    getchar();  // Absorve o '\n'
                    cont++;  // Incrementa para sair do loop
                    break;
                }
                // Verifica se o saldo é suficiente para a compra
                else if (38.50 > carteira[indice]) {
                    printf("Saldo insuficiente!!\n");
                    break;
                }
                else {
                    // Valida a senha do usuário
                    if (strcmp(senha_usuario, p[indice].senha) == 0) {
                        carteira[indice] -= 38.50;  // Deduz o valor do jogo
                        printf("Compra realizada com sucesso!!\n");
                        salvar_biblioteca(p[indice].cpf, "Rainbow_Six_Siege", compra);  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo Enigma_do_Medo
            case 9:
                printf("Jogo escolhido: Enigma_do_Medo | Tipo: RPG\n");
                printf("Saldo de sua conta: R$%.2f\n", carteira[indice]);
                printf("Digite a sua senha para confirmar a compra (ou '0' para voltar ao menu): ");
                scanf("%s", senha_usuario);
                // Se o usuário digitar 0 ele será direcionado para o menu
                if (strcmp(senha_usuario, "0") == 0) {
                    getchar();  // Absorve o '\n'
                    cont++;  // Incrementa para sair do loop
                    break;
                }
                // Verifica se o saldo é suficiente para a compra
                else if (49.99 > carteira[indice]) {
                    printf("Saldo insuficiente!!\n");
                    break;
                }
                else {
                    // Valida a senha do usuário
                    if (strcmp(senha_usuario, p[indice].senha) == 0) {
                        carteira[indice] -= 49.99;  // Deduz o valor do jogo
                        printf("Compra realizada com sucesso!!\n");
                        salvar_biblioteca(p[indice].cpf, "Enigma_do_Medo", compra);  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo Borderlands_3
            case 10:
                printf("Jogo escolhido: Borderlands_3 | Tipo: Tiro\n");
                printf("Saldo de sua conta: R$%.2f\n", carteira[indice]);
                printf("Digite a sua senha para confirmar a compra (ou '0' para voltar ao menu): ");
                scanf("%s", senha_usuario);
                // Se o usuário digitar 0 ele será direcionado para o menu
                if (strcmp(senha_usuario, "0") == 0) {
                    getchar();  // Absorve o '\n'
                    cont++;  // Incrementa para sair do loop
                    break;
                }
                // Verifica se o saldo é suficiente para a compra
                else if (122.89 > carteira[indice]) {
                    printf("Saldo insuficiente!!\n");
                    break;
                }
                else {
                    // Valida a senha do usuário
                    if (strcmp(senha_usuario, p[indice].senha) == 0) {
                        carteira[indice] -= 122.89;  // Deduz o valor do jogo
                        printf("Compra realizada com sucesso!!\n");
                        salvar_biblioteca(p[indice].cpf, "Borderlands_3", compra);  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Se a escolha não existir
            default:
                printf("Opção inválida!!\n");  // Mensagem de opção inválida
                break;
        }

        // Se o contador for diferente de 0, sai do loop
        if (cont != 0) {
            break;
        }
    }
}