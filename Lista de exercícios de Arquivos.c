#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 1000

typedef struct {
    int Cod_Cli;
    char Nome[50];
    char Endereco[100];
    char Fone[20];
} Cliente;

typedef struct {
    int Num_doc;
    float Valor_doc;
    char Data_Emissao[15];
    char Data_Vencimento[15];
    int Cod_Cli;
} Recebimento;

typedef struct {
    int codEstilista;
    char nome[50];
    float salario;
} Estilista;

typedef struct {
    int codEstacao;
    char nome[50];
} Estacao;

typedef struct {
    int codRoupa;
    char descricao[100];
    int codEstilista;
    int codEstacao;
    int ano;
} Roupa;

typedef struct {
    int numero;
    char nome[50];
    float nota1;
    float nota2;
} Aluno;

typedef struct {
    int codigo;
    char descricao[100];
    float preco;
} Produto;

int dataAnterior(const char *data1, const char *data2) {
    int d1, m1, a1, d2, m2, a2;
    sscanf(data1, "%d/%d/%d", &d1, &m1, &a1);
    sscanf(data2, "%d/%d/%d", &d2, &m2, &a2);
    if (a1 < a2) return 1;
    if (a1 == a2 && m1 < m2) return 1;
    if (a1 == a2 && m1 == m2 && d1 < d2) return 1;
    return 0;
}

int clienteExiste(int cod) {
    Cliente c;
    FILE *arq = fopen("clientes.dat", "rb");
    if (!arq) return 0;
    while (fread(&c, sizeof(Cliente), 1, arq)) {
        if (c.Cod_Cli == cod) {
            fclose(arq);
            return 1;
        }
    }
    fclose(arq);
    return 0;
}

int estilistaExiste(int cod) {
    Estilista e;
    FILE *arq = fopen("estilistas.dat", "rb");
    if (!arq) return 0;
    while (fread(&e, sizeof(Estilista), 1, arq)) {
        if (e.codEstilista == cod) {
            fclose(arq);
            return 1;
        }
    }
    fclose(arq);
    return 0;
}

int estacaoExiste(int cod) {
    Estacao e;
    FILE *arq = fopen("estacoes.dat", "rb");
    if (!arq) return 0;
    while (fread(&e, sizeof(Estacao), 1, arq)) {
        if (e.codEstacao == cod) {
            fclose(arq);
            return 1;
        }
    }
    fclose(arq);
    return 0;
}

int produtoExiste(int cod) {
    Produto p;
    FILE *arq = fopen("produtos.dat", "rb");
    if (!arq) return 0;
    while (fread(&p, sizeof(Produto), 1, arq)) {
        if (p.codigo == cod) {
            fclose(arq);
            return 1;
        }
    }
    fclose(arq);
    return 0;
}

void buscarPorValorEntre() {
    float val1, val2;
    printf("Digite o valor mínimo: ");
    scanf("%f", &val1);
    printf("Digite o valor máximo: ");
    scanf("%f", &val2);
    if (val1 > val2) {
        float temp = val1; val1 = val2; val2 = temp;
    }
    FILE *arq = fopen("recebimentos.dat", "rb");
    if (!arq) { printf("Nenhum recebimento cadastrado.\n"); return; }
    Recebimento r;
    int achou = 0;
    while (fread(&r, sizeof(Recebimento), 1, arq)) {
        if (r.Valor_doc >= val1 && r.Valor_doc <= val2) {
            printf("Documento: %d Valor: %.2f Data Vencimento: %s Cliente: %d\n", r.Num_doc, r.Valor_doc, r.Data_Vencimento, r.Cod_Cli);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum recebimento encontrado entre os valores informados.\n");
    fclose(arq);
}

void buscarPorValorAbaixo() {
    float valor;
    printf("Digite o valor máximo: ");
    scanf("%f", &valor);
    FILE *arq = fopen("recebimentos.dat", "rb");
    if (!arq) { printf("Nenhum recebimento cadastrado.\n"); return; }
    Recebimento r;
    int achou = 0;
    while (fread(&r, sizeof(Recebimento), 1, arq)) {
        if (r.Valor_doc < valor) {
            printf("Documento: %d Valor: %.2f Data Vencimento: %s Cliente: %d\n", r.Num_doc, r.Valor_doc, r.Data_Vencimento, r.Cod_Cli);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum recebimento encontrado abaixo do valor informado.\n");
    fclose(arq);
}

void buscarPorValorAcima() {
    float valor;
    printf("Digite o valor mínimo: ");
    scanf("%f", &valor);
    FILE *arq = fopen("recebimentos.dat", "rb");
    if (!arq) { printf("Nenhum recebimento cadastrado.\n"); return; }
    Recebimento r;
    int achou = 0;
    while (fread(&r, sizeof(Recebimento), 1, arq)) {
        if (r.Valor_doc > valor) {
            printf("Documento: %d Valor: %.2f Data Vencimento: %s Cliente: %d\n", r.Num_doc, r.Valor_doc, r.Data_Vencimento, r.Cod_Cli);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum recebimento encontrado acima do valor informado.\n");
    fclose(arq);
}

void buscarPorCliente() {
    int codCli;
    printf("Digite o código do cliente: ");
    scanf("%d", &codCli);
    if (!clienteExiste(codCli)) { printf("Cliente não existe.\n"); return; }
    FILE *arq = fopen("recebimentos.dat", "rb");
    if (!arq) { printf("Nenhum recebimento cadastrado.\n"); return; }
    Recebimento r;
    int achou = 0;
    while (fread(&r, sizeof(Recebimento), 1, arq)) {
        if (r.Cod_Cli == codCli) {
            printf("Documento: %d Valor: %.2f Data Emissão: %s Data Vencimento: %s\n", r.Num_doc, r.Valor_doc, r.Data_Emissao, r.Data_Vencimento);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum recebimento encontrado para esse cliente.\n");
    fclose(arq);
}

void listarRecebimentos() {
    FILE *arq = fopen("recebimentos.dat", "rb");
    if (!arq) { printf("Nenhum recebimento cadastrado.\n"); return; }
    Recebimento r;
    while (fread(&r, sizeof(Recebimento), 1, arq)) {
        printf("Documento: %d Valor: %.2f Data Emissão: %s Data Vencimento: %s Cliente: %d\n", r.Num_doc, r.Valor_doc, r.Data_Emissao, r.Data_Vencimento, r.Cod_Cli);
    }
    fclose(arq);
}

void alterarRecebimento() {
    int numdoc;
    printf("Digite o número do documento para alterar: ");
    scanf("%d", &numdoc);
    FILE *arq = fopen("recebimentos.dat", "r+b");
    if (!arq) { printf("Nenhum recebimento cadastrado.\n"); return; }
    Recebimento r;
    int achou = 0;
    while (fread(&r, sizeof(Recebimento), 1, arq)) {
        if (r.Num_doc == numdoc) {
            achou = 1;
            printf("Digite o novo valor do documento: ");
            scanf("%f", &r.Valor_doc);
            getchar();
            printf("Digite a nova data de emissão (dd/mm/aaaa): ");
            fgets(r.Data_Emissao, sizeof(r.Data_Emissao), stdin);
            r.Data_Emissao[strcspn(r.Data_Emissao, "\n")] = 0;
            printf("Digite a nova data de vencimento (dd/mm/aaaa): ");
            fgets(r.Data_Vencimento, sizeof(r.Data_Vencimento), stdin);
            r.Data_Vencimento[strcspn(r.Data_Vencimento, "\n")] = 0;
            printf("Digite o código do cliente: ");
            scanf("%d", &r.Cod_Cli);
            if (!clienteExiste(r.Cod_Cli)) { printf("Cliente não existe!\n"); fclose(arq); return; }
            fseek(arq, -sizeof(Recebimento), SEEK_CUR);
            fwrite(&r, sizeof(Recebimento), 1, arq);
            printf("Recebimento alterado com sucesso.\n");
            break;
        }
    }
    if (!achou) printf("Documento não encontrado.\n");
    fclose(arq);
}

int recebimentoExiste(int numdoc) {
    Recebimento r;
    FILE *arq = fopen("recebimentos.dat", "rb");
    if (!arq) return 0;
    while (fread(&r, sizeof(Recebimento), 1, arq)) {
        if (r.Num_doc == numdoc) {
            fclose(arq);
            return 1;
        }
    }
    fclose(arq);
    return 0;
}

void cadastrarRecebimento() {
    Recebimento r;
    FILE *arq = fopen("recebimentos.dat", "ab+");
    if (!arq) { printf("Erro ao abrir arquivo de recebimentos.\n"); return; }
    printf("Digite o número do documento: ");
    scanf("%d", &r.Num_doc);
    if (recebimentoExiste(r.Num_doc)) { printf("Documento já existe!\n"); fclose(arq); return; }
    printf("Digite o valor do documento: ");
    scanf("%f", &r.Valor_doc);
    printf("Digite a data de emissão (dd/mm/aaaa): ");
    getchar();
    fgets(r.Data_Emissao, sizeof(r.Data_Emissao), stdin);
    r.Data_Emissao[strcspn(r.Data_Emissao, "\n")] = 0;
    printf("Digite a data de vencimento (dd/mm/aaaa): ");
    fgets(r.Data_Vencimento, sizeof(r.Data_Vencimento), stdin);
    r.Data_Vencimento[strcspn(r.Data_Vencimento, "\n")] = 0;
    printf("Digite o código do cliente: ");
    scanf("%d", &r.Cod_Cli);
    if (!clienteExiste(r.Cod_Cli)) { printf("Cliente não existe!\n"); fclose(arq); return; }
    fwrite(&r, sizeof(Recebimento), 1, arq);
    fclose(arq);
    printf("Recebimento cadastrado com sucesso!\n");
}

void alterarCliente() {
    int cod;
    printf("Digite o código do cliente para alterar: ");
    scanf("%d", &cod);
    FILE *arq = fopen("clientes.dat", "r+b");
    if (!arq) { printf("Nenhum cliente cadastrado.\n"); return; }
    Cliente c;
    int achou = 0;
    while (fread(&c, sizeof(Cliente), 1, arq)) {
        if (c.Cod_Cli == cod) {
            achou = 1;
            printf("Digite o novo nome: ");
            getchar();
            fgets(c.Nome, sizeof(c.Nome), stdin);
            c.Nome[strcspn(c.Nome, "\n")] = 0;
            printf("Digite o novo endereço: ");
            fgets(c.Endereco, sizeof(c.Endereco), stdin);
            c.Endereco[strcspn(c.Endereco, "\n")] = 0;
            printf("Digite o novo telefone: ");
            fgets(c.Fone, sizeof(c.Fone), stdin);
            c.Fone[strcspn(c.Fone, "\n")] = 0;
            fseek(arq, -sizeof(Cliente), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, arq);
            printf("Cliente alterado com sucesso.\n");
            break;
        }
    }
    if (!achou) printf("Cliente não encontrado.\n");
    fclose(arq);
}

void excluirCliente() {
    int cod;
    printf("Digite o código do cliente para excluir: ");
    scanf("%d", &cod);
    FILE *arq = fopen("clientes.dat", "rb");
    if (!arq) { printf("Nenhum cliente cadastrado.\n"); return; }
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) { printf("Erro ao abrir arquivo temporário.\n"); fclose(arq); return; }
    Cliente c;
    int achou = 0;
    while (fread(&c, sizeof(Cliente), 1, arq)) {
        if (c.Cod_Cli == cod) { achou = 1; continue; }
        fwrite(&c, sizeof(Cliente), 1, temp);
    }
    fclose(arq);
    fclose(temp);
    if (achou) {
        remove("clientes.dat");
        rename("temp.dat", "clientes.dat");
        printf("Cliente excluído com sucesso.\n");
    } else {
        printf("Cliente não encontrado.\n");
        remove("temp.dat");
    }
}

void listarClientes() {
    FILE *arq = fopen("clientes.dat", "rb");
    if (!arq) { printf("Nenhum cliente cadastrado.\n"); return; }
    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, arq)) {
        printf("Código: %d Nome: %s Endereço: %s Telefone: %s\n", c.Cod_Cli, c.Nome, c.Endereco, c.Fone);
    }
    fclose(arq);
}

void cadastrarCliente() {
    Cliente c;
    FILE *arq = fopen("clientes.dat", "ab+");
    if (!arq) { printf("Erro ao abrir arquivo de clientes.\n"); return; }
    printf("Digite o código do cliente: ");
    scanf("%d", &c.Cod_Cli);
    if (clienteExiste(c.Cod_Cli)) { printf("Cliente com código %d já existe!\n", c.Cod_Cli); fclose(arq); return; }
    printf("Digite o nome: ");
    getchar();
    fgets(c.Nome, sizeof(c.Nome), stdin);
    c.Nome[strcspn(c.Nome, "\n")] = 0;
    printf("Digite o endereço: ");
    fgets(c.Endereco, sizeof(c.Endereco), stdin);
    c.Endereco[strcspn(c.Endereco, "\n")] = 0;
    printf("Digite o telefone: ");
    fgets(c.Fone, sizeof(c.Fone), stdin);
    c.Fone[strcspn(c.Fone, "\n")] = 0;
    fwrite(&c, sizeof(Cliente), 1, arq);
    fclose(arq);
    printf("Cliente cadastrado com sucesso!\n");
}

void cadastrarEstacao() {
    Estacao e;
    FILE *arq = fopen("estacoes.dat", "ab+");
    if (!arq) { printf("Erro ao abrir arquivo de estações.\n"); return; }
    printf("Digite o código da estação: ");
    scanf("%d", &e.codEstacao);
    if (estacaoExiste(e.codEstacao)) { printf("Estação já existe!\n"); fclose(arq); return; }
    printf("Digite o nome da estação: ");
    getchar();
    fgets(e.nome, sizeof(e.nome), stdin);
    e.nome[strcspn(e.nome, "\n")] = 0;
    fwrite(&e, sizeof(Estacao), 1, arq);
    fclose(arq);
    printf("Estação cadastrada com sucesso!\n");
}

void cadastrarEstilista() {
    Estilista e;
    FILE *arq = fopen("estilistas.dat", "ab+");
    if (!arq) { printf("Erro ao abrir arquivo de estilistas.\n"); return; }
    printf("Digite o código do estilista: ");
    scanf("%d", &e.codEstilista);
    if (estilistaExiste(e.codEstilista)) { printf("Estilista já existe!\n"); fclose(arq); return; }
    printf("Digite o nome do estilista: ");
    getchar();
    fgets(e.nome, sizeof(e.nome), stdin);
    e.nome[strcspn(e.nome, "\n")] = 0;
    printf("Digite o salário: ");
    scanf("%f", &e.salario);
    fwrite(&e, sizeof(Estilista), 1, arq);
    fclose(arq);
    printf("Estilista cadastrado com sucesso!\n");
}

void listarRecebimentosPorPeriodoComAtraso() {
    char dataAtual[15];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // Formata data atual em dd/mm/aaaa
    snprintf(dataAtual, sizeof(dataAtual), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    
    FILE *arq = fopen("recebimentos.dat", "rb");
    if (!arq) {
        printf("Nenhum recebimento cadastrado.\n");
        return;
    }
    
    Recebimento r;
    int achou = 0;
    while (fread(&r, sizeof(Recebimento), 1, arq)) {
        if (dataAnterior(r.Data_Vencimento, dataAtual)) { // vencimento antes de hoje
            printf("Documento: %d Valor: %.2f Data Vencimento: %s Cliente: %d\n", r.Num_doc, r.Valor_doc, r.Data_Vencimento, r.Cod_Cli);
            achou = 1;
        }
    }
    
    if (!achou)
        printf("Nenhum recebimento em atraso.\n");
    
    fclose(arq);
}

void cadastrarRoupa() {
    Roupa r;
    FILE *arq = fopen("roupas.dat", "ab+");
    if (!arq) { printf("Erro ao abrir arquivo de roupas.\n"); return; }
    printf("Digite o código da roupa: ");
    scanf("%d", &r.codRoupa);
    printf("Digite a descrição: ");
    getchar();
    fgets(r.descricao, sizeof(r.descricao), stdin);
    r.descricao[strcspn(r.descricao, "\n")] = 0;
    printf("Digite o código do estilista: ");
    scanf("%d", &r.codEstilista);
    if (!estilistaExiste(r.codEstilista)) { printf("Estilista não existe!\n"); fclose(arq); return; }
    printf("Digite o código da estação: ");
    scanf("%d", &r.codEstacao);
    if (!estacaoExiste(r.codEstacao)) { printf("Estação não existe!\n"); fclose(arq); return; }
    printf("Digite o ano: ");
    scanf("%d", &r.ano);
    fwrite(&r, sizeof(Roupa), 1, arq);
    fclose(arq);
    printf("Roupa cadastrada com sucesso!\n");
}

void reajustarPreco15Porcento() {
    FILE *arq = fopen("produtos.dat", "r+b");
    if (!arq) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    Produto p;
    while (fread(&p, sizeof(Produto), 1, arq)) {
        p.preco = p.preco * 1.15f;  // aumenta 15%
        fseek(arq, -sizeof(Produto), SEEK_CUR);
        fwrite(&p, sizeof(Produto), 1, arq);
        fflush(arq);
    }
    fclose(arq);
    printf("Reajuste de 15%% aplicado a todos os produtos.\n");
}


void listarRoupasPorEstacao() {
    int codEst;
    printf("Digite o código da estação: ");
    scanf("%d", &codEst);
    if (!estacaoExiste(codEst)) { printf("Estação não existe.\n"); return; }
    FILE *arq = fopen("roupas.dat", "rb");
    if (!arq) { printf("Nenhuma roupa cadastrada.\n"); return; }
    Roupa r;
    int achou = 0;
    while (fread(&r, sizeof(Roupa), 1, arq)) {
        if (r.codEstacao == codEst) {
            printf("Código: %d Descrição: %s Ano: %d Estilista: %d\n", r.codRoupa, r.descricao, r.ano, r.codEstilista);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhuma roupa encontrada para essa estação.\n");
    fclose(arq);
}

void criarArquivoNotas() {
    FILE *arq = fopen("notas.dat", "wb"); // cria ou reseta arquivo
    if (!arq) {
        printf("Erro ao criar arquivo de notas.\n");
        return;
    }
    fclose(arq);
    printf("Arquivo de notas criado com sucesso.\n");
}

void incluirNotas() {
    Aluno a;
    FILE *arq = fopen("notas.dat", "ab");
    if (!arq) {
        printf("Erro ao abrir arquivo de notas.\n");
        return;
    }
    printf("Digite o número do aluno: ");
    scanf("%d", &a.numero);
    printf("Digite o nome do aluno: ");
    getchar();
    fgets(a.nome, sizeof(a.nome), stdin);
    a.nome[strcspn(a.nome, "\n")] = 0;
    printf("Digite a nota 1: ");
    scanf("%f", &a.nota1);
    printf("Digite a nota 2: ");
    scanf("%f", &a.nota2);

    fwrite(&a, sizeof(Aluno), 1, arq);
    fclose(arq);
    printf("Notas incluídas com sucesso.\n");
}

void excluirProdutoPorCodigo() {
    int cod;
    printf("Digite o código do produto para excluir: ");
    scanf("%d", &cod);

    FILE *arq = fopen("produtos.dat", "rb");
    if (!arq) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arq);
        return;
    }

    Produto p;
    int achou = 0;
    while (fread(&p, sizeof(Produto), 1, arq)) {
        if (p.codigo == cod) {
            achou = 1;
            continue; // pula o produto para excluir
        }
        fwrite(&p, sizeof(Produto), 1, temp);
    }

    fclose(arq);
    fclose(temp);

    if (achou) {
        remove("produtos.dat");
        rename("temp.dat", "produtos.dat");
        printf("Produto excluído com sucesso.\n");
    } else {
        printf("Produto não encontrado.\n");
        remove("temp.dat");
    }
}

void criarArquivoProdutos() {
    FILE *arq = fopen("produtos.dat", "wb"); // reseta arquivo produtos
    if (!arq) {
        printf("Erro ao criar arquivo de produtos.\n");
        return;
    }
    fclose(arq);
    printf("Arquivo de produtos criado com sucesso.\n");
}


void listarRoupasPorAno() {
    int ano;
    printf("Digite o ano: ");
    scanf("%d", &ano);
    FILE *arq = fopen("roupas.dat", "rb");
    if (!arq) { printf("Nenhuma roupa cadastrada.\n"); return; }
    Roupa r;
    int achou = 0;
    while (fread(&r, sizeof(Roupa), 1, arq)) {
        if (r.ano == ano) {
            printf("Código: %d Descrição: %s Ano: %d Estilista: %d Estação: %d\n", r.codRoupa, r.descricao, r.ano, r.codEstilista, r.codEstacao);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhuma roupa encontrada para esse ano.\n");
    fclose(arq);
}

void incluirProduto() {
    Produto p;
    FILE *arq = fopen("produtos.dat", "ab");
    if (!arq) { printf("Erro ao abrir arquivo de produtos.\n"); return; }
    printf("Digite o código do produto: ");
    scanf("%d", &p.codigo);
    if (produtoExiste(p.codigo)) { printf("Produto já existe!\n"); fclose(arq); return; }
    printf("Digite a descrição do produto: ");
    getchar();
    fgets(p.descricao, sizeof(p.descricao), stdin);
    p.descricao[strcspn(p.descricao, "\n")] = 0;
    printf("Digite o preço: ");
    scanf("%f", &p.preco);
    fwrite(&p, sizeof(Produto), 1, arq);
    fclose(arq);
    printf("Produto incluído com sucesso.\n");
}

void consultarProdutosPrecoMaior500() {
    FILE *arq = fopen("produtos.dat", "rb");
    if (!arq) { printf("Nenhum produto cadastrado.\n"); return; }
    Produto p;
    int achou = 0;
    while (fread(&p, sizeof(Produto), 1, arq)) {
        if (p.preco > 500) {
            printf("Código: %d Descrição: %s Preço: %.2f\n", p.codigo, p.descricao, p.preco);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum produto com preço maior que 500.\n");
    fclose(arq);
}

void aumentarPreco10ReaisMais100() {
    FILE *arq = fopen("produtos.dat", "r+b");
    if (!arq) { printf("Nenhum produto cadastrado.\n"); return; }
    Produto p;
    while (fread(&p, sizeof(Produto), 1, arq)) {
        if (p.preco > 100) {
            p.preco += 10.0f;
            fseek(arq, -sizeof(Produto), SEEK_CUR);
            fwrite(&p, sizeof(Produto), 1, arq);
            fflush(arq);
        }
    }
    fclose(arq);
    printf("Aumento aplicado aos produtos com preço acima de 100.\n");
}

void consultarProdutosComNomeLetraEPrecoEntre() {
    float val1, val2;
    printf("Digite o valor mínimo: ");
    scanf("%f", &val1);
    printf("Digite o valor máximo: ");
    scanf("%f", &val2);
    if (val1 > val2) {
        float temp = val1; val1 = val2; val2 = temp;
    }
    FILE *arq = fopen("produtos.dat", "rb");
    if (!arq) { printf("Nenhum produto cadastrado.\n"); return; }
    Produto p;
    int achou = 0;
    while (fread(&p, sizeof(Produto), 1, arq)) {
        if ((p.descricao[0] == 'E' || p.descricao[0] == 'e') && p.preco >= val1 && p.preco <= val2) {
            printf("Código: %d Descrição: %s Preço: %.2f\n", p.codigo, p.descricao, p.preco);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum produto encontrado com letra 'E' e preço entre os valores.\n");
    fclose(arq);
}

void consultarProdutosComecamComM() {
    FILE *arq = fopen("produtos.dat", "rb");
    if (!arq) { printf("Nenhum produto cadastrado.\n"); return; }
    Produto p;
    int achou = 0;
    while (fread(&p, sizeof(Produto), 1, arq)) {
        if (p.descricao[0] == 'M' || p.descricao[0] == 'm') {
            printf("Código: %d Descrição: %s Preço: %.2f\n", p.codigo, p.descricao, p.preco);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum produto encontrado que começa com 'M'.\n");
    fclose(arq);
}

void consultarProdutosPrecoMenor15() {
    FILE *arq = fopen("produtos.dat", "rb");
    if (!arq) { printf("Nenhum produto cadastrado.\n"); return; }
    Produto p;
    int achou = 0;
    while (fread(&p, sizeof(Produto), 1, arq)) {
        if (p.preco < 15) {
            printf("Código: %d Descrição: %s Preço: %.2f\n", p.codigo, p.descricao, p.preco);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum produto encontrado com preço menor que 15.\n");
    fclose(arq);
}

void excluirProdutosPrecoMaior200() {
    FILE *arq = fopen("produtos.dat", "rb");
    if (!arq) { printf("Nenhum produto cadastrado.\n"); return; }
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) { printf("Erro ao criar arquivo temporário.\n"); fclose(arq); return; }
    Produto p;
    int achou = 0;
    while (fread(&p, sizeof(Produto), 1, arq)) {
        if (p.preco > 200) { achou = 1; continue; }
        fwrite(&p, sizeof(Produto), 1, temp);
    }
    fclose(arq);
    fclose(temp);
    if (achou) {
        remove("produtos.dat");
        rename("temp.dat", "produtos.dat");
        printf("Produtos com preço maior que 200 excluídos.\n");
    } else {
        printf("Nenhum produto encontrado com preço maior que 200.\n");
        remove("temp.dat");
    }
}

void aplicarDescontoPorcentagemEntreValores() {
    float val1, val2, desconto;
    printf("Digite o valor mínimo: ");
    scanf("%f", &val1);
    printf("Digite o valor máximo: ");
    scanf("%f", &val2);
    printf("Digite a porcentagem de desconto: ");
    scanf("%f", &desconto);
    if (val1 > val2) {
        float temp = val1; val1 = val2; val2 = temp;
    }
    FILE *arq = fopen("produtos.dat", "r+b");
    if (!arq) { printf("Nenhum produto cadastrado.\n"); return; }
    Produto p;
    int achou = 0;
    while (fread(&p, sizeof(Produto), 1, arq)) {
        if (p.preco >= val1 && p.preco <= val2) {
            p.preco -= p.preco * (desconto / 100);
            fseek(arq, -sizeof(Produto), SEEK_CUR);
            fwrite(&p, sizeof(Produto), 1, arq);
            fflush(arq);
            achou = 1;
        }
    }
    fclose(arq);
    if (achou)
        printf("Desconto aplicado nos produtos dentro dos valores informados.\n");
    else
        printf("Nenhum produto encontrado dentro dos valores informados.\n");
}

void menuProdutos() {
    int opc;
    do {
        printf("\n--- Menu Produtos ---\n");
        printf("1. Incluir produto\n");
        printf("2. Consultar produtos com preço maior que 500\n");
        printf("3. Aumentar preço em 10 reais para produtos com preço maior que 100\n");
        printf("4. Consultar produtos com descrição começando com 'E' e preço entre dois valores\n");
        printf("5. Consultar produtos com descrição começando com 'M'\n");
        printf("6. Consultar produtos com preço menor que 15\n");
        printf("7. Excluir produtos com preço maior que 200\n");
        printf("8. Aplicar desconto em porcentagem para produtos com preço entre dois valores\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1: incluirProduto(); break;
            case 2: consultarProdutosPrecoMaior500(); break;
            case 3: aumentarPreco10ReaisMais100(); break;
            case 4: consultarProdutosComNomeLetraEPrecoEntre(); break;
            case 5: consultarProdutosComecamComM(); break;
            case 6: consultarProdutosPrecoMenor15(); break;
            case 7: excluirProdutosPrecoMaior200(); break;
            case 8: aplicarDescontoPorcentagemEntreValores(); break;
            case 0: break;
            default: printf("Opção inválida.\n");
        }
    } while (opc != 0);
}

void menuClientes() {
    int opc;
    do {
        printf("\n--- Menu Clientes ---\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listar clientes\n");
        printf("3. Alterar cliente\n");
        printf("4. Excluir cliente\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1: cadastrarCliente(); break;
            case 2: listarClientes(); break;
            case 3: alterarCliente(); break;
            case 4: excluirCliente(); break;
            case 0: break;
            default: printf("Opção inválida.\n");
        }
    } while (opc != 0);
}

void menuRecebimentos() {
    int opc;
    do {
        printf("\n--- Menu Recebimentos ---\n");
        printf("1. Cadastrar recebimento\n");
        printf("2. Listar recebimentos\n");
        printf("3. Alterar recebimento\n");
        printf("4. Buscar recebimentos por valor entre dois valores\n");
        printf("5. Buscar recebimentos por valor abaixo de um valor\n");
        printf("6. Buscar recebimentos por valor acima de um valor\n");
        printf("7. Buscar recebimentos por código do cliente\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1: cadastrarRecebimento(); break;
            case 2: listarRecebimentos(); break;
            case 3: alterarRecebimento(); break;
            case 4: buscarPorValorEntre(); break;
            case 5: buscarPorValorAbaixo(); break;
            case 6: buscarPorValorAcima(); break;
            case 7: buscarPorCliente(); break;
            case 0: break;
            default: printf("Opção inválida.\n");
        }
    } while (opc != 0);
}

void menuEstilistas() {
    int opc;
    do {
        printf("\n--- Menu Estilistas ---\n");
        printf("1. Cadastrar estilista\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1: cadastrarEstilista(); break;
            case 0: break;
            default: printf("Opção inválida.\n");
        }
    } while (opc != 0);
}

void menuEstacoes() {
    int opc;
    do {
        printf("\n--- Menu Estações ---\n");
        printf("1. Cadastrar estação\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1: cadastrarEstacao(); break;
            case 0: break;
            default: printf("Opção inválida.\n");
        }
    } while (opc != 0);
}

void menuRoupas() {
    int opc;
    do {
        printf("\n--- Menu Roupas ---\n");
        printf("1. Cadastrar roupa\n");
        printf("2. Listar roupas por estação\n");
        printf("3. Listar roupas por ano\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1: cadastrarRoupa(); break;
            case 2: listarRoupasPorEstacao(); break;
            case 3: listarRoupasPorAno(); break;
            case 0: break;
            default: printf("Opção inválida.\n");
        }
    } while (opc != 0);
}

int main() {
    int opc;
    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listar clientes\n");
        printf("3. Excluir cliente\n");
        printf("4. Alterar cliente\n");
        printf("5. Cadastrar recebimento\n");
        printf("6. Alterar recebimento\n");
        printf("7. Listar recebimentos por período com atraso\n");
        printf("8. Buscar recebimentos por cliente\n");
        printf("9. Buscar recebimentos por valor acima\n");
        printf("10. Buscar recebimentos por valor abaixo\n");
        printf("11. Buscar recebimentos por valor entre\n");
        printf("12. Cadastrar estação\n");
        printf("13. Cadastrar estilista\n");
        printf("14. Cadastrar roupa\n");
        printf("15. Listar roupas por estação\n");
        printf("16. Criar arquivo de notas\n");
        printf("17. Incluir notas\n");
        printf("18. Criar arquivo de produtos\n");
        printf("19. Incluir produto\n");
        printf("20. Consultar produtos que começam com 'M'\n");
        printf("21. Reajustar preço em 15 por cento\n");
        printf("22. Consultar produtos com preço menor que 15\n");
        printf("23. Excluir produto por código\n");
        printf("24. Excluir produtos com preço maior que 200\n");
        printf("25. Aplicar desconto porcentagem entre valores\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: cadastrarCliente(); break;
            case 2: listarClientes(); break;
            case 3: excluirCliente(); break;
            case 4: alterarCliente(); break;
            case 5: cadastrarRecebimento(); break;
            case 6: alterarRecebimento(); break;
            case 7: listarRecebimentosPorPeriodoComAtraso(); break;
            case 8: buscarPorCliente(); break;
            case 9: buscarPorValorAcima(); break;
            case 10: buscarPorValorAbaixo(); break;
            case 11: buscarPorValorEntre(); break;
            case 12: cadastrarEstacao(); break;
            case 13: cadastrarEstilista(); break;
            case 14: cadastrarRoupa(); break;
            case 15: listarRoupasPorEstacao(); break;
            case 16: criarArquivoNotas(); break;
            case 17: incluirNotas(); break;
            case 18: criarArquivoProdutos(); break;
            case 19: incluirProduto(); break;
            case 20: consultarProdutosComecamComM(); break;
            case 21: reajustarPreco15Porcento(); break;
            case 22: consultarProdutosPrecoMenor15(); break;
            case 23: excluirProdutoPorCodigo(); break;
            case 24: excluirProdutosPrecoMaior200(); break;
            case 25: aplicarDescontoPorcentagemEntreValores(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (opc != 0);

    return 0;
}
