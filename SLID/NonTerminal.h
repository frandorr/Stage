#ifndef NONTERMINAL_H_
#define NONTERMINAL_H_


#include "Utils.h"

class NonTerminal{
private:
  //symbol representing the non terminal
  int symbol_;

public:
	// constructor
	NonTerminal(int symbol);
	// destructor
	~NonTerminal();

  int getSymbol() const;
  void setSymbol(int symbol);


};

#endif /* NONTERMINAL_H_*/
