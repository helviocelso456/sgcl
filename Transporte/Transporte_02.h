#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<windows.h>
#define BARCO 20000
#define CAMINHAO 45
#define COMBOIO 20000

typedef char String [50];
typedef char DIR [200];

//TIPO DE DADO TRANSPORTE
typedef struct transporte{
	int id;
	int Cap;
	String Tipo;
	String Estado;
	String Origem, Destino;
	//Terminal Origem;
	//Terminal Destino;
}Transporte;

//NÓ DA LISTA
typedef struct lt{
	Transporte t;
	struct lt *prox; 
}No;


//NÓ CABEÇA
typedef struct {
	No *cabeca;
}LSLTrp;


//INICIALIA LISTA
void initLista(LSLTrp *l){
	l->cabeca = NULL;
}

//FUNCAO VAZIA
int vazia(LSLTrp *l){
	if(l->cabeca == NULL){
		printf("A lista está vazia !\n");
		return 1;
	}
}

//QUANTIDADE
int quantidade(LSLTrp *l){
	int i = 0;
	No *aux = l->cabeca;
	
	while(aux != NULL){
		i++;
		aux = aux->prox;
		
	}
	
	return i;
}

//LIMPAR TELA
void limpar_tela(){
	
	system("cls");
}



//VALIDAÇÕES  
//VALIDAR TIPOS DE TRANSPORTES
int validar_tipo(Transporte *t){	

	if(strcmp(t->Tipo, "Barco") == 0){
		t->Cap = BARCO;	
		return 1;
	}	
	
	if(strcmp(t->Tipo, "Caminhao") == 0 ){
		t->Cap = CAMINHAO;
		return 1;
	}
	
	if(strcmp(t->Tipo, "Comboio") == 0){
		t->Cap = COMBOIO;	
		return 1;
	}
	
	return 0;
}

//VALIDAR ESTADOS DE TRANSPORTE
int validar_estado(Transporte *t){	

	if(strcmp(t->Estado, "Aguardando") == 0){	
		return 1;
	}	
	
	if(strcmp(t->Estado, "Carregando") == 0 ){
		return 2;
	}
	
	if(strcmp(t->Estado, "Retirando") == 0){	
		return 3;
	}
	
	return 0;
}

//CRIAR ARQUIVO TRANSPORTE
void file_transporte(Transporte *t){
	
	DIR caminho = ".\\Arquivos\\Transportes\\";
	DIR n = "Transporte_";
	DIR nome_arquivo;
	
	sprintf(nome_arquivo, "%s%s[0%d].txt", caminho, n, t->id);
	
	FILE *arquivo = fopen(nome_arquivo, "w");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo !\n");
	}
		
	printf("\n\n");
	fprintf(arquivo, "ID [0%d]\n", t->id);
	fprintf(arquivo, "TIPO: %s\n", t->Tipo);
	fprintf(arquivo, "CAPACIDADE MAXIMA: %d TONELADAS\n", t->Cap);
	fprintf(arquivo, "ESTADO: %s\n", t->Estado);
	fprintf(arquivo, "TERMINAL DE PARTIDA: %s\n", t->Origem);
	fprintf(arquivo, "TERMINAL DE CHEGADA: %s\n", t->Destino);
	
	printf("Arquivo de Texto criado com sucesso.");
	fclose(arquivo);
	return;
	
}

//CRIAR TRANSPORTE 
int criar_Transporte (Transporte *t){
	
	T:	
	printf("Tipo de Transporte: ");
	scanf("%[^\n]s", t->Tipo);
	getchar();
	
	if(validar_tipo(t) == 0){
		printf("Transporte inválido!\n");
		printf("Transportes disponivéis:");
		printf("\n  -[Barco]\n  -[Comboio]\n  -[Caminhao]\n");
		goto T;
	}
		
	E:
	printf("Estado: ");
	scanf("%[^\n]s", t->Estado);
	getchar();
	
	if(validar_estado(t) == 0){
		printf("Estado inválido!\n");
		printf("Estados disponivéis:\n");
		printf("\n  -[Aguardando]\n  -[Carregando]\n  -[Retirando]\n");
		goto E;
	}
	
	printf("Terminal de Partida: ");
	scanf("%[^\n]s", t->Origem);
	getchar();
	
	printf("Terminal de Chegada: ");
	scanf("%[^\n]s", t->Destino);
	getchar();

	file_transporte(t);
	
	return 1;		
}

//CRIAR NO
No* criar_No(LSLTrp *l){
	Transporte T;
	
	T.id = quantidade(l);
	criar_Transporte(&T);
	
	No *novo = (No*)malloc(sizeof(No));
	novo->t = T;
	novo->prox =  NULL;
	
	return novo;
}


//FUNÇÕES PARA MOSTRAR
//MOSTRAR MENU
void Menu(){
	printf("\n");
	printf("=============================\n");
	printf("============ SGCL ===========\n");
	printf("=============================\n\n");
	
	printf("[1] - Cadastrar Transporte\n");
	printf("[2] - Mostrar Transporte\n");
	printf("[3] - Buscar Transporte por ID\n");
	printf("[0] - Sair\n");
	printf("ESCOLHA: ");
	
}

//MOSTRAR TRANSPORTE
void show_transporte(LSLTrp *l){

	if(l->cabeca == NULL){
		printf("Nenhum transporte cadastrado !\n");
		sleep(3);
		limpar_tela();
		return;
	}
	
	No *aux = l->cabeca;
	while(aux->prox != NULL){
		aux = aux->prox;
		
		printf("\n\n");
		printf("ID [0%d]\n", aux->t.id);
		printf("TIPO: %s\n", aux->t.Tipo);
		printf("CAPACIDADE MAXIMA: %d TONELADAS\n", aux->t.Cap);
		printf("ESTADO: %s\n", aux->t.Estado);
		printf("TERMINAL DE PARTIDA: %s\n", aux->t.Origem);
		printf("TERMINAL DE CHEGADA: %s\n", aux->t.Destino);
	}
	return;
	
}

//Inserir no na lista
int inserir(LSLTrp *l){
	No *novo = (No*)malloc(sizeof(No));
	novo = criar_No(l);
	novo->prox = l->cabeca;
	l->cabeca = novo;
	
	printf("\nNo inserido na lista com sucesso");
	return 1;
}

void busca(LSLTrp *l, int id){
	
	int qtd = quantidade(l);
		
	
	if(id < 0 || id > qtd){
		printf("\nPosição inválida.\n");
		sleep(2);
		limpar_tela();
		return ;
	}
	
	No *aux = l->cabeca;
	
	while(aux != NULL){
		aux = aux->prox;
		if(id == aux->t.id){
			printf("Valor encontrado\n");
		}
	}
	
	
}


