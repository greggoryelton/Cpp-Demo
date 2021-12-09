fp:	main.o Control.o Record.o ReportGenerator.o View.o Record.o
	g++ -std=c++98 -o fp main.o Control.o Record.o ReportGenerator.o View.o

main.o:	main.cc Control.o View.o
	g++ -c main.cc

Control.o:	Control.h Control.cc
	g++ -c Control.cc

Record.o:	Record.h Record.cc
	g++ -c Record.cc

ReportGenerator.o: ReportGenerator.h ReportGenerator.cc Property.h 
	g++ -c ReportGenerator.cc 

clean:
	rm -rf *.o fp
