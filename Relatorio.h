#include <stdio.h>
#include <windows.h>

void Rel_Transportes(){
	
	Linha l;
	DIR caminho = ".\\Transporte\\Arquivos\\Transportes\\";//String que armazena o caminho 
    DIR nome_arquivo;
    
    //nome_arquivo recebe o caminho e tbm o ficheiro txt
    sprintf(nome_arquivo, "%stransportes.txt", caminho);
    
    FILE *arquivo = fopen(nome_arquivo, "r");//*arquivo recebe o caminho caminho do ficheiro e "r" permite a leitura do ficheiro
    
    //Se o arquivo for igual a null quer dizer q a criação do arquivo falhou ou que ele não existe;
    if(arquivo == NULL){
        printf("Nenhum transporte cadastrado !\n");
        sleep(2);
        limpar_tela();
        return;
    }
    
    //enquanto o resultado de fgets for diferente de NULL 
    while(fgets(l, sizeof(l), arquivo) != NULL){
    	printf("%s", l);//apresente o resultado da linha
    	sleep(1);
	}
    	
    fclose(arquivo);//fecha o arquivo txt após o uso dele
    return;   
}

void Rel_Terminais() {
    linha l; // Buffer para armazenar cada linha do arquivo
    DIR caminho = ".\\Terminais\\Arquivos\\Terminais\\"; // Diretório base para armazenamento
    DIR nome_arquivo; // Buffer para montar o caminho completo

    // Monta o caminho completo do arquivo (concatena diretório + nome do arquivo)
    snprintf(nome_arquivo, sizeof(nome_arquivo), "%sTerminais.txt", caminho);
    
    // Tenta abrir o arquivo em modo leitura (r = read)
    FILE *arquivo = fopen(nome_arquivo, "r");
    
    // Verifica se houve erro na abertura
    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo de terminais!\n");
        return;
    }
    
    // Imprime cabeçalho para organização
    printf("\n====== LISTAGEM DE TERMINAIS ======\n");
    
    // Lê o arquivo linha por linha até o final (EOF)
    while(fgets(l, sizeof(l), arquivo) != NULL){
    	printf("%s", l);//apresente o resultado da linha
    	sleep(1);
	}
    
    // Fecha o arquivo após o uso (boas práticas)
    fclose(arquivo);
    
    printf("\n====== FIM DA LISTAGEM ======\n");
    return;
}

void Rel_Cargas(){
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
    while(fgets(l, sizeof(l), arquivo) != NULL){
    	printf("%s", l);//apresente o resultado da linha
    	sleep(1);
	}
    
    // Fecha o arquivo após o uso (boas práticas)
    fclose(arquivo);
    
    printf("\n====== FIM DA LISTAGEM ======\n");
    return;
}

void Relatorio (){
	system("cls");
	 printf("\n====== LISTAGEM DE TRANSPORTES ======\n");
	Rel_Transportes();
	printf("\n====== FIM DA LISTAGEM ======\n");
	printf("\n");
	
	sleep(2);
	Rel_Terminais();
	printf("\n");
	
	Rel_Cargas();
	printf("\n");
	
	sleep(10);
	system("cls");
}
