import random
from itertools import izip
def pairwise(iterable):
    "s -> (s0,s1), (s1,s2), (s2, s3), ..."
    a = iter(iterable)
    return izip(a, a)

def pairFunction(x,y):
	if x<y:
		res = y**2 + x - y
	else:
		res = x**2 + x + y - x
	return res

my_randoms = [2,1,1,0,0,1,3,0,0]
print my_randoms

while len(my_randoms)>1:
	res = []
	for a,b in pairwise(my_randoms):
		print a, b
		res.append(pairFunction(a,b))

	my_randoms = res

print res
