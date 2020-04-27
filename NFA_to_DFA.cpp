//
// NFA_To_DFA.cpp
// FiniteAutomataLabExperiments
//
// Created by Muntashir Al-Islam at 14 November, 2018
// Copyright (c) 2018 Muntashir Al-Islam. All rights reserved.
//

#include "./NFA_to_DFA.h"

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Init EPSILON
const input_symbol NFAToDFA::EPSILON = '\0';

// Constructor.
NFAToDFA::NFAToDFA(int n_states, const vector<input_symbol> &input_symbols,
                   const vector<state> &start_state,
                   const vector<state> &accepting_states)
                   : n_states(n_states), input_symbols(input_symbols),
                   start_state(start_state), accepting_states(accepting_states),
                   n_input_symbols(input_symbols.size()) {
  has_epsilon = false;
  while (n_states--) {
    vector< vector< state > > t_row(n_input_symbols);
    transition_table.push_back(t_row);
  }
}

// Construct DFA from NFA.
void NFAToDFA::construct(const vector<state> &q) {
  if (visited(q)) return;
  add_to_visited(q);
  vector<state> tmp_state;
  for (int i = 0; i < n_input_symbols; ++i) {
    tmp_state = tf(q, input_symbols[i]);
    if (tmp_state.size() != 0 && !visited(tmp_state)) {
      construct(tmp_state);
    }
  }
}

// Get index by input symbol.
int NFAToDFA::get_index_by_input_symbol(input_symbol e) {
  int n = n_input_symbols;
  while (n--)
    if (e == input_symbols[n]) return n;
  return -1;
}

// Whether a set of states (DFA state) has at least one end state.
bool NFAToDFA::has_accepting_state(const vector<state> &states) {
  for (int i = 0; i < states.size(); ++i) {
    if (is_accepting_state(states[i])) return true;
  }
  return false;
}

// Find if the given NFA state is an accepting state.
bool NFAToDFA::is_accepting_state(state q) {
  int n = accepting_states.size();
  while (n--)
    if (q == accepting_states[n]) return true;
  return false;
}

// Output DFA transision table to the standard output
void NFAToDFA::print_DFA_transition_table() {
  int dfa_n_input_symbols = n_input_symbols;
  if (!has_epsilon) --dfa_n_input_symbols;
  cout << "DFA Transition Table\n      ";
  for (int j = 0; j < dfa_n_input_symbols; ++j)
    cout << " | " << (input_symbols[j] == EPSILON ? 'E': input_symbols[j]);
  cout << " |\n------";
  for (int j = 0; j < dfa_n_input_symbols; ++j) cout << "----";
  cout << "--\n";
  vector<state> tmp_state;
  for (int j = 0; j < visited_states.size(); ++j) {
    cout << (start_state == visited_states[j] ? "-> " : "   ")
         << (has_accepting_state(visited_states[j]) ? "* ": "  ")
         << static_cast<char>('A' + j);
    for (int i = 0; i < dfa_n_input_symbols; ++i) {
        cout << " | " << states_to_state(
          tf(visited_states[j], input_symbols[i]));
    }
    cout << " |\n";
  }
  cout << "\nWhere:\n";
  for (int i = 0; i < visited_states.size(); ++i) {
    cout << states_to_state(visited_states[i]) << " = { ";
    int k = 0;
    for ( ; k < visited_states[i].size()-1; ++k)
      cout << 'q' << visited_states[i][k] << ", ";
    cout << 'q' << visited_states[i][k];
    cout << " }" << endl;
  }
}

// Output NFA transision table to the standard output, useful for debugging.
void NFAToDFA::print_NFA_transition_table() {
  cout << "NFA Transition Table\n     ";
  for (int j = 0; j < n_input_symbols; ++j)
    cout << "   |    " << (input_symbols[j] == EPSILON ? 'E': input_symbols[j]);
  cout << "   |\n-------";
  for (int j = 0; j < n_input_symbols; ++j) cout << "---------";
  cout << "--\n";

  for (int i = 0; i < n_states; ++i) {
    cout << (i == start_state[0] ? "-> " : "   ")
         << (is_accepting_state(i) ? "* ": "  ")
         << 'q' << i;
    for (int j = 0; j < n_input_symbols; ++j) {
      cout << " | { ";
      if (transition_table[i][j].size() > 0) {
        int k = 0;
        for ( ; k < transition_table[i][j].size()-1; ++k)
          cout << 'q' << transition_table[i][j][k] << ", ";
        cout << 'q' << transition_table[i][j][k];
      }
      cout << " }";
    }
    cout << " |\n";
  }
  cout << endl;
}


// Print visited set of states (DFA state), useful for debugging.
void NFAToDFA::print_visited() {
  vector<state> tmp_state;
  for (int j = 0; j < visited_states.size(); ++j) {
    for (int i = 0; i < visited_states[j].size(); ++i)
      cout << 'q' << visited_states[j][i] << " ";
    cout << "\t";
    for (int i = 0; i < n_input_symbols; ++i) {
      tmp_state = tf(visited_states[j], input_symbols[i]);
      cout << "\t" << i << " => ";
      for (int k = 0; k < tmp_state.size(); ++k)
        cout << 'q' << tmp_state[k] << " ";
    }
    cout << endl;
  }
}

// Insert data into transition table.
void NFAToDFA::set_state(state q, input_symbol e, state s) {
  if (e == EPSILON) has_epsilon = true;
  transition_table[q][get_index_by_input_symbol(e)].push_back(s);
}

// Assign a set of NFA states (DFA state) a letter.
char NFAToDFA::states_to_state(const vector<state> &states) {
  for (int i = 0; i < visited_states.size(); ++i) {
    if (visited_states[i] == states) return static_cast<char>('A'+i);
  }
  return '\0';  // To suppress compile time warning
}

// Transition function.
vector<state> NFAToDFA::tf(const vector<state> &q, input_symbol e) {
  vector<state> tmp_state;
  int index_e = get_index_by_input_symbol(e);
  for (int i = 0; i < q.size(); ++i) {
    for (int j = 0; j < transition_table[q[i]][index_e].size(); ++j) {
      bool found = false;
      for (int k = 0; k < tmp_state.size(); ++k) {
        if (tmp_state[k] == transition_table[q[i]][index_e][j]) {
          found = true;
          break;
        }
      }
      if (!found) tmp_state.push_back(transition_table[q[i]][index_e][j]);
    }
  }
  return tmp_state;
}

// Whether the given set of state is visited already.
bool NFAToDFA::visited(const vector<state> &states) {
  for (int i = 0; i < visited_states.size(); ++i) {
    if (visited_states[i] == states)
      return true;
  }
  return false;
}
