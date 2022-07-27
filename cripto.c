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
                fscanf(data, "%d", &vetalunos[i]->pendencias);
                fscanf(data, "%d", &vetalunos[i]->livro);
                fscanf(data, "%d", &vetalunos[i]->recurso);
                fscanf(data, " %[^\n]", vetalunos[i]->nome);
                fscanf(data, " %[^\n]", vetalunos[i]->matricula);
                correto = 1;
            }
            else{
                free(vetalunos[i]);
                vetalunos[i] = NULL;
                correto = 0;
            }
        }
        //printf("%s\n", vetalunos[2]->nome);       
    }
}