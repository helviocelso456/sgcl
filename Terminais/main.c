#include "Terminais.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    LISTA l;
    inicializarTerminal(&l);
    TERMINAL t = {1,"Moxico",200,100};
    registoTerminais(&l,t);
    ListarTerminais(&l);
    return 0;
}