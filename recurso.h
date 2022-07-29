#ifndef RECURSO_H
#define RECURSO_H
#include "dados.h"

///Funcao que cadastra um recurso.
///
///Cadastra e verifica se já existe utilizando a função busca_recurso() antes de cadastrar.
///@param cab cabeca da lista de recursos.
///@see busca_recurso()
void cadastro_recurso(recurso *cab);
///Funcao que remove um recurso.
///
///Remove um recurso da lista de recursos, verifica se o recurso existe utilizando a função busca_recurso() e se não possui nenhum emprestimo.
///@param cab cabeca da lista de recursos.
void remove_recurso(recurso *cab);
///Funcao que imprime os dados de todos os recursos.
///
///Imprime os dados de todos os recursos.
///@param cab cabeca da lista de recursos.
///@param pessoas vetor de alunos.
///@note A matrícula do aluno que aparece na listagem, ao invés do ID.
void lista_recurso(recurso *cab, alunos **pessoas);
///Funcao de busca de recurso.
///
///Busca um recurso na lista de recursos, verifica se o recurso existe utilizando a função busca_recurso().
///@param cab cabeca da lista de recursos.
///@param pessoas vetor de alunos.
///@note A matrícula do aluno que aparece na busca, ao invés do ID.
void busca_recurso_menu(recurso *cab, alunos **pessoas);
///Funcao de ocupação de recurso.
///
///Recebe o ID do recurso e o ID do aluno, verifica se o recurso existe utilizando a função busca_recurso(), se o aluno existe e somente ocupa se o recurso estiver disponível.
///@param cab cabeca da lista de recursos.
///@param pessoas vetor de alunos.
//@param totalalunos total de alunos que já forma cadastrados.
void ocupa_recurso(recurso *cab, alunos **pessoas, int totalalunos);
///Funçao que retorna um recurso.
///
///Recebe um ID do recurso para verificar se o recurso existe e retorna o recurso ou, se não existir, retorna NULL.
///@param cab cabeca da lista de recursos.
///@param id ID do recurso.
///@param ant serve como auxiliar para percorrer a lista.
recurso * busca_recurso(recurso *cab, int id, recurso **ant);

#endif