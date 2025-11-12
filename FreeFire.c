#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Incluída conforme instruído, embora não usada para timing explícito

// --- Requisito 1: Criação de Structs ---

/**
 * @brief Estrutura que representa um Item no inventário.
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/**
 * @brief Estrutura para o Nó (Node) da Lista Encadeada.
 */
typedef struct No {
    Item dados;             // Os dados do item armazenados no nó
    struct No* proximo;     // Ponteiro para o próximo nó da lista
} No;


// --- Variáveis Globais para o Vetor (Lista Sequencial) ---
#define CAPACIDADE_MAXIMA 10
Item mochilaVetor[CAPACIDADE_MAXIMA];
int numItensVetor = 0;

// --- Variáveis Globais para a Lista Encadeada (Estrutura Dinâmica) ---
No* mochilaLista = NULL; // Ponteiro para a cabeça (início) da lista

// --- Contador de Operações (Requisito 6) ---
long long contadorComparacoes = 0;


// ====================================================================
//                          FUNÇÕES PARA O VETOR
// ====================================================================

/**
 * @brief Insere um item na primeira posição livre do vetor.
 */
void inserirItemVetor() {
    if (numItensVetor >= CAPACIDADE_MAXIMA) {
        printf("🚫 Mochila (Vetor) Cheia! Capacidade máxima atingida.\n");
        return;
    }

    printf("--- Cadastro de Item (Vetor) ---\n");
    printf("Nome: ");
    if (scanf(" %29[^\n]", mochilaVetor[numItensVetor].nome) != 1) return;
    printf("Tipo: ");
    if (scanf(" %19[^\n]", mochilaVetor[numItensVetor].tipo) != 1) return;
    printf("Quantidade: ");
    if (scanf("%d", &mochilaVetor[numItensVetor].quantidade) != 1) {
        printf("⚠️ Erro na leitura da quantidade.\n");
        while (getchar() != '\n'); // Limpa buffer
        return;
    }

    numItensVetor++;
    printf("✅ Item '%s' inserido com sucesso no vetor.\n", mochilaVetor[numItensVetor - 1].nome);
}

/**
 * @brief Remove um item por nome do vetor.
 * Utiliza o método de compactação (movendo itens subsequentes).
 */
void removerItemVetor() {
    if (numItensVetor == 0) {
        printf("⚠️ Mochila (Vetor) vazia. Nada para remover.\n");
        return;
    }

    char nomeParaRemover[30];
    printf("Informe o Nome do Item para remover: ");
    if (scanf(" %29[^\n]", nomeParaRemover) != 1) return;

    int indice = -1;
    for (int i = 0; i < numItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeParaRemover) == 0) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        printf("🗑️ Removendo Item: **%s**\n", mochilaVetor[indice].nome);
        // Compactação: Move todos os itens subsequentes uma posição para frente.
        for (int i = indice; i < numItensVetor - 1; i++) {
            mochilaVetor[i] = mochilaVetor[i + 1];
        }
        numItensVetor--;
        printf("✅ Item removido do vetor.\n");
    } else {
        printf("❌ Item '%s' não encontrado no vetor.\n", nomeParaRemover);
    }
}

/**
 * @brief Lista todos os itens do vetor.
 */
void listarItensVetor() {
    printf("\n--- 📝 Inventário (Vetor - %d/%d) ---\n", numItensVetor, CAPACIDADE_MAXIMA);
    if (numItensVetor == 0) {
        printf("⚠️ Mochila vazia.\n");
        return;
    }

    printf("| %-29s | %-19s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < numItensVetor; i++) {
        printf("| %-29s | %-19s | %-10d |\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
    printf("----------------------------------------------------------------\n");
}

/**
 * @brief Ordena o vetor de itens por nome (Bubble Sort).
 * @note Requisito 4: Ordenação no vetor.
 */
void ordenarVetor() {
    if (numItensVetor <= 1) return; // Nada para ordenar

    // Bubble Sort
    for (int i = 0; i < numItensVetor - 1; i++) {
        for (int j = 0; j < numItensVetor - i - 1; j++) {
            // Compara os nomes. Se o item 'j' for 'maior' que 'j+1' (alfabeticamente)
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                // Troca (swap)
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }
    printf("✨ Vetor ordenado com sucesso (por Nome).\n");
}

/**
 * @brief Busca sequencial no vetor, contando as comparações.
 * @note Requisito 3: Busca sequencial.
 */
void buscarSequencialVetor(const char *nomeBusca) {
    contadorComparacoes = 0;
    int encontrado = 0;

    for (int i = 0; i < numItensVetor; i++) {
        contadorComparacoes++; // Uma comparação de string
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            printf("✅ Busca Sequencial: Item '%s' Encontrado!\n", nomeBusca);
            printf("> Tipo: %s | Quantidade: %d\n", mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("❌ Busca Sequencial: Item '%s' não encontrado.\n", nomeBusca);
    }
    printf("➡️ Comparações realizadas (Sequencial): %lld\n", contadorComparacoes);
}

/**
 * @brief Busca binária no vetor ordenado, contando as comparações.
 * @note Requisito 5: Busca Binária.
 */
void buscarBinariaVetor(const char *nomeBusca) {
    contadorComparacoes = 0;
    int inicio = 0;
    int fim = numItensVetor - 1;
    int encontrado = 0;

    if (numItensVetor == 0) {
        printf("⚠️ Busca Binária: Vetor vazio.\n");
        return;
    }

    // A busca binária exige que o vetor esteja ORDENADO!
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        int resultadoComparacao = strcmp(mochilaVetor[meio].nome, nomeBusca);
        contadorComparacoes++; // Uma comparação de string

        if (resultadoComparacao == 0) {
            // Encontrado
            printf("✅ Busca Binária: Item '%s' Encontrado!\n", nomeBusca);
            printf("> Tipo: %s | Quantidade: %d\n", mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            encontrado = 1;
            break;
        } else if (resultadoComparacao < 0) {
            // Item buscado é 'maior', ignora a primeira metade
            inicio = meio + 1;
        } else {
            // Item buscado é 'menor', ignora a segunda metade
            fim = meio - 1;
        }
    }

    if (!encontrado) {
        printf("❌ Busca Binária: Item '%s' não encontrado.\n", nomeBusca);
    }
    printf("➡️ Comparações realizadas (Binária): %lld\n", contadorComparacoes);
}

// ====================================================================
//                       FUNÇÕES PARA A LISTA ENCADEADA
// ====================================================================

/**
 * @brief Cria um novo nó com os dados do item.
 */
No* criarNo(Item novoItem) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("❌ Erro de alocação de memória.\n");
        exit(1);
    }
    novo->dados = novoItem;
    novo->proximo = NULL;
    return novo;
}

/**
 * @brief Insere um item no início da lista encadeada (inserção O(1)).
 */
void inserirItemLista() {
    Item novoItem;
    printf("--- Cadastro de Item (Lista Encadeada) ---\n");
    printf("Nome: ");
    if (scanf(" %29[^\n]", novoItem.nome) != 1) return;
    printf("Tipo: ");
    if (scanf(" %19[^\n]", novoItem.tipo) != 1) return;
    printf("Quantidade: ");
    if (scanf("%d", &novoItem.quantidade) != 1) {
        printf("⚠️ Erro na leitura da quantidade.\n");
        while (getchar() != '\n');
        return;
    }

    No* novoNo = criarNo(novoItem);
    // Insere no início: novoNo aponta para o antigo primeiro, e a cabeça vira novoNo.
    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;

    printf("✅ Item '%s' inserido com sucesso na lista encadeada (Início).\n", novoItem.nome);
}

/**
 * @brief Remove o primeiro item encontrado com o nome especificado.
 * @note Requisito 3: Remoção por nome.
 */
void removerItemLista() {
    if (mochilaLista == NULL) {
        printf("⚠️ Mochila (Lista) vazia. Nada para remover.\n");
        return;
    }

    char nomeParaRemover[30];
    printf("Informe o Nome do Item para remover: ");
    if (scanf(" %29[^\n]", nomeParaRemover) != 1) return;

    No *atual = mochilaLista;
    No *anterior = NULL;

    // Busca o nó a ser removido
    while (atual != NULL && strcmp(atual->dados.nome, nomeParaRemover) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) {
        printf("🗑️ Removendo Item: **%s**\n", atual->dados.nome);

        if (anterior == NULL) {
            // O nó a ser removido é o primeiro (cabeça)
            mochilaLista = atual->proximo;
        } else {
            // O nó a ser removido está no meio ou fim
            anterior->proximo = atual->proximo;
        }

        free(atual); // Libera a memória do nó removido
        printf("✅ Item removido da lista encadeada.\n");
    } else {
        printf("❌ Item '%s' não encontrado na lista encadeada.\n", nomeParaRemover);
    }
}

/**
 * @brief Lista todos os itens da lista encadeada.
 */
void listarItensLista() {
    printf("\n--- 📝 Inventário (Lista Encadeada) ---\n");
    if (mochilaLista == NULL) {
        printf("⚠️ Mochila vazia.\n");
        return;
    }

    printf("| %-29s | %-19s | %-10s |\n", "NOME", "TIPO", "QUANTIDADE");
    printf("----------------------------------------------------------------\n");

    No* atual = mochilaLista;
    while (atual != NULL) {
        printf("| %-29s | %-19s | %-10d |\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("----------------------------------------------------------------\n");
}

/**
 * @brief Busca sequencial na lista encadeada, contando as comparações.
 * @note A lista encadeada não suporta busca binária.
 */
void buscarSequencialLista(const char *nomeBusca) {
    contadorComparacoes = 0;
    No* atual = mochilaLista;
    int encontrado = 0;

    while (atual != NULL) {
        contadorComparacoes++; // Uma comparação de string
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("✅ Busca Sequencial (Lista): Item '%s' Encontrado!\n", nomeBusca);
            printf("> Tipo: %s | Quantidade: %d\n", atual->dados.tipo, atual->dados.quantidade);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("❌ Busca Sequencial (Lista): Item '%s' não encontrado.\n", nomeBusca);
    }
    printf("➡️ Comparações realizadas (Sequencial): %lld\n", contadorComparacoes);
}

// ====================================================================
//                          FUNÇÃO PRINCIPAL E MENU
// ====================================================================

void menuVetor() {
    int opcao;
    char nomeBusca[30];

    do {
        listarItensVetor();
        printf("\n--- MOCHILA (VETOR) MENU ---\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Ordenar por Nome\n");
        printf("4. Buscar Sequencial\n");
        printf("5. Buscar Binária (Exige ordenação!)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("----------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\n⚠️ Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n');
            opcao = -1; // Força repetição
            continue;
        }

        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: ordenarVetor(); break;
            case 4:
                printf("Nome para Busca Sequencial: ");
                if (scanf(" %29[^\n]", nomeBusca) == 1) buscarSequencialVetor(nomeBusca);
                break;
            case 5:
                printf("Nome para Busca Binária: ");
                if (scanf(" %29[^\n]", nomeBusca) == 1) buscarBinariaVetor(nomeBusca);
                break;
            case 0: break;
            default: printf("\n⚠️ Opção inválida.\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...\n");
            while (getchar() != '\n');
            getchar();
        }

    } while (opcao != 0);
}

void menuLista() {
    int opcao;
    char nomeBusca[30];

    do {
        listarItensLista();
        printf("\n--- MOCHILA (LISTA ENCADEADA) MENU ---\n");
        printf("1. Inserir Item (O(1))\n");
        printf("2. Remover Item\n");
        printf("3. Buscar Sequencial\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("--------------------------------------\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\n⚠️ Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3:
                printf("Nome para Busca Sequencial: ");
                if (scanf(" %29[^\n]", nomeBusca) == 1) buscarSequencialLista(nomeBusca);
                break;
            case 0: break;
            default: printf("\n⚠️ Opção inválida.\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...\n");
            while (getchar() != '\n');
            getchar();
        }

    } while (opcao != 0);
}

int main() {
    int escolha;

    printf("=== ⚔️ SIMULADOR DE INVENTÁRIO CRÍTICO (Vetor vs. Lista) ⚔️ ===\n");
    printf("Escolha a estrutura de dados para gerenciar sua mochila:\n");

    do {
        printf("\n--- Menu de Escolha de Estrutura ---\n");
        printf("1. 🟦 Vetor (Lista Sequencial - Fixo, Rápido na Busca Binária)\n");
        printf("2. 🔗 Lista Encadeada (Estrutura Dinâmica - Flexível na Inserção/Remoção)\n");
        printf("0. 🚪 Sair do Jogo\n");
        printf("------------------------------------\n");
        printf("Escolha: ");

        if (scanf("%d", &escolha) != 1) {
            printf("\n⚠️ Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (escolha) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 0:
                printf("\n👋 Jogo encerrado. As escolhas de estrutura são vitais para a performance!\n");
                // Liberação de memória da lista (boa prática)
                No *atual = mochilaLista;
                while (atual != NULL) {
                    No *temp = atual;
                    atual = atual->proximo;
                    free(temp);
                }
                break;
            default:
                printf("\n⚠️ Opção inválida. Tente novamente.\n");
        }

    } while (escolha != 0);

    return 0;
}