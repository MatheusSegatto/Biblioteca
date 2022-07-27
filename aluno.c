#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void novo_cadastro_aluno(alunos ***tabela, alunos **vet, int *matriculados, int *turmas){
    system("clear");
    char matricula[12];
    printf("Qual a matrícula do aluno que será cadastrado?\n");
    scanf(" %[^\n]", matricula);
    int status = 0;
    for (int i = 0; i < *matriculados; i++)
    {
        if (vet[i] != NULL && strcmp(vet[i]->matricula, matricula) == 0)
        {
            printf("Aluno já cadastrado! Operação cancelada\n");
            status = 1;
            break;
        }
    }
    if (status == 0)
    {
        if ((*matriculados + 1) > ((*turmas) * 35))
        {
            *turmas += 1;
            *tabela = realloc(*tabela, (35 * (*turmas)) * sizeof(alunos *));
            for (size_t i = (35 * ((*turmas) - 1)); i < (35 * (*turmas)); i++)
            {
                (*tabela)[i] = (alunos *)malloc(sizeof(alunos));
            }
        }
        strcpy((*tabela)[*matriculados]->matricula, matricula);
        printf("Qual o nome do aluno?\n");
        scanf(" %[^\n]", (*tabela)[*matriculados]->nome);
        (*tabela)[*matriculados]->livro = -1;
        (*tabela)[*matriculados]->recurso = -1;
        (*tabela)[*matriculados]->pendencias = 0;
        *matriculados += 1;
        printf("Aluno Cadastrado com sucesso!\n");
        
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

void remove_aluno(alunos **vet, int matriculados){
    system("clear");
    int id = 0;
    printf("Digite o ID do aluno que quer remover\n");
    scanf("%d", &id);
    //TODO Verificar se possui algo emprestado
    if(id < matriculados && vet[id] != NULL){
        if (vet[id]->livro == -1 && vet[id]->recurso == -1 && vet[id]->pendencias == 0)
        {
            free(vet[id]);
            vet[id] = NULL;
            printf("Aluno removido do sistema!\n");
        }
        else{
            printf("O aluno possui alguma pendência com a biblioteca! Operação canceladada!\n");
        }
    }
    else{
        printf("Aluno não está no sistema!\n");
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

void lista_aluno(alunos **vet, int quantidade){
    system("clear");
    for (int i = 0; i < quantidade; i++)
    {
        if (vet[i] != NULL)
        {
            printf("====================================\n");
            printf("NOME: %s\nID: %d\nMATRICULA: %s\nSTATUS: %d Pendências com a biblioteca\n", vet[i]->nome, i, vet[i]->matricula, vet[i]->pendencias);
        }
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
    //system("pause");
    
}

void busca_aluno(alunos **vet, int cadastrados){
    system("clear");
    printf("Qual ID do aluno procurado?\n");
    int id;
    scanf("%d", &id);
    if (id < (cadastrados) && vet[id] != NULL)
    {
        printf("====================================\n");
        printf("Aluno encontrado!\nNOME: %s\nMATRICULA: %s\nSTATUS: %d livros emprestados\n", vet[id]->nome, vet[id]->matricula, vet[id]->pendencias);
    }
    else
    {
        printf("Aluno não existe no sistema\n");
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}
