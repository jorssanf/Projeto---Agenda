//Jorge Roberto Sousa dos Santos Filho - Projeto de Introdução à programação

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct Contato{
	    int id;
	    char primeiroNome[20];
		char sobrenome[20];
		char telefone[16];
		char email[20];
		char aniversario[10];
		char tipoSanguineo[3];
};

typedef struct Contato contato;

int quant;

contato *contatos;

void quantidadeContatos();
void listarContatos();
void buscarContato(char nomeContato[]);
void apagarContato(char nomeContato[]);
void AtualizarQuantContatos(int contatosAdicionados);
void gravarContatos(contato *contatos, int contatosAdicionados);
void gerarContatos();
int  menu();
int  adicionarContatos();


int main(void){
	setlocale(LC_ALL, "Portuguese");	
	
	return menu();
}

int menu(){
	int opcao, executando=1, numContatos;
	char nome[50];
	
	while(executando){
		quantidadeContatos();
		system("cls");
		printf("\n\n************** AGENDA TELEFONICA **************\n\n");
		
			printf("Digite 1 para inserir um contato:\n");
		    printf("Digite 2 para listar os contatos:\n");
		    printf("Digite 3 para remover um contato:\n");
		    printf("Digite 4 para pesquisar um contato:\n");
		    printf("Digite 5 para encerrar o programa:\n");
			scanf("%d", &opcao);
		
		switch(opcao){
			
			case 1:
				system("cls");
				numContatos = adicionarContatos();
			    AtualizarQuantContatos(numContatos);
			    gerarContatos();
			break;
			
			case 2:
				listarContatos();
			break;
						
			case 3:
				system("cls");
				setbuf(stdin, NULL);
				printf("\n\n************** Apagar contatos **************\n\n");
				printf("Digite o nome do contato a ser deletado: ");	
				scanf("%[^\n]50s", &nome);
			    apagarContato(nome);
			break;
			
			case 4:
				system("cls");
				setbuf(stdin, NULL);
				printf("\n\n************** Buscar contatos **************\n\n");
				printf("Digite o nome do contato a ser buscado: ");
				scanf("%[^\n]50s", &nome);
				buscarContato(nome);
			break;
		
			case 5:
				executando = 0;	
			break;
				
		}
	}
	
	return EXIT_SUCCESS;	
}

void AtualizarQuantContatos(int numContatos){
	
	FILE *qtdAt = fopen("quantContatos.txt","w");
	
	if(qtdAt==NULL){
		printf("Não foi possível abrir o arquivo!");
	}
	
	quant = quant+numContatos;
	
	fprintf(qtdAt, "%d", quant);
	
	fclose(qtdAt);	
}

int adicionarContatos(){

	printf("************** Adicionar Contato **************\n\n");
	
	contatos = (contato*) malloc(sizeof(contato)); 
	
	int contQuant=quant+1,i;
	char primeiroNome[20], sobrenome[20], telefone[16], aniversario[10], email[20], tipoSanguineo[3];
		
			contato c;
			
			c.id = contQuant;
			
			setbuf(stdin, NULL);
			printf("\nDigite o nome do contato: ");
			scanf("%[^\n]100s", primeiroNome);
			strcpy(c.primeiroNome, primeiroNome);
			
			setbuf(stdin, NULL);
			printf("Digite o sobrenome : ");
			scanf("%[^\n]100s", sobrenome);			
			strcpy(c.sobrenome, sobrenome);
				
			setbuf(stdin, NULL);
			printf("Digite o email: ");
			scanf("%[^\n]100s", email);				
			strcpy(c.email, email);
			
			setbuf(stdin, NULL);
			printf("Digite o número do telefone: ");
			scanf("%[^\n]100s", telefone);
			strcpy(c.telefone, telefone);
			
			setbuf(stdin, NULL);
			printf("Digite a data de nascimento:[dd/mm/AAAA] ");
			scanf("%[^\n]100s", aniversario);			
			strcpy(c.aniversario, aniversario);
			
			setbuf(stdin, NULL);
		    printf("Digite o tipo sanguineo: ");
			scanf("%[^\n]100s", tipoSanguineo);			 			
			strcpy(c.tipoSanguineo, tipoSanguineo);
			
			*(contatos) = c;	
			
		FILE *salvar = fopen("salvarContatos.txt","a");
		
		if (salvar == NULL) 
			printf("O arquivo não pode ser aberto.\n");		
		
		fwrite(&c, sizeof(contato),01,salvar);
		
		fclose(salvar);
	
	return 1;
}

void gerarContatos(){
	
	int i;
	contato contatos[quant];
	FILE *fb= fopen("salvarContatos.txt", "rb");
	
	if (fb == NULL)
		printf("O arquivo não pode ser aberto.\n");
	
	fread(contatos, sizeof(contatos[i]), quant, fb);

	fclose(fb);
	
	FILE *ft = fopen("contatos.txt","w");
	
	if (ft == NULL)
		printf("O arquivo não pode ser aberto.\n");
	
	for(i=0;i<quant;i++){
		fprintf(ft, "ID: %d\n", contatos[i].id); 
		fprintf(ft, "Nome: %s\n", contatos[i].primeiroNome);
		fprintf(ft, "Sobrenome: %s\n", contatos[i].sobrenome);
		fprintf(ft, "Telefone: %s\n", contatos[i].telefone);
		fprintf(ft, "Email: %s\n", contatos[i].email);
		fprintf(ft, "Data de nascimento: %s\n", contatos[i].aniversario);
		fprintf(ft, "Tipo sanguineo: %s\n\n", contatos[i].tipoSanguineo);
		
	}
	
	fclose(ft);

}

void listarContatos(){
	contato cLidos[quant];
		int i, contatosRegistrados, ultimoRegistro=0;
	
		FILE *ft = fopen("salvarContatos.txt", "rb");
		
		if (ft == NULL)
			printf("O arquivo não pode ser aberto.\n");
		
		system("cls");
		printf("\n\n************** Listagem de contatos **************\n\n");	
		
		contatosRegistrados = fread(cLidos, sizeof(cLidos[i]), (quant - ultimoRegistro), ft);
		
		if((quant - ultimoRegistro)!=0){
			for(i=0;i<(quant - ultimoRegistro);i++){					
				printf("ID: %d\n", cLidos[i].id); 
				printf("Nome: %s\n", cLidos[i].primeiroNome);
				printf("Sobrenome: %s\n", cLidos[i].sobrenome);
				printf("Telefone: %s\n", cLidos[i].telefone);
				printf("Email: %s\n", cLidos[i].email);
				printf("Data de nascimento: %s\n", cLidos[i].aniversario);
				printf("Tipo sanguineo: %s\n\n", cLidos[i].tipoSanguineo);
			}		
		}
	
		if(quant==0)
			printf("Não há contatos registrados\n");			
		
	fclose(ft);
	printf("\nPressione enter para voltar ao menu...\n");
	getch();

}

void quantidadeContatos(){
	FILE *qtd = fopen("quantContatos.txt", "r");
	char str[10];
	
	if (qtd == NULL){	
		FILE *qtdNovo = fopen("quantContatos.txt","w");
		
		if(qtdNovo==NULL)
			printf("O arquivo não pode ser aberto\n");
		
		fprintf(qtdNovo, "%d", 0);
		
		fclose(qtdNovo);	
	}
	else{
		fgets(str, 10, qtd);
		quant = atoi(str);
				
	}
	
	fclose(qtd);

}

void buscarContato(char nomeContato[]){
	FILE *fBuscaNome = fopen("salvarContatos.txt", "r");
	contato contatosAchados[10], contatosBuscados[quant];
	int i,cont=0;
	
	if(fBuscaNome==NULL)
		printf("O arquivo não pode ser aberto!\n");	
	
	fread(contatosBuscados, sizeof(contatosBuscados[i]), quant, fBuscaNome);
	
	for(i=0;i<=quant;i++){
		if((strstr(contatosBuscados[i].primeiroNome, nomeContato))!=NULL){
			contatosAchados[0] = contatosBuscados[i];
			cont++;
		}
	}
	
	if(cont>0){
		printf("\nOs seguintes contatos foram encontrados:\n\n");
		
		for(i=0;i<cont;i++){
		  printf("Nome: %s\n", contatosAchados[i].primeiroNome);
		  printf("Sobrenome: %s\n", contatosAchados[i].sobrenome);
		  printf("Telefone: %s\n", contatosAchados[i].telefone);
		  printf("Email: %s\n", contatosAchados[i].email);
		  printf("Data de nascimento: %s\n", contatosAchados[i].aniversario);
		  printf("Tipo sanguineo: %s\n\n", contatosAchados[i].tipoSanguineo);
		}
		
	}
	else{
		printf("\n%s não foi encontrado\n", nomeContato);
	}
	
	printf("\nPressione enter para voltar ao menu...");
	getch();
	
}

void apagarContato(char nomeContato[]){  

 FILE *arquivo = fopen("salvarContatos.txt", "r");

	contato c, contatos[quant];
	int i,achei=0;
	
	fread(contatos, sizeof(contatos[i]),quant, arquivo);

	for(i=0;i<=quant;i++){
		if((strstr(contatos[i].primeiroNome, nomeContato))!=NULL){
		 c = contatos[i];
		 achei++;	
			
		}			
		
	}
			
	fclose(arquivo);
	
	contato cLidos[quant];
	int opcao;		
						
	if(achei){	
			printf("\nConfirmar exclusão do contato?\n\n");
			printf("Nome: %s\n",c.primeiroNome);
			
			setbuf(stdin, NULL);
			printf("\nTem certeza que deseja excluir o contato?\nDigite 1 para Sim e 0 para Não. ");
			scanf("%d",&opcao);
			
			if(opcao==1){
									
				FILE *f = fopen("salvarContatos.txt", "rb");
									
				int contatosRegistrados = fread(cLidos, sizeof(cLidos[i]), quant, f);
				int idCorrente; 
				int achou=0,cont=0;
				
				fclose(f);
				
				FILE *salvar = fopen("salvarContatos.txt","w");
							
				for(i=0;i<quant;i++){
					if(cLidos[i].id!=c.id)									
					fwrite(&cLidos[i], sizeof(contato),01,salvar);														
				}
				
				fclose(salvar);
				
				quant = quant -1;
				AtualizarQuantContatos(0);
				gerarContatos();
				printf("\nContato excluido com sucesso!\n");
				
	        }else{
	        	menu();
			
			}
    } else {
		printf("\nNenhum contato encontrado com esse nome!\n");
		
	}

	printf("\nPressione enter para voltar ao menu...\n");
	getch();
}


 


