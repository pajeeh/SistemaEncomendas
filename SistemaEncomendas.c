/* ####################################################################################################*/
//SOBRE O PROGRAMA
//Título: Sistema de Encomendas
//Subtítulo: Versão 9.0
//Descrição: Sistema de Encomendas para a disciplina de Algoritmos e Programação de Computadores II
//Autores: Luís A. G. Dos Santos - 256647, Thiago A. P. Correa 254366, Carolina Noda Morishita - 254187
//Faculdade de Tecnologia da Universidade Estadual De Campinas - FT UNICAMP
/* ####################################################################################################*/

#ifdef WIN32
system ("pause");
#endif

// BIBLIOTECAS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>

// PERFUMARIA DAS CORES DO TERMINAL, USANDO CÓDIGO DE CORES ANSI
#define RED         "\e[31m"    // 31 - RED
#define GREEN       "\e[32;1m"  // 32 - GREEN
#define CIANO       "\e[36;5m"  
#define YLW         "\e[33;1m"
#define BHGRN       "\e[92;5m"
#define BHRED       "\e[1;91m"
#define BHYLW       "\e[1;33m"
#define BHMAG       "\e[1;95m"
#define BHBLU       "\e[1;94m"
#define BHBLK       "\e[1;90m"
#define BHWHI       "\e[1;97m"
#define BHCYN       "\e[1;96m"
#define fundoPreto  "\e[40m"
#define RESET       "\x1B[0m"

#define MAX 50

float calcularTotal(float precoProduto, int quantidadeProduto, float taxaFrete);//função para calcular o valor total de uma encomenda

//ESTRUTURAS DE DADOS
typedef struct data
{
    char dia[3];
    char mes[15];
    char ano[5];
} Data;

typedef struct tamanhoStruct{
    float altura;
    float largura;
    float profundidade;
} Tamanho;

/* typedef struct codigoStruct{
    char codigo;
} Codigo;*/

typedef struct enderecoStruct{
    char numero[MAX];
    char rua[MAX];
    char bairro[MAX];
    char cidade[MAX];
    char estado[MAX];
    char pais[MAX];
    char cep[MAX];
} Endereco;

//Estrutura para armazenar os dados de um cliente
typedef struct clienteStruct{
    char nome[15];
    char cpf[15];
    char rg[15];
    char telefone[12];
    //Data data_nasc;
    Endereco end;
} Pessoa;

//Estrutura para armazenar os dados de um produto, como nome, preço, quantidade e descrição(Peso, tamanho, etc)
typedef struct produtoStruct{
    char codProduto[10];
    char nome[15];
    char descricao[15];
    char categoria[15];
    char cor[15];
    float preco;
    Tamanho tam;
} Produto;

//Estrutura para armazenar os dados do pedido, como o cliente, o produto, a quantidade e o valor total
typedef struct encomendaStruct{
    char codEncomenda[10];
    char status[2];//status do pedido, se está em andamento, finalizado, cancelado, etc
    char pessoa[15];//nome do cliente que fez o pedido
    char produto[15];//nome do produto que foi pedido
    char quantidade[10];//quantidade do produto que foi pedido
    char valorTotal;//valor total do pedido (quantidade * preço + taxa de frete)
    //Data data_encomenda;
    //Data data_entrega;
    Endereco endEntrega;
} Encomenda;

//Declaração de variáveis globais.
int input = 0;
int qtdClientes;
int tamClientes;
Pessoa *clientes;
FILE *arquivoClientes;
char clientes_dir[] = "Clientes.txt";
//char clientes_dirBin[] = "Clientes.bin";
int qtdProdutos;
int tamProdutos;
Produto *produtos;
FILE *arquivoProdutos;
char produtos_dir[] = "Produtos.txt";
//char produtos_dirBin[] = "Produtos.bin";
int qtdEncomendas;
int tamEncomendas;
Encomenda *encomendas;
FILE *arquivoEncomendas;
char encomendas_dir[] = "Encomendas.txt";
char encomendas_dirBin[] = "Encomendas.bin";

//Declaração de funções que serão utilizadas.
void titulo();//Função para imprimir o título do programa. Título: Sistema de Encomendas de Produtos. Subtítulo: Versão 9.0
void tituloProg();
void subTitulo();
void autores();
void descricao();
void about();//Função para exibir os dados do programa. Nome do programa, versão, autores, etc.
void encerrar();//Função para encerrar o programa. Chama a função exit(0); e exibe uma mensagem de encerramento.
void erro(char *nomeArquivo);//Função para exibir uma mensagem de erro, caso ocorra algum erro na abertura do arquivo.
void sucesso();//Função para exibir uma mensagem de sucesso. OPERAÇÃO REALIZADA COM SUCESSO!
void receberString(char *string_destino, int quantidade_caracteres);//Função para receber uma string de tamanho determinado.
void removerQuebraLinha(char *string);//Função para remover a quebra de linha do final de uma string.
void mensagem();

//MENU PRINCIPAL
void menu();//Função que mostra o menu inicial. Layout colorido com cores da perfumaria de cores. Todas as funções são chamadas por ela.
//Opção 1 exibe o menu de gerenciamento de clientes na cor ciano e título em verde.
//Opção 2 exibe o menu de gerenciamento de produtos na cor amarela e título em verde.
//Opção 3 exibe o menu de gerenciamento de encomendas na cor magenta e título em verde.
//Opção 4 finaliza o programa exibindo a mensagem de despedida na cor vermelha e fundo preto.
//Opção 5 chama a função about e exibe os dados do programa, na cor branco e fundo preto.

//MENU DE GERENCIAMENTO DE CLIENTES. Segue o mesmo layout do menu principal.
void menuClientes();//Função que mostra o menu de gerenciamento de clientes. Segue o modelo do menu inicial. Título: GERENCIAMENTO DE CLIENTES
//Opção 1 cadastra um novo cliente e exibe o menu de gerenciamento de clientes quando finalizado o cadastro
//Opção 2 lista todos os clientes cadastrados no sistema (ordenados por código)
//Opção 3 busca um cliente pelo Código de Cliente e exibe seus dados. Se não encontrar, exibe a mensagem de erro.
//Opção 4 exclui um cliente pelo Código de Cliente e exibe a mensagem de sucesso. Se não encontrar, exibe a mensagem de erro.
//Opção 5 exibe o menu de alterar dados de um cliente
//Opção 6 Voltar ao menu inicial
//Opção 7 encerrar o programa

void cadastrarCliente();//Função que cadastra um cliente. Aponta para estrutura Pessoa. Armazena os dados nas variáveis da estrutura.
int removerCliente();//Função que remove um cliente do arquivo Clientes.txt. Retorna 1 se o cliente foi removido com sucesso, e 0 caso contrário.

//MENU DE ALTERAR DADOS DOS CLIENTES. Segue o modelo do menu inicial.
void menuAlterarCliente();//Função que mostra o menu de alteração de clientes. Layout colorido com cores. Segue o modelo do menu inicial.
//Opção 1 altera o nome do cliente
//Opção 2 altera o sexo do cliente
//Opção 3 altera a data de nascimento do cliente
//Opção 4 altera o endereço do cliente
//Opção 5 altera o telefone do cliente
//Opção 6 Voltar ao menu de gerenciamento de clientes
void alterarNomeCliente();//Abre o arquivo de clientes e altera o nome do cliente pelo código de cliente.
void alterarCPFCliente();//Abre o arquivo de clientes e altera o CPF do cliente pelo código de cliente.
void alterarRGCliente();//Abre o arquivo de clientes e altera o RG do cliente pelo código de cliente.
void alterarTelefoneCliente();//Abre o arquivo de clientes e altera o telefone do cliente pelo código de cliente.
void alterarEmailCliente();//Abre o arquivo de clientes e altera o email do cliente pelo código de cliente.
void alterarDataNascCliente();//Abre o arquivo de clientes e altera a data de nascimento do cliente pelo código de cliente.
void alterarEnderecoCliente();//Abre o arquivo de clientes e altera o endereço do cliente pelo código de cliente.

//MENU DE GERENCIAMENTO DE PRODUTOS. Segue o modelo do menu inicial.
void menuProdutos();//Função que mostra o menu de gerenciamento de produtos. Segue o modelo do menu inicial. Título: GERENCIAMENTO DE PRODUTOS
//Opção 1 cadastra um novo produto e exibe o menu de gerenciamento de produtos quando finalizado o cadastro
//Opção 2 lista todos os produtos cadastrados no sistema (ordenados por código)
//Opção 3 busca um produto pelo Código de Produto e exibe seus dados. Se não encontrar, exibe a mensagem de erro.
//Opção 4 exclui um produto pelo Código de Produto e exibe a mensagem de sucesso. Se não encontrar, exibe a mensagem de erro.
//Opção 5 exibe o menu de alteração de produtos
//Opção 6 Voltar ao menu inicial
//Opção 7 encerrar o programa

//MENU DE ALTERAR DADOS DOS PRODUTOS. Segue o modelo do menu inicial.
void menuAlterarProduto();//Função que mostra o menu de alteração de produtos. Segue o modelo do menu inicial.
void alterarNomeProduto();//Abre o arquivo de produtos e altera o nome do produto.
void alterarPrecoProduto();//Abre o arquivo de produtos e altera o preço do produto.
void alterarQuantidadeProduto();//Abre o arquivo de produtos e altera a quantidade do produto.
void alterarDescricaoProduto();//Abre o arquivo de produtos e altera a descrição do produto.
void alterarCategoriaProduto();//Abre o arquivo de produtos e altera a categoria do produto.
void alterarMarcaProduto();//Abre o arquivo de produtos e altera a marca do produto.
void alterarTamanhoProduto();//Abre o arquivo de produtos e altera o tamanho do produto.
void alterarCorProduto();//Abre o arquivo de produtos e altera a cor do produto.
void alterarTipoProduto();//Abre o arquivo de produtos e altera o tipo do produto.
void alterarCodigoProduto();//Abre o arquivo de produtos e altera o código do produto.

//MENU DE GERENCIAMENTO DE ENCOMENDAS. Segue o modelo do menu inicial.
void menuEncomendas();//Função que mostra o menu de gerenciamento de encomendas. Segue o modelo do menu inicial. Título: GERENCIAMENTO DE ENCOMENDAS
//Opção 1 cadastra uma nova encomenda e exibe o menu de gerenciamento de encomendas quando finalizado o cadastro
//Opção 2 lista todas as encomendas cadastradas no sistema (ordenadas por código)
//Opção 3 busca uma encomenda pelo Código de Encomenda e exibe seus dados. Se não encontrar, exibe a mensagem de erro.
//Opção 4 exclui uma encomenda pelo Código de Encomenda e exibe a mensagem de sucesso. Se não encontrar, exibe a mensagem de erro.
//Opção 5 exibe o menu de alteração de encomendas
//Opção 6 Voltar ao menu inicial
//Opção 7 encerrar o programa

//MENU DE ALTERAR DADOS DAS ENCOMENDAS. Segue o modelo do menu inicial.
void menuAlterarEncomenda();//Função que mostra o menu de alteração de encomendas. Segue o modelo do menu inicial.
void alterarStatusEncomenda();//Abre o arquivo de Encomendas.txt e altera o status da encomenda.
void alterarEndEntrega();//Abre o arquivo de Encomendas.txt e altera o endereço de entrega da encomenda.
void alterarDataEntrega();//Abre o arquivo de Encomendas.txt e altera a data de entrega da encomenda.
void alterarClienteEncomenda();//Abre o arquivo de Encomendas.txt e altera o cliente que fez a encomenda.
void alterarProdutoEncomenda();//Abre o arquivo de Encomendas.txt e altera o produto que foi encomendado.
void alterarCodigoEncomenda();//Abre o arquivo de Encomendas.txt e altera o código da encomenda.
void alterarQntdProdutoEncomenda();//Abre o arquivo de Encomendas.txt e altera a quantidade do produto encomendado.

Data receberData();//Função que recebe uma data do usuário.
Pessoa receberCliente();
Endereco receberEndereco();
Produto receberProduto();
Encomenda receberEncomenda();
Produto receberTamProduto();

void inserirClienteArq();//Função que abre o arquivo Clientes.txt para escrita, e escreve os dados do cliente recebidos na função receberCliente().
void inserirProdutoArq();//Função que abre o arquivo Produtos.txt para escrita, e escreve os dados do produto recebidos na função receberProduto().
void inserirEncomendaArq();//Função que abre o arquivo Encomendas.txt para escrita, e escreve os dados da encomenda recebidos na função receberEncomenda().

void inserirData();
void inserirCliente();//+1 para a quantidade de clientes cadastrados no sistema.
void inserirProduto();
void inserirEncomenda();

void seekCliente();//Função que abre o arquivo Clientes.txt para leitura, e busca um cliente pelo CPF.
void seekProduto();//Função que abre o arquivo Produtos.txt para leitura, e busca um produto pelo Código de Produto.

Pessoa *buscarCliente();
Produto *buscarProduto();
Encomenda *buscarEncomenda();

void alterarEnderecoEncomenda();//Função que altera o endereço de entrega de uma encomenda.

/* ===================================================================== */

void listarClientes();//Busca no arquivo Clientes.txt o cliente especificado pelo CPF, e mostra seus dados.
void listarEncomendas();//Busca no arquivo Encomendas.txt, a encomenda especificada pelo código, e mostra seus dados.
void listarProdutos();//Busca no arquivo Produtos.txt, o produto especificado pelo código, e mostra seus dados.

/* ===================================================================== */

int removerCliente();//Função que remove um cliente do arquivo Clientes.txt. Retorna 1 se o cliente foi removido com sucesso, e 0 caso contrário.
int removerProduto();//Função que remove um produto do arquivo Produtos.txt. Retorna 1 se o produto foi removido com sucesso, e 0 caso contrário.
int removerEncomenda();//Função que remove uma encomenda do arquivo Encomendas.txt. Retorna 1 se a encomenda foi removida com sucesso, e 0 caso contrário.
/* =======================================================================================================================================================*/

void menu()
//Opção 1 exibe o menu de gerenciamento de clientes na cor ciano e título em verde.
//Opção 2 exibe o menu de gerenciamento de produtos na cor amarela e título em verde.
//Opção 3 exibe o menu de gerenciamento de encomendas na cor magenta e título em verde.
//Opção 4 finaliza o programa exibindo a mensagem de despedida na cor vermelha e fundo preto.
//Opção 5 chama a função about e exibe os dados do programa, na cor branco e fundo preto.
{
    //system("clear");
    //fflush(stdin);

    do
    {
        printf(GREEN"\t\t ╔════════════ MENU PRINCIPAL ════════════╗\n"RESET);
        printf(GREEN"\t\t ║"RESET BHCYN"\t 1 ==> CLIENTES"RESET GREEN"\t\t\t  ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHYLW"\t 2 ==> PRODUTOS"RESET GREEN"\t\t\t  ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHMAG"\t 3 ==> ENCOMENDAS"RESET GREEN"\t\t  ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHRED"\t 4 ==> SAIR"RESET GREEN"\t\t\t  ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHBLU"\t 5 ==> SOBRE"RESET GREEN"\t\t\t  ║\n"RESET);
        printf(GREEN"\t\t ╚════════════════════════════════════════╝\n"RESET);
        printf(BHWHI"\n\t\tDigite a opção desejada: "RESET);
        fflush(stdin);
        scanf("%d", &input);
        system("clear");
        switch(input)
        {
            case 1:
                menuClientes();
                break;
            case 2:
                menuProdutos();
                break;
            case 3:
                menuEncomendas();
                break;
            case 4:
                //encerrar();
                exit(EXIT_SUCCESS);
            case 5:
                about();
                break;
            default:
                fflush(stdin);
                printf(RED"\n\t\t\tOPÇÃO INVÁLIDA!\n\n"RESET);
                getchar();
                fflush(stdin);
        }
    } while(input != 0);
    system("clear");
    
}

void menuClientes()
{
    do
    {
        printf(GREEN"\t\t ╔═════════════ MENU CLIENTES ═════════════╗\n"RESET);
        printf(GREEN"\t\t ║"RESET BHCYN"\t 1 ==> CADASTRAR CLIENTE "RESET GREEN"\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHCYN"\t 2 ==> LISTAR CLIENTES "RESET GREEN"\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHCYN"\t 3 ==> BUSCAR "RESET GREEN"\t\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHCYN"\t 4 ==> ALTERAR "RESET GREEN"\t\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHCYN"\t 5 ==> EXCLUIR "RESET GREEN"\t\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHCYN"\t 6 ==> VOLTAR "RESET GREEN"\t\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHRED"\t 7 ==> SAIR "RESET GREEN"\t\t\t   ║\n"RESET);
        printf(GREEN"\t\t ╚═════════════════════════════════════════╝\n"RESET);
        printf(BHWHI"\n\t\tDigite a opção desejada: "RESET);
        fflush(stdin);
        scanf("%d", &input);
        getchar();
        system("clear");
        switch(input)
        {
            case 1:
                fflush(stdin);
                inserirCliente(receberCliente());
                break;
            case 2:
                fflush(stdin);
                //listarClientes();
                mensagem();
                getchar();
                break;
            case 3:
                fflush(stdin);
                //seekCliente();
                mensagem();
                getchar();
                break;
            case 4:
                fflush(stdin);
                menuAlterarCliente();
                getchar();
                break;
            case 5:
                fflush(stdin);
                removerCliente();
                break;
            case 6:
                fflush(stdin);
                menu();
                break;
            case 7:
                exit(EXIT_SUCCESS);
            default:
                printf ("\n\t\t\tOPÇÃO INVÁLIDA!\n\n");
                fflush(stdin);
        }
    } 
    while(input != 0);
    system("clear");
}

void menuProdutos()
{
    int input;
    do
    {
        system("clear");
        printf(GREEN"\t\t ╔═════════════ MENU PRODUTOS ═════════════╗\n"RESET);
        printf(GREEN"\t\t ║"RESET BHYLW"\t 1 ==> CADASTRAR PRODUTO "RESET GREEN"\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHYLW"\t 2 ==> LISTAR PRODUTOS "RESET GREEN"\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHYLW"\t 3 ==> BUSCAR PRODUTO"RESET GREEN"\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHYLW"\t 4 ==> ALTERAR PRODUTO"RESET GREEN"\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHYLW"\t 5 ==> EXCLUIR PRODUTO"RESET GREEN"\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHBLU"\t 6 ==> VOLTAR "RESET GREEN"\t\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHRED"\t 7 ==> SAIR "RESET GREEN"\t\t\t   ║\n"RESET);
        printf(GREEN"\t\t ╚═════════════════════════════════════════╝\n"RESET);
        printf(BHWHI"\n\t\tDigite a opção desejada: "RESET);
        fflush(stdin);
        scanf("%d", &input);
        getchar();
        system("clear");
        switch(input)
        {
            case 1:
                fflush(stdin);
                inserirProduto(receberProduto());
                break;
            case 2:
                fflush(stdin);
                listarProdutos();
                getchar();
                break;
            case 3:
                fflush(stdin);
                //mensagem();
                seekProduto();
                getchar();
                break;
            case 4:
                fflush(stdin);
                menuAlterarProduto();
                break;
            case 5:
                fflush(stdin);
                removerProduto();
                break;
            case 6:
                menu();
                break;
            case 7:
                exit(EXIT_SUCCESS);
            default:
                printf(RED"\n\t\t\tOPÇÃO INVÁLIDA!\n\n"RESET);
                fflush(stdin);
        }
    }
    while(input != 7);
    system("clear");
}

void menuEncomendas()
{
    int input;
    do
    {
        printf(GREEN"\t\t ╔═════════════ MENU ENCOMENDAS ═════════════╗\n"RESET);
        printf(GREEN"\t\t ║"RESET BHMAG"\t 1 ==> CADASTRAR ENCOMENDA "RESET GREEN"\t     ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHMAG"\t 2 ==> LISTAR ENCOMENDAS "RESET GREEN"\t     ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHMAG"\t 3 ==> BUSCAR ENCOMENDA "RESET GREEN"\t     ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHMAG"\t 4 ==> ALTERAR ENCOMENDA "RESET GREEN"\t     ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHMAG"\t 5 ==> EXCLUIR ENCOMENDA "RESET GREEN"\t     ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHBLU"\t 6 ==> VOLTAR "RESET GREEN"\t\t\t     ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHRED"\t 7 ==> SAIR "RESET GREEN"\t\t\t     ║\n"RESET);
        printf(GREEN"\t\t ╚═══════════════════════════════════════════╝\n"RESET);
        printf(BHWHI"\n\t\tDigite a opção desejada: "RESET);
        fflush(stdin);
        scanf("%d", &input);
        getchar();
        system("clear");
        switch(input)
        {
            case 1:
                fflush(stdin);
                inserirEncomenda(receberEncomenda());
                break;
            case 2:
                fflush(stdin);
                listarEncomendas();
                //mensagem();
                getchar();
                break;
            case 3:
                fflush(stdin);
                mensagem();
                break;  
            case 4:
                fflush(stdin);
                mensagem();
                break;
            case 5:
                fflush(stdin);
                removerEncomenda();
                break;
            case 6:
                menu();
                break;
            case 7:
                exit(EXIT_SUCCESS);
            default:
                printf ("\n\t\t\tOPÇÃO INVÁLIDA!\n\n");
                fflush(stdin);
        }
    } 
    while(input != 7);
    system("clear");
}

void menuAlterarCliente()
{
    int input;
    do
    {
        printf(GREEN"\t\t ╔═════════════ MENU ALTERAR CLIENTE ═════════════╗\n"RESET);
        printf(GREEN"\t\t ║"RESET BHYLW"\t 1 ==> ALTERAR NOME "RESET GREEN"\t\t     ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHYLW"\t 2 ==> ALTERAR CPF "RESET GREEN"\t\t     ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHYLW"\t 3 ==> ALTERAR ENDEREÇO "RESET GREEN"\t     ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHYLW"\t 4 ==> ALTERAR TELEFONE "RESET GREEN"\t     ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHYLW"\t 5 ==> VOLTAR "RESET GREEN"\t\t\t     ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHRED"\t 6 ==> SAIR "RESET GREEN"\t\t\t     ║\n"RESET);
        printf(GREEN"\t\t ╚═══════════════════════════════════════════╝\n"RESET);
        printf(BHWHI"\n\t\tDigite a opção desejada: "RESET);
        fflush(stdin);
        scanf("%d", &input);
        getchar();
        system("clear");
        switch(input)
        {
            case 1:
                fflush(stdin);
                alterarNomeCliente();
                getchar();
                break;
            case 2:
                fflush(stdin);
                //alterarCpfCliente();
                mensagem();
                getchar();
                break;
            case 3:
                fflush(stdin);
                //alterarEnderecoCliente();
                mensagem();
                getchar();
                break;
            case 4:
                fflush(stdin);
                //alterarTelefoneCliente();
                mensagem();
                getchar();
                break;
            case 5:
                menu();
                break;
            case 6:
                exit(EXIT_SUCCESS);
            default:
                printf(RED"\n\t\t\tOPÇÃO INVÁLIDA!\n\n"RESET);
                fflush(stdin);
        }
    }while(input != 0);
    system("clear");
}

void menuAlterarProduto()//Exibe o menu de alteração de produtos
{
    int input;
    do
    {
        printf(BHBLU"\n\t\t\tALTERAR PRODUTO\n\n"RESET);
        printf(GREEN"\t\t ╔═════════════════════════════════════════╗\n"RESET);
        printf(GREEN"\t\t ║"RESET BHMAG"\t 1 ==> ALTERAR CÓDIGO"RESET GREEN"\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHMAG"\t 2 ==> ALTERAR NOME"RESET GREEN"\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHMAG"\t 3 ==> ALTERAR DESCRIÇÃO"RESET GREEN"\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHMAG"\t 4 ==> ALTERAR CATEGORIA"RESET GREEN"\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHMAG"\t 5 ==> ALTERAR COR"RESET GREEN"\t\t   ║\n"RESET);
        //printf(GREEN"\t\t ║"RESET BHMAG"\t 6 ==> ALTERAR PREÇO"RESET GREEN"\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHBLU"\t 6 ==> VOLTAR "RESET GREEN"\t\t\t   ║\n"RESET);
        printf(GREEN"\t\t ║"RESET BHRED"\t 7 ==> SAIR "RESET GREEN"\t\t\t   ║\n"RESET);
        printf(GREEN"\t\t ╚═════════════════════════════════════════╝\n"RESET);
        printf(BHWHI"\n\t\tDigite a opção desejada: "RESET);
        fflush(stdin);
        scanf("%d", &input);
        getchar();
        system("clear");
        switch(input)
        {
            case 1:
                fflush(stdin);
                break;
            case 2:
                fflush(stdin);
                alterarNomeProduto();
                //getchar();
                break;
            case 3:
                mensagem();
                break;
            case 4:
                mensagem();
                break;
            case 5:
                mensagem();
                break;
            case 6:
                menuProdutos();
                break;
            case 7:
                exit(EXIT_SUCCESS);
            default:
                printf(RED"\n\t\t\tOPÇÃO INVÁLIDA!\n\n"RESET);
                fflush(stdin);
        }
    }
    while(input != 7);
    system("clear");
}

/* ===================================================================== */

Pessoa receberCliente()
{
    Pessoa p;

    printf(BHWHI"\n\t\tDigite o NOME do cliente: "RESET);
    receberString(p.nome, 40);
    printf(BHWHI"\n\t\tDigite o CPF do cliente: "RESET);
    receberString(p.cpf, 11);
    printf(BHWHI"\n\t\tDigite o RG do cliente: "RESET);
    receberString(p.rg, 10);
    printf(BHWHI"\n\t\tDigite o TELEFONE do cliente: "RESET);
    receberString(p.telefone, 11);

    p.end = receberEndereco();
    sucesso();
    return p;
}

Endereco receberEndereco()//Recebe os dados de endereço
{
    Endereco e;
    FILE *arq;
    arq = fopen("Enderecos.txt", "a");

    printf(BHWHI"\n\t\tRUA: "RESET);
    receberString(e.rua, 40);
    printf(BHWHI"\n\t\tNÚMERO: "RESET);
    receberString(e.numero, 10);
    printf(BHWHI"\n\t\tBAIRRO: "RESET);
    receberString(e.bairro, 40);
    printf(BHWHI"\n\t\tCEP: "RESET);
    receberString(e.cep, 10);
    printf(BHWHI"\n\t\tCIDADE: "RESET);
    receberString(e.cidade, 40);
    printf(BHWHI"\n\t\tESTADO: "RESET);
    receberString(e.estado, 40);
    printf(BHWHI"\n\t\tPAÍS: "RESET);
    receberString(e.pais, 40);
    fprintf(arq, "%s %s %s %s %s %s %s\n", e.rua, e.numero, e.bairro, e.cep, e.cidade, e.estado, e.pais);
    fclose(arq);
    return e;
}

Produto receberProduto()
{
    Produto p;
    //FILE * arq;
    //arq = fopen("Produtos.txt", "a");

    printf(BHWHI"\n\t\tDigite o CÓDIGO do produto: "RESET);
    receberString(p.codProduto, 10);//getchar();
    printf(BHWHI"\n\t\tDigite o NOME do produto: "RESET);
    receberString(p.nome, 50);//getchar();
    printf(BHWHI"\n\t\tDigite a DESCRICAO do produto: "RESET);
    receberString(p.descricao, 50);//getchar();
    printf(BHWHI"\n\t\tDigite a CATEGORIA do produto: "RESET);
    receberString(p.categoria, 50);//getchar();
    printf(BHWHI"\n\t\tDigite a COR do produto: "RESET);
    receberString(p.cor, 50);//getchar();
    printf(BHWHI"\n\t\tDigite o PREÇO do produto: "RESET);
    fscanf(stdin, "%f", &p.preco);
    fflush(stdin);
    getchar();
    
    //prod.tam = receberTamProduto();
    
    return p;
}

Encomenda receberEncomenda()
{
    Encomenda e;
    
    printf(BHWHI"\n\t\tDigite o CÓDIGO da encomenda: "RESET);
    receberString(e.codEncomenda, 10);//getchar();
    printf(BHWHI"\n\t\tDigite o STATUS do pedido: "RESET);//0 ==> Pendente, 1 ==> Em andamento, 2 ==> Entregue
    receberString(e.status, 2);//getchar();
    printf(BHWHI"\n\t\tDigite o NOME do cliente: "RESET);
    receberString(e.pessoa, 20);getchar();
    printf(BHWHI"\n\t\tDigite o NOME do produto: "RESET);
    receberString(e.produto, 20);getchar();
    printf(BHWHI"\n\t\tDigite a QUANTIDADE do produto: "RESET);
    receberString(e.quantidade, 5);getchar();

    //e.data_encomenda = receberData();
    //e.data_entrega = receberData();
    e.endEntrega = receberEndereco();
    sucesso();
    return e;
}

Data receberData()
{
    Data d;
    FILE *arq;
    arq = fopen("Data.txt", "a");

    printf(BHWHI"\n\t\tDIA: "RESET);
    receberString(d.dia, 2);
    printf(BHWHI"\n\t\tMÊS: "RESET);
    receberString(d.mes, 2);
    printf(BHWHI"\n\t\tANO: "RESET);
    receberString(d.ano, 4);

    fprintf(arq, "%s/%s/%s\n", d.dia, d.mes, d.ano);
    fclose(arq);
    return d;
}

/* ===================================================================== */

void inserirCliente(Pessoa p)//Abre o arquivo Clientes.txt para escrita, e adiciona ao final do arquivo
{
    FILE *arq;
    arq = fopen("Clientes.txt", "a");
    if(arq == NULL)
    {
        printf("\nErro ao abrir o arquivo Clientes.txt");
        exit(EXIT_FAILURE);
    }
    fprintf(arq, "%s\n", p.nome);
    fprintf(arq, "%s\n", p.cpf);
    fprintf(arq, "%s\n", p.rg);
    fprintf(arq, "%s\n", p.telefone);
    fprintf(arq, "%s\n", p.end.rua);
    fprintf(arq, "%s\n", p.end.numero);
    fprintf(arq, "%s\n", p.end.cep);
    fprintf(arq, "%s\n", p.end.bairro);
    fprintf(arq, "%s\n", p.end.cidade);
    fprintf(arq, "%s\n", p.end.estado);
    fprintf(arq, "%s\n", p.end.pais);
    fclose(arq);
}

void inserirProduto(Produto p)//Abre o arquivo Produtos.txt no modo de escrita, e escreve os dados do produto no fim do arquivo.
{
    FILE * arq;
    arq = fopen("Produtos.txt", "a");
    if(arq == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    //fprintf(arq, "CÓDIGO | NOME | DESCRIÇÃO | CATEGORIA | COR | PREÇO \n");
    fprintf(arq, "\n%s %s %s %s %s %2.2f\n", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, p.preco);

    fclose(arq);
}

void inserirEncomenda(Encomenda e)//Abre o arquivo Encomendas.txt no modo de escrita, e escreve os dados do pedido no fim do arquivo.
{
    FILE * arq;
    arq = fopen("Encomendas.txt", "a");
    if(arq == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    fprintf(arq, "%s\n", e.codEncomenda);
    fprintf(arq, "%s\n", e.status);
    fprintf(arq, "%s\n", e.pessoa);
    fprintf(arq, "%s\n", e.produto);
    fprintf(arq, "%s\n", e.quantidade);
    fclose(arq);
}

/* ===================================================================== */

//FUNÇÕES DE BASE
/*Pessoa *buscarCliente()//Abre o arquivo Clientes.txt em modo de leitura, busca o cliente pelo CPF, e exibe os dados na tela.
{
    FILE * arq;
    Pessoa *p;
    char cpf[12];
    int i = 0;
    arq = fopen("Clientes.txt", "r");
    printf("Digite o CPF do cliente a ser buscado:");
    fgets(cpf, 12, stdin);
    if(arq == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    while(fread(&p, sizeof(Pessoa), 1, arq) == 1)
    {
        if(strcmp(p->cpf, cpf) == 0)
        {
            printf("\n\t\t\tDADOS DO CLIENTE\n\n");
            printf("\t\t\tNome: %s\n", p->nome);
            printf("\t\t\tCPF: %s\n", p->cpf);
            printf("\t\t\tTelefone: %s\n", p->telefone);
            //printf("\t\t\tData de Nascimento: %s\n", p->data_nasc);
            printf("\t\t\tEndereço: %s\n", p->end);
            printf("\t\t\t\n\n");
            i++;
        }
    }
    if(i == 0)
    {
        printf(BHRED"\n\t\t\tCLIENTE NÃO ENCONTRADO!\n\n"RESET);
    }
    fclose(arq);
    return p;
}*/

void seekCliente()
//Recebe o CPF a ser buscado no arquivo de Clientes, e retorna os dados do cliente, caso o CPF não exista, exibe uma mensagem de erro.
{
    FILE * arq;
    Pessoa *p;
    char cpf[12];
    int i = 0;
    arq = fopen("Clientes.txt", "r");
    printf("Digite o CPF do cliente a ser buscado:");
    fgets(cpf, 12, stdin);
    if(arq == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    while(fread(&p, sizeof(Pessoa), 1, arq) == 1)
    {
        if(strcmp(p->cpf, cpf) == 0)
        {
            printf("\n\t\t\tDADOS DO CLIENTE\n\n");
            printf("\t\t\tNome: %s\n", p->nome);
            printf("\t\t\tCPF: %s\n", p->cpf);
            printf("\t\t\tRG: %s\n", p->rg);
            printf("\t\t\tTelefone: %s\n", p->telefone);
            //printf("\t\t\tData de Nascimento: %s\n", p->data_nasc);
            printf("\t\t\tEndereço: %s ,%s ,%s ,%s ,%s ,%s - %s\n", p->end.rua, p->end.numero, p->end.bairro, p->end.cep, p->end.cidade, p->end.estado, p->end.pais);
            printf("\t\t\t\n\n");
            i++;
        }
    }
    if(i == 0)
    {
        printf(BHRED"\n\t\t\tCLIENTE NÃO ENCONTRADO!\n\n"RESET);
    }
    fclose(arq);
}

void seekProduto()
/* Recebe o código de um produto, abre o arquivo Produtos.txt no modo de leitura, busca o produto que possui
o código informado, caso exista, imprime na tela as informações daquele produto, caso não exista,
o programa emite uma mensagem, e retorna ao menu de produtos. */
{
    FILE *arq;
    Produto p;
    char codProduto[10];
    int achou = 0;
    arq = fopen("Produtos.txt", "r");
    if(arq == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    printf(BHWHI"\n\t\tDigite o CÓDIGO do produto: "RESET);
    receberString(codProduto, 10);//getchar();
    fscanf(arq, "%s %s %s %s %s %f", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, &p.preco);
    while(!feof(arq))
    {
        if(strcmp(codProduto, p.codProduto) == 0)
        {
            printf("\n\t\tCÓDIGO: %s\n\t\tNOME: %s\n\t\tDESCRIÇÃO: %s\n\t\tCATEGORIA: %s\n\t\tCOR: %s\n\t\tPREÇO: %2.2f\n", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, p.preco);
            achou = 1;
        }
        fscanf(arq, "%s %s %s %s %s %f", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, &p.preco);
    }
    if(achou == 0)
    {
        printf(BHRED"\n\t\t\tPRODUTO NÃO ENCONTRADO!\n\n"RESET);
    }
    fclose(arq);
}

/* ===================================================================== */

void listarProdutos()//Lista todos os produtos do arquivo Produtos.txt
{
    FILE * arq;
    Produto p;
    arq = fopen("Produtos.txt", "r");
    if(arq == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    fscanf(arq, "%s %s %s %s %s %f", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, &p.preco);
    while(!feof(arq))
    {
        printf("\n\t\tCÓDIGO: %s\n\t\tNOME: %s\n\t\tDESCRIÇÃO: %s\n\t\tCATEGORIA: %s\n\t\tCOR: %s\n\t\tPREÇO: %2.2f\n", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, p.preco);
        fscanf(arq, "%s %s %s %s %s %f", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, &p.preco);
    }
    fclose(arq);
}

/*void listarClientes()//Lista todos os clientes do arquivo Clientes.txt
{
    FILE * arq;
    Pessoa *p;
    arq = fopen("Clientes.txt", "r");
    if(arq == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    fscanf(arq, "%s %s %s %s %s %s %s %s %s %s", p->cpf, p->nome, p->telefone, p->end.rua, p->end.numero, p->end.bairro, p->end.cidade, p->end.estado, p->end.cep, p->end.pais);
    while(!feof(arq))
    {
        printf("\n\t\tCPF: %s\n\t\tNOME: %s\n\t\tTELEFONE: %s\n\t\tENDEREÇO: %s %s %s %s %s %s %s\n", p->cpf, p->nome, p->telefone, p->end.rua,p->end.numero, p->end.bairro, p->end.cidade, p->end.estado, p->end.cep, p->end.pais);
        fscanf(arq, "%s %s %s %s %s %s %s %s %s %s", p->cpf, p->nome, p->telefone, p->end.rua, p->end.numero, p->end.bairro, p->end.cidade, p->end.estado, p->end.cep, p->end.pais);
    }
    fclose(arq);
}*/

void listarEncomendas()//Lista todas as encomendas do arquivo Encomendas.txt
{
    FILE *arq;
    Encomenda e;
    arq = fopen("Encomendas.txt", "r");
    if(arq == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    fscanf(arq, "%s", e.codEncomenda);
    fscanf(arq, "%s", e.status);
    fscanf(arq, "%s", e.pessoa);
    fscanf(arq, "%s", e.produto);
    fscanf(arq, "%s", e.quantidade);
    /*fscanf(arq, "%s", e->endEntrega.rua);
    fscanf(arq, "%s", e->endEntrega.numero);
    fscanf(arq, "%s", e->endEntrega.bairro);
    fscanf(arq, "%s", e->endEntrega.cidade);
    fscanf(arq, "%s", e->endEntrega.estado);
    fscanf(arq, "%s", e->endEntrega.cep);
    fscanf(arq, "%s", e->endEntrega.pais);*/
    while(!feof(arq))
    {
        printf("\tCÓDIGO DA ENCOMENDA: %s\n", e.codEncomenda);
        printf("\tSTATUS: %s\n", e.status);
        printf("\tCLIENTE: %s\n", e.pessoa);
        printf("\tNOME DO PRODUTO: %s\n", e.produto);
        printf("\tQUANTIDADE: %s\n", e.quantidade);
        printf(BHGRN"========================================\n"RESET);

        fscanf(arq, "%s", e.codEncomenda);
        fscanf(arq, "%s", e.status);
        fscanf(arq, "%s", e.pessoa);
        fscanf(arq, "%s", e.produto);
        fscanf(arq, "%s", e.quantidade);

        if(e.status == 0)
        {
            printf("\n\t\tSTATUS: %s", "PENDENTE");
        }
        else if(e.status == 1)
        {
            printf("\n\t\tSTATUS: %s", "EM ANDAMENTO");
        }
        else if(e.status == 2)
        {
            printf("\n\t\tSTATUS: %s", "ENTREGUE");
        }
        else if(e.status == 3)
        {
            printf("\n\t\tSTATUS: %s", "CANCELADA");
        }
    }
    fclose(arq);
}


/* ==================================================================================== */
void alterarNomeCliente()
/* Recebe o CPFd do cliente que terá seu nome alterado, copia o arquivo Clientes.txt para ClientesMod.txt.
abre o arquivo ClientesMod.txt para escrita, e altera somente o nome do cliente. Apaga o arquivo Clientes.txt. 
e renomeia ClientesMod.txt para Clientes.txt. */ 
{
    FILE *arq, *arq2;
    Pessoa c;
    char cpf[15];
    char novoNome[50];
    arq = fopen("Clientes.txt", "r");
    if(arq == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    arq2 = fopen("ClientesMod.txt", "w");
    if(arq2 == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    printf(BHWHI"\n\t\tDigite o CPF do cliente: "RESET);
    receberString(cpf, 15);//getchar();
    fscanf(arq, "%s", c.cpf);
    fscanf(arq, "%s", c.rg);
    fscanf(arq, "%s", c.nome);
    fscanf(arq, "%s", c.telefone);
    /*fscanf(arq, "%s", c->end.rua);
    fscanf(arq, "%s", c->end.numero);
    fscanf(arq, "%s", c->end.bairro);
    fscanf(arq, "%s", c->end.cidade);
    fscanf(arq, "%s", c->end.estado);
    fscanf(arq, "%s", c->end.cep);*/
    while(!feof(arq))
    {
        if(strcmp(cpf, c.cpf) == 0)
        {
            printf(BHWHI"\n\t\tDigite o novo nome do cliente: "RESET);
            receberString(novoNome, 50);//getchar();
            fprintf(arq2, "%s %s %s %s\n", c.cpf, c.rg, novoNome, c.telefone /*,c->end.rua, c->end.numero, c->end.bairro, c->end.cidade, c->end.estado, c->end.cep*/);
        }
        else
        {
            fprintf(arq2, "%s %s %s %s\n", c.cpf, c.rg, c.nome, c.telefone /*,c->end.rua, c->end.numero, c->end.bairro, c->end.cidade, c->end.estado, c->end.cep*/);
        }
        fscanf(arq, "%s", c.cpf);
        fscanf(arq, "%s", c.rg);
        fscanf(arq, "%s", c.nome);
        fscanf(arq, "%s", c.telefone);
        /*fscanf(arq, "%s", c->end.rua);
        fscanf(arq, "%s", c->end.numero);
        fscanf(arq, "%s", c->end.bairro);
        fscanf(arq, "%s", c->end.cidade);
        fscanf(arq, "%s", c->end.estado);
        fscanf(arq, "%s", c->end.cep);*/
    }
    fclose(arq);
    fclose(arq2);
    remove("Clientes.txt");
    rename("ClientesMod.txt", "Clientes.txt");
}

void alterarNomeProduto()
/*Recebe o código do produto que será alterado, copia o arquivo Produtos.txt para ProdutosMod.txt,
abre o arquivo PodutosMod.txt para escrita, e altera o nome do produto. Apaga o arquivo
Produtos.txt, e renomeia ProdutosMod.txt para Produtos.txt.*/
{
    FILE *arq, *arq2;
    Produto p;
    char codigo[10];
    char novoNome[50];
    arq = fopen("Produtos.txt", "r");
    if(arq == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    arq2 = fopen("ProdutosMod.txt", "w");
    if(arq2 == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    printf(BHWHI"\n\t\tDigite o CÓDIGO do produto: "RESET);
    receberString(codigo, 10);
    fscanf(arq, "%s %s %s %s %s %f", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, &p.preco);
    while(!feof(arq))
    {
        if(strcmp(p.codProduto, codigo) == 0)
        {
            printf(BHWHI"\n\t\tDigite o novo NOME do produto: "RESET);
            receberString(novoNome, 50);
            fprintf(arq2, "%s %s %s %s %s %f\n", p.codProduto, novoNome, p.descricao, p.categoria, p.cor, p.preco);
        }
        else
        {
            fprintf(arq2, "%s %s %s %s %s %f\n", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, p.preco);
        }
        fscanf(arq, "%s %s %s %s %s %f", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, &p.preco);
    }
    fclose(arq);
    fclose(arq2);
    remove("Produtos.txt");
    rename("ProdutosMod.txt", "Produtos.txt");
}

/* ==================================================================================== */

int removerCliente()
{
    FILE *arq, *arq2;
    char cpfBusca[15];
    int i = 0;
    arq = fopen("Clientes.txt", "r");
    arq2 = fopen("Clientes2.txt", "w");
    if(arq == NULL || arq2 == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    printf(BHWHI"\n\t\tDigite o CPF do cliente que deseja remover: "RESET);
    receberString(cpfBusca, 15);
    while(fgets(cpfBusca, 15, arq) != NULL)
    {
        if(strcmp(cpfBusca, cpfBusca) != 0)
        {
            fprintf(arq2, "%s", cpfBusca);
        }
        i++;
    }
    fclose(arq);
    fclose(arq2);
    remove("Clientes.txt");
    rename("Clientes2.txt", "Clientes.txt");
    return i;    
}

int removerEncomenda()
/*Copia o arquivo original para o arquivo de modificação. Recebe o código da encomenda que será
removida, apaga a linha em que a encomenda está, apaga o arquivo antigo, e renomeia o de 
modificação para Encomendas.txt */ 
{
    FILE * arq, * arq2;
    char cod[10];
    int i = 0;
    arq = fopen("Encomendas.txt", "r");
    arq2 = fopen("Encomendas2.txt", "w");
    if(arq == NULL || arq2 == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    printf(BHWHI"\n\t\tDigite o CÓDIGO da encomenda a ser removida: "RESET);
    receberString(cod, 10);
    while(fgets(cod, 10, arq) != NULL)
    {
        if(strcmp(cod, cod) != 0)
        {
            fprintf(arq2, "%s", cod);
        }
        else
        {
            i++;
        }
    }
    fclose(arq);
    fclose(arq2);
    remove("Encomendas.txt");
    rename("Encomendas2.txt", "Encomendas.txt");
    return i;
}

int removerProduto()
/*Copia o arquivo original para o arquivo de modificação. Recebe o código do produto que será
removido, apaga a linha em que o produto está, apaga o arquivo antigo, e renomeia o de 
modificação para Produtos.txt */
{
    FILE *arq, *arq2;
    Produto p;
    char codigo[10];
    int linha = 0;
    arq = fopen("Produtos.txt", "r");
    if(arq == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    arq2 = fopen("ProdutosMod.txt", "w");
    if(arq2 == NULL)
    {
        printf(BHRED"\n\t\t\tERRO AO ABRIR O ARQUIVO!\n\n"RESET);
        exit(EXIT_FAILURE);
    }
    printf(BHWHI"\n\t\tDigite o CÓDIGO do produto: "RESET);
    receberString(codigo, 10);
    fscanf(arq, "%s %s %s %s %s %f", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, &p.preco);
    while(!feof(arq))
    {
        if(strcmp(p.codProduto, codigo) == 0)
        {
            linha = 1;
        }
        else
        {
            fprintf(arq2, "%s %s %s %s %s %f\n", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, p.preco);
        }
        fscanf(arq, "%s %s %s %s %s %f", p.codProduto, p.nome, p.descricao, p.categoria, p.cor, &p.preco);
    }
    fclose(arq);
    fclose(arq2);
    remove("Produtos.txt");
    rename("ProdutosMod.txt", "Produtos.txt");
    return linha;
}

/* ==================================================================================== */

void encerrar()
{
    exit(EXIT_SUCCESS);
}

/* ==================================================================================== */
void about()
{   
    system("clear");
    tituloProg();
    subTitulo();
    autores();
    descricao();

    getchar();
    printf("APERTE <ENTER>");
    getchar();
    system("clear");
}

void tituloProg()
{
    printf(BHWHI"\tSistema De Encomendas"RESET);
}

void subTitulo()
//Mostra a versão do programa
{
    printf(BHWHI" - V10.0.5\n"RESET);
}

void autores()
{
    char autores[]={"\tLuís A. G. Dos Santos - 256647\n"
                    "\tThiago A. P. Correa 254366\n"
                    "\tCarolina Noda Morishita - 254187\n"
                    "\tNome - RA\n"
    };
    printf(BHWHI"\nDesenvolvido por: \n%s", autores, RESET);
}

void descricao()
{
    char desc[]={
        "Sistema de Encomendas "
        "para a disciplina de "
        "Algoritmos e Programação " 
        "de Computadores II\n"
        "Faculdade de Tecnologia "
        "da Universidade Estadual "
        "De Campinas - FT UNICAMP\n"};
    printf(BHWHI"\n%s\n", desc, RESET);
}

/* ==================================================================================== */
void mensagem()
//imprime uma mensagem na tela, na cor amarelo, que a funcionalidade ainda está em desenvolvimento
{
    printf(BHYLW"\t\t Esta funcionalidade ainda está em desenvolvimento!\n"RESET);
    printf(BHWHI"\n\t\tAPERTE <ENTER> PARA VOLTAR AO MENU ANTERIOR\n"RESET);
    getchar();
    system("clear");
}

/* ==================================================================================== */

void sucesso()
{
    system("clear");
    printf (GREEN"Operacao realizada com sucesso!\n"RESET);
    getchar();
    system("clear");
}

void erro(char *nome_arquivo)
{
    printf("Nao foi possivel abrir o arquivo %s\n", nome_arquivo);
}

void removerQuebraLinha(char *string)
{
    if(string != NULL && strlen(string) > 0)
    {
        short tamanho = strlen(string);
        if(string[tamanho-1] == '\n')
        {
            string[tamanho-1] = '\0';
        }
    }
}

void receberString(char *string_destino, int quantidade_caracteres)
{
    fgets(string_destino, quantidade_caracteres, stdin);
    //printf("PRESSIONE <ENTER>");
    //getchar();
    system("clear");
    removerQuebraLinha(string_destino);
}

/* início do programa */

int main(/*int argc, char** argv*/)
{
    setlocale(LC_ALL, "Portuguese");
    menu();
    return (EXIT_SUCCESS);
}