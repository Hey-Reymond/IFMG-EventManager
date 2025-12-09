#ifndef TRANSACAO_MODEL_H
#define TRANSACAO_MODEL_H
#include "model/sistema.h"

// Salva a lista de transacoes no modo de armazenamnto escolhido
void salvarTransacoes(Sistema *sistema);

// Carrega as transacoes do arquivo para a memoria
void carregarTransacoes(Sistema *sistema);

// Libera a memoria alocada para a trasancoes
void liberarMemoriaTransacoes(Sistema *sistema);

 // Para salvar saldo do caixa
void salvarCaixa(Sistema *sistema);

 // Para carregar osaldo do caixa
void carregarCaixa(Sistema *sistema);
#endif