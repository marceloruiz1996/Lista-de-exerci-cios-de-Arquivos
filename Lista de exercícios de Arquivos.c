
#include <stdio.h>
#include <stdlib.h>
int main()
{
//FILE *fclientes, *frecebimentos;
 
  Cliente cliente;
  Recebimento recebimento;
 
  printf("Cadastro de cliente\n");
  

 
  printf("\n");
 
  printf("Cadastro de recebimento\n");
  
  printf("Número de Documento: ")
  scanf("%d\n", & Recebimento.Num_doc);
  printf("Valor do Documento: ")
  scanf("%f\n", & Recebimento.Valor_doc);
  printf("Data de Emissão: ");
  scanf("%[^\n]", & Recebimento.Data_Emissao);
  printf("Data de Vencimento: ");
  scanf("%[^\n]", & Recebimento.Data_Vencimento);
  printf("código do Cliente: ");
  scanf("%d\n", & Recebimento.Cod_Cli);

    return 0;
}

typedef struct
  {
  int Cod_Cli;
  char Nome[50];
  char Endereco[400];
  char Fone[20];
  } Cliente;

int cadastrarPessoa()
  {
   printf("código do Cliente: ");
  scanf("%d\n", & Cliente.Cod_Cli);
  printf("Nome: ");
  fgets(Cliente.Nome, 50, stdin);
  printf("Endereco: ");
  fgets(Cliente.Endereco, 400, stdin):
  printf("Fone: ");
  fgets(Cliente.Fone, 20, stdin);
  }
 
typedef struct
  {
  int Num_doc;
  float Valor_doc;
  char Data_Emissao[15];
  char Data_Vencimento[15];
  int Cod_Cli;
  } Recebimento;
 
