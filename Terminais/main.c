#include "Terminais.h"

int main()
{
    setlocale(LC_ALL, "");
    LISTA l;
    inicializarTerminal(&l);
    TERMINAL t;
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
    	    MenuRegistar(&l,t);
    	    break;
    	    
    	    case '2':
    	    ListagemTerminaisTexto();
    	    break;
    	    
    	    case '3':
    	    
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
