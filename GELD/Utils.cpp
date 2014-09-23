#include "Utils.h"

bool VERBATIM = 0;

/**
 * convert a number to its char version based on the alphabet. It's hardcoded
 * rightnow
 * @param  n number
 * @return   char representing the number
 */
char toChar(int n)
{
	switch(n){
		case 1: return 'S';
		break;
		case 2: return '|';
		break;
		case 3: return 'a';
		break;
		case 4: return 'c';
		break;
		case 5: return 'g';
		break;
		case 6: return 't';
		break;
		default: return (char) (((int)'0')+n);
		break;
	}
}

