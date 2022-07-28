#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

void export_data(alunos **vetalunos, livros **vetlivros, recurso *cab, int matriculados, int sistema_livros, int turmas, int caixas, char *senha){
    FILE *data;
    int tam_senha = strlen(senha);
    int key = 0, soma = 0, j = 0;
    //int lixo;
    for (size_t i = 0; i < tam_senha; i++)
    {
        key += senha[i];
    }
    //printf("%s\n%d\n", senha, key);
    //scanf("%d", &lixo);
    data = fopen("data.txt", "w");

    fprintf(data, "%d %d ", (matriculados + key), (turmas + key));

    // Tratando vetores de char

    for (int i = 0; i < matriculados; i++)
    {
        if (vetalunos[i] != NULL)
        {
            j = 0;
            while(vetalunos[i]->nome[j] != '\0') //Só deixei um usando WHILE e outro usando FOR pq um bug no meu pc fez com que eu pensasse que o FOR não estva funcionando
            {
                //printf("ENTREI NO WHILE\n");
                soma = vetalunos[i]->nome[j] + key;
                while (soma > 126)
                {
                    soma -= 93;
                }
                vetalunos[i]->nome[j] = soma; //Talvez não funcione dessa forma
                j += 1;
            }
            for (int j = 0; j < strlen(vetalunos[i]->matricula); j++)
            {
                //printf("ENTREI NO FOR\n");
                soma = vetalunos[i]->matricula[j] + key;
                while (soma > 126)
                {
                    soma -= 93;
                }
                vetalunos[i]->matricula[j] = soma;
            }
            //printf("%d\n", soma);
            fprintf(data, "%d %d %d %d\n%s\n%s\n", (i + key), (vetalunos[i]->pendencias + key), (vetalunos[i]->livro + key), (vetalunos[i]->recurso + key), (vetalunos[i]->nome), (vetalunos[i]->matricula));
        }
        //scanf("%d", &lixo);
    }
    fprintf(data, "\n");
    fprintf(data, "%d %d ", (sistema_livros + key), (caixas + key));
    for (int i = 0; i < sistema_livros; i++)
    {
        if (vetlivros[i] != NULL)
        {
            j = 0;
            while (vetlivros[i]->nome[j] != '\0')
            {
                soma = vetlivros[i]->nome[j] + key;
                while (soma > 126)
                {
                    soma -= 93;
                }
                vetlivros[i]->nome[j] = soma;
                j += 1;
            }
            j = 0;
            while(vetlivros[i]->categoria[j] != '\0')
            {
                soma = vetlivros[i]->categoria[j] + key;
                while (soma > 126)
                {
                    soma -= 93;
                }
                vetlivros[i]->categoria[j] = soma;
                j += 1;
            }
            fprintf(data, "%d %d %d %d\n%s\n%s\n", (i + key), (vetlivros[i]->ano + key), (vetlivros[i]->status + key), (vetlivros[i]->aluno + key), vetlivros[i]->nome, vetlivros[i]->categoria);
        }    
    }
    fprintf(data, "\n");
    if (cab->prox != NULL)
    {
        recurso *p = cab->prox;
        while (p != NULL)
        {
            j = 0;
            while(p->tipo[j] != '\0')
            {
                soma = p->tipo[j] + key;
                while (soma > 126)
                {
                    soma -= 93;
                }
                p->tipo[j] = soma;
                j += 1;
            }
            fprintf(data, "%d %d %d\n%s\n", (p->ID + key), (p->status + key), (p->aluno + key), p->tipo);
            p = p->prox;
        }
    }
    fclose(data);
}

void import(alunos ***tab_alunos, livros ***tab_livros, alunos **vetalunos, livros **vetlivros, recurso *cab, int *matriculados, int *sistema_livros, int *turmas, int *caixas, char *senha){
    int id, correto = 1;
    if (access("data.txt", F_OK) != 0)
    {
        printf("Olá, aparentemente é sua primeira vez acessando o sistema. Por favor, defina uma senha (Máx. 20 caracteres)\n");
        scanf(" %[^\n]", senha);
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
            //printf("ENTREI NOO REALLOC LIVRO\n");
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
        // Recurso:
        recurso *p = cab->prox;
        while (fscanf(data, "%d", &id) != EOF)
        {
            // printf("ENtrou no while\n");
            //int lixo;
            p = (recurso *)malloc(sizeof(recurso));
            p->ID = id;
            // printf("%d\n", id);
            fscanf(data, "%d", &(p->status));
            // printf("%d\n", p->status);
            fscanf(data, "%d", &(p->aluno));
            // printf("%d\n", p->aluno);
            fscanf(data, " %[^\n]", p->tipo);
            // printf("%s\n", p->tipo);
            //scanf("%d", &lixo);
            p->prox = cab->prox;
            cab->prox = p;
        }
    }
}