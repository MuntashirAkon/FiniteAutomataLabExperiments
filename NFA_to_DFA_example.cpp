//
// NFA_To_DFA_example.cpp
// FiniteAutomataLabExperiments
//
// Created by Muntashir Al-Islam at 14 November, 2018
// Copyright (c) 2018 Muntashir Al-Islam. All rights reserved.
//

#include<iostream>
#include<vector>
#include<string>

#include "NFA_to_DFA.h"

using std::cin;
using std::cout;
using std::vector;

int main() {
  int n_states = 4;
  vector<state> start_state;  // Start state is a DFA state
  start_state.push_back(0);
  vector<state> accepting_states;
  accepting_states.push_back(3);
  vector<input_symbol> input_symbols;
  input_symbols.push_back('0');
  input_symbols.push_back('1');
  input_symbols.push_back(NFAToDFA::EPSILON);

  NFAToDFA ntd(n_states, input_symbols, start_state, accepting_states);
  // Transition table : NFA
  ntd.set_state(0, '0', 0);
  ntd.set_state(0, '0', 1);
  ntd.set_state(0, '1', 0);
  ntd.set_state(1, '0', 2);
  ntd.set_state(1, '1', 2);
  ntd.set_state(2, '0', 3);
  ntd.set_state(3, '0', 3);
  ntd.set_state(3, '1', 3);

  // Output
  // ntd.print_NFA_transition_table();
  ntd.construct(start_state);
  // ntd.print_visited();
  ntd.print_DFA_transition_table();
  return 0;
}
