#ifndef PRODUCTION_H_
#define PRODUCTION_H_


#include "Utils.h"
#include "Symbol.h"
#include "Production.h"

class Production{
private:
  int lhs_;
  int* rhs_;
  int size_;


public:
	// constructor
	Production(int lhs, int* rhs, int size);
	// destructor
	~Production();

	void unfoldNonTerminal(shared_ptr<Production>  nT, queue<int> & electionQueue);
	vector<int> getOption(int opt) const;
	int getElectionStartPos(int election) const;
	int getElectionEndPos(int election) const;
	//Getters:
	int getSize() const;
	int * getRHS() const;
	int getLHS() const;

	friend ostream& operator<<(ostream& cout, const Production &p);

};

#endif /* PRODUCTION_H_*/
