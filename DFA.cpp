//
// DFA.cpp
// FiniteAutomataLabExperiments
//
// Created by Muntashir Al-Islam at 27 October, 2018
// Copyright (c) 2018 Muntashir Al-Islam. All rights reserved.
//

#include "./DFA.h"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Constructor.
DFA::DFA(int n_states, const vector<input_symbol> &input_symbols,
         state start_state, const vector<state> &accepting_states)
         : n_states(n_states), input_symbols(input_symbols),
         start_state(start_state), accepting_states(accepting_states),
         n_input_symbols(input_symbols.size()) {
    // Push rows to the transition table to create an empty 2D array
  while (n_states--) {
    vector< state > t_row(n_input_symbols);
    transition_table.push_back(t_row);
  }
}

// Evaluate the given string.
bool DFA::evaluate(const string &str, bool print_states) {
  reset_current_state();
  if (print_states) cout << "Transitions: ";
  for (int i = 0; i < str.length(); ++i) {
    if (print_states) cout << " -> q" << get_current_state();
    tf(get_current_state(), str[i]);
  }
  if (print_states) cout << " -> q" << get_current_state() << endl;
  return is_accepting_state();
}

// Get index by input symbol.
int DFA::get_index_by_input_symbol(input_symbol e) {
  int n = input_symbols.size();
  while (n--)
    if (e == input_symbols[n]) return n;
  return -1;
}

// Find if the given state is an accepting state.
bool DFA::is_accepting_state(state q) {
  int n = accepting_states.size();
  while (n--)
    if (q == accepting_states[n]) return true;
  return false;
}

// Output transision table to the standard output, useful for debugging.
void DFA::print_transition_table() {
  cout << "Transition Table\n       ";
  for (int j = 0; j < n_input_symbols; ++j)
    cout << " |  " << static_cast<char>(input_symbols[j]);
  cout << " |\n-------";
  for (int j = 0; j < n_input_symbols; ++j) cout << "-----";
  cout << "--\n";

  for (int i = 0; i < n_states; ++i) {
    cout << (i == start_state ? "-> " : "   ")
         << (is_accepting_state(i) ? "* ": "  ")
         << 'q' << i;
    for (int j = 0; j < n_input_symbols; ++j) {
      cout << " | " << 'q' << tf(i, input_symbols[j]);
    }
    cout << " |\n";
  }
  cout << endl;
}
