#ifndef CLIENTE_MODEL_H
#define CLIENTE_MODEL_H

#include "model/sistema.h"

// Salva a lista de clientes no armazenamnto escolhido
void salvarClientes(Sistema *sistema);

// Carrega os dados dos clientes do arquivo para a memória.
void carregarClientes(Sistema *sistema);

// Libera a memoria alocada para a lista de clientes.
void liberarMemoriaClientes(Sistema *sistema);

#endif
