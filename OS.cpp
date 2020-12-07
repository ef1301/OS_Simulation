#include "RAM.cpp"
#include "DiskQueue.cpp"
#include <iterator>
#include <map>
#include <vector>

/*
  Returns true if the first pair has a high priority
  Returns false if the second pair has a higher priority
  Helper input function to the list sort function
*/
bool compare_priority(const std::pair<int,int>& first, const std::pair<int,int>& second) {
  if(first.second > second.second) {
    return true;
  } else {
    return false;
  }
}

class OperatingSystem {
  public:
  /*
   Constructor with RAM and hard_disk inputs
  */
  OperatingSystem (unsigned long int input_RAM, int input_hard_disks):
    RAM_MEM(input_RAM),
    number_of_hard_disks(input_hard_disks)
  {
    std::pair<int, int> p(0,-1);
    ready_queue.push_back(p);
    for(int i = 0; i < input_hard_disks; i++) {
      DiskQueue disk(i);
      disk_queue.push_back(disk);
    }
  };

  /*
    Create a new process (RAM_MEM.CreateNewProcess)
    Adds it to the ready queue or it adds it to the CPU if it is empty (AddToReadyQueue)
    Sort the priority queue (highest priority to lowest priority)
  */
  void CreateProcess(int input_priority, unsigned long int size) {
    RAM_MEM.CreateNewProcess(input_priority, size);
    int latest_process = RAM_MEM.GetCount();
    AddToReadyQueue(latest_process, input_priority);
    SortQueue();
  }

  /*
    Terminates the current process running on the CPU
    First/front of RAM_MEM (RAM Memory)
  */
  void TerminateCurrentProcess() {
    int current_process = ready_queue.front().first;
    if(ready_queue.empty() == false && current_process > 0) {
      std::cout << "To be terminated: P" << current_process << std::endl;
      RAM_MEM.TerminatePCB(current_process);
      GetNextFromReadyQueue();
    }
    else {
      std::cout << "ERROR: There is no process to terminate.\n";
    }
  }

  void newDiskRead(int disk_num, std::list<int> input) {
    if(ready_queue.empty()) { // cannot do a disk read b/c no process to append to dqueue
      std::cout << "ERROR: No processes to read current cylinder input.\n";
    } else { //take first from pqueue and append to dqueue
      int PID = ready_queue.front().first;
      if(PID != 0) {
        disk_queue[disk_num].insert(PID, input);
        disk_queue[disk_num].nextHead();
        ready_queue.pop_front();
      } else {
        std::cout << "ERROR: No processes in priority queue to read current cylinder input.\n";
      }
    }
  }

  void readCylinder(int disk_num) {
    if(disk_queue[disk_num].isEmpty() == false) { //No Processes on dqueue
      if(disk_queue[disk_num].noCylinders() == true) { //if no cylinders to read, add back to pqueue
        int PID = disk_queue[disk_num].getPID();
        int priority_level = RAM_MEM.FindPriority(PID);
        if(priority_level != -1){
          AddToReadyQueue(PID, priority_level);
          disk_queue[disk_num].removeFront();
        } else {
          std::cout << "ERROR: Cannot find procss with PID " << PID << ".\n";
        }
      } else {
        disk_queue[disk_num].readHead();
      }
    } else {
      std::cout << "ERROR: No cylinders to read from Disk " << disk_num << ".\n";
    }
  }

  //PRINT FUNCTIONS
  void print() {
    std::cout << "RAM MEMORY:" << std::endl;
    RAM_MEM.print();
  }

  void PrintCurrent() { //S r command
    if(ready_queue.front().first > 0) {
      std::cout << "CPU (Current Process): P" << ready_queue.front().first << std::endl;
    } else {
      std::cout << "CPU (Current Process):" << std::endl;
    }
    std::cout << "Common queue: " << std::endl;
    std::list<std::pair<int,int>>::iterator it = ready_queue.begin();
    it++;
    while(it != ready_queue.end()) {
      std::cout << "P" << (*it).first << " ";
      it++;
    }
    //print();
  }

  void PrintDisks() { //S i command
    std::vector<DiskQueue>::iterator it;
    for(it = disk_queue.begin(); it != disk_queue.end(); it++) {
      (*it).print();
      std::cout << "\n";
    }
  }

  void PrintMEM() { //S m command
    std::cout << std::endl;
    RAM_MEM.PrintMemory();
  }

  //========================================================================================================>

  private:
  RAM RAM_MEM; //RAM
  int number_of_hard_disks; //# of hard disks
  std::list<std::pair<int,int>> ready_queue; //<PID, priority_level>
  std::vector<DiskQueue> disk_queue; // <PID, HardDisk>

  /*
    Sorts processes in ready_queue from highest priority to lowest priority
  */
  void SortQueue() {
    ready_queue.sort(compare_priority);
  }

  /*
    If ready_queue is empty, push_back a blank/dummy process
    Else, pop_front and front should be the next highest priority process
   */
  void GetNextFromReadyQueue() {
    if(ready_queue.empty()) {
      ready_queue.push_back(std::make_pair(0,-1));
    }
    else {
      ready_queue.pop_front();
    }
  }

  /*
    Adds a process of some pid to the ready queue or it goes to the CPU if it is currently idle
  */
  void AddToReadyQueue(const int PID, const int input_priority) {
    if(ready_queue.front().first == 0) {
      ready_queue.pop_front();
    }
    ready_queue.push_back(std::make_pair(PID, input_priority));
    //SortQueue();
  };
};
