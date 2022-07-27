#ifndef ALUNO_H
#define ALUNO_H
#include "dados.h"

void novo_cadastro_aluno(alunos ***tabela, alunos **vet, int *matriculados, int *turmas);
void remove_aluno(alunos **vet, int matriculados);
void lista_aluno(alunos **vet, int quantidade);
void busca_aluno(alunos **vet, int cadastrados);

#endif