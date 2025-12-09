#ifndef PRODUTORA_MODEL_H
#define PRODUTORA_MODEL_H

#include "model/sistema.h"

// Salva os dados da produtora conforme o modo de armazenamento escolhido
void salvarProdutora(Sistema *sistema);

// Carrega os dados da produtora do arquivo para a memoria
void carregarProdutora(Sistema *sistema);

// Libera a memoria alocada para os dados da produtora
void liberarMemoriaProdutora(Sistema *sistema);

#endif
