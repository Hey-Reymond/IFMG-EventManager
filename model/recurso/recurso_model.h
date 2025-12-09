#ifndef RECURSO_MODEL_H
#define RECURSO_MODEL_H

#include "model/sistema.h"

// Salva a lista de recursos no formato de armazenamento escolhido
void salvarRecursos(Sistema *sistema);

// Carrega os recursos do arquivo para a memoria
void carregarRecursos(Sistema *sistema);

// Libera a memoria alocada para os recursos
void liberarMemoriaRecursos(Sistema *sistema);

#endif
