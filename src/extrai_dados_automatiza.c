/*
    Autor: Nemer Mollon
    Data de criação: 02/03/2021 11:32
    Data de modificação: 02/03/2021 15:28
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { E_SUCESSO, E_NOME_ARQUIVO=200, E_ABRIR_ARQUIVO, E_MEMORIA } e_retorno;

struct _s_usuario // Total de 28 bytes
{
    char ign01[3]; // 3 primeiros bytes (verificar qual a aplicação deles)
    char senha[5]; // Exatamente 5 caracteres, sem o '\0'
    char nome[8]; // Exatamente 8 caracteres, sem o '\0'
    int uid[3]; // 12 bytes restantes, onde está o UID inclusive
}; //__attribute__((packed));

typedef struct _s_usuario s_usuario;

int main(int argc, char *argv[])
{
    FILE *arquivo_entrada;
    int tamanho_arquivo;
    
    s_usuario usuario;
    int total_usuarios;
    
    char usuario_impressao[9];
    char senha_impressao[6];
    
    int i;
    int j;
    
    #ifdef DEBUG
    printf("Tamanho struct: %d\n", sizeof(s_usuario));
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
    
    total_usuarios = tamanho_arquivo/sizeof(s_usuario);
    
    #ifdef DEBUG
    printf("Total de usuarios: %d\n", total_usuarios);
    #endif
    
    for (i=0; i<total_usuarios; i++) {
        
        fread(&usuario, 1, sizeof(s_usuario), arquivo_entrada);
        
        strncpy(usuario_impressao, usuario.nome, 8);
        usuario_impressao[8] = 0;
        
        #ifdef DEBUG
        printf("Primeiros 3 bytes: %3d %3d %3d\t", usuario.ign01[0], usuario.ign01[1], usuario.ign01[2]);
        #endif
        
        printf("Usuario: %-8s\t", usuario_impressao);
        
        #ifdef COMPLETO
        strncpy(senha_impressao, usuario.senha, 5);
        senha_impressao[5] = 0;
        printf("Senha: %-5s\t", senha_impressao);
        #endif
        
        #ifdef DEBUG
        for (j=0; j<3; j++) {
            printf("%d\t", usuario.uid[j]);
        }
        puts("");
        #else
        printf("UID: %04d\n", usuario.uid[2]);
        #endif
    }
    
    fclose(arquivo_entrada);
    
    return E_SUCESSO;
}
