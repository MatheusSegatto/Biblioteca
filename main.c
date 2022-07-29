#include "dados.h"
#include "livro.h"
#include "aluno.h"
#include "recurso.h"
#include "cripto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    //Alocando vetor de alunos
    //vetalunos[0] = (alunos *)malloc(sizeof(alunos));
    //vetalunos[i]->nome;
    //chamada -> rm_aluno(v[i])
    //rm_aluno(struct aluno *p)
    //p->nome = "novonome";
    ///p = NULL -> mesma coisa que p = malloc(0*sizeof(alunos));
    char senha[20];
    int matriculados = 0;
    alunos **vetalunos = (alunos **)malloc(sizeof(alunos *));
    vetalunos = realloc(vetalunos, 35 * sizeof(alunos *));
    for (size_t i = 0; i < 35; i++)
    {
        vetalunos[i] = (alunos *)malloc(sizeof(alunos));
    }

    //Alocando vetor de livros
    livros **vetlivros = (livros **)(malloc(sizeof(livros *)));
    //vetlivros[0] = (livros *)malloc(sizeof(livros));
    vetlivros = realloc(vetlivros, 50 * sizeof(livros *));
    for (size_t i = 0; i < 50; i++)
    {
        vetlivros[i] = (livros *)malloc(sizeof(livros));
    }

    recurso *cab = (recurso *)malloc(sizeof(recurso));
    cab->prox = NULL;


    //vetalunos[3]->teste = 56;
    int turmas = 1, escolha = 1, caixas = 1, sistema_livros = 0;
    import(&vetalunos, &vetlivros, vetalunos, vetlivros, cab, &matriculados, &sistema_livros, &turmas, &caixas, senha);
    //printf("%s", vetalunos[0]->nome);
    while (escolha != 0) //Menu Principal
    {
        system("clear");
        printf("MENU:\n1- Seção aluno\n2- Seção livro\n3- Seção recurso\n0- Sair\n");
        scanf("%d", &escolha);
        if (escolha == 1)
        {
            while(escolha != 0){ //Menu Aluno
                system("clear");
                printf("MENU:\n1- Cadastrar aluno\n2- Remover aluno\n3- Listar alunos\n4- Pesquisar aluno\n0- Sair\n");
                scanf("%d", &escolha);
                if(escolha == 1){
                    novo_cadastro_aluno(&vetalunos, vetalunos, &matriculados, &turmas);
                }
                else if (escolha == 2)
                {
                    remove_aluno(vetalunos, matriculados);
                }
                else if (escolha == 3)
                {
                    lista_aluno(vetalunos, matriculados);
                }
                else if (escolha == 4)
                {
                    busca_aluno(vetalunos, matriculados);
                }
            }
            escolha = 1;
        }
        else if (escolha == 2)
        {
            while (escolha != 0)
            {
                system("clear");
                printf("1- Cadastrar livro\n2- Remover livro\n3- Listar livros\n4- Buscar livro\n5- Empréstimo de livro\n0- Sair\n");
                scanf("%d", &escolha);
                if (escolha == 1)
                {
                    cadastro_livro(&vetlivros, &sistema_livros, &caixas);
                }
                else if (escolha == 2)
                {
                    remove_livro(vetlivros, sistema_livros);
                }
                else if (escolha == 3)
                {
                    lista_livro(vetlivros, sistema_livros, vetalunos);
                }
                else if (escolha == 4)
                {
                    busca_livro(vetlivros, sistema_livros, vetalunos);
                }
                else if (escolha == 5)
                {
                    empresta_livro(vetlivros, vetalunos, sistema_livros, matriculados);
                }
            }
            escolha = 1;
        }
        else if (escolha == 3)
        {
            while (escolha != 0)
            {
                system("clear");
                printf("1- Cadastrar recurso\n2- Remover recurso\n3- Listar recurso\n4- Buscar recurso\n5- Ocupar/desocupar recurso\n0- Sair\n");
                scanf("%d", &escolha);
                if (escolha == 1)
                {
                    cadastro_recurso(cab);
                }
                else if (escolha == 2)
                {
                    remove_recurso(cab);
                }
                else if (escolha == 3)
                {
                    lista_recurso(cab, vetalunos);
                }
                else if (escolha == 4)
                {
                    busca_recurso_menu(cab, vetalunos);
                }
                else if (escolha == 5)
                {
                    ocupa_recurso(cab, vetalunos, matriculados);
                }
                
            }
            escolha = 1;
        }
    }
    //printf("%s\n", vetalunos[0]->nome);
    export_data(vetalunos, vetlivros, cab, matriculados, sistema_livros, turmas, caixas, senha);
    free(vetalunos);
    free(vetlivros);
    return 0;
}
