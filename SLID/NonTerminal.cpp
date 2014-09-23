#include "NonTerminal.h"

NonTerminal::NonTerminal(int symbol)
{
	symbol_ = symbol;
}


int NonTerminal::getSymbol() const
{
	return symbol_;
}

void NonTerminal::setSymbol(int symbol)
{
	symbol_ = symbol;
}