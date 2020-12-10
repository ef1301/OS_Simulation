/*
  Name: Emily Fang
  Contains Cylinders class for storing cylinders to be read

  Private Members:
  - std::list<int> cylinders

  Public Functions:
  - <constructor>
  - <destructor>
  - std::list<int>::iterator findCylinder(int value)
  - void read(int head)
  - std::list<int>::iterator end()
  - int nextHead(int head)
  - bool isEmpty()
  - void print()
 */
#include <list>
#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>

bool compare_cylinder(const int first, const int second) {
  if(first < second) return true;
  else return false;
}

// Cylinders are organized in the same order in which they were inputted
class Cylinders {
  public:
  /*
    Constructor
  */
  Cylinders(std::list<int> input): cylinders(input) {}

  /*
    Destructor
  */
  ~Cylinders() { cylinders.clear(); }


  /*
    Return iterator to requested cylinder if exists
    Else, return cylinder.end()
  */
  std::list<int>::iterator findCylinder(int value) {
    std::list<int>::iterator it = cylinders.begin();
    while(it != cylinders.end()) {
      if((*it) == value) {
        return it;
      }
      it++;
    }
    return cylinders.end();
  }

  /*
    If the head position exists in the list of cylinders, erase it.
    Else, throw error.
   */
  void read(int head) {
    std::list<int>::iterator it = findCylinder(head);
    if(it != cylinders.end()) {
      cylinders.erase(it);
    } else {
      std::cout << "ERROR: head does not exist." << std::endl;
    }
  }

  std::list<int>::iterator end() {
    return cylinders.end();
  }

  /*
    Check if the list of cylinders in not empty
   */
  int nextHead(int head) {
    std::list<int>::iterator closest;
    int difference = INT_MAX;
    if (cylinders.empty()) { // no more cylinders to read
      return -1;
    } else { // still are cylinders to read
      //find the cylinder that's closest to read
      for(std::list<int>::iterator it = cylinders.begin(); it != cylinders.end(); it++) {
        if(abs((*it) - head) < difference) {
          closest = it;
          difference = abs((*it) - head);
        }
      }
      return (*closest);
    }
  }

  /*
    Returns true if there are no cylinders to read
    otherwise, false
  */
  bool isEmpty() {
    return cylinders.empty();
  }

  /*
    Print statement
  */
  void print() {
    std::list<int>::iterator it;
    for(it = cylinders.begin(); it != cylinders.end(); it++) {
      std::cout << (*it) << " ";
    }
    std::cout << "\n";
  }

  private:
  std::list<int> cylinders; // cylinders retain the order that they were inserted
};
