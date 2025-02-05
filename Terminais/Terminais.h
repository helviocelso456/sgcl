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
typedef char linha [1000];
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
}NoTerminais;

//Definindo o cabeça
typedef struct 
{
    NoTerminais *cabeca;
    NoTerminais *ultimo; 
}ListaT;

//Inicializando a lista
void inicializarTerminal(ListaT *l)
{
   l->cabeca = NULL;
   l->ultimo = NULL;
}

int TerminalVazio(ListaT *l)
{
    if(l->cabeca == NULL)
    {
        return 1;
    }

   return 0;
}

//Definindo a quantidade de terminais
int qtdTerminais(ListaT *l)
{
    int qtd = 0;
    NoTerminais *aux = l->cabeca;
    while(aux != NULL)
    {
        qtd++;
        aux = aux->prox;

    }
    return qtd;
}

//Fun��o para limpar a tela
void limparTelaT()
{
    system("cls");
}

//Definindo a listagem de terminais
 void ListarTerminais(ListaT *l)
{  
   limparTelaT();
   NoTerminais *aux = l->cabeca;
   while(aux != NULL)
   {
      printf("Id: %d | Localiza��o: %s, Capacidade Maxima: %d, Cargas Atuais: %d\n",aux->t.id,aux->t.localizacao,aux->t.capacidadeMaxima,aux->t.cargasAtuais);
      aux = aux->prox;
   }
 
}

//Definindo a busca sequencial por ids
int BuscaSequencial(ListaT *l, int id)
{
    NoTerminais *aux = l->cabeca;
    while(aux != NULL)
   {
      if(id == aux->t.id)
      {
         printf("Id: %d | Localiza��o: %s, Capacidade Maxima: %d, Cargas Atuais:: %d\n",aux->t.id,aux->t.localizacao,aux->t.capacidadeMaxima,aux->t.cargasAtuais);
         return id;
      }
      aux = aux->prox;
   }
    return 0;
}
//Fun��o para criar o arquivo de texto
//CRIAR ARQUIVO TRANSPORTE
void file_terminal(TERMINAL *t){
	//Caminho do arquivo
	DIR caminho = ".\\Terminais\\Arquivos\\Terminais\\";
	//Prefixo do nome do arquivo
	DIR n = "Terminais";
	//Vai armazenar a string com o prefixo, caminho e id do terminal
	DIR nome_arquivo;
	//Responsavel por formatar a string
	sprintf(nome_arquivo, "%s%s.txt", caminho, n);
	//Tipo file para criar o documento em modo de escrita
	FILE *arquivo = fopen(nome_arquivo, "a+");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo !\n");
	}
	//Come�a a escrita do documento	
	printf("\n\n");
	fprintf(arquivo, "ID %02d| ", t->id);
	fprintf(arquivo, "TIPO: %s| ", t->localizacao);
	fprintf(arquivo, "CAPACIDADE MAXIMA: %d TONELADAS| ", t->capacidadeMaxima);
	fprintf(arquivo, "N�mero de Cargas Atuais: %d|\n", t->cargasAtuais);
	
	
	printf("Arquivo de Texto criado com sucesso.");
	//Encerra do documento
	fclose(arquivo);
	return;
	
}

//Retorna a quantidade de elementos lendo os arquivos de texto
int quantidadeTerminaisTxT() {
    DIR caminho = ".\\Terminais\\Arquivos\\Terminais\\"; // Diret�rio base
    DIR nome_arquivo;
    int n = 0;
    int c; // Deve ser int para compatibilidade com fgetc()

    // 1. Montagem segura do caminho do arquivo
    snprintf(nome_arquivo, sizeof(nome_arquivo), "%sTerminais.txt", caminho);

    // 2. Abertura do arquivo
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL) {
        printf("Arquivo de terminais n�o encontrado!\n");
        return 0;
    }

    // 3. Contagem precisa de linhas
    int ultimo_char = '\n'; // Controla quebras de linha no final
    while((c = fgetc(arquivo)) != EOF) {
        if(c == '\n') {
            n++;
            ultimo_char = c;
        } else {
            ultimo_char = 0;
        }
    }

    // 4. Contabiliza �ltima linha sem quebra
    if(ultimo_char != '\n' && n > 0) {
        n++;
    }

    fclose(arquivo);
    return n;
}

//Registo de terminais de maneira sequencial
int registoTerminais(ListaT *l, TERMINAL *t)
{  //Para Validar a inicializa��o
   if (l == NULL) {
        printf("Erro: Lista n�o inicializada!\n");
        return -1;
    }
   //Criamos no no
   NoTerminais *no = (NoTerminais*) malloc(sizeof(NoTerminais));
   //Valida o malloc
    if (no == NULL) {
        printf("Erro ao alocar memoria para o no.\n");
        return -1;
    }
   //Definimos o prox do no como null pra evitar certos comportamentos
   no->prox = NULL;
   //Atribuindo o terminal ao no
   no->t = *t;
   if(l->cabeca == NULL)
   {
      //O cabe�a vai ser igual ao ultimo elemento
      l->cabeca = no;
      l->ultimo = no;
      //Mandando pro arquivo de Texto
      file_terminal(t);
   }

   else
   {
       //Primeiro definimos que o prox do ant e o no
       l->ultimo->prox = no;
       //Depois definimos que o ultimo e o no
       l->ultimo = no;
       //Mandando pro arquivo de Texto
       file_terminal(t);
   }

   return 0;
}

//MOSTRAR Terminais TXT
void ListagemTerminaisTexto() {
    linha l; // Buffer para armazenar cada linha do arquivo
    DIR caminho = ".\\Terminais\\Arquivos\\Terminais\\"; // Diret�rio base para armazenamento
    DIR nome_arquivo; // Buffer para montar o caminho completo

    // Monta o caminho completo do arquivo (concatena diret�rio + nome do arquivo)
    snprintf(nome_arquivo, sizeof(nome_arquivo), "%sTerminais.txt", caminho);
    
    // Tenta abrir o arquivo em modo leitura (r = read)
    FILE *arquivo = fopen(nome_arquivo, "r");
    
    // Verifica se houve erro na abertura
    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo de terminais!\n");
        return;
    }
    
    // Imprime cabe�alho para organiza��o
    printf("\n====== LISTAGEM DE TERMINAIS ======\n");
    
    // L� o arquivo linha por linha at� o final (EOF)
    while(fgets(l, sizeof(l), arquivo) != NULL) {
        printf("%s", l); // Imprime cada linha do arquivo
    }
    
    // Fecha o arquivo ap�s o uso (boas pr�ticas)
    fclose(arquivo);
    
    printf("\n====== FIM DA LISTAGEM ======\n");
    return;
}

int BuscaSequencialTerminaisTxT(int id){
	
	int n = 1;
	int qtd = quantidadeTxT();
	
	if(id < 0 || id > qtd){
		printf("ID inv�lido!\n");
		sleep(2);
		limparTelaT();
		return 0;
	}
	
	linha l;
	DIR caminho = ".\\Terminais\\Arquivos\\Terminais\\";//String que armazena o caminho 
    DIR nome_arquivo;
    
    sprintf(nome_arquivo, "%sTerminais.txt", caminho);
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("Nenhum terminal cadastrado !\n");
        sleep(2);
        limparTelaT();
        return 0;
    }
    
    //enquanto o resultado de fgets for diferente de NULL 
    while(fgets(l, sizeof(l), arquivo) != NULL){
    	
		//Verifica se o ID � igual ao contador
		if(id == n){
    		printf("%s", l);//Apresenta a linha caso seja igual
    		sleep(5);
    		limparTelaT();
			return id;
		}
		n++;//Se n�o for incrementa o contador e repete o la�o
	}
    	
    	
    fclose(arquivo);//fecha o arquivo txt ap�s o uso dele
    return 0;   
}

void MenuTerminais()
{
	int op2;
    TERMINAL t;
    ListaT l;
    inicializarTerminal(&l);
	printf("\n");
    printf("=============================\n");
    printf("============ SGCL ===========\n");
    printf("=============================\n\n");
    //Op��es
    printf("[1] - Cadastrar Terminal\n");
    printf("[2] - Listar Terminais\n");
    printf("[3] - Buscar Terminais\n");
    printf("[4] - Sair\n");
    printf("ESCOLHA: ");
    scanf("%d",&op2);
    switch(op2)
    {
    	case 1:
    	MenuRegistarTerminais(&l,t);	
        break;
        
        case 2:
        ListagemTerminaisTexto();   
        break;
        
        case 3:
        MenuBuscaSequencialTerminais(); 
        break;
        
        default:
        printf("Insira uma op��o v�lida");
		sleep(2);
		limpar_tela();
	}
}

void MenuRegistarTerminais(ListaT *l, TERMINAL t)
{
	 limparTelaT();
	 printf("\n=============================\n");
     printf("===== Registo de Terminais =====\n");
     printf("=============================\n\n");
     
    // Atribui ID ao terminal
    t.id = quantidadeTerminaisTxT() + 1;
    
     // L� a localiza��o
    printf("Insira a localiza��o: ");
    scanf("%s", &t.localizacao);
	 // Captura espa�os em branco
    
    // L� a capacidade m�xima
    printf("Insira a capacidade m�xima: ");
    scanf("%d", &t.capacidadeMaxima);

    // Define cargas atuais como 0
    t.cargasAtuais = 0;

    // Registra o terminal na lista
    registoTerminais(l, &t);
    //Limpando a tela
    limparTelaT();
    printf("ID: %d | Localiza��o: %s | Capacidade M�xima: %d | Cargas Atuais: %d",t.id,t.localizacao,t.capacidadeMaxima,t.cargasAtuais);
    sleep(4);
    limparTelaT();
   			
}

void MenuBuscaSequencialTerminais()
{
	limparTelaT();
	int id;
	printf("Insira o id do terminal: ");
	scanf("%d",&id);
	BuscaSequencialTxT(id);	
}

#endif
