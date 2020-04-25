//
// DFA.h
// FiniteAutomataLabExperiments
//
// Created by Muntashir Al-Islam at 27 October, 2018
// Copyright (c) 2018 Muntashir Al-Islam. All rights reserved.
//

#ifndef DFA_H_
#define DFA_H_

#include <string>
#include <vector>

// Define types
typedef unsigned int state;
typedef char input_symbol;

using std::string;
using std::vector;

/**
 Deterministic finite automata class
 
 In order to use this, states must be unsigned integers (starting from zero) and input symbols must be characters.
 */
class DFA {
 public:
  /**
   Constructor.
   @param n_states Total states
   @param n_input_symbols Total input symbols
   @param start_state Start state
   @param accepting_states Accepting states
   */
  DFA(int n_states, const vector<input_symbol> &input_symbols,
      state start_state, const vector<state> &accepting_states);

  /**
   Insert data into transition table.
   @param q Current state
   @param e Input symbol to set
   @param s Destination state
   */
  void set_state(state q, input_symbol e, state s) {
    transition_table[q][get_index_by_input_symbol(e)] = s;
  }

  /**
   Output transision table to the standard output, useful for debugging.

   Start state has a `->` and accepting states have `*` beside them.
   */
  void print_transition_table();

  /**
   Evaluate the given string.
   @param str String evaluate
   @param print_states Whether to output states to the standard output
   @return True on accepted, false on rejected
   */
  bool evaluate(const string &str, bool print_states = false);

  /**
   Transition function.
   @param q Current state
   @param e Input symbol from the current state
   @return Next state based on the input symbol
   */
  state tf(state q, input_symbol e) {
    return (current_state =
            transition_table[q][get_index_by_input_symbol(e)]);
  }

 private:
  // Total states
  const int n_states;

  // Total input symbols
  const int n_input_symbols;

  // Transition table
  vector< vector< state > > transition_table;

  // Start state
  const state start_state;

  // Accepting states
  const vector< state > accepting_states;

  // Input symbols
  const vector<input_symbol> input_symbols;

  // Current state for DFA::evaluate()
  state current_state;

  /**
   Find if the current state is an accepting state.
   @return True if current state is an accepting state, false otherwise
   */
  bool is_accepting_state() { return is_accepting_state(current_state); }

  /**
   Find if the given state is an accepting state.
   @param q State to check for
   @return True if given state is an accepting state, false otherwise
   */
  bool is_accepting_state(state q);

  /**
   Get current state.
   @return Current state
   */
  state get_current_state() { return current_state; }

  /**
   Reset current state, i.e. set current state to start state.
   */
  void reset_current_state() { current_state = start_state; }

  /**
   Get index by input symbol.
   @param e Input symbol
   @return Index of input_symbols array
   */
  int get_index_by_input_symbol(input_symbol e);
};

#endif  // DFA_H_
