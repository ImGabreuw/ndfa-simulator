#include "automaton.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int set_alphabet(Automaton *a, const char *alphabet_str) {
    int len = strlen(alphabet_str);
    if (len < 1 || len > MAX_SYMBOLS) {
        printf("Erro: O tamanho do alfabeto deve ser entre 1 e %d.\n", MAX_SYMBOLS);
        return EXIT_FAILURE;
    }
    if (alphabet_str[0] != 'a') {
        printf("Erro: O alfabeto deve iniciar com 'a'.\n");
        return EXIT_FAILURE;
    }
    // Verificar se os símbolos estão em ordem alfabética
    for (int i = 1; i < len; i++) {
        if (alphabet_str[i] < alphabet_str[i-1]) {
            printf("Erro: O alfabeto não está em ordem alfabética.\n");
            return EXIT_FAILURE;
        }
    }

    strcpy(a->alphabet, alphabet_str);
    a->num_symbols = len;
    return EXIT_SUCCESS;
}

void init_transitions(Automaton *a) {
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            a->transitions[i][j].count = 0;
        }
    }
}

int set_transition(Automaton *a, int state_from, char symbol, int state_to) {
    // Encontrar o índice do símbolo no alfabeto
    int index = -1;
    for (int i = 0; i < a->num_symbols; i++) {
        if (a->alphabet[i] == symbol) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Erro: Símbolo '%c' não pertence ao alfabeto.\n", symbol);
        return EXIT_FAILURE;
    }

    // Verifica se os estados são válidos
    if (state_from < 0 || state_from >= a->num_states || state_to < 0 || state_to >= a->num_states) {
        printf("Erro: Estado inválido na transição %d -> %d.\n", state_from, state_to);
        return EXIT_FAILURE;
    }

    TransitionList *tlist = &a->transitions[state_from][index];
    if (tlist->count >= MAX_STATES) {
        printf("Erro: Limite de transições excedido para o estado %d com símbolo '%c'.\n", state_from, symbol);
        return 1;
    }

    tlist->dest[tlist->count++] = state_to;
    return 0;
}

bool is_final_state(Automaton *a, int state) {
    for (int i = 0; i < a->num_final_states; i++) {
        if (a->final_states[i] == state) {
            return true;
        }
    }
    return false;
}

int walk(Automaton *a, int current_state, const char *word, int pos) {
    // Se chegamos ao fim da palavra, verifica se o estado atual é final
    if (word[pos] == '\0') {
        return is_final_state(a, current_state) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    
    // Obter o símbolo atual e seu índice no alfabeto
    char symbol = word[pos];
    int symbol_index = -1;
    for (int i = 0; i < a->num_symbols; i++) {
        if (a->alphabet[i] == symbol) {
            symbol_index = i;
            break;
        }
    }

    if (symbol_index == -1) {
        // Símbolo não pertence ao alfabeto: falha nessa ramificação
        return EXIT_FAILURE;
    }
    
    TransitionList *tlist = &a->transitions[current_state][symbol_index];
    // Se não houver transição para esse símbolo:
    //   se o estado atual é final, consideramos o caminho como aceito (ignorando os símbolos restantes)
    //   caso contrário, esse caminho falha.
    if (tlist->count == 0) {
        return is_final_state(a, current_state) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    
    // Testa cada transição possível recursivamente
    for (int i = 0; i < tlist->count; i++) {
        int dest = tlist->dest[i];
        if (walk(a, dest, word, pos + 1) == 0) {
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE; 
}

int check(Automaton *a, const char *word) {
    return walk(a, 0, word, 0);
}
