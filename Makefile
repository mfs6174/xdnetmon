All : main.cpp var.o include.h h.h pcap.o  map.o sql.o exit.o timer.o human.o main.o conf.o interactive.o snifer.o
	g++  -o netmon  -lstdc++ -lpcap -lsqlite3  pcap.o  sql.o  map.o exit.o human.o timer.o main.o var.o conf.o interactive.o snifer.o
	chmod +x netmon 
main.o :main.cpp include.h h.h
	g++  -o main.o -c main.cpp
var.o: var.cpp include.h h.h
	g++  -o var.o -c var.cpp
pcap.o: pcapinit.cpp include.h h.h
	g++  -lpcap -o pcap.o -c pcapinit.cpp 
map.o : map.cpp var.o h.h include.h
	g++  -o map.o -c map.cpp
exit.o: exit.cpp include.h h.h
	g++  -o exit.o -c exit.cpp
sql.o : sql.cpp include.h h.h
	g++  -lsqlite3 -o sql.o -c sql.cpp
timer.o: timer.cpp include.h h.h
	g++  -o timer.o -c timer.cpp
human.o: human.cpp include.h h.h
	g++  -o human.o -c human.cpp
conf.o: conf.cpp include.h h.h
	g++  -o conf.o -c conf.cpp
interactive.o: interactive.cpp include.h h.h
	g++  -o interactive.o -c interactive.cpp
snifer.o: sniff.cpp include.h h.h
	g++  -o snifer.o -c sniff.cpp
clean:
	rm -f *.o
cleandata:
	rm -f *.db

