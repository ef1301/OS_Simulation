/*
  Name: Emily Fang
  Contains DiskQueue class for storing pairs of <PID, Cylinders> in a list

  Private Member:
  - int disk_num
  - int head
  - std::list<std::pair<int, Cylinders>> dqueue

  Public Function:
  - <constructor>
  - void insert(int PID, std::list<int> input)
  - bool noCylinders()
  - bool isEmpty()
  - int getPID()
  - void readHead()
  - void nextHead()
  - void removeFront()
  - void print()
*/

#include "Cylinders.cpp"

class DiskQueue {
  public:
  /*
    Constructor
  */
  DiskQueue(int disk): disk_num(disk), head(0){}

  /*
    Inserts a process (from the pqueue) to read a list of cylinders
  */
  void insert(int PID, std::list<int> input) {
    Cylinders c(input);
    std::pair<int, Cylinders> p(PID,c);
    dqueue.push_back(p);
  }

  /*
    Checks if first process on the queue has no cylinders to read
  */
  bool noCylinders() {
    return dqueue.front().second.isEmpty();
  }

  /*
    Checks if there are no processes left on dqueue
  */
  bool isEmpty() {
    return dqueue.empty();
  }

  /*
    Returns the PID of the first process in queue
  */
  int getPID() {
    return dqueue.front().first;
  }

  /*
    Reads the cylinder matching the head position
    Set new head
  */
  void readHead() {
    if(dqueue.empty() == false) {
      dqueue.front().second.read(head); //head is removed/"read"
      nextHead(); //update the head
    } else {
    }
  }

  /*
    Calls helper function to look for the next possible head position
    Using SSTF
  */
  void nextHead() {
    int cylinder = dqueue.front().second.nextHead(head);
    if(cylinder != -1) { //exists cylinders to read
      head = cylinder;
    } else {
    }
  }

  /*
    Remove the first process on the dqueue
  */
  void removeFront() {
    dqueue.pop_front();
  }

  /*
    Print statement to print process and its cylinders
  */
  void print() {
    std::cout << "Hard Disk #: " << disk_num << " - Head Position: " << head << std::endl;
    std::list<std::pair<int, Cylinders>>::iterator it;
    for(it = dqueue.begin(); it != dqueue.end(); it++) {
      std::cout << "PID " << (*it).first << " requesting cylinder(s): ";
      (*it).second.print();
    }
  }

  private:
  int disk_num;
  int head; //current head position
  std::list<std::pair<int, Cylinders>> dqueue; // <PID, Cylinders>
};
