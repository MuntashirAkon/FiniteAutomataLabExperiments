//
// eClosures.h
// FiniteAutomataLabExperiments
//
// Created by Muntashir Al-Islam at 5 December, 2018
// Copyright (c) 2018 Muntashir Al-Islam. All rights reserved.
//

#ifndef ECLOSURES_H_
#define ECLOSURES_H_

#include <string>
#include <vector>

// Define types
typedef unsigned int state;
typedef char input_symbol;

using std::string;
using std::vector;

/**
 e closures finding class.
 */
class ENFA {
 public:
  // Epsilon is taken as constant
  static const input_symbol EPSILON;

  /**
   Constructor.
   @param n_states Total states
   @param input_symbols Total input symbols
   @param start_state Start state
   @param accepting_states Accepting states
   */
  ENFA(int n_states, const vector<input_symbol> &input_symbols,
       state start_state, const vector<state> &accepting_states);

  /**
   Evaluate the given string.
   @param str String evaluate
   @param print_states Whether to output states to the standard output
   @return True on accepted, false on rejected
   */
  bool evaluate(const string &str);

  /**
   Find e-closures starting with some state

   NOTE: This is a recursive function
   @param i_state Input state (default: 0)
   */
  void findEClosures(state i_state = 0);

  /**
   Find epsilon state for some state and save them to t_state

   NOTE: This is a recursive function
   @param i_state Input state
   */
  void findEStates(state i_state);

  /**
   Print all e-closures
   */
  void printEClosures();

  /**
   Insert data into transition table.
   @param q Current state
   @param e Input symbol to set
   @param s Destination state
   */
  void set_state(state q, input_symbol e, state s);

  /**
   Transition function.
   @param q Current state
   @param e Input symbol from the current state
   @return Next state based on the input symbol
   */
  vector<state> tf(const vector<state> &q, input_symbol e);

 private:
  // Accepting states
  const vector<state> accepting_states;

  // Current state
  vector<state> current_state;

  // Input symbols
  const vector<input_symbol> input_symbols;

  // Calculated e-closures
  vector< vector<state> > e_closures;

  // Location of epsilon in the input symbols table
  int epsilon_loc;

  // Total states
  const int n_states;

  // Total input symbols
  int n_input_symbols;

  // Start state
  const state start_state;

  // Temporary subset of states
  vector<state> t_state;

  // Transition table
  vector< vector< vector<state> > > transition_table;

  /**
   Get index by input symbol.
   @param e Input symbol
   @return Index of input_symbols array
   */
  int get_index_by_input_symbol(input_symbol e);

  /**
   Whether a set of states has at least one accepting state.
   @param states Set of states
   @return True if it has at least one accepting state, false otherwise
   */
  bool has_accepting_state(vector<state> states);

  /**
   Find if the given state is an accepting state.
   @param q State to check for
   @return True if given state is an accepting state, false otherwise
   */
  bool is_accepting_state(state q);
};

#endif  // ECLOSURES_H_
