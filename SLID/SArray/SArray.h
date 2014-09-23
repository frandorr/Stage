#ifndef _SArray_h_
#define _SArray_h_

typedef unsigned char uchar;

int lcpa(const int *a, const int *s, int *b, int n, int *inv);
int pred_char(int const* seq, const int pos);



void suffixArray(int* s, int* SA, int n, int K) ;
void suffixsort(int *x, int *p, int n, int k, int l);

int sais_int(const int *T, int *SA, int n, int k);


#endif // _SArray_h_
