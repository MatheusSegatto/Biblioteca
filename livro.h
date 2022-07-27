#ifndef LIVRO_H
#define LIVRO_H
#include "dados.h"

void cadastro_livro(livros ***tabela, int *cadastrados, int *caixas);
void remove_livro(livros **vet, int cadastrados);
void lista_livro(livros **vet, int cadastrados, alunos **pessoas);
void busca_livro(livros **vet, int cadastrados);
void empresta_livro(livros **vet, alunos **pessoas, int cadastrados, int totalalunos);

#endif