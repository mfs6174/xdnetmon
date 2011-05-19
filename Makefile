All : main.cpp var.o include.h h.h pcap.o
	g++ -g -o netmon main.cpp var.o pcap.o
var.o: var.h
	g++ -g -o var.o var.h
pcap.o: pcapinit.cpp var.o include.h h.h
	g++ -g -o pcap.o pcapinit.cpp var.o