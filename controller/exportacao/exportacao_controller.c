#include "exportacao_controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view/exportacao/exportacao_view.h"
#include "utils/utils.h"

int ler_tag_xml(char *linha, char *tag, char *destino) {
    char tag_ini[50];
    char tag_fim[50];
    
    sprintf(tag_ini, "<%s>", tag);
    sprintf(tag_fim, "</%s>", tag);

    char *inicio = strstr(linha, tag_ini);
    
    if (inicio) {
        inicio += strlen(tag_ini);
        char *fim = strstr(inicio, tag_fim);
        if (fim) {
            int tamanho = fim - inicio;
            strncpy(destino, inicio, tamanho);
            destino[tamanho] = '\0';
            return 1;
        }
    }
    return 0;
}

void exportar_clientes(Sistema *s, FILE *f) {
    fprintf(f, "<dados>\n");
    fprintf(f, "<tabela-cliente>\n");
    for(int i=0; i < s->num_clientes; i++) {
        Cliente *c = &s->lista_clientes[i];
        fprintf(f, "<registro>\n");
        fprintf(f, "<codigo>%d</codigo>\n", c->codigo);
        fprintf(f, "<razao_social>%s</razao_social>\n", c->razao_social);
        fprintf(f, "<endereco>%s</endereco>\n", c->endereco);
        fprintf(f, "<cnpj>%s</cnpj>\n", c->cnpj);
        fprintf(f, "<telefone>%s</telefone>\n", c->telefone);
        fprintf(f, "<email>%s</email>\n", c->email);
        fprintf(f, "<nome_contato>%s</nome_contato>\n", c->nome_do_contato);
        fprintf(f, "</registro>\n");
    }
    fprintf(f, "</tabela-cliente>\n");
    fprintf(f, "</dados>\n");
}

void exportar_equipamentos(Sistema *s, FILE *f) {
    fprintf(f, "<dados>\n");
    fprintf(f, "<tabela-equipamento>\n");
    for(int i=0; i < s->num_recursos; i++) {
        Recurso *r = &s->lista_recursos[i];
        fprintf(f, "<registro>\n");
        fprintf(f, "<codigo>%d</codigo>\n", r->codigo);
        fprintf(f, "<descricao>%s</descricao>\n", r->descricao);
        fprintf(f, "<categoria>%s</categoria>\n", r->categoria);
        fprintf(f, "<quantidade_estoque>%d</quantidade_estoque>\n", r->quantidade_estoque);
        fprintf(f, "<preco_custo>%.2f</preco_custo>\n", r->preco_custo);
        fprintf(f, "<valor_locacao>%.2f</valor_locacao>\n", r->valor_locacao);
        fprintf(f, "</registro>\n");
    }
    fprintf(f, "</tabela-equipamento>\n");
    fprintf(f, "</dados>\n");
}

void exportar_eventos(Sistema *s, FILE *f) {
    fprintf(f, "<dados>\n");
    fprintf(f, "<tabela-evento>\n");
    for(int i=0; i < s->num_eventos; i++) {
        Evento *e = &s->lista_eventos[i];
        
        char st[20];
        if(e->status == ORCAMENTO) strcpy(st, "Orcamento");
        else if(e->status == APROVADO) strcpy(st, "Aprovado");
        else if(e->status == FINALIZADO) strcpy(st, "Finalizado");
        else strcpy(st, "Cancelado");

        fprintf(f, "<registro>\n");
        fprintf(f, "<codigo_evento>%d</codigo_evento>\n", e->codigo);
        fprintf(f, "<nome_evento>%s</nome_evento>\n", e->nome_evento);
        fprintf(f, "<codigo_cliente>%d</codigo_cliente>\n", e->codigo_cliente);
        fprintf(f, "<status>%s</status>\n", st);
        fprintf(f, "</registro>\n");
    }
    fprintf(f, "</tabela-evento>\n");
    fprintf(f, "</dados>\n");
}

void exportar_produtora(Sistema *s, FILE *f) {
    if(s->dados_produtora == NULL) return;
    Produtora *p = s->dados_produtora;

    fprintf(f, "<dados>\n");
    fprintf(f, "<tabela-produtora>\n");
    fprintf(f, "<registro>\n");
    fprintf(f, "<nome_fantasia>%s</nome_fantasia>\n", p->nome_fantasia);
    fprintf(f, "<razao_social>%s</razao_social>\n", p->razao_social);
    fprintf(f, "<responsavel>%s</responsavel>\n", p->nome_do_responsavel);
    fprintf(f, "<cnpj>%s</cnpj>\n", p->cnpj);
    fprintf(f, "<inscricao_est>%s</inscricao_est>\n", p->inscricao_estadual);
    fprintf(f, "<endereco>%s</endereco>\n", p->endereco);
    fprintf(f, "<telefone>%s</telefone>\n", p->telefone);
    fprintf(f, "<tel_resp>%s</tel_resp>\n", p->telefone_responsavel);
    fprintf(f, "<email>%s</email>\n", p->email);
    fprintf(f, "<margem>%.2f</margem>\n", p->margem_lucro);
    fprintf(f, "</registro>\n");
    fprintf(f, "</tabela-produtora>\n");
    fprintf(f, "</dados>\n");
}

void exportar_fornecedores(Sistema *s, FILE *f) {
    fprintf(f, "<dados>\n");
    fprintf(f, "<tabela-fornecedor>\n");
    for(int i=0; i < s->num_fornecedores; i++) {
        Fornecedor *fo = &s->lista_fornecedores[i];
        fprintf(f, "<registro>\n");
        fprintf(f, "<codigo>%d</codigo>\n", fo->codigo);
        fprintf(f, "<nome_fantasia>%s</nome_fantasia>\n", fo->nome_fantasia);
        fprintf(f, "<razao_social>%s</razao_social>\n", fo->razao_social);
        fprintf(f, "<cnpj>%s</cnpj>\n", fo->cnpj);
        fprintf(f, "<endereco>%s</endereco>\n", fo->endereco);
        fprintf(f, "<telefone>%s</telefone>\n", fo->telefone);
        fprintf(f, "<tipo_servico>%s</tipo_servico>\n", fo->tipo_servico);
        fprintf(f, "<valor_servico>%.2f</valor_servico>\n", fo->valor_servico);
        fprintf(f, "</registro>\n");
    }
    fprintf(f, "</tabela-fornecedor>\n");
    fprintf(f, "</dados>\n");
}

void exportar_equipe(Sistema *s, FILE *f) {
    fprintf(f, "<dados>\n");
    fprintf(f, "<tabela-equipe>\n");
    for(int i=0; i < s->num_equipe; i++) {
        EquipeInterna *e = &s->lista_equipe[i];
        fprintf(f, "<registro>\n");
        fprintf(f, "<codigo>%d</codigo>\n", e->codigo);
        fprintf(f, "<nome>%s</nome>\n", e->nome);
        fprintf(f, "<cpf>%s</cpf>\n", e->cpf);
        fprintf(f, "<funcao>%s</funcao>\n", e->funcao);
        fprintf(f, "<valor_diaria>%.2f</valor_diaria>\n", e->valor_diaria);
        fprintf(f, "</registro>\n");
    }
    fprintf(f, "</tabela-equipe>\n");
    fprintf(f, "</dados>\n");
}

void exportar_transacoes(Sistema *s, FILE *f) {
    fprintf(f, "<dados>\n");
    fprintf(f, "<tabela-transacao>\n");
    for(int i=0; i < s->num_transacoes; i++) {
        Transacao *t = &s->lista_transacoes[i];
        
        char tipo[20];
        if(t->tipo == CONTA_A_RECEBER) strcpy(tipo, "Receber");
        else if(t->tipo == CONTA_A_PAGAR) strcpy(tipo, "Pagar");
        else strcpy(tipo, "Caixa");

        char status[20];
        if(t->status == PAGA) strcpy(status, "Paga");
        else strcpy(status, "Pendente");

        fprintf(f, "<registro>\n");
        fprintf(f, "<codigo>%d</codigo>\n", t->codigo);
        fprintf(f, "<tipo>%s</tipo>\n", tipo);
        fprintf(f, "<status>%s</status>\n", status);
        fprintf(f, "<descricao>%s</descricao>\n", t->descricao);
        fprintf(f, "<valor>%.2f</valor>\n", t->valor);
        fprintf(f, "<data_venc>%s</data_venc>\n", t->data_vencimento);
        fprintf(f, "<data_pag>%s</data_pag>\n", t->data_pagamento);
        fprintf(f, "<cod_cliente>%d</cod_cliente>\n", t->codigo_cliente_ref);
        fprintf(f, "<cod_evento>%d</cod_evento>\n", t->codigo_evento_ref);
        fprintf(f, "</registro>\n");
    }
    fprintf(f, "</tabela-transacao>\n");
    fprintf(f, "</dados>\n");
}

void importar_clientes(Sistema *s, FILE *f) {
    char linha[500], valor[200];
    Cliente temp;
    memset(&temp, 0, sizeof(Cliente));
    int cont = 0;

    while(fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;

        if(strstr(linha, "<registro>")) {
            memset(&temp, 0, sizeof(Cliente));
        }

        if(ler_tag_xml(linha, "codigo", valor)) temp.codigo = atoi(valor);
        if(ler_tag_xml(linha, "razao_social", valor)) strcpy(temp.razao_social, valor);
        if(ler_tag_xml(linha, "endereco", valor)) strcpy(temp.endereco, valor);
        if(ler_tag_xml(linha, "cnpj", valor)) strcpy(temp.cnpj, valor);
        if(ler_tag_xml(linha, "telefone", valor)) strcpy(temp.telefone, valor);
        if(ler_tag_xml(linha, "email", valor)) strcpy(temp.email, valor);
        if(ler_tag_xml(linha, "nome_contato", valor)) strcpy(temp.nome_do_contato, valor);

        if(strstr(linha, "</registro>")) {
            if (s->num_clientes == s->capacidade_clientes) {
                int nova = (s->capacidade_clientes == 0) ? 10 : s->capacidade_clientes * 2;
                s->lista_clientes = realloc(s->lista_clientes, nova * sizeof(Cliente));
                s->capacidade_clientes = nova;
            }
            s->lista_clientes[s->num_clientes] = temp;
            s->num_clientes++;
            cont++;
        }
    }
    msg_importacao_sucesso(cont);
}

void importar_equipamentos(Sistema *s, FILE *f) {
    char linha[500], valor[200];
    Recurso temp;
    memset(&temp, 0, sizeof(Recurso));
    int cont = 0;

    while(fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;

        if(strstr(linha, "<registro>")) {
            memset(&temp, 0, sizeof(Recurso));
        }

        if(ler_tag_xml(linha, "codigo", valor)) temp.codigo = atoi(valor);
        if(ler_tag_xml(linha, "descricao", valor)) strcpy(temp.descricao, valor);
        if(ler_tag_xml(linha, "categoria", valor)) strcpy(temp.categoria, valor);
        if(ler_tag_xml(linha, "quantidade_estoque", valor)) temp.quantidade_estoque = atoi(valor);
        if(ler_tag_xml(linha, "preco_custo", valor)) temp.preco_custo = atof(valor);
        if(ler_tag_xml(linha, "valor_locacao", valor)) temp.valor_locacao = atof(valor);

        if(strstr(linha, "</registro>")) {
            if (s->num_recursos == s->capacidade_recursos) {
                int nova = (s->capacidade_recursos == 0) ? 10 : s->capacidade_recursos * 2;
                s->lista_recursos = realloc(s->lista_recursos, nova * sizeof(Recurso));
                s->capacidade_recursos = nova;
            }
            s->lista_recursos[s->num_recursos] = temp;
            s->num_recursos++;
            cont++;
        }
    }
    msg_importacao_sucesso(cont);
}

void importar_eventos(Sistema *s, FILE *f) {
    char linha[500], valor[200];
    Evento temp;
    memset(&temp, 0, sizeof(Evento));
    int cont = 0;

    while(fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;

        if(strstr(linha, "<registro>")) {
            memset(&temp, 0, sizeof(Evento));
            temp.status = ORCAMENTO;
        }

        if(ler_tag_xml(linha, "codigo_evento", valor)) temp.codigo = atoi(valor);
        if(ler_tag_xml(linha, "nome_evento", valor)) strcpy(temp.nome_evento, valor);
        if(ler_tag_xml(linha, "codigo_cliente", valor)) temp.codigo_cliente = atoi(valor);
        
        if(ler_tag_xml(linha, "status", valor)) {
            if(strcmp(valor, "Aprovado") == 0) temp.status = APROVADO;
            else if(strcmp(valor, "Finalizado") == 0) temp.status = FINALIZADO;
            else if(strcmp(valor, "Orcamento") == 0) temp.status = ORCAMENTO;
            else temp.status = CANCELADO;
        }

        if(strstr(linha, "</registro>")) {
            if (s->num_eventos == s->capacidade_eventos) {
                int nova = (s->capacidade_eventos == 0) ? 10 : s->capacidade_eventos * 2;
                s->lista_eventos = realloc(s->lista_eventos, nova * sizeof(Evento));
                s->capacidade_eventos = nova;
            }
            s->lista_eventos[s->num_eventos] = temp;
            s->num_eventos++;
            cont++;
        }
    }
    msg_importacao_sucesso(cont);
}

void importar_produtora(Sistema *s, FILE *f) {
    char linha[500], valor[200];
    int lendo = 0;
    int cont = 0;

    if(s->dados_produtora == NULL) {
        s->dados_produtora = malloc(sizeof(Produtora));
    }
    Produtora *p = s->dados_produtora;

    while(fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;

        if(strstr(linha, "<registro>")) {
            lendo = 1;
            continue;
        }

        if(lendo) {
            if(ler_tag_xml(linha, "nome_fantasia", valor)) strcpy(p->nome_fantasia, valor);
            if(ler_tag_xml(linha, "razao_social", valor)) strcpy(p->razao_social, valor);
            if(ler_tag_xml(linha, "responsavel", valor)) strcpy(p->nome_do_responsavel, valor);
            if(ler_tag_xml(linha, "cnpj", valor)) strcpy(p->cnpj, valor);
            if(ler_tag_xml(linha, "inscricao_est", valor)) strcpy(p->inscricao_estadual, valor);
            if(ler_tag_xml(linha, "endereco", valor)) strcpy(p->endereco, valor);
            if(ler_tag_xml(linha, "telefone", valor)) strcpy(p->telefone, valor);
            if(ler_tag_xml(linha, "tel_resp", valor)) strcpy(p->telefone_responsavel, valor);
            if(ler_tag_xml(linha, "email", valor)) strcpy(p->email, valor);
            if(ler_tag_xml(linha, "margem", valor)) p->margem_lucro = atof(valor);

            if(strstr(linha, "</registro>")) {
                cont = 1; 
                lendo = 0;
            }
        }
    }
    if(cont) msg_importacao_sucesso(1);
    else printf("\nNenhum dado de produtora encontrado.\n");
}

void importar_fornecedores(Sistema *s, FILE *f) {
    char linha[500], valor[200];
    Fornecedor temp;
    memset(&temp, 0, sizeof(Fornecedor));
    int cont = 0;

    while(fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;

        if(strstr(linha, "<registro>")) {
            memset(&temp, 0, sizeof(Fornecedor));
        }

        if(ler_tag_xml(linha, "codigo", valor)) temp.codigo = atoi(valor);
        if(ler_tag_xml(linha, "nome_fantasia", valor)) strcpy(temp.nome_fantasia, valor);
        if(ler_tag_xml(linha, "razao_social", valor)) strcpy(temp.razao_social, valor);
        if(ler_tag_xml(linha, "cnpj", valor)) strcpy(temp.cnpj, valor);
        if(ler_tag_xml(linha, "endereco", valor)) strcpy(temp.endereco, valor);
        if(ler_tag_xml(linha, "telefone", valor)) strcpy(temp.telefone, valor);
        if(ler_tag_xml(linha, "tipo_servico", valor)) strcpy(temp.tipo_servico, valor);
        if(ler_tag_xml(linha, "valor_servico", valor)) temp.valor_servico = atof(valor);

        if(strstr(linha, "</registro>")) {
            if (s->num_fornecedores == s->capacidade_fornecedores) {
                int nova = (s->capacidade_fornecedores == 0) ? 10 : s->capacidade_fornecedores * 2;
                s->lista_fornecedores = realloc(s->lista_fornecedores, nova * sizeof(Fornecedor));
                s->capacidade_fornecedores = nova;
            }
            s->lista_fornecedores[s->num_fornecedores] = temp;
            s->num_fornecedores++;
            cont++;
        }
    }
    msg_importacao_sucesso(cont);
}

void importar_equipe(Sistema *s, FILE *f) {
    char linha[500], valor[200];
    EquipeInterna temp;
    memset(&temp, 0, sizeof(EquipeInterna));
    int cont = 0;

    while(fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;

        if(strstr(linha, "<registro>")) {
            memset(&temp, 0, sizeof(EquipeInterna));
        }

        if(ler_tag_xml(linha, "codigo", valor)) temp.codigo = atoi(valor);
        if(ler_tag_xml(linha, "nome", valor)) strcpy(temp.nome, valor);
        if(ler_tag_xml(linha, "cpf", valor)) strcpy(temp.cpf, valor);
        if(ler_tag_xml(linha, "funcao", valor)) strcpy(temp.funcao, valor);
        if(ler_tag_xml(linha, "valor_diaria", valor)) temp.valor_diaria = atof(valor);

        if(strstr(linha, "</registro>")) {
            if (s->num_equipe == s->capacidade_equipe) {
                int nova = (s->capacidade_equipe == 0) ? 10 : s->capacidade_equipe * 2;
                s->lista_equipe = realloc(s->lista_equipe, nova * sizeof(EquipeInterna));
                s->capacidade_equipe = nova;
            }
            s->lista_equipe[s->num_equipe] = temp;
            s->num_equipe++;
            cont++;
        }
    }
    msg_importacao_sucesso(cont);
}

void importar_transacoes(Sistema *s, FILE *f) {
    char linha[500], valor[200];
    Transacao temp;
    memset(&temp, 0, sizeof(Transacao));
    int cont = 0;

    while(fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;

        if(strstr(linha, "<registro>")) {
            memset(&temp, 0, sizeof(Transacao));
            temp.tipo = CONTA_A_PAGAR;
            temp.status = PENDENTE;
        }

        if(ler_tag_xml(linha, "codigo", valor)) temp.codigo = atoi(valor);
        
        if(ler_tag_xml(linha, "tipo", valor)) {
            if(strcmp(valor, "Receber") == 0) temp.tipo = CONTA_A_RECEBER;
            else if(strcmp(valor, "Pagar") == 0) temp.tipo = CONTA_A_PAGAR;
            else temp.tipo = MOVIMENTACAO_CAIXA;
        }

        if(ler_tag_xml(linha, "status", valor)) {
            if(strcmp(valor, "Paga") == 0) temp.status = PAGA;
            else temp.status = PENDENTE;
        }

        if(ler_tag_xml(linha, "descricao", valor)) strcpy(temp.descricao, valor);
        if(ler_tag_xml(linha, "valor", valor)) temp.valor = atof(valor);
        if(ler_tag_xml(linha, "data_venc", valor)) strcpy(temp.data_vencimento, valor);
        if(ler_tag_xml(linha, "data_pag", valor)) strcpy(temp.data_pagamento, valor);
        if(ler_tag_xml(linha, "cod_cliente", valor)) temp.codigo_cliente_ref = atoi(valor);
        if(ler_tag_xml(linha, "cod_evento", valor)) temp.codigo_evento_ref = atoi(valor);

        if(strstr(linha, "</registro>")) {
            if (s->num_transacoes == s->capacidade_transacoes) {
                int nova = (s->capacidade_transacoes == 0) ? 10 : s->capacidade_transacoes * 2;
                s->lista_transacoes = realloc(s->lista_transacoes, nova * sizeof(Transacao));
                s->capacidade_transacoes = nova;
            }
            s->lista_transacoes[s->num_transacoes] = temp;
            s->num_transacoes++;
            cont++;
        }
    }
    msg_importacao_sucesso(cont);
}

void menuXMLController(Sistema *sistema) {
    int op = 0;
    do {
        menuXMLView();
        op = obterOpcaoXML();
        
        if (op == 0) return;

        int tabela = menuEscolherTabela();
        if (tabela == 0) continue;

        char arquivo[50];
        
        if (tabela == 1) strcpy(arquivo, "clientes_export.xml");
        else if (tabela == 2) strcpy(arquivo, "equipamentos_export.xml");
        else if (tabela == 3) strcpy(arquivo, "eventos_export.xml");
        else if (tabela == 4) strcpy(arquivo, "produtora_export.xml");
        else if (tabela == 5) strcpy(arquivo, "fornecedores_export.xml");
        else if (tabela == 6) strcpy(arquivo, "equipe_export.xml");
        else if (tabela == 7) strcpy(arquivo, "transacoes_export.xml");

        if (op == 1) { 
            msg_gravando_arquivo();
            FILE *f = fopen(arquivo, "w");
            if (!f) { msg_erro_arquivo_xml(); continue; }

            if(tabela == 1) exportar_clientes(sistema, f);
            if(tabela == 2) exportar_equipamentos(sistema, f);
            if(tabela == 3) exportar_eventos(sistema, f);
            if(tabela == 4) exportar_produtora(sistema, f);
            if(tabela == 5) exportar_fornecedores(sistema, f);
            if(tabela == 6) exportar_equipe(sistema, f);
            if(tabela == 7) exportar_transacoes(sistema, f);

            fclose(f);
            msg_exportacao_sucesso(arquivo);
        }
        else if (op == 2) { 
            msg_lendo_arquivo();
            FILE *f = fopen(arquivo, "r");
            if (!f) { msg_erro_arquivo_xml(); continue; }

            if(tabela == 1) importar_clientes(sistema, f);
            if(tabela == 2) importar_equipamentos(sistema, f);
            if(tabela == 3) importar_eventos(sistema, f);
            if(tabela == 4) importar_produtora(sistema, f);
            if(tabela == 5) importar_fornecedores(sistema, f);
            if(tabela == 6) importar_equipe(sistema, f);
            if(tabela == 7) importar_transacoes(sistema, f);
            
            fclose(f);
        }

    } while (op != 0);
}