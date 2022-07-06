#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Lib usada para a funcão isdigit
#include <dirent.h> // Lib para verificar se a pasta existe
#include <unistd.h> // Lib para criar uma pasta
#include <time.h> // Lib usada para verificar a data atual do sistema
#include "functions.h"

// Variáveis globais
int nextClientID = 1,
	nextGestorID = 1,
	nextProdutoID = 1,
	nextStockID = 1,
	nextAccountID = 1,
	nextBuyID = 1;
	
ListaContasLogin *listaContasLogin;
ListaCliente *listaClientes;
ListaGestor *listaGestor;
ListaProduto *listaProduto;
ListaStock *listaStock;
ListaCarrinhoCompras *listaCarrinhoCompras;
ListaCompra *listaCompra;
ListaItemsCompra *listaItemsCompra;
	
ContasLogin contaLogin;
Cliente cliente;
Gestor gestor;
//

char* lerPassowrd() {
	char pass[30], c;
    int index = 0;

	while((c = getch()) != 13){
        if(index < 0)
            index = 0;
        if(c == 8 && index > 0){
			putch('\b');
            putch(NULL);
            putch('\b');
            index--;
       		continue;
        }
        if (c != 8) {
        	if (index == 30) continue;
        	pass[index++] = c;
        	putch('*');
		}
    }
    pass[index] = '\0';
    
    return pass;
}

void lerInteiro(int *n) {
	int temp, res;

	// Verifica se o valor introduzido é um inteiro, se não for, faz loop até introduzir um inteiro
	res = scanf("%d", &temp);
	while(res != 1) {
        printf("Precisa escrever um número inteiro.\n");
		printf("Tente novamente: ");
		fflush(stdin);
        res = scanf("%d", &temp);
    }

	fflush(stdin);

	// Manda o valor da variável temp para o ponteiro *n
	*n = temp;
}

void lerFloat(float *n) {
	int res;
	float temp;

	// Verifica se o valor introduzido é um float, se não for, faz loop até introduzir um float
	res = scanf("%f", &temp);
	while(res != 1) {
		printf("Precisa escrever um número real.\n");
		printf("Tente novamente: ");
		fflush(stdin);
		res = scanf("%f", &temp);
	}

	fflush(stdin);

	// Mandar o valor da variável temp para o ponteiro *n
	*n = temp;
}

ListaContasLogin* criaListaContasLogin() {
	ListaContasLogin* li = (ListaContasLogin*) malloc(sizeof(ListaContasLogin));
	
	if (li != NULL) *li = NULL;
	
	return li;
}

ListaCliente* criaListaCliente() {
	ListaCliente* li = (ListaCliente*) malloc(sizeof(ListaCliente));
	
	if (li != NULL) *li = NULL;
	
	return li;
}

ListaGestor* criaListaGestor() {
	ListaGestor* li = (ListaGestor*) malloc(sizeof(ListaGestor));
	
	if (li != NULL) *li = NULL;
	
	return li;
}

ListaProduto* criaListaProduto() {
	ListaProduto* li = (ListaProduto*) malloc(sizeof(ListaProduto));
	
	if (li != NULL) *li = NULL;
	
	return li;
}

ListaStock* criaListaStock() {
	ListaStock* li = (ListaStock*) malloc(sizeof(ListaStock));
	
	if (li != NULL) *li = NULL;
	
	return li;
}

ListaCarrinhoCompras* criaListaCarrinhoCompras() {
	ListaCarrinhoCompras* li = (ListaCarrinhoCompras*) malloc(sizeof(ListaCarrinhoCompras));
	
	if (li != NULL) *li = NULL;
	
	return li;
}

ListaCompra* criaListaCompra() {
	ListaCompra* li = (ListaCompra*) malloc(sizeof(ListaCompra));
	
	if (li != NULL) *li = NULL;
	
	return li;
}

ListaItemsCompra* criaListaItemsCompra() {
	ListaItemsCompra* li = (ListaItemsCompra*) malloc(sizeof(ListaItemsCompra));
	
	if (li != NULL) *li = NULL;
	
	return li;
}

void libertaListaContasLogin(ListaContasLogin* li) {
	if (li != NULL) {
		ElementoContasLogin* no;
		while((*li) != NULL) {
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}

void libertaListaCliente(ListaCliente* li) {
	if (li != NULL) {
		ElementoCliente* no;
		while((*li) != NULL) {
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}

void libertaListaGestor(ListaGestor* li) {
	if (li != NULL) {
		ElementoGestor* no;
		while((*li) != NULL) {
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}

void libertaListaProduto(ListaProduto* li) {
	if (li != NULL) {
		ElementoProduto* no;
		while((*li) != NULL) {
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}

void libertaListaStock(ListaStock* li) {
	if (li != NULL) {
		ElementoStock* no;
		while((*li) != NULL) {
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}

void libertaListaCarrinhoCompras(ListaCarrinhoCompras* li) {
	if (li != NULL) {
		ElementoCarrinhoCompras* no;
		while((*li) != NULL) {
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}

void libertaListaCompra(ListaCompra* li) {
	if (li != NULL) {
		ElementoCompra* no;
		while((*li) != NULL) {
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}

void libertaListaItemsCompra(ListaItemsCompra* li) {
	if (li != NULL) {
		ElementoItemsCompra* no;
		while((*li) != NULL) {
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}

int startProgram() {
	// Cria as listas
	printf("A criar as listas...\n");
	listaContasLogin = criaListaContasLogin();
	if (listaContasLogin == NULL) return 0;
	
	listaClientes = criaListaCliente();
	if (listaClientes == NULL) return 0;
	
	listaGestor = criaListaGestor();
	if (listaGestor == NULL) return 0;
	
	listaProduto = criaListaProduto();
	if (listaProduto == NULL) return 0;
	
	listaStock = criaListaStock();
	if (listaStock == NULL) return 0;
	
	listaCarrinhoCompras = criaListaCarrinhoCompras();
	if (listaCarrinhoCompras == NULL) return 0;
	
	listaCompra = criaListaCompra();
	if (listaCompra == NULL) return 0;
	
	listaItemsCompra = criaListaItemsCompra();
	if (listaItemsCompra == NULL) return 0;
	//
	
	// Verifica se a pasta "database" exist
	printf("A verificar a pasta da base de dados...\n");
	DIR* dir = opendir(DATABASE_FOLDER);
	if (dir != NULL) {
		closedir(dir);
	} else {
		int dirCreated = mkdir(DATABASE_FOLDER);
		if (dirCreated != 0) return 0; // Se a var "dirCreated" for diferente de 0 é porque a pasta não foi criada
	}
	//
	
	// Verifica qual foi o ultimo id dos dados no sistema
	printf("A verificar os ids do sistema...\n");
	if (fileExist(&FILE_ID_CLIENTE) == 1) {
		if (getIdFromFile(&nextClientID, &FILE_ID_CLIENTE) == 0) return 0;
	} else {
		if (changeIDInFile(&FILE_ID_CLIENTE, nextClientID) == 0) return 0;
	}
	
	if (fileExist(&FILE_ID_GESTOR) == 1) {
		if (getIdFromFile(&nextGestorID, &FILE_ID_GESTOR) == 0) return 0;
	} else {
		if (changeIDInFile(&FILE_ID_GESTOR, nextGestorID) == 0) return 0;
	}
	
	if (fileExist(&FILE_ID_PRODUCT) == 1) {
		if (getIdFromFile(&nextProdutoID, &FILE_ID_PRODUCT) == 0) return 0;
	} else {
		if (changeIDInFile(&FILE_ID_PRODUCT, nextProdutoID) == 0) return 0;
	}
	
	if (fileExist(&FILE_ID_STOCK) == 1) {
		if (getIdFromFile(&nextStockID, &FILE_ID_STOCK) == 0) return 0;
	} else {
		if (changeIDInFile(&FILE_ID_STOCK, nextStockID) == 0) return 0;
	}
	
	if (fileExist(&FILE_ID_ACCOUNT) == 1) {
		if (getIdFromFile(&nextAccountID, &FILE_ID_ACCOUNT) == 0) return 0;
	} else {
		if (changeIDInFile(&FILE_ID_ACCOUNT, nextAccountID) == 0) return 0;
	}
	
	if (fileExist(&FILE_ID_COMPRA) == 1) {
		if (getIdFromFile(&nextBuyID, &FILE_ID_COMPRA) == 0) return 0;
	} else {
		if (changeIDInFile(&FILE_ID_COMPRA, nextBuyID) == 0) return 0;
	}
	//
	
	// Função para carregar os registos dos arquivos
	printf("A carregar os registos da base de dados...\n");
	
	if (fileExist(&FILE_ACCOUNT))
		if (carregarContasLogin() == 0) return 0;
	
	if (fileExist(&FILE_CLIENTES))
		if (carregarClientes() == 0) return 0;
	
	if (fileExist(&FILE_GESTORES))
		if (carregarGestores() == 0) return 0;
	
	if (fileExist(&FILE_PRODUCTS))
		if (carregarProdutos() == 0) return 0;
	
	if (fileExist(&FILE_STOCKS))
		if (carregarStock() == 0) return 0;
	
	if (fileExist(&FILE_COMPRAS))
		if (carregarCompras() == 0) return 0;
	
	if (fileExist(&FILE_ITEMS_COMPRAS))
		if (carregarItemsCompras() == 0) return 0;
	//
	
	// Verifica se tem pelo menos uma conta de gestor, e verifica o stock dos produtos
	printf("A verificar os processos do sistema...\n");
	if ((*listaGestor) == NULL || (*listaContasLogin) == NULL) {
		ContasLogin contaLogin = { nextAccountID, "admin", "passwordAdmin", 2, nextGestorID, 1 };
		Gestor gestor = { nextGestorID, "Admin" };
		
		if (insereGestor(listaGestor, gestor, 0) == 0) return 0;
		
		if (insereContaLogin(listaContasLogin, contaLogin, 0) == 0) return 0;
		
		printf("Conta Administrador recriada.\n");
	}
	
	verificarStocksProdutos(listaStock);
	//
	
	return 1;
}

void endProgram() {
	libertaListaContasLogin(listaContasLogin);
	libertaListaCliente(listaClientes);
	libertaListaGestor(listaGestor);
	libertaListaProduto(listaProduto);
	libertaListaStock(listaStock);
	libertaListaCarrinhoCompras(listaCarrinhoCompras);
	libertaListaCompra(listaCompra);
	libertaListaItemsCompra(listaItemsCompra);
}

int getIdFromFile(int *n, char *file) {
	FILE *fp;
	int id;
	
	fp = fopen(file, "rb");
	if (fp == NULL) return 0;
	
	fread(&id, sizeof(int), 1, fp);
	
	if (id != NULL) *n = id;
	else *n = 1;
	
	fclose(fp);
		
	return 1;
}

int fileExist(char *file) {
	FILE *fp;
	
	if (fp = fopen(file, "rb")) {
		fclose(fp);
		return 1;
	}
	
	return 0;
}

int changeIDInFile(char *file, int id) {
	FILE *fp;
	
	fp = fopen(file, "wb");
	
	if (fp == NULL) return 0;
	
	fwrite(&id, sizeof(int), 1, fp);
	
	fclose(fp);
	
	return fwrite == 0 ? 0 : 1;
}

int insereContaLogin(ListaContasLogin* li, ContasLogin contaLogin, int isFromSystem) {
	if(li == NULL) return 0;
	
    ElementoContasLogin *no;
    no = (ElementoContasLogin*) malloc(sizeof(ElementoContasLogin));
    if(no == NULL) return 0;
    
    no->contaLogin = contaLogin;
    no->prox = NULL;
    
    if((*li) == NULL){
        *li = no;
    }else{
        ElementoContasLogin *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    
    if (isFromSystem == 0) {
    	if (salvarContasLogin(li) == 0) return 0;
    	
    	nextAccountID++;
    	if (changeIDInFile(&FILE_ID_ACCOUNT, nextAccountID) == 0) return 0;
	}
    
    return 1;
}

int insereCliente(ListaCliente* li, Cliente cliente, int isFromSystem) {
	if(li == NULL) return 0;
	
    ElementoCliente *no;
    no = (ElementoCliente*) malloc(sizeof(ElementoCliente));
    if(no == NULL) return 0;
    
    no->cliente = cliente;
    no->prox = NULL;
    
    if((*li) == NULL){
        *li = no;
    }else{
        ElementoCliente *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    
    if (isFromSystem == 0) {
    	if (salvarClientes(li) == 0) return 0;
    	
    	nextClientID++;
    	if (changeIDInFile(&FILE_ID_CLIENTE, nextClientID) == 0) return 0;
	}
    
    return 1;
}

int insereGestor(ListaGestor* li, Gestor gestor, int isFromSystem) {
	if(li == NULL) return 0;
	
    ElementoGestor *no;
    no = (ElementoGestor*) malloc(sizeof(ElementoGestor));
    if(no == NULL) return 0;
    
    no->gestor = gestor;
    no->prox = NULL;
    
    if((*li) == NULL){
        *li = no;
    }else{
        ElementoGestor *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    
    if (isFromSystem == 0) {
    	if (salvarGestores(li) == 0) return 0;
    	
    	nextGestorID++;
    	if (changeIDInFile(&FILE_ID_GESTOR, nextGestorID) == 0) return 0;
	}
    
    return 1;
}

int insereProduto(ListaProduto* li, Produto produto, int isFromSystem) {
	if(li == NULL) return 0;
	
    ElementoProduto *no;
    no = (ElementoProduto*) malloc(sizeof(ElementoProduto));
    if(no == NULL) return 0;
    
    no->produto = produto;
    no->prox = NULL;
    
    if((*li) == NULL){
        *li = no;
    }else{
        ElementoProduto *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    
    if (isFromSystem == 0) {
    	if (salvarProdutos(li) == 0) return 0;
    	
    	nextProdutoID++;
    	if (changeIDInFile(&FILE_ID_PRODUCT, nextProdutoID) == 0) return 0;
	}
    
    return 1;
}

int insereStock(ListaStock* li, Stock stock, int isFromSystem) {
	if(li == NULL) return 0;
	
    ElementoStock *no;
    no = (ElementoStock*) malloc(sizeof(ElementoStock));
    if(no == NULL) return 0;
    
    no->stock = stock;
    no->prox = NULL;
    
    if((*li) == NULL){
        *li = no;
    }else{
        ElementoStock *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    
    if (isFromSystem == 0) {
    	if (salvarStock(li) == 0) return 0;
    
	    nextStockID++;
	    if (changeIDInFile(&FILE_ID_STOCK, nextStockID) == 0) return 0;
	}
    
    return 1;
}

int insereCarrinhoCompras(ListaCarrinhoCompras* li, CarrinhoCompras carrinhoCompra) {
	if(li == NULL) return 0;
	
    ElementoCarrinhoCompras *no;
    no = (ElementoCarrinhoCompras*) malloc(sizeof(ElementoCarrinhoCompras));
    if(no == NULL) return 0;
    
    no->carrinhoCompras = carrinhoCompra;
    no->prox = NULL;
    
    if((*li) == NULL){
        *li = no;
    }else{
        ElementoCarrinhoCompras *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    
    return 1;
}

int insereCompra(ListaCompra* li, Compra compra, int isFromSystem) {
	if(li == NULL) return 0;

    ElementoCompra *no;
    no = (ElementoCompra*) malloc(sizeof(ElementoCompra));
    if(no == NULL) return 0;
    
    no->compra = compra;
    no->prox = NULL;
    
    if((*li) == NULL){
        *li = no;
    }else{
        ElementoCompra *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    
    if (isFromSystem == 0) {
    	if (salvarCompras(li) == 0) return 0;
    
	    nextBuyID++;
	    if (changeIDInFile(&FILE_ID_COMPRA, nextBuyID) == 0) return 0;
	}
  	
    return 1;
}

int insereItemsCompra(ListaItemsCompra* li, ItemsCompra itemCompra, int isFromSystem) {
	if(li == NULL) return 0;
	
    ElementoItemsCompra *no;
    no = (ElementoItemsCompra*) malloc(sizeof(ElementoItemsCompra));
    if(no == NULL) return 0;
    
    no->itemsCompra = itemCompra;
    no->prox = NULL;
    
    if((*li) == NULL){
        *li = no;
    }else{
        ElementoItemsCompra *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    
    if (isFromSystem == 0)    
    	if (salvarItemsCompras(li) == 0) return 0;
    
    return 1;
}

int removeContaLogin(ListaContasLogin* li, int id) {
    if(li == NULL || (*li) == NULL) return 0;
        
    ElementoContasLogin *ant, *no = *li;
    
    while(no != NULL && no->contaLogin.id != id) {
        ant = no;
        no = no->prox;
    }
    
    if(no == NULL) return 0;

    if(no == *li) *li = no->prox;
    else ant->prox = no->prox;
    
    free(no);
    
    if (salvarContasLogin(li) == 0) return 0;
    
    return 1;
}

int removeCliente(ListaCliente* li, int numCliente) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCliente *ant, *no = *li;
	
	while(no != NULL && no->cliente.numCliente != numCliente) {
		ant = no;
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	
	if (no == *li) *li = no->prox;
	else ant->prox = no->prox;
	
	free(no);
	
	if (salvarClientes(li) == 0) return 0;
	
	return 1; 
}

int removeGestor(ListaGestor* li, int codGestor) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoGestor *ant, *no = *li;
	
	while(no != NULL && no->gestor.codGestor != codGestor) {
		ant = no;
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	
	if (no == *li) *li = no->prox;
	else ant->prox = no->prox;
	
	free(no);
	
	if (salvarGestores(li) == 0) return 0;
	
	return 1;
}

int removeProduto(ListaProduto* li, int codProduto) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoProduto *ant, *no = *li;
	
	while(no != NULL && no->produto.codProduto != codProduto) {
		ant = no;
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	
	if (no == *li) *li = no->prox;
	else ant->prox = no->prox;
	
	free(no);
	
	if (salvarProdutos(li) == 0) return 0;
	
	return 1;
}

int removeStock(ListaStock* li, int id) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoStock *ant, *no = *li;
	
	while(no != NULL && no->stock.id != id) {
		ant = no;
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	
	if (no == *li) *li = no->prox;
	else ant->prox = no->prox;
	
	free(no);
	
	if (salvarStock(li) == 0) return 0;
	
	return 1;
}

int removeStockProduto(ListaStock* li, int idProduto) {
	int found = 0;
	
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoStock *ant, *no = *li;
	
	while(no != NULL && no->stock.productID != idProduto || found == 1) {
		ant = no;
		no = no->prox;
		found = 1;
	}
	
	if (no == NULL) return 0;
	
	if (no == *li) *li = no->prox;
	else ant->prox = no->prox;
	
	free(no);
	
	if (salvarStock(li) == 0) return 0;
	
	return 1;
}

int removeCarrinhoCompras(ListaCarrinhoCompras* li, int idProduto) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCarrinhoCompras *ant, *no = *li;
	
	while(no != NULL && no->carrinhoCompras.idProduto != idProduto) {
		ant = no;
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	
	if (no == *li) *li = no->prox;
	else ant->prox = no->prox;
	
	free(no);
	
	return 1;
}

int removeCompra(ListaCompra* li, int id) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCompra *ant, *no = *li;
	
	while(no != NULL && no->compra.id != id) {
		ant = no;
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	
	if (no == *li) *li = no->prox;
	else ant->prox = no->prox;
	
	free(no);
	
	if (salvarCompras(li) == 0) return 0;
	
	return 1;
}

int removeItemsCompra(ListaItemsCompra* li, int idCompra) {
	int found = 0;
	
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCompra *ant, *no = *li;
	
	while(no != NULL && no->compra.id != idCompra || found == 1) {
		ant = no;
		no = no->prox;
		found = 1;
	}
	
	if (no == NULL) return 0;
	
	if (no == *li) *li = no->prox;
	else ant->prox = no->prox;
	
	free(no);
	
	if (salvarItemsCompras(li) == 0) return 0;
	
	return 1;
}

Data dataAtual() {
	time_t t = time(NULL);
    struct tm tm = *localtime(&t);
  	
    Data date;
    date.ano = tm.tm_year + 1900;
    date.mes = tm.tm_mon + 1;
    date.dia = tm.tm_mday;

    return date;
}

int dentroDaValidade(Data dataValidade) {
	int valido = 0;
	Data date = dataAtual();
	
	if (dataValidade.ano > date.ano) {
        valido = 1;
    } else if (dataValidade.ano == date.ano) {
        if (dataValidade.mes > date.mes) {
            valido = 1;
        } else if (dataValidade.mes == date.mes && dataValidade.dia >= date.dia) {
            valido = 1;
        }
    }
    
    return valido;
}

int verificarStockProduto(ListaStock* li, int idProduto) {
	int stock = 0;
	
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoStock* no = *li;
	
	while (no != NULL) {
		if (no->stock.productID == idProduto) {
			if (dentroDaValidade(no->stock.validade)) stock += no->stock.quantidadeStock;
			else removeStock(li, no->stock.id);
		}
		
		no = no->prox;
	}
	
	return stock;
}

int imprimeClientes(ListaCliente* li) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCliente* no = *li;
	char cartaoCreditoEscondido[21];
	
	while (no != NULL) {
		printf("Nº de cliente: %d\n", no->cliente.numCliente);
		printf("Nome: %s\n", no->cliente.nome);
		printf("Morada: %s\n", no->cliente.morada);
		printf("Nº de contribuinte: %d\n", no->cliente.nContribuinte);
		strcpy(cartaoCreditoEscondido, esconderCartaoCredito(no->cliente.nCartaoCredito));
		printf("Nº do cartão: %s\n", cartaoCreditoEscondido);
		printf("----------------------------\n\n");
		
		no = no->prox;
	}
	
	return 1;
}

int imprimeGestores(ListaGestor* li) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoGestor* no = *li;
	
	while (no != NULL) {
		printf("Código de gestor: %d\n", no->gestor.codGestor);
		printf("Nome: %s\n", no->gestor.nome);
		printf("----------------------------\n\n");
		
		no = no->prox;
	}
	
	return 1;
}

int imprimeProdutos(ListaProduto* li) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoProduto* no = *li;
	
	while (no != NULL) {
		printf("Código do produto: %d\n", no->produto.codProduto);
		printf("Nome: %s\n", no->produto.nome);
		printf("Preço: %f\n", no->produto.preco);
		printf("Stock do produto: %d\n", verificarStockProduto(listaStock, no->produto.codProduto));
		printf("----------------------------\n\n");
		
		no = no->prox;
	}
	
	return 1;
}

int imprimeStocksProduto(ListaStock* li, int idProduto) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoStock *no = *li;
	Data data;
	int contador = 0;
	
	while (no != NULL) {
		if (no->stock.productID == idProduto) {
			data = no->stock.validade;
		
			printf("Id do stock: %d\n", no->stock.id);
			printf("Data de validade: %d/%d/%d", data.dia, data.mes, data.ano);
			printf("Quantidade: %d", no->stock.quantidadeStock);
			printf("----------------------------\n\n");
			
			contador++;
		}
		
		no = no->prox;
	}
	
	return contador;
}

int imprimeCarrinhoCompras(ListaCarrinhoCompras* li) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCarrinhoCompras *no = *li;
	Produto produto;
	float precoTotal = 0;
	
	while (no != NULL) {
		int productExist = consultaProduto(listaProduto, no->carrinhoCompras.idProduto, &produto);
		
		printf("Id do produto: %d\n", no->carrinhoCompras.idProduto);
		printf("Nome do produto: %s\n", productExist == 0 ? "Produto não existe" : produto.nome);
		printf("Quantidade: %d\n", no->carrinhoCompras.quantidade);
		printf("----------------------------\n\n");
		
		if (productExist == 0) removeCarrinhoCompras(li, no->carrinhoCompras.idProduto);
		else precoTotal += no->carrinhoCompras.quantidade * produto.preco;
		
		no = no->prox;
	}
	
	printf("Preço final da compra: %.2f\n\n", precoTotal);
	
	return 1;
}

int imprimeCompras(ListaCompra* li) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCompra *no = *li;
	Cliente cliente;
	Data data;
	
	while (no != NULL) {
		int clienteExist = consultaCliente(listaClientes, no->compra.idCliente, &cliente);
		data = no->compra.dataCompra;
		
		printf("Id da compra: %d\n", no->compra.id);
		printf("Nome do cliente: %s\n", clienteExist == 0 ? "Cliente não encontrado" : cliente.nome);
		printf("Data: %d/%d/%d ", data.dia, data.mes, data.ano);
		printf(" Preço: %.2f ", no->compra.precoTotal);
		printf(" Produtos da compra: \n");
		if (imprimeItemsCompra(listaItemsCompra, no->compra.id) == 0)
			printf("Não foi possível encontrar os produtos desta compra.\n"),
		printf("----------------------------\n\n");
		
		no = no->prox;
	}
	
	return 1;	
}

int imprimeComprasCliente(ListaCompra* li, int idCliente) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCompra *no = *li;
	Data data;
	int contador = 0;
	
	while (no != NULL) {
		if (no->compra.idCliente == idCliente) {
			data = no->compra.dataCompra;
		
			printf("Id da compra: %d\n", no->compra.id);
			printf("Data: %d/%d/%d", data.dia, data.mes, data.ano);
			printf("Preço: %.2f", no->compra.precoTotal);
			printf("Produtos da compra: \n");
			if (imprimeItemsCompra(listaItemsCompra, no->compra.id) == 0)
				printf("Não foi possível encontrar os produtos desta compra.\n"),
			printf("----------------------------\n\n");
			
			contador++;
		}
		
		no = no->prox;
	}
	
	return contador;
}

int imprimeItemsCompra(ListaItemsCompra* li, int idCompra) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoItemsCompra *no = *li;
	Produto produto;
	int contador = 0;
	
	while (no != NULL) {
		if (no->itemsCompra.idCompra == idCompra) {
			int productExist = consultaProduto(listaProduto, no->itemsCompra.idProduto, &produto);
			
			printf("\tId do Produto: %d\n", no->itemsCompra.idProduto);
			printf("\tNome do Produto: %s\n", productExist == 0 ? "Produto não encontrado" : produto.nome);
			printf("\tQuantidade: %d\n", no->itemsCompra.quantidade);
			printf("\t----------------------------\n");
		}
		
		no = no->prox;
	}
	
	return contador;
}

int consultaContaLoginByID(ListaContasLogin* li, int id, ContasLogin *contaLogin) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoContasLogin *no = *li;
	
	while (no != NULL && no->contaLogin.id != id) {
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	else {
		*contaLogin = no->contaLogin;
		return 1;
	}
}

int consultaContaLoginByUsername(ListaContasLogin* li, char *username, ContasLogin *contaLogin) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoContasLogin *no = *li;
	
	while (no != NULL && strcmp(username, no->contaLogin.username) != 0) {
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	else {
		*contaLogin = no->contaLogin;
		return 1;
	}
}

int consultaContaLoginByIDTipo(ListaContasLogin* li, int tipoConta, int idTipo, ContasLogin *contaLogin) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoContasLogin *no = *li;
	
	while (no != NULL && no->contaLogin.tipoConta == tipoConta && no->contaLogin.idTipo == idTipo) {
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	else {
		*contaLogin = no->contaLogin;
		return 1;
	}
}

int consultaCliente(ListaCliente* li, int numCliente, Cliente *cliente) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCliente *no = *li;
	
	while (no != NULL && no->cliente.numCliente != numCliente) {
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	else {
		*cliente = no->cliente;
		return 1;
	}
}

int consultaGestor(ListaGestor* li, int codGestor, Gestor *gestor) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoGestor *no = *li;
	
	while (no != NULL && no->gestor.codGestor != codGestor) {
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	else {
		*gestor = no->gestor;
		return 1;
	}
}

int consultaProduto(ListaProduto* li, int codProduto, Produto *produto) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoProduto *no = *li;
	
	while (no != NULL && no->produto.codProduto != codProduto) {
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	else {
		*produto = no->produto;
		return 1;
	}
}

int consultaStock(ListaStock* li, int id, Stock *stock) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoStock *no = *li;
	
	while (no != NULL && no->stock.id != id) {
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	else {
		*stock = no->stock;
		return 1;
	}
}

int consultaStockProduto(ListaStock* li, int idProduto, Stock *stock) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoStock *no = *li;
	
	while (no != NULL && no->stock.productID != idProduto) {
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	else {
		*stock = no->stock;
		return 1;
	}
}

int consultaCarrinhoCompras(ListaCarrinhoCompras* li, int idProduto, CarrinhoCompras *carrinhoCompra) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCarrinhoCompras *no = *li;
	
	while (no != NULL && no->carrinhoCompras.idProduto != idProduto) {
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	else {
		*carrinhoCompra = no->carrinhoCompras;
		return 1;
	}
}

int consultaCompra(ListaCompra* li, int id, Compra *compra) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCompra *no = *li;
	
	while (no != NULL && no->compra.id != id) {
		no = no->prox;
	}
	
	if (no == NULL) return 0;
	else {
		*compra = no->compra;
		return 1;
	}
}

int carregarContasLogin() {
	FILE *fp;
	ContasLogin contaLoginTemp;
	int statusCode = 1;
	
	fp = fopen(FILE_ACCOUNT, "rb");
	if (fp == NULL) return 0;
	
	while (fread(&contaLoginTemp, sizeof(ContasLogin), 1, fp) || statusCode != 1) {
		statusCode = insereContaLogin(listaContasLogin, contaLoginTemp, 1);
	}
	
	fclose(fp);
	
	return statusCode;
}

int carregarClientes() {
	FILE *fp;
	Cliente clienteTemp;
	int statusCode = 1;
	
	fp = fopen(FILE_CLIENTES, "rb");
	if (fp == NULL) return 0;
	
	while (fread(&clienteTemp, sizeof(Cliente), 1, fp) || statusCode != 1) {
		statusCode = insereCliente(listaClientes, clienteTemp, 1);
	}
	
	fclose(fp);
	
	return statusCode;
}

int carregarGestores() {
	FILE *fp;
	Gestor gestorTemp;
	int statusCode = 1;
	
	fp = fopen(FILE_GESTORES, "rb");
	if (fp == NULL) return 0;
	
	while (fread(&gestorTemp, sizeof(Gestor), 1, fp) || statusCode != 1) {
		statusCode = insereGestor(listaGestor, gestorTemp, 1);
	}
	
	fclose(fp);
	
	return statusCode;
}

int carregarProdutos() {
	FILE *fp;
	Produto produtoTemp;
	int statusCode = 1;
	
	fp = fopen(FILE_PRODUCTS, "rb");
	if (fp == NULL) return 0;
	
	while (fread(&produtoTemp, sizeof(Produto), 1, fp) || statusCode != 1) {
		statusCode = insereProduto(listaProduto, produtoTemp, 1);
	}
	
	fclose(fp);
	
	return statusCode;
}

int carregarStock() {
	FILE *fp;
	Stock stockTemp;
	int statusCode = 1;
	
	fp = fopen(FILE_STOCKS, "rb");
	if (fp == NULL) return 0;
	
	while (fread(&stockTemp, sizeof(Stock), 1, fp) || statusCode != 1) {
		statusCode = insereStock(listaStock, stockTemp, 1);
	}
	
	fclose(fp);
	
	return statusCode;
}

int carregarCompras() {
	FILE *fp;
	Compra compraTemp;
	int statusCode = 1;
	
	fp = fopen(FILE_COMPRAS, "rb");
	if (fp == NULL) return 0;
	
	while (fread(&compraTemp, sizeof(Compra), 1, fp) || statusCode != 1) {
		statusCode = insereCompra(listaCompra, compraTemp, 1);
	}
	
	fclose(fp);
	
	return statusCode;
}

int carregarItemsCompras() {
	FILE *fp;
	ItemsCompra itemCompraTemp;
	int statusCode = 1;
	
	fp = fopen(FILE_ITEMS_COMPRAS, "rb");
	if (fp == NULL) return 0;
	
	while (fread(&itemCompraTemp, sizeof(ItemsCompra), 1, fp) || statusCode != 1) {
		statusCode = insereItemsCompra(listaItemsCompra, itemCompraTemp, 1);
	}
	
	fclose(fp);
	
	return statusCode;
}

int salvarContasLogin(ListaContasLogin* li) {
	if (li == NULL) return 0;
	
	FILE *fp;
	ElementoContasLogin *no = *li;
	ContasLogin contasLoginTemp;
	
	fp = fopen(FILE_ACCOUNT, "wb");
	if (fp == NULL) return 0;
	
	while (no != NULL) {
		contasLoginTemp = no->contaLogin;
		
		fwrite(&contasLoginTemp, sizeof(ContasLogin), 1, fp);
		
		no = no->prox;
	}
	
	fclose(fp);
	
	return fwrite == 0 ? 0 : 1;
}

int salvarClientes(ListaCliente* li) {
	if (li == NULL) return 0;
	
	FILE *fp;
	ElementoCliente *no = *li;
	Cliente clienteTemp;
	
	fp = fopen(FILE_CLIENTES, "wb");
	if (fp == NULL) return 0;
	
	while (no != NULL) {
		clienteTemp = no->cliente;
		
		fwrite(&clienteTemp, sizeof(Cliente), 1, fp);
		
		no = no->prox;
	}
	
	fclose(fp);
	
	return fwrite == 0 ? 0 : 1;
}

int salvarGestores(ListaGestor* li) {
	if (li == NULL) return 0;
	
	FILE *fp;
	ElementoGestor *no = *li;
	Gestor gestorTemp;
	
	fp = fopen(FILE_GESTORES, "wb");
	if (fp == NULL) return 0;
	
	while (no != NULL) {
		gestorTemp = no->gestor;
		
		fwrite(&gestorTemp, sizeof(Gestor), 1, fp);
		
		no = no->prox;
	}
	
	fclose(fp);
	
	return fwrite == 0 ? 0 : 1;
}

int salvarProdutos(ListaProduto* li) {
	if (li == NULL) return 0;
	
	FILE *fp;
	ElementoProduto *no = *li;
	Produto produtoTemp;
	
	fp = fopen(FILE_PRODUCTS, "wb");
	if (fp == NULL) return 0;
	
	while (no != NULL) {
		produtoTemp = no->produto;
		
		fwrite(&produtoTemp, sizeof(Produto), 1, fp);
		
		no = no->prox;
	}
	
	fclose(fp);
	
	return fwrite == 0 ? 0 : 1;
}

int salvarStock(ListaStock* li) {
	if (li == NULL) return 0;
	
	FILE *fp;
	ElementoStock *no = *li;
	Stock stockTemp;
	
	fp = fopen(FILE_STOCKS, "wb");
	if (fp == NULL) return 0;
	
	while (no != NULL) {
		stockTemp = no->stock;
		
		fwrite(&stockTemp, sizeof(Stock), 1, fp);
		
		no = no->prox;
	}
	
	fclose(fp);
	
	return fwrite == 0 ? 0 : 1;
}

int salvarCompras(ListaCompra* li) {
	if (li == NULL) return 0;
	
	FILE *fp;
	ElementoCompra *no = *li;
	Compra compraTemp;
	
	fp = fopen(FILE_COMPRAS, "wb");
	if (fp == NULL) return 0;
	
	while (no != NULL) {
		compraTemp = no->compra;
		
		fwrite(&compraTemp, sizeof(Compra), 1, fp);
		
		no = no->prox;
	}
	
	fclose(fp);
	
	return fwrite == 0 ? 0 : 1;
}

int salvarItemsCompras(ListaItemsCompra* li) {
	if (li == NULL) return 0;
	
	FILE *fp;
	ElementoItemsCompra *no = *li;
	ItemsCompra itemCompraTemp;
	
	fp = fopen(FILE_ITEMS_COMPRAS, "wb");
	if (fp == NULL) return 0;
	
	while (no != NULL) {
		itemCompraTemp = no->itemsCompra;
		
		fwrite(&itemCompraTemp, sizeof(ItemsCompra), 1, fp);
		
		no = no->prox;
	}
	
	fclose(fp);
	
	return fwrite == 0 ? 0 : 1;
}

int alterarContaLogin(ListaContasLogin* li, ContasLogin contaLogin) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoContasLogin *no = *li;
	int alterado = 0;
	
	while (no != NULL) {
		if (no->contaLogin.id == contaLogin.id) {
			no->contaLogin = contaLogin;
			
			alterado = 1;
		}		
		
		no = no->prox;
	}
	
	if (alterado == 1) {
		if (salvarContasLogin(li) == 0) return 0;
	}
	
	return alterado;
}

int alterarCliente(ListaCliente* li, Cliente cliente) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCliente *no = *li;
	int alterado = 0;
	
	while (no != NULL) {
		if (no->cliente.numCliente == cliente.numCliente) {
			no->cliente = cliente;
			
			alterado = 1;
		}
		
		no = no->prox;
	}
	
	if (alterado == 1) {
		if (salvarClientes(li) == 0) return 0;
	}
	
	return alterado;
}

int alterarGestor(ListaGestor* li, Gestor gestor) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoGestor *no = *li;
	int alterado = 0;
	
	while (no != NULL) {
		if (no->gestor.codGestor == gestor.codGestor) {
			no->gestor = gestor;
			
			alterado = 1;
		}
		
		no = no->prox;
	}
	
	if (alterado == 1) {
		if (salvarGestores(li) == 0) return 0;
	}
	
	return alterado;
}

int alterarProduto(ListaProduto* li, Produto produto) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoProduto *no = *li;
	int alterado = 0;
	
	while (no != NULL) {
		if (no->produto.codProduto == produto.codProduto) {
			no->produto = produto;
			
			alterado = 1;
		}
		
		no = no->prox;
	}
	
	if (alterado == 1) {
		if (salvarProdutos(li) == 0) return 0;
	}
	
	return alterado;
}

int alterarStock(ListaStock* li, Stock stock) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoStock *no = *li;
	int alterado = 0;
	
	while (no != NULL) {
		if (no->stock.id == stock.id) {
			no->stock = stock;
			
			alterado = 1;
		}
		
		no = no->prox;
	}
	
	if (alterado == 1) {
		if (salvarStock(li) == 0) return 0;
	}
	
	else return alterado;
}

int alterarCarrinhoCompras(ListaCarrinhoCompras* li, CarrinhoCompras carrinhoCompras) {
	if (li == NULL || (*li) == NULL) return 0;
	
	ElementoCarrinhoCompras *no = *li;
	int alterado = 0;
	
	while (no != NULL) {
		if (no->carrinhoCompras.idProduto == carrinhoCompras.idProduto) {
			no->carrinhoCompras = carrinhoCompras;
			
			alterado = 1;
		}
		
		no = no->prox;
	}
	
	return alterado;
}

void menuLogin() {
	int opcao;
	
	do {
		printf("Menu Admin: \n");
		printf("1 - Login;\n");
		printf("2 - Criar conta cliente;\n");
		printf("0 - Sair;\n");
		printf("Escolha uma opção: ");
		lerInteiro(&opcao);
		
		switch (opcao) {
			case 1:
				login();
				break;
			case 2:
				if (criarContaCliente(0)) printf("Conta criada com sucesso.\n\n");
				else printf("Ocorreu um erro ao criar a conta.\n\n");
				break;
			case 0:
				endProgram();
				break;
			default:
				printf("Opção inválida!! Tente novamente.\n\n");
				break;
		}
	} while (opcao != 0);
}

void login() {
	char username[30], password[30], opcao;
	
	printf("Introduza o username da conta: ");
	gets(username); fflush(stdin);
	printf("Introduza a password da conta: ");
	strcpy(password, lerPassowrd()); fflush(stdin);
	printf("\n");
	
	if (consultaContaLoginByUsername(listaContasLogin, username, &contaLogin)) {
		if (strcmp(password, contaLogin.password) != 0 ) {
			printf("Falha ao entrar.\nPretende tentar novamente?[s/S]: ");
			scanf(" %c", &opcao); getchar(); fflush(stdin);
			
			if (opcao == 's' || opcao == 'S') login();
		} else {
			if (contaLogin.createdByAdmin == 1) {
				printf("Como a sua conta foi criada por um Administrador tens de alterar a password.\n");
				alterarPassword();
			}
			
			if (contaLogin.tipoConta == 1) {
				if (consultaCliente(listaClientes, contaLogin.idTipo, &cliente)) {
					printf("Bem-Vindo(a) de volta %s.\n\n", cliente.nome);
					menuCliente();
				} else {
					printf("Impossível realizar o login, tente novamente mais tarde.\n\n");
				}
			} else {
				if (consultaGestor(listaGestor, contaLogin.idTipo, &gestor)) {
					printf("Bem-Vindo(a) de volta %s.\n\n", gestor.nome);
					menuGestor();
				} else {
					printf("Impossível realizar o login, tente novamente mais tarde.\n\n");
				}
			}
		}
	} else {
		printf("Falha ao entrar.\nPretende tentar novamente?[s/S]: ");
		scanf(" %c", &opcao); getchar(); fflush(stdin);
			
		if (opcao == 's' || opcao == 'S') login();
	}
}

int criarContaCliente(int createdByAdmin) {
	Cliente clienteTemp;
	ContasLogin contaLoginTemp, contaLoginProcura;
	
	printf("Criar conta do cliente: \n");
	
	// Dados do cliente
	clienteTemp.numCliente = nextClientID;
	printf("Introduza o nome: ");
	gets(clienteTemp.nome); fflush(stdin);
	printf("Introduza a morada: ");
	gets(clienteTemp.morada); fflush(stdin);
	printf("Introduza o número de contribuinte: ");
	lerInteiro(&clienteTemp.nContribuinte);
	while (clienteTemp.nContribuinte < 100000000 || clienteTemp.nContribuinte > 999999999) {
		printf("Número de contribuinte inválido. Deve estar entre 100000000 e 999999999.\n");
		printf("Introduza o número de contribuinte: ");
		lerInteiro(&clienteTemp.nContribuinte);
	}
	printf("Introduza o númerodo cartão de crédito: ");
	gets(clienteTemp.nCartaoCredito); fflush(stdin);
	while (verificarNumeroCartao(clienteTemp.nCartaoCredito) == 0) {
		printf("Introduza o númerodo cartão de crédito");
		gets(clienteTemp.nCartaoCredito); fflush(stdin);
	}
	
	// Dados de login
	contaLoginTemp.id = nextAccountID;
	contaLoginTemp.createdByAdmin = createdByAdmin;
	contaLoginTemp.tipoConta = 1;
	contaLoginTemp.idTipo = clienteTemp.numCliente;
	printf("Introduza o username da conta: ");
	gets(contaLoginTemp.username); fflush(stdin);
	while (consultaContaLoginByUsername(listaContasLogin, contaLoginTemp.username, &contaLoginProcura) != 0) {
		printf("Username ja está em uso, escolha outro.\n");
		printf("Introduza o username da conta ");
		gets(contaLoginTemp.username); fflush(stdin);
	}
	printf("Introduza a password da conta: ");
	strcpy(contaLoginTemp.password, lerPassowrd()); fflush(stdin);
	printf("\n");
	
	if (insereCliente(listaClientes, clienteTemp, 0) == 0) return 0;
	
	if (insereContaLogin(listaContasLogin, contaLoginTemp, 0) == 0) return 0;
	
	return 1;
}

void alterarPassword() {
	char opcao;
	
	printf("Introduza a nova password: ");
	strcpy(contaLogin.password, lerPassowrd()); fflush(stdin);
	printf("\n");
	if (contaLogin.createdByAdmin == 0) {
		printf("Tem a certeza que pretende alterar a password?[s/S]: ");
		scanf(" %c", &opcao); getchar(); fflush(stdin);
	}
	
	if (contaLogin.createdByAdmin == 1 || opcao == 's' || opcao == 'S') {
		contaLogin.createdByAdmin = 0;
		
		if (alterarContaLogin(listaContasLogin, contaLogin) == 0) {
			printf("Ocorreu algum erro ao tentar alterar a password.\n\n");
		} else {
			printf("Password alterada com sucesso.\n\n");
		}
	} else {
		printf("Password não alterada.\n\n");
	}
}

void menuCliente() {
	int opcao, idProduto;
	char numCartaoCreditoEscondido[21], opcaoChar;
	Produto produto;
	
	do {
		printf("Menu Cliente:\n");
		printf("1 - Consultar os meus dados;\n");
		printf("2 - Alterar os meus dados;\n");
		printf("3 - Visualizar catálogo;\n");
		printf("4 - Consultar produto;\n");
		printf("5 - Visualizar carrinho;\n");
		printf("6 - Adicionar produto;\n");
		printf("7 - Alterar quantidade de produtos;\n");
		printf("8 - Remover produto do carrinho;\n");
		printf("9 - Efetuar compra;\n");
		printf("10 - Esvaziar carrinho;\n");
		printf("11 - Histórico de compras;\n");
		printf("12 - Eliminar conta;\n");
		printf("0 - Logout;\n");
		printf("Escolha uma opção: ");
		lerInteiro(&opcao);
		
		switch (opcao) {
			case 1:
				printf("\nDados Pessoais: \n");
				printf("Nº de cliente: %d\n", cliente.numCliente);
				printf("Nome: %s\n", cliente.nome);
				printf("Morada: %s\n", cliente.morada);
				printf("Nº de contribuinte: %d\n", cliente.nContribuinte);
				strcpy(numCartaoCreditoEscondido, esconderCartaoCredito(cliente.nCartaoCredito));
				printf("Nº do cartão: %s\n\n", numCartaoCreditoEscondido);
				break;
			case 2:
				alterarDadosCliente();
				break;
			case 3:
				printf("\nProdutos existentes na loja: \n");
				if (imprimeProdutos(listaProduto) == 0) {
					printf("Não foi possível listar os produtos, ou não existe nenhum produto no sistema.\n\n");
				}
				break;
			case 4:
				printf("\nIntroduza o Id do produto a consultar: ");
				lerInteiro(&idProduto);
				if (consultaProduto(listaProduto, idProduto, &produto) == 0) {
					printf("Não existe nenhum produto com esse id.\n\n");
				} else {
					printf("Código do produto: %d\n", produto.codProduto);
					printf("Nome: %s\n", produto.nome);
					printf("Preço: %.2f\n", produto.preco);
					printf("Stock produto: %d\n\n", verificarStockProduto(listaProduto, idProduto));
				}
				break;
			case 5:
				printf("\nItems do carrinho de compras: \n");
				if (imprimeCarrinhoCompras(listaCarrinhoCompras) == 0) {
					printf("Não foi possível listar o carrinho de compras, pois está vazio.\n\n");
				}
				break;
			case 6:
				comprarProduto();
				break;
			case 7:
				alterarQuantidadeProdutoCarrinho();
				break;
			case 8:
				removerProdutoCarrinho();
				break;
			case 9:
				finalizarCompra();
				break;
			case 10:
				libertaListaCarrinhoCompras(listaCarrinhoCompras);
				listaCarrinhoCompras = criaListaCarrinhoCompras();
				if (listaCarrinhoCompras == NULL) {
					printf("Ocorreu algum erro ao limpar o carrinho de compras.\n\n");
				} else {
					printf("Carrinho de compras limpo com sucesso.\n\n");
				}
				break;
			case 11:
				printf("\nHistório de Compras: \n");
				if (imprimeComprasCliente(listaCompra, cliente.numCliente) == 0) {
					printf("Ocorreu algum erro a listar as suas compras, pois ainda não foi realizada nenhuma.\n\n");
				}
				break;
			case 12:
				printf("Pretende mesmo remover a sua conta?[s/S]: ");
				scanf(" %c", &opcaoChar);
				if (opcao == 's' || opcao == 'S') {
					if (removeContaLogin(listaContasLogin, contaLogin.id)) {
						removeCliente(listaClientes, cliente.numCliente);
						printf("Conta removida com sucesso.\n\n");
						opcao = 0;
					} else {
						printf("Ocorreu algum erro ao tentar remover a sua conta.\n\n");
					}
				} else {
					printf("Remoção da conta cancelada.\n\n");
				}
				break;
			case 0:
				printf("\nA sair da conta...\n\n");
				if ((*listaCarrinhoCompras) != NULL) {
					libertaListaCarrinhoCompras(listaCarrinhoCompras);
					listaCarrinhoCompras = criaListaCarrinhoCompras();
				}
				break;
			default: 
				printf("Opção inválida!! Tente novamente.\n\n");
				break;
		}
	} while (opcao != 0);
}

void menuGestor() {
	int opcao, idCliente, idGestor, idProduto, idStock, idCompra;
	char numCartaoCreditoEscondido[21], opcaoChar;
	Cliente clienteTemp;
	Gestor gestorTemp;
	Produto produtoTemp;
	Stock stockTemp;
	Compra compraTemp;
	
	do {
		printf("Menu gestor:\n");
		printf("1 - Consultar os meus dados;\n");
		printf("2 - Alterar os meus dados;\n");
		printf("3 - Consultar clientes;\n");
		printf("4 - Procurar cliente;\n");
		printf("5 - Inserir cliente;\n");
		printf("6 - Eliminar cliente;\n");
		printf("7 - Consultar gestores;\n");
		printf("8 - Procurar gestor;\n");
		printf("9 - Inserir gestor;\n");
		printf("10 - Eliminar gestor;\n");
		printf("11 - Consultar produtos;\n");
		printf("12 - Procurar produto;\n");
		printf("13 - Inserir produto;\n");
		printf("14 - Remover produto;\n");
		printf("15 - Inserir stock;\n");
		printf("16 - Consultar stock produto;\n");
		printf("17 - Remover stock;\n");
		printf("18 - Consultar compras;\n");
		printf("19 - Procurar compra;\n");
		printf("20 - Eliminar conta;\n");
		printf("0 - Logout;\n");
		printf("Escolha uma opção: ");
		lerInteiro(&opcao);
		
		switch (opcao) {
			case 1:
				printf("\nDados Pessoais: \n");
				printf("Código de gestor: %d\n", gestor.codGestor);
				printf("Nome: %s\n\n", gestor.nome);
				break;
			case 2:
				alterarDadosGestor();
				break;
			case 3:
				printf("\nDados dos Clientes: \n");
				if (imprimeClientes(listaClientes) == 0) {
					printf("Ocorreu algum erro ao imprimir os clientes, pois não existe nenhum no sistema.\n\n");
				}
				break;
			case 4:
				printf("\nIntroduza o Id do cliente a procurar: ");
				lerInteiro(&idCliente);
				if (consultaCliente(listaClientes, idCliente, &clienteTemp)) {
					printf("Dados do cliente encontrado:\n");
					printf("Nº de cliente: %d\n", clienteTemp.numCliente);
					printf("Nome: %s\n", clienteTemp.nome);
					printf("Morada: %s\n", clienteTemp.morada);
					printf("Nº de contribuinte: %d\n", clienteTemp.nContribuinte);
					strcpy(numCartaoCreditoEscondido, esconderCartaoCredito(clienteTemp.nCartaoCredito));
					printf("Nº do cartão: %s\n\n", numCartaoCreditoEscondido);
				} else {
					printf("Não foi possível encontrar nenhum cliente com esse id.\n\n");
				}
				break;
			case 5:
				criarContaCliente(1);
				break;
			case 6:
				removerCliente();
				break;
			case 7:
				printf("\nDados dos gestores: \n");
				if (imprimeGestores(listaGestor) == 0) {
					printf("Ocorreu algum erro ao imprimir os gestores, pois não existe nenhum no sistema.\n\n");
				}
				break;
			case 8:
				printf("\nIntroduza o Id do gestor a procurar: ");
                lerInteiro(&idGestor);
                if (consultaGestor(listaGestor, idGestor, &gestorTemp)) {
                    printf("Dados do gestor encontrado:\n");
                    printf("Nº de gestor: %d\n", gestorTemp.codGestor);
                    printf("Nome: %s\n\n", gestorTemp.nome);
                } else {
                    printf("Não existe nenhum gestor com esse id.\n\n");
                }
                break;
            case 9:
            	if (strcmp("admin", contaLogin.username) == 0) {
            		criarGestor();
				} else {
					printf("Sem permissões para adicionar gestores.\n\n");
				}
				break;
			case 10:
				if (strcmp("admin", contaLogin.username) == 0) {
            		removerGestor();
				} else {
					printf("Sem permissões para remover gestores.\n\n");
				}
				break;
			case 11:
				printf("\nDados dos produtos: \n");
				if (imprimeProdutos(listaProduto) == 0) {
					printf("Ocorreu algum erro ao imprimir os produtos, pois não existe nenhum produto no sistema.\n\n");
				}
				break;
			case 12:
				printf("Introduza o Id do produto a consultar: ");
				lerInteiro(&idProduto);
				
				if (consultaProduto(listaProduto, idProduto, &produtoTemp)) {
					printf("Dados do produto encontrado:\n");
					printf("Código do produto: %d\n", produtoTemp.codProduto);
					printf("Nome: %s\n", produtoTemp.nome);
					printf("Preco: %.2f\n", produtoTemp.preco);
					printf("Stock produto: %d\n\n", verificarStockProduto(listaStock, idProduto));
				} else {
					printf("Não existe nenhum produto com esse id.\n\n");
				}
				break;
			case 13:
				adicionarProduto();
				break;
			case 14:
				removerProduto();
				break;
			case 15:
				adicionarStock();
				break;
			case 16:
				printf("Introduza o Id do produto a consultar o stock: ");
				lerInteiro(&idProduto);
				if (consultaProduto(listaProduto, idProduto, &produtoTemp)) {
					int stockProduto = verificarStockProduto(listaStock, idProduto);
					
					printf("O produto %s tem %d stock.\n", produtoTemp.nome, stockProduto);
					
					if (stockProduto > 0) {
						printf("Pretende ver todos os dados do stock deste produto?[s/S]: ");
						scanf(" %c", &opcaoChar); fflush(stdin);
						if (opcaoChar == 's' || opcaoChar == 'S') {
							printf("Dados do stock do produto %s:\n", produtoTemp.nome);
							if (imprimeStocksProduto(listaStock, idProduto) == 0) {
								printf("Ocorreu algum erro ao imprimir os dados do stock do produto.\n\n");
							}
						}
					}
				} else {
					printf("Não existe nenhum produto com esse id.\n\n");
				}
				break;
			case 17:
				printf("Introduza o Id do stock a remover: ");
				lerInteiro(&idStock);
				if (consultaStock(listaStock, idStock, &stockTemp)) {
					printf("Pretende mesmo remover o stock com o id %d ?[s/S]: ");
					scanf(" %c", &opcaoChar); fflush(stdin);
					if (opcaoChar == 's' || opcaoChar == 'S') {
						if (removeStock(listaStock, idStock)) {
							printf("Stock removido com sucesso.\n\n");
						} else {
							printf("Ocorreu algum erro ao remover o stock.\n\n");
						}
					} else {
						printf("Remoção do stock cancelada.\n\n");
					}
				} else {
					printf("Não existe nenhum stock com esse id.\n\n");
				}
				break;
			case 18:
				printf("\nHistório de Compras:\n");
				if (imprimeCompras(listaCompra) == 0) {
					printf("Ocorreu algum erro a imprimir as compras, pois não existe nenhuma compra no sistema.\n\n");
				}
				break;
			case 19:
				printf("Introduza o Id da compra a consultar: ");
				lerInteiro(&idCompra);
				if (consultaCompra(listaCompra, idCompra, &compraTemp)) {
					printf("Dados da compra: \n");
					printf("ID da compra: %d\n", compraTemp.id);
					printf("ID do cliente: %d\n", compraTemp.idCliente);
					printf("Data: %d/%d/%d\n", compraTemp.dataCompra.dia, compraTemp.dataCompra.mes, compraTemp.dataCompra.ano);
					printf("Preço total: %f\n", compraTemp.precoTotal);
					
					printf("Pretende ver o talão da compra?[s/S]: ");
					scanf(" %c", &opcaoChar); fflush(stdin);
					if (opcaoChar == 's' || opcaoChar == 'S') {
						printf("Talão da compra:\n");
						if (imprimeItemsCompra(listaItemsCompra, idCompra) == 0) {
							printf("Ocorreu algum erro ao imprimir o talão da compra.\n\n");
						}
					}
				} else {
					printf("Não existe nenhuma compra com esse id.\n\n");
				}
				break;
			case 20:
				if (strcmp("admin", contaLogin.username) != 0) {
					printf("Prentede remover a sua conta?[s/S]: ");
	                scanf(" %c", &opcaoChar); fflush(stdin);
	                if (opcao == 's' || opcao == 'S') {
	                    if (removeContaLogin(listaContasLogin, contaLogin.id)) {
	                        removeGestor(listaGestor, gestor.codGestor);
	                        printf("Conta removida com sucesso.\n\n");
	                        opcao = 0;
	                    } else {
	                        printf("Ocorreu algum erro ao tentar remover a sua conta.\n\n");
	                    }
	                } else {
	                    printf("Remoção da conta cancelada.\n\n");
	                }
				} else {
					printf("Não podes remover, porque és o gestor principal do sistema.\n\n");
				}
				break;
			case 0:
				printf("\nA sair da conta...\n\n");
				break;
			default:
				printf("Opção inválida!! Tente novamente.\n\n");
				break;
		}
	} while (opcao != 0);
}

char* esconderCartaoCredito(char *numCartao) {
	char numCartaoEscondido[21];
	int i, k = 0;
	
	for (i = 0; i < 16; i++) {
		if (i > 11) numCartaoEscondido[k] = numCartao[i];
		else numCartaoEscondido[k] = '*';
		
		k++;
		
		if ((i+1) % 4 == 0) {
			numCartaoEscondido[k] = ' ';
			k++;
		}
	}
	
	numCartaoEscondido[k] = '\0';
	
	return numCartaoEscondido;
}

int isAllNumber(char *string) {
	int i;
	
	for (i = 0; string[i] != '\0'; i++) {
		if (isdigit(string[i]) == 0) return 0;
	}
	
	return 1;
}

int verificarNumeroCartao(char *numCartao) {
	int i, tamanho;
	
	tamanho = strlen(numCartao);
	if (tamanho != 16) {
		printf("O número do cartão precisa de ter 16 dígitos!\n");
		return 0;
	}
	
	if (isAllNumber(numCartao)) return 1;
	else {
		printf("O número do cartão tem de ser números!\n");
		return 0;
	}
}

void verificarStocksProdutos(ListaStock* li) {
	if (li == NULL || (*li) == NULL) return;
	
	ElementoStock *no = *li;
	
	while (no != NULL) {
		if (dentroDaValidade(no->stock.validade) == 0) removeStock(li, no->stock.id);
		
		no = no->prox;
	}
}

void alterarDadosCliente() {
	int opcao;
	
	do {
		printf("\nMenu para alterar: \n");
		printf("1 - Alterar nome;\n");
		printf("2 - Alterar morada;\n");
		printf("3 - Alterar número do cartão de crédito\n");
		printf("4 - Alterar password;\n");
		printf("0 - Voltar;\n");
		printf("Escolha uma opção: ");
		lerInteiro(&opcao);
		
		switch (opcao) {
			case 1:
				printf("Introduza o seu novo nome: ");
				gets(cliente.nome); fflush(stdin);
				if (alterarCliente(listaClientes, cliente)) {
					printf("Nome alterado com sucesso.\n\n");
				} else {
					printf("Ocorreu algum erro ao tentar alterar o nome.\n\n");
				}
				break;
			case 2:
				printf("Introduza a nova morada: ");
				gets(cliente.morada); fflush(stdin);
				if (alterarCliente(listaClientes, cliente)) {
					printf("Morada alterada com sucesso.\n\n");
				} else {
					printf("Ocorreu algum erro ao tentar alterar a morada.\n\n");
				}
				break;
			case 3:
				printf("Introduza o novo número de cartão de crédito: ");
				gets(cliente.nCartaoCredito); fflush(stdin);
				while (verificarNumeroCartao(cliente.nCartaoCredito) == 0) {
					printf("Introduza o número de cartão de crédito: ");
					gets(cliente.nCartaoCredito); fflush(stdin);
				}
				if (alterarCliente(listaClientes, cliente)) {
					printf("Número do cartão alterado com sucesso.\n\n");
				} else {
					printf("Ocorreu algum erro ao tentar alterar o número do cartão\n\n");
				}
				break;
			case 4:
				printf("Introduza a nova password: ");
				strcpy(contaLogin.password, lerPassowrd());
				if (alterarContaLogin(listaContasLogin, contaLogin)) {
					printf("Password alterada com sucesso.\n\n");
				} else {
					printf("Ocorreu algum erro ao tentar alterar a password.\n\n");
				}
				break;
			case 0:
				printf("A voltar para o menu.\n\n");
				break;
			default:
				printf("Opção inválida!! Tente novamente.\n\n");
				break;
		}
	} while (opcao != 0);
}

void comprarProduto() {
	int idProduto, quantidade, stockProduto;
	char opcao;
	Produto produto;
	CarrinhoCompras carrinhoCompra;
	
	printf("Introduza o Id do produto que deseja comprar: ");
	lerInteiro(&idProduto);
	if (consultaProduto(listaProduto, idProduto, &produto) == 0) {
		printf("Não existe nenhum produto com esse Id.\n\n");
		return;
	}
	
	stockProduto = verificarStockProduto(listaStock, idProduto);
	if (stockProduto <= 0) {
		printf("Esse produto está sem stock.\n\n");
		return;
	}
	
	if (consultaCarrinhoCompras(listaCarrinhoCompras, idProduto, &carrinhoCompra)) {
		printf("Você ja tem %d do item %s no seu carrinho, pretende comprar mais?[s/S]: ");
		scanf(" %c", &opcao);
		
		if (opcao == 's' || opcao == 'S') {
			printf("Introduza a quatidade do produtos %s que pretende comprar (Quantidade Disponivel: %d): ", produto.nome, (stockProduto - carrinhoCompra.quantidade));
			lerInteiro(&quantidade);
			while (quantidade <= 0 || (quantidade + carrinhoCompra.quantidade) > stockProduto) {
				printf("Quantidade inválida, a quantidade deve ser no maximo %d.\n", (stockProduto - carrinhoCompra.quantidade));
				printf("Introduza a quatidade do produtos %s que pretende comprar (Quantidade Disponivel: %d): ", produto.nome, (stockProduto - carrinhoCompra.quantidade));
				lerInteiro(&quantidade);
			}
			
			carrinhoCompra.quantidade += quantidade;
			
			if (alterarCarrinhoCompras(listaCarrinhoCompras, carrinhoCompra)) {
				printf("Quantidade de compra alterada com sucesso.\n\n");
			} else {
				printf("Não foi possível alterar a quantidade.\n\n");
			}
		}
	} else {
		printf("Introduza a quantidade do produto %s que pretende comprar (Quantidade Disponivel: %d): ", produto.nome, stockProduto);
		lerInteiro(&quantidade);
		while (quantidade <= 0 || quantidade > stockProduto) {
			printf("Quantidade inválida, a quantidade deve ser no maximo%d.\n", stockProduto);
			printf("Introduza a quatidade do produtos %s que pretende comprar (Quantidade Disponivel: %d): ", produto.nome, stockProduto);
			lerInteiro(&quantidade);
		}
		
		carrinhoCompra.idProduto = idProduto;
		carrinhoCompra.quantidade = quantidade;
		
		if (insereCarrinhoCompras(listaCarrinhoCompras, carrinhoCompra)) {
			printf("Item introduzido com sucesso no carrinho de compras.\n\n");
		} else {
			printf("Ocorreu algum erro ao tentar introduzir o item no carrinho.\n\n");
		}
	}
}

void alterarQuantidadeProdutoCarrinho() {
	int idProduto, quantidade, stockProduto;
	char opcao;
	CarrinhoCompras carrinhoCompra;
	
	printf("Introduza o Id do produto a alterar a quantidade de compra: ");
	lerInteiro(&idProduto);
	if (consultaCarrinhoCompras(listaCarrinhoCompras, idProduto, &carrinhoCompra) == 0) {
		printf("Não foi possível encontrar nenhum produto com essse Id no seu carrinho.\n\n");
	} else {
		stockProduto = verificarStockProduto(listaStock, idProduto);
		if (stockProduto <= 0) {
			printf("Esse produto está sem stock.\nA remove-lo do carrinho...\n\n");
			removeCarrinhoCompras(listaCarrinhoCompras, idProduto);
		} else {
			printf("Introduza a nova quantidade a comprar (Quantidade Disponivel: %d): ", stockProduto);
			lerInteiro(&quantidade);
			while (quantidade <= 0 || quantidade > stockProduto) {
				printf("Quantidade inválida a quantidade deve ser entre 1 e %d", stockProduto);
				printf("Introduza a nova quantidade a comprar (Quantidade Disponivel: %d): ", stockProduto);
				lerInteiro(&quantidade);
			}
			
			printf("Preetende alterar a quantidade de %d para %d: ", carrinhoCompra.quantidade, quantidade);
			scanf(" %c", &opcao);
			if (opcao == 's' || opcao == 'S') {
				carrinhoCompra.quantidade = quantidade;
				if (alterarCarrinhoCompras(listaCarrinhoCompras, carrinhoCompra)) {
					printf("Quantidade alterada com sucesso.\n\n");
				} else {
					printf("Ocorreu algum erro a alterar a quantidade do produto.\n\n");
				}
			} else {
				printf("Alteração cancelada.\n\n");
			}
		}
	}
}

void removerProdutoCarrinho() {
	int idProduto;
	char opcao;
	CarrinhoCompras carrinhoCompra;
	Produto produto;
	
	printf("Introduza o Id do produto a remover do carrinho: "),
	lerInteiro(&idProduto);
	
	if (consultaCarrinhoCompras(listaCarrinhoCompras, idProduto, &carrinhoCompra) == 0) {
		printf("Não existe nenhum produto com esse Id no carrinho.\n\n");
	} else {
		if (consultaProduto(listaProduto, idProduto, &produto) == 0) {
			printf("Ocorreu algum erro ao tentar remover o produto. Tente novamente mais tarde.\n\n");
		} else {
			printf("Pretende remover o produto %s do seu carrinho de compras?[s/S]: ");
			scanf(" %c", &opcao);
			if (opcao == 's' || opcao == 'S') {
				if (removeCarrinhoCompras(listaCarrinhoCompras, idProduto)) {
					printf("Produto removido com sucesso do carrinho de compras.\n\n");
				} else {
					printf("Ocorreu algum erro ao tentar remover o produto do carrinho de compras.\n\n");
				}
			} else {
				printf("Remoção cancelada.\n\n");
			}
		}
	}
}

void finalizarCompra() {
	if(*listaCarrinhoCompras == NULL) 
	{
		printf("\nCarrinho vazio.\n");
		return;
	}
	int nextBuyItemID = 1, compraSucesso = 1, stockProduto = 0;
	Data data = dataAtual();
	Produto produto;
	Compra compra = { nextBuyID, data, cliente.numCliente, 0 };
	ElementoCarrinhoCompras *no = *listaCarrinhoCompras;
	
	while (no != NULL || compraSucesso != 1) {
		compraSucesso = consultaProduto(listaProduto, no->carrinhoCompras.idProduto, &produto);
		
		if (compraSucesso == 1) {
			stockProduto = verificarStockProduto(listaStock, no->carrinhoCompras.idProduto);
			
			if (stockProduto <= 0 || no->carrinhoCompras.quantidade > stockProduto) {
				compraSucesso = 0;
			} else {
				compraSucesso = removerStockProduto(listaStock, no->carrinhoCompras.idProduto, no->carrinhoCompras.quantidade);
				
				if (compraSucesso == 1) {
					ItemsCompra itemCompra = { nextBuyItemID, compra.id, no->carrinhoCompras.idProduto, no->carrinhoCompras.quantidade };
		
					compra.precoTotal += produto.preco * no->carrinhoCompras.quantidade;
					
					compraSucesso = insereItemsCompra(listaItemsCompra, itemCompra, 0);
				
					nextBuyItemID++;
				}
			}
		}		
		
		no  = no->prox;
	}
	
	if (compraSucesso == 0) {
		int statusClearIItemsBuy = removeItemsCompra(listaCompra, compra.id);
		while (statusClearIItemsBuy == 1) {
			statusClearIItemsBuy = removeItemsCompra(listaCompra, compra.id);
		}
		
		printf("Ocorreu algum erro ao tentar finalizar a compra.\n\n");
	} else {
		if ((*listaCarrinhoCompras) == NULL) {
			printf("O carrinho de compras está vázio.\n\n");
			return;
		}
		if (insereCompra(listaCompra, compra, 0)) {
			printf("Compra realizada com sucesso.\n");
			
			libertaListaCarrinhoCompras(listaCarrinhoCompras);
			listaCarrinhoCompras = criaListaCarrinhoCompras();
			if (listaCarrinhoCompras == NULL) {
				printf("Ocorreu algum erro ao tentar limpar o carrinho de compras, tente novamente mais tarde.\n");
			}
			printf("\n");
		} else {
			printf("Ocorreu algum erro ao tentar finalizar a compra.\n\n");
		}
	}
	
}

int removerStockProduto(ListaStock* li, int idProduto, int stockARemover) {
	int stockARemoverRestante = stockARemover, status = 1;
	Stock stock;
	
	while (stockARemoverRestante != 0 || status != 1) {
		status = consultaStockProduto(listaStock, idProduto, &stock);
		
		if (stockARemover >= stock.quantidadeStock) {
			stockARemoverRestante -= stock.quantidadeStock;
			status = removeStock(li, stock.id);
		} else {
			stock.quantidadeStock -= stockARemoverRestante;
			stockARemoverRestante = 0;
			status = alterarStock(li, stock);
		}
	}
	
	return status;
}

void alterarDadosGestor() {
	int opcao;
	
	do {
		printf("\nMenu para alterar: \n");
		printf("1 - Alterar nome;\n");
		printf("2 - Alterar password;\n");
		printf("0 - Voltar;\n");
		printf("Escolha uma opção: ");
		lerInteiro(&opcao);
		
		switch (opcao) {
			case 1:
				printf("Introduza o seu novo nome: ");
				gets(gestor.nome); fflush(stdin);
				if (alterarGestor(listaGestor, gestor)) {
					printf("Nome alterado com sucesso.\n\n");
				} else {
					printf("Ocorreu algum erro ao tentar alterar o nome.\n\n");
				}
				break;
			case 2:
				printf("Introduza a sua nova password: ");
				strcpy(contaLogin.password, lerPassowrd());
				if (alterarContaLogin(listaContasLogin, contaLogin)) {
					printf("Password alterada com sucesso.\n\n");
				} else {
					printf("Ocorreu algum erro ao tentar alterar a password.\n\n");
				}
				break;
			case 0:
				printf("A voltar para o menu.\n\n");
				break;
			default:
				printf("Opção inválida!! Tente novamente.\n\n");
				break;
		}
	} while (opcao != 0);
}

void removerCliente() {
	int idCliente;
	char opcao;
	Cliente clienteTemp;
	ContasLogin contaLoginTemp;
	
	printf("\nIntroduza o Id do cliente a remover: ");
	lerInteiro(&idCliente);
	if (consultaCliente(listaClientes, idCliente, &clienteTemp)) {
		printf("Pretende remover o cliente %s ?[s/S]: ", clienteTemp.nome);
		scanf(" %c", &opcao); fflush(stdin);
		if (opcao == 's' || opcao == 'S') {
			int statusRemoverLogin = 1;
			if (consultaContaLoginByIDTipo(listaContasLogin, 1, idCliente, &contaLoginTemp)) {
				statusRemoverLogin = removeContaLogin(listaContasLogin, contaLoginTemp.id);
			}
		
			if (statusRemoverLogin == 1) {
				if (removeCliente(listaClientes, idCliente)) {
					printf("Cliente removido com sucesso.\n\n");
				} else {
					printf("Ocorreu algum erro ao tentar remover o cliente.\n\n");
				}
			} else {
				printf("Ocorreu algum erro ao tentar remover a conta do cliente.\n\n");
			}
		} else {
			printf("Remoção cancelada.\n\n");
		}
	} else {
		printf("Não existe nenhum cliente com esse id.\n\n");
	}
}

void criarGestor() {
	Gestor gestorTemp;
	ContasLogin contaLoginTemp, contaLoginProcura;
	
	printf("A criar o gestor: \n");
	
	// Dados do gestor
	gestorTemp.codGestor = nextGestorID;
	printf("Introduza o nome do gestor: ");
	gets(gestorTemp.nome); fflush(stdin);
	//
	
	// Dados conta login
	contaLoginTemp.id = nextAccountID;
	contaLoginTemp.createdByAdmin = 1;
	contaLoginTemp.tipoConta = 2;
	contaLoginTemp.idTipo = gestorTemp.codGestor;
	printf("Introduza o username da conta ");
	gets(contaLoginTemp.username); fflush(stdin);
	while (consultaContaLoginByUsername(listaContasLogin, contaLoginTemp.username, &contaLoginProcura) != 0) {
		printf("Username ja está em uso, escolha outro.\n");
		printf("Introduza o username da conta ");
		gets(contaLoginTemp.username); fflush(stdin);
	}
	printf("Introduza a password da conta: ");
	strcpy(contaLoginTemp.password, lerPassowrd()); fflush(stdin);
	printf("\n");
	//
	
	if (insereGestor(listaGestor, gestorTemp, 0)) {
		if (insereContaLogin(listaContasLogin, contaLoginTemp, 0)) {
			printf("Conta criada com sucesso.\n\n");
		} else {
			printf("Ocorreu algum erro ao tentar criar a conta.\n\n");
		}
	} else {
		printf("Ocorreu algum erro ao tentar criar a conta.\n\n");
	}
}

void removerGestor() {
	int idGestor;
	char opcao;
	Gestor gestorTemp;
	ContasLogin contaLoginTemp;
	
	printf("Introduza o Id do gestor a remover: ");
	lerInteiro(&idGestor);
	
	if (consultaGestor(listaGestor, idGestor, &gestorTemp)) {
		printf("Pretende remover o gestor %s ?[s/S]: ", gestorTemp.nome);
		scanf(" %c", &opcao); fflush(stdin);
		if (opcao == 's' || opcao == 'S') {
			int statusRemoverLogin = 1;
			if (consultaContaLoginByIDTipo(listaContasLogin, 2, idGestor, &contaLoginTemp)) {
				statusRemoverLogin = removeContaLogin(listaContasLogin, contaLoginTemp.id);
			}
			
			if (statusRemoverLogin == 1) {
				if (removeGestor(listaGestor, idGestor)) {
					printf("Gestor removido com sucesso.\n\n");
				} else {
					printf("Ocorreu algum erro ao tentar remover o gestor.\n\n");
				}
			} else {
				printf("Ocorreu algum erro ao tentar remover a conta do gestor.\n\n");
			}
		} else {
			printf("Remoção do gestor cancelada.\n\n");
		}
	} else {
		printf("Não existe nenhum gestor com essse Id.\n\n");
	}
}

void adicionarProduto() {
	Produto produtoTemp;
	
	produtoTemp.codProduto = nextProdutoID;
	printf("Introduza o nome do produto: ");
	gets(produtoTemp.nome); fflush(stdin);
	printf("Introduza o preço do produto: ");
	lerFloat(&produtoTemp.preco);
	while (produtoTemp.preco <= 0) {
		printf("O preço do produto não pode ser inferior ou igual a 0.\n");
		printf("Introduza o preço do produto: ");
		lerFloat(&produtoTemp.preco);
	}
	
	if (insereProduto(listaProduto, produtoTemp, 0)) {
		printf("Protudo criado com sucesso.\n\n");
	} else {
		printf("Ocorreu algum erro ao tentar criar o produto.\n\n");
	}
}

void removerProduto() {
	int idProduto;
	char opcao;
	Produto produtoTemp;
	
	printf("Introduza o Id do produto a remover: ");
	lerInteiro(&idProduto);
	
	if (consultaProduto(listaProduto, idProduto, &produtoTemp)) {
		printf("Pretende remover o produto com o nome %s ?[s/S]: ", produtoTemp.nome);
		scanf(" %c", &opcao); fflush(stdin);
		
		if (opcao == 's' || opcao == 'S') {
			if (removeProduto(listaProduto, idProduto)) {
				int statusRemocaoProduto = removeStockProduto(listaStock, idProduto);
				while (statusRemocaoProduto != 0) {
					statusRemocaoProduto = removeStockProduto(listaStock, idProduto);
				}
				
				printf("Produto removido com sucesso.\n\n");
			} else {
				printf("Ocorreu algum erro ao tentar remover o produto.\n\n");
			}
		} else {
			printf("Remoção do produto cancelada.\n\n");
		}
	} else {
		printf("Não existe nenhum produto com esse Id.\n\n");
	}
}

void adicionarStock() {
	int idProduto;
	Produto produtoTemp;
	Stock stockTemp;
	
	printf("Introduza o Id do produto a adicionar stock: ");
	lerInteiro(&idProduto);
	
	if (consultaProduto(listaProduto, idProduto, &produtoTemp)) {
		stockTemp.id = nextStockID;
		stockTemp.productID = idProduto;
		
		printf("Validade do produto:\n");
		stockTemp.validade = lerData();
		while (dentroDaValidade(stockTemp.validade)!= 1) {
			printf("A data tem de ser superior ou igual a data de hoje.\n");
			printf("Validade do produto:\n");
			stockTemp.validade = lerData();
		}
		
		printf("Introduza a quantidade de stock a adicionar: ");
		lerInteiro(&stockTemp.quantidadeStock);
		while (stockTemp.quantidadeStock <= 0) {
			printf("A quantidade tem de ser superior a 0.\n");
			printf("Introduza a quantidade de stock a adicionar ");
			lerInteiro(stockTemp.quantidadeStock);
		}
		
		if (insereStock(listaStock, stockTemp, 0)) {
			printf("Stock introduzido com sucesso.\n\n");
		} else {
			printf("Ocorreu algum erro ao tentar introduzir o stock.\n\n");
		}
	} else {
		printf("Não existe nenhum produto com esse Id.\n\n");
	}
}

Data lerData() {
	int diasMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	Data data;
	
	printf("Introduza o mês: ");
	lerInteiro(&data.mes);
	while (data.mes < 1 || data.mes > 12) {
		printf("O mês introduzido é inválido!! Tem de estar entre 1 e 12.\n");
		printf("Introduza o mês");
		lerInteiro(&data.mes);
	}
	
	printf("Introduza o dia: ");
	lerInteiro(&data.dia);
	while(data.dia < 1 || data.dia > diasMes[data.mes - 1]) {
		printf("O dia introduzido é inválido!! Tem de ser entre 1 e %d.\n", diasMes[data.mes -1]);
		printf("Introduza o dia ");
		lerInteiro(&data.dia);
	}
	
	printf("Introduza o ano: ");
	lerInteiro(&data.ano);
	while (data.ano < 2000) {
		printf("O ano introduzido é inválido!! Tem de ser superior ou igual a 2000");
		printf("Introduza o ano: ");
		lerInteiro(&data.ano);
	}
	
	return data;
}

