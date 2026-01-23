#ifndef state_machine_logic_include
#define state_machine_logic_include

// struct representing states
typedef struct curr_state {
    int state_A;
    int state_B;
} curr_state_t;
curr_state_t curr_states;

void InitializeStates();
void stateMachine(int state_A, int state_B);

// enums of states to be used for switch cases
typedef enum {
    LED12A_state, LED1A_state,  LED2A_state,  LED3A_state,
    LED4A_state,  LED5A_state,  LED6A_state,  LED7A_state,
    LED8A_state,  LED9A_state,  LED10A_state, LED11A_state
} LEDA_states;

typedef enum {
    LED12B_state, LED1B_state,  LED2B_state,  LED3B_state,
    LED4B_state,  LED5B_state,  LED6B_state,  LED7B_state,
    LED8B_state,  LED9B_state,  LED10B_state, LED11B_state
} LEDB_states;

#endif /* state_machine_logic_include */
