#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "model/sistema.h"

// Controller para gerenciar a inicializacao do sistema
void configuracaoInicialController(Sistema *sistema);
void carregarTodosOsDadosController(Sistema *sistema);
void liberarTodaMemoriaController(Sistema *sistema);

#endif
