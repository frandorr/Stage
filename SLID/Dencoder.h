#ifndef DENCODER_H_
#define DENCODER_H_

#include <assert.h>
#include "Utils.h"
#include "Sequence.h"
#include "UYiV.h"
#include "Word.h"
#include "NonTerminal.h"
#include "Production.h"
#include "Grammar.h"
#include "Symbol.h"

using namespace std;

class Dencoder{
private:
	// pointer to the original sequence
	shared_ptr<Sequence> sequenceOri_;
  // pointer to the sequence that would be updated
	shared_ptr<Sequence> sequence_;
	shared_ptr<Grammar> grammar_;
	Symbol * symbol_;
	Alphabet * alph_;
  map< int, queue<int> > prodElectionOrder_;
  int totalElectionSize_;

public:
	// constructor
	Dencoder();
	// destructor
	~Dencoder();
	void readSequence(const char* filename);
  void updateSequence(shared_ptr<Sequence> newSeq);

  shared_ptr<UYiV> createUYiVFromMaximalRepeats(WordList* mrs);
  shared_ptr<UYiV> getBestUYiV(unordered_set<shared_ptr<Word> > * ws) const;

  double score(shared_ptr<UYiV> uyv) const;
  double score(shared_ptr<Word> w) const;

  shared_ptr<UYiV> bestUV(const list < shared_ptr<UYiV> > * ls) const;
  shared_ptr<Word> bestWord(unordered_set< shared_ptr<Word> > * us) const;

  void recursionReplace(shared_ptr< UYiV > uyv);
  void updateWord(shared_ptr<Sequence> seq, shared_ptr<Word> &w);

  void getUVFromMaximalRepeat(shared_ptr<UYiV> &best, shared_ptr<Word> mr);

  int encodingChanges(shared_ptr<UYiV> uyv) const;

  void replace(shared_ptr<UYiV> uyv);

  void replaceNonTerminal(shared_ptr<UYiV> uyv, int nonTerminal);
  void replaceNonTerminalSimple(shared_ptr<UYiV> uyv, int nonTerminal);
  void replaceNonTerminalWord(shared_ptr<Word> w, int nonTerminal);
  
  list<shared_ptr<Production> > * rebuildGrammar(int * sec, vector<int> delimiterPos, int total);

  void replaceWord(shared_ptr<Word> w);
  void replaceYield(shared_ptr<UYiV> uyv);
  void replaceYieldSimple(shared_ptr<UYiV> uyv);

  void decode(); 

  void dfsEnc(int nonTerminal, int start, int end, vector<int> &enc);

  // Getters
  shared_ptr<Sequence> getSeqOri() const;
  shared_ptr<Sequence> getSeq() const;
  Symbol * getSymbol() const;
  shared_ptr<Grammar> getGrammar() const;

  queue<int> &  getProdElectionOrder(int nonTerminal);
  int getProdElectionSize() const ;


  //Setters
  void setGrammar(shared_ptr<Grammar> g);


};

#endif /* DENCODER_H_*/
