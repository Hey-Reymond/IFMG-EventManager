#ifndef EQUIPE_INTERNA_MODEL_H
#define EQUIPE_INTERNA_MODEL_H

#include "model/sistema.h"

// Salva os dados da equipe interna no modo de armazenamento escolhido
void salvarEquipeInterna(Sistema *sistema);

// Carrega os dados da equipe interna do arquivo para a memoria
void carregarEquipeInterna(Sistema *sistema);

// Libera a memoria alocada para a lista da equipe interna
void liberarMemoriaEquipe(Sistema *sistema);

#endif
