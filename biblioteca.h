#ifndef Biblioteca_h
#define Biblioteca_h

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct que armazena o cadastro dos usuarios
typedef struct cadastro {
  char cpf[12];
  char nome[100];
  char senha[10];
} cadastro;
// Funções Gerais
int salvar_biblioteca(const char *cpf, const char *nome_jogo, int trasacao);
int contar_usuarios();
int achar_usuario(cadastro **p);
void depositar_credito(float *carteira, int indice);
void iniciacao_arquivos(float *carteira);
void atualizacao_das_carteiras(float *carteira);
void comprar_jogo(float *carteira, cadastro *p, int indice);
void vender_jogo(cadastro *p, int indice, float *carteira);
void adicionar_avaliacao();
void consultar_biblioteca_de_jogos(cadastro *p, int indice);
void login(cadastro *p, int num_usuarios);
void menu();
void mostrar_arquivo();
void mostrar_avaliacao();

#endif
