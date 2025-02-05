//Bibliotecas da Linguagem
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<windows.h>

//Bibliotecas Criadas
#include "C:\\Users\\GIL\\Desktop\\SGCL_CENTRAL\\00\\Terminais.h"
//#include "Contentor.h"
//#include "Vagao.h"

//Constantes dos transportes
#define BARCO 10000
#define CAMINHAO 45
#define COMBOIO 20000

typedef char String [50];
typedef char DIR [200];
typedef char Linha [1000];

//TIPO DE DADO TRANSPORTE
typedef struct transporte{
    int id;
    int Cap;
    String Origem, Destino;
    String Tipo;
    String Estado;
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
    l->cabeca == NULL;
}

//FUNCAO VAZIA
int vazia(LSLTrp *l){
    if(l->cabeca == NULL){
        printf("A lista está vazia !\n");
        return 1;
    }
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

//Estados do TRANSPORTE
//Coloca o estado do transporte por default
void init_estado(Transporte *t){  
	String  estado = "Aguardando";
	
	strcpy(t->Estado, estado);
	return;
}

//Inicia o terminal do transporte como indefinido
void init_terminal(Transporte *t){
	String terminal = "Indefinido";
	
	strcpy(t->Destino, terminal);
	strcpy(t->Origem, terminal);
	return;
}


//CRIAÇÃO E MANIPULAÇÃO ARQUIVOS TXT
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
    
    //printf("Guardou os dados.\n");
    //printf("Arquivo de Texto criado com sucesso.");
    fclose(arquivo);
    return;
    
}


//IMPEDE A REPETIÇÃO NO ID E CALCULA A QTD APARTIR DO Nº DE LINHAS DO FICHEIRO
int quantidade(){
    
	//Cria uma String com o caminho do diretório do ficheiro
    DIR caminho = ".\\Arquivos\\Transportes\\";
    DIR nome_arquivo;
    
	int n = 1;
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
    t->id = quantidade();
    
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
    
	//Coloca o estado por default em "Aguardando"
    init_estado(t);
    
    init_terminal(t);

    file_transporte(t);
    
    return 1;       
}

//CRIAR NO
No* criar_No(LSLTrp *l){
	//Criamos uma variavel T do Tipo Transporte
    Transporte T;
    
    //Chamamos a função criar transporte para T receber os atributos
    criar_Transporte(&T);
    
    //Criamos um novo nó
    No *novo = (No*)malloc(sizeof(No));
    novo->t = T;
    novo->prox =  NULL;
    
    return novo;
}


//FUNÇÕES PARA MOSTRAR
//MOSTRAR MENU
void Menu_Transportes(){
    printf("\n");
    printf("=====================================\n");
    printf("============== SGCL =================\n");
    printf("=====================================\n");
    
    printf("== [1] - Cadastrar Transporte      ==\n");
    printf("== [2] - Mostrar Transporte        ==\n");
    printf("== [3] - Carregar Transporte       ==\n");
    printf("== [4] - Retirar Transporte        ==\n");
    printf("== [5] - Buscar  Transporte por ID ==\n");
    printf("== [0] - Sair                      ==\n");
    printf("=====================================\n");
    printf("ESCOLHA: ");
    
}

//MOSTRAR TODOS TRANSPORTES TXT
void ListagemTransportesTxT(){
	Linha l;
	DIR caminho = ".\\Arquivos\\Transportes\\";//String que armazena o caminho 
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
     // Imprime cabeçalho para organização
    printf("\n====== LISTAGEM DE TERMINAIS ======\n");
    
    //enquanto o resultado de fgets for diferente de NULL 
    while(fgets(l, sizeof(l), arquivo) != NULL)
    	printf("%s", l);//apresente o resultado da linha
    	
    fclose(arquivo);//fecha o arquivo txt após o uso dele
    
	printf("\n====== FIM DA LISTAGEM ======\n");
	 
	return;   
}

//MOSTRAR TRANSPORTES por ID TXT
void MostrarTransporteId(int id){
	
	int n = 1;
	int qtd = quantidade();
	
	if(id < 1 || id >= qtd){
		printf("ID inválido!\n");
		sleep(2);
		limpar_tela();
		return;
	}
	
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
    
    //enquanto o resultado de fgets for diferente de NULL 
    while(fgets(l, sizeof(l), arquivo) != NULL){
    	
		//Verifica se o ID é igual ao contador
		if(id == n){
    		printf("%s", l);//Apresenta a linha caso seja igual
    		sleep(5);
    		limpar_tela();
			return;
		}
		n++;//Se não for incrementa o contador e repete o laço
	}
    	
    	
    fclose(arquivo);//fecha o arquivo txt após o uso dele
    return;   
}

//Inserir no final da lista
int inserir(LSLTrp *l){
	//Criamos um novo No com alocação dinâmica
    No *novo = criar_No(l);
    novo->prox = NULL;
    l->cabeca = novo;
    //printf("\nTransporte criado com sucesso !");
    return 1;
}

//InserirTerminal
void InserirTerminalOrigem(int idt, String Terminal){
	
	Linha l;
	DIR caminho = ".\\Arquivos\\Transportes\\";//String que armazena o caminho 
    DIR nome_arquivo;
    
    sprintf(nome_arquivo, "%stransportes.txt", caminho);
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    FILE *temp = fopen("temp.txt", "w");
    
	if(arquivo == NULL || temp==NULL){
		printf("Erro ao abrir o Arquivo !\n");
        return;
	}
	
	while(fgets(l, sizeof(l), arquivo)){
		int id, cap;
		String tp, to, td, et;
		if(sscanf(l, "Id: %02d | Tipo: %s | Cap_Max: %d | Estado: %s | Terminal de Origem: %s | Terminal de Destino: %s", &id, &tp, &cap, &et, &to, &td) == 6){
			if(id == idt){
				printf("ID encontrado\n");
				printf("TO = %s\n", to);
				printf("TER = %s\n", Terminal);
				strcpy(to, Terminal);
				printf("To = %s\n", to);
				strcpy(et, "Carregando");
				printf("Estado: %s\n", et);
				
			}
			fprintf(temp, "Id: %02d | Tipo: %s | Cap_Max: %d | Estado: %s | Terminal de Origem: %s | Terminal de Destino: %s\n", id, tp, cap, et, to, td);
			
		} else {
			fprintf(temp, "%s", l);
		}
		
	}
	
	fclose(arquivo);
	fclose(temp);
	
	remove(nome_arquivo);
	rename("temp.txt", nome_arquivo);
	return;
}

//Função para Carregar Transporte
void CarregarTransporte(int id){
	int id_Partida = 0;
	int id_Destino = 0;
	String to, td;
	MostrarTransporteId(id);
	
	printf("Digite o Id do Terminal de Partida");
	scanf("%d", &id_Partida);
	BuscaSequencialTxT(id_Partida);
	
	printf("Insira o nome do Terminal: ");
	scanf("%s", &to);
	InserirTerminalOrigem(id, to);
	
	
	
	return;
}

int Main_Transporte(){
	
	
	Transporte A;
	LSLTrp l;
	initLista (&l);
	char op, id;
	
	do{
		Menu_Transportes();
		scanf(" %c", &op);
		getchar();
	
		printf("\n");
	

		switch (op){
			
			case '1':
				inserir(&l);
				sleep(3);
				limpar_tela();
				break;
		
			case '2':
				ListagemTransportesTxT();
				sleep(5);
				limpar_tela();
				break;
				
			
			
			case '3':
				//Verifica se o arquivo txt está ou não vazio
				if(quantidade()==0){
					printf("Nenhum transporte cadastrado !\n");
					sleep(2);
					limpar_tela();
					break;
				}
					
				else{
					printf("Id: ");
					scanf("%d", &id);
					getchar();
					CarregarTransporte(id);
					break;
				}
				
			case '5':
				//Verifica se o arquivo txt está ou não vazio
				if(quantidade()==0){
					printf("Nenhum transporte cadastrado !\n");
					sleep(2);
					limpar_tela();
					break;
				}
					
				else{
					printf("Id: ");
					scanf("%d", &id);
					getchar();
					MostrarTransporteId(id);
					break;
				}
			
			case '0':
				printf("Saindo...\n");
				sleep(2);
				limpar_tela();
				Menu_Central();
				break;
			
			default:
				printf("Tentativa Inválida!\n");
				sleep(1);
				printf("Tente Novamente.");
				sleep(1);
				limpar_tela();
				break;
		}
	}while(op != '0');
	
	
	return 123;
}
