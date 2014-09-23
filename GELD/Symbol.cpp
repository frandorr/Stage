#include "Symbol.h"

/**
 * Constructor
 * @param alphSize
 */
Symbol::Symbol(int alphSize)
{
	alphSize_ = alphSize;
	currentSymbol_ = alphSize+1;
}

/**
 * Destructor
 */
Symbol::~Symbol(){}

/**
 * check if a number is non terminal
 * @param  symbol
 * @return boolean
 */
bool Symbol::isNonTerminal(int symbol) const
{
	return (symbol > 6);
}


int Symbol::getFirstNonTerminal() const
{
	return alphSize_+1;
}

/**
 * Get the start symbol number
 * @return
 */
int Symbol::getStartSymbol() const
{
	return -1;
}

/**
 * get a non terminal and increments the currentSymbol counter
 * @return nonterminal
 */
int Symbol::getNonTerminal()
{
	int res = currentSymbol_;
	currentSymbol_++;
	return res;
}

void Symbol::increaseNonTerminal(int n)
{
	currentSymbol_+= n;
}

/**
 * check if a number is terminal
 * @param  symbol number
 * @return        boolean
 */
bool Symbol::isTerminal(int symbol) const
{
	return (symbol >= 7);
}

/**
 * check if a number is a delimiter
 * @param  symbol
 * @return        boolean
 */
bool Symbol::isDelimiter(int symbol) const
{
	return (symbol == 1);
}

/**
 * Get the current symbol
 * @return currentSymbol_
 */
int Symbol::getCurrentSymbol() const
{
	return currentSymbol_;
}

// Print

/**
 * Overload << operator to cout the Symbol
 */
ostream& operator<<(ostream& cout, const Symbol &s)
{
	cout << s.getCurrentSymbol();

  return cout;
}
