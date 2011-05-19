All : main.cpp var.o include.h h.h pcap.o map.o
	g++ -g -o netmon -c main.cpp -l var.o pcap.o map.o
var.o: var.h include.h h.h
	g++ -g -o var.o -c var.h
pcap.o: pcapinit.cpp var.o include.h h.h
	g++ -g -lpcap -o pcap.o -c pcapinit.cpp -l var.o
map.o : map.cpp var.o h.h include.h
	g++ -g -o map.o -c map.cpp -l var.o
exit.o: exit.cpp var.o include.h h.h
	g++ -g -o exit.o -c exit.cpp -l var.o
