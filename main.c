#include "Terminais/Terminais.h"
#include "Transporte/Transporte.h"
#include "Cargas/cargas.h"
#include "Relatorio.h"
int main()
{
	//N�s
	ListaT lT;
	LSLTrp lTransporte;
	LISTA lCargas;
	//Locale
	setlocale(LC_ALL,"Portuguese");
	//Outros
	int i = 1;
	int op;
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
		printf("5 - Encerrar\n");
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


