/*
	Autor: Nemer Mollon
	Data de criação: 26/05/2022 14:25
	Data de modificação: 26/05/2022 14:25
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { E_SUCESSO, E_NOME_ARQUIVO=200, E_ABRIR_ARQUIVO, E_MEMORIA } e_retorno;

struct _s_log // Total de 39 bytes
{
	char id[9];
	char delimitador1; // Caractere "\t"
	char ano[4];
	char delimitador2;
	char mes[2];
	char delimitador3;
	char dia[2];
	char delimitador4;
	char hora[2];
	char delimitador5;
	char minuto[2];
	char delimitador6;
	char segundo[2];
	char ign[10];
}; //__attribute__((packed));

typedef struct _s_log s_log;

int main(int argc, char *argv[])
{
	FILE *arquivo_entrada;
	int tamanho_arquivo;
	
	s_log log;
	int total_logs;
	
	char id[10];
	char data[11];
	char hora[9];
	
	int i;
	
	#ifdef DEBUG
	printf("Tamanho struct: %d\n", sizeof(s_log));
	#endif
	
	if (argc < 2) {
		puts("Informe o nome do arquivo!");
		printf("Uso:\t%s nome_arquivo.dat\n", argv[0]);
		return E_NOME_ARQUIVO;
	}
	
	if (!(arquivo_entrada = fopen(argv[1], "rb"))) {
		printf("Erro ao abrir o arquivo \"%s\"\n", argv[1]);
		return E_ABRIR_ARQUIVO;
	}
	
	/* Tamanho do arquivo */
	fseek(arquivo_entrada, 0, SEEK_END);
	tamanho_arquivo = ftell(arquivo_entrada);
	rewind(arquivo_entrada);
	
	#ifdef DEBUG
	printf("Tamanho do arquivo: %d\n", tamanho_arquivo);
	#endif
	
	total_logs = tamanho_arquivo/sizeof(s_log);
	
	#ifdef DEBUG
	printf("Total de logs: %d\n", total_logs);
	#endif
	
	for (i=0; i<total_logs; i++) {
		memset(&id, 0, 10);
		memset(&data, 0, 11);
		memset(&hora, 0, 9);
		
		fread(&log, 1, sizeof(s_log), arquivo_entrada);
		
		strncpy(id, log.id, 9);
		
		strncpy(data, log.dia, 2);
		strcat(data, "/");
		strncat(data, log.mes, 2);
		strcat(data, "/");
		strncat(data, log.ano, 4);
		
		strncpy(hora, log.hora, 2);
		strcat(hora, ":");
		strncat(hora, log.minuto, 2);
		strcat(hora, ":");
		strncat(hora, log.segundo, 2);
		
		printf("Id: %s    Data: %s    Hora: %s\n", id, data, hora);
	}
	
	fclose(arquivo_entrada);
	
	return E_SUCESSO;
}

