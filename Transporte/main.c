#include "Transporte.h"

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
				show_t();
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
					show_id(id);
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

