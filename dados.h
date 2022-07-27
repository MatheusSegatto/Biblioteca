#ifndef DADOS_H
#define DADOS_H

typedef struct
{
    int livro;
    int recurso;
    int pendencias;
    char nome[50];
    char matricula[12]; //Matrícula do cefet tem 11 caracteres ex: 2112227GCOM
} alunos;

typedef struct
{
    int ano; //Para fins de otimização de memória, pode ser uma boa idéia colocar um tipo menor
    int status; // Disponivel = 1 | Emprestado = 0
    int aluno;
    char nome[50];
    char categoria[20];
} livros;

typedef struct recurso
{
    int ID; // Nesse caso, como é inserido manualmente, tenho que deixar na struct
    int status; //Livre = 1 | Emprestado = 0
    int aluno;
    struct recurso *prox;
    char tipo[11]; //sala, computador ou armário
} recurso;

#endif