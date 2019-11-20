CXXFLAGS += -std=c++11

hwk5: main.o Cabin.o Copilot.o CrewMember.o CrewMembers.o Flight.o Flights.o Pilot.o Plane.o Planes.o
	g++ $(CXXFLAGS) -o hwk5 main.o Cabin.o Copilot.o CrewMember.o CrewMembers.o Flight.o Flights.o Pilot.o Plane.o Planes.o
Cabin.o: Cabin.cpp Cabin.h CrewMember.h
	g++ $(CXXFLAGS) -c Cabin.cpp
Copilot.o: Copilot.cpp Copilot.h CrewMember.h
	g++ $(CXXFLAGS) -c Copilot.cpp
CrewMember.o: CrewMember.cpp CrewMember.h
	g++ $(CXXFLAGS) -c CrewMember.cpp
CrewMembers.o: CrewMembers.cpp CrewMembers.h CrewMember.h Pilot.h Copilot.h Cabin.h
	g++ $(CXXFLAGS) -c CrewMembers.cpp
Flight.o: Flight.cpp Flight.h CrewMember.h
	g++ $(CXXFLAGS) -c Flight.cpp
Flights.o: Flights.cpp Flights.h Flight.h CrewMember.h CrewMembers.h Planes.h Plane.h
	g++ $(CXXFLAGS) -c Flights.cpp
Pilot.o: Pilot.cpp Pilot.h CrewMember.h
	g++ $(CXXFLAGS) -c Pilot.cpp
Plane.o: Plane.cpp Plane.h
	g++ $(CXXFLAGS) -c Plane.cpp
Planes.o: Planes.cpp Planes.h Plane.h
	g++ $(CXXFLAGS) -c Planes.cpp
main.o: main.cpp Planes.h Plane.h CrewMembers.h CrewMember.h Flights.h Flight.h
	g++ $(CXXFLAGS) -c main.cpp
