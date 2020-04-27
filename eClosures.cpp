//
// eClosures.cpp
// FiniteAutomataLabExperiments
//
// Created by Muntashir Al-Islam at 5 December, 2018
// Copyright (c) 2018 Muntashir Al-Islam. All rights reserved.
//

#include "./eClosures.h"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Init EPSILON
const input_symbol ENFA::EPSILON = '\0';

// Constructor.
ENFA::ENFA(int n_states, const vector<input_symbol> &input_symbols,
           state start_state, const vector<state> &accepting_states)
           : n_states(n_states), input_symbols(input_symbols),
           start_state(start_state), accepting_states(accepting_states),
           n_input_symbols(input_symbols.size()) {
  current_state.push_back(start_state);
  epsilon_loc = get_index_by_input_symbol(EPSILON);
  // Init transition table and e closure
  while (n_states--) {
    vector< vector<state> > t_row(n_input_symbols);
    transition_table.push_back(t_row);
    vector<state> s_row;
    e_closures.push_back(s_row);
  }
}

// Evaluate the given string.
bool ENFA::evaluate(const string &str) {
    vector<state> s_state;
    s_state.push_back(start_state);
    bool found = true;
    for (int i = 0; i < str.length(); ++i) {
      vector<state> t_state = tf(s_state, str[i]);
      // DEBUG
      // cout << str[i] << ": ";
      // for (int j = 0; j < t_state.size(); ++j)
      //   cout << t_state[j] << ", ";
      // cout << endl;
      s_state = t_state;
      if (t_state.size() == 0) found = false;
    }
    // Reject even if found provided the final subset of states
    // doesn't have a accepting state
    if (found && !has_accepting_state(s_state)) found = false;
    return found;
}

// Find e-closures starting with some state
void ENFA::findEClosures(state i_state) {
  if (i_state == n_states) return;
  // Add default
  e_closures[i_state].push_back(i_state);
  findEStates(i_state);
  // Find others
  for (int j = 0; j < t_state.size(); ++j)
    e_closures[i_state].push_back(t_state[j]);
  t_state.clear();
  findEClosures(i_state + 1);
}

// Find epsilon state for some state and save them to t_state
void ENFA::findEStates(state i_state) {
  vector<state> e_states = transition_table[i_state][epsilon_loc];
  for (int i = 0; i < e_states.size(); ++i) {
    t_state.push_back(e_states[i]);
    findEStates(e_states[i]);
  }
}

// Get index by input symbol.
int ENFA::get_index_by_input_symbol(input_symbol e) {
  int n = n_input_symbols;
  while (n--)
    if (e == input_symbols[n]) return n;
  return -1;
}

// Whether a set of states has at least one accepting state.
bool ENFA::has_accepting_state(vector<state> states) {
  for (int i = 0; i < states.size(); ++i) {
    if (is_accepting_state(states[i])) return true;
  }
  return false;
}

// Find if the given state is an accepting state.
bool ENFA::is_accepting_state(state q) {
  int n = accepting_states.size();
  while (n--)
    if (q == accepting_states[n]) return true;
  return false;
}

// Print all e-closures
void ENFA::printEClosures() {
  for (int i = 0; i < e_closures.size(); ++i) {
    cout << "ECLOSE(" << 'q' << e_closures[i][0] << ") = { ";
    for (int q = 0; q < e_closures[i].size(); ++q) {
      cout << 'q' << e_closures[i][q] << ", ";
    }
    cout << "}" << endl;
  }
}

// Insert data into transition table.
void ENFA::set_state(state q, input_symbol e, state s) {
  transition_table[q][get_index_by_input_symbol(e)].push_back(s);
}

// Transition function.
vector<state> ENFA::tf(const vector<state> &q, input_symbol e) {
  vector<bool> tmp_state(n_states, false);
  int index_input_sym = get_index_by_input_symbol(e);
  // Iterate over each state
  vector<state>::const_iterator s;
  for (s = q.begin(); s != q.end(); ++s) {
    // Add states
    for (int j = 0; j < transition_table[*s][index_input_sym].size(); ++j) {
      vector<state> states =
          e_closures[transition_table[*s][index_input_sym][j]];
      for (int i = 0; i < states.size(); ++i)
        tmp_state[states[i]] = true;
    }
  }
  vector<state> out_state;
  for (int i = 0; i < n_states; ++i)
    if (tmp_state[i]) out_state.push_back(i);
  return out_state;
}
