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
  float peso;
  String estado;
  int origem;
  int destino;	
}CARGAS;

//Definindo o no
typedef struct noC
{
   CARGAS c;
   struct noC *prox;	
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
    DIR caminho = ".\\Cargas\\Arquivos\\Cargas\\"; // Diretório base
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
	DIR caminho = ".\\Cargas\\Arquivos\\Cargas\\";
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
	fprintf(arquivo, "%02d|", c->id);
	fprintf(arquivo, "%s|", c->Descricao);
	fprintf(arquivo, "%.1f|", c->peso);
	fprintf(arquivo, "%s|", c->estado);
	fprintf(arquivo, "%d|", c->origem);
	fprintf(arquivo, "%d\n", c->destino);
	
	
	printf("Arquivo de Texto criado com sucesso.");
	//Encerra do documento
	fclose(arquivo);
	return;
	
}

void ListarCargas(LISTA *l)
{
	limpar_tela();
	NO *aux = l->cabeca;
	while(aux != NULL)
	{
		printf("ID %d| Descrição: %s, Peso: %.1f, Estado: %s, Terminal de Origem: %d, Terminal de Destino: %d\n",aux->c.id,aux->c.Descricao,aux->c.peso,aux->c.estado,aux->c.origem,aux->c.destino);
		aux = aux->prox;
	}
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
    DIR caminho = ".\\Cargas\\Arquivos\\Cargas\\"; // Diretório base para armazenamento
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
	DIR caminho = ".\\Cargas\\Arquivos\\Cargas\\";//String que armazena o caminho 
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

int recriarCargas(LISTA *lCargas)
{
	linha l; //Vai pegar as linhas
	DIR caminho = ".\\Cargas\\Arquivos\\Cargas\\";//String que armazena o caminho 
	DIR nome_arquivo; //Vair armazenar o caminho e o nome;
	CARGAS c;
	//Vai mandar tudo pra variável nome_arquivo
	sprintf(nome_arquivo, "%sCargas.txt", caminho);
    //Abre o arquivo de texto em modo de leitura
    FILE *arquivo = fopen(nome_arquivo, "r");
    //Validando
    if(arquivo == NULL)
    {
       printf("Não foi possível abrir o arquivo");
       return 0;
	}
	
	while(fgets(l, sizeof(l), arquivo) != NULL)
	{
		//Remove o \n
		if (l[strlen(l) - 1] == '\n') {
            l[strlen(l) - 1] = '\0';
        }
        
        // Dividir a linha usando o delimitador |
        char *token = strtok(l, "|");
         //Atribuindo o id;
         if(token != NULL) c.id = atoi(token);
         
         //Passando pro proximo
         token = strtok(NULL, "|");
         if(token != NULL) strcpy(c.Descricao, token); 
         
         //Passando pro proximo
         token = strtok(NULL, "|");
         if(token != NULL) c.peso = atof(token);
         
         //Passando pro proximo
         token = strtok(NULL, "|");
         if(token != NULL) strcpy(c.estado,token);
         
         //Passando pro proximo
         token = strtok(NULL, "|");
         if(token != NULL) c.origem = atoi(token);
         
         //Passando pro proximo
         token = strtok(NULL, "|");
         if(token != NULL) c.destino = atoi(token);
         
         //Cria novamente o NO
         recriarNoCargas(lCargas, c);
	}
	
	//Boas Praticas
	fclose(arquivo);
	return 1;
}

int recriarNoCargas(LISTA *lCargas, CARGAS c)
{
	if(lCargas == NULL)
	{
		printf("Lista não inicializada");
		return 0;
	}
	
	NO *novo = (NO*) malloc(sizeof(NO));
	if(novo == NULL)
	{ 
	   printf("Erro ao alocar a memoria");
	   return 0;
	}
	
	novo->prox = NULL;
	novo->c = c;
	
	if(lCargas->cabeca == NULL)
	{
		//Caso a lista esteja vazia
		lCargas->cabeca = novo;
		lCargas->ultimo = novo;
	}
	
	else
	{
		//Inserimos como o ultimo elemento
		lCargas->ultimo->prox = novo;
		lCargas->ultimo = novo;
	}
	
	return 1;
}

NO *buscaNoCargas(LISTA *lCargas, int id)
{
	limpar_tela();
	int qtd = quantidadeTxT();
	if(id < 0 || id > qtd)
	{
		printf("Identificador Invalido");
		return NULL;
	}
	NO *aux = lCargas->cabeca;
	while(aux != NULL && aux->c.id != id)
	{
		aux = aux->prox;
	}
	
	if(aux->c.id == id)
	{
	   printf("Cargas Encontrada!!\n");
	   printf("ID %d| Descrição: %s, Peso: %.1f, Estado: %s, Terminal de Origem: %d, Terminal de Destino: %d\n",aux->c.id,aux->c.Descricao,aux->c.peso,aux->c.estado,aux->c.origem,aux->c.destino);
	   return aux;
	}
	
	else
	{
		printf("Carga Não Encontrada");
	}
	
	return NULL;
	
}

//Update das cargas
void update_cargas(LISTA *lCargas){
	//Caminho do arquivo
	DIR caminho = ".\\Cargas\\Arquivos\\Cargas\\";
	//Prefixo do nome do arquivo
	DIR n = "Cargas";
	//Vai armazenar a string com o prefixo, caminho e id da carga
	DIR nome_arquivo;
	//Responsavel por formatar a string
	sprintf(nome_arquivo, "%s%s.txt", caminho, n);
	//Tipo file para criar o documento em modo de escrita
	FILE *arquivo = fopen(nome_arquivo, "w");
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo !\n");
		return;
	}
	
	//No auxiliar
	NO *aux = lCargas->cabeca;
	//Começa a escrita do documento	
	while(aux != NULL)
	{
     printf("\n\n");
	 fprintf(arquivo, "%02d|", aux->c.id);
	 fprintf(arquivo, "%s|", aux->c.Descricao);
	 fprintf(arquivo, "%.1f|", aux->c.peso);
	 fprintf(arquivo, "%s|", aux->c.estado);
	 fprintf(arquivo, "%d|", aux->c.origem);
	 fprintf(arquivo, "%d\n", aux->c.destino);
	 aux = aux->prox;
	}
	
	
	printf("Cargas Atualizadas Com Sucesso.\n");
	//Encerra do documento
	fclose(arquivo);
	
}

void MenuCargas(LISTA *lCargas)
{   
    int op2;
    CARGAS c;
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
    scanf("%d",&op2);
    switch(op2)
    {
    	case 1:
    	MenuRegistarCargas(lCargas,c);	
        break;
        
        case 2:
        ListarCargas(lCargas);   
        break;
        
        case 3:
        MenuBuscaSequencialCargas(lCargas);   
        break;
        
        default:
        printf("Insira uma opção válida");
		sleep(2);
		limpar_tela();
	}
}

void MenuRegistarCargas(LISTA *l, CARGAS c)
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
    scanf("%f", &c.peso);
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
    printf("ID: %d | Descrição: %s | Peso: %.1f | Estado: %s | Terminal de Origem: %d | Terminal de Destino: %d",c.id,c.Descricao,c.peso,c.estado,c.origem,c.destino);
    sleep(4);
    limparTela();
   			
}

void MenuBuscaSequencialCargas(LISTA *lCargas)
{
	limparTela();
	int id;
	printf("Insira o ID da Carga: ");
	scanf("%d",&id);
	buscaNoCargas(lCargas,id);	
}

#endif
