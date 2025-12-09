#ifndef EVENTO_MODEL_H
#define EVENTO_MODEL_H
#include "model/sistema.h"

// Salva os dados do evento no modo de armazenamento escolhido
void salvarEventos(Sistema *sistema);

// Carrega os dados do evento do arquivo para a memoria
void carregarEventos(Sistema *sistema);

// Libera a memoria alocada para a lista do evento
void liberarMemoriaEventos(Sistema *sistema);
#endif