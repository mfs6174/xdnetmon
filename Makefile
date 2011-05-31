All : main.cpp var.o include.h h.h pcap.o map.o sql.o exit.o timer.o hunman.o main.o
	g++ -g -o netmon  -lpcap -lsqlite3  pcap.o map.o sql.o exit.o hunman.o timer.o main.o
	sudo chmod +x netmon 
main.o :main.cpp include.h h.h
	g++ -g -o main.o -c main.cpp -l var.o
var.o: var.h include.h h.h
	g++ -g -o var.o var.h
pcap.o: pcapinit.cpp var.o include.h h.h
	g++ -g -lpcap -o pcap.o -c pcapinit.cpp -l var.o
map.o : map.cpp var.o h.h include.h
	g++ -g -o map.o -c map.cpp -l var.o
exit.o: exit.cpp var.o include.h h.h
	g++ -g -o exit.o -c exit.cpp -l var.o
sql.o : sql.cpp var.o include.h h.h
	g++ -g -lsqlite3 -o sql.o -c sql.cpp -l var.o
timer.o: timer.cpp include.h h.h
	g++ -g -o timer.o -c timer.cpp
hunman.o: hunman.cpp include.h h.h
	g++ -g -o hunman.o -c hunman.cpp
clean:
	rm -f *.o

