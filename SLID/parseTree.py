import nltk
from nltk import grammar
from nltk.grammar import Nonterminal
from nltk.draw.tree import draw_trees
from nltk import tree, treetransforms
from copy import deepcopy


def noRepeats(seq):
    seen = set()
    seen_add = seen.add
    return [ x for x in seq if not (x in seen or seen_add(x))]


def slade(t):
	lcount = {}

	xs = [];
	# Dic with key = lhs, value list of rhs
	prods = {}

	# I'm gonna use this to avoid repeated Non Terminals
	rhs = set()

	# This set has all Insides non terminals
	inside = set()
	lastInside = -1
	x = -1
	i = -1

	# Count apparitions of non terminals lhs
	for p in noRepeats(t.productions()):
		lcount[p.lhs()] = lcount.get(p.lhs(), 0) + 1
		print p


	# add inside non terminals to inside set
	for key, value in lcount.iteritems():
		if value > 1:
			inside.add(key)
 
	# Nodes in postOrder
	postOrder = t.treepositions(order='postorder')
	for n in postOrder:
		if type(t[n]) is not str:
			currentProd = t[n].productions()[0]


			# Add prods to dict where key is lhs and value a list of the rhs
			if(currentProd.lhs() not in prods):
				prods[currentProd.lhs()] = []

			# If rhs is not in the lhs key, add it to the rhs list
			if(currentProd.rhs() not in prods.get(currentProd.lhs())):
				prods[currentProd.lhs()].append(currentProd.rhs())
				

			# Remember last inside used, to add the +x
			if(currentProd.lhs() in inside):
				lastInside = int(Nonterminal.symbol(currentProd.lhs()))
				x = prods[currentProd.lhs()].index(currentProd.rhs())
				i = 0
			else:
				i = prods[currentProd.lhs()].index(currentProd.rhs())

			# change node name based on Inside
			if(Nonterminal.symbol(currentProd.lhs()) != 'S'):
				if(int(Nonterminal.symbol(currentProd.lhs())) == lastInside + 1):
					t[n].node = t[n].node + "(" + str(i) + ")" + " + " + str(x)
					xs.append(x);
					# t[n].node = t[n].node + str(i)  + str(x)
				else: 
					t[n].node = t[n].node + "(" + str(i) + ")"
					# t[n].node = t[n].node + str(i) 

	# Print parse tree productions
	print "Productions: "
	noRep = noRepeats(t.productions())
	for p in noRep:
		if p.rhs() in rhs:
			noRep.remove(p)
		rhs.add(p.rhs())	

	total = 0
	for p in noRep:
		total += p.__len__() + 1
		print p

	print "TAM TOTAL: "
	print total

	print "ENCODING"
	for el in xs:
		print el

	# draw parse tree
	t.draw()


	# lcount = {}
	# prhs = {}


	# t.draw()
	# counter = 0
	# # prods = {}
	# # productions = t.productions()

	# # for prod in productions:
	# # 	prods[prod.lhs] = prod.rhs

	# # # RHS: saves the already added rhs 
	# rhs = {}

	# # Obtain nodes in postOrder
	# postOrder = t.treepositions(order='postorder')
	# for pos in postOrder:

	# 	# Do not enter if it's the first node S, or a terminal
	# 	if pos != () and t[pos] != 'a' and t[pos] != 'g' and t[pos] != 'c' and t[pos] != 't':
	# 		# print t[pos].productions()
			
	# 		# take first production of a position (subtree)
	# 		prod = t[pos].productions()[0]
	# 		if lcount.get(p.lhs()) > 1:
	# 			prhs[p.lhs].append(p.rhs)
	# 			lastInside = p.lhs()
	# 		else:
	# 			# instead of this maybe is better to have a dict: Non Termi -> Inside
	# 			if p.lhs() == lastInside + 1:
	# 				t[pos].node = t[pos].node + "+" lastInsideIndex


	# 		# If it already exists a rhs in the dict, use its value lhs as node name
	# 		if prod.rhs() in rhs:
	# 			t[pos].node = str(rhs.get(prod.rhs(), 0)) 

	# 		# else add new name
	# 		else:
	# 			t[pos].node = str(counter)
	# 			rhs[prod.rhs()] = counter
	# 			counter +=1
	# 	# if pos != () and t[pos] != 'a' and t[pos] != 'c' and t[pos] != 'g' and t[pos] != 't':
	# 	# 	print t[pos]
	# 	# 	t[pos] = counter
	# 	# 	counter+=1
	# 	# tPos = t[pos]
	# 	# print tPos
	# 	# 	if tPos in rhs:
	# 	# 		t[pos] = rhs.get(tPos.rhs(), 0)
	# 	# 	else:
	# 	# 		rhs[tPos.rhs()] = t[pos]
	# print "CAMBIO ALGO?"
	# for p in noRepeats(t.productions()):
	# 	print p
	# t.draw()

	# grammar = nltk.induce_pcfg('S', noRepeats(t.productions()))
	# print grammar

	# parser = tree.Tree.parse(t.pprint(margin=70, indent=0, nodesep='', parens='()', quotes=False))
	# gram = grammar.('S', noRepeats(t.productions()))
	# print gram

file_content = open("token").read()
tokens = nltk.word_tokenize(file_content)


grammar = nltk.data.load('file:myGrammar.cfg')
# print grammar
# grammar = nltk.parse_cfg("""
# S -> 8 'a' 'a' 10 10 'g' 8 't' 't' 'a' 
# 7 -> 'a' 'c' 'g' 'a' | 'g' |
# 8 -> 'a' 'g' 7 't' 
# 9 -> 'a' 'a' 8 | 
# 10 -> 8 'g' 9 'g' 'a' 'c' 'c' 
# """)
# 
# 
# (S (NP I) (VP (V saw) (NP him)))

print grammar.is_chomsky_normal_form()
sent = tokens
parser = nltk.ChartParser(grammar)
trees = parser.nbest_parse(sent)
# print "trees"
slade(trees[0])
# for t in trees:
	# t.draw()
	# slade(t)
	# t.draw()
	# print "PostOrder"
	# print t.treepositions(order='postorder')
	# print "InOrder"	
	# print t.treepositions(order='inorder')
	# print "PreOrder"
	# print t.treepositions(order='preorder')
	# # print tree
	# # tree.collapse_unary(collapsePOS = False, collapseRoot = False, joinChar = "+")
	# # print tree
	# # tree.chomsky_normal_form(factor='left', horzMarkov=None, vertMarkov=0, childChar='|', parentChar='^')
	# print "Pretty Print"
	# print t.pprint(margin=70, indent=0, nodesep=':', parens='[]', quotes=False)
	# s = tree.Tree.parse(t.pprint(margin=70, indent=0, nodesep='', parens='()', quotes=False))
	# for p in s.productions():
	# 	print p

	# g = nltk.grammar.induce_pcfg('S', s.productions())
	# print "GRAMMAR"
	# print g
	# print "SUBTREES"
	# for sub in t.subtrees(lambda t: t.height() == 2):
	# 	print(sub)
	# s.chomsky_normal_form(factor="right", horzMarkov=None, vertMarkov=0, childChar="|", parentChar="^")

