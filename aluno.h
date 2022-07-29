#ifndef ALUNO_H
#define ALUNO_H
#include "dados.h"
///Funcao que cadastra um aluno.
///
///Cadastra, verifica se já existe e faz o aumento no número de turmas e cadastrados.
///@param tabela serve para aumentar o número de turmas cadastradas, assim, aumentando o número de vagas.
///@param vet vetor de alunos.
///@param matriculados total de alunos que já forma cadastrados.
///@param turmas total de turmas no sistema.
void novo_cadastro_aluno(alunos ***tabela, alunos **vet, int *matriculados, int *turmas);
///Funcao que remove um aluno.
///
///Remove um aluno da tabela de alunos, verifica se o aluno existe e se não possui nenhum emprestimo.
///@param vet vetor de alunos.
///@param matriculados total de alunos que já forma cadastrados.
void remove_aluno(alunos **vet, int matriculados);
///Funcao que imprime os dados de todos os alunos.
///
///Imprime os dados de todos os alunos.
///@param vet vetor de alunos.
///@param quantidade total de alunos que já forma cadastrados.
void lista_aluno(alunos **vet, int quantidade);
///Funcao de busca de aluno.
///
///Busca um aluno na tabela de alunos, verifica se o aluno existe.
///@param vet vetor de alunos.
///@param cadastrados total de alunos que já forma cadastrados.
void busca_aluno(alunos **vet, int cadastrados);

#endif