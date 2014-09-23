#include "SubSequence.h"
#include "Sequence.h"
#include "SArray/SArray.h"


/**
 * All ptrs to NULL and size to 0
 */
Sequence::Sequence()
{
	sArray_ = NULL;
	sequence_ = NULL;
	intSequence_ = NULL;
  alph_ = new Alphabet;
	size_ = 0;
}

/**
 * Delete sArray_, Sequences_ and alph_
 */
Sequence::~Sequence()
{
	delete sArray_;
  sArray_ = NULL;
	delete[] sequence_;
  sequence_ = NULL;
  delete[] intSequence_;
  intSequence_ = NULL;
  delete alph_;
  alph_ = NULL;
}

// Methods:




// Public functions


/**
 * Obtain an int sequence from the Sequence object. Uses
 * this->alph_ to translate the chars to int
 * @return intSeq
 */
int* Sequence::toInt() const
{
	int size = getSize();
	// char* seq = getSequence();
	int* intSeq = new int[size];

  for(int i = 0; i<size; i++)
  {

    intSeq[i] = i;
  }
	return intSeq;
}

/**
 * read a sequence from a given filename, takes token separate by spaces.
 * @param filename 
 */
void Sequence::readFromFile(const char* filename)
{
  stringstream ss;
  vector<string> in;
  string line;
  string current;

  ifstream file(filename);
  while(getline(file, line))
  {
    stringstream ss(line);
    while(ss >> current)
    {
      in.push_back(current);
    }
  }

  size_ = in.size();

  intSequence_ = new int[size_];
  int newSymbol = 0;
  string s;
  int i = 0;
  for(vector<string>::iterator it = in.begin(); it!=in.end(); ++it)
  {
    s = *it;
    newSymbol = alph_->getSize()+1;
    alph_->insert(s, newSymbol);
    intSequence_[i] = alph_->getValue(s);
    i++;
  }
  sArray_ = new SuffixArray(intSequence_, size_, 0, 0);

}

// void Sequence::readFromFile(const char* filename)
// {

//   stringstream ss;
//   string s, current;

//   const char *eol = "1";
//   const char *pipe = "|";
//   const char *a = "a";
//   const char *c = "c";
//   const char *g = "g";
//   const char *t = "t";

//   const char *pipeint = "2";
//   const char *aint = "3";
//   const char *cint = "4";
//   const char *gint = "5";
//   const char *tint = "6";

//   string streol(eol);
//   string strpipe(pipe);
//   string stra(a);
//   string strc(c);
//   string strg(g);
//   string strt(t);

//   string str2(pipeint);
//   string str3(aint);
//   string str4(cint);
//   string str5(gint);
//   string str6(tint);
 

//   ifstream file(filename);

//   vector<string> in;
//   string line;
//   while(getline(file, line))
//   {
//         stringstream ss(line);
//         while (ss >> current)
//         {
//           if(current == stra)
//           {
//             in.push_back(str3);
//           }
//           else if(current == strc)
//           {
//             in.push_back(str4);
//           }
//           else if(current == strg)
//           {
//             in.push_back(str5);
//           }
//           else if(current == strt)
//           {
//             in.push_back(str6);
//           }
//           else if(current == strpipe)
//           {
//             in.push_back(str2);
//           }
//           else 
//           {
//             in.push_back(current);
//           }
//         } 
//         in.push_back(streol);
//   }

//   int seqSize = in.size();

//   size_ = seqSize;
//   sequence_ = new char [seqSize];
//   intSequence_ = new int [seqSize];


//   for(unsigned int i = 0; i<in.size(); i++)
//   {
//     intSequence_[i] = stoi(in[i]);
//   }

//   // intSequence_ = this->toInt();
 


//   // ifstream read(filename);
//   // string current;
//   // for(int i=1;i<=800;i++)
//   // {

//   //   read>>current;
//   //   cout << current << " ";
//   //   in.push_back(current);
//   // }

// }

/**
 * Read a file containing a string and complete the attributes of the Sequence object
 * @param filename with string
 */
// void Sequence::readFromFile(const char* filename)
// {
// 	int seqSize = 0;


//   ifstream ifs;

//   ifs.open(filename, ifstream::in);

//   if(ifs.fail())
//   {
//     cerr << "problems opening the file" << filename << endl;
//     exit(-1);
//   }

//   // Get seq size
//   ifs.seekg(0, ios::end);
//   seqSize = ifs.tellg();
//   ifs.seekg(0, ios::beg);
//   size_ = seqSize;

//   sequence_ = new char[ size_ ];

//   char c = ifs.get();


//   int i = 0;
//   while(ifs.good()) {

//     if (ifs.eof()) break;

//     alph_->insert(c, alph_->getSize()+1);
//     sequence_[i] = c;
//     i++;
//     c = ifs.get();
//   }
//   intSequence_ = this->toInt();
//   sArray_ = new SuffixArray(intSequence_, size_, 0, 0);

//   ifs.close();

//   int current;
//   for (int i=0; i<size_; i++)
//   {
//     current = intSequence_[i];
//     if ((current == 1) || (current == 2)) delimiterPos_.push_back(i);
//   }
// }


/**
 * create a Sequence object from an int array
 * @param intSeq array
 * @param size   size of the array
 */
void Sequence::createFromInt(int* intSeq, int size)
{
  int current;
  size_ = size;
  intSequence_ = new int[size];
  sequence_ = new char[size];

  for(int i = 0; i< size;i++)
  {
    sequence_[i] = toChar(intSeq[i]);
    intSequence_[i] = intSeq[i];
    current = intSequence_[i];
    if ((current == 1) || (current == 2))
    {
      delimiterPos_.push_back(i);
    }
  }
  sArray_ = new SuffixArray(intSequence_, size_, 0, 0);
}

/**
 * get shared ptr from this
 */
std::shared_ptr<Sequence> Sequence::getShared()
{
  return shared_from_this();
}


/**
 * if l1==0 return 1 otherwise Compares l1 and l2, if they are different, return 0, otherwise l1.
 * @param  l1 letter1
 * @param  l2 letter2
 * @return    int
 */
inline int LEletter(int l1, int l2){
  return (l1 == 0 or l1 != l2 ? 0 : l1);
}


/**
 * Get all maximal repeats from the Sequence
 * @return a ptr to WordList that are maximal repeats words
 */
unordered_set< shared_ptr<Word> > * Sequence::maximalRepeats()
{
  //this could be an attr from the sequence
  // vector<int> delimiterPos;
  // int current;
  // for (int i=0; i<size_; i++)
  // {
  //   current = intSequence_[i];
  //   if ((current == 1) || (current == 2)) delimiterPos.push_back(i);
  // }

  int * sArray = sArray_->getSArray();
  int * lcp = sArray_->getLCP();
  int seqIndex = 0;
  int length; 
  pair<int,int> startAndEnd;

  int minsize = 1;
  unordered_set< shared_ptr<Word> > * result = new unordered_set< shared_ptr<Word> >();
  int ilcp, lb, bwt, bwt1, bwt2;
  boost::tuple<int,int,int>* t;

  lb = 0;
  ilcp = lcp[0];
  bwt1 = pred_char(intSequence_, sArray[0]);
  stack<boost::tuple<int,int,int>* > st;
  st.push(new boost::tuple<int,int,int>(ilcp, lb, bwt1));

  for (int i = 0; i <= size_; i++){
    lb = i;
    ilcp = lcp[i+1];
    bwt2 = pred_char(intSequence_, sArray[i+1]);
    bwt = LEletter(bwt1, bwt2);
    bwt1 = bwt2;
    while(!st.empty() && st.top()->get<0>() > ilcp){
      t = st.top(); st.pop();
      int prevbwt = t->get<2>();
      if ((prevbwt == 0) && (t->get<0>() >= minsize)){

        // t->get<1> = start index in suffix array
        // i+1 = end index in suffix array
        // t->get<0> = length
        length = t->get<0>();
        //get the subsequence Index in sequence
        seqIndex = sArray[t->get<1>()];
        //get the subsequence last pos in sequence
        //len < 3 increase the performance mantaining similar results...
        // if(length < 3){

          createWordsFromLimits(seqIndex, length, result);
        // }

      }


        // exact_repeat* rep = new exact_repeat(t->second, i+1, t->first);
        // sub->non_overlapping_list(sarr, strandinfo);

      lb = t->get<1>();
      if (!st.empty()){
        st.top()->get<2>() = LEletter(prevbwt, st.top()->get<2>());
      }
      bwt = LEletter(prevbwt, bwt);
      delete t;
      t = NULL;
    }
    if (!st.empty() && st.top()->get<0>() == ilcp){
      st.top()->get<2>() = LEletter(st.top()->get<2>(), bwt);
    } else{
      st.push(new boost::tuple<int,int,int>(ilcp,lb,bwt));
    }
  }
  /* empty stack to clean memory */
  while(!st.empty()){
    delete st.top();
    st.top() = NULL;
    st.pop();
  }
  return result;
}

/**
 * Create words based on delimiters in the sequence. Given and index and a length, check if
 * it has a delimiter in the middle and creates words separated by those delimiters.
 * @param seqIndex index in the sequence
 * @param length   length
 * @param result   set of words
 */
void Sequence::createWordsFromLimits(int seqIndex, int length, unordered_set< shared_ptr<Word> > *result)
{
  list<int> separator;
  getSeparatorPos(separator, seqIndex, length);
  pair<int,int> startAndEnd;
  int lastSep = seqIndex-1;
  int currentSep = seqIndex;


  for(list<int>::iterator it = separator.begin(); it!=separator.end(); ++it)
  {
    currentSep = *it;
    length = currentSep - lastSep - 1;

    if(length>0)
    {
      startAndEnd = sArray_->search(&(*this)[lastSep+1], length);
      SubSequence* subSeq = new SubSequence(getShared(), lastSep+1, currentSep);
      // if (!subSeq->isInvalid() && (t->get<0>() == k || t->get<0>() == l))
      list<int> * wOccs;
      // wOccs = getSubSeqOccPos(subSeq, t->get<1>(), i+1);
      wOccs = getSubSeqOccPos(subSeq, startAndEnd.first, startAndEnd.second);

      shared_ptr<Word> w = make_shared<Word>(getShared(), lastSep+1, currentSep, wOccs);
      result->insert(w);
      delete subSeq;
      subSeq = NULL;

    }

    lastSep = currentSep;

  }

}

/**
 * Get the positions of the separatos starting from the index and finishin in index+length, 
 * it could be pipes or $
 * @param separator list of separatos
 * @param seqIndex  index in the seq
 * @param length    length
 */
void Sequence::getSeparatorPos(list<int> &separator,int seqIndex,int length)
{
  int current = 0;
  for(int i = seqIndex; i<seqIndex+length; i++)
  {
    current = (*this)[i]; 
    if(current == 1 || current == 2)
    {
      separator.push_back(i);
    } 
  }
  separator.push_back(seqIndex+length);
}

/**
 * get all occs in order of a given subSeq
 * @param subSeq a subsequence from the Sequence.
 * @result list of occs positions.
 */
list<int>* Sequence::getSubSeqOccPos(const SubSequence* word, int sArrayStartIndex,
                                       int sArrayEndIndex ) const
{
  int * sArray = sArray_->getSArray();

  int length = word->getSize();

  vector<int>* wordVec = new vector<int>();
  for (int i = sArrayStartIndex; i != sArrayEndIndex; i++)
  {
    wordVec->push_back(sArray[i]);
  }

  //Sort vector with Sequence position of my Word
  sort(wordVec->begin(), wordVec->end());

  int endPosition = *wordVec->begin() + length - 1;

  //Save all occPos
  list<int> * occPos = new list<int>(wordVec->begin(), wordVec->end());
  // delete vector
  delete wordVec;
  wordVec = NULL;

  //Search for overlapped words
  list<int>::iterator iter = occPos->begin();
  // bool eliminated = false;
  iter++;

  // a word ocurrs at least one times
  while(iter != occPos->end())
  {
    if (*iter > endPosition)
    {
      // don't overlap
      endPosition = *iter + length -1;
      ++iter;
    }
    else
    {  // overlap: delete it
      iter = occPos->erase(iter);
      // eliminated = true;
    }
  }
  return occPos;

}


/**
 * given two Words, return one list with no overlapped pairs of these words pos
 * in the follow way:
 took the first element y from vPos. Look for the max x in uPos, with x+uSize<y.
 (x,y) is a pair in the res list.
 *@param u
 *@param v
 *@return list<pairPos> pairs representing a context, it can be NULL
 */
list< pair<int,int> >* Sequence::wordPosPairList(shared_ptr<Word> u, shared_ptr<Word> v) const{


  list< pair<int,int> >* res = new list< pair<int,int> >;

  list<int> * uPos = u->getOccPos();
  list<int> * vPos = v->getOccPos();

  int uSize = u->getSize();
  int vSize = v->getSize();

  typename list<int>::iterator uIt = uPos->begin();
  typename list<int>::iterator vIt = vPos->begin();
  typename list<int>::iterator next;
  /*I don't like this (-1) to start... but otherwise doens't work*/
  int lastPosV = -1;

  /*Iterator to the next u element*/
  next = boost::next(uPos->begin());

  while(vIt != vPos->end() && uIt != uPos->end())
  {
    if (*uIt+uSize <= *vIt)
    { /*if last element in uPos + uSize <= last element in vPos,
                  I should check before adding a new pair to the lists
                  if it's not overlapped with the last one. That's why I
                  use the next if statemen:*/
      if((*uIt > lastPosV) && (next == uPos->end() || *next + uSize > *vIt)
                           && (groupNumber(*uIt) == groupNumber(*vIt))) //groupNumber check is to avoid having
                                                                        //an u-v with $ or | in between
      {
        res->push_back(make_pair(*uIt, *vIt));
        lastPosV = *vIt+vSize-1;
        next++;
        vIt++;
        uIt++;
      } else {
        next++;
        uIt++;
      }

    } 
    else 
    {
      vIt++;
    }

  }

  //If I couldn't find any position should return NULL
  if (res->size() == 0)
  {
    delete res;
    res = NULL;
  }
  return res;
}

/**
 * each group is separated by a delimiter (pipe or $), return the group number 
 * of a given pos in the sequence
 * @param  pos 
 * @return     group number
 */
int Sequence::groupNumber(int pos) const
{
  for(unsigned int i = 0; i<delimiterPos_.size(); i++)
  {
    if (pos < delimiterPos_[i]) return i;
  }
  return delimiterPos_.size();
}

/**
 * Given a word create a subword of it given a start and an end index
 * @param w word
 * @param start 
 * @param end
 * @return subword
 */
shared_ptr<Word> Sequence::createSubWord(shared_ptr<Word> w, int start, int end)
{
  
  pair<int,int> startAndEnd;
  list<int>* occs;
  SuffixArray * sArray = getSArray();

  int startPos = w->getOccPos()->front() + start;
  int endPos;
  int length = end-start;

  startAndEnd = sArray->search(&(*this)[startPos], length); 
  startPos = (*sArray)[startAndEnd.first];
  endPos = startPos + length;

  SubSequence* subSeq = new SubSequence(getShared(), startPos, endPos);
  occs = getSubSeqOccPos(subSeq, startAndEnd.first, startAndEnd.second);
  delete subSeq;
  return make_shared<Word>(getShared(), startPos, endPos, occs);
}

/**
 * obtain a WordList from all the Words within the posPairs list given
 * @param  posPairs positions from contexts u and v
 * @param  uSize    size of u context
 * @param  vSize    size of v context
 * @return          WordList of all insides words
 */
WordList* Sequence::obtainWordsInside(list<std::pair<int,int> >* posPairs, int uSize)
{
  //If there is no pairs, there is no Wordlist, so return NULL
  if (posPairs == NULL) return NULL;

  pair<int,int> startAndEnd;

  SuffixArray * sArray = getSArray();

  int uPos = 0;
  int vPos = 0;
  int yPos = 0;
  int ylength = 0;

  int startPos;
  int endPos;
  shared_ptr<Word> yWord;
  shared_ptr<Word> findWord;
  WordList* result = new WordList();

  map< shared_ptr<Word>, int> wordsOccs;

  // list<int> * occs;
  // 
  // cout << "PosPairs size: " << posPairs->size() << endl;

  //iterate over pairs
  for(list< std::pair<int,int> >::iterator it = posPairs->begin(); it != posPairs->end(); ++it)
  {
    clock_t t;
    t = clock();
    uPos = (*it).first;
    vPos = (*it).second;
    yPos = uPos+uSize;
    
    //TODO: Here I'm avoiding the epsilon Inside, shouldn't do it
    if(yPos != vPos)
    {
 
      ylength = vPos - yPos;


      startAndEnd = sArray->search(&(*this)[yPos], ylength);
  

      startPos = (*sArray)[startAndEnd.first];
      endPos = startPos +ylength;
    }
    // Case where I have an empty Inside (Epsilon)
    else
    {
      startPos = 0;
      endPos = 0;
    }
     
    //if I want to save the insides occs I should uncomment the next text:
    //
    // SubSequence* subSeq = new SubSequence(getShared(), startPos, endPos);
    // occs = getSubSeqOccPos(subSeq, startAndEnd.first, startAndEnd.second);
    // delete subSeq;
    // yWord = make_shared<Word>(getShared(), startPos, endPos, occs);
    // 
    yWord = make_shared<Word>(getShared(), startPos, endPos, (list<int>*)NULL);
    //Find if same word has been added, returns NULL or a pointer to existing word.
    findWord = result->find(yWord);


    //if it's not, add it.
    if(findWord == NULL)
    {
      result->insert(yWord);
      wordsOccs.insert(std::make_pair(yWord, 0));
    }
    //Otherwise add a ptr to the existing word and delete the new one.
    else
    {
      result->insert(findWord);
      wordsOccs[findWord]++;
    }
    

    t = clock() - t;
   // printf("Loop: It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

  }

  vector<std::pair<shared_ptr<Word>, int> > wordVec;

  // cout << "Vector rellenado y orden" << endl;

      clock_t t;
    t = clock();

  for( map< shared_ptr<Word>, int>::iterator it = wordsOccs.begin(); it != wordsOccs.end(); ++it ) {
      wordVec.push_back( *it );
  }

  std::sort(wordVec.begin(), wordVec.end(), 
          boost::bind(&std::pair< shared_ptr<Word>, int>::second, _1) >
          boost::bind(&std::pair< shared_ptr<Word>, int>::second, _2));

  result->setOccsVec(wordVec);

      t = clock() - t;
   // printf("Orden: It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

  return result;
}


// Getters:

/**
 * Get Sequence size
 * @return int size
 */
int Sequence::getSize() const
{
	return size_;
}

/**
 * get Sequence in char*
 * @return char* sequence_
 */
char* Sequence::getSequence() const
{
	return sequence_;
}


/**
 * get Sequence in int
 * @return int* intSequence_
 */
int* Sequence::getIntSequence() const
{
	return intSequence_;
}

/**
 * get the Alphabet
 * @return alph_
 */
Alphabet * Sequence::getAlphabet() const
{
  return alph_;
}

/**
 * get the sArray 
 * @return SuffixArray
 */
SuffixArray* Sequence::getSArray() const
{
  return sArray_;
}

//Overload[]

int& Sequence::operator[](int idx)
{
  return intSequence_[idx];
}
const int& Sequence::operator[](int idx) const
{
  return intSequence_[idx];
}

// Print

/**
 * Overload << operator to cout the Sequence
 */
ostream& operator<<(ostream& cout, const Sequence &seq)
{
	int* intS = seq.getIntSequence();
	int size = seq.getSize();

  cout << endl;
  cout << "Printing Sequence..." << endl;
  for(int i=0; i<size;i++)
  {
  	cout << intS[i] << " ";
  }
  cout << endl;
  // cout << "Printing SuffixArray..." << endl;
  // cout << *seq.sArray_;

  return cout;
}
