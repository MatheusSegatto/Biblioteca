#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    char *matricula;
    int livro;
    struct alunos *prox;
} alunos;

typedef struct
{
    char nome[50];
    int ano; //Para fins de otimização de memória, pode ser uma boa idéia colocar um tipo menor
    char *categoria;
    int status; // Disponivel = 1 | Emprestado = 0

} livros;

typedef struct
{
    int ID; // Nesse caso, como é inserido manualmente, tenho que deixar na struct
    int status; //Talvez possa usar char, pois não precisa ser muito grande
    int aluno;

} recurso;



// void cadastro_aluno(alunos *cab){
//     char matricula[20];
//     char nome[50];
//     //Perguntar matrícula, caso exista, dizer que já existe e voltar ao menu
//     printf("Qual a matrícula do aluno?\n");
//     scanf("%s", matricula);
//     alunos *ant = NULL;
//     alunos *p = pesquisa_aluno(1, matricula, cab, &ant);
//     if (p != NULL)
//     {
//         printf("Aluno já cadastrado!\n");
//         return;
//     }
//     p = (alunos *)malloc(sizeof(alunos));
//     printf("Qual o nome do aluno?\n");
//     scanf(" %[^\n]", nome);
//     strcpy(p->nome, nome);
//     strcpy(p->matricula, matricula);
//     p->prox = cab->prox;
//     cab->prox = p;
//     printf("Aluno cadastrado com sucesso!\n");


// } 
alunos * pesquisa_aluno(int sw, char *procurado,alunos *cab, alunos **ant){

}
void cadastro_livro(){

}

void cadastro_recurso(){

}

// void menu(){
//     int escolha;
//     while (escolha != 5)
//     {
//         printf("MENU:\n1- Cadastrar aluno\n2- Cadastrar livro\n3- Cadastrar recurso\n4- Pesquisa\n5- Sair\n");
//         scanf("%d", &escolha);
//         if (escolha == 1)
//         {
//             cadastro_aluno();
//         }
//         else if (escolha == 2)
//         {
//             cadastro_livro();
//         }
//         else if (escolha == 3)
//         {
//             cadastro_recurso();
//         }
//         else if (escolha == 4)
//         {
//             pesquisa();
//         }
        
        
//     }
// }
int main(int argc, char const *argv[])
{
    alunos **vet = (alunos **)(malloc(sizeof(sizeof *)));
    vet[0] = (alunos *)malloc(sizeof(alunos));
    int a = 1;
    for (size_t i = 1; i < 35; i++)
    {
        a++; //TODO a já fica 2 antes do primeiro realloc
        vet = realloc(vet, sizeof(a * sizeof(alunos *)));
        vet[i] = (alunos *)(malloc(sizeof(alunos)));
    }
    int escolha;
    while (escolha != 5)
    {
        printf("MENU:\n1- Cadastrar aluno\n2- Cadastrar livro\n3- Cadastrar recurso\n4- Pesquisa\n5- Sair\n");
        scanf("%d", &escolha);
        if (escolha == 1)
        {
            cadastro_aluno();
        }
        else if (escolha == 2)
        {
            cadastro_livro();
        }
        else if (escolha == 3)
        {
            cadastro_recurso();
        }
        else if (escolha == 4)
        {
            pesquisa();
        }
    }
    
    return 0;
}
