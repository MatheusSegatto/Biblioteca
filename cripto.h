#ifndef CRIPTO_H
#define CRIPTO_H
#include "dados.h"

///Funcao de exportação de dados.
///
///Exporta os dados de todos os alunos, livros e recursos para um arquivo.
///@param vetalunos vetor de alunos.
///@param vetlivros vetor de livros.
///@param cab cabeça da lista de recursos.
///@param matriculados total de alunos que já forma cadastrados.
///@param sistema_livros total de livros no sistema.
///@param turmas total de turmas no sistema.
///@param caixas total de caixas no sistema.
///@param senha senha do usuário.
///@note O arquivo é salvo criptografado.
void export_data(alunos **vetalunos, livros **vetlivros, recurso *cab, int matriculados, int sistema_livros, int turmas, int caixas, char *senha);
///Funcao de importação de dados.
///
///Importa os dados de todos os alunos, livros e recursos de um arquivo criptografado.
///@param tab_alunos ponteiro para a tabela de alunos.
///@param tab_livros ponteiro para a tabela de livros.
///@param vetalunos vetor de alunos.
///@param vetlivros vetor de livros.
///@param cab cabeça da lista de recursos.
///@param matriculados total de alunos que já forma cadastrados.
///@param sistema_livros total de livros no sistema.
///@param turmas total de turmas no sistema.
///@param caixas total de caixas no sistema.
///@param senha senha do usuário.
///@note Caso o arquivo não exista, o programa pedirá para o usuário criar uma nova senha.
///@warning Caso o usuário não tenha a senha correta, não será possível importar os dados.
void import(alunos ***tab_alunos, livros ***tab_livros, alunos **vetalunos, livros **vetlivros, recurso *cab, int *matriculados, int *sistema_livros, int *turmas, int *caixas, char *senha);

#endif