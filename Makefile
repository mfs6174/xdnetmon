All : main.cpp var.o include.h h.h pcap.o map.o
	g++ -g -o netmon main.cpp var.o pcap.o map.o
var.o: var.h include.h
	g++ -g -o var.o var.h
pcap.o: pcapinit.cpp var.o include.h h.h
	g++ -g -o pcap.o pcapinit.cpp var.o
map.o : map.cpp var.o h.h include.h
	g++ -g -o map.o map.cpp var.o
