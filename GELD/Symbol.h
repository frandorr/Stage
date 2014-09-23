#ifndef SYMBOL_H_
#define SYMBOL_H_


#include "Utils.h"

class Symbol{

private:
	int currentSymbol_ ;
	int alphSize_;

public:
	// constructor
	Symbol(int alphSize);
	// destructor
	~Symbol();

	bool isNonTerminal(int symbol) const ;
	bool isTerminal(int symbol) const ;
	bool isDelimiter(int symbol) const ;
	int getFirstNonTerminal() const;
	int getStartSymbol() const ;
	int getNonTerminal() ;
	void increaseNonTerminal(int n);
	int getCurrentSymbol() const ;

		// Print
	friend ostream& operator<<(ostream& cout, const Symbol &s);
};

#endif /* SYMBOL_H_*/
