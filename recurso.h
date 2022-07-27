#ifndef RECURSO_H
#define RECURSO_H
#include "dados.h"

void cadastro_recurso(recurso *cab);
void remove_recurso(recurso *cab);
void lista_recurso(recurso *cab, alunos **pessoas);
void busca_recurso_menu(recurso *cab, alunos **pessoas);
void ocupa_recurso(recurso *cab, alunos **pessoas, int totalalunos);

#endif