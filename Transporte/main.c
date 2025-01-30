#include "Transporte_02.h"

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	Transporte A;
	LSLTrp l;
	initLista (&l);
	char op, id;
	
	do{
		Menu();
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
				show_transporte(&l);
				break;
				
			case '3':
				if(l.cabeca == NULL){
					printf("Nenhum transporte cadastrado !\n");
					sleep(2);
					limpar_tela();
					break;
				}
					
				else{
					printf("ID: ");
					scanf("%d", &id);
					getchar();
					busca(&l,  id);
					break;
				}
			
			case '0':
				printf("Saindo...\n");
				sleep(2);
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
	
	printf("Obrigado por usar o SGCL.\n");
	sleep(2);
	
	return 123;
}

