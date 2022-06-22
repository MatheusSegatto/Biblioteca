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
    char status; // Disponivel = 1 | Emprestado = 0

} livros;

typedef struct
{
    int ID; // Nesse caso, como é inserido manualmente, tenho que deixar na struct
    char status;
    int aluno;

} recurso;



void cadastro_aluno(int *n, alunos **aluno){
    *n = *n + 1;
    //alunos *aluno = (alunos*)realloc(*aluno, (*n * sizeof(alunos)))

} 
int main(int argc, char const *argv[])
{
    int n_alunos = 0;
    alunos *aluno;
    cadastro_aluno(&n_alunos, &aluno);
    printf("n_alunos: %d\n", n_alunos);
    return 0;
}
