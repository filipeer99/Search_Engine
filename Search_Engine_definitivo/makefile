output: main.o Varredura.o tratamento.o ind_inv.o ranking.o
	g++ main.o Varredura.o tratamento.o ind_inv.o ranking.o -o output

main.o: main.cpp
	g++ -c main.cpp

Varredura.o: Varredura.cpp Varredura.h
	g++ -c Varredura.cpp

tratamento.o: tratamento.cpp Tratamento.h
	g++ -c tratamento.cpp 

ind_inv.o: ind_inv.cpp ind_inv.h
	g++ -c ind_inv.cpp

ranking.o: ranking.cpp ranking.h
	g++ -c ranking.cpp

teste.o: teste.cpp
	g++ -c teste.cpp

teste: tratamento.o ind_inv.o teste.o
	g++ -c tratamento.o ind_inv.o teste.o -o teste_run


clean:
	rm *.o