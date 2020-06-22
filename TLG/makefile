file=$(shell ls -ltr *cpp | cut -d" " -f 9-9)
ofile=$(shell basename $(file) .cpp).exe
in1=1.in

.PHONY: top

$(ofile): $(file)
	g++ -std=c++17 -o $@ $^

t1: $(ofile)
	./$(ofile) < $(in1)
