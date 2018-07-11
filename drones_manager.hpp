#ifndef DRONES_MANAGER_HPP
#define DRONES_MANAGER_HPP
#include <string>
#include <iostream>
using namespace std;

class DronesManager {
protected:
    // node structure used for DronesManager
    struct DroneRecord {
    	DroneRecord() : prev(), next() {}
    	DroneRecord(unsigned int newDroneID) : prev(), next(), droneID(newDroneID) {}
        DroneRecord(unsigned int newDroneID, unsigned int newRange,
			unsigned int newYearBought, string newDroneType,
			string newManufacturer, string newDescription, string newBatteryType) :
				prev(), next(), droneID(newDroneID), range(newRange),
				droneType(newDroneType), yearBought(newYearBought),
				manufacturer(newManufacturer), description(newDescription),
				batteryType(newBatteryType) {}

        unsigned int droneID, range, yearBought;
		string droneType, manufacturer, description, batteryType;

        DroneRecord* next;
        DroneRecord* prev;
    };
    
    // setup DronesManagerTest as friend so tests have access to private variables
	friend class DronesManagerTest;
	// implement comparison  operator to compare two DroneRecord instances
	friend bool operator==(const DronesManager::DroneRecord&, const DronesManager::DroneRecord&);

	// optional: helper method to get the DroneRecord pointer using drone index
	// this method will not be used in testing
    DroneRecord* getDroneRecord(unsigned int) const;

    // a pointer to the first node in the list
    DroneRecord* first;
    // a pointer to the last node in the list
    DroneRecord* last;
    // the number of elements in the list
    unsigned int size;    

    // copy constructor; not to be used for this assignment
    DronesManager(const DronesManager& rhs) {}
    // assignment operator; not to be used for this assignment
    //DronesManager& operator=(const DronesManager& rhs) {}
    
public:
	// EXPLICIT CONSTRUCTOR AND DESTRUCTOR
    // creates a new empty DronesManager
    DronesManager();
    // destroy this DronesManager, and frees up all dynamically allocated memory
    ~DronesManager();

	// ACCESSORS
    // returns the number of elements in the list
    unsigned int get_size() const;
    // returns true if the list is empty, false otherwise
    bool empty() const;
    // returns the value at the given index in the list 
    // if index is invalid, returns the last element; if the list is empty, returns DroneRecord(0)
    DroneRecord select(unsigned int index) const;
    // searches for the given value, and returns the index of this value if found
    // returns the size of the list otherwise; if the list is empty, returns 0
    unsigned int search(DroneRecord val) const;
    // prints all elements in the list to the standard output
    void print() const;

	// MUTATORS
    // inserts a value into the list at a given index; the list is not sorted
    bool insert(DroneRecord val, unsigned int index);
    // inserts a value at the beginning of the list; the list is not sorted
    bool insert_front(DroneRecord val);
    // inserts a value at the end of the list; the list is not sorted
    bool insert_back(DroneRecord val);
    
    // deletes a value from the list at the given index
    bool remove(unsigned int index);
    // deletes a value from the beginning of the list
    bool remove_front();
    // deletes a value at the end of the list
    bool remove_back();
    
    // replaces the value at the given index with the given value; the list is not sorted
    bool replace(unsigned int index, DroneRecord val);    
    // reverses the linked list
    bool reverse_list();
};

// application of inheritance; DronesManagerSorted inherits public and protected members of DronesManager
// visibility declaration is "public", so public members of DronesManager remain public
class DronesManagerSorted : public DronesManager {	
public:
	// ACCESSORS
	// returns true if the list is sorted in ascending (non-descending) order
    bool is_sorted_asc() const;
    // returns true if the list is sorted in descending (non-ascending) order
    bool is_sorted_desc() const;
    
	// MUTATORS    
	// inserts a value so that the list remains sorted in ascending order
	// if the list is not sorted in appropriate order, insertion is rejected
    bool insert_sorted_asc(DroneRecord val);
    // inserts a value so that the list remains sorted in descending order
    // if the list is not sorted in appropriate order, insertion is rejected
    bool insert_sorted_desc(DroneRecord val);
    // sorts the list into ascending (non-descending) order
    void sort_asc();
    // sorts the list into descending (non-ascending) order
    void sort_desc();
    void swapValues(DroneRecord* valOne, DroneRecord* valTwo);
};
#endif 
