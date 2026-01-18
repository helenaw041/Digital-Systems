#ifndef state_machine_logic_include
#define state_machine_logic_include

typedef struct state {
    int next_state;
    int output;
} state_t;
state_t LEDA_states[12];
state_t LEDB_states[12];

void InitializeStates();

// int GetNextState(int current_state);

// int GetStateOutputGPIOA(int current_state, int index, int aorb);

// int GetStateOutputGPIOB(int current_state, int index, int aorb);

/* Define states as constants */
// #define OFF 0
// #define ON1  1
// #define ON2  2

#endif /* state_machine_logic_include */
