#ifndef Transporte_H
#define Transporte_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<windows.h>
#define BARCO 20000
#define CAMINHAO 45
#define COMBOIO 20000
//Definindo TDA
typedef char String [50];
typedef char DIR [200];
typedef char Linha [1000];
//TIPO DE DADO TRANSPORTE
typedef struct transporte{
    int id;
    String Tipo;
    int Cap;
    String Estado;
    int Origem, Destino;
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
    
    return 0;
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
void init_estado(Transporte *t){  
	String  estado = "Aguardando";
	
	strcpy(t->Estado, estado);
	return;
}


//CRIAÇÃO E MANIPULAÇÃO ARQUIVOS TXT
//CRIAR ARQUIVO 
void file_transporte(Transporte *t){
    
    DIR caminho = ".\\Transporte\\Arquivos\\Transportes\\";//String que armazena o caminho 
    DIR nome_arquivo;
    
    sprintf(nome_arquivo, "%stransportes.txt", caminho);
    
    FILE *arquivo = fopen(nome_arquivo, "a+");
    if(arquivo == NULL){
        //printf("Erro ao abrir o arquivo !\n");
        return;
    }
        
    fprintf(arquivo ,"%02d|%s|%d|%s|%d|%d\n", t->id, t->Tipo, t->Cap, t->Estado, t->Origem, t->Destino);
    
    //printf("Arquivo de Texto criado com sucesso.");
    fclose(arquivo);
    return;
    
}

void update_transporte(LSLTrp *l){
    
    DIR caminho = ".\\Transporte\\Arquivos\\Transportes\\";//String que armazena o caminho 
    DIR nome_arquivo;
    
    sprintf(nome_arquivo, "%stransportes.txt", caminho);
    
    FILE *arquivo = fopen(nome_arquivo, "w");
    if(arquivo == NULL){
        //printf("Erro ao abrir o arquivo !\n");
        return;
    }
        
    //Auxiliar
    No *aux = l->cabeca;
    while( aux != NULL)
    {
    	fprintf(arquivo ,"%02d|%s|%d|%s|%d|%d\n", aux->t.id, aux->t.Tipo, aux->t.Cap, aux->t.Estado, aux->t.Origem, aux->t.Destino);
    	aux = aux->prox;
	}
    
    fclose(arquivo);
    printf("Transportes Atualizados com sucesso.\n");    
}


//IMPEDE A REPETIÇÃO NO ID E CALCULA A QTD APARTIR DO Nº DE LINHAS DO FICHEIRO
int quantidade(){
    
	//Cria uma String com o caminho do diretório do ficheiro
    DIR caminho = ".\\Transporte\\Arquivos\\Transportes\\";
    DIR nome_arquivo;
    
	int n = 0;
    char c;
    
    //A string nome_arquivo recebe o "caminho" + o nome do ficheiro e a sua extensão
    sprintf(nome_arquivo, "%stransportes.txt", caminho);
    
    //Cria um ficheiro de texto e se ele já foi criado abre para leitura
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        //printf("Erro ao abrir o arquivo !\n");
        return n;
    }
    
    
    //Recebe um caracter de cada vez e verifica se o caractere chegou ao final da linha com o EOF (End Of File)
    while((c = fgetc(arquivo)) != EOF){
    	//Se o caracter for igual ao barra linha add 1 a qtd
    	if(c == '\n'){
    		n++;
		}
	}
	fclose(arquivo);
	
	return n;
    
}

//CRIAR TRANSPORTE 
int criar_Transporte (Transporte *t){
    
    //Insere o id consoante ao numero de linhas contido no arquivo txt
    t->id = quantidade() + 1;
    
    T:  
    printf("Tipo de Transporte: ");
    scanf("%[^\n]s", t->Tipo);
    getchar();
    
    if(validar_tipo(t) == 0){
        printf("Transportes disponivéis:");
        printf("\n  -[Barco]\n  -[Comboio]\n  -[Caminhao]\n");
        goto T;
    }
    
	//Coloca o estado por default em "Aguardando"
    init_estado(t);
    //Define a origem e destino default que é 0
	t->Origem = 0;
	t->Destino = 0;
    file_transporte(t);
    return 1;       
}

//CRIAR NO
No* criar_No(LSLTrp *l){
    Transporte T;
    
    criar_Transporte(&T);
    
    No *novo = (No*)malloc(sizeof(No));
    novo->t = T;
    novo->prox =  NULL;
    
    return novo;
}

void recriarTransporte(LSLTrp *lT)
{
	//Para pegar as linhas do arquivo
	Linha l;
	//Caminho do arquivo
	DIR caminho = ".\\Transporte\\Arquivos\\Transportes\\";
	//Vai armazenar o caminho e o nome
    DIR nome_arquivo;
    //Transporte
    Transporte t;
    //Juntando
    sprintf(nome_arquivo, "%stransportes.txt", caminho);
    
    //Abrindo o arquivo
    FILE *arquivo = fopen(nome_arquivo, "r");
    
    //Verifica se o arquivo foi aberto
    if(arquivo == NULL)
	{ 
	  printf("Erro ao abrir o arquivo"); 
	  return; 
	}
    
    //Percorre o arquivo
    while(fgets(l, sizeof(l), arquivo) != NULL)
    {   
       //Caso o caracter do final da linha seja \n ele remove
    	if (l[strlen(l) - 1] == '\n') {
            l[strlen(l) - 1] = '\0';
        }
        
        // Dividir a linha usando o delimitador |
        char *token = strtok(l, "|"); //Pega a primeira parte da linha
        if(token != NULL)
		{
		  t.id = atoi(token);
		} //Pegou o id
        
        token = strtok(NULL, "|"); //Para pegar a outra pare
        if(token != NULL) 
		{
		  strcpy(t.Tipo, token);
		} //Pegou o tipo
        
        token = strtok(NULL, "|"); //Passou para a outra parte
        if(token != NULL) // Pegou a capacidade
        {   
          t.Cap = atoi(token);
		} //Pegou a capacidade
		    
        token = strtok(NULL, "|"); //Passou para a outra parte
        if(token != NULL)
		{   
		  strcpy(t.Estado, token);
		} // Pegou o estado
	
		
        token = strtok(NULL, "|"); //Passou para a outra parte
        if(token != NULL)
        {   
          t.Origem = atoi(token);
		} // Pegou a origem
		
        token = strtok(NULL, "|"); //Passou para a outra parte
        if(token != NULL)
		{   
		  t.Destino = atoi(token);
		}
		// Pegou o destino
        
        //Recria a lista
        recriarNoTransporte(lT,t);
	}
	
	//Encerra o arquivo, boas práticas
	fclose(arquivo);
}

int recriarNoTransporte(LSLTrp *l, Transporte t){
   
   //Para Validar a inicialização
   if (l == NULL) {
        printf("Erro: Lista não inicializada!\n");
        return 0;
    }
    
   No *novo = (No*) malloc(sizeof(No));
   if(novo == NULL)
   {
   	 printf("Erro ao alocar memória");
   	 return 0;
   }
   novo->prox = NULL; //Evita comportamentos inesperados
   novo->t = t; //Adiciona o conteudo
   
   //Quer dizer que a lista esta vazia
   if(l->cabeca == NULL)
   {
   	  l->cabeca = novo;
   }
   
   else
   {  
      //Usamos um auxiliar para pegar o ultimo elemento
   	  No *aux = l->cabeca;
   	  
   	  //Percorrendo a lista
   	  while(aux->prox != NULL)
   	  {
   	  	  aux = aux->prox;
	  }
	  
	  //Após percorrer
	  aux->prox = novo; //Adiciona na ultima pos
   	  
   }
    
    return 1;
}

No *busca(LSLTrp *l, int id){
    limpar_tela();
    int qtd = quantidade(l);
        
    if(id < 0 || id > qtd){
        printf("Identificador Invalido\n");
        sleep(2);
        limpar_tela();
        return NULL;
    }
    
    No *aux = l->cabeca;
    
    while(aux != NULL && aux->t.id != id){
       aux = aux->prox;
    }
    
    if(aux->t.id == id)
    {
    	printf("Transporte Encontrado!!\n");
    	printf("\n\n");
        printf("ID %d| ", aux->t.id);
        printf("TIPO: %s, ", aux->t.Tipo);
        printf("CAPACIDADE MAXIMA: %d TONELADAS, ", aux->t.Cap);
        printf("ESTADO: %s, ", aux->t.Estado);
        printf("TERMINAL DE PARTIDA: %d, ", aux->t.Origem);
        printf("TERMINAL DE CHEGADA: %d", aux->t.Destino);
        printf("\n");
        return aux;
	}
	
	return NULL;
}


//FUNÇÕES PARA MOSTRAR
//MOSTRAR MENU
void Menu(LSLTrp *lTransporte){
	int op2,id;
	Transporte t;
    printf("\n");
    printf("=====================================\n");
    printf("============== SGCL =================\n");
    printf("=====================================\n");
    
    printf("== [1] - Cadastrar Transporte      ==\n");
    printf("== [2] - Mostrar Transporte        ==\n");
    printf("== [3] - Buscar Transporte por ID  ==\n");
    printf("== [0] - Voltar                    ==\n");
    printf("=====================================\n");
    printf("ESCOLHA: ");
    scanf("%d",&op2);
    switch(op2)
    {
    	case 1:
    	inserir(lTransporte);	
        break;
        
        case 2:
        show_all(lTransporte);    
        break;
        
        case 3:
        printf("Insira o ID: ");
		scanf("%d",&id);
		busca(lTransporte, id);   
        break;
        
        default:
        printf("Insira uma opção válida");
		sleep(2);
		limpar_tela();
	}
    
}

//MOSTRAR TODOS TRANSPORTES TXT
void show_t(){
	Linha l;
	DIR caminho = ".\\Transporte\\Arquivos\\Transportes\\";//String que armazena o caminho 
    DIR nome_arquivo;
    
    //nome_arquivo recebe o caminho e tbm o ficheiro txt
    sprintf(nome_arquivo, "%stransportes.txt", caminho);
    
    FILE *arquivo = fopen(nome_arquivo, "r");//*arquivo recebe o caminho caminho do ficheiro e "r" permite a leitura do ficheiro
    
    //Se o arquivo for igual a null quer dizer q a criação do arquivo falhou ou que ele não existe;
    if(arquivo == NULL){
        printf("Nenhum transporte cadastrado !\n");
        sleep(2);
        limpar_tela();
        return;
    }
    printf("ID|Tipo|Capacidade|Estado|Origem|Destino\n"); 
    //enquanto o resultado de fgets for diferente de NULL 
    while(fgets(l, sizeof(l), arquivo) != NULL)
    	printf("%s", l);//apresente o resultado da linha
    	
    fclose(arquivo);//fecha o arquivo txt após o uso dele
    return;   
}

//MOSTRAR TRANSPORTES por ID TXT
int show_id(int id){
	
	int n = 1;
	int qtd = quantidade();
	
	if(id < 0 || id > qtd){
		printf("ID inválido!\n");
		sleep(2);
		limpar_tela();
		return 0;
	}
	
	Linha l;
	DIR caminho = ".\\Transporte\\Arquivos\\Transportes\\";//String que armazena o caminho 
    DIR nome_arquivo;
    
    sprintf(nome_arquivo, "%stransportes.txt", caminho);
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("Nenhum transporte cadastrado !\n");
        sleep(2);
        limpar_tela();
        return 0;
    }
    
    printf("ID|Tipo|Capacidade|Estado|Origem|Destino\n");
    //enquanto o resultado de fgets for diferente de NULL 
    while(fgets(l, sizeof(l), arquivo) != NULL){
    	
		//Verifica se o ID é igual ao contador
		if(id == n){
    		printf("%s", l);//Apresenta a linha caso seja igual
    		sleep(5);
    		limpar_tela();
			return id;
		}
		n++;//Se não for incrementa o contador e repete o laço
	}
    	
    	
    fclose(arquivo);//fecha o arquivo txt após o uso dele
    return 0;   
}

//MOSTRAR TRANSPORTE
void show_transporte(Transporte t){
	

    printf("\n\n");
    printf("ID %d | ", t.id);
    printf("TIPO: %s |", t.Tipo);
    printf("CAPACIDADE MAXIMA: %d TONELADAS| ", t.Cap);
    printf("ESTADO: %s | ", t.Estado);
    printf("TERMINAL DE PARTIDA: %d | ", t.Origem);
    printf("TERMINAL DE CHEGADA: %d | ", t.Destino);
    printf("\n");
}

void busca_01(LSLTrp *l, int id){
	int qtd = quantidade();
        
    
    if(id < 0 || id > qtd){
        printf("\nPosição inválida.\n");
        sleep(2);
        limpar_tela();
        return ;
    }
	
    No *aux = l->cabeca;
    while(aux->prox != NULL){
        if(aux->t.id == id){
            
            return;
        }
        aux = aux->prox;
    }
    printf("Transporte com ID %d não encontrado.\n", id);
}

void show_all(LSLTrp *l){

    if(l->cabeca == NULL){
        printf("Nenhum transporte cadastrado !\n");
        sleep(3);
        limpar_tela();
        return;
    }
    
    No *aux = l->cabeca;
    while(aux != NULL)
	{
    	show_transporte(aux->t);
        aux = aux->prox;
    }
}


//Inserir no na lista
int inserir(LSLTrp *l){
    No *novo = (No*)malloc(sizeof(No));
    novo = criar_No(l);
    if(l->cabeca == NULL)
    {
    	l->cabeca = novo;
	}
	
	else
	{
		No *aux = l->cabeca;
		while(aux != NULL)
		{
			aux = aux->prox;
		}
		
		aux = novo;
	}
    
    printf("\nTransporte criado com sucesso !");
    return 1;
}

#endif
