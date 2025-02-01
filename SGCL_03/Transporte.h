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
typedef char Linha [1000];

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

//N� DA LISTA
typedef struct lt{
    Transporte t;
    struct lt *prox; 
}No;


//N� CABE�A
typedef struct {
    No *cabeca;
}LSLTrp;


//INICIALIA LISTA
void initLista(LSLTrp *l){
    l->cabeca == NULL;
}

//FUNCAO VAZIA
int vazia(LSLTrp *l){
    if(l->cabeca == NULL){
        printf("A lista est� vazia !\n");
        return 1;
    }
}

//LIMPAR TELA
void limpar_tela(){
    system("cls");
}



//VALIDA��ES  
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


//CRIA��O E MANIPULA��O ARQUIVOS TXT
//CRIAR ARQUIVO 
void file_transporte(Transporte *t){
    
    DIR caminho = ".\\Arquivos\\Transportes\\";//String que armazena o caminho 
    DIR nome_arquivo;
    
    sprintf(nome_arquivo, "%stransportes.txt", caminho);
    
    FILE *arquivo = fopen(nome_arquivo, "a+");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo !\n");
        return;
    }
        
    fprintf(arquivo ,"Id: %02d | Tipo: %s | Cap_Max: %d | Estado: %s | Terminal de Origem: %s | Terminal de Destino: %s\n", t->id, t->Tipo, t->Cap, t->Estado, t->Origem, t->Destino);
    
    printf("Arquivo de Texto criado com sucesso.");
    fclose(arquivo);
    return;
    
}


//IMPEDE A REPETI��O NO ID E CALCULA A QTD APARTIR DO N� DE LINHAS DO FICHEIRO
int quantidade(){
    //Cria uma String com o caminho do diret�rio do ficheiro
    DIR caminho = ".\\Arquivos\\Transportes\\";
    DIR nome_arquivo;
    
    //A string nome_arquivo recebe o "caminho" + o nome do ficheiro e a sua extens�o
    sprintf(nome_arquivo, "%stransportes.txt", caminho);
    
    //Cria um ficheiro de texto e se ele j� foi criado abre para leitura
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo !\n");
        return 0;
    }
    
    int n = 0;
    char c;
    
    //Recebe um caracter de cada vez e verifica se o caractere chegou ao final da linha com o EOF (End Of File)
    while((c = fgetc(arquivo)) != EOF){
    	//Se o caracter for igual ao barra linha add 1 a qtd
    	if(c == '\n'){
    		n++;
		}
	}
	fclose(arquivo);
	
	return n+1;
    
}

//CRIAR TRANSPORTE 
int criar_Transporte (Transporte *t){
    
    T:  
    printf("Tipo de Transporte: ");
    scanf("%[^\n]s", t->Tipo);
    getchar();
    
    if(validar_tipo(t) == 0){
        printf("Transporte inv�lido!\n");
        printf("Transportes disponiv�is:");
        printf("\n  -[Barco]\n  -[Comboio]\n  -[Caminhao]\n");
        goto T;
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
    
    T.id = quantidade();
    criar_Transporte(&T);
    
    No *novo = (No*)malloc(sizeof(No));
    novo->t = T;
    novo->prox =  NULL;
    
    return novo;
}


//FUN��ES PARA MOSTRAR
//MOSTRAR MENU
void Menu(){
    printf("\n");
    printf("=====================================\n");
    printf("============== SGCL =================\n");
    printf("=====================================\n");
    
    printf("== [1] - Cadastrar Transporte      ==\n");
    printf("== [2] - Mostrar Transporte        ==\n");
    printf("== [3] - Buscar Transporte por ID  ==\n");
    printf("== [0] - Sair                      ==\n");
    printf("=====================================\n");
    printf("ESCOLHA: ");
    
}

//MOSTRAR TRANSPORTES TXT
void show_t(){
	Linha l;
	DIR caminho = ".\\Arquivos\\Transportes\\";//String que armazena o caminho 
    DIR nome_arquivo;
    
    sprintf(nome_arquivo, "%stransportes.txt", caminho);
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("Nenhum transporte cadastrado !\n");
        sleep(2);
        limpar_tela();
        return;
    }
    
    while(fgets(l, sizeof(l), arquivo) != NULL)
    	printf("%s", l);
    	
    fclose(arquivo);
    return;
    
    
}

//MOSTRAR TRANSPORTE
void show_transporte(Transporte t){
	

    printf("\n\n");
    printf("ID [%02d]\n", t.id);
    printf("TIPO: %s\n", t.Tipo);
    printf("CAPACIDADE MAXIMA: %d TONELADAS\n", t.Cap);
    printf("ESTADO: %s\n", t.Estado);
    printf("TERMINAL DE PARTIDA: %s\n", t.Origem);
    printf("TERMINAL DE CHEGADA: %s\n", t.Destino);
    printf("\n");
}

void busca_01(LSLTrp *l, int id){
	int qtd = quantidade();
        
    
    if(id < 0 || id > qtd){
        printf("\nPosi��o inv�lida.\n");
        sleep(2);
        limpar_tela();
        return ;
    }
	
    No *aux = l->cabeca;
    while(aux->prox != NULL){
        if(aux->t.id == id){
            printf("\n\n");
    		printf("ID [%02d]\n", aux->t.id);
   			printf("TIPO: %s\n", aux->t.Tipo);
    		printf("CAPACIDADE MAXIMA: %d TONELADAS\n", aux->t.Cap);
    		printf("ESTADO: %s\n", aux->t.Estado);
    		printf("TERMINAL DE PARTIDA: %s\n", aux->t.Origem);
    		printf("TERMINAL DE CHEGADA: %s\n", aux->t.Destino);
    		printf("\n");
            return;
        }
        aux = aux->prox;
    }
    printf("Transporte com ID %d n�o encontrado.\n", id);
}

void show_all(LSLTrp *l){

    if(l->cabeca == NULL){
        printf("Nenhum transporte cadastrado !\n");
        sleep(3);
        limpar_tela();
        return;
    }
    
    No *aux = l->cabeca;
    while(aux->prox != NULL){
        aux = aux->prox;
        show_transporte(aux->t);
    }
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
        printf("\nPosi��o inv�lida.\n");
        sleep(2);
        limpar_tela();
        return ;
    }
    
    No *aux = l->cabeca;
    
    while(aux != NULL){
        
        if(id == aux->t.id){
            printf("Transporte encontrado\n");
            show_transporte(aux->t);
            return;
        }
        aux = aux->prox;
    }
}
