#include "SuffixArray.h"


// SuffixArray::SuffixArray()
// {
// 	sequence_ = NULL;
// 	sArray_ = NULL;
// 	lcp_ = NULL;
// 	inverse_ = NULL;
// 	size_ = 0;
// 	maxAlph_ = 0;
// }


/**
 * make new sArray
 */
void SuffixArray::makeSArray_()
{
	sArray_ = new int[size_+2];
	int max = *max_element(sequence_, sequence_+size_+1);

	sais_int(sequence_, sArray_, size_+1, max+1);

	sArray_[size_+1] = 0;
}

/**
 * Construct sArray based on
 * @param seq, the sequence
 * @param size, the size of the sequence
 * @param larsson
 * @param maxAlpha
 */
SuffixArray::SuffixArray(int* seq, int size, bool larsson, int maxAlph)
{
	// Prepare seq for sarray creation requirements
	int* sArraySeq = new int[size+6];
	for( int i=0; i< size; i++)
	{
		sArraySeq[i] = seq[i];
	}

	maxAlph_ = maxAlph;
	size_ = size;
	sequence_ = sArraySeq;
	// Set requirements:
	sequence_[size] = 0;
	sequence_[size+1] = 0;
	sequence_[size+2] = 0;
	sequence_[size+3] = 0;

	inverse_ = new int[size+1];

	if(larsson)
	{
		for(int i=0; i<size+1 ; i++)
		{
			inverse_[i] = sequence_[i];
		}
		inverse_[size] = 0;
		this->makeSArray_();
	}
	else
	{
		this->makeSArray_();
		for(int i=0; i < size+1; i++ )
		{
			inverse_[sArray_[i]] = i;
		}
	}
	lcp_ = new int[size+2]; //least common prefix
	lcpa(sArray_, sequence_, lcp_, size+1, inverse_); //calculate lcp

	// Why delete inverse here and not in the destructor??
	// delete[] inverse_;
	// inverse_ = NULL;
	lcp_[size+1] = 0;
}

/**
 * delete sequence_ sArray_, inverse_, lcp_
 */
SuffixArray::~SuffixArray()
{
	delete[] sequence_;
	delete[] sArray_;
	delete[] lcp_;
	delete[] inverse_;
}


static int genstrcmp(int* s1, int start1, int end1, int* s2, int start2, int end2){
	while(start1 < end1 && start2 < end2 && s1[start1] == s2[start2]){
		start1++; start2++;
	}
	int res;
	if (start1 == end1 && start2 == end2 && s1[start1-1] == s2[start2-1]) res = 0;
	else if (start1 == end1) res = -1;
	else if (start2 == end2) res = 1;
	else{
		res = (s1[start1] < s2[start2] ? -1  : 1);
	}
	return res;
}


pair<int,int> SuffixArray::search(int* s, int size){
  int l,r,m,cmp;
  m = 0;
  l = 0; r = size_;
  while(r-l > 1){
    m = (l+r)/2;
    cmp = genstrcmp(s, 0, size, sequence_, sArray_[m], sArray_[m]+size);
    if (cmp == 0)
      r = l = m;
     else if (cmp < 0)
      r = m;
    else
      l = m;
  }
  int b,e;
  e=r+1; b=r;
  while(lcp_[e] >= size) e++;
  while(lcp_[b] >= size) b--;
  return make_pair(b,e);
}

//Overload []

int& SuffixArray::operator[](int idx)
{
  return sArray_[idx];
}
const int& SuffixArray::operator[](int idx) const
{
  return sArray_[idx];
}


// Getters

/**
 * get suffix array size
 * @return int size_
 */
int SuffixArray::getSize() const
{
	return size_;
}

/**
 * get sArray
 * @return int* sArray_
 */
int* SuffixArray::getSArray() const
{
	return sArray_;
}

/**
 * get less common prefix
 * @return int* lcp_
 */
int* SuffixArray::getLCP() const
{
	return lcp_;
}

// Print

/**
 * overload << operator to print SuffixArray
 */
ostream& operator<<(ostream& cout, SuffixArray &sArray)
{

	int* sA = sArray.getSArray();
	int* lcp = sArray.getLCP();
	int size = sArray.getSize();
  cout << endl << "==== SARRAY ====" << endl << endl;
  for(int i=0; i<size+1;i++)
  {
  	cout << sA[i] << " ";
  }
  cout << endl;

  cout << endl << "==== LCP ====" << endl << endl;
  for(int i=0; i<size+1;i++)
  {
  	cout << lcp[i] << " ";
  }
  cout << endl;
  return cout;
}
