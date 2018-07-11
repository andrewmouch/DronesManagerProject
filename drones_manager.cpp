#include "drones_manager.hpp"

DronesManager::DronesManager() {
    first = NULL;
    last = NULL;
    size = 0;
}

DronesManager::~DronesManager() {
    //WILL FINISH LATER
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
    return (first == NULL);
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (empty()){
	    return DroneRecord(0);
	}
    if (index > size - 1){
	    index = size - 1;
	}
    DroneRecord* temp = first;
    for (int i = 0; i < index; i++){
        temp = temp->next;
	}
    return *temp;
}

unsigned int DronesManager::search(DroneRecord value) const {
	if (empty()) {
        return 0;
    }
    DroneRecord* temp = first;

	unsigned int index = 0;
	while (!(operator==(*temp,value)) && index != size){
        temp =temp->next;
        index++;
	}
	return index;
}

void DronesManager::print() const {
    DroneRecord* temp = first;
    for (int i = 0; i < size; i++){
        cout << "Drone ID: " << temp->droneID
             << "   Range: " << temp->range
             << "   YearBought: " << temp->yearBought
             << "   DroneType: " << temp->droneType
             << "   Manufacturer: " << temp->manufacturer
             << "   Description: " << temp->description
             << "   BatteryType: " << temp->batteryType << endl;
        temp=temp->next;
    }
    cout << endl;
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
    return (lhs.droneID == rhs.droneID);
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	if (index > size) {
        return false;
    }
    if (index == 0){
	    return insert_front(value);
	}
    if (index == size){
        return insert_back(value);
    }

    DroneRecord* addressPtr = first;
	int iterIndex = 0;
	while (iterIndex < index){
	    addressPtr = addressPtr->next;
	    iterIndex++;
	}
	DroneRecord* newVal = new DroneRecord();
	*newVal = value;
	newVal->next = addressPtr;
	newVal->prev = addressPtr->prev;
	newVal->prev->next = newVal;
	newVal->next->prev = newVal;
	size++;
	return true;
}

bool DronesManager::insert_front(DroneRecord value) {
    if (size == 0){
        DroneRecord* newVal = new DroneRecord();
        *newVal = value;
        first = newVal;
        first->next = NULL;
        first->prev = NULL;
        last = newVal;
        size++;
        return true;
    }

    DroneRecord* newVal = new DroneRecord();
    *newVal = value;
	newVal->next = first;
	newVal->prev = NULL;
	newVal->next->prev = newVal;
	first = newVal;
    size++;
    return true;
}

bool DronesManager::insert_back(DroneRecord value) {
    if (size == 0){
        DroneRecord* newVal = new DroneRecord();
        *newVal = value;
        first = newVal;
        first->next = NULL;
        first->prev = NULL;
        last = newVal;
        size++;
        return true;
    }

    DroneRecord* newVal = new DroneRecord();
    *newVal = value;
    newVal->next = NULL;
    newVal->prev = last;
    newVal->prev->next = newVal;
    last = newVal;
    size++;
    return true;
}

bool DronesManager::remove(unsigned int index) {
    if (size == 0){
        return false;
    }
    if (index > size-1){
        return false;
    }
    if (index == 0){
        return remove_front();
    }
    if (index == size-1){
        return remove_back();
    }
    if (size == 1){
        delete first;
        first = NULL;
        last = NULL;
        size--;
        return true;
    }
    unsigned int iterIndex = 0;
    DroneRecord* addressPtr = first;
    while (iterIndex < index){
        addressPtr = addressPtr->next;
        iterIndex++;
    }

    addressPtr->next->prev = addressPtr->prev;
    addressPtr->prev->next = addressPtr->next;
    delete addressPtr;
    size--;
	return true;
}

bool DronesManager::remove_front() {
    if (size == 0){
        return false;
    }
    if (size == 1){
        delete first;
        first = NULL;
        last = NULL;
        size--;
        return true;
    }

    first = first->next;
    delete first->prev;
    first->prev = NULL;
    size--;
    return true;
}

bool DronesManager::remove_back() {
    if (size == 0){
        return false;
    }
    if (size == 1){
        delete first;
        first = NULL;
        last = NULL;
        size--;
        return true;
    }

    last = last->prev;
    delete last->next;
    last->next = NULL;
    size--;
    return true;

}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    remove(index);
    insert(value,index);
    return true;
}

bool DronesManager::reverse_list() {

    int iterIndex = 1;
    DroneRecord* addressPtr = first ->next;
    DroneRecord* temp;
    temp = first;
    first = last;
    last = temp;
    first->prev = NULL;
    last->next = NULL;
    while (iterIndex < size-1){
        temp = addressPtr->next;
        addressPtr->next = addressPtr->prev;
        addressPtr->prev = temp;
        if (iterIndex == size - 2){
            first->next = addressPtr;
        }
        if (iterIndex == 1){
            last->prev = addressPtr;
        }
        addressPtr = addressPtr->next;
        iterIndex++;
    }
	return true;
}

bool DronesManagerSorted::is_sorted_asc() const {
	bool sorted = true;
	int current = 0;
	DroneRecord* addressPtr = first;
	while (current < size - 1){
	    if (addressPtr->droneID > addressPtr->next->droneID){
	        sorted = false;
	    }
	    current++;
	    addressPtr = addressPtr->next;
	}
    return sorted;
}

bool DronesManagerSorted::is_sorted_desc() const {

    bool sorted = true;
    int current = 0;
    DroneRecord* addressPtr = first;
    while (current < size - 2){
        if (addressPtr->droneID < addressPtr->next->droneID){
            sorted = false;
        }
        current++;
        addressPtr = addressPtr->next;
    }
    return sorted;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
	if (!is_sorted_asc()) {
        return false;
    }
    DroneRecord* addressPtr = first;
	unsigned int index = 0;
	while (addressPtr->droneID < val.droneID){
	    addressPtr = addressPtr->next;
	    index++;
	}
    return insert(val, index);
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
    if (!is_sorted_desc()) {
        return false;
    }
    DroneRecord* addressPtr = first;
    unsigned int index = 0;
    while (addressPtr->droneID > val.droneID){
        addressPtr = addressPtr->next;
        index++;
    }
    return insert(val, index);

}

void DronesManagerSorted::sort_asc() {
    for (int i = 0; i < size; ++i) {
        DroneRecord* iterate = first;
        for (int j = 0; j < size-1; j++) {
            if (iterate->droneID > iterate->next->droneID){
                swapValues(iterate, iterate->next);
            }
            iterate = iterate->next;
        }
    }
}

void DronesManagerSorted::sort_desc() {
    for (int i = 0; i < size; ++i) {
        DroneRecord* iterate = first;
        for (int j = 0; j < size-1; j++) {
            if (iterate->droneID < iterate->next->droneID) {
                swapValues(iterate, iterate->next);
            }
            iterate = iterate->next;
        }
    }
}

void DronesManagerSorted::swapValues(DroneRecord* valOne, DroneRecord* valTwo){
    DroneRecord* temp = new DroneRecord();
    temp->droneID = valOne->droneID;
    temp->batteryType = valOne->batteryType;
    temp->description = valOne->description;
    temp->droneType = valOne->droneType;
    temp->manufacturer = valOne->manufacturer;
    temp->range = valOne->range;
    temp->yearBought = valOne->yearBought;
    valOne->droneID = valTwo->droneID;
    valOne->batteryType = valTwo->batteryType;
    valOne->description = valTwo->description;
    valOne->droneType = valTwo->droneType;
    valOne->manufacturer = valTwo->manufacturer;
    valOne->range = valTwo->range;
    valOne->yearBought = valTwo->yearBought;
    valTwo->droneID = temp->droneID;
    valTwo->batteryType = temp->batteryType;
    valTwo->description = temp->description;
    valTwo->droneType = temp->droneType;
    valTwo->manufacturer = temp->manufacturer;
    valTwo->range = temp->range;
    valTwo->yearBought = temp->yearBought;
    delete temp;
    temp = NULL;
}
