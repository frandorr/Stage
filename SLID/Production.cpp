#include "Production.h"

/**
 * Constructor
 * @param lhs left-hand side
 * @param rhs right-hand side
 * @param size |rhs|+1
 */
Production::Production(int lhs, int * rhs, int size)
{
	lhs_ = lhs;
	rhs_ = rhs;
	size_ = size+1;
}

/**
 * Destructor, delete rhs
 */
Production::~Production()
{
	delete[] rhs_;
}

/**
 * replace nonTerminal by given rhs
 * @param nonTerminal non terminal
 * @param rhs         rhs to replace non terminal
 */
void Production::unfoldNonTerminal(shared_ptr<Production>  nT, queue<int> & electionQueue)
{
	int * rhs = nT->getRHS();

	int nonTerminal = nT->getLHS();

	vector<int> newRHSVec;
	
	//if I have a rule with disjunction I could have many "elections". That's
	//why I should pick the right one
	int election;

	for(int i = 0; i<size_-1; i++)
	{
		if(rhs_[i] == nonTerminal)
		{
			if(electionQueue.empty())
			{
				election = 0;
			}
			else
			{
				election = electionQueue.front();
				electionQueue.pop();		
			}
			
			if(election != -1)
			{
				// the election start and end in my sequence
				int start = nT->getElectionStartPos(election);
				int end = nT->getElectionEndPos(election);

				for(int j = start; j<end; j++)
				{
					newRHSVec.push_back(rhs[j]);
				}

			}

		}
		else
		{
			newRHSVec.push_back(rhs_[i]);
		}
	}

	delete[] rhs_;

	rhs_ = new int[newRHSVec.size()];
	size_ = newRHSVec.size()+1;

	for(unsigned int i = 0; i< newRHSVec.size(); i++)
	{
		rhs_[i] = newRHSVec[i];
	}
}

/**
 * Get the start position of an Inside election
 * @param  election number
 * @return          start position in production rhs
 */
int Production::getElectionStartPos(int election) const 
{

	for(int i = 0 ; i<size_-1 ; i++)
	{
		if(election == 0)
		{
			return i;
		}
		if(rhs_[i] == 2)
		{
			election--;
		}
	}

	cerr << "Election out of limit ..." << election << endl;

	exit(1);
}

/**
 * get the end position of an Inside election
 * @param  election number
 * @return          end position in production rhs
 */
int Production::getElectionEndPos(int election) const
{
	for (int i = getElectionStartPos(election); i<size_-1; i++)
	{
		if(rhs_[i] == 2)
		{
			return i;
		}
	}
	return size_-1 ;
}


/**
 * if the production has many possible branches, return as a vector 
 * the one given by opt
 * @param opt option to return
 * @return a vector containing the option
 */
vector<int> Production::getOption(int opt) const
{
	int countPipe = 0;
	vector<int> res;
	int *rhs = getRHS();

	for(int i = 0; i<size_-1;i++)
	{
		if(rhs[i] == 2)
	  {
	  	countPipe++;
	  	i++;
	  }

		if(countPipe == opt)
		{
	    res.push_back(rhs[i]);
			
		}

	}

	return res;
}

/**
 * get Production size
 * @return size_ (|rhs|+1)
 */
int Production::getSize() const
{
	return size_;
}

/**
 * get Production rhs
 * @return rhs_
 */
int * Production::getRHS() const
{
	return rhs_;
}

/**
 * get Production lhs
 * @return lhs_
 */
int Production::getLHS() const
{
	return lhs_;
}


/**
 * Print Production
 */
ostream& operator<<(ostream& cout, const Production &p)
{
	int * rhs = p.getRHS();
	cout << p.getLHS() << " --> ";
	for(int i = 0; i<p.getSize()-1; i++)
	{
		if(rhs[i] > 6){

		 cout <<  rhs[i] << " ";
		}
		else {
			// assert(rhs[i]!=37);
			cout << toChar(rhs[i]) << " ";
		}
	}

  return cout;
}
