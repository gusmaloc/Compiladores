#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>

/*
* Uma entrada qualquer de exemplo
*/
char* cadeia = "-123.45";

/*
* Tipos de tokens (classificação)
*/
typedef enum {
	ERRO,
	NUM_INTEIRO,
	NUM_REAL
} TOKEN_TYPE;

/* 
* Protótipos de funções
*/
TOKEN_TYPE validar(char*);
void msg_erro(char*);

/*
* Este programa implementa um analisador
* léxico a partir de um AFD que realiza
* a validação de sentenças.
*/
int main(int argc, char* argv[]) {
	
	char* entrada;
	int classificacao;

	if (argc < 2) {
		printf("Uso:\n");
		printf("  afd_numeros.exe <string>:\n");
		printf("\n");
		printf("Onde <string> pode ser qualquer sequência de caracteres a ser verificada e validada\n");
		printf("como um número, sinalizado ou não, do tipo inteiro ou real.\n");
		printf("\n\n");
		entrada = cadeia;
	}
	else
		entrada = argv[1];

	printf("Executando para a entrada: %s\n", entrada);
	classificacao = validar(entrada);

	return 0;
}

/*
* AFD para validação/reconhecimento de
* sentenças numéricas, quer sejam reais
* ou inteiras.
* 
* RegEx: (+|-|e)(0-9)+(.(0-9)+)?
*/
TOKEN_TYPE validar(char* simb) {

	char tk[30] = "";

	q0:
		if ((*simb == '+') || (*simb == '-')) {
			strncat(tk, simb, 1);
			simb++;
		}
		goto q1;

	q1:
		if ((*simb >= '0') && (*simb <= '9')) {
			strncat(tk, simb, 1);
			simb++;
			goto q2;
		}
		else {
			msg_erro(simb);
			return ERRO;
		}

	q2: 
		while ((*simb >= '0') && (*simb <= '9')) {
			strncat(tk, simb, 1);
			simb++;
		}
		if (*simb == '.') {
			strncat(tk, simb, 1);
			simb++;
			goto q3;
		}
		else if (*simb == '\x0') {
			printf("tk: %s\n", tk);
			return NUM_INTEIRO;
		}
		else {
			msg_erro(simb);
			return ERRO;
		}

	q3:
		if ((*simb >= '0') && (*simb <= '9')) {
			strncat(tk, simb, 1);
			simb++;
			goto q4;
		}
		else {
			msg_erro(simb);
			return ERRO;
		}

	q4:
		while ((*simb >= '0') && (*simb <= '9')) {
			strncat(tk, simb, 1);
			simb++;
		}
		if (*simb == '\x0') {
			printf("tk: %s\n", tk);
			return NUM_REAL;
		}
		else {
			msg_erro(simb);
			return ERRO;
		}

}

/*
* Apresenta uma mensagem na tela, reportando
* algum erro de natureza léxica.
*/
void msg_erro(char* simb) {
	printf("Erro: simbolo \'%c\' inesperado.", *simb);
}