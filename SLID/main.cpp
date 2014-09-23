#include "IO.h"
#include "Utils.h"

#include <list>

// Boost libs
#include <boost/foreach.hpp>

// SArray headers
#include "SArray/SArray.h"
#include "SArray/LLArray.h"

#include "Dencoder.h"
#include "Sequence.h"
#include "SubSequence.h"
#include "Alphabet.h"
#include "Word.h"
#include "WordList.h"
#include "NonTerminal.h"
#include "Production.h"
#include "Grammar.h"
#include <time.h>

using namespace std;


void help(){
  cerr << endl;
  cerr << "Usage: <file> [iter] [Output]" << endl;
//  cerr << "\t-a\t given path to file with forbidden constituents" << endl;
  cerr << "<file>: sequence to compress, with spaces within tokens, for example:" << endl;
  cerr << "\ta g g t g a g g a g t g a g t g a c a c a c a c a c a g g g t g a g a g a c" << endl;
  cerr << "[iter]: optional parameter. It says how many iterations we want." << endl;
  cerr << "[output]: optional parameter to save the output grammar" << endl;
  exit(-1);
}


int wordIsContext = 0;
int wordElection = 0;
int uyvElection = 0;
int size = 0;
int lastSize = 0;

int main(int argc, char** argv) {
  if(argc == 1)
  {
    help();
  }
  int MAX_ITER;
  if(argc == 2)
  {
    MAX_ITER = -1;
  }
  else
  {
    MAX_ITER = atoi(argv[2]);
  }
  cout << "Max Iter: " << MAX_ITER << endl;
  // int k = atoi(argv[2]);
  // int j = atoi(argv[3]);

  // cout << "k j: " << k << j << endl;

  // ==== NEW DENCODER ====
  Dencoder *d = new Dencoder;


  // ==== READ FILE ====
  d->readSequence(argv[1]);

  // cout << "Sequence read" << endl;

  shared_ptr<Sequence> secuOri = d->getSeqOri();
  int * intSecuOri = secuOri->getIntSequence();


  // ==== CREATE SEQUENCE TO REPLACE ====
  shared_ptr<Sequence> secu = make_shared<Sequence>();



  secu->createFromInt(intSecuOri, secuOri->getSize());

  d->updateSequence(secu);


  // ==== MAXIMAL REPEATS WORDLIST ====
  unordered_set<shared_ptr<Word> > * mrs;
  mrs = secu->maximalRepeats();
  // cout << "Mrs size: " << endl;
  // cout << mrs->size();

  // cout << "maximalRepeats size: " << mrs->getSize() << endl;
  

  //here instead of crossing All words I need a createUIiVFromMr(mrs)  



  // cout << endl <<  "==== INITIAL GRAM ==== " << endl;
  shared_ptr<Grammar> g1 = d->getGrammar();
  size = g1->getSize();
  cout << "Initial Size: " << size << endl << endl;
  // lastSize = size;
  cout << "Initial Grammar: " << endl;
  *debug << *g1;

  std::ofstream outputInitialGrammar("token");
  outputInitialGrammar << *g1;

  // ==== REPLACE THE BEST YIELD FOUNDED ====
  
  //==== BEST UYV ====

  clock_t t;
  t = clock();
  shared_ptr<Word> bestWord = d->bestWord(mrs);

  t = clock() - t;
  // printf("bestWord: It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

  shared_ptr<UYiV> best = NULL;

  // list< std::pair<shared_ptr<Word> , shared_ptr<Word> > > cross = mrs->crossAllWords();


  t = clock();

  best = d->getBestUYiV(mrs);
  t = clock() - t;
  // printf("bestUYiV: It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);


  delete mrs;
  // cross.clear();
  // cout << "Scores: " << endl;
  // cout << "WordScore: " << d->score(bestWord) << endl;
  // cout << "YieldScore: " << d->score(best) << endl;

  if(d->score(bestWord)>d->score(best))
  {
    // cout << "Best Word!" << endl;
    d->replaceWord(bestWord);
    wordElection++;
  }
  else{
    if(best->getU() == bestWord || best->getV() == bestWord) wordIsContext++;
    // cout << "Best Yield!" << endl;
    d->replace(best);
    uyvElection++;
  }

  g1 = d->getGrammar();

  size = g1->getSize();
  // cout << endl << "==== GRAM 1 ITER ====" << endl;
  // *debug << *g1;
  // cout << "Size (Including Encoding): " << size << endl;
  // cout << "Improvement: " << 1 - (double) size / (double) lastSize << endl;

  lastSize = size;

  // exit(1);

  bool iter = true;
  int i = 2;

  while(iter)
  {
    // ==== CONVERT GRAMMAR TO INT SEQUENCE ====
    int * grammarSeq;
    grammarSeq = g1->convertToInt();


    // ==== CREATE SEQUENCE FROM GRAMMAR INT SEQUENCE ====
    shared_ptr<Sequence> seqFromInt = make_shared<Sequence>();


    seqFromInt->createFromInt(grammarSeq, g1->getSize());

    delete[] grammarSeq;
    // *debug << *seqFromInt << endl;

    d->updateSequence(seqFromInt);

    // delete mrs;
    mrs = seqFromInt->maximalRepeats();

    // cout << "cant max repeat: " << mrs->getSize() << endl;
    // cout << *mrs;
    // cout << "maximalRepeats size: " << mrs->getSize() << endl;
    // cout << *mrs << endl;



    //==== BEST UYV ====

//==== BEST UYV ====
//
    // cout << *mrs;
    bestWord = d->bestWord(mrs);
    // cross = mrs->crossAllWords();


    best = d->getBestUYiV(mrs);

    delete mrs;

    // cross.clear();


    if(bestWord == NULL && best == NULL)
    {
      break;
    }

    if(bestWord == NULL)
    {
      // cout << "Best Yield!" << endl;
      d->replace(best);
      uyvElection++;
    }
    if(best == NULL)
    {
      // cout << "Best Word!" << endl;
      d->replaceWord(bestWord);
      wordElection++;    
    }

    if(bestWord!=NULL && best!=NULL)
    {
      if(best->getU() == bestWord || best->getV() == bestWord) wordIsContext++;
      // cout << "Scores: " << endl;
      // cout << "WordScore: " << d->score(bestWord) << endl;
      // cout << "YieldScore: " << d->score(best) << endl;
      if(d->score(bestWord)>d->score(best))
      {
        // cout << "Best Word!" << endl;
        d->replaceWord(bestWord);
        wordElection++;
      }
      else{
        // cout << "Best Yield!" << endl;
        d->replace(best);
        uyvElection++;
      }      
    }


    g1 = d->getGrammar();

    size = g1->getSize();
    // cout << endl << "==== GRAM "<< i <<" ITER ==== " << endl;
    // *debug << *g1;
    // cout << "Size (Including Encoding): " << size << endl;
    // cout << "Improvement: " << 1 - (double) size / (double) lastSize << endl;

    // lastSize = size;

    // cout << endl << "==== GRAM "<< i <<" ITER ==== " << endl;
    // cout << "Size (Including Encoding): " << g1->getSize() + d->getProdElectionSize() << endl;
    // cout << *g1;







    //delete
    i++;
    if(i == MAX_ITER)
    {
      iter = false;
    }

  }


    //   queue<int> q;
    // int j = 0;
    // for(unsigned int i = 0; i<1000; i++)
    // {

    //   q = d->getProdElectionOrder(i);
    //   while(!q.empty())
    //   {
    //     cout << (q.front())<< ",";
    //     q.pop();
    //     j++;
    //   }
    //   }



    // }
    // cout << "tamaño j: " << j << endl;


  cout << endl << "==== FINAL GRAM "<< i-1 <<" ITER ==== " << endl;
  cout << *g1;
  cout << endl;
  std::ofstream outputGrammar(argv[3]);
  outputGrammar << *g1;

  cout << "Encoding Size: " << d->getProdElectionSize() << endl;
  cout << "Final Size: " << g1->getSize()  << endl;
  cout << "Grammar + Encoding: " << g1->getSize() + d->getProdElectionSize() << endl;
  cout << "Words Chosen: " << wordElection << "(" << 100 * (double) wordElection/(double) (wordElection+uyvElection) << " per cent)" << endl;
  cout << "Contexts Chosen: " << uyvElection << "(" << 100 * (double) uyvElection/(double) (wordElection+uyvElection) << " per cent)" << endl;
  // cout << "Word part of contexts: " << wordIsContext << endl;

  // cout << "ULTIMAS MRS: " << mrs->getSize() << endl;
  // cout << *mrs << endl;


  // shared_ptr<Production> firstP = g1->getProds()->front();
  //   vector<int> v;
  //   d->dfsEnc(-1, 0, firstP->getSize()-1, v);

  //   cout << "Que hay en el vector: " << v.size() << endl;
  //   for(unsigned int i= 0; i<v.size(); i++){
  //     cout << v[i] << " ";
  //   }

  cout << endl << "==== UNFOLDED GRAMMAR ====" << endl;
  d->decode();
  cout << endl;
  cout << *g1;

  // delete pairMR;
  // pairMR = NULL;
  // 

  // delete mrs;
  mrs = NULL;

  delete d;
  d = NULL;
  return 0;
}
