#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//TODO Mostrar matrícula do aluno que pegou livro emprestado na listagem de livros
typedef struct
{
    char nome[50];
    char matricula[12]; //Matrícula do cefet tem 11 caracteres ex: 2112227GCOM
    int livro;
    int recurso;
} alunos;

typedef struct
{
    char nome[50];
    int ano; //Para fins de otimização de memória, pode ser uma boa idéia colocar um tipo menor
    char categoria[20];
    int status; // Disponivel = 1 | Emprestado = 0
    int aluno;
} livros;

typedef struct recurso
{
    int ID; // Nesse caso, como é inserido manualmente, tenho que deixar na struct
    int status; //Livre = 1 | Emprestado = 0
    int aluno;
    char tipo[15]; //sala, computador ou armário
    struct recurso *prox;
} recurso;

void novo_cadastro_aluno(alunos ***tabela, alunos **vet, int *matriculados, int *turmas){
    system("clear");
    char matricula[12];
    printf("Qual a matrícula do aluno que será cadastrado?\n");
    scanf(" %[^\n]", matricula);
    int status = 0;
    for (int i = 0; i < *matriculados; i++)
    {
        if ((*tabela) != NULL && strcmp((*tabela)[i]->matricula, matricula) == 0)
        {
            printf("Aluno já cadastrado! Operação cancelada\n");
            status = 1;
            break;
        }
    }
    if (status == 0)
    {
        if ((*matriculados + 1) > ((*turmas) * 35))
        {
            *turmas += 1;
            *tabela = realloc(*tabela, (35 * (*turmas)) * sizeof(alunos *));
            for (size_t i = (35 * ((*turmas) - 1)); i < (35 * (*turmas)); i++)
            {
                (*tabela)[i] = (alunos *)malloc(sizeof(alunos));
            }
        }
        strcpy((*tabela)[*matriculados]->matricula, matricula);
        printf("Qual o nome do aluno?\n");
        scanf(" %[^\n]", (*tabela)[*matriculados]->nome); //? Será que funciona dessa forma?
        (*tabela)[*matriculados]->livro = -1;
        (*tabela)[*matriculados]->recurso = -1;
        *matriculados += 1;
        printf("Aluno Cadastrado com sucesso!\n");
        
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

void cadastro_aluno(alunos *p){
    char nome[50];

    printf("Qual o nome do aluno?\n");
    scanf(" %[^\n]", nome);
    strcpy(p->nome, nome);
    //printf("%s", p->nome);
    p->livro = -1;
    p->recurso = -1;
    return;
}

void remove_aluno(alunos **vet, int matriculados){
    system("clear");
    int id = 0;
    printf("Digite o ID do aluno que quer remover\n");
    scanf("%d", &id);
    //TODO Verificar se possui algo emprestado
    if(id < matriculados && vet[id] != NULL){

    
        if (vet[id]->livro == -1 && vet[id]->recurso == -1)
        {
            free(vet[id]);
            vet[id] = NULL;
            printf("Aluno removido do sistema!\n");
        }
        else{
            printf("O aluno possui alguma pendência com a biblioteca! Operação canceladada!\n");
        }
    }
    else{
        printf("Aluno não está no sistema!\n");
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

void lista_aluno(alunos **vet, int quantidade){
    system("clear");
    for (int i = 0; i < quantidade; i++)
    {
        if (vet[i] != NULL)
        {
            printf("====================================\n");
            printf("NOME: %s\nID: %d\nMATRICULA: %s\n", vet[i]->nome, i, vet[i]->matricula); //Por algum motivo, esse print tá começando na posição errada v[1] é igual a o que deveria ser v[0]
        }
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
    
}
void busca_aluno(alunos **vet, int cadastrados){
    system("clear");
    printf("Qual ID do aluno procurado?\n");
    int id;
    scanf("%d", &id);
    if (id < (cadastrados) && vet[id] != NULL)
    {
        printf("====================================\n");
        printf("Aluno encontrado!\nNOME: %s\nMATRICULA: %s\n", vet[id]->nome, vet[id]->matricula);
    }
    else
    {
        printf("Aluno não existe no sistema");
    }
    printf("====================================\n");
    char saida;
    printf("Pressione qualquer tecla para sair\n");
    scanf("%s", &saida);
}

// alunos * pesquisa_aluno(int sw, char *procurado,alunos *cab, alunos **ant){}


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
        for (int i = 0; i < cadastrados; i++)
        {
            if (strcmp(tmp, vet[i]->categoria) == 0)
            {
                printf("====================================\n");
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
        if (id < (cadastrados) && vet[id] != NULL)
        {
            printf("Qual ID do aluno que ficará com o livro?\n");
            scanf("%d", &aluno);
            if (aluno < (totalalunos) && pessoas[aluno] != NULL)
            {
                pessoas[aluno]->livro = id;
                vet[id]->aluno = aluno;
                vet[id]->status = 0;
                printf("Livro emprestado!\n");
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
        if (id < (cadastrados) && vet[id] != NULL && vet[id]->aluno != -1)
        {
            vet[id]->status = 1;
            pessoas[vet[id]->aluno]->livro = -1;
            vet[id]->aluno = -1;
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
        strcpy(p->tipo, "Armário");
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
            printf("Recurso ocupado! Operação cancelada\n");
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
        if (p != NULL)
        {
            printf("Qual ID do aluno que ocupará o recurso?\n");
            scanf("%d", &aluno);
            if (aluno < (totalalunos) && pessoas[aluno] != NULL)
            {
                // pessoas[aluno]->livro = id;
                // vet[id]->aluno = aluno;
                // vet[id]->status = 0;
                pessoas[aluno]->recurso = id;
                p->aluno = aluno;
                p->status = 0;
                printf("Recurso ocupado com sucesso!\n");
            }
            else{
                printf("Aluno não está no sistema\n");
            }

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

int main(int argc, char const *argv[])
{
    //Alocando vetor de alunos
    //vetalunos[0] = (alunos *)malloc(sizeof(alunos));
    //vetalunos[i]->nome;
    //chamada -> rm_aluno(v[i])
    //rm_aluno(struct aluno *p)
    //p->nome = "novonome";
    ///p = NULL -> mesma coisa que p = malloc(0*sizeof(alunos));

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
    
    return 0;
}
