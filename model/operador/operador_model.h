#ifndef OPERADOR_MODEL_H
#define OPERADOR_MODEL_H

#include "model/sistema.h"

// Salva a lista de operadores conforme o modo de armazenamento escolhido
void salvarOperadores(Sistema *sistema);

// Carrega os operadores do arquivo para a memoria ao iniciar o sistema
void carregarOperadores(Sistema *sistema);

// Libera a memoria usada pela lista de operadores
void liberarMemoriaOperadores(Sistema *sistema);

#endif
