

sample: sample.o
	g++ -o sample sample.o -L ../lib -lstdc++ -ldltools -ldlparser -lantlr -ldlite -lsqlite

sample.o: sample.cpp
	g++ -c -O2 -I ../include sample.cpp 
	
clean:
	rm sample.exe
	rm sample.o
