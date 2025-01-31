#ifndef Terminais_H
#define Terminais_H
//Evita que o cabeçalho seja incluido varias vezes no projeto
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<windows.h>

//Definindo TDA
typedef char String [50];
typedef char DIR [200];

//Definindo a estrutura
typedef struct 
{
   int id;
   String localizacao;
   int capacidadeMaxima;
   int cargasAtuais;

}TERMINAL; 

//Definindo o No
typedef struct no
{
   TERMINAL t;
   struct no *prox;
}NO;

//Definindo o cabeça
typedef struct 
{
    NO *cabeca;
    NO *ultimo; 
}LISTA;

//Inicializando a lista
void inicializarTerminal(LISTA *l)
{
   l->cabeca = NULL;
   l->ultimo = NULL;
}

int ListaVazia(LISTA *l)
{
    if(l->cabeca == NULL)
    {
        return 1;
    }

   return 0;
}

//Definindo a quantidade de terminais
int qtdTerminais(LISTA *l)
{
    int qtd = 0;
    NO *aux = l->cabeca;
    while(aux != NULL)
    {
        qtd++;
        aux = aux->prox;

    }
    return qtd;
}

//Função para limpar a tela
void limparTela()
{
    system("cls");
}

//Definindo a listagem de terminais
 void ListarTerminais(LISTA *l)
{  
   limparTela();
   NO *aux = l->cabeca;
   while(aux != NULL)
   {
      printf("Id: %d | Localização: %s, Capacidade Máxima: %d, Cargas Atuais: %d\n",aux->t.id,aux->t.localizacao,aux->t.capacidadeMaxima,aux->t.cargasAtuais);
      aux = aux->prox;
   }
 
}

//Definindo a busca sequencial por ids
int BuscaSequencial(LISTA *l, int id)
{
    NO *aux = l->cabeca;
    while(aux != NULL)
   {
      if(id == aux->t.id)
      {
         printf("Id: %d | Localização: %s, Capacidade Máxima: %d, Cargas Atuais: %d\n",aux->t.id,aux->t.localizacao,aux->t.capacidadeMaxima,aux->t.cargasAtuais);
         return id;
      }
      aux = aux->prox;
   }
    return 0;
}
//Função para criar o arquivo de texto
//CRIAR ARQUIVO TRANSPORTE
void file_terminal(TERMINAL *t){
	//Caminho do arquivo
	DIR caminho = ".\\Arquivos\\Terminais\\";
	//Prefixo do nome do arquivo
	DIR n = "Terminais_";
	//Vai armazenar a string com o prefixo, caminho e id do transporte
	DIR nome_arquivo;
	//Responsavel por formatar a string
	sprintf(nome_arquivo, "%s%s[0%d].txt", caminho, n, t->id);
	//Tipo file para criar o documento em modo de escrita
	FILE *arquivo = fopen(nome_arquivo, "w");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo !\n");
	}
	//Come�a a escrita do documento	
	printf("\n\n");
	fprintf(arquivo, "ID [0%d]\n", t->id);
	fprintf(arquivo, "TIPO: %s\n", t->localizacao);
	fprintf(arquivo, "CAPACIDADE MAXIMA: %d TONELADAS\n", t->capacidadeMaxima);
	fprintf(arquivo, "Número de Cargas Atuais: %d\n", t->cargasAtuais);
	
	
	printf("Arquivo de Texto criado com sucesso.");
	//Encerra do documento
	fclose(arquivo);
	return;
	
}

//Registo de terminais de maneira sequencial
int registoTerminais(LISTA *l, TERMINAL t)
{
   //Criamos no no
   NO *no = (NO*) malloc(sizeof(NO));
   //Definimos o prox do no como null pra evitar certos comportamentos
   no->prox = NULL;
   //Atribuindo o terminal ao no
   no->t = t;
   if(l->cabeca == NULL)
   {
      l->cabeca = no;
      l->ultimo = no;
      //Mandando pro arquivo de Texto
      file_terminal(&t);
   }

   else
   {
       //Primeiro definimos que o prox do ant e o no
       l->ultimo->prox = no;
       //Depois definimos que o ultimo e o no
       l->ultimo = no;
       //Mandando pro arquivo de texto
       file_terminal(&t);
   }

   return 0;
}


#endif