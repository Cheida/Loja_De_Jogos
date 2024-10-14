#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int indice;
int i = 0;
float carteira[10]={};

// struct que armazena o cadastro dos usuarios
typedef struct cadastro {
    char cpf[12];
    char nome[100];
    char senha[10];
} cadastro;

// struct que armazena o jogos disponíveis
struct jogo {
    char nome[50];
    float preco;
    int quantidade;
};

// Funções Gerais
void iniciacao_aquivo(float *carteira);
void carrega_jogos(struct jogo **jogos, int *num_jogos);
void depositar_creditos(float *carteira);
void comprar_jogo();
void vender_jogo();
void adicionar_jogo();
void remover_jogo();
void consultar_biblioteca_de_jogos();
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

// Função para o login, compara as informações recebidas do usuário com o arquivo.txt
void login(cadastro *p, int num_usuarios, int *indice) {
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
	*indice = contador;
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
	struct jogo *jogos = NULL;
    int num_jogos = 0; 
    cadastro *pessoas; // Ponteiro para armazenar os dados dos usuários
    int num_usuarios = contar_usuarios();

    if (num_usuarios > 0) {
        if (achar_usuario(&pessoas) == 0) {
	    carrega_jogos(&jogos, &num_jogos);		
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
        printf("|         Bem-Vindo a Loja          |\n");
        printf("|-----------------------------------|\n");
        printf("| 1 - Comprar Jogo                  |\n");
        printf("| 2 - Vender Jogo                   |\n");
        printf("| 3 - Adicionar Jogo                |\n");
        printf("| 4 - Consultar Biblioteca de Jogos |\n");
	     printf("| 5 -      Depositar Créditos      |\n");
        printf("| 6 - Sair                          |\n");
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
                adicionar_jogo();
                break;
            case 4:
                consultar_biblioteca_de_jogos();
                break;
		case 5:
			depositar_creditos(carteira);
			break;
            case 6:
                printf("Ficando OFF...\n");
                system("pause");
                exit(0);
            default:
                printf("Essa opção não é válida!!\n");
        }
    }
}

// Carrega os jogos existentes no arquivo jogos.txt

void carrega_jogos(struct jogo **jogos, int *num_jogos){
	int i = 0;
	FILE *file = fopen("jogos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de jogos.\n");
        return 0;
    }


    while (fscanf(file, "%s %f %d", jogos[i]->nome, &jogos[i]->preco, &jogos[i]->quantidade) != EOF) {
    	i++;
    }
    fclose(file);
    return i;
};
void atualiza_credito(float*carteira){
	FILE *carteirafile;

	carteirafile = fopen("creditos.bin","wb");
     size_t escrevendo = fwrite(carteira, sizeof(float),10,carteirafile);
     fclose(carteirafile);
}
void iniciacao_arquivo(float*carteira){
	FILE *carteirafile;
	
	carteirafile = fopen("creditos.bin","rb");
     size_t lendo = fread(carteira, sizeof(float),10,carteirafile);
     fclose(carteirafile);
}

void depositar_creditos(float*carteira){
	
    	float valor;
	while(1){
		printf("Quanto deseja depositar de créditos (ou 0 para não depositar): ");
    		scanf("%f", &valor);
		if (valor < 0){
			printf("Digite um valor válido!\n");
		}
		else {
			carteira[indice] += valor;	
			break
		}
		
	}
	atualiza_credito(carteira);
	
}
void comprar_jogo() {
		printf("Hello Wordl 1\n");
}


void vender_jogo() {
    printf("Hello World 2\n");
}

void adicionar_jogo() {
    FILE *arquivo;


    char nome[255];
    char tipo[255];
    float valor;

    arquivo = fopen("jogos.txt", "a"); // Abre o arquivo jogos.txt para atualizar

    if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo!\n");
		exit(1);
	}

	printf("|Qual é o nome do jogo: ");
	scanf("%s", &nome);

	printf("|Qual é o tipo do jogo: ");
	scanf("%s", &tipo);

	printf("|Qual é o valor do jogo: ");
	scanf("%f", &valor);

	getchar(); // Tirar o '\n'

	fprintf(arquivo, "Nome: %s; tipo: %s; valor: %.2f\n", nome, tipo, valor); // Salva no arquivo, com esse formato escrito

	fclose(arquivo);
	printf("Atualização feita com sucesso!!\n");


}

void remover_jogo() {
    printf("Hello World 4\n");
}

void consultar_biblioteca_de_jogos() {
    printf("Hello World 5\n");
}
// <<<<<<< Cheida-patch-1-FunÃ§Ã£o-Adicionar-Jogos

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



