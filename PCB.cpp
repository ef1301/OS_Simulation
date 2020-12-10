/*
  Name: Emily Fang
  Contains PCB struct for representing and impementing a Process Block (PID, priority, size, memory range)
 */
#include <utility>
#include <iostream>

//PROCESS STRUCT
struct PCB {
  int PID;
  int priority_level;
  unsigned long int size;
  std::pair<unsigned long int, unsigned long int> memory_occupied;

  //Constructor
  PCB(int p, int pl, std::pair<unsigned long int, unsigned long int> mo) :
    PID(p),
    priority_level(pl),
    size(mo.second - mo.first + 1),
    memory_occupied(mo){}

  //Destructor
  ~PCB() {}

  // Prints PCB Information
  void print() {
    std::cout << PID << " " <<  priority_level << " " << memory_occupied.first << " " << memory_occupied.second << std::endl;
  }

  //PCB loses its PID and priority but retains information on the empty space
  void freePCB() {
    PID = 0;
    priority_level = -1;
  }

  /*
    Merges the memory space between two PCBs by changing the range to cover the extend of both PCBs
    So one can be removed
  */
  void mergeEmptyPCB(unsigned long int start, unsigned long int end) {
    memory_occupied.first = start;
    memory_occupied.second = end;
  }

  /*
    Changes PCB information
    For creating new processes to either:
     - Take up the whole space range
     - Take up a portion
   */
  void reusePCB(int _pid, int priority, unsigned long int start, unsigned long int end) {
    PID = _pid;
    priority_level = priority;
    size = end - start +1;
    memory_occupied.first = start;
    memory_occupied.second = end;
  }
};
