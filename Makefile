All : main.cpp var.o include.h h.h pcap.o  map.o sql.o exit.o timer.o hunman.o main.o
	g++ -g -o netmon  -lstdc++ -lpcap -lsqlite3  pcap.o  sql.o  map.o exit.o hunman.o timer.o main.o var.o
	chmod +x netmon 
main.o :main.cpp include.h h.h
	g++ -g -o main.o -c main.cpp
var.o: var.cpp include.h h.h
	g++ -g -o var.o -c var.cpp
pcap.o: pcapinit.cpp include.h h.h
	g++ -g -lpcap -o pcap.o -c pcapinit.cpp 
map.o : map.cpp var.o h.h include.h
	g++ -g -o map.o -c map.cpp
exit.o: exit.cpp include.h h.h
	g++ -g -o exit.o -c exit.cpp
sql.o : sql.cpp include.h h.h
	g++ -g -lsqlite3 -o sql.o -c sql.cpp
timer.o: timer.cpp include.h h.h
	g++ -g -o timer.o -c timer.cpp
hunman.o: hunman.cpp include.h h.h
	g++ -g -o hunman.o -c hunman.cpp
clean:
	rm -f *.o

