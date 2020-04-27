//
// eClosures_example.cpp
// FiniteAutomataLabExperiments
//
// Created by Muntashir Al-Islam at 5 December, 2018
// Copyright (c) 2018 Muntashir Al-Islam. All rights reserved.
//

//
// Problem: Find e-closures for the following eNFA
// |     |  ε   |  a   |  b   | c    |
// |-----|------|------|------|------|
// |→ q0 |  ∅   | {q0} | {q1} | {q2} |
// |  q1 | {q0} | {q1} | {q2} |  ∅   |
// |* q2 | {q1} | {q2} |  ∅   | {q2} |
//
// Where → denotes start state and * denotes accepting states,
// and ε denotes epsilon input symbol
//
// Rejected examples: a*ba*
//

#include <iostream>
#include <string>
#include <vector>

#include "eClosures.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// Main
int main() {
  int n_states = 3;
  state start_state = 0;
  vector<state> accepting_states;
  accepting_states.push_back(2);
  vector<input_symbol> input_symbols;
  input_symbols.push_back('a');
  input_symbols.push_back('b');
  input_symbols.push_back('c');
  input_symbols.push_back(ENFA::EPSILON);

  ENFA aENFA(n_states, input_symbols, start_state, accepting_states);
  // Transition table
  aENFA.set_state(0, 'a', 0);
  aENFA.set_state(0, 'b', 1);
  aENFA.set_state(0, 'c', 2);
  aENFA.set_state(1, ENFA::EPSILON, 0);
  aENFA.set_state(1, 'a', 1);
  aENFA.set_state(1, 'b', 2);
  aENFA.set_state(2, ENFA::EPSILON, 1);
  aENFA.set_state(2, 'a', 2);
  aENFA.set_state(2, 'c', 1);
  // Find e-closures
  aENFA.findEClosures();
  aENFA.printEClosures();
  // Match string
  string str;
  while (true) {
    cout << "Enter a string: "; cin >> str;
    if (str == "-1") break;
    bool status = aENFA.evaluate(str);
    cout << "Status: "
         << (status ? "Accepted" : "Rejected")
         << "\n" << endl;
  }
  return 0;
}
