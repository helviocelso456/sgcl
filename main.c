#include "Terminais/Terminais.h"
#include "Transporte/Transporte.h"
#include "Cargas/cargas.h"

int main()
{
	setlocale(LC_ALL,"Portuguese");
	int i = 1;
	int op;
	while(i != 0)
	{
		//Apresenta��o
		printf("----------Bem Vindo ao SGCL - Sistema de Gest�o do Corredor do Lobito----------\n");
		printf("--------------------Insira a Op��o Desejada--------------------\n");
		//Menu
		printf("1 - Terminais\n");
		printf("2 - Transportes\n");
		printf("3 - Cargas\n");
		printf("4 - Encerrar\n");
		printf("Escolha: ");
		scanf("%d",&op);
		//Switch Case
		switch(op)
		{
		  case 1:
		  MenuTerminais();
		  break;
		  
		  case 2:
		  Menu();
		  break;
		  
		  case 3:
		  MenuCargas();
		  break;
		  
		  case 4:
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


