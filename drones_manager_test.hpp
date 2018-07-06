// Andrew Mouchantaf 20708318
// Gerry Saporito 20715429
#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// new empty list is valid
    bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
    }

	// insert_front() and insert_back() on zero-element list
    bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)

        ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))
	    return true;
    }

	// select() and search() work properly
    bool test3() {
	    DronesManager manager1;
        DronesManager::DroneRecord droneOne(100);
        DronesManager::DroneRecord droneTwo(200);
        DronesManager::DroneRecord droneThree(50);
	    manager1.insert_front(droneOne);
	    manager1.insert_front(droneTwo);
        manager1.insert_front(droneThree);
        ASSERT_TRUE(manager1.search(droneOne) == 2);
        ASSERT_TRUE(manager1.search(droneTwo) == 1);
        ASSERT_TRUE(manager1.search(droneThree) == 0);
        ASSERT_TRUE(manager1.select(0) == droneThree);
        ASSERT_TRUE(manager1.select(1) == droneTwo);
        ASSERT_TRUE(manager1.select(2) == droneOne);
        return true;
    }
    
    // remove_front() and remove_back() on one-element list
    bool test4() {
        DronesManager manager1,manager2;
        DronesManager::DroneRecord droneOne(100);
        DronesManager::DroneRecord droneTwo(200);
        manager1.insert_front(droneOne);
        manager2.insert_front(droneTwo);
        manager1.remove_front();
        manager2.remove_back();
        ASSERT_TRUE(manager1.get_size() ==  0 && manager2.get_size() == 0);
        ASSERT_TRUE(manager1.first == NULL && manager1.last == NULL)
        ASSERT_TRUE(manager2.first == NULL && manager2.last == NULL)
        return true;
    }
    
    // replace() and reverse_list() work properly
    bool test5() {
	    DronesManager manager1;
        DronesManager::DroneRecord droneOne(100);
        DronesManager::DroneRecord droneTwo(200);
        DronesManager::DroneRecord droneThree(50);
        DronesManager::DroneRecord droneFour(500);
        manager1.insert_front(droneOne);
        manager1.insert_back(droneTwo);
        manager1.insert_back(droneThree);
        manager1.replace(0, droneFour);
        manager1.reverse_list();
        ASSERT_TRUE(manager1.search(droneFour) == 2);
        ASSERT_TRUE(manager1.search(droneTwo) == 1);
        ASSERT_TRUE(manager1.search(droneThree) == 0);
        ASSERT_TRUE(manager1.select(0) == droneThree);
        ASSERT_TRUE(manager1.select(1) == droneTwo);
        ASSERT_TRUE(manager1.select(2) == droneFour);
        return true;

    }
    
    // insert_front() keeps moving elements forward
    bool test6() {
        DronesManager manager1;
        DronesManager::DroneRecord droneOne(100);
        DronesManager::DroneRecord droneTwo(200);
        DronesManager::DroneRecord droneThree(50);
        DronesManager::DroneRecord droneFour(500);
        manager1.insert_front(droneOne);
        manager1.insert_front(droneTwo);
        manager1.insert_front(droneThree);
        manager1.insert_front(droneFour);
        ASSERT_TRUE(manager1.search(droneFour) == 0);
        ASSERT_TRUE(manager1.search(droneThree) == 1);
        ASSERT_TRUE(manager1.search(droneTwo) == 2);
        ASSERT_TRUE(manager1.search(droneOne) == 3);
        ASSERT_TRUE(manager1.select(0) == droneFour);
        ASSERT_TRUE(manager1.select(1) == droneThree);
        ASSERT_TRUE(manager1.select(2) == droneTwo);
        ASSERT_TRUE(manager1.select(3) == droneOne);
        return true;
    }
    
    // inserting at different positions in the list
    bool test7() {
	    DronesManager manager1;
        DronesManager::DroneRecord droneOne(100);
        DronesManager::DroneRecord droneTwo(200);
        DronesManager::DroneRecord droneThree(50);
        DronesManager::DroneRecord droneFour(500);
        manager1.insert(droneOne, 0);
        manager1.insert(droneTwo, 2);
        manager1.insert(droneThree, 1);
        manager1.insert(droneFour, 7);
        ASSERT_TRUE(manager1.get_size() == 2);
        ASSERT_TRUE(manager1.select(0) == droneOne);
        ASSERT_TRUE(manager1.select(1) == droneThree);
 	    return true;
    }
    
    // try to remove too many elements, then add a few elements
    bool test8() {
        DronesManager manager1;
        DronesManager::DroneRecord droneOne(100);
        DronesManager::DroneRecord droneTwo(200);
        DronesManager::DroneRecord droneThree(50);
        DronesManager::DroneRecord droneFour(500);
        manager1.insert(droneOne, 0);
        manager1.remove_front();
        manager1.remove_front();
        manager1.remove_front();
        manager1.insert(droneTwo, 0);
        manager1.insert(droneThree, 1);
        manager1.insert(droneFour, 2);
        ASSERT_TRUE(manager1.get_size() == 3);
        ASSERT_TRUE(manager1.select(0) == droneTwo);
        ASSERT_TRUE(manager1.select(1) == droneThree);
        ASSERT_TRUE(manager1.select(2) == droneFour);
        return true;
    }
    
 	// lots of inserts and deletes, some of them invalid
	bool test9() {DronesManager manager1;
        DronesManager::DroneRecord droneOne(100);
        DronesManager::DroneRecord droneTwo(200);
        DronesManager::DroneRecord droneThree(50);
        DronesManager::DroneRecord droneFour(500);
        DronesManager::DroneRecord droneFive(700);
        DronesManager::DroneRecord droneSix(12);
        DronesManager::DroneRecord droneSeven(220);
        DronesManager::DroneRecord droneEight(110);
        manager1.insert_front(droneOne); //valid
        manager1.insert(droneTwo, 9); //invalid
        manager1.remove_front(); //valid
        manager1.remove(12); //invalid
        manager1.insert_front(droneTwo); //valid
        manager1.insert(droneThree, 1); //valid
        manager1.insert_front(droneFour); //valid
        manager1.insert_back(droneFive); //valid
        manager1.remove(3); //valid
        manager1.remove(7); //invalid
        manager1.insert(droneSix, 18); //invalid
        manager1.insert(droneSeven, 1); //valid
        manager1.insert_back(droneEight); // valid
        manager1.remove_back(); //valid
        ASSERT_TRUE(manager1.get_size() == 4);
        ASSERT_TRUE(manager1.select(0) == droneFour);
        ASSERT_TRUE(manager1.select(1) == droneSeven);
        ASSERT_TRUE(manager1.select(2) == droneTwo);
        ASSERT_TRUE(manager1.select(3) == droneThree);
        return true;
	}    
	    	
		// inserts into an unsorted list, then sort the list
	bool test10() {
	    DronesManagerSorted manager1;
	    DronesManager::DroneRecord droneOne(100);
        DronesManager::DroneRecord droneTwo(200);
        DronesManager::DroneRecord droneThree(50);
        manager1.insert_front(droneOne);
        manager1.insert_front(droneTwo);
        manager1.insert_front(droneThree);
        manager1.sort_asc();
        ASSERT_TRUE(manager1.select(0) == droneThree);
        ASSERT_TRUE(manager1.select(1) == droneOne);
        ASSERT_TRUE(manager1.select(2) == droneTwo);
	    return true;
	}  
	
	// insert and remove into sorted manager in ascending order
	bool test11() {
	    DronesManagerSorted manager1;
        DronesManager::DroneRecord droneOne(100);
        DronesManager::DroneRecord droneTwo(200);
        DronesManager::DroneRecord droneThree(50);
        DronesManager::DroneRecord droneFour(500);
        DronesManager::DroneRecord droneFive(300);
        DronesManager::DroneRecord droneSix(150);
        manager1.insert_front(droneOne);
        manager1.insert_front(droneTwo);
        manager1.insert_front(droneThree);
        manager1.insert_front(droneFour);
        manager1.sort_asc();
        manager1.insert_sorted_asc(droneFive);
        manager1.insert_sorted_asc(droneSix);
        ASSERT_TRUE(manager1.select(0) == droneThree);
        ASSERT_TRUE(manager1.select(1) == droneOne);
        ASSERT_TRUE(manager1.select(2) == droneSix);
        ASSERT_TRUE(manager1.select(3) == droneTwo);
        ASSERT_TRUE(manager1.select(4) == droneFive);
        ASSERT_TRUE(manager1.select(5) == droneFour);
        return true;
	}
	
	  //insert and remove into sorted manager in descending order
	bool test12() {
          DronesManagerSorted manager1;
          DronesManager::DroneRecord droneOne(100);
          DronesManager::DroneRecord droneTwo(200);
          DronesManager::DroneRecord droneThree(50);
          DronesManager::DroneRecord droneFour(500);
          DronesManager::DroneRecord droneFive(300);
          DronesManager::DroneRecord droneSix(150);
          manager1.insert_front(droneOne);
          manager1.insert_front(droneTwo);
          manager1.insert_front(droneThree);
          manager1.insert_front(droneFour);
          manager1.sort_desc();
          manager1.insert_sorted_desc(droneFive);
          manager1.insert_sorted_desc(droneSix);
          ASSERT_TRUE(manager1.select(0) == droneFour);
          ASSERT_TRUE(manager1.select(1) == droneFive);
          ASSERT_TRUE(manager1.select(2) == droneTwo);
          ASSERT_TRUE(manager1.select(3) == droneSix);
          ASSERT_TRUE(manager1.select(4) == droneOne);
          ASSERT_TRUE(manager1.select(5) == droneThree);
          return true;
	}  
};


#endif
