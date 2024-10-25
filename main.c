#include "biblioteca.h"

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
