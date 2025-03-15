// abordagem moderna em relação ao #ifdef para reduzir a chance de erros de múltipla inclusão.
#pragma once

#include <stdbool.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10
#define MAX_WORD_LENGTH 100

typedef struct
{
    int dest[MAX_STATES]; // Lista de estados de destino
    int count;            // Quantidade de destinos armazenados
} TransitionList;

typedef struct
{
    char alphabet[MAX_SYMBOLS];                          // string do alfabeto (ex: "abcde")
    int num_symbols;                                     // quantidade de símbolos do alfabeto
    int num_states;                                      // número de estados (|Q|)
    TransitionList transitions[MAX_STATES][MAX_SYMBOLS]; // matriz de transições: -1 indica transição não definida
    int final_states[MAX_STATES];                        // array dos estados finais
    int num_final_states;                                // quantidade de estados finais (F)
} Automaton;

/**
 * @brief Configura o alfabeto do autômato. Valida se a string informada está em ordem alfabética iniciando com 'a'
 *
 * @param alphabet_str String com os símbolos do alfabeto sem espaços
 *
 * @return Retorna 0 em caso de sucesso ou 1 se ocorrer algum erro
 */
int set_alphabet(Automaton *a, const char *alphabet_str);

/**
 * @brief Inicializa a matriz de transições com -1 (indicando transição inexistente).
 */
void init_transitions(Automaton *a);

/**
 * @brief configura uma transição do autômato.
 *
 * @param state_from estado de partida
 * @param symbol símbolo que dispara a transição
 * @param state_to estado de chegada
 *
 * @return Retorna 0 em caso de sucesso ou 1 se ocorrer um erro (por exemplo, símbolo inválido ou estado fora do intervalo).
 */
int set_transition(Automaton *a, int state_from, char symbol, int state_to);

/**
 * @brief Verifica se um estado é final.
 *
 * @param state estado a ser verificado
 *
 * @return Retorna true se for final, ou false caso contrário.
 */
bool is_final_state(Automaton *a, int state);

/**
 * @brief Percorre o autômato com base em uma palavra de entrada. Inicia sempre no estado 0.
 *
 * @param word palavra a ser reconhecido pelo autômato
 *
 * @return Retorna 0 se a palavra for aceita (terminar em um estado final) ou 1 se for rejeitada.
 */
int walk(Automaton *a, int current_state, const char *word, int pos);

int check(Automaton *a, const char *word);