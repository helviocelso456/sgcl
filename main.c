#include "main.h"



int main(){
	setlocale(LC_ALL, "Portuguese");
    
    int i = 1;
    
    
    while(i != 0)
    {
    	Menu_Central();
    	char op;
    	scanf(" %c", &op);
    	//Switch Case
    	switch(op)
    	{
    		case '1':
    		limpar_tela();
    	    Main_Transporte();
    	    break;
    	    
    	    case '2':
    	    limpar_tela();
    	    Main_Terminais();
    	    break;
    	    
    	    case '3':
    	    limpar_tela();
    	    //main_Cargas();
    	    break;
    	    
    	    case '4':
    	    i = 0;
    	    break;
    	    
    	    default:
    	    printf("Opção Invalida");
    	    
		}
    	
	}
    
	return 123;
}

