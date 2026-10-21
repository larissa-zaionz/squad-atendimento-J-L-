# Sistema de Atendimento — Squad Atendimento J-L

Projeto da disciplina **PSC II** — Engenharia de Software, Faculdade Campo Real (Prof. Giovane Galvão).

Simulação de um sistema de atendimento médico que integra três estruturas de dados implementadas **do zero**, sem usar a STL (`vector`, `queue`, `stack`, `list` etc.).

## Integrantes

- [Larissa Zaions]
- [João Augusto]
- [João Gabriel]
- [Lucas Kruppa]

## Estruturas implementadas

| Requisito | Estrutura | Uso no sistema |
|---|---|---|
| **R1** | Fila (FIFO, dois ponteiros) | Pacientes aguardando atendimento |
| **R2** | Pilha (LIFO) | Histórico de atendimentos concluídos |
| **R3** | Lista encadeada | Médicos de plantão disponíveis |
| **R4** | Relatório | Impressão do histórico completo sem destruí-lo |

Todas usam o mesmo nó base (`struct No`), com `nome`, `urgencia` e o ponteiro `prox`.

## Como compilar

Requisitos: compilador `g++` com suporte a C++17.

```bash
g++ -std=c++17 -Wall -o atendimento atendimento_template.cpp
```

## Como executar

```bash
./atendimento
```

No Windows (PowerShell): `.\atendimento.exe`

## Como funciona

1. Os médicos são cadastrados na lista (R3) e exibidos com `percorrer()`.
2. Os pacientes chegam e entram no final da fila (R1).
3. Enquanto houver paciente e médico disponível, o primeiro da fila é atendido pelo primeiro médico da lista.
4. Cada atendimento é empilhado no histórico (R2).
5. Ao final, `imprimirHistorico()` mostra todos os atendimentos, do mais recente ao mais antigo (R4). Uma pilha auxiliar garante que o histórico não seja perdido na impressão.

## Exemplo de saída

(Serão adicionados posteriormente)

## Gerenciamento de memória

Toda alocação com `new` possui o `delete` correspondente: os destrutores de `FilaPacientes`, `PilhaHistorico` e `ListaMedicos` liberam os nós restantes.

## Estrutura do repositório

```
.
├── atendimento_template.cpp   # código-fonte
└── README.md                  # este arquivo
```