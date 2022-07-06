#define FILE_ID_CLIENTE "database/next_cliente_id.dat" // Arquivo para guardar o proximo id de cliente
#define FILE_ID_GESTOR "database/next_gestor_id.dat" // Arquivo para guardar o proximo id de gestor
#define FILE_ID_PRODUCT "database/next_product_id.dat" // Arquivo para guardar o proximo id de produto
#define FILE_ID_STOCK "database/next_stock_id.dat" // Arquivo para guardar o proximo id de stock
#define FILE_ID_ACCOUNT "database/next_account_id.dat" // Arquivo para guardar o proximo id de conta
#define FILE_ID_COMPRA "database/next_buy_id.dat" // Arquivo para guardar o proximo id da compra

#define FILE_CLIENTES "database/clientes.dat" // Arquivo para guardar todas as contas de clientes
#define FILE_GESTORES "database/gestores.dat" // Arquivo para guardar todos as contas de gestores
#define FILE_PRODUCTS "database/products.dat" // Arquivo para guardar todos os produtos
#define FILE_STOCKS "database/sockts.dat" // Arquivo para guardar todo o stock do sistema
#define FILE_ACCOUNT "database/accounts.dat" // Arquivo para guardar todas as contas do sistema
#define FILE_COMPRAS "database/compras.dat" // Arquivo para guardar todas as compras feitas no sistema
#define FILE_ITEMS_COMPRAS "database/itemsCompras.dat" // Arquivo para guardar todos os items das compras feitas no sistemas

#define DATABASE_FOLDER "database" // Nome da pasta em que os arquivos de base de dados vão ser guardados

// Estruturas
typedef struct {
	int dia, mes, ano;
} Data;

typedef struct {
	int id; // Prenchido automaticamente com o valor do arquivo "FILE_ID_ACCOUNT"
	char username[30];
	char password[30];
	int tipoConta; // 1 - Cliente, 2 - Gestor
	int idTipo; // Guarda o Id do cliente/gestor dependendo do tipo da conta
	int createdByAdmin; // 0 ou null se não for criado pelo admin, 1 se tiver sido
} ContasLogin;

typedef struct {
	int numCliente; // Prenchido automaticamente com o valor do arquivo "FILE_ID_CLIENTE"
	char nome[30];
	char morada[50];
	int nContribuinte;
	char nCartaoCredito[16];
} Cliente;

typedef struct {
	int codGestor; // Prenchido automaticamente com o valor do Arquivo "FILE_ID_GESTOR"
	char nome[30];
} Gestor;

typedef struct {
	int codProduto; // Prenchido automaticamente com o valor do Arquivo "FILE_ID_PRODUCT"
	char nome[30];
	float preco;
} Produto;

typedef struct {
	int id; // Prenchido automaticamente com o valor do Arquivo "FILE_ID_STOCK"
	int productID;
	Data validade;
	int quantidadeStock;
} Stock;

typedef struct {
	int idProduto;
	int quantidade;
} CarrinhoCompras;

typedef struct {
	int id; // Prenchido automaticamente com o valor do Arquivo "FILE_ID_COMPRA"
	Data dataCompra;
	int idCliente;
	float precoTotal;
} Compra;

typedef struct {
	int id;
	int idCompra;
	int idProduto;
	int quantidade;
} ItemsCompra;
//

// Elementos das listas
typedef struct elementoContasLogin {
	ContasLogin contaLogin;
	struct elementoContasLogin *prox;
} ElementoContasLogin;

typedef struct elementoCliente {
	Cliente cliente;
	struct elementoCliente *prox;
} ElementoCliente;

typedef struct elementoGestor {
	Gestor gestor;
	struct elementoGestor *prox;
} ElementoGestor;

typedef struct elementoProduto {
	Produto produto;
	struct elementoProduto *prox;
} ElementoProduto;

typedef struct elementoStock {
	Stock stock;
	struct elementoStock *prox;
} ElementoStock;

typedef struct elementoCarrinhoCompras {
	CarrinhoCompras carrinhoCompras;
	struct elementoCarrinhoCompras *prox;
} ElementoCarrinhoCompras;

typedef struct elementoCompra {
	Compra compra;
	struct elementoCompra *prox;
} ElementoCompra;

typedef struct elementoItemsCompra {
	ItemsCompra itemsCompra;
	struct elementoItemsCompra *prox;
} ElementoItemsCompra;
//

// Listas
typedef ElementoContasLogin* ListaContasLogin;
typedef ElementoCliente* ListaCliente;
typedef ElementoGestor* ListaGestor;
typedef ElementoProduto* ListaProduto;
typedef ElementoStock* ListaStock;
typedef ElementoCarrinhoCompras* ListaCarrinhoCompras;
typedef ElementoCompra* ListaCompra;
typedef ElementoItemsCompra* ListaItemsCompra;
//
