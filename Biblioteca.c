#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *nome;
    char *matricula;
    int livro;
} alunos;

typedef struct
{
    char *nome;
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



void cadastro_aluno(/*int *n, alunos **aluno*/){
    //*n = *n + 1;
    //alunos *aluno = (alunos*)realloc(*aluno, (*n * sizeof(alunos)))

} 
void cadastro_livro(){

}

void cadastro_recurso(){

}
void pesquisa(){

}

void menu(){
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
}
int main(int argc, char const *argv[])
{
    int n_alunos = 0;
    alunos *aluno;
    cadastro_aluno(&n_alunos, &aluno);
    printf("n_alunos: %d\n", n_alunos);
    menu();
    return 0;
}
