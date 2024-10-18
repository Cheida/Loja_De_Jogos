#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define NUM_OF_USERS 10
int indice;

float carteira[NUM_OF_USERS]={};

// struct que armazena o cadastro dos usuarios
typedef struct cadastro {
    char cpf[12];
    char nome[100];
    char senha[10];
} cadastro;

// struct que armazena o jogos dispon�veis
typedef struct jogo {
    char nome[50];
    char tipo [10];
    float preco;
} jogo;

// Fun��es Gerais
void depositar_credito(float *carteira);
void iniciacao_arquivos(float *carteira);
void atualizacao_das_carteiras(float *carteira);
void comprar_jogo();
void vender_jogo();
void adicionar_avaliacao();
void remover_jogo();
void consultar_biblioteca_de_jogos();
void menu();
void mostrar_arquivo();

// Fun��o para limpar o conte�do, preenchendo com '\0'
void limparstring(char *array) {
    int i;
    for (i = 0; i < 255; i++) {
        array[i] = '\0';
    }
}

int quant_jogos(){
    FILE *arquivo;
    arquivo = fopen("jogos.txt", "r");

    int cont = 0;
    char linha[255];
    while(fgets(linha, sizeof(linha), arquivo)){
        cont++;
    }
    fclose(arquivo);
    return cont;
}
// Conta quantos usu�rios existem no arquivo, retornando a quantidade de linhas
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

int carregar_jogos(jogo **j){
    FILE *arquivo;
    arquivo = fopen("jogos.txt","r");

    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    int num_jogos = quant_jogos();
    *j = (jogo *)malloc(num_jogos * sizeof(jogo));

    if (*j == NULL){
        printf("Erro ao alocar mem�ria\n");
        return 1;
    }
    int posicao_struct = 0;
    char linha[255];

    while (fgets(linha, 255, arquivo)) {
        char *token = strtok(linha, ";");
        int cont = 0; // Vari�vel para contar os campos (nome, tipo, preco)

        while (token != NULL) {
            if (cont == 0) {
                strcpy((*j)[posicao_struct].nome, token); // Armazena o nome
            } else if (cont == 1) {
                strcpy((*j)[posicao_struct].tipo, token); // Armazena o tipo
            } else if (cont == 2) {
                (*j)[posicao_struct].preco = atof(token); // Armazena a preco
            }
            token = strtok(NULL, ";");
            cont++;
        }
        posicao_struct++; // Avan�a para o pr�ximo jogo
    }

}

// Encontra os usu�rios no arquivo e os carrega
int achar_usuario(cadastro **p) {
    FILE *arquivo;
    arquivo = fopen("usuarios.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    int num_usuarios = contar_usuarios();
    *p = (cadastro *)malloc(num_usuarios * sizeof(cadastro));  // Aloca dinamicamente para o n�mero de usu�rios

    if (*p == NULL) {
        printf("Erro ao alocar mem�ria\n");
        return 1;
    }

    int posicao_struct = 0;
    char linha[255];

    while (fgets(linha, 255, arquivo)) {
        char *token = strtok(linha, ";");
        int contador = 0; // Vari�vel para contar os campos (CPF, nome, senha)

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
        posicao_struct++; // Avan�a para o pr�ximo usu�rio
    }

    fclose(arquivo);
    return 0;
}

// Fun��o para o login, compara as informa��es recebidas do usu�rio com o arquivo.txt
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
                indice = i;
            }
        }

        if (contador != 0) {
            printf("|Usu�rio: %s\n", nome);
            menu(p);
            getchar();  // Tirar o '\n' vindo da fun��o
        } 
            printf("Usu�rio n�o cadastrado ou dados incorretos\n");
            printf("Tente novamente !!!\n");
        }
    }


int main() {
    setlocale(LC_ALL, "portuguese");
    cadastro *pessoas; // Ponteiro para armazenar os dados dos usu�rios
    int num_usuarios = contar_usuarios();
    jogo *jogos;
    int num_jogos = quant_jogos();

    if (num_usuarios > 0) {
        if (achar_usuario(&pessoas) == 0) {
            iniciacao_arquivos(carteira);
            carregar_jogos(&jogos);
            login(pessoas, num_usuarios);
        }
        free(pessoas); // Libera a mem�ria alocada ap�s o uso
    } else {
        printf("Nenhum usu�rio encontrado no arquivo.\n");
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
        printf("|         Bem-Vindo a Loja          |\n");
        printf("|-----------------------------------|\n");
        printf("| 1 - Comprar Jogo                  |\n");
        printf("| 2 - Vender Jogo                   |\n");
        printf("| 3 - Adicionar Avalia��o do Jogo   |\n");
        printf("| 4 - Consultar Biblioteca de Jogos |\n");
        printf("| 5 - Depositar Cr�dito             |\n");
        printf("| 6 - Sair                          |\n");
        printf("|-----------------------------------|\n");
        printf("Qual escolha voc� deseja: ");
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
                adicionar_avaliacao();
                break;
            case 4:
                consultar_biblioteca_de_jogos();
                break;
            case 5:
                depositar_credito(carteira);
                break;
            case 6:
                atualizacao_das_carteiras(carteira);
                printf("Ficando OFF...\n");
                system("pause");
                exit(0);
            default:
                printf("Essa op��o n�o � v�lida!!\n");
        }
    }
}

void depositar_credito(float *carteira){
    float valor;

    while(1){
        printf("Quanto deseja depositar (ou 0 para n�o depositar): ");
        scanf("%f", &valor);

        if (valor < 0){
            printf("Valor inv�lido!!\n");
        }
        else{
            carteira[indice] += valor;
            printf("Dep�sito realizado com sucesso!!\n");
            getchar();
            break;
        }
    }

}



void comprar_jogo() {
        printf("Hello Wordl 1\n");
}


void vender_jogo() {
    printf("Hello World 2\n");
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

    printf("|Qual � o nome do jogo: ");
    scanf("%s", &nome);

    printf("|Como foi a sua experi�ncia: ");
    scanf("%s", &comentario);

    printf("|Qual � a nota do jogo: ");
    scanf("%f", &nota);

    getchar(); // Tirar o '\n'

    fprintf(arquivo, "Nome: %s; Comentario: %s; Nota: %.2f\n", nome, comentario, nota); // Salva no arquivo, com esse formato escrito

    fclose(arquivo);
    printf("Atualiza��o feita com sucesso!!\n");


}

void remover_jogo() {
    printf("Hello World 4\n");
}

void consultar_biblioteca_de_jogos() {
    printf("Hello World 5\n");
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

void atualizacao_das_carteiras(float *carteira){
    FILE *carteirafile;

    carteirafile = fopen("creditos.bin","wb");

     size_t escrevendo = fwrite(carteira, sizeof(float),10,carteirafile);
     fclose(carteirafile);
}

void iniciacao_arquivos(float *carteira){
    FILE *carteirafile;

    carteirafile = fopen("creditos.bin","rb");

    if (carteirafile == NULL){
        printf("Erro ao abrir o arquivo\n");
    }

     size_t lendo = fread(carteira, sizeof(float),10,carteirafile);
     fclose(carteirafile);
}
