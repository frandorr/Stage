#ifndef WORDLIST_H_
#define WORDLIST_H_

//STL

//Boost

//User
#include "Utils.h"
#include "Word.h"



using namespace std;

/*An WordList is a class that represents a list of words */


class WordList
{
private:
	int sumListItemsSize_;
	int sumSetItemsSize_;

	list< shared_ptr<Word> >* wordList_;
	set< shared_ptr<Word> > * wordSet_;
	vector<pair< shared_ptr<Word>, int> > wordOccsVec_;
	int size_;


public:
	WordList();
	WordList(list<shared_ptr<Word>>* wordList);
	~WordList();

	void insert(shared_ptr<Word> w);
	void setOccsVec(vector<pair< shared_ptr<Word>, int> > v);
	shared_ptr<Word> find(const shared_ptr<Word>w) const;
	list< std::pair<shared_ptr<Word>, shared_ptr<Word> > > crossAllWords() ;
	int sumWordsLengthWithRepeats() const;
	int sumWordsLengthWithoutRepeats() const;
	
	void clear();
	// Getters

	list<shared_ptr<Word> >* getWordList() const;
	set<shared_ptr<Word> >* getWordSet() const ;
	vector<pair< shared_ptr<Word>, int> > getWordVec() const;

	int wordPos(shared_ptr<Word> w) const;

	int getSize() const;
	// list<int> listOfStartPos() const;


	// Print
	friend ostream& operator<<(ostream& cout, const WordList &wS);

};

#endif /* WORDLIST_H_*/
