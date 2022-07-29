#ifndef LIVRO_H
#define LIVRO_H
#include "dados.h"

///Funcao que cadastra um livro.
///
///Cadastra, verifica se já existe e faz o aumento no número de caixas e cadastrados.
///@param tabela serve para aumentar o número de caixas cadastradas, assim, aumentando o número de vagas.
///@param cadastrados total de livros que já forma cadastrados.
void cadastro_livro(livros ***tabela, int *cadastrados, int *caixas);
///Funcao que remove um livro.
///
///Remove um livro da tabela de livros, verifica se o livro existe e se não possui nenhum emprestimo.
///@param vet vetor de livros.
///@param cadastrados total de livros que já forma cadastrados.
void remove_livro(livros **vet, int cadastrados);
///Funcao que imprime os dados de todos os livros.
///
///Imprime os dados de todos os livros.
///@param vet vetor de livros.
///@param cadastrados total de livros que já forma cadastrados.
///@param pessoas vetor de alunos para verificar a matricula do aluno que pegou emprestado o livro.
///@note A matrícula do aluno que aparece na listagem, ao invés do ID.
void lista_livro(livros **vet, int cadastrados, alunos **pessoas);
///Funcao de busca de livro.
///
///Busca um livro na tabela de livros, verifica se o livro existe.
///@param vet vetor de livros.
///@param cadastrados total de livros que já forma cadastrados.
///@param pessoas vetor de alunos para verificar a matricula do aluno que pegou emprestado o livro.
///@note A matrícula do aluno que aparece na busca, ao invés do ID.
void busca_livro(livros **vet, int cadastrados, alunos **pessoas);
///Função responsável por emprestar e devolver um livro.
///
///Recebe o ID do livro e o ID do aluno, verifica se o livro existe, se o aluno existe e somente empresta se o livro estiver disponível.
///@param vet vetor de livros.
///@param pessoas vetor de alunos para realizar o emprestimo.
///@param cadastrados total de livros que já forma cadastrados.
///@param totalalunos total de alunos que já forma cadastrados.
void empresta_livro(livros **vet, alunos **pessoas, int cadastrados, int totalalunos);

#endif