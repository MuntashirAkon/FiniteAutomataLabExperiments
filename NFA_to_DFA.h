//
// NFA_To_DFA.h
// FiniteAutomataLabExperiments
//
// Created by Muntashir Al-Islam at 14 November, 2018
// Copyright (c) 2018 Muntashir Al-Islam. All rights reserved.
//

#ifndef NFA_TO_DFA_H_
#define NFA_TO_DFA_H_

#include <vector>
#include <string>

// Define types
typedef unsigned int state;
typedef char input_symbol;

using std::vector;

/**
 NFA to DFA conversion class.
 
 A simple class to convert from non-deterministic finite automata to
 deterministic finite automata using lazy evaluation technique.
 */
class NFAToDFA {
 public:
  // Epsilon is taken as constant
  static const input_symbol EPSILON;

  /**
   Constructor.
   @param n_states Total states
   @param input_symbols Input symbols
   @param start_states Start state (DFA state)
   @param accepting_states Accepting states
   */
  NFAToDFA(int n_states, const vector<input_symbol> &input_symbols,
           const vector<state> &start_states,
           const vector<state> &accepting_states);

  /**
   Construct DFA from NFA.

   Lazy evaluation technique is used instead of subset construction technique.
   In the lazy evaluation technique, the irrelevant subsets are not visited. As
   a result, provided the DFA doesn't contain all possible subsets of the NFA
   states, the exponential growth can be reduced significantly.

   NOTE: This is a recursive function.

   @param q Initialized with start state (DFA state)
   */
  void construct(const vector<state> &q);

  /**
   Output DFA transision table to the standard output

   Start state has a `->` and accepting states have `*` beside them.
   */
  void print_DFA_transition_table();

  /**
   Output NFA transision table to the standard output, useful for debugging.

   Start state has a `->` and accepting states have `*` beside them.
   */
  void print_NFA_transition_table();

  /**
   Print visited set of states (DFA state), useful for debugging.
   */
  void print_visited();

  /**
   Insert data into transition table.
   @param q Current NFA state
   @param e Input symbol to set
   @param s Destination NFA state
   */
  void set_state(state q, input_symbol e, state s);

  /**
   Transition function.
   @param q Current states
   @param e Input symbol from the current state
   @return Next states based on the input symbol
   */
  vector<state> tf(const vector<state> &q, input_symbol e);

 private:
  // Accepting states
  const vector<state> accepting_states;

  // Whether the any has any epsilon transition
  bool has_epsilon;

  // Input symbols: EPSILON if exists has to be the last symbol
  const vector<input_symbol> input_symbols;

  // Total states
  const int n_states;

  // Total input symbols
  const int n_input_symbols;

  // Start states
  const vector<state> start_state;

  // Transition table
  vector< vector< vector<state> > > transition_table;

  // Visited states: subset of total states and each is a state of DFA
  vector< vector<state> > visited_states;

  /**
   Add a set of states to the visited list.
   @param states Set of states (DFA state)
   */
  void add_to_visited(vector<state> states) {
    visited_states.push_back(states);
  }

  /**
   Get index by input symbol.
   @param e Input symbol
   @return Index of input_symbols array
   */
  int get_index_by_input_symbol(input_symbol e);

  /**
   Whether a set of states (DFA state) has at least one accepting state.
   @param states Set of states (DFA state)
   @return True if it has at least one accepting state, false otherwise
   */
  bool has_accepting_state(const vector<state> &states);

  /**
   Find if the given NFA state is an accepting state.
   @param q NFA state
   @return True if the given state is an accepting state, false otherwise
   */
  bool is_accepting_state(state q);

  /**
   Assign a set of NFA states (DFA state) a letter.
   @param states Set of states (DFA state)
   */
  char states_to_state(const vector<state> &states);

  /**
   Whether the given set of state is visited already.
   @param states Set of states (subset of all states)
   @return True if visited, otherwise false
   */
  bool visited(const vector<state> &states);
};

#endif  // NFA_TO_DFA_H_
