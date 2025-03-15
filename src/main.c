#include <stdio.h>
#include <stdlib.h>

#include "automaton.h"

int main(void)
{
    Automaton automaton;

    if (set_alphabet(&automaton, "abcde") != 0)
    {
        return EXIT_FAILURE;
    }

    automaton.num_states = 5;

    init_transitions(&automaton);

    /* Configuração de transições (exemplo):
       q0 --'a'--> q1
       q0 --'a'--> q2   (duas transições diferentes para o símbolo 'a')
       q1 --'b'--> q3
       q2 --'c'--> q3
       q3 --'d'--> q4
    */
    set_transition(&automaton, 0, 'a', 1);
    set_transition(&automaton, 0, 'a', 2); // Outra transição para 'a' a partir de q0
    set_transition(&automaton, 1, 'b', 3);
    set_transition(&automaton, 2, 'c', 3);
    set_transition(&automaton, 3, 'd', 4);

    // Definir os estados finais (exemplo: apenas q4 é final)
    automaton.num_final_states = 1;
    automaton.final_states[0] = 4;

    const char *word1 = "abd"; // Pode ser rejeitada se não houver caminho completo
    const char *word2 = "acd"; // Caminho: q0->(a)q2->(c)q3->(d)q4 => Aceita

    int res1 = check(&automaton, word1);
    int res2 = check(&automaton, word2);

    printf("Palavra \"%s\" é %s.\n", word1, res1 == 0 ? "válida" : "inválida");
    printf("Palavra \"%s\" é %s.\n", word2, res2 == 0 ? "válida" : "inválida");

    return EXIT_SUCCESS;
}
