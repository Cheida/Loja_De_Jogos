#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// struct que armazena o cadastro dos usuarios
typedef struct cadastro {
    char cpf[12];
    char nome[100];
    char senha[10];
} cadastro;

// Funções Gerais
void depositar_credito(float *carteira, int indice);
void iniciacao_arquivos(float *carteira);
void atualizacao_das_carteiras(float *carteira);
void comprar_jogo(float *carteira, cadastro *p, int indice);
void vender_jogo();
void adicionar_avaliacao();
void consultar_biblioteca_de_jogos(cadastro *p, int indice);
void menu();
void mostrar_arquivo();



// Função para limpar o conteúdo, preenchendo com '\0'
void limparstring(char *array) {
    int i;
    for (i = 0; i < 255; i++) {
        array[i] = '\0';
    }
}

// Conta quantos usuários existem no arquivo, retornando a quantidade de linhas
int contar_usuarios() {
    FILE *arquivo;
    arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }

    int count = 0;
    char linha[255];
    while (fgets(linha, sizeof(linha), arquivo)) {
        count++;
    }
    fclose(arquivo);
    return count;
}


// Encontra os usuários no arquivo e os carrega
int achar_usuario(cadastro **p) {
    FILE *arquivo;
    arquivo = fopen("usuarios.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    int num_usuarios = contar_usuarios();
    *p = (cadastro *)malloc(num_usuarios * sizeof(cadastro));  // Aloca dinamicamente para o número de usuários

    if (*p == NULL) {
        printf("Erro ao alocar memória\n");
        return 1;
    }

    int posicao_struct = 0;
    char linha[255];

    while (fgets(linha, 255, arquivo)) {
        char *token = strtok(linha, ";");
        int contador = 0; // Variável para contar os campos (CPF, nome, senha)

        while (token != NULL) {
            if (contador == 0) {
                strcpy((*p)[posicao_struct].cpf, token); // Armazena o CPF
            } else if (contador == 1) {
                strcpy((*p)[posicao_struct].nome, token); // Armazena o nome
            } else if (contador == 2) {
                strcpy((*p)[posicao_struct].senha, token); // Armazena a senha
            }
            token = strtok(NULL, ";");
            contador++;
        }
        posicao_struct++; // Avança para o próximo usuário
    }

    fclose(arquivo);
    return 0;
}

// Função que salva os jogos comprados na biblioteca
void salvar_biblioteca(const char *cpf, const char *nome_jogo) {
    FILE *arquivo_bib = fopen("biblioteca_jogos.txt", "a");

    if (arquivo_bib == NULL) {
        printf("Erro ao abrir o arquivo de biblioteca!\n");
        return;
    }

    // Grava o CPF do usuário e o nome do jogo no arquivo
    fprintf(arquivo_bib, "%s;%s\n", cpf, nome_jogo);

    fclose(arquivo_bib);
}



// Função para o login, compara as informações recebidas do usuário com o arquivo.txt
void login(cadastro *p, int num_usuarios) {
    char nome[100];
    char cpf[12];
    char senha[10];
    int indice;

    while (1) {
        printf("|-----------------------------------|\n");
        printf("|        BEM-VINDO A LOJA DARK      |\n");
        printf("|-----------------------------------|\n");
        printf("|NOME: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';  // Remove o '\n' no final, se presente
        printf("|CPF: ");
        scanf("%s", cpf);
        getchar();
        printf("|SENHA: ");
        scanf("%s", senha);
        getchar();
        printf("|-----------------------------------|\n");

        int i, contador = 0;
        for (i = 0; i < num_usuarios; i++) {
            if (strcmp(cpf, p[i].cpf) == 0 && strcmp(nome, p[i].nome) == 0 && strcmp(senha, p[i].senha) == 0) {
                contador++;
                indice = i;
            }
        }

        if (contador != 0) {
            printf("|Usuário: %s\n", nome);
            menu(p, indice);
            getchar();  // Tirar o '\n' vindo da função
        } 
            printf("Usuário não cadastrado ou dados incorretos\n");
            printf("Tente novamente !!!\n");
        }
}

int main() {
    setlocale(LC_ALL, "portuguese");
    cadastro *pessoas; // Ponteiro para armazenar os dados dos usuários
    int num_usuarios = contar_usuarios();

    if (num_usuarios > 0) {
        if (achar_usuario(&pessoas) == 0) {
            login(pessoas, num_usuarios);
        }
        free(pessoas); // Libera a memória alocada após o uso
    } else {
        printf("Nenhum usuário encontrado no arquivo.\n");
    }

    system("pause");
    return 0;
}




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
        printf("| 4 - Consultar Biblioteca de Jogos |\n");
        printf("| 5 - Depositar Crédito             |\n");
        printf("| 6 - Sair                          |\n");
        printf("|-----------------------------------|\n");
        printf("Qual escolha você deseja: ");
        fgets(escolha_str, sizeof(escolha_str), stdin);
        escolha = atoi(escolha_str); // Converte a string para inteiro

        switch (escolha) {
            case 1:
                comprar_jogo(&carteira, p, indice);
                break;
            case 2:
                vender_jogo();
                break;
            case 3:
                adicionar_avaliacao();
                break;
            case 4:
                consultar_biblioteca_de_jogos(p, indice);
                break;
            case 5:
                depositar_credito(&carteira, indice);
                break;
            case 6:
                atualizacao_das_carteiras(carteira);
                printf("Ficando OFF...\n");
                system("pause");
                exit(0);
            default:
                printf("Essa opção não é válida!!\n");
        }
    }
}

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


// Função que compra os jogos
void comprar_jogo(float *carteira, cadastro *p, int indice) {
    int opcao; // Variável para armazenar a opção do usuário
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
                        salvar_biblioteca(p[indice].cpf, "Fort");  // Salva a compra na biblioteca do usuário
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
                        salvar_biblioteca(p[indice].cpf, "Hallo");  // Salva o jogo na biblioteca do usuário
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo The Last Of Us
            case 3:
                printf("Jogo escolhido: The Last Of Us | Tipo: Adv\n");
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
                        salvar_biblioteca(p[indice].cpf, "The Last Of Us");  // Salva o jogo na biblioteca
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
                        salvar_biblioteca(p[indice].cpf, "Minecraft");  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo Baldur's Gate
            case 5:
                printf("Jogo escolhido: Baldur's Gate | Tipo: RPG\n");
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
                        salvar_biblioteca(p[indice].cpf, "Baldu's Gate");  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo GTA V
            case 6:
                printf("Jogo escolhido: GTA V | Tipo: Ação\n");
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
                        printf("Compra realizada... com sucesso!!\n");
                        salvar_biblioteca(p[indice].cpf, "GTA V");  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo Cyberpunk 2077
            case 7:
                printf("Jogo escolhido: Cyberpunk 2077 | Tipo: Ação\n");
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
                        salvar_biblioteca(p[indice].cpf, "Cyberpunk 2077");  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo Rainbow Six Siege
            case 8:
                printf("Jogo escolhido: Rainbow Six Siege | Tipo: Tiro\n");
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
                        salvar_biblioteca(p[indice].cpf, "Rainbow Six Siege");  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo Enigma do Medo
            case 9:
                printf("Jogo escolhido: Enigma do Medo | Tipo: RPG\n");
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
                        salvar_biblioteca(p[indice].cpf, "Enigma do Medo");  // Salva o jogo na biblioteca
                        getchar();  // Absorve o '\n'
                        cont++;  // Incrementa para sair do loop
                        break;
                    } else {
                        printf("Senha incorreta!!\n");
                        break;
                    }
                }

            // Compra do Jogo Borderlands 3
            case 10:
                printf("Jogo escolhido: Borderlands 3 | Tipo: Tiro\n");
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
                        salvar_biblioteca(p[indice].cpf, "Borderlands 3");  // Salva o jogo na biblioteca
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



void vender_jogo() {
    printf("Hello World 2\n");
}

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

    printf("|Qual é a nota do jogo: ");
    scanf("%f", &nota);

    getchar(); // Tirar o '\n'

    fprintf(arquivo, "Nome: %s; Comentario: %s; Nota: %.2f\n", nome, comentario, nota); // Salva no arquivo, com esse formato escrito

    fclose(arquivo);
    printf("Atualização feita com sucesso!!\n");


}

void mostrar_arquivo(){
    FILE *arquivo;
    char linhas[255];

    arquivo = fopen("jogos.txt", "r"); // Abre o arquivo para ler

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    while (fgets(linhas, sizeof(linhas), arquivo)){ // Ele vai ler o arquivo linha por linha e vai mostrar no console
        printf("%s", linhas);
    }
    fclose(arquivo);
}

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
