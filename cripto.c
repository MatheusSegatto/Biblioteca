#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

void export_data(alunos **vetalunos, livros **vetlivros, recurso *cab, int matriculados, int sistema_livros, int turmas, int caixas){
    FILE *data;
    
    data = fopen("data.txt", "w");
    fprintf(data, "%d %d ", matriculados, turmas);
    for (int i = 0; i < matriculados; i++)
    {
        if (vetalunos[i] != NULL)
        {
            fprintf(data, "%d %d %d %d\n%s\n%s\n", i, vetalunos[i]->pendencias, vetalunos[i]->livro, vetalunos[i]->recurso, vetalunos[i]->nome, vetalunos[i]->matricula);
        }
    }
    fprintf(data, "\n");
    fprintf(data, "%d %d ", sistema_livros, caixas);
    for (int i = 0; i < sistema_livros; i++)
    {
        if (vetlivros[i] != NULL)
        {
            fprintf(data, "%d %d %d %d\n%s\n%s\n", i, vetlivros[i]->ano, vetlivros[i]->status, vetlivros[i]->aluno, vetlivros[i]->nome, vetlivros[i]->categoria);
        }    
    }
    fprintf(data, "\n");
    if (cab->prox != NULL)
    {
        recurso *p = cab->prox;
        while (p != NULL)
        {
            fprintf(data, "%d %d %d\n%s\n", p->ID, p->status, p->aluno, p->tipo);
            p = p->prox;
        }
    }
    fclose(data);
}

void import(alunos ***tab_alunos, livros ***tab_livros, alunos **vetalunos, livros **vetlivros, recurso *cab, int *matriculados, int *sistema_livros, int *turmas, int *caixas){
    int id, correto = 1;
    if (access("data.txt", F_OK) != 0)
    {
        return;
    }
    else{
        FILE *data;
        data = fopen("data.txt", "r");
        fscanf(data, "%d", &(*matriculados));
        fscanf(data, "%d", &(*turmas));
        if ((*matriculados + 1) > ((*turmas) * 35))
        {
            *turmas += 1;
            *tab_alunos = realloc(*tab_alunos, (35 * (*turmas)) * sizeof(alunos *));
            for (size_t i = (35 * ((*turmas) - 1)); i < (35 * (*turmas)); i++)
            {
                (*tab_alunos)[i] = (alunos *)malloc(sizeof(alunos));
            }
        }
        for (int i = 0; i < *matriculados; i++)
        {
            //Talvez usar um alternador status 
            if (correto == 1)
            {
                fscanf(data, "%d", &id);
            } 
            if (id == i)
            {
                fscanf(data, "%d", &(*tab_alunos)[i]->pendencias);
                fscanf(data, "%d", &(*tab_alunos)[i]->livro);
                fscanf(data, "%d", &(*tab_alunos)[i]->recurso);
                fscanf(data, " %[^\n]", (*tab_alunos)[i]->nome);
                fscanf(data, " %[^\n]", (*tab_alunos)[i]->matricula);
                correto = 1;
            }
            else{
                free((*tab_alunos)[i]);
                (*tab_alunos)[i] = NULL;
                correto = 0;
            }
        }
        fscanf(data, "%d", &(*sistema_livros));
        fscanf(data, "%d", &(*caixas));
        if ((*sistema_livros + 1) > ((*caixas) *50))
        {
            printf("ENTREI NOO REALLOC LIVRO\n");
            *caixas += 1;
            *tab_livros = realloc(*tab_livros, (50 * (*caixas)) * sizeof(livros *));
            for (size_t i = (50 * ((*caixas) - 1)); i < (50 * (*caixas)); i++)
            {
                (*tab_livros)[i] = (livros *)malloc(sizeof(livros));
            }
        }
        // printf("PASSEI DO REALOC\nLIVROS: %d\n", *sistema_livros);
        // int lixo;
        // scanf("%d", &lixo);
        correto = 1;
        for (int i = 0; i < *sistema_livros; i++)
        {
            if (correto == 1)
            {
                fscanf(data, "%d", &id);
                // printf("%d\n", id);
                // scanf("%d", &lixo);
            }
            if (id == i)
            {
                fscanf(data, "%d", &(*tab_livros)[i]->ano);
                fscanf(data, "%d", &(*tab_livros)[i]->status);
                fscanf(data, "%d", &(*tab_livros)[i]->aluno);
                fscanf(data, " %[^\n]", (*tab_livros)[i]->nome);
                fscanf(data, " %[^\n]", (*tab_livros)[i]->categoria);
            }
            else{
                correto = 0;
                free((*tab_livros)[i]);
                (*tab_livros)[i] = NULL;
            }
        }
        
        
        //printf("%s\n", vetalunos[2]->nome);       
    }
}