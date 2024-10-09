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
void comprar_jogo();
void vender_jogo();
void adicionar_jogo();
void remover_jogo();
void consultar_biblioteca_de_jogos();
void menu();

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

// Função para o login, compara as informações recebidas do usuário com o arquivo.txt
void login(cadastro *p, int num_usuarios) {
    char nome[100];
    char cpf[12];
    char senha[10];

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
            }
        }

        if (contador != 0) {
            printf("|Usuário: %s\n", nome);
            menu(p);
            getchar();  // Tirar o '\n' vindo da função
            char letra;
            printf("|Deseja sair(s/n)?|\n");
            scanf(" %c", &letra);
            getchar();
            if (letra == 's') {
                break;
            } else {
                continue;
            }
        } else {
            printf("Usuário não cadastrado ou dados incorretos\n");
            printf("Tente novamente !!!\n");
        }
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
void menu(cadastro *p) {
    int escolha;
    char escolha_str[10];

    while (1) {
        printf("|-----------------------------------|\n");
        printf("|         Bem-Vindo da Loja         |\n");
        printf("|-----------------------------------|\n");
        printf("| 1 - Comprar Jogo                  |\n");
        printf("| 2 - Vender Jogo                   |\n");
        printf("| 3 - Consultar Biblioteca de Jogos |\n");
        printf("| 4 - Sair                          |\n");
        printf("|-----------------------------------|\n");
        printf("Qual escolha você deseja: ");
        fgets(escolha_str, sizeof(escolha_str), stdin);
        escolha = atoi(escolha_str); // Converte a string para inteiro

        switch (escolha) {
            case 1:
                comprar_jogo();
                break;
            case 2:
                vender_jogo();
                break;
            case 3:
                consultar_biblioteca_de_jogos();
                break;
            case 4:
                printf("Ficando OFF...\n");
                exit(0);
            default:
                printf("Essa opção não é válida!!\n");
        }
    }
}

void comprar_jogo() {
    printf("Hello World 1\n");
}

void vender_jogo() {
    printf("Hello World 2\n");
}

void adicionar_jogo() {
    printf("Hello World 3\n");
}

void remover_jogo() {
    printf("Hello World 4\n");
}

void consultar_biblioteca_de_jogos() {
    printf("Hello World 5\n");
}

