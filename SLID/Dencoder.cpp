#include "Dencoder.h"

/**
 * all ptr to NULL
 */
Dencoder::Dencoder()
{
  sequenceOri_ = NULL;
  sequence_ = NULL;
  grammar_ = NULL;
  alph_ = NULL;
  symbol_ = NULL;
  totalElectionSize_ = 0 ;
}

/**
 * Delete Sequences objects
 */
Dencoder::~Dencoder()
{

  //alphabet is destroyed in the sequence

  delete symbol_;
  symbol_ = NULL;

}

/**
 * read the string in the file and convert it to an Sequence object. Points sequenceOri
 * to it.
 * @param filename
 */
void Dencoder::readSequence(const char* filename)
{
  shared_ptr<Sequence> s_ori = make_shared<Sequence>();

  s_ori->readFromFile(filename);

  sequenceOri_ = s_ori;
  alph_ = sequenceOri_->getAlphabet();
  symbol_ = new Symbol(alph_->getSize());

  //Create Production for grammar:
  int S = -1;
  int * intSeq = sequenceOri_->getIntSequence();
  //Create a copy of the start sequence for the first production, just
  //to avoid problems
  int* startRHS = new int[sequenceOri_->getSize()];
  for(int i = 0; i< sequenceOri_->getSize(); ++i)
  {
    startRHS[i] = intSeq[i];
  }


  shared_ptr<Production> p1 = make_shared<Production>(S, startRHS, sequenceOri_->getSize());
  list<shared_ptr<Production> >* lp = new list<shared_ptr<Production> >;
  lp->push_back(p1);
  grammar_ = make_shared<Grammar>(lp);
}

/**
 * update the Sequence with the given one.
 * @param newSeq
 */
void Dencoder::updateSequence(shared_ptr<Sequence>newSeq)
{
  sequence_ = newSeq;
}

/**
 * Given a WordList, get the best Yield formed from one of those maximal repeats
 * @param mrs a wordList
 * @return best Yield founded based on score.
 */
shared_ptr<UYiV> Dencoder::createUYiVFromMaximalRepeats(WordList* mrs)
{

  list<shared_ptr<Word> > * wl = mrs->getWordList();
  shared_ptr<Word> current;
  shared_ptr<UYiV> best = NULL;

  for(list< shared_ptr<Word> >::iterator it = wl->begin(); it!=wl->end(); ++it)
  {
    current = *it;
    getUVFromMaximalRepeat(best, current);
  }
  return best;
}

/**
 * Given the current best Yield and a word, try to find a Yield with the suffix
 * and prefix of this word that's better than the current one.
 * @param best current best yield
 * @param mr   word
 */
void Dencoder::getUVFromMaximalRepeat(shared_ptr<UYiV> &best, shared_ptr<Word> mr)
{
  shared_ptr<Word> u;
  shared_ptr<Word> v;
  shared_ptr<Sequence> seq = getSeq();
  int size = mr->getSize();

  shared_ptr<UYiV> newUYV;
  WordList* y;
  list <std::pair<int,int> > * wordPosPairs;

  for(int i = 1; i<size; ++i)
  {
    u = seq->createSubWord(mr, 0, i);
    for(int j = i; j<size; ++j)
    {
      v = seq->createSubWord(mr, j, size);
      wordPosPairs = seq->wordPosPairList(u,v);

        clock_t t;
  t = clock();

      y = seq->obtainWordsInside(wordPosPairs, u->getSize());
  t = clock() - t;
  printf("obtainWordsInside: It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
      newUYV = make_shared<UYiV>(u, v, y, wordPosPairs);

      if(!(wordPosPairs == NULL || y->getSize() == 0))
      {
        if(score(best)<score(newUYV))
        {
          // cout << "Score best: " << score(best) << endl;
          best = newUYV;
          // cout << "Score New: " << score(newUYV) << endl;
        }

      }      

    }
    // cout << "Score primer palabra: " << score(best) << endl;
  }
}

/**
 * Given a wordset create UYiV yields crossing them and return the best one
 * @param ws set of words
 * @return best UYiV
 */
shared_ptr<UYiV> Dencoder::getBestUYiV(unordered_set< shared_ptr<Word> > * ws) const
{


  shared_ptr<Sequence> seq = getSeq();
  shared_ptr<Word> u;
  shared_ptr<Word> v;
  list <std::pair<int,int> > * wordPosPairs;
  WordList* y;

  shared_ptr<UYiV> newUYV;
  shared_ptr<UYiV> best = NULL;

  for(unordered_set< shared_ptr<Word> >::iterator it1 = ws->begin(); it1!= ws->end(); ++it1)
  {
    u = *it1;
    for(unordered_set< shared_ptr<Word> >::iterator it2 = ws->begin(); it2!= ws->end(); ++it2)
    {
      v = *it2;

      //wordPosPairs could be NULL
      wordPosPairs = seq->wordPosPairList(u,v);
      if(wordPosPairs == NULL || wordPosPairs->size()>=2)
      {
        y = seq->obtainWordsInside(wordPosPairs, u->getSize());
        newUYV = make_shared<UYiV>(u, v, y, wordPosPairs);

        if(!(wordPosPairs == NULL || y->getSize() == 0))
        {
          if(score(best)<=score(newUYV))
          {
            // cout << "Score best: " << score(best) << endl;
            best = newUYV;
            // cout << "Score New: " << score(newUYV) << endl;
          }
        }  
      }
      else
      {
        delete wordPosPairs;
      }
      // it = ls.erase(it);
    }
  }
  return best;
}


/**
 * Calculate score of a given UYiV. The score is based on the formulas written in the inform.
 * @param  uyv
 * @return score
 */
double Dencoder::score(shared_ptr<UYiV> uyv) const
{
  if (uyv == NULL) return -1;

  WordList* y = uyv->getYList();
  //if the yList is NULL return score 0
  
  assert(y != NULL);
  if (y == NULL) return 0;
  // if (y->getSize() == 0) return -1;

  int p, q, k, l, pipes, I, encoding, total;
  p = uyv->getWordsPosPairs()->size();
  //This is the complete encoding... And I just to count the encoding of the new uyv...
  encoding = 0;
  q = y->getWordVec().size();
  k = uyv->getU()->getSize();
  l = uyv->getV()->getSize();
  pipes = (q-1) ;
  I = 1;


  // the terms with the + are our gains, the - our penalties

  // total = - getProdElectionSize() + p*k + p*l + y->sumWordsLengthWithoutRepeats() - y->sumWordsLengthWithRepeats() - p - 1 - k - l - 1 - 1 - (q - 1);
  total =  p*k + p*l + y->sumWordsLengthWithRepeats() -
                          y->sumWordsLengthWithoutRepeats() - 
                          encoding - 
                          p - 1 - k - l - 1 - I - pipes ;
  assert(y->sumWordsLengthWithRepeats()>=y->sumWordsLengthWithoutRepeats());

  return total;
}


/**
 * Calculate score of a given Word. The score is based on the formulas written in the inform.
 * @param  word
 * @return score
 */
double Dencoder::score(shared_ptr<Word> w) const
{
  if (w == NULL) return -1;
  int p, k, total;
  p = w->getOccPos()->size();
  k = w->getSize();

  // p = number of occs
  // k = word size
  // 1 = non terminal added
  total =  p*k - p - k - 1;

  return total;
}


/**
 * Get the best u-v contexts based on a score function from the dencoder
 * @param  ls list containing uyv
 * @return    best shared_ptr<UYiV>
 */
shared_ptr<UYiV> Dencoder::bestUV(const list< shared_ptr<UYiV> > * ls) const
{
  //Creates a pointer to a u_v class.
  //This pointer is going to be the best_pair
  shared_ptr<UYiV> best = NULL;
  shared_ptr<UYiV> current = NULL;
  double bestScore = 0;
  double currentScore = 0;

  for(list < shared_ptr<UYiV> >::const_iterator it = ls->begin(); it != ls->end(); ++it)
  {

    current = *it;

    if(current->getWordsPosPairs() != NULL)
    {
      currentScore = score(current);
      if (currentScore >= bestScore){ // it the current_score is better than the last one,
                                   //replace it
        bestScore = currentScore;
        best = current; // new best pair points now to new best UYiV
      }
      
    }


  }
  return best;
}

/**
 * Get the best Word based on a score function 
 * @param us unordered set of words
 * @return best word
 */
shared_ptr<Word> Dencoder::bestWord(unordered_set< shared_ptr<Word> > * us) const
{
  shared_ptr<Word> best;
  shared_ptr<Word> current;
  double bestScore = 0;
  double currentScore = 0;

  for(unordered_set <shared_ptr<Word> >::iterator it = us->begin(); it!=us->end(); ++it)
  {
    current = *it;
    currentScore = score(current);
    if(currentScore >= bestScore){
      bestScore = currentScore;
      best = current;
    }

  }
  return best;
}


/**
 * replace given yield in the sequence
 * @param uyv yield to be replaced
 */
void Dencoder::replace(shared_ptr<UYiV> uyv)
{

  if(uyv->getYList()->sumWordsLengthWithoutRepeats() == 0)
  {
    replaceYieldSimple(uyv);
  }
  else
  {
    replaceYield(uyv);
  }

}


/**
 * replace the given shield with a NonTerminal in the Sequence
 * @param uyv the yield to be replaced
 * @param nonTerminal
 */
void Dencoder::replaceNonTerminal(shared_ptr<UYiV> uyv, int nonTerminal)
{

  int I = nonTerminal-1;

  vector<int> delimiterPos;
  shared_ptr<Word> u = uyv->getU();
  shared_ptr<Word> v = uyv->getV();


  int uSize = u->getSize();
  int vSize = v->getSize();

  int uPos = -1;
  int vPos = -1;
  int yieldLength = -1;
  int diff = 0;

  //I'm gonna use this just to know which y i'm adding and its position. 
  WordList* y = uyv->getYList();

  set< shared_ptr<Word> > * wordSet = y->getWordSet();

  list< shared_ptr<Word> > * wordList = y->getWordList();
  list< shared_ptr<Word> >::iterator yIt = wordList->begin();

  int p, k, l, total;
  p = uyv->getWordsPosPairs()->size();
  k = uyv->getU()->getSize();
  l = uyv->getV()->getSize();

  // if(opt == 0)
  // total = getSeq()->getSize() - (p*k + p*l + y->sumWordsLengthWithRepeats() - p);
  // else
  
  total = getSeq()->getSize() - (p*k + p*l + y->sumWordsLengthWithRepeats() - p) ;


  int * newSeq = new int[total];

  shared_ptr<Sequence> oldSequence = getSeq();
  int realSize = oldSequence->getSize();

  int* oldSeq = oldSequence->getIntSequence();


  list<std::pair<int, int> > * wordsPosPairs = uyv->getWordsPosPairs();
  list<std::pair<int,int> >::iterator posIt = wordsPosPairs->begin();

  int yWordPos;
  //Rewrite
    
  for(int i = 0; i < realSize; i++)
  {
    assert(i<oldSequence->getSize());
    assert(i-diff<total);

    if (posIt!=wordsPosPairs->end() && i == (*posIt).first)
    {
      uPos = (*posIt).first;
      vPos = (*posIt).second;

      if(uPos+uSize == vPos)
      {
        prodElectionOrder_[I].push(-1); //Push negative number to know it's an epsilon
        // Changes for the new encode:
        yWordPos = 0;
      }
      else
      {
        //add which production option I chose here
        yWordPos = y->wordPos(*yIt)+1;
        prodElectionOrder_[I].push(yWordPos);
        // Changes for the new encode:
        ++yIt; 
      }

      yieldLength = vPos + vSize - uPos;
      
      newSeq[i - diff] = nonTerminal+yWordPos;
      diff += yieldLength-1;
      i += yieldLength-1;

      //increase pos iterator
      posIt++;
    }
    else
    {
      if(oldSeq[i] == 1)
        {
          delimiterPos.push_back(i-diff);
        }
      newSeq[i-diff] = oldSeq[i];
    }
  }

  symbol_->increaseNonTerminal(wordSet->size());
  //Create Productions:
  list<shared_ptr<Production> >* lp;
  lp = rebuildGrammar(newSeq, delimiterPos, total);
  delete[] newSeq;
  grammar_ = make_shared<Grammar>(lp);
}

/**
 * replace given uyv yield by a non terminal. UYiV must have empty insides. 
 It's similar to word replace.
 * @param uyv         yield to replace
 * @param nonTerminal 
 */
void Dencoder::replaceNonTerminalSimple(shared_ptr<UYiV> uyv, int nonTerminal)
{


  vector<int> delimiterPos;
  shared_ptr<Word> u = uyv->getU();
  shared_ptr<Word> v = uyv->getV();


  int vSize = v->getSize();
  int uSize = u->getSize();
  int yieldLength = uSize+vSize;
  int uPos = -1;
  int vPos = -1;
  int diff = 0;


  list<std::pair<int, int> > * wordsPosPairs = uyv->getWordsPosPairs();


  assert(wordsPosPairs != NULL);

  int p, k, l, total;

  p = wordsPosPairs->size();
  k = uyv->getU()->getSize();
  l = uyv->getV()->getSize();

  total = getSeq()->getSize() - (p*k + p*l - p);

  int * newSeq = new int[total];

  shared_ptr<Sequence> oldSequence = getSeq();
  int realSize = oldSequence->getSize();

  int* oldSeq = oldSequence->getIntSequence();


  list<std::pair<int,int> >::iterator posIt = wordsPosPairs->begin();


  //Rewrite
    
  for(int i = 0; i < realSize; i++)
  {
    assert(i<oldSequence->getSize());
    assert(i-diff<total);

    if (posIt!=wordsPosPairs->end() && i == (*posIt).first)
    {
      uPos = (*posIt).first;
      vPos = (*posIt).second;

      newSeq[i - diff] = nonTerminal;
      diff += yieldLength-1;
      i += yieldLength-1;
      //increase pos iterator
      posIt++;
    }
    else
    {
      if(oldSeq[i] == 1)
        {
          delimiterPos.push_back(i-diff);
        }
      newSeq[i-diff] = oldSeq[i];
    }
  }

  assert(uPos!=-1);
  assert(vPos!=-1);
  //Create Productions:
  list<shared_ptr<Production> >* lp;
  lp = rebuildGrammar(newSeq, delimiterPos, total);
  delete[] newSeq;
  grammar_ = make_shared<Grammar>(lp);
}


/**
 * replace a word by a non terminal in the sequence
 * @param w           word to be replaced
 * @param nonTerminal 
 */
void Dencoder::replaceNonTerminalWord(shared_ptr<Word> w, int nonTerminal)
{


  vector<int> delimiterPos;
  list<int> * occs;

  occs = w->getOccPos();

  int wSize = w->getSize();
  int wPos = -1;
  assert(wPos!=0);
  int diff = 0;

  int p, k, total;

  p = occs->size();
  k = wSize;

  total = getSeq()->getSize() - p*k + p;

  int * newSeq = new int[total];

  shared_ptr<Sequence> oldSequence = getSeq();
  int realSize = oldSequence->getSize();

  int* oldSeq = oldSequence->getIntSequence();


  list<int>::iterator posIt = occs->begin();


  //Rewrite
    
  for(int i = 0; i < realSize; i++)
  {
    assert(i<oldSequence->getSize());
    assert(i-diff<total);

    if (posIt!=occs->end() && i == (*posIt))
    {
      wPos = (*posIt);

      newSeq[i - diff] = nonTerminal;
      diff += wSize-1;
      i += wSize-1;
      //increase pos iterator
      posIt++;
    }
    else
    {
      if(oldSeq[i] == 1)
        {
          delimiterPos.push_back(i-diff);
        }
      newSeq[i-diff] = oldSeq[i];
    }
  }

  //Create Productions:
  list<shared_ptr<Production> >* lp;
  lp = rebuildGrammar(newSeq, delimiterPos, total);
  delete[] newSeq;
  grammar_ = make_shared<Grammar>(lp);
}


/**
 * replace the given yield and generate the productions needed
 * @param uyv
 */
void Dencoder::replaceYield(shared_ptr<UYiV> uyv)
{
  shared_ptr<Word> u = uyv->getU();
  int * uInt = u->getSubSequence();
  shared_ptr<Word> v = uyv->getV();
  int * vInt = v->getSubSequence();
  int uSize = u->getSize();
  int vSize = v->getSize();
  int ySize = 0;
  int *yInt;
  int currentPos = 0;

  WordList* y = uyv->getYList();
  assert(y!= NULL);
  // set<shared_ptr<Word> > * yWords = y->getWordSet();
  vector< pair<shared_ptr<Word>, int> > vecWord = y->getWordVec();


  int lenghtInside = y->sumWordsLengthWithoutRepeats();

  int I = symbol_->getNonTerminal();
  int N = symbol_->getNonTerminal();

  std::queue<int> initialQ;
  prodElectionOrder_[I] = initialQ ;
    
  replaceNonTerminal(uyv, N);
  // U size + I NonTerminal + v Size
  int * nRHS = new int[uSize+1+vSize];
  // Rule for the insides + y->size() are the pipes
  int * iRHS = new int[lenghtInside+vecWord.size()];


  //Add u symbols
  for(int i = 0; i < uSize; ++i)
  {
    nRHS[i] = uInt[i];
  }
  //Add I nonTerminal
  nRHS[uSize] = I;
  //Add v symbols
  for(int i = 0; i < vSize; ++i)
  {
    nRHS[uSize+1+i] = vInt[i];
  }

  //Add y simbols
  for(vector< pair<shared_ptr<Word>, int> >::iterator it = vecWord.begin(); it != vecWord.end(); ++it)
  {
    shared_ptr<Word> y = (*it).first;
    yInt = y->getSubSequence();
    ySize = y->getSize();
    //cannot be 0
    // assert(ySize!=0);
    for (int i = 0; i < ySize; ++i)
    {
      iRHS[currentPos+i] = yInt[i];

    }
    iRHS[currentPos + ySize] = 2;
    currentPos += ySize+1;

    // cout << endl << *y << endl << (*it).second << endl;
  }


  // int sProdSize = getSeq()->getSize() - y->sumWordsLengthWithRepeats() - n*(uSize+vSize) + n;

  //Create Productions:
  shared_ptr<Production> p1 = make_shared<Production>(I, iRHS, lenghtInside+y->getWordSet()->size()-1);
  shared_ptr<Production> p2 = make_shared<Production>(N, nRHS, uSize+1+vSize);
  grammar_->addProd(p1);
  grammar_->addProd(p2);

}

/**
 * replace the given yield with Inside NULL (simple repeat) and generate the productions needed
 * @param uyv
 */
void Dencoder::replaceYieldSimple(shared_ptr<UYiV> uyv)
{
  shared_ptr<Word> u = uyv->getU();
  int * uInt = u->getSubSequence();
  shared_ptr<Word> v = uyv->getV();
  int * vInt = v->getSubSequence();
  int uSize = u->getSize();
  int vSize = v->getSize();


  int N = symbol_->getNonTerminal(); 
  
  replaceNonTerminalSimple(uyv, N);
  // U size + I NonTerminal + v Size
  int * nRHS = new int[uSize + vSize];

  //Add u symbols
  for(int i = 0; i < uSize; ++i)
  {
    nRHS[i] = uInt[i];
  }
  //Add v symbols
  for(int i = 0; i < vSize; ++i)
  {
    nRHS[uSize + i] = vInt[i];
  }

  //Create Productions:
  shared_ptr<Production> p1 = make_shared<Production>(N, nRHS, uSize+vSize);
  grammar_->addProd(p1);
}

/**
 * replace the given word by the next non terminal
 * @param w word to be replaced
 */
void Dencoder::replaceWord(shared_ptr<Word> w)
{
  int * wInt = w->getSubSequence();
  int wSize = w->getSize();


  int N = symbol_->getNonTerminal();
 

  replaceNonTerminalWord(w, N);
  // U size + I NonTerminal + v Size
  int * nRHS = new int[wSize];

  //Add u symbols
  for(int i = 0; i < wSize; ++i)
  {
    nRHS[i] = wInt[i];
  }

  //Create Productions:
  shared_ptr<Production> p1 = make_shared<Production>(N, nRHS, wSize);
  grammar_->addProd(p1);

}




/**
 * Rebuild the grammar based on a given int sequence. It iterates over the sec
 * looking for the delimiters $, when they are founded it means a new production
 * must be created.
 * @param sec the int sequence
 * @param delimiterPos a vector telling where are the delimiters
 * @param total the total size
 * @return the grammar list of productions
 */
list<shared_ptr<Production> > * Dencoder::rebuildGrammar(int * sec, vector<int> delimiterPos, int total)
{
  int * currentRHS;
  shared_ptr<Production>  currentProd;
  int start = 0, end = 0, size = 0, symbol = 0;

  list<shared_ptr<Production> > * result = new list<shared_ptr<Production> >;
  if(delimiterPos.empty())
  {
    size = total;
    currentRHS = new int[size];

    for(int j=0; j<size;j++)
    {
      currentRHS[j] = sec[j];
    }
    result->push_back(make_shared<Production>(-1, currentRHS, total));
    return result;
  }

  //First Production
  symbol = -1;
  start = 0;
  end = delimiterPos[0];
  size = end-start;
  currentRHS = new int[size];

  for(int j=start; j<end;j++)
  {
    currentRHS[j] = sec[j];
  }

  currentProd = make_shared<Production>(symbol, currentRHS, size);
  result->push_back(currentProd);
  symbol = symbol_->getFirstNonTerminal();

  //All others productions
  for (unsigned int i=1; i<delimiterPos.size(); i++)
  {
    start = delimiterPos[i-1]+1;
    end = delimiterPos[i];
    size = end-start;
    currentRHS = new int [size];

    for(int j=start; j<end;j++)
    {
      currentRHS[j-start] = sec[j];
    }

    currentProd = make_shared<Production>(symbol, currentRHS, size);
    result->push_back(currentProd);
    symbol++;
    if(symbol == 1)
    {
      symbol+=2; //+2 because 37 == % and I'm using it for epsilon right now.
    }
    if(symbol == 2)
    {
      symbol++;
    }

  }

  return result;

}

/**
 * decode the grammar into the original sequence
 * @return Sequence
 */
void Dencoder::decode() 
{

  int current = symbol_->getCurrentSymbol()-1;

  while(current >= symbol_->getFirstNonTerminal())
  {
    grammar_->unfoldNonTerminal(current, getProdElectionOrder(current));
    current--;
    // cout << "Unfolding..." << endl;
    // cout << *grammar_ << endl;
  }

}


// void Dencoder::dfsEnc(int nonTerminal, int start, int end, vector<int> &enc)
// {
//   shared_ptr<Production> p = grammar_->getProdByLHS(nonTerminal);
//   shared_ptr<Production> nextP;

//   int nextStart = 0;
//   int nextEnd = 0;
//   int * rhs = p->getRHS();
//   int currentSymbol;
//   int election;


//   for(int i = start; i< end;i++)
//   {
//     currentSymbol = rhs[i];
//     if(symbol_->isNonTerminal(currentSymbol))
//     {
//       // cout << " " << currentSymbol;
//       nextP = grammar_->getProdByLHS(currentSymbol);
//       queue<int> &q = getProdElectionOrder(currentSymbol);
//       if(!q.empty())
//       {
//         election = q.front();
//         if(currentSymbol == 9)
//         {

//           cout << "queue size: " << q.size() <<  " ";
//           cout << "Election: " << election << endl;
//         }
//         enc.push_back(election);
//         // cout << "election: " << election << endl;
//         nextStart = nextP->getElectionStartPos(election);
//         nextEnd = nextP->getElectionEndPos(election);
//         q.pop();
//         totalElectionSize_--;
//         //TODO: por alguna razón me deja la cola vacía antes de tiempo...

//       }
//       else
//       {
//         nextStart = 0;
//         nextEnd = nextP->getSize()-1;
//       }
//       dfsEnc(currentSymbol, nextStart, nextEnd, enc);
//     }
//   }
//   return;
// }

// Getters

/**
 * get ptr to the original Sequence. If NULL exit.
 * @return ptr to original sequence
 */
shared_ptr<Sequence> Dencoder::getSeqOri() const
{
  if(sequenceOri_==NULL){
    cerr << "Seq is NULL!! Exiting.." << endl;
    exit(1);
  }
  return sequenceOri_;
}

/**
 * Get ptr to current Sequence if NULL exit.
 * @return ptr to current sequence
 */
shared_ptr<Sequence> Dencoder::getSeq() const
{
  if(sequence_==NULL){
    cerr << "Seq is NULL!! Exiting.." << endl;
    exit(1);
  }
  return sequence_;
}

/**
 * get the symbol
 * @return symbol_
 */
Symbol * Dencoder::getSymbol() const
{
  return symbol_;
}

/**
 * get the Grammar
 * @return grammar_
 */
shared_ptr<Grammar> Dencoder::getGrammar() const
{
  return grammar_ ;
}

/**
 * returns a reference to the nonTerminal elections queue
 */
queue<int> & Dencoder::getProdElectionOrder(int nonTerminal) 
{
  return prodElectionOrder_[nonTerminal];
}

/**
 * Get the total size of the elections queues
 * @return total size
 */
int Dencoder::getProdElectionSize() const 
{
  return totalElectionSize_;
}

/**
 * Set a new grammar
 * @param g new grammar
 */
void Dencoder::setGrammar(shared_ptr<Grammar> g)
{
  grammar_ = g;
}
