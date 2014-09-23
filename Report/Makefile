CC = pdflatex
CCLOG = makelog

PDF = report.pdf
TEX = report.tex 
MAIN = report.tex

TRASH = *.log *.toc *.aux *.out makelog

.PHONY: all clean

all: $(PDF)
	rm -f $(TRASH) $(PDF)
	make $(PDF)
	rm -f $(TRASH)

$(PDF): $(TEX) 
	$(CC) $(MAIN) > $(CCLOG)
	echo "" >> $(CCLOG) && echo "" >> $(CCLOG)
	echo "-------------------------------------------------------------\
	-----------" >> $(CCLOG)
	echo "" >> $(CCLOG) && echo "" >> $(CCLOG)
	$(CC) $(MAIN) >> $(CCLOG)

clean:
	rm -f $(TRASH)
