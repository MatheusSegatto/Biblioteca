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
    int verificador = 321;
    for (size_t i = 0; i < tam_senha; i++)
    {
        key += senha[i];
    }
    data = fopen("data.txt", "w");

    int uteis = 0;
    // Verificando quantas posições não são nulas no vetor de alunos
    for(int i = 0; i < matriculados; i++){
        if(vetalunos[i] != NULL){
            uteis += 1;
        }
    }
    fprintf(data, "%d\n%d %d %d ", (verificador + key), (matriculados + key), (turmas + key), (uteis + key));

    // Tratando vetores de char
    for (int i = 0; i < matriculados; i++)
    {
        if (vetalunos[i] != NULL)
        {
            j = 0;
            while(vetalunos[i]->nome[j] != '\0') //Só deixei um usando WHILE e outro usando FOR pq um bug no meu pc fez com que eu pensasse que o FOR não estva funcionando
            {
                // Verificar se o caractere é um espaço
                if (vetalunos[i]->nome[j] != 32)
                {
                    soma = vetalunos[i]->nome[j] + key;
                    while (soma > 126)
                    {
                        soma -= 93;
                    }
                    vetalunos[i]->nome[j] = soma;
                }
                j += 1;
            }
            for (int j = 0; j < strlen(vetalunos[i]->matricula); j++)
            {
                if(vetalunos[i]->matricula[j] != 32)
                {
                    soma = vetalunos[i]->matricula[j] + key;
                    while (soma > 126)
                    {
                        soma -= 93;
                    }
                    vetalunos[i]->matricula[j] = soma;
                }
            }
            fprintf(data, "%d %d %d %d\n%s\n%s\n", (i + key), (vetalunos[i]->pendencias + key), (vetalunos[i]->livro + key), (vetalunos[i]->recurso + key), (vetalunos[i]->nome), (vetalunos[i]->matricula));
        }
    }
    fprintf(data, "\n");
    // Verificando quantas posições não são nulas no vetor de livros
    uteis = 0;
    for(size_t i = 0; i < sistema_livros; i++){
        if(vetlivros[i] != NULL){
            uteis += 1;
        }
    }
    fprintf(data, "%d %d %d ", (sistema_livros + key), (caixas + key), (uteis + key));
    for (int i = 0; i < sistema_livros; i++)
    {
        if (vetlivros[i] != NULL)
        {
            j = 0;
            while (vetlivros[i]->nome[j] != '\0')
            {
                if(vetlivros[i]->nome[j] != 32)
                {
                    soma = vetlivros[i]->nome[j] + key;
                    while (soma > 126)
                    {
                        soma -= 93;
                    }
                    vetlivros[i]->nome[j] = soma;
                }
                j += 1;
            }
            j = 0;
            while(vetlivros[i]->categoria[j] != '\0')
            {
                if(vetlivros [i]->categoria[j] != 32)
                {
                    soma = vetlivros[i]->categoria[j] + key;
                    while (soma > 126)
                    {
                        soma -= 93;
                    }
                    vetlivros[i]->categoria[j] = soma;
                }
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
    int id, correto = 1, uteis;
    if (access("data.txt", F_OK) != 0)
    {
        printf("Olá, aparentemente é sua primeira vez acessando o sistema. Por favor, defina uma senha (Máx. 20 caracteres)\n");
        scanf(" %[^\n]", senha);
        return;
    }
    else{
        FILE *data;
        int key = 0, soma = 0, verificador;
        data = fopen("data.txt", "r");
        printf("Digite a senha: ");
        scanf(" %[^\n]", senha);
        int tam_senha = strlen(senha);
        for (size_t i = 0; i < tam_senha; i++)
        {
            key += senha[i];
        }
        fscanf(data, "%d", &verificador);
        //Enquanto a senha for incorreta, o usuário será perguntado para digitar a senha novamente
        while (correto == 1)
        {
            if ((verificador - key) != 321)
            {
                printf("Senha incorreta. Digite a senha novamente: ");
                scanf(" %[^\n]", senha);
                tam_senha = strlen(senha);
                key = 0;
                for (size_t i = 0; i < tam_senha; i++)
                {
                    key += senha[i];
                }
            }
            else
            {
                correto = 0;
            }
        }
        fscanf(data, "%d", &(*matriculados));
        fscanf(data, "%d", &(*turmas));
        fscanf(data, "%d", &uteis);
        *turmas -= key;
        *matriculados -= key;
        uteis -= key;
        if ((*matriculados + 1) > ((*turmas) * 35))
        {
            *turmas += 1;
            *tab_alunos = realloc(*tab_alunos, (35 * (*turmas)) * sizeof(alunos *));
            for (size_t i = (35 * ((*turmas) - 1)); i < (35 * (*turmas)); i++)
            {
                (*tab_alunos)[i] = (alunos *)malloc(sizeof(alunos));
            }
        }
        correto = 1;
        int aux;
        char txt_aux[50];
        if(uteis != 0){
            for (int i = 0; i < *matriculados; i++)
            { 
                if (correto == 1)
                {
                    fscanf(data, "%d", &id);
                    id -= key;
                } 
                if (id == i)
                {
                    //fscanf(data, "%d", &(*tab_alunos)[i]->pendencias);
                    fscanf(data, "%d", &aux);
                    (*tab_alunos)[i]->pendencias = aux - key;
                    //fscanf(data, "%d", &(*tab_alunos)[i]->livro);
                    fscanf(data, "%d", &aux);
                    (*tab_alunos)[i]->livro = aux - key;
                    // fscanf(data, "%d", &(*tab_alunos)[i]->recurso);
                    fscanf(data, "%d", &aux);
                    (*tab_alunos)[i]->recurso = aux - key;
                    //fscanf(data, " %[^\n]", (*tab_alunos)[i]->nome);
                    fscanf(data, " %[^\n]", txt_aux);
                    int j = 0, tam_aux = strlen(txt_aux);
                    soma = 0;
                    while (txt_aux[j] != '\0')
                    {
                        // Verificar se caractere é espaço, se for, não fazer nada.
                        if(txt_aux[j] != 32)
                        {
                            soma = txt_aux[j];
                            // Descriptografar o caractere
                            for(;;)
                            {
                                soma += 93;
                                if (soma > key && (soma - key) > 33)
                                {
                                    soma -= key;
                                    txt_aux[j] = soma;
                                    break;
                                }
                            }
                        }
                        j += 1;
                        soma = 0;
                    }
                    soma = 0;
                    strcpy((*tab_alunos)[i]->nome, txt_aux);
                    // fscanf(data, " %[^\n]", (*tab_alunos)[i]->matricula);
                    fscanf(data, " %[^\n]", txt_aux);
                    j = 0;
                    while (txt_aux[j] != '\0')
                    {
                        // Verificar se caractere é espaço, se for, não fazer nada.
                        if(txt_aux[j] != 32)
                        {
                            // Descriptografar o caractere
                            soma = txt_aux[j];
                            for(;;)
                            {
                                soma += 93;
                                if (soma > key && (soma - key) > 33)
                                {
                                    soma -= key;
                                    txt_aux[j] = soma;
                                    break;
                                }
                            }
                        }
                        j += 1;
                        soma = 0;
                    }
                    strcpy((*tab_alunos)[i]->matricula, txt_aux);
                    correto = 1;
                }
                else{
                    free((*tab_alunos)[i]);
                    (*tab_alunos)[i] = NULL;
                    correto = 0;
                }
            }
        }
        else if ((*matriculados) != 0){
            free(*tab_alunos[0]);
            (*tab_alunos)[0] = NULL;
        }
        fscanf(data, "%d", &(*sistema_livros));
        *sistema_livros -= key;
        fscanf(data, "%d", &(*caixas));
        *caixas -= key;
        fscanf(data, "%d", &uteis);
        uteis -= key;
        if ((*sistema_livros + 1) > ((*caixas) *50))
        {
            *caixas += 1;
            *tab_livros = realloc(*tab_livros, (50 * (*caixas)) * sizeof(livros *));
            for (size_t i = (50 * ((*caixas) - 1)); i < (50 * (*caixas)); i++)
            {
                (*tab_livros)[i] = (livros *)malloc(sizeof(livros));
            }
        }
        correto = 1;
        if(uteis != 0){
            for (int i = 0; i < *sistema_livros; i++)
            {
                if (correto == 1)
                {
                    fscanf(data, "%d", &id);
                    id -= key;
                    // printf("%d\n", id);
                }
                if (id == i)
                {
                    // fscanf(data, "%d", &(*tab_livros)[i]->ano);
                    fscanf(data, "%d", &aux);
                    (*tab_livros)[i]->ano = aux - key;
                    // fscanf(data, "%d", &(*tab_livros)[i]->status);
                    fscanf(data, "%d", &aux);
                    (*tab_livros)[i]->status = aux - key;
                    // fscanf(data, "%d", &(*tab_livros)[i]->aluno);
                    fscanf(data, "%d", &aux);
                    (*tab_livros)[i]->aluno = aux - key;
                    // fscanf(data, " %[^\n]", (*tab_livros)[i]->nome);
                    fscanf(data, " %[^\n]", txt_aux);
                    int j = 0;
                    soma = 0;
                    while (txt_aux[j] != '\0')
                    {
                        // Verificar se caractere é espaço, se for, não fazer nada.
                        if(txt_aux[j] != 32)
                        {
                            // Descriptografar o caractere
                            soma = txt_aux[j];
                            for(;;)
                            {
                                soma += 93;
                                if (soma > key && (soma - key) > 33)
                                {
                                    soma -= key;
                                    txt_aux[j] = soma;
                                    break;
                                }
                            }
                        }
                        j += 1;
                        soma = 0;
                    }
                    strcpy((*tab_livros)[i]->nome, txt_aux);
                    // fscanf(data, " %[^\n]", (*tab_livros)[i]->categoria);
                    fscanf(data, " %[^\n]", txt_aux);
                    j = 0;
                    soma = 0;
                    while (txt_aux[j] != '\0')
                    {
                        // Verificar se caractere é espaço, se for, não fazer nada.
                        if(txt_aux[j] != 32)
                        {
                            soma = txt_aux[j];
                            // Descriptografar o caractere
                            for(;;)
                            {
                                soma += 93;
                                if (soma > key && (soma - key) > 33)
                                {
                                    soma -= key;
                                    txt_aux[j] = soma;
                                    break;
                                }
                            }
                        }
                        j += 1;
                        soma = 0;
                    }
                    strcpy((*tab_livros)[i]->categoria, txt_aux);
                }
                else{
                    correto = 0;
                    free((*tab_livros)[i]);
                    (*tab_livros)[i] = NULL;
                }
            }
        }
        else if((*sistema_livros) != 0){
            free((*tab_livros)[0]);
            (*tab_livros)[0] = NULL;
        }
        // Recurso:
        recurso *p = cab->prox;
        while (fscanf(data, "%d", &id) != EOF)
        {
            p = (recurso *)malloc(sizeof(recurso));
            p->ID = (id - key);
            // printf("%d\n", id);
            // fscanf(data, "%d", &(p->status));
            fscanf(data, "%d", &aux);
            p->status = aux - key;
            // printf("%d\n", p->status);
            // fscanf(data, "%d", &(p->aluno));
            fscanf(data, "%d", &aux);
            p->aluno = aux - key;
            // printf("%d\n", p->aluno);
            // fscanf(data, " %[^\n]", p->tipo);
            fscanf(data, " %[^\n]", txt_aux);
            int j = 0;
            soma = 0;
            while (txt_aux[j] != '\0')
            {
                // Verificar se caractere é espaço, se for, não fazer nada.
                if(txt_aux[j] != 32)
                {
                    soma = txt_aux[j];
                    // Descriptografar o caractere
                    for(;;)
                    {
                        soma += 93;
                        if (soma > key && (soma - key) > 33)
                        {
                            soma -= key;
                            txt_aux[j] = soma;
                            break;
                        }
                    }
                }
                j += 1;
                soma = 0;
            }
            strcpy(p->tipo, txt_aux);
            // printf("%s\n", p->tipo);
            p->prox = cab->prox;
            cab->prox = p;
        }
    fclose(data);
    }
}
