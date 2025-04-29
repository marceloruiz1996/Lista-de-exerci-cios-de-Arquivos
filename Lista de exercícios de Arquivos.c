
#include <stdio.h>
#include <stdlib.h>

typedef struct
  {
  int Cod_Cli;
  char Nome[50];
  char Endereco[400];
  char Fone[20];
  } Cliente;

#difine TAM 1000000; // tamanho 
clientes[TAM];
int quant=0;

int cadastrarCliente(Cliente *c)
  {
  if(quant<TAM)
    {
    printf("Cadastro de cliente\n");
    printf("código do Cliente: ");
    scanf("%d", & c->.Cod_Cli);
    getchar(); //limpa o \n (buffer)do scanf para nao bugar os fgets;
    printf("\nNome: ");
    fgets(c->Nome, 50, stdin);
    printf("\nEndereco: ");
    fgets(c->Endereco, 400, stdin);
    printf("\nFone: ");
    fgets(c->Fone, 20, stdin);
    quant++;
    return 0;
    }
  else
    {
    printf("erro, quantidade máxima de cadastro efetuada");
    }
  }

void listarClientes()
  {
  int i;
  for(i=0, i < quant, i++)
    {
    printf("cliente %d\n", i+1);
    printf("código: %d\n", clientes[i].Cod_Cli);
    printf("nome: %c\n", clientes[i].Nome);
    printf("endereço: %c\n", clientes[i].Endereco);
    printf("telefone: %c\n", clientes[i].Fone);    
    }
  }

void arquivoCliente()
  {
  FILE *arq = fopen("cliente.txt", "w");
  if(arq)
    {
    for(i=0, i, i++)
      {
      
      }
    }
  else
    {
    printf("ERRO");
    }
  }

typedef struct
  {
  int Num_doc;
  float Valor_doc;
  char Data_Emissao[15];
  char Data_Vencimento[15];
  int Cod_Cli;
  } Recebimento;

int cadastrarRecebimento(Recebimento *r)
  {
  printf("Cadastro de recebimento\n");
  printf("Número de Documento: ");
  scanf("%d", & r->Num_doc);
  printf("\nValor do Documento: ");
  scanf("%f", & r->Valor_doc);
  getchar();
  printf("\nData de Emissão: ");
  fgets(r->Data_Emissao, 15, stdin);
  printf("\nData de Vencimento: ");
  fgets(r->Data_Vencimento, 15, stdin);
  printf("\ncódigo do Cliente: ");
  scanf("%d", & r->Cod_Cli);
  getchar();
  
  return 0;
  }
int 
int main()
  {
  int op;
  
  do
    {
    printf("\n1 - cadastrar cliente \n2 - imprimir cliente\n0 - sair");
    scanf("%d", & op);
    
    switch(op)
      {
      case 0:
        prinft("encerrado");
        break;
      
      case 1:
        cadastrarCliente();
        break;

      case 2:
        listarClientes();
        break;
      
      default:
        printf("opção invalida");
      }while(op != 0);    
    }
  
 
  return 0;
  }
