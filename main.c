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
		//Apresentação
		printf("----------Bem Vindo ao SGCL - Sistema de Gestão do Corredor do Lobito----------\n");
		printf("--------------------Insira a Opção Desejada--------------------\n");
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
		  printf("Insira uma opção válida");
		  sleep(2);
		  limpar_tela();	
		}
	}
	return 0;
}


