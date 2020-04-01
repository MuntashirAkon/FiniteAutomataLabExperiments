/**
 DFA Example file
 DFA_example.cpp
 Purpose: Match any string with substring `011`, `-1` to exit
 Created at 27 October, 2018
 @author Muntashir Al-Islam
 @version 1.0
*/
#include<iostream>
#include<string>
#include<vector>

#include "DFA.h"

using namespace std;

int main(){
    state start_state = 0;
    vector<state> accepting_states;
    accepting_states.push_back(3);
    vector<input_symbol> input_symbols;
    input_symbols.push_back('0');
    input_symbols.push_back('1');
    DFA str_011(4, input_symbols, start_state, accepting_states);
    // Transition table
    str_011.set_state(0,'0',1);
    str_011.set_state(0,'1',0);
    str_011.set_state(1,'0',1);
    str_011.set_state(1,'1',2);
    str_011.set_state(2,'0',1);
    str_011.set_state(2,'1',3);
    str_011.set_state(3,'0',3);
    str_011.set_state(3,'1',3);
    // Print transition table
    str_011.print_transition_table();
    
    string str;
    while(true){
        cout << "Enter a string: "; cin >> str;
        if(str == "-1") break;
        bool status = str_011.evaluate(str, true);
        cout << "Status: " << (status ? "Accepted" : "Rejected") << "\n" << endl;
    }
    return 0;
}
