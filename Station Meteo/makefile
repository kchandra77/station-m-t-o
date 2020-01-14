all: stationMeteo G2PortSerie.o WS2300.o main.o

G2PortSerie.o: G2PortSerie.cpp G2PortSerie.h
	g++ -Wall -c G2PortSerie.cpp

WS2300.o: WS2300.h WS2300.cpp
	g++ -Wall -c WS2300.cpp

main.o: main.cpp
	g++ -Wall -c main.cpp

stationMeteo: main.o G2PortSerie.o WS2300.o
	g++ -Wall main.o G2PortSerie.o WS2300.o -o stationMeteo

clean:
	rm -f main.o G2PortSerie.o WS2300.o stationMeteo  
