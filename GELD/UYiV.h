#ifndef UYIV_H_
#define UYIV_H_

//STL

//Boost

//User
#include "Utils.h"
#include "Word.h"
#include "WordList.h"



using namespace std;

/*A UYiV is a class that represents contexts (u, v) and the y_i words where they
can be applied.*/


class UYiV
{
private:
	shared_ptr<Word> u_;
	shared_ptr<Word> v_;

	WordList* y_;
	list <std::pair<int,int> > * wordPosPairs_;


public:
	UYiV(shared_ptr<Word> u, shared_ptr<Word> v, WordList* y, list <std::pair<int,int> > * wordPosPairs);
	~UYiV();

	// int getEncoding() const;
	shared_ptr<Word> getU() const;
	shared_ptr<Word> getV() const;
	WordList* getYList() const;
	list <std::pair<int,int> > * getWordsPosPairs() const;
	// Getters


	// Print
	friend ostream& operator<<(ostream& cout, const UYiV &uyv);

};

#endif /* UYIV_H_*/
