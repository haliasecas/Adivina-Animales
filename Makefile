all: adivina.cpp
	@g++ adivina.cpp -o Adivina -O2
	@echo "Compilado";

clean: 
	@rm -f ./a.out
