/*
  Name: Emily Fang
  Contains RAM class for storing PCBs

  Private Members:
  - std::list<PCB*> memory
  - unsigned long int size
  - int process_count

  Public Functions:
  - <constructor>
  - int GetCount()
  - void print()
  - void PrintMemory()
  - int FindPriority(int PID)
  - void CreateNewProcess(int priority, unsigned long int size)
  - void TerminatePCB(int PID)
 */

#include "PCB.cpp"
#include <list>

//RAM - stores PCB's in memory
class RAM {
  public:
  RAM(unsigned long int _size):
    process_count(0),
    size(_size) {
    PCB* first_block = new PCB(0, -1, std::make_pair<unsigned long int, unsigned long int>(0, _size -1));
    memory.push_back(first_block);
  }

  int GetCount() {
    return CurrentProcessCount();
  }

  void print() {
    std::list<PCB*>::iterator it = memory.begin();
    while(it != memory.end()) {
      std::cout << (*it)->PID << " " << (*it)->priority_level << " " << (*it)->memory_occupied.first << " " << (*it)->memory_occupied.second << std::endl;
      it++;
    }
    std::cout << std::endl;
  }

  void PrintMemory() {
    std::list<PCB*>::iterator it = memory.begin();
    while(it != memory.end()) {
      if((*it)->PID != 0) {
        std::cout << "Process Number: " << (*it)->PID << std::endl;
        std::cout << "Process Number: " << (*it)->memory_occupied.first << " - " << (*it)->memory_occupied.second << std::endl;
        it++;
      } else {
        it++;
      }
    }
  }

  int FindPriority(int PID) {
    std::list<PCB*>::iterator it = memory.begin();
    while(it != memory.end()) {
      if((*it)->PID == PID) {
        return (*it)->priority_level;
      }
      it++;
    }
    return -1;
  }

  void CreateNewProcess(int priority, unsigned long int size) {
    std::list<PCB*>::iterator it = memory.begin();
    while(it != memory.end()) {
      if((*it)->PID == 0) {
        unsigned long int s = (*it)->size;
        if(s == size) { //fits exactly, change pid and priority level
          process_count++;
          (*it)->PID = process_count;
          (*it)->priority_level = priority;
          break;
        }
        else if (s > size) { // doesn't fit exactly, change existing one to hold new process and insert leftover space
            unsigned long int start = (*it)->memory_occupied.first;
            unsigned long int end = start + size - 1;
            std::pair<unsigned long int, unsigned long int> empty_PCB_mem;
            empty_PCB_mem = std::make_pair(start + size, (*it)->memory_occupied.second);
            PCB* empty_PCB_ptr = new PCB(0, -1, empty_PCB_mem);
            process_count++;
            (*it)->reusePCB(process_count, priority, start, end);
            memory.push_back(empty_PCB_ptr);
            //print();
            break;
        } else {
          ++it;
        }
      }
      else {
        ++it;
      }
    }
  }

  void TerminatePCB(int PID) {
    std::list<PCB*>::iterator it = memory.begin();
    while(it != memory.end()) {
      if((*it)->PID == PID) {
        (*it)->PID = 0;
        (*it)->priority_level = -1;
        break;
      }
      it++;
    }
    MergeEmptyPCB();
  }

  private:
  std::list<PCB*> memory;
  unsigned long int size;
  int process_count;

  int CurrentProcessCount() {
    return process_count;
  }

  void Reduce(std::list<PCB*>::iterator it) {
    while(it != memory.end()) {
      std::list<PCB*>::iterator next = it++;
      if(next != memory.end()) {
        (*next)->reusePCB((*it)->PID, (*it)->priority_level, (*it)->memory_occupied.first, (*it)->memory_occupied.second);
      }
      it++;
    }
  }

  void MergeEmptyPCB() {
    std::list<PCB*>::iterator it = memory.begin();
    std::list<PCB*>::iterator next = it++;
    bool merged = false;
    while(it != memory.end()) {
      if((*it)->PID == 0) { //empty slot
        if(next != memory.end()) {
          if((*next)->PID == 0) {
            /*std::cout << "it" << std::endl;
            (*it)->print();
            std::cout << "next" << std::endl;
            (*next)->print();*/
            (*it)->mergeEmptyPCB((*next)->memory_occupied.first, (*it)->memory_occupied.second);
            //memory.erase(next);
            merged = true;
            break;
          } else {
            it++;
            next++;
          }
        } else {
          break;
        }
      } else {
        it++;
        next++;
      }
      }
    if(merged) {
      //std::cout << "MERGED\n";
      (*it)->print();
      if(next != memory.end()) {
        Reduce(next);
        memory.pop_front();
      }
    }
  }
};
