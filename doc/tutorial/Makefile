#SRC = $(wildcard *.tex)
SRC = tutorial-ja.tex
DVI = $(SRC*.tex=.dvi)
PDF = $(SRC:.tex=.pdf)
TEXC = platex
DVI2PDF = dvipdfmx


all: $(PDF)
	echo $(PDF)

%.pdf: %.dvi
	$(DVI2PDF) $^ 
	@echo done.

%.dvi: %.tex
	$(TEXC) $^
	@echo done.


c: clean

clean:
	rm -rf *.dvi *.pdf *.log *.aux *~

