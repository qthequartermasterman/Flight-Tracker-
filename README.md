# Flight Tracker
DESCRIPTION:   Rudimentary Airline Model Program. A console-based flight tracker capable of scheduling pilots, planes, and airports. Implemented in C++ as a project for the class CSCE 1040.

AUTHOR:        Andrew P. Sansom

VERSION:       1.0.0

VERSION DATE:  3/19/19

EMAIL:         andrewsansom@my.unt.edu

COURSE:        CSCE 1040

## Function Psuedocode Samples
###	Global Functions
- load() loads all the data from a previously saved file.
- save() saves all the data to a file on the drive.
- main() presents a menu dialog to the user, which then allows them to choose other actions. Every time a user operation is completed, it autosaves the information. The main function also uses Flights’s updateAllFlightStatuses() periodically.

#### CrewMember
- Standard set/get methods
- void printInfo() which prints the crew member’s record to the console.

#### Flight
- Standard set/get methods
- printInfo() which prints the flight data to the console

#### Plane
- Standard set/get methods
- printInfo() which prints the plane data to the console
o

#### CrewMembers
- addCrew() presents a dialog to the user that asks for the potential CrewMember’s ID (integer) and careerType (string, such as Pilot or Cabin).
- editCrew() presents a dialog to the user asking which properties they would like to change. It then prompts for the new value, checking against its restrictions (for example, if an ID is already taken). If the user tries to change a value that will cause another property to have an illegal value, it warns the user. If the user decides to continue, it then asks for updated values of the other properties.
- deleteCrew() presents a dialog to the user that asks for the ID of the CrewMember that they would like to delete. It then asks for confirmation before deleting the CrewMember object and updating the collection.
- findCrewMembersByName(name) searches for every Crew Member with the given name
- findCrewMembersByID(crewID) searches for every CrewMember with the given crewID.
- findCrewMembersByType(type) searches for every CrewMember with the given type.
- printListOfPeople() iterates over every CrewMember in the collection and runs printIndividualInfo(crewID) with their respective crewID.
- printIndividualInfo(crewID) displays an individual CrewMember’s information in an organized table to the console.
- checkCareerType(crewID) returns the careerType of the crewmember with crewID in the collection.
- isIDtaken(id) checks all of the CrewMembers to see if there is already a CrewMember with the specified id.
- loadData() Loads data from disk.
- storeData() Saves data from disk.

#### Flights
- addFlight() presents a dialog to the user that asks for the potential flight’s startTime (date/time), endTime (date/time), startPort (string), endPort (string), numberOfPilots (integer), numberOfCrewCabin (integer), pilotIDs (List), cabinCrewIDs (List), numberOfPassengers (integer). Before accepting each value, it checks if the value is valid. I.E. If the if the flight is longer than 8 hours, it must have 2 pilots and 2 copilots and twice the minimum crew of the plane. It also checks, when recording pilotIDs and cabinCrewIDs, if the crewmember is of the correct occupation/type. It then creates a new flight, adds it to the collection, and sets all of its info to the recorded values. Also checks if the plane has a range sufficiently large to make the flight.
- editFlight() presents a dialog to the user asking which properties they would like to change. It then prompts for the new value, checking against its restrictions. If the user tries to change a value that will cause another property to have an illegal value, it warns the user. If the user decides to continue, it then asks for updated values of the other properties.
- deleteFlight() presents a dialog to the user that asks for the ID of the flight that they would like to delete. It then asks for confirmation before deleting the flight object and updating the collection.
- cancelFlight() prompts the user for the flightID of the flight the user wishes to cancel. It then searches for that flight, and changes its status to “Canceled”
- findFlightsByID() searches for every flight with the givenID.
- findFlightsByPlane(planeID) searches for every flight with the plane with planeID.
- findFlightsByCrew(crewID) searches for every flight with a crewmember with crewID.
- findFlightsByStatus(status) searches for every flight with status.
- printIndividualFlightInfo(flightID) prints to the console the information of the flight with flightID.
- printListOfFlights() runs printIndividualFlightInfo(flightID) for every flight in the collection.
- checkIfPlaneIsAvailable(planeID, time) searches for every flight with the given planeID and sees if time is between its start time and end time return true if available, false if not.
- printPlaneSchedule(planeID) searches for every flight that uses the plane with planeID, then prints that flight’s info to the console.
- printCrewMemberSchedule(personID) searches for every flight that uses the crew member with personID, then prints that flight’s info to the console.
- printListOfFlightsByStatus(status) searches for every flight with status, and then runs printIndividualFlightInfo() with that flight’s ID.
- deleteAllCanceledFlights() searches for every flight that is marked as “Cancelled”, then deletes that flight with the deleteFlight() method.
- deleteAllCompletedFlights() searches for every flight that is marked as “Completed”, then deletes that flight with the deleteFlight() method.
- updateAllFlightStatuses() loops over each Flight in the collection. If a flight is not canceled, it checks if the date/time is after the end time. If so, it will update the status from “Active” to “Completed”.
- isIDtaken(id) checks all of the flights to see if there is already a flight with the specified id.
- updateCrewForAllFlightsWithPlane(planeID) searches for every flight with planeID, and then checks if the crewAssigned is atleast that plane’s minimumNumberOfSeats (if a short flight) or twice the minimum (if a long flight). If there is a deficit, it asks the user to supply more crew Members until the deficit is fixed. NOTE: This would normally only be called automatically when the user modifies a plane’s minimumNumberOfSeats.
- isCrewMemberAvailable(int crewID, time startTime,time endTime) searches for every flight with the given crewmember and checks if time is between its start time and end time return true if available, false if not.
o
- checkIfPlaneIsAvailable(string planeID, time startTime,time endTime) searches for every flight with the given planeID and sees if time is between its start time and end time return true if available, false if not.
- loadData() Loads data from disk.
- storeData() Saves data from disk.

#### Planes
- addPlane() presents a dialog to the user that asks for the potential plane’s data:
    - Make (string)
    - Model (integer)
    - Tail Number (string)
    - Number of Seats (integer)
    - Range (integer)
    - minimumNumberOfCrew (integer)
    - Before accepting each value, it checks if the value is valid. E.G. Seat Number, Range, and minimumNumberOfCrew must all be nonnegative. It then creates a new plane, adds it to the collection, and sets all of its info to the recorded values.
- editPlane() presents a dialog to the user asking which properties they would like to change. It then prompts for the new value, checking against its restrictions. If the user tries to change a value that will cause another property to have an illegal value, it warns the user. If the user decides to continue, it then asks for updated values of the other properties.
    - NOTE: This might mean that some already booked flights might have too few CrewMembers. If the minimumNumberOfCrew increases, then run “updateCrewForAllFlightsWithPlane(planeID)”, which will prompt the user to update the crews on flights with this plane.
- deletePlane() presents a dialog to the user that asks for the ID of the plane that they would like to delete. It then asks for confirmation before deleting the plane object and updating the collection.
- findPlanesByID(planeID) returns all planes with the given planeID.
- printListOfPlanes() runs printIndividualPlaneInfo(planeID) for every plane in the collection.
- printIndividualPlaneInfo() displays an individual plane’s information in an organized table to the console.
- doesPlaneHaveEnoughSeats(integer planeID, int necessaryNumberOfSeats) searches for the plane in its collection with planeID, and checks if it has greater than or equal to the necessaryNumberOfSeats, returning the result.
- isIDtaken(id) checks all of the planes to see if there is already a plane with the specified id.
- getMinCrewOfPlane(string planeID) Returns the minimum number of crew required for a certain plane.
- loadData() Loads data from disk.
- storeData() Saves data from disk.

#### Pilot (Inherited from CrewMember)
- int getType() returns the integer corresponding to the pilot type
- editInfo method prompts the user for which property they would like to change. It then provides appropriate prompts to adjust those properties.
- printInfo method first prints the base class info, then the derived class info

#### Copilot
- int getType() returns the integer corresponding to the copilot type
- editInfo method prompts the user for which property they would like to change. It then provides appropriate prompts to adjust those properties.
- printInfo method first prints the base class info, then the derived class info

#### Cabin
- int getType() returns the integer corresponding to the cabincrew type
- editInfo method prompts the user for which property they would like to change. It then provides appropriate prompts to adjust those properties.
- printInfo method first prints the base class info, then the derived class info


## Post Mortem Report

I spent approximately 7-9 hours on this assignment. Although I started several weeks ago, I got caught up with other things and neglected to finish the revisions until the weekend before this assignment was due. It was fairly straight forward as soon as I understood the inheritance relations. Those took me a brief moment to understand how to picture the use of virtual functions to solve problems. As soon as I figured, those out, however, the code almost wrote itself.
The bulk of the time spent was mostly just a matter of continuing to test and retest things to make sure the modifications did not break previously functional behavior. I wish I had written automated unit tests prior. That would have accelerated a lot of time spent testing things over and over again.
