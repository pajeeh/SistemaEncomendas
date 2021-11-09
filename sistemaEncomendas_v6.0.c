// BIBLIOTECAS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>

// PERFUMARIA
#define RED "\x1B[31m"
#define GREEN "\x1B[32;1m"
#define BRGREEN "\e[92;5m"
#define BHRED "\e[1;91m"
#define BHYELLOW "\e[1;33m"
#define BHMAG "\e[1;95m"
#define BHBLUE "\e[1;94m"
#define CIANO "\e[36;5m"
#define RESET "\x1B[0m"
#define MAX 100

typedef struct data
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct endereco
{
    char rua[50];
    char bairro[50];
    char cidade[50];
    char estado[50];
    int cep;
    int numero;
    char complemento[50];
} Endereco;

typedef struct dadosClientes
{
    char nome[50];
    char cpf[11];
    char rg[12];
    char telefone[12];
    char email[50];
    int idade;
    int sexo;
    Data data_nasc;
    Endereco *endereco;
} DadosClientes;

typedef struct detalhesProduto
{
    int *codigo;
    char *nome[50];
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
} DetalhesProduto;

typedef struct cadastroClientes
{
    DadosClientes dados;
    struct cadastroClientes *proximo;
} CadastroClientes;

typedef struct tag_pedido
{
    int codigoPedido;
    int cod_cliente;
    int quantidade;
    int status;
    DetalhesProduto produto;
    Endereco enderecoEntrega;
    Data data_pedido;
    Data data_entrega;
    struct pedido *proximaEntrega; // Armazena o próximo pedido num ponteiro
} Pedido;

//PROTÓTIPOS DAS FUNÇÕES

void inserir(Pedido **cabeca);//Insere um pedido na lista
void listar(Pedido *cabeca, FILE *arquivo);//Imprime na tela todos os pedidos armazenados no arquivo
Pedido* leArquivo(FILE *arquivo);//Lê a lista de pedidos a partir de um arquivo
//void listarPorStatus(Pedido *cabeca, char *criterio, char *status);//Lista pedidos por status
FILE * abreArquivo(char *nomeArquivo, const char *modo);//Abre um arquivo
void salvarArquivo(Pedido *cabeca, FILE *arquivo);//Salva a lista de pedidos em um arquivo
//void listarPorData(Pedido *cabeca, char *criterio, char *valor);//Lista pedidos por data
//void listarPorCliente(Pedido *cabeca, char *criterio, char *valor);//Lista pedidos por cliente
//oid listarPorCodigo(Pedido *cabeca, char *criterio, char *valor);//Lista pedidos por código
//void listarPorProduto(Pedido *cabeca, char *criterio, char *valor);//Lista pedidos por produto
//void listarPorEndereco(Pedido *cabeca, char *criterio, char *valor);//Lista pedidos por endereço
void leCliente(DadosClientes *cliente);//Lê os dados de um cliente
void leProduto(DetalhesProduto *produto);//Lê os dados de um produto
void leEndereco(Endereco *endereco);//Lê os dados de um endereço
void lePedido(Pedido *pedido);//Lê os dados de um pedido
void lePedidoCliente(Pedido *pedido);//Lê os dados de um pedido e seu cliente
void leDadosNo(Pedido *novono);
void imprimeNo(FILE *arquivo, Pedido *noatual);
Pedido* desalocaLista(Pedido* cabeca);
void alocaCopia(char **, char*);
//void alterarEntrega(Pedido *cabeca);
//void excluirPedido(Pedido **cabeca, int codigo);
void buscarPedido(Pedido *cabeca, int codigo);

void titulo()
{
    printf(BRGREEN"\t\tSISTEMA DE ENCOMENDAS\n\n"RESET);
}

void sair()
{
    exit(0);
}

//FUNÇÃO PRINCIPAL
int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    Pedido *cabeca = NULL;
    char q;
    FILE *arquivo = NULL;

    titulo();
    do{
        printf(BHBLUE"\nOPÇÕES\n"RESET);
        printf(BHMAG"\n(1) -> Inserir Entrega"RESET);
        printf(BHMAG"\n(2) -> Pesquisar Entrega"RESET);
        printf(BHMAG"\n(3) -> Alterar Entrega"RESET);
        printf(BHMAG"\n(4) -> Excluir Entrega"RESET);
        printf(BHMAG"\n(5) -> SAIR"RESET);
        printf(BHBLUE"\n\nDigite a opção desejada: "RESET);
        
        fflush(stdin);      // Limpa o buffer de entrada
        scanf("%d", &q);    // Lê a opção do usuário
        fflush(stdin);      // Limpa o buffer de entrada
        switch(q)           // Verifica qual opção foi escolhida
        {
            case 1:
                inserir(&cabeca);
                break;
            case 2:
                listar(cabeca, arquivo);
                break;
            case 3:
                alterarPedidoPorLinha(cabeca);
                break;
            case 4:
                excluirPedidoPorLinha(&cabeca, 0);
                break;
            case 5:
                sair();
                break;
            default:
                printf(BHRED"\n\nOPÇÃO INVÁLIDA !\n"RESET);
                break;
        }
    }while(q != 5);
    cabeca = desalocaLista(cabeca);
}
//DESALOCA A MEMÓRIA ALOCADA PARA OS ELEMENTOS DA LISTA
Pedido* desalocaLista(Pedido* cabeca)
{
    Pedido *aux = cabeca;
    Pedido *aux2 = NULL;
    while(aux != NULL)
    {
        aux2 = aux->proximaEntrega;
        free(aux);
        aux = aux2;
    }
    return cabeca;
}

//LISTA TODOS OS PEDIDOS NA LISTA ENCADEADA
void listar(Pedido *cabeca, FILE *arquivo)
{
    Pedido *aux = cabeca;
    if(aux == NULL)
    {
        printf(BHRED"\n\nNão há pedidos cadastrados!\n\n"RESET);
    }
        else
        {
            printf(BHBLUE"\n\nCÓDIGO\t\tCLIENTE\t\tPRODUTO\t\tDATA\t\tSTATUS\n"RESET);
            while(aux != NULL)
            {
                printf(BHBLUE"\n%d\t\t%d\t\t%s\t\t%d/%d/%d\t\t%d\n"RESET, aux->codigoPedido, aux->cod_cliente, aux->produto.nome, aux->data_pedido.dia, aux->data_pedido.mes, aux->data_pedido.ano, aux->status);
                aux = aux->proximaEntrega;
            }
        }
}

//LISTA OS PEDIDOS DE MANEIRA SELETIVA, POR STATUS
/*void listarPorStatus(Pedido *cabeca, char *criterio, char *status)
{
    Pedido *aux = cabeca;
    if(aux == NULL)
    {
        printf(BHRED"\n\nNão há pedidos cadastrados!\n\n"RESET);
    }
        else
        {
            printf(BHBLUE"\n\nCÓDIGO\t\tCLIENTE\t\tPRODUTO\t\tDATA\t\tSTATUS\n"RESET);
            while(aux != NULL)
            {
                if(strcmp(aux->status, status) == 0)
                {
                    printf(BHBLUE"\n%d\t\t%d\t\t%s\t\t%d/%d/%d\t\t%d\n"RESET, aux->codigoPedido, aux->cod_cliente, aux->produto.nome, aux->data_pedido.dia, aux->data_pedido.mes, aux->data_pedido.ano, aux->status);
                }
                aux = aux->proximaEntrega;
            }
        }
}*/ //Tirei porque não estava funcionando direito

//BUSCA UM PEDIDO NA LISTA E IMPRIME SEU DETALHE
void buscarPedido(Pedido *cabeca, int codigo)
{
    Pedido *aux = cabeca;
    if(aux == NULL)
    {
        printf(BHRED"\n\nNão há pedidos cadastrados!\n\n"RESET);
    }
        else
        {
            while(aux != NULL)
            {
                if(aux->codigoPedido == codigo)
                {
                    printf(BHBLUE"\n\nCÓDIGO\t\tCLIENTE\t\tPRODUTO\t\tDATA\t\tSTATUS\n"RESET);
                    printf(BHBLUE"\n%d\t\t%d\t\t%s\t\t%d/%d/%d\t\t%d\n"RESET, aux->codigoPedido, aux->cod_cliente, aux->produto.nome, aux->data_pedido.dia, aux->data_pedido.mes, aux->data_pedido.ano, aux->status);
                }
                aux = aux->proximaEntrega;
            }
        }
}

//FUNÇÃO PARA ABRIR ARQUIVO


//FUNÇÃO PARA INSERIR UM NOVO PEDIDO AO FINAL DO ARQUIVO
void inserir(Pedido **cabeca)
{
    Pedido *aux = *cabeca;
    Pedido *novo = (Pedido*)malloc(sizeof(Pedido));
    if(novo == NULL)
    {
        printf(BHRED"\n\nNão foi possível alocar memória!\n\n"RESET);
    }
        else
        {
            printf(BHBLUE"\n\nDigite o código do pedido: "RESET);
            scanf("%d", &novo->codigoPedido);
            printf(BHBLUE"\nDigite o código do cliente: "RESET);
            scanf("%d", &novo->cod_cliente);
            printf(BHBLUE"\nDigite o nome do produto: "RESET);
            fflush(stdin);
            gets(novo->produto.nome);
            printf(BHBLUE"\nDigite a data do pedido (DD/MM/AAAA): "RESET);
            scanf("%d/%d/%d", &novo->data_pedido.dia, &novo->data_pedido.mes, &novo->data_pedido.ano);
            printf(BHBLUE"\nDigite o status do pedido (0 - Pendente, 1 - Entregue): "RESET);
            scanf("%d", &novo->status);
            novo->proximaEntrega = NULL;
            if(aux == NULL)
            {
                *cabeca = novo;
            }
        }
}


//ENTRA COM OS DADOS VIA TECLADO E ARMAZENA NO NÓ DA LISTA
/*void leDadosNo(Pedido *novono)
{
    char buffer[MAX];


}*/

//LÊ A LISTA DE PEDIDOS ARMAZENADA EM UM ARQUIVO E RETORNA O PONTEIRO PARA O NÓ CABEÇA DA LISTA
/*Pedido *lerPedidos(FILE *arquivo)
{

}*/

//FUNÇÃO PARA EXCLUIR UM PEDIDO DA LISTA
/*void excluirPedido(Pedido **cabeca, int codigo)
{
    Pedido *aux = *cabeca;
    Pedido *aux2 = NULL;
    if(aux == NULL)
    {
        printf(BHRED"\n\nNão há pedidos cadastrados!\n\n"RESET);
    }
        else
        {
            while(aux != NULL)
            {
                if(aux->codigoPedido == codigo)
                {
                    if(aux == *cabeca)
                    {
                        *cabeca = aux->proximaEntrega;
                    }
                    else
                    {
                        aux2->proximaEntrega = aux->proximaEntrega;
                    }
                    free(aux);
                    printf(BRGREEN"\n\nPEDIDO EXCLUÍDO COM SUCESSO!\n\n"RESET);
                    return;
                }
                aux2 = aux;
                aux = aux->proximaEntrega;
            }
            printf(BHRED"\n\nPEDIDO NÃO ENCONTRADO!\n\n"RESET);
        }
}
*/

//FUNÇÃO PARA EXCLUIR PEDIDO POR LINHA
void excluirPedidoPorLinha()
{
    FILE *fileptr1, *fileptr2;
    char nomeArquivo1[MAX], ctrl;
    int linhaSelecionada, temp = 1;
    titulo();
    fileptr1 = fopen("pedidos.txt", "rt");
    ctrl = getc(fileptr1);
    while(ctrl != EOF)
    {
        printf("%c", ctrl);
        ctrl = getc(fileptr1);
    }
    rewind(fileptr1);
    printf("Digite o número da linha que será excluída: ");
    scanf("%d", &linhaSelecionada);
    //Abrir em modo de escrita para editar
    fileptr2 = fopen("bckp.txt", "wt");
    ctrl = getc(fileptr1);
    while(ctrl != EOF)
    {
        if(temp == linhaSelecionada)
        {
            ctrl = getc(fileptr1);
            while(ctrl != '\n')
            {
                ctrl = getc(fileptr1);
            }
        }
        else
        {
            fprintf(fileptr2, "%c", ctrl);
            ctrl = getc(fileptr1);
        }
        temp++;
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove(nomeArquivo1);
    rename("bckp.txt", nomeArquivo1);
    printf(BRGREEN"\n\nPEDIDO DA LINHA %d EXCLUÍDO COM SUCESSO!\n\n", linhaSelecionada,RESET);
    printf("\nConteúdo do arquivo modificado: ");
    fileptr1 = fopen(nomeArquivo1, "rt");
    ctrl = getc(fileptr1);
    while(ctrl != EOF)
    {
        printf("%c", ctrl);
        ctrl = getc(fileptr1);
    }
    fclose(fileptr1);
    return 0;
}

void alterarPedidoPorLinha()
{
    FILE *fileptr1, *fileptr2;
    char nomeArquivo1[MAX], ctrl;
    int linhaSelecionada, temp = 1;
    titulo();
    fileptr1 = fopen("pedidos.txt", "rt");
    ctrl = getc(fileptr1);
    while(ctrl != EOF)
    {
        printf("%c", ctrl);
        ctrl = getc(fileptr1);
    }
    rewind(fileptr1);
    printf("Digite o número da linha que será alterada: ");
    scanf("%d", &linhaSelecionada);
    //Abrir em modo de escrita para editar
    fileptr2 = fopen("bckp.txt", "wt");
    ctrl = getc(fileptr1);
    while(ctrl != EOF)
    {
        if(temp == linhaSelecionada)
        {
            ctrl = getc(fileptr1);
            while(ctrl != '\n')
            {
                ctrl = getc(fileptr1);
            }
        }
        else
        {
            fprintf(fileptr2, "%c", ctrl);
            ctrl = getc(fileptr1);
        }
        temp++;
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove(nomeArquivo1);
    rename("bckp.txt", nomeArquivo1);
}
