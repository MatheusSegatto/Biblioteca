#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    char matricula[12]; //Matrícula do cefet tem 11 caracteres ex: 2112227GCOM
    int livro;
    //int teste;
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
void cadastro_aluno(alunos *p){
    char nome[50];

    printf("Qual o nome do aluno?\n");
    scanf(" %[^\n]", nome);
    strcpy(p->nome, nome);
    return;
}


//? alunos * pesquisa_aluno(int sw, char *procurado,alunos *cab, alunos **ant){}


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
    //Alocando vetor de alunos
    alunos **vetalunos = (alunos **)(malloc(sizeof(alunos *)));
    vetalunos[0] = (alunos *)malloc(sizeof(alunos));
    //vetalunos[i]->nome;
    //chamada -> rm_aluno(v[i])
    //rm_aluno(struct aluno *p)
    //p->nome = "novonome";
    ///p = NULL -> mesma coisa que p = malloc(0*sizeof(alunos));

    int matriculados = 0;
    vetalunos = realloc(vetalunos, sizeof(35 * sizeof(alunos *)));
    for (size_t i = 1; i < 35; i++)
    {
        //a++;
        //vetalunos = realloc(vetalunos, sizeof((a) * sizeof(alunos *)));
        vetalunos[i] = (alunos *)(malloc(sizeof(alunos)));
    }
    //Alocando vetor de livros
    livros **vetlivros = (livros **)(malloc(sizeof(livros *)));
    vetlivros[0] = (livros *)malloc(sizeof(livros));
    vetlivros = realloc(vetlivros, sizeof(50 * sizeof(livros *)));
    for (size_t i = 1; i < 50; i++)
    {
        //a++;
        //vetlivros = realloc(vetlivros, sizeof((a) * sizeof(livros *)));
        vetlivros[i] = (livros *)malloc(sizeof(livros));
    }
    

    //vetalunos[3]->teste = 56;

    int cadastrados = 0, turmas = 1;
    int escolha;
    while (escolha != 5)
    {
        printf("MENU:\n1- Cadastrar aluno\n2- Cadastrar livro\n3- Cadastrar recurso\n4- Pesquisa\n5- Sair\n");
        scanf("%d", &escolha);
        if (escolha == 1)
        {
            matriculados +=1;
            if (matriculados > 35)
            {
                //Aumentar vetor de alunos
                turmas += 1;
                vetalunos = realloc(vetalunos, sizeof((35 * turmas) * sizeof(alunos *)));
            }
            //Perguntar matrícula antes de entrar na função
            printf("Qual a matrícula do aluno?\n");
            char matricula[12];//Matrícula do cefet tem 11 caracteres ex: 2112227GCOM
            scanf("%s", matricula);
            int status = 0;
            //Verficando se aluno já está matriculado
            for (int i = 0; i < cadastrados; i++)
            {
                //TODO Como faria pra entrar na função sem modificar quantidade de cadastrados
                if (strcmp(matricula, vetalunos[i]->matricula) == 0)
                {
                    printf("Aluno já cadastrado! ID: %d\n", i);
                    status = 1;
                    break;
                }
            }
            if(status == 0)
            {
            strcpy(vetalunos[cadastrados]->matricula, matricula);
            cadastro_aluno(vetalunos[cadastrados]);
            cadastrados += 1;
            }
        }
        else if (escolha == 2)
        {
            //cadastro_livro();
        }
        else if (escolha == 3)
        {
            //cadastro_recurso();
        }
        else if (escolha == 4)
        {
            //pesquisa();
        }
    }
    printf("%s\n", vetalunos[2]->nome);
    
    return 0;
}
