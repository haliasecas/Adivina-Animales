all: adivina.cpp
	g++ adivina.cpp -o Adivina -O2

clean: 
	rm -f ./a.out
