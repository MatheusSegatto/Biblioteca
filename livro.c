#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void cadastro_livro(livros ***tabela, int *cadastrados, int *caixas){
    system("clear");
    //Para alterar, usar *caixas
    if ((*cadastrados + 1) > (*caixas * 50))
    {
        *caixas += 1;
        *tabela = realloc(*tabela, (50 * (*caixas)) * sizeof(livros *));
        for (size_t i = (50 * ((*caixas) - 1)); i < (50 * (*caixas)); i++)
        {
            (*tabela)[i] = (livros *)malloc(sizeof(livros)); //É *tabela msm? Quando coloquei só "tabela" recebi um warning do gcc
        }
    }
    char tmp[20];
    int ano;
    printf("Qual o nome do livro?\n");
    scanf(" %[^\n]", tmp);
    strcpy((*tabela)[*cadastrados]->nome, tmp);

    printf("Qual categoria do livro?\n");
    scanf(" %[^\n]", tmp);
    for (int i = 0; tmp[i]; i++)
        {
            tmp[i] = tolower(tmp[i]);
        }
    strcpy((*tabela)[*cadastrados]->categoria, tmp);

    printf("Qual o ano de publicação?\n");
    scanf("%d", &ano);

    (*tabela)[*cadastrados]->ano = ano;

    (*tabela)[*cadastrados]->status = 1;

    *cadastrados += 1;

    printf("====================================\n");
    printf("Livro cadastrado com sucesso!\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

void remove_livro(livros **vet, int cadastrados){
    system("clear");
    int id;
    printf("Digite o ID do livro que deseja remover\n");
    scanf("%d", &id);
    if(id < cadastrados && vet[id] != NULL){
        if (vet[id]->status == 0)
        {
            printf("Livro está emprestado para o aluno de ID: %d! Operação cancelada!\n", vet[id]->aluno);
        }
        else{
            free(vet[id]);
            vet[id] = NULL;
            printf("Livro removido do sistema!\n");
        }
    }
    else{
        printf("Livro não está no sistema, verifique o ID! Operação cancelada\n");
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

void lista_livro(livros **vet, int cadastrados, alunos **pessoas){
    system("clear");
    for (int i = 0; i < cadastrados; i++)
    {
        if (vet[i] != NULL)
        {
            printf("====================================\n");
            printf("ID: %d\nNOME: %s\nCATEGORIA: %s\nANO: %d\n", i, vet[i]->nome, vet[i]->categoria, vet[i]->ano);
            if (vet[i]->status == 0)
            {
                printf("STATUS: Emprestado para o aluno de matrícula: %s\n", pessoas[vet[i]->aluno]->matricula);
            }
            else{
                printf("STATUS: Disponível\n");
            }
            
        }
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
    
}

void busca_livro(livros **vet, int cadastrados){
    system("clear");
    int escolha, id;
    char tmp[20];
    printf("1- Buscar por ID\n2- Buscar por categoria\n");
    scanf("%d", &escolha);
    if (escolha == 1)   
    {
        printf("Qual o ID procurado?\n");
        scanf("%d", &id);
        if (id > (cadastrados - 1))
        {
            printf("Livro não está no sistema!\n");
        }
        else{
            system("clear");
            printf("====================================\n");
            printf("Livro encontrado!\nID: %d\nNOME: %s\nCATEGORIA: %s\nANO: %d\n", id, vet[id]->nome, vet[id]->categoria, vet[id]->ano);
            if (vet[id]->status == 0)
            {
                printf("STATUS: Emprestado para o aluno de ID: %d\n", vet[id]->aluno);
            }
            else{
                printf("STATUS: Disponível\n");
            }
        }
        
    }
    else if(escolha == 2)
    {
        printf("Escreva a categoria desejada:\n");
        scanf(" %[^\n]", tmp);
        for (int i = 0; tmp[i]; i++)
        {
            tmp[i] = tolower(tmp[i]);
        }
        system("clear");
        for (int i = 0; i < cadastrados; i++)
        {
            if (strcmp(tmp, vet[i]->categoria) == 0)
            {
                printf("====================================\n");
                printf("NOME: %s\nANO: %d\nID: %d\n", vet[i]->nome, vet[i]->ano, i);
                if (vet[i]->status == 0)
                {
                printf("STATUS: Emprestado\n");
                }
                else{
                printf("STATUS: Disponível\n");
                }
            }   
        }
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

void empresta_livro(livros **vet, alunos **pessoas, int cadastrados, int totalalunos){
    system("clear");
    int escolha, id, aluno;
    printf("1- EMPRESTAR\n2- DEVOLVER\n");
    scanf("%d", &escolha);
    if (escolha == 1)
    {
        printf("Qual ID do livro que será emprestado?\n");
        scanf("%d", &id);
        if (id < (cadastrados) && vet[id] != NULL && vet[id]->aluno == -1)
        {
            printf("Qual ID do aluno que ficará com o livro?\n");
            scanf("%d", &aluno);
            if (aluno < (totalalunos) && pessoas[aluno] != NULL)
            {
                pessoas[aluno]->livro = id;
                vet[id]->aluno = aluno;
                vet[id]->status = 0;
                pessoas[aluno]->pendencias += 1;
                printf("Livro emprestado!\n");
            }
            else{
                printf("Aluno não está no sistema\n");
            }
        }
        else if (id < (cadastrados) && vet[id] != NULL && vet[id]->aluno != -1)
        {
            printf("Livro já está emprestado para o aluno de ID: %d\n", vet[id]->aluno);
        }
        else{
            printf("Livro não está no sistema, verifique ID!\n");
        }
    }
    else if (escolha == 2)
    {
        printf("Qual ID do livro que será devolvido?\n");
        scanf("%d", &id);
        if (id < (cadastrados) && vet[id] != NULL && vet[id]->aluno != -1)
        {
            vet[id]->status = 1;
            pessoas[vet[id]->aluno]->livro = -1;
            pessoas[vet[id]->aluno]->pendencias -= 1;
            vet[id]->aluno = -1;
            printf("Livro devolvido à biblioteca com sucesso!\n");
        }
        else{
            printf("Livro não está no sistema, verifique ID!\n");
        }
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}
