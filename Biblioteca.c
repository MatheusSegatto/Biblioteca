#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    char categoria[20];
    int status; // Disponivel = 1 | Emprestado = 0
    int aluno;
} livros;

typedef struct
{
    int ID; // Nesse caso, como é inserido manualmente, tenho que deixar na struct
    int status; //Talvez possa usar char, pois não precisa ser muito grande
    int aluno;

} recurso;


void cadastro_aluno(alunos *p){
    char nome[50];

    printf("Qual o nome do aluno?\n");
    scanf(" %[^\n]", nome);
    strcpy(p->nome, nome);
    //printf("%s", p->nome);
    //p->livro = -1;
    return;
}

void remove_aluno(alunos **vet){
    int id = 0;
    printf("Digite o ID do aluno que quer remover\n");
    scanf("%d", &id);
    //TODO Verificar se possui algo emprestado
    //printf("%p\n", vet[id]);
    free(vet[id]);
    vet[id] = NULL;
}

void lista_aluno(alunos **vet, int quantidade){
    for (int i = 0; i < quantidade; i++)
    {
        if (vet[i] != NULL)
        {
            printf("NOME: %s\nID: %d\nMATRICULA: %s\n", vet[i]->nome, i, vet[i]->matricula); //Por algum motivo, esse print tá começando na posição errada v[1] é igual a o que deveria ser v[0]
        }
    }
    
}
void busca_aluno(alunos **vet, int cadastrados){
    printf("Qual ID do aluno procurado?\n");
    int id;
    scanf("%d", &id);
    if (id > (cadastrados - 1))
    {
        printf("Aluno não existe no sistema");
    }
    else
    {
        printf("Aluno encontrado!\nNOME: %s\nMATRICULA: %s\n", vet[id]->nome, vet[id]->matricula);
    }
}

// alunos * pesquisa_aluno(int sw, char *procurado,alunos *cab, alunos **ant){}


void cadastro_livro(livros ***tabela, livros **vet, int *cadastrados, int *caixas){
    //Para alterar, usar *caixas
    if (*cadastrados > (*caixas * 50))
    {
        *caixas += 1;
        tabela = realloc(tabela, (50 * (*caixas)) * sizeof(livros *)); //
        for (size_t i = (50 * ((*caixas) - 1)); i < (50 * (*caixas)); i++)
        {
            *tabela[i] = (livros *)malloc(sizeof(livros)); //É *tabela msm? Quando coloquei só "tabela" recebi um warning do gcc
        }
    }
    char tmp[20];
    int ano;
    printf("Qual o nome do livro?\n");
    scanf(" %[^\n]", tmp);
    strcpy(vet[*cadastrados]->nome, tmp);

    printf("Qual categoria do livro?\n");
    scanf(" %[^\n]", tmp);
    for (int i = 0; tmp[i]; i++)
        {
            tmp[i] = tolower(tmp[i]);
        }
    strcpy(vet[*cadastrados]->categoria, tmp);

    printf("Qual o ano de publicação?\n");
    scanf("%d", &ano);

    vet[*cadastrados]->ano = ano;

    vet[*cadastrados]->status = 1;

    *cadastrados += 1;
}

void remove_livro(livros **vet){
    int id;
    printf("Digite o ID do livro que deseja remover\n");
    scanf("%d", &id);
    free(vet[id]);
    vet[id] = NULL;
}

void lista_livro(livros **vet, int cadastrados){
    for (int i = 0; i < cadastrados; i++)
    {
        if (vet[i] != NULL)
        {
            printf("ID: %d\nNOME: %s\nCATEGORIA: %s\nANO: %d\n", i, vet[i]->nome, vet[i]->categoria, vet[i]->ano);
            if (vet[i]->status == 0)
            {
                printf("STATUS: Emprestado para o aluno de ID: %d\n", vet[i]->aluno);
            }
            else{
                printf("STATUS: Disponível\n");
            }
            
        }
    }
    
}
void busca_livro(livros **vet, int cadastrados){
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
        for (int i = 0; i < cadastrados; i++)
        {
            if (strcmp(tmp, vet[i]->categoria) == 0)
            {
                printf("NOME: %s\nID: %d\n", vet[i]->nome, i);
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
}

void empresta_livro(livros **vet, alunos **pessoas, int cadastrados, int totalalunos){
    int escolha, id, aluno;
    printf("1- EMPRESTAR\n2- DEVOLVER\n");
    scanf("%d", &escolha);
    if (escolha == 1)
    {
        printf("Qual ID do livro que será emprestado?\n");
        scanf("%d", &id);
        if (id < (cadastrados - 1) && vet[id] != NULL)//Talvez de problema verificar se é NULL se a posição for inválida
        {
            printf("Qual ID do aluno que ficará com o livro?\n");
            scanf("%d", &aluno);
            if (aluno < (totalalunos - 1) && pessoas[id] != NULL)
            {
                pessoas[aluno]->livro = id;
                vet[id]->aluno = aluno;
                vet[id]->status = 0;
            }
            else{
                printf("Aluno não está no sistema\n");
            }
        }
        else{
            printf("Livro não está no sistema, verifique ID!\n");
        }
    }
    else if (escolha == 2)
    {
        printf("Qual ID do livro que será devolvido?\n");
        scanf("%d", &id);
        if (id > (cadastrados - 1) || vet[id] == NULL)
        {
            printf("Livro não está no sistema, verifique ID!\n");
        }
        else{
            vet[id]->status = 1;
            pessoas[vet[id]->aluno]->livro = -1;
            vet[id]->aluno = -1;
        }
    }
    
    
}

int main(int argc, char const *argv[])
{
    //Alocando vetor de alunos
    alunos **vetalunos = (alunos **)malloc(sizeof(alunos *));
    //vetalunos[0] = (alunos *)malloc(sizeof(alunos));
    //vetalunos[i]->nome;
    //chamada -> rm_aluno(v[i])
    //rm_aluno(struct aluno *p)
    //p->nome = "novonome";
    ///p = NULL -> mesma coisa que p = malloc(0*sizeof(alunos));

    int matriculados = 0;
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
    //vetalunos[3]->teste = 56;
    int turmas = 1, escolha = 1, caixas = 1, sistema_livros = 0;
    while (escolha != 0) //Menu Principal
    {
        printf("MENU:\n1- Seção aluno\n2- Seção livro\n3- Seção recurso\n0- Sair\n");
        scanf("%d", &escolha);
        if (escolha == 1)
        {
            while(escolha != 0){ //Menu Aluno
                printf("MENU:\n1- Cadastrar aluno\n2- Remover aluno\n3- Listar alunos\n4- Pesquisar aluno\n0- Sair\n");
                scanf("%d", &escolha);
                if(escolha == 1){
                    //Perguntar matrícula antes de entrar na função
                    printf("Qual a matrícula do aluno?\n");
                    char matricula[12];//Matrícula do cefet tem 11 caracteres ex: 2112227GCOM
                    scanf("%s", matricula);
                    int status = 0;
                    //Verficando se aluno já está matriculado
                    for (int i = 0; i < matriculados; i++)
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
                    
                    if ((matriculados + 1) > (35 * turmas))
                    {
                        //Aumentar vetor de alunos
                        turmas += 1;
                        vetalunos = realloc(vetalunos, (35 * turmas) * sizeof(alunos *));
                        for (size_t i = (35 * (turmas - 1)); i < (35 * turmas); i++)
                        {
                            vetalunos[i] = (alunos *)malloc(sizeof(alunos));
                        }
                        
                    }
                    strcpy(vetalunos[matriculados]->matricula, matricula);
                    cadastro_aluno(vetalunos[matriculados]);
                    matriculados += 1;
                    }
                }
                else if (escolha == 2)
                {
                    remove_aluno(vetalunos);
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
                printf("1- Cadastrar livro\n2- Remover livro\n3- Listar livros\n4- Buscar livro\n5- Emprestar livro\n0- Sair\n");
                scanf("%d", &escolha);
                if (escolha == 1)
                {
                    cadastro_livro(&vetlivros, vetlivros, &sistema_livros, &caixas);
                }
                else if (escolha == 2)
                {
                    remove_livro(vetlivros);
                }
                else if (escolha == 3)
                {
                    lista_livro(vetlivros, sistema_livros);
                }
                else if (escolha == 4)
                {
                    busca_livro(vetlivros, sistema_livros);
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
            //cadastro_recurso();
        }
        else if (escolha == 4)
        {
            //pesquisa();
        }
    }
    //printf("%s\n", vetalunos[0]->nome);
    
    return 0;
}
