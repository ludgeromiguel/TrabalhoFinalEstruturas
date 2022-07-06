#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "functions.h"

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	printf("A iniciar o programa...\n");
	
	if (startProgram()) {
		printf("Programa inciado com sucesso.\n\n");
		menuLogin();
	} else {
		printf("Ocorreu algum erro ao iniciar o programa, tente novamente mais tarde.\n\n");
		endProgram();
		exit(1);
	}
	
	return 0;
}
