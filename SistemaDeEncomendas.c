#include<stdio.h>
#include<string.h>
#include<math.h>

int main()
{
	typedef struct caracteristicas
	{
		char Dproduto[50];
		char Descricao[100];
		int Quantidade;
		float Altura;
		float Largura;
		float Comprimento;
		float Volume;
		float Peso;
		float VolumeTotal;
		float PesoTotal;

	}Caracteristicas;

	typedef struct endereco
	{
		int CEP;
		char Pais[50];
		char Estado[50];
		char Cidade[50];
		char Bairro[50];
		char Rua[50];
		int Numero;
		char Complemento[50];

	}Endereco;

	typedef struct pedido
	{
		long CodPedido;
		Endereco EndDaentrega;
		Caracteristicas Produto;

	}Pedido;

	int Escolha;
	char Teste[1];
	Pedido Entrega;
	int Controle = 0; // Tire isso depois
	// StatusDoPedido; (Recebido, à caminho, entregue)

    printf("Sistema de Gestão de entregas\n");
    
	do{
		printf("Escolha :\n");
		printf("(1)Adicionar Entrega\n");
		printf("(2)Pesquisar Entrega\n");
		printf("(3)Alterar Entrega\n");
		printf("(4)Excluir Entrega\n");

		scanf("%d",&Escolha);

		if(Escolha == 1){

			printf("\nAdicionar Entrega\n");
			fgets(Entrega.Produto.Dproduto, 50, stdin);
			
			printf("Produto\n");
			fgets(Entrega.Produto.Dproduto, 50, stdin);
			printf("Descrição\n");
			fgets(Entrega.Produto.Descricao, 100, stdin);

			printf("Quantidade\n");
			scanf("%d", &Entrega.Produto.Quantidade);
			printf("Altura\n");
			scanf("%f", &Entrega.Produto.Altura);
			printf("Largura\n");
			scanf("%f", &Entrega.Produto.Largura);
			printf("Comprimento\n");
			scanf("%f", &Entrega.Produto.Comprimento);
			printf("Peso\n");
			scanf("%f", &Entrega.Produto.Peso);

			printf("CEP\n");
			scanf("%d", &Entrega.EndDaentrega.CEP);
			
			fgets(Entrega.EndDaentrega.Pais, 50, stdin);
			
			printf("País:\n");
			fgets(Entrega.EndDaentrega.Pais, 50, stdin);
			printf("Estado:\n");
			fgets(Entrega.EndDaentrega.Estado, 50, stdin);
			printf("Cidade:\n");
			fgets(Entrega.EndDaentrega.Cidade, 50, stdin);
			printf("Bairro:\n");
			fgets(Entrega.EndDaentrega.Bairro, 50, stdin);
			printf("Rua:\n");
			fgets(Entrega.EndDaentrega.Rua, 50, stdin);
		    printf("Numero:\n");
			scanf("%d", &Entrega.EndDaentrega.Numero);
			
			int Escolha2;
			
			printf("Tem Complemento? (1)Sim (2)Não\n");
			scanf("%d", &Escolha2);
			
			if(Escolha2 == 1){
			    printf("Complemento:\n");
			    fgets(Entrega.EndDaentrega.Complemento, 50, stdin);
			    fgets(Entrega.EndDaentrega.Complemento, 50, stdin);
			}
			else if(Escolha2 == 2){
			    continue;
			}
			
		}

		else if (Escolha == 2){

			printf("\nPesquisar Entrega\n");

		}

		else if (Escolha == 3){

			printf("\nAlterar Entrega\n");

		}

		else if (Escolha == 4){

			printf("\nExcluir Entrega\n");

		}

		else{
			printf("\nNão tem essa escolha\n");
		}

		printf("\nUsar Novamente: Sim(1) Não(2)\n");
		scanf("%d",&Controle);

	} while(Controle == 1);

	return 0;
}

//scanf("%d", &Di[i].resp);
//fgets(Di[i].nome, 101, stdin)