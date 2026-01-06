# EventManager - Sistema de Gestão de Eventos

![Status do Projeto](https://img.shields.io/badge/status-concluido-brightgreen)
![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Licença](https://img.shields.io/badge/licen%C3%A7a-MIT-green)

> Projeto acadêmico da disciplina de Algoritmos e Estruturas de Dados do IFMG - Campus Formiga. Um sistema completo em C para gerenciamento de uma produtora de eventos, controle financeiro e alocação de recursos.

---

## 📖 Sobre o Projeto

O **EventManager** é uma solução de backend/console desenvolvida em C puro para gerenciar os processos de uma produtora de eventos. O sistema utiliza uma arquitetura organizada (MVC - Model View Controller) e foca na integridade dos dados e na gestão de recursos.

O projeto resolve problemas como: conflito de agenda de equipamentos e equipe, controle de orçamentos, fluxo de caixa e persistência de dados em múltiplos formatos.

## 🚀 Funcionalidades Implementadas

* **Gestão de Cadastros (CRUD):** Gerenciamento completo de Clientes, Equipe Interna, Fornecedores, Operadores e Equipamentos/Recursos.
* **Fluxo de Eventos Inteligente:**
    * Criação de Orçamentos (status inicial).
    * **Verificação de Conflitos:** O sistema impede a aprovação de eventos se houver falta de estoque de equipamentos ou se um membro da equipe já estiver alocado em outro evento no mesmo horário.
    * Finalização e Faturamento automático.
* **Módulo Financeiro:**
    * Contas a Pagar (compras de equipamentos/gastos) e a Receber (eventos finalizados).
    * Controle de Saldo de Caixa.
    * Registro de compras com atualização automática de estoque e preço médio.
* **Persistência de Dados Avançada:**
    * Suporte híbrido: Salva em **Binário (.dat)** para performance ou **Texto (.txt)** para legibilidade.
    * Conversor integrado: Ferramenta interna para converter os dados entre Binário e Texto.
* **Importação e Exportação:**
    * Geração e leitura de arquivos **XML** para todas as tabelas do sistema.
* **Relatórios Gerenciais:**
    * Listagens na tela ou exportação para **CSV** (Excel).
    * Relatórios de Clientes, Cronograma de Eventos, Inventário e Extrato Financeiro.

## 💻 Como Executar

### Pré-requisitos
* Compilador GCC (`MinGW` no Windows ou `build-essential` no Linux).
* Make (opcional, para usar o makefile).

### Passos
1.  Clone este repositório:
    ```bash
    git clone [https://github.com/reireymond/eventmananger.git](https://github.com/reireymond/eventmananger.git)
    ```
2.  Compile o projeto usando o `makefile` incluso:
    ```bash
    make run
    ```
    *Ou compile manualmente:*
    ```bash
    gcc -I. main.c controller/*/*.c model/*/*.c view/*/*.c utils/*.c -o eventmanager.exe
    ./eventmanager.exe
    ```
3.  **Primeiro Acesso:**
    * O sistema detectará que não há operadores cadastrados.
    * Siga as instruções na tela para criar o usuário **Administrador**.

## 📂 Estrutura de Arquivos

O projeto segue o padrão **MVC (Model-View-Controller)** para organização do código:

* `main.c`: Ponto de entrada do sistema.
* `model/`: Definição das `structs` e lógica de persistência (salvar/carregar arquivos).
* `view/`: Interfaces de usuário (Menus, Formulários e Exibição de dados).
* `controller/`: Lógica de negócios (Validações, Cálculos, Conexão entre Model e View).
* `utils/`: Bibliotecas auxiliares (Validação de CPF/CNPJ, tratamento de strings e datas).
* `data/`: Pasta onde os bancos de dados (`.txt`, `.dat`) e exportações (`.xml`, `.csv`) são armazenados.

---

## 👤 Autores

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/reireymond">
        <img src="https://github.com/reireymond.png?size=100" width="100px;" alt="Foto de Kaua Teixeira Nascimento no GitHub"/>
        <br />
        <sub>
          <b>Kaua Teixeira N.</b>
        </sub>
      </a>
    </td>
  </tr>
</table>

> Este projeto está sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
