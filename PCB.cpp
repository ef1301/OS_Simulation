#include <utility>
#include <iostream>

//PROCESS STRUCT
struct PCB {
  int PID;
  int priority_level;
  unsigned long int size;
  std::pair<unsigned long int, unsigned long int> memory_occupied;

  PCB(int p, int pl, std::pair<unsigned long int, unsigned long int> mo) :
    PID(p),
    priority_level(pl),
    size(mo.second - mo.first + 1),
    memory_occupied(mo){}

  ~PCB() {

  }

  void print() {
    std::cout << PID << " " <<  priority_level << " " << memory_occupied.first << " " << memory_occupied.second << std::endl;
  }

  void freePCB() {
    PID = 0;
    priority_level = -1;
  }

  void mergeEmptyPCB(unsigned long int start, unsigned long int end) {
    memory_occupied.first = start;
    memory_occupied.second = end;
  }

  void reusePCB(int _pid, int priority, unsigned long int start, unsigned long int end) {
    PID = _pid;
    priority_level = priority;
    size = end - start +1;
    memory_occupied.first = start;
    memory_occupied.second = end;
  }
};
