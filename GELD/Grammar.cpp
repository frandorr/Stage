#include "Grammar.h"


/**
 * Constructor
 * @param prods a list of Production
 */
Grammar::Grammar(list< shared_ptr<Production> >* prods)
{
	int totalSize = 0;
	startProd_ = prods->front();
	prods_ = prods;
	for(list<shared_ptr<Production> >::iterator it = prods->begin(); it!= prods->end(); ++it)
	{
		totalSize += (*it)->getSize();
	}
	size_ = totalSize;
}

/**
 * Destructor
 */
Grammar::~Grammar(){
	delete prods_;
	prods_ = NULL;
}

/**
 * Convert the grammar to an int array
 * @return int* seqGrammar
 */
int * Grammar::convertToInt() const
{
	int * seqGrammar = new int[size_];
	int prodRHSSize = 0;
	int * rhs;
	int i = 0;

	for(list<shared_ptr<Production> >::const_iterator it = prods_->begin(); it != prods_->end(); ++it)
	{
		prodRHSSize = (*it)->getSize()-1;
		rhs = (*it)->getRHS();
		for(int j = 0; j<prodRHSSize; j++)
		{

			seqGrammar[i+j] = rhs[j];
		}
		i += prodRHSSize;
		//each production is delimited by a symbols:
		seqGrammar[i] = 1;
		i++;
	}
	return seqGrammar;
}

void Grammar::addProd(shared_ptr<Production> p)
{
	prods_->push_back(p);
	size_ += p->getSize();
}

/**
 * Get Grammar size
 * @return size_
 */
int Grammar::getSize() const
{
	return size_;
}

/**
 * get Grammar Productions
 */
list<shared_ptr<Production> > * Grammar::getProds() const {
	return prods_;
}

/**
 * given a nonTerminal, look for it in each Production and replace it by its right side
 * @param nonTerminal nonTerminal to be replaced
 */
void Grammar::unfoldNonTerminal(int nonTerminal, queue<int> & electionQueue)
{
	shared_ptr<Production>  p = getProdByLHS(nonTerminal);
	int newSize = 0;

	//iterate over all productions unfolding the given nonTerminal
	for(list<shared_ptr<Production> >::iterator it = prods_->begin(); it != prods_->end(); ++it)
	{
		newSize = size_ - (*it)->getSize();

		//unfold the non terminal in the grammar
		(*it)->unfoldNonTerminal(p, electionQueue);

		//update grammar size
		size_ += newSize + (*it)->getSize();
	}
	//delete the unfolded prod from the grammar
	deleteProd(p);
}

/**
 * delete given production from grammar
 * @param p production to be deleted
 */
void Grammar::deleteProd(shared_ptr<Production> p)
{
	prods_->remove(p);
}


/**
 * get a Production by its LHS
 * @param  lhs a nonTerminal 
 * @return     production with such lhs
 */
shared_ptr<Production> Grammar::getProdByLHS(int lhs) const
{
	for(list<shared_ptr<Production> >::iterator it = prods_->begin(); it!=prods_->end(); ++it)
	{
		if ((*it)->getLHS() == lhs)
		{
			return *it;
		}
	}
	return NULL;
}

// Print

/**
 * cout overload for Grammar
 */
ostream& operator<<(ostream& cout, const Grammar &g)
{
	list<shared_ptr<Production> >* prods = g.getProds();
	for(list<shared_ptr<Production> >::iterator it = prods->begin(); it != prods->end(); ++it)
	{
		cout << *(*it) << endl;
	}

  return cout;
}


