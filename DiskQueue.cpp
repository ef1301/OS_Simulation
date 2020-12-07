#include "Cylinders.cpp"

class DiskQueue {
  public:
  DiskQueue(int disk): disk_num(disk), head(0){}

  void insert(int PID, std::list<int> input) {
    Cylinders c(input);
    std::pair<int, Cylinders> p(PID,c);
    dqueue.push_back(p);
  }

  bool noCylinders() {
    if(dqueue.front().second.isEmpty()) {
      return true;
    } else {
      return false;
    }
  }

  bool isEmpty() {
    return dqueue.empty();
  }

  int getPID() {
    return dqueue.front().first;
  }

  void readHead() {
    dqueue.front().second.read(head); //head is removed/"read"
    nextHead(); //update the head
  }

  void nextHead() {
    int cylinder = dqueue.front().second.nextHead(head);
    if(cylinder != -1) { //exists cylinders to read
      head = cylinder;
    } else {
    }
  }

  void removeFront() {
    dqueue.pop_front();
  }

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
  int head;
  std::list<std::pair<int, Cylinders>> dqueue;
};
