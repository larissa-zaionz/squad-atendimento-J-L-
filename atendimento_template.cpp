// ╔══════════════════════════════════════════════════════════════════════════╗
// ║  DESAFIO SQUAD — Sistema de Atendimento                                 ║
// ║  PSC II · Engenharia de Software · Campo Real · Prof. Giovane Galvão    ║
// ╠══════════════════════════════════════════════════════════════════════════╣
// ║  Compilar:  g++ -std=c++17 -Wall -o atendimento atendimento_template.cpp ║
// ║  Rodar:     ./atendimento                                                ║
// ╠══════════════════════════════════════════════════════════════════════════╣
// ║  REGRAS:                                                                 ║
// ║   • Não usar STL (vector, queue, stack, list etc.)                       ║
// ║   • Toda alocação dinâmica (new) deve ter seu delete correspondente      ║
// ║   • Commitar a cada requisito implementado (R1, R2, R3, R4)             ║
// ║   • README.md no repositório explicando como compilar e usar             ║
// ╠══════════════════════════════════════════════════════════════════════════╣
// ║  RANKING:                                                                ║
// ║   +1 por requisito que compila e funciona                                ║
// ║   +1 por commit organizado com mensagem descritiva                       ║
// ║   +2 por README.md completo                                              ║
// ║   +2 squad com melhor demo (2 min)                                       ║
// ╚══════════════════════════════════════════════════════════════════════════╝

#include <iostream>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════
// ESTRUTURA BASE — Nó genérico (NÃO MODIFIQUE)
// ════════════════════════════════════════════════════════════════
struct No {
    string nome;
    int    urgencia;   // 1=baixa, 2=media, 3=alta (usado apenas por Paciente)
    No*    prox;
    No(const string& n, int u = 0) : nome(n), urgencia(u), prox(nullptr) {}
};

// ════════════════════════════════════════════════════════════════
// R1 · FILA DE PACIENTES (estrutura FIFO com dois ponteiros)
// ════════════════════════════════════════════════════════════════
// Pacientes entram pelo "trás" e saem pela "frente"
// Dentro da mesma urgência, quem chegou primeiro é atendido primeiro

struct FilaPacientes {
    No* frente = nullptr;
    No* tras   = nullptr;

    // TODO 1: Implemente enqueue(nome, urgencia)
    //         Paciente entra no final da fila
    void enqueue(const string& nome, int urgencia) {
        No* aux = new No(nome, urgencia);
        if(!tras) {
            frente = tras = aux;
            return;
        }
        tras->prox = aux;
        
        // Dica: crie um novo No, atualize 'tras' e 'frente' se necessário
        // ...
    }

    // TODO 2: Implemente dequeue()
    //         Remove e retorna o nome do paciente na frente da fila
    string dequeue() {
        string tmp = frente->nome;
        No* aux = frente;
        frente = aux->prox;
        if(!frente) {
            tras = nullptr;
        }
        delete aux;
        
        // Dica: guarde o nome antes de deletar, atualize 'frente'
        //       se frente ficar nullptr, atualize 'tras' também!
        return tmp;  // substitua pelo retorno correto
    }

    // TODO 3: Implemente frente_peek() — ver quem está na frente sem remover
    string frente_peek() const {
        if (frente == nullptr){
            return ""; 
        }

        return frente->nome;
    }

    bool isEmpty() const { return frente == nullptr; }

    // BÔNUS: Implemente tamanho() que conta os nós na fila
    int tamanho() const {
        // ...
        return 0;
    }

    ~FilaPacientes() {
        while (!isEmpty()) dequeue();
    }
};

// ════════════════════════════════════════════════════════════════
// R2 · HISTÓRICO COM PILHA (estrutura LIFO)
// ════════════════════════════════════════════════════════════════
// Cada atendimento concluído vai para a pilha de histórico
// O médico pode consultar o último atendimento com peek()

struct PilhaHistorico {
    No* topo = nullptr;

    // TODO 4: Implemente push(nome)
    //         Empilha um atendimento concluído
    void push(const string& nome) {
        No* novo = new No(nome);

        novo->prox = topo;
        topo = novo;
        // ...
    }

    // TODO 5: Implemente pop()
    //         Desempilha e retorna o último atendimento
    string pop() {
        if (topo == nullptr) return "";  // substitua pelo retorno correto
        
        No* temp = topo;
        string nome = temp->nome;

        topo = topo->prox;
        delete temp;

        return nome;
    }

    // TODO 6: Implemente peek()
    //         Retorna o último atendimento SEM remover
    string peek() const {
    if (isEmpty()) return "";
    return topo->nome;
    }

    bool isEmpty() const { return topo == nullptr; }

    ~PilhaHistorico() {
        while (!isEmpty()) pop();
    }
};

// ════════════════════════════════════════════════════════════════
// R3 · LISTA DE MÉDICOS DISPONÍVEIS (lista encadeada)
// ════════════════════════════════════════════════════════════════
// Lista de médicos plantão. Quando chamado, médico sai da lista.
// Quando termina o atendimento, volta para o final da lista.

struct ListaMedicos {
    No* head = nullptr;

    // TODO 7: Implemente adicionarMedico(nome)
    //         Adiciona um médico no final da lista
void adicionarMedico(const string& nome) {
    No* novo = new No(nome);

    if (head == nullptr) {
        head = novo;
        return;
    }

    No* p = head;
    while (p->prox != nullptr) {
        p = p->prox;
    }
    p->prox = novo;
}

    // TODO 8: Implemente chamarMedico()
    //         Remove e retorna o primeiro médico disponível
    string chamarMedico() {
    if (head == nullptr) return "";

    No* temp = head;
    string nome = temp->nome;
    head = head->prox;
    delete temp;

    return nome;
}

    // TODO 9: Implemente percorrer()
    //         Imprime todos os médicos disponíveis
    void percorrer(const string& prefixo = "") const {
    if (!prefixo.empty()) cout << prefixo << ": ";
    if (!head) {
        cout << "(lista vazia)\n";
        return;
    }
    No* medicoAtual = head;
    while (medicoAtual) {
        cout << medicoAtual->nome;
        if (medicoAtual->prox) cout << " -> ";
        medicoAtual = medicoAtual->prox;
    }
    cout << "\n";
    }

    bool temMedico() const { return head != nullptr; }

    ~ListaMedicos() {
        while (head) {
            No* t = head;
            head  = head->prox;
            delete t;
        }
    }
};

// ════════════════════════════════════════════════════════════════
// R4 · RELATÓRIO E HISTÓRICO COMPLETO
// ════════════════════════════════════════════════════════════════

// TODO 10: Implemente a função imprimirHistorico(PilhaHistorico&)
//          Imprime todos os atendimentos do histórico na ordem (do topo à base)
//          ATENÇÃO: não destrua o histórico ao imprimir!
//          Dica: use uma pilha auxiliar para preservar os dados
void imprimirHistorico(PilhaHistorico& hist) {
    cout << "\n=== Relatório de Atendimentos ===\n";
    if (hist.isEmpty()) {
        cout << "(nenhum atendimento registrado)\n";
        return;
    }

    PilhaHistorico pilhaTemporaria;   // guarda os atendimentos enquanto imprimimos
    int numeroAtendimento = 1;

    // 1) Desempilha tudo (do topo à base), imprimindo e guardando na pilha temporária
    while (!hist.isEmpty()) {
        string atendimentoAtual = hist.pop();
        cout << "  " << numeroAtendimento++ << ". " << atendimentoAtual << "\n";
        pilhaTemporaria.push(atendimentoAtual);
    }

    // 2) Devolve tudo para o histórico original, restaurando a ordem
    while (!pilhaTemporaria.isEmpty()) {
        hist.push(pilhaTemporaria.pop());
    }
}

// ════════════════════════════════════════════════════════════════
// PROGRAMA PRINCIPAL — integra as 4 estruturas
// ════════════════════════════════════════════════════════════════

int main() {
    cout << "╔═══════════════════════════════════════════════════╗\n";
    cout << "║  Sistema de Atendimento — Squad ________________  ║\n";
    cout << "╚═══════════════════════════════════════════════════╝\n\n";

    // Crie as estruturas
    FilaPacientes  fila;
    PilhaHistorico historico;
    ListaMedicos   medicos;

    // ── Cadastrar médicos (R3) ────────────────────────────────
    medicos.adicionarMedico("Dra. Ana Lima");
    medicos.adicionarMedico("Dr. Bruno Costa");
    medicos.adicionarMedico("Dra. Carla Ramos");
    medicos.percorrer("Médicos disponíveis");

    // ── Pacientes chegam na fila (R1) ─────────────────────────
    cout << "\nPacientes chegando:\n";
    fila.enqueue("Eduardo (urgencia=3)", 3);
    fila.enqueue("Fernanda (urgencia=1)", 1);
    fila.enqueue("Gabriel (urgencia=2)", 2);
    fila.enqueue("Helena (urgencia=1)", 1);

    cout << "Próximo a ser atendido: " << fila.frente_peek() << "\n";
    cout << "Total na fila: " << fila.tamanho() << "\n";

    // ── Simulação de atendimentos ─────────────────────────────
    cout << "\nSimulação de atendimentos:\n";
    int atend = 1;
    while (!fila.isEmpty() && medicos.temMedico()) {
        string paciente = fila.dequeue();
        string medico   = medicos.chamarMedico();

        cout << "  [" << atend++ << "] " << medico
             << " atende " << paciente << "\n";

        // Registra no histórico (R2)
        historico.push(medico + " → " + paciente);

        // Médico volta para a fila depois de atender
        // (descomente após implementar adicionarMedico)
        // medicos.adicionarMedico(medico);
    }

    // ── Último atendimento (peek na pilha) ────────────────────
    cout << "\nÚltimo atendimento registrado (peek): " << historico.peek() << "\n";

    // ── Relatório final (R4) ──────────────────────────────────
    imprimirHistorico(historico);

    return 0;
}

// ════════════════════════════════════════════════════════════════
// CHECKLIST DE ENTREGA
// ════════════════════════════════════════════════════════════════
// [ ] TODO 1 — enqueue funciona (paciente entra na fila)
// [ ] TODO 2 — dequeue funciona (paciente sai da fila, memória liberada)
// [ ] TODO 3 — frente_peek retorna o nome sem remover
// [ ] TODO 4 — push empilha no histórico
// [ ] TODO 5 — pop desempilha e libera memória
// [ ] TODO 6 — peek retorna o topo sem remover
// [ ] TODO 7 — adicionarMedico insere no final da lista
// [ ] TODO 8 — chamarMedico remove do início e retorna o nome
// [x] TODO 9 — percorrer imprime todos os médicos com setas
// [x] TODO 10 — imprimirHistorico imprime sem destruir os dados
// [ ] Programa compila sem warnings: g++ -std=c++17 -Wall -o sis main.cpp
// [ ] Sem vazamentos de memória (todo new tem delete correspondente)
// [ ] Repositório no GitHub com histórico de commits organizado
// [x] README.md com instrução de compilação e exemplo de saída
