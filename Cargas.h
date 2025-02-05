#ifndef cargas_H
#define cargas_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<windows.h>
//Definindo TDA
typedef char String [50];
typedef char DIR [200];
typedef char linha [1000];
//Definindo Estruturas
typedef struct
{
  int id;
  String Descricao;
  int peso;
  String estado;
  int origem;
  int destino;	
}CARGAS;

//Definindo o no
typedef struct no{
   CARGAS c;
   struct no *prox;	
}NO;

//Definindo o cabeça
typedef struct 
{
    NO *cabeca;
    NO *ultimo; 
}LISTA;

//Inicializando a lista
void inicializarLista(LISTA *l)
{
	l->cabeca = NULL;
	l->ultimo = NULL;
}

//Função para limpar a tela
void limparTela()
{
    system("cls");
}

//Retorna a quantidade de elementos lendo os arquivos de texto
int quantidadeTxT() {
    DIR caminho = ".\\Arquivos\\Cargas\\"; // Diretório base
    DIR nome_arquivo;
    int n = 0;
    int c; // Deve ser int para compatibilidade com fgetc()

    // 1. Montagem segura do caminho do arquivo
    snprintf(nome_arquivo, sizeof(nome_arquivo), "%sCargas.txt", caminho);

    // 2. Abertura do arquivo
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL) {
        printf("Arquivo de cargas não encontrado!\n");
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

    // 4. Contabiliza última linha sem quebra
    if(ultimo_char != '\n' && n > 0) {
        n++;
    }

    fclose(arquivo);
    return n;
}

//Função para criar o arquivo de texto
void file_cargas(CARGAS *c){
	//Caminho do arquivo
	DIR caminho = ".\\Arquivos\\Cargas\\";
	//Prefixo do nome do arquivo
	DIR n = "Cargas";
	//Vai armazenar a string com o prefixo, caminho e id da carga
	DIR nome_arquivo;
	//Responsavel por formatar a string
	sprintf(nome_arquivo, "%s%s.txt", caminho, n);
	//Tipo file para criar o documento em modo de escrita
	FILE *arquivo = fopen(nome_arquivo, "a+");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo !\n");
	}
	//Começa a escrita do documento	
	printf("\n\n");
	fprintf(arquivo, "ID %02d| ", c->id);
	fprintf(arquivo, "Descrição: %s| ", c->Descricao);
	fprintf(arquivo, "Peso: %d TONELADAS| ", c->peso);
	fprintf(arquivo, "Estado: %s| ", c->estado);
	fprintf(arquivo, "Terminal de Origem: %d|", c->origem);
	fprintf(arquivo, "Terminal de Destino: %d|\n", c->destino);
	
	
	printf("Arquivo de Texto criado com sucesso.");
	//Encerra do documento
	fclose(arquivo);
	return;
	
}

//Registando Elementos
int registoCargas(LISTA *l, CARGAS *c)
{  //Para Validar a inicialização
   if (l == NULL) {
        printf("Erro: Lista não inicializada!\n");
        return -1;
    }
   //Criamos no no
   NO *no = (NO*) malloc(sizeof(NO));
   //Valida o malloc
    if (no == NULL) {
        printf("Erro ao alocar memoria para o no.\n");
        return -1;
    }
   //Definimos o prox do no como null pra evitar certos comportamentos
   no->prox = NULL;
   //Atribuindo o terminal ao no
   no->c = *c;
   if(l->cabeca == NULL)
   {
      //O cabeça vai ser igual ao ultimo elemento
      l->cabeca = no;
      l->ultimo = no;
      //Mandando pro arquivo de Texto
      file_cargas(c);
   }
    else
   {
       //Primeiro definimos que o prox do ant e o no
       l->ultimo->prox = no;
       //Depois definimos que o ultimo e o no
       l->ultimo = no;
       //Mandando pro arquivo de Texto
       file_cargas(c);
   }
    
    return 0;
}

//MOSTRAR Cargas TXT
void ListagemCargasTexto(){
    linha l; // Buffer para armazenar cada linha do arquivo
    DIR caminho = ".\\Arquivos\\Cargas\\"; // Diretório base para armazenamento
    DIR nome_arquivo; // Buffer para montar o caminho completo

    // Monta o caminho completo do arquivo (concatena diretório + nome do arquivo)
    snprintf(nome_arquivo, sizeof(nome_arquivo), "%sCargas.txt", caminho);
    
    // Tenta abrir o arquivo em modo leitura (r = read)
    FILE *arquivo = fopen(nome_arquivo, "r");
    
    // Verifica se houve erro na abertura
    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo de cargas!\n");
        return;
    }
    
    // Imprime cabeçalho para organização
    printf("\n====== LISTAGEM DE CARGAS ======\n");
    
    // Lê o arquivo linha por linha até o final (EOF)
    while(fgets(l, sizeof(l), arquivo) != NULL) {
        printf("%s", l); // Imprime cada linha do arquivo
    }
    
    // Fecha o arquivo após o uso (boas práticas)
    fclose(arquivo);
    
    printf("\n====== FIM DA LISTAGEM ======\n");
    return;
}

//Busca Sequencial no arquivo de texto
int BuscaSequencialTxT(int id){
	
	int n = 1;
	int qtd = quantidadeTxT();
	
	if(id < 0 || id > qtd){
		printf("ID inválido!\n");
		sleep(2);
		limparTela();
		return 0;
	}
	
	linha l;
	DIR caminho = ".\\Arquivos\\Cargas\\";//String que armazena o caminho 
    DIR nome_arquivo;
    
    sprintf(nome_arquivo, "%sCargas.txt", caminho);
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("Nenhum terminal cadastrado !\n");
        sleep(2);
        limparTela();
        return 0;
    }
    
    //enquanto o resultado de fgets for diferente de NULL 
    while(fgets(l, sizeof(l), arquivo) != NULL){
    	
		//Verifica se o ID é igual ao contador
		if(id == n){
    		printf("%s", l);//Apresenta a linha caso seja igual
    		sleep(5);
    		limparTela();
			return id;
		}
		n++;//Se não for incrementa o contador e repete o laço
	}
    	
    	
    fclose(arquivo);//fecha o arquivo txt após o uso dele
    return 0;   
}

void Menu()
{
	printf("\n");
    printf("=============================\n");
    printf("============ SGCL ===========\n");
    printf("=============================\n\n");
    //Opções
    printf("[1] - Cadastrar Cargas\n");
    printf("[2] - Listar Cargas\n");
    printf("[3] - Buscar Cargas\n");
    printf("[4] - Sair\n");
    printf("ESCOLHA: ");
}

void MenuRegistar(LISTA *l, CARGAS c)
{
	 limparTela();
	 printf("\n=============================\n");
     printf("===== Registo de Cargas =====\n");
     printf("=============================\n\n");
     
    // Atribui ID ao terminal
    c.id = quantidadeTxT() + 1;
    //Insere a descrição
    printf("Insira a Descrição: ");
    scanf("%s", &c.Descricao);
    // Insere o peso
    printf("Insira o Peso em Toneladas: ");
    scanf("%d", &c.peso);
	 //Definindo o estado default
	strcpy(c.estado, "Aguardando");
    // Define a origem e destino default
    c.origem = 0;
    c.destino = 0;
    // O zero quer dizer indefinido

    // Registra a carga
    registoCargas(l,&c);
    //Limpando a tela
    limparTela();
    printf("ID: %d | Descrição: %s | Peso: %d | Estado: %s | Terminal de Origem: %d | Terminal de Destino: %d",c.id,c.Descricao,c.peso,c.estado,c.origem,c.destino);
    sleep(4);
    limparTela();
   			
}

void MenuBuscaSequencial()
{
	limparTela();
	int id;
	printf("Insira o ID da Carga: ");
	scanf("%d",&id);
	BuscaSequencialTxT(id);	
}

int main_Cargas()
{
	LISTA l;
    inicializarLista(&l);
    CARGAS c;
    
    int i = 1;
    
    while(i != 0)
    {
    	char op;
    	Menu();
    	scanf(" %c", &op);
    	//Switch Case
    	switch(op)
    	{
    		case '1':
    	    MenuRegistar(&l,c);
    	    break;
    	    
    	    case '2':
    	    ListagemCargasTexto();
    	    break;
    	    
    	    case '3':
    	    MenuBuscaSequencial();
    	    break;
    	    
    	    case '4':
    	    i = 0;
    	    break;
    	    
    	    default:
    	    printf("Opção Invalida");
    	    
		}
    	
	}
    
    return 0;
}
#endif
