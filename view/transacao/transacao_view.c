#include "transacao_view.h"
#include <stdio.h>
#include "utils/utils.h"
#include "utils/validation.h"
#include "controller/transacao/transacao_controller.h"
#include "model/recurso/recurso_model.h"
#include "view/recurso/recurso_view.h"

void menuTransacoesView(Sistema *sistema) {
    int opcao;
    do {
        limpar_tela();
        printf("+=====================================================+\n");
        printf("|             MENU FINANCEIRO / COMPRAS               |\n");
        printf("+=====================================================+\n");
        printf("| [1] Registrar Compra (Nota Fiscal)                  |\n");
        printf("| [2] Gerenciar Contas a Receber                      |\n");
        printf("| [3] Gerenciar Contas a Pagar                        |\n");
        printf("| [4] Ver Saldo do Caixa                              |\n");
        printf("+-----------------------------------------------------+\n");
        printf("| [0] Voltar                                          |\n");
        printf("+=====================================================+\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1: formularioRegistrarCompraView(sistema); break;
            case 2: gerenciarContasReceberController(sistema); break;
            case 3: gerenciarContasPagarController(sistema); break;
            case 4: verSaldoCaixaController(sistema); break;
            case 0: break;
            default: printf("Opcao invalida.\n"); break;
        }
        if (opcao != 0) pausar();
    } while (opcao != 0);
}

void formularioRegistrarCompraView(Sistema *sistema) {
    if (sistema->dados_produtora == NULL) {
        printf("\nErro: Cadastre a Produtora antes.\n");
        pausar();
        return;
    }

    float margem = sistema->dados_produtora->margem_lucro;
    float val_frete = 0;
    float val_imposto = 0;
    int qtd_total_nota = 0;
    float total_gasto_nota = 0;

    limpar_tela();
    printf("REGISTRAR COMPRA (NOTA FISCAL)\n");

    printf("Valor Total do Frete: ");
    ler_float_positivo(&val_frete);

    printf("Valor Total de Impostos: ");
    ler_float_positivo(&val_imposto);

    printf("Quantidade total de itens na nota: ");
    ler_inteiro_valido(&qtd_total_nota, 1, 10000);

    float frete_un = val_frete / qtd_total_nota;
    float imp_un = val_imposto / qtd_total_nota;

    int continuar = 1;
    while(continuar) {
        listarRecursosView(sistema);
        
        int id_rec;
        printf("\nDigite o ID do Recurso comprado: ");
        ler_inteiro_valido(&id_rec, 1, 999999);

        Recurso *r = NULL;
        for(int i=0; i < sistema->num_recursos; i++) {
            if(sistema->lista_recursos[i].codigo == id_rec) {
                r = &sistema->lista_recursos[i];
                break;
            }
        }

        if(r != NULL) {
            int qtd_item;
            float custo_item;
            
            printf("Quantidade comprada deste item: ");
            ler_inteiro_valido(&qtd_item, 1, 9999);

            printf("Preco de Custo Unitario: ");
            ler_float_positivo(&custo_item);

            float custo_final = custo_item + frete_un + imp_un;
            float novo_preco_locacao = custo_final * (margem / 100.0);

            r->quantidade_estoque += qtd_item;
            r->preco_custo = custo_item;
            r->valor_locacao = novo_preco_locacao;

            total_gasto_nota += (custo_item * qtd_item);

            printf("\nItem atualizado!\n");
            printf("Custo Final: %.2f\n", custo_final);
            printf("Novo Valor Locacao: %.2f\n", novo_preco_locacao);
        } else {
            printf("\nRecurso nao encontrado.\n");
        }

        printf("\nAdicionar outro item? (1-Sim, 0-Nao): ");
        scanf("%d", &continuar);
        limpar_buffer();
    }

    Transacao t;
    t.valor = total_gasto_nota + val_frete + val_imposto;
    t.tipo = CONTA_A_PAGAR;
    t.status = PENDENTE;
    t.codigo_cliente_ref = 0;
    t.codigo_evento_ref = 0;

    printf("\nDescricao da Nota: ");
    ler_texto_valido(t.descricao, 150, VALIDAR_NAO_VAZIO);

    printf("Data Vencimento (DD/MM/AAAA): ");
    ler_texto_valido(t.data_vencimento, 15, VALIDAR_DATA);

    registrarTransacao(sistema, t);
    salvarRecursos(sistema);

    printf("\nCompra registrada com sucesso!\n");
}

void listar_contas_filtro(Sistema *sistema, TipoTransacao tipo) {
    printf("\n--- Lista de Contas ---\n");
    int achou = 0;
    for(int i=0; i < sistema->num_transacoes; i++) {
        if(sistema->lista_transacoes[i].tipo == tipo) {
            char *status_txt = (sistema->lista_transacoes[i].status == PAGA) ? "PAGA" : "PENDENTE";
            printf("ID: %d | %s | R$ %.2f | Vence: %s | Status: %s\n", 
                sistema->lista_transacoes[i].codigo, 
                sistema->lista_transacoes[i].descricao, 
                sistema->lista_transacoes[i].valor, 
                sistema->lista_transacoes[i].data_vencimento,
                status_txt);
            achou = 1;
        }
    }
    if(!achou) printf("Nenhuma conta encontrada neste filtro.\n");
}

int pedir_id_pagamento() {
    int id;
    printf("\nDigite o ID da conta (ou 0 para voltar): ");
    ler_inteiro_valido(&id, 0, 999999);
    return id;
}

void mostrar_saldo(float saldo) {
    printf("\n==================================\n");
    printf(" SALDO ATUAL DO CAIXA: R$ %.2f\n", saldo);
    printf("==================================\n");
}

void msg_conta_paga_sucesso() {
    mensagem_sucesso("Transacao realizada com sucesso!");
}

void msg_sem_saldo(float saldo_atual) {
    printf("\n[ERRO] Saldo insuficiente! Voce tem apenas R$ %.2f\n", saldo_atual);
    pausar();
}