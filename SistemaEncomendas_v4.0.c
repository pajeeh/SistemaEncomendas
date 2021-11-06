// BIBLIOTECAS
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include<ctype.h>

// PERFUMARIA	
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define BRGREEN "\x1B[1;92m"
#define BHRED   "\e[1;91m"
#define BHYELLOW "\e[1;33m"
#define BHMAG   "\e[1;95m"
#define BHBLUE  "\e[1;94m"
#define CIANO   "\e[36;5m"
#define RESET   "\x1B[0m"

typedef struct{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct{
    char nome[50];
    char cpf[11];
    char rg[12];
    char endereco[50];
    char telefone[12];
    char email[50];
    Data data_nasc;
    int idade;
    int sexo;
} Cliente;

typedef struct{
    int codigo;
    char nome[50];
    char descricao[50];
    float preco;
    int status;
    float peso;
    float Altura;
    float Largura;
    float Comprimento;
    float Volume;
    float volume_total;
    float Peso_total;
} Produto;

typedef struct{
    char rua[50];
    char bairro[50];
    char cidade[50];
    char estado[50];
    int cep;
    int numero;
    char complemento[50];
} Endereco;

typedef struct{
    Produto detalhes;
    int quantidade;
    Endereco enderecoEntrega;
} Pedido;
Pedido pedido;

void Add_Entrega(){
    char op;
    FILE *arqEntrega;
    arqEntrega = fopen("entrega.txt", "a+");
    if(arqEntrega == NULL){
        //printf("Erro ao abrir o arquivo\n");
        arqEntrega = fopen("entrega.txt", "w");
    }
    titulo();
    printf(BHBLUE"\n\tCADASTRAR NOVA ENTREGA"RESET);
    
    printf("\nDADOS DO PRODUTO: ");
    if(arqEntrega){
        do{
            printf("\n\tCodigo: ");
            //scanf("%d", &pedido.detalhes.codigo);
            gets(pedido.detalhes.codigo);
            fprintf(arqEntrega, "%d\n", pedido.detalhes.codigo);//colocar no final tira o erro

            /*printf("\n\tNome: ");
            scanf("%s", pedido.detalhes.nome);
            printf("\n\tDescricao: ");
            scanf("%s", pedido.detalhes.descricao);
            printf("\n\tPreco: ");
            scanf("%f", &pedido.detalhes.preco);
            printf("\n\tStatus: ");
            scanf("%d", &pedido.detalhes.status);
            printf("\n\tPeso: ");
            scanf("%f", &pedido.detalhes.peso);
            printf("\n\tAltura: ");
            scanf("%f", &pedido.detalhes.Altura);
            printf("\n\tLargura: ");
            scanf("%f", &pedido.detalhes.Largura);
            printf("\n\tComprimento: ");
            scanf("%f", &pedido.detalhes.Comprimento);
            printf("\n\tVolume: ");
            scanf("%f", &pedido.detalhes.Volume);
            printf("\n\tVolume Total: ");
            scanf("%f", &pedido.detalhes.volume_total);
            printf("\n\tPeso Total: ");
            scanf("%f", &pedido.detalhes.Peso_total);
            printf("\n\tQuantidade: ");
            scanf("%d", &pedido.quantidade);*/
           
            printf("Deseja cadastrar outra entrega?: Y ou N");
            scanf("%s",&op);
        }while(op=='y' || op=='Y');
    }
    fclose(arqEntrega);

    printf("\n\tRua: ");
    scanf("%s", pedido.enderecoEntrega.rua);
    printf("\n\tBairro: ");
    scanf("%s", pedido.enderecoEntrega.bairro);
    printf("\n\tCidade: ");
    scanf("%s", pedido.enderecoEntrega.cidade);
    printf("\n\tEstado: ");
    scanf("%s", pedido.enderecoEntrega.estado);
    printf("\n\tCEP: ");
    scanf("%d", &pedido.enderecoEntrega.cep);
    

}

void titulo()
{
    printf(GREEN"\t\t SISTEMA DE ENCOMENDAS\n"RESET);
}

void excluir()
{   
    FILE *fileptr1, *fileptr2;
    char nomeArq[40], ch;
    int linha_selecionada, temp = 1;
    titulo();
    /*printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArq);
    fileptr1 = fopen(nomeArq,"r");*/ // Abrir em modo de leitura
    fileptr1 = fopen("entrega.txt", "r");
    ch = getc(fileptr1);
    while(ch!=EOF)
    {
        printf("%c",ch);
        ch = getc(fileptr1);
    }
    rewind(fileptr1);
    printf("\nDigite o número da linha que será deletada: ");
    scanf("%d",&linha_selecionada);
    // Abrir em modo de escrita para editar
    fileptr2 = fopen("copia.txt","w");
    ch = getc(fileptr1);
    while(ch!=EOF)
    {
        ch = getc(fileptr1);
        if(ch == '\n')
        temp++;
        if(temp != linha_selecionada)
        {
            putc(ch,fileptr2);//copia todas as linhas para o backup.c
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove(nomeArq);
    rename("backup.txt", nomeArq);
    printf("\nLINHA %d FOI APAGADA COM SUCESSO", linha_selecionada);
    printf("\nConteúdo do arquivo modificado:");
    fileptr1 = fopen(nomeArq,"r");
    ch = getc(fileptr1);
    while(ch != EOF)
    {
        printf("%c",ch);
        ch = getc(fileptr1);
    }
    fclose(fileptr1);
    return 0;
}

void sair()
{
    exit(0);
}

void menu()
	{   
        titulo();
		int op;
		do{
		printf("Escolha uma das opções abaixo:\n");
		printf(BHBLUE"(1)Adicionar Entrega\n"RESET);
		printf(BHYELLOW"(2)Pesquisar Entrega\n"RESET);
		printf(CIANO"(3)Alterar Entrega\n"RESET);
		printf(BHMAG"(4)Excluir Entrega\n"RESET);
        printf(RED"(0)SAIR DO SISTEMA\n"RESET);

		scanf("%d", &op);
		system("cls || clear");

		switch(op)
		{
			case 1:
			Add_Entrega();//função adicionar entrega
			break;

			case 2:
			//função pesquisar Entrega
			break;

			case 3:
			//função alterar entrega
			break;

			case 4:
			excluir();//função excluir entrega
			break;

            case 0:
            sair();

			default:
			printf("COMANDO NÃO PERMITIDO\n");
		}
			}while(op);
	}

void main() 
{
    setlocale(LC_ALL,"portuguese");
    char nomeARQUIVO[40];
    /*printf("Digite o nome do arquivo: \nEx.:DADOS.txt");
    scanf("%s", nomeARQUIVO);*/
    menu();
}
