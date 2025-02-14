#include "Terminais/Terminais.h"
#include "Transporte/Transporte.h"
#include "Cargas/cargas.h"
#include "Relatorio.h"

//TDA Comas as cargas
typedef struct cT
{
  CARGAS c;
  struct cT *prox;
}CargasTerminal;

//Deque
typedef struct
{
  CargasTerminal *baseEsquerda;
  CargasTerminal *baseDireita;
}deque;

//Inicializar Deque
void inicializarDeque(deque *d)
{
	d->baseDireita = NULL;
	d->baseEsquerda = NULL;
}

//Armzena as opera��es do deque
int file_deque(String tipo, int idC, int id)
{   
    //Caminho do arquivo
	DIR caminho = ".\\Operacoes\\";
	//Nome Arquivo
	DIR nome_arquivo;
	//Formatando a string
	sprintf(nome_arquivo, "%soperacoes.txt",caminho);
	//Tipo File
	FILE *arquivo = fopen(nome_arquivo, "a+");
	//Validando
	if(arquivo == NULL)
	{
		printf("N�o foi Poss�vel Abrir ou Criar o Arquivo");
		return 0;
	}
	//Gravando no arquivo
	fprintf(arquivo, "%s|%d|%d\n",tipo,idC,id);
	//Boas Praticas
	fclose(arquivo);
	printf("Opera��o de %s Efectuada com Sucesso!!\n");
	sleep(2);
	limparTela();
	return 1;
}

int armazenarCarga(ListaT *lT,LISTA *lCargas, deque *d, int idT)
{
	//Primeiro pegamos o terminal
	NoTerminais *noT = BuscaSequencialTerminal(lT, idT);
	String tipo = "Armazenamento";
	//Verifica se encontrou
	if(noT == NULL)
	{
		return 0;
	}
	
	//Verifica o espa�o disponivel 
	if(noT->t.cargasAtuais == noT->t.capacidadeMaxima){
		printf("O terminal est� cheio!!");
		return 0;
	}
	
	//Declaramos o no pra cargas
	NO *noC;
	int idC;
	//Inserimos o id pra pegar a carga
	printf("Insira o identificador da carga: ");
	scanf("%d", &idC);
	//Pegamos a carga
	noC = buscaNoCargas(lCargas,idC);
	//Verifica se foi achada
	if(noC == NULL)
	{
		return 0;
	}
	
	//Chamamos o no do deque
	CargasTerminal *cT = (CargasTerminal*) malloc(sizeof(CargasTerminal));
	if(cT == NULL)
	{
		printf("Erro ao alocar memoria");
		return 0;
	}
	
	cT->prox = NULL;
	cT->c = noC->c;
	//Quer dizer que o n� ta vazio
	if(d->baseEsquerda == NULL && d->baseDireita == NULL)
	{
		//Ambos apontam pra mesma carga pois s� existe ela
		d->baseEsquerda = cT;
		d->baseDireita = cT;
		noC->c.origem = noT->t.id;
		noT->t.cargasAtuais++;
		update_cargas(lCargas);
		update_terminal(lT);
		file_deque(tipo,idC,idT);
		printf("Carga Adicionada ao Deque!!\n");
	}
	
	else if(cT->c.peso > 4)
	{
		//Adiciona no fim
		d->baseDireita->prox = cT;
		d->baseDireita = cT;
		noC->c.origem = noT->t.id;
		noT->t.cargasAtuais++;
		update_cargas(lCargas);
		update_terminal(lT);
		file_deque(tipo,idC,idT);
		printf("Carga Adicionada ao Deque!!\n");
	}
	
	else
	{
		//Adiciona no inicio
		cT->prox = d->baseEsquerda;
		d->baseEsquerda = cT;
		noC->c.origem = noT->t.id;
		noT->t.cargasAtuais++;
		update_cargas(lCargas);
		update_terminal(lT);
		file_deque(tipo,idC,idT);
		printf("Carga Adicionada ao Deque!!\n");
	}
	
	return 1;
}

int carregaTransporte(ListaT *lT, LSLTrp *lTrans, LISTA *lCargas, deque *d, int idT)
{
   //Primeiro pegamos o terminal
	NoTerminais *noT = BuscaSequencialTerminal(lT, idT);
	String tipo = "Carregamento";
	
	//Verifica se encontrou
	if(noT == NULL)
	{
		return 0;
	}
	
	//Procurando o transporte
	int idTrans;
	printf("Insira o Identificador do Transporte: ");
	scanf("%d", &idTrans);
	No *noTrans = busca(lTrans, idTrans);
	
	//Verifica se achou
	if(noTrans == NULL)
	{
		return 0;
	}
	
	int idC;
	printf("Insira o Identificador da Carga");
	scanf("%d", &idC);
	NO *noC = buscaNoCargas(lCargas, idC);
	
	//Verifica se achou
	if(noC == NULL)
	{
		return 0;
	}
	
	strcpy(noC->c.estado, "Em Transporte");
	noTrans->t.Origem = noC->c.origem;
	noTrans->t.Destino = idT;
	strcpy(noTrans->t.Estado, "Transportando");
	update_cargas(lCargas);
	update_transporte(lTrans);
	file_deque(tipo,idC,idTrans);
	printf("Carga Adicionada ao Transporte!!\n");
		
	return 1;			
}

int main()
{
	//N�s
	ListaT lT;
	LSLTrp lTransporte;
	LISTA lCargas;
	deque d;
	inicializarDeque(&d);
	//Locale
	setlocale(LC_ALL,"Portuguese");
	//Outros
	int i = 1;
	int op,idT;
	while(i != 0)
	{
		inicializarTerminal(&lT);
	    initLista(&lTransporte);
	    inicializarLista(&lCargas);
	    recriarTerminal(&lT);
	    recriarTransporte(&lTransporte);
	    recriarCargas(&lCargas);
		//Apresenta��o
		printf("----------Bem Vindo ao SGCL - Sistema de Gest�o do Corredor do Lobito----------\n");
		printf("--------------------Insira a Op��o Desejada--------------------\n");
		//Menu
		printf("1 - Terminais\n");
		printf("2 - Transportes\n");
		printf("3 - Cargas\n");
		printf("4 - Relat�rios\n");
		printf("5 - Armazenar Cargas\n");
		printf("6 - Carregar Transporte\n");
		printf("7 - Encerrar\n");
		printf("Escolha: ");
		scanf("%d",&op);
		//Switch Case
		switch(op)
		{
		  case 1:
		  MenuTerminais(&lT);
		  break;
		  
		  case 2:
		  Menu(&lTransporte);
		  break;
		  
		  case 3:
		  MenuCargas(&lCargas);
		  break;
		  
		  case 4:
		  Relatorio ();
		  break;
		  
		  case 5:
		  printf("Insira o Identificador do Terminal: ");
		  scanf("%d",&idT);
		  armazenarCarga(&lT, &lCargas, &d, idT);
		  break;
		  
		  case 6:
		  printf("Insira o Identificador do Terminal de Destino: ");
		  scanf("%d",&idT);
		  carregaTransporte(&lT, &lTransporte, &lCargas, &d,idT);
		  break;
		  
		  case 7:
		  i = 0;
		  printf("----------Muito Obrigada Por Usar o SGCL----------\n");
		  printf("Sistema Encerrado");
		  break;
		  
		  default:
		  printf("Insira uma op��o v�lida");
		  sleep(2);
		  limpar_tela();	
		}
	}
	return 0;
}


