#ifndef GRAMMAR_H_
#define GRAMMAR_H_


#include "Utils.h"
#include "Production.h"

class Grammar{
private:
  //symbol representing the start non terminal
  shared_ptr<Production> startProd_;
  list<shared_ptr<Production> >* prods_;
  int size_;

public:
	// constructor
	Grammar(list<shared_ptr<Production> >* prods);
	// destructor
	~Grammar();

	int* convertToInt() const;
  void addProd(shared_ptr<Production> p);
	int getSize() const;

	list<shared_ptr<Production> >* getProds() const ;

	void unfoldNonTerminal(int nonTerminal, queue<int> & electionQueue);
	void deleteProd(shared_ptr<Production> p);

	shared_ptr<Production> getProdByLHS(int lhs) const;

	// Print
	friend ostream& operator<<(ostream& cout, const Grammar &g);
};

#endif /* GRAMMAR_H_*/
