#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

recurso * busca_recurso(recurso *cab, int id, recurso **ant){
    (*ant) = cab;
    recurso *p = cab->prox;
    while (p != NULL && p->ID != id)
    {
        (*ant) = p;
        p = p->prox;
    }
    return p;
}
void cadastro_recurso(recurso *cab){
    system("clear");
    recurso *ant = NULL;
    int id;
    printf("Insira o ID do recurso\n");
    scanf("%d", &id);
    recurso *p = busca_recurso(cab, id, &ant);
    if (p != NULL)
    {
        printf("Recurso já cadastrado! Operação cancelada.\n");
        printf("====================================\n");
        char saida;
        printf("Pressione qualquer tecla para sair\n");
        scanf("%s", &saida);
        return;
    }
    //Inserção do recurso
    p = (recurso *)malloc(sizeof(recurso));
    p->ID = id;
    int escolha;
    printf("TIPO:\n1- Sala\n2- Computador\n3- Armário\n");
    scanf("%d", &escolha);
    if (escolha == 1)
    {
        strcpy(p->tipo, "Sala");
    }
    else if (escolha == 2)
    {
        strcpy(p->tipo, "Computador");
    }
    else if (escolha == 3)
    {
        strcpy(p->tipo, "Armario");
    }
    p->aluno = -1;
    p->status = 1;
    printf("RECURSO CADASTRADO!\n");
    p->prox = cab->prox;
    cab->prox = p;
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

void remove_recurso(recurso *cab){
    system("clear");
    recurso *ant = NULL;
    recurso *p;
    int id;

    printf("Qual ID do recurso que será removido?\n");
    scanf("%d", &id);
    p = busca_recurso(cab, id, &ant);
    if (p != NULL)
    {
        if(p->status == 1)
        {
            ant->prox = p->prox;
            free(p);
            printf("Recurso removido com sucesso!\n");
        }
        else{
            printf("Recurso ocupado pelo aluno de ID: %d! Operação cancelada\n", p->aluno);
        }
    }
    else{
        printf("Recurso não encontrado! Verifique o ID.\n");
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

void lista_recurso(recurso *cab, alunos **pessoas){
    system("clear");
    if (cab->prox == NULL)
    {
        printf("Nenhum recurso cadastrado!\n");
        printf("====================================\n");
        char saida;
        printf("Pressione qualquer tecla para sair\n");
        scanf("%s", &saida);
        return;
    }
    
    recurso *p = cab->prox;
    printf("RECURSOS:\n");
    while (p != NULL)
    {
        printf("====================================\n");
        printf("ID: %d\nTIPO: %s\n", p->ID, p->tipo);
        if (p->status == 0)
        {
            printf("STATUS: Ocupado pelo aluno de matrícula: %s\n", pessoas[p->aluno]->matricula);
        }
        else{
            printf("STATUS: Disponível\n");
        }
        p = p->prox;
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

void busca_recurso_menu(recurso *cab, alunos **pessoas){
    system("clear");
    recurso *ant = NULL;
    recurso *p;
    int id;
    printf("Qual ID do recurso buscado?\n");
    scanf("%d", &id);
    p = busca_recurso(cab, id, &ant);
    if (p != NULL)
    {
        printf("====================================\n");
        printf("Recurso encontrado:\nID: %d\nTIPO: %s\n", p->ID, p->tipo);
        // TODO STATUS
        if (p->status == 0)
        {
            printf("STATUS: Ocupado pelo aluno de matrícula: %s\n", pessoas[p->aluno]->matricula);
        }
        else{
            printf("STATUS: Disponível\n");
        }
        
    }
    else{
        printf("Recurso não encontrado! Verifique o ID.\n");
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

void ocupa_recurso(recurso *cab, alunos **pessoas, int totalalunos){
    system("clear");
    recurso *ant = NULL;
    recurso *p;
    int id, escolha, aluno;
    printf("1- OCUPAR RECURSO\n2- DESOCUPAR RECURSO\n");
    scanf("%d", &escolha);
    if (escolha == 1)
    {
        // Ocupar
        printf("Qual ID do recurso que será ocupado?\n");
        scanf("%d", &id);
        p = busca_recurso(cab, id, &ant);
        if (p != NULL && p->status == 1)
        {
            printf("Qual ID do aluno que ocupará o recurso?\n");
            scanf("%d", &aluno);
            if (aluno < (totalalunos) && pessoas[aluno] != NULL)
            {
                // pessoas[aluno]->livro = id;
                // vet[id]->aluno = aluno;
                // vet[id]->status = 0;
                pessoas[aluno]->recurso = id;
                pessoas[aluno]->pendencias += 1;
                p->aluno = aluno;
                p->status = 0;
                printf("Recurso ocupado com sucesso!\n");
            }
            else{
                printf("Aluno não está no sistema\n");
            }

        }
        else if (p->status == 0)
        {
            printf("Recurso já ocupado pelo aluno de ID: %d\n", p->aluno);
        }
        else{
            printf("Recurso não encontrado! Verifique o ID.\n");
        }
    }
    else if (escolha ==2)
    {
        // Desocupar
        printf("Qual ID do recurso que será desocupado?\n");
        scanf("%d", &id);
        p = busca_recurso(cab, id, &ant);
        if (p != NULL)
        {
            pessoas[p->aluno]->recurso = -1;
            pessoas[p->aluno]->pendencias -= 1;
            p->aluno = -1;
            p->status = 1;
            printf("Recurso desocupado com sucesso!\n");
        }
        else{
            printf("Recurso não encontrado! Verifique o ID.\n");
        }
    }
    
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
    
}
