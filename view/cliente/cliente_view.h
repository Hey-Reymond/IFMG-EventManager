#ifndef CLIENTE_VIEW_H
#define CLIENTE_VIEW_H

#include "model/sistema.h"

// Exibe o menu de clientes
void menuClientesView(Sistema *sistema);

// Lista todos os clientes cadastrados 
void listarClientesView(Sistema *sistema);

void mensagem_sucesso(const char *msg);
void mensagem_erro(const char *msg);
void mensagem_aviso(const char *msg);

// O Controller chama isso para preencher dados
void formulario_novo_cliente(Cliente *cliente);
int pedir_id_cliente(const char *acao); 

int menu_alterar_cliente(Cliente *c);
void atualizar_campo_cliente(Cliente *c, int opcao);
int confirmar_exclusao(const char *nome);

#endif
