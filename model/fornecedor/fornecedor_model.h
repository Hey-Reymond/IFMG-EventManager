#ifndef FORNECEDOR_MODEL_H
#define FORNECEDOR_MODEL_H

#include "model/sistema.h"

// Salva a lista de fornecedores no formato escolido
void salvarFornecedores(Sistema *sistema);

// Carrega os dados dos fornecedores de um arquivo para a memoria
void carregarFornecedores(Sistema *sistema);

// Libera a memoria alocada para a lista de fornecedores
void liberarMemoriaFornecedores(Sistema *sistema);

#endif
