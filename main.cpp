#include "OS.cpp"
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo> // for testing

bool is_number(const std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int main() {
  bool simulation_start = true;
  unsigned long int RAM = 0;
  int hard_disks = 0;
  while(simulation_start) {
    while(RAM <= 0 || RAM > 4000000000) {
      std::cout << "How much RAM memory is there on the simulated computer? (in bytes)" << std::endl;
      std::cout << "Please enter a integer between 0 and 4000000000 only:" << std::endl;
      std::cout << " > ";
      std::cin >> RAM;
      if(std::cin.fail()) {
        std::cin.clear(); //This corrects the stream.
        std::cin.ignore(); //This skips the left over stream data.
        std::cout << "====================================\nERROR: Please enter a integer between 0 and 4000000000 only." << std::endl;
      }
    }
    while(hard_disks <= 0) {
      std::cout << "How many hard disks does the simulated computer have?" << std::endl;
      std::cout << "Please enter a positive integer:" << std::endl;
      std::cout << " > ";
      std::cin >> hard_disks;
      if(std::cin.fail()) {
        std::cin.clear(); //This corrects the stream.
        std::cin.ignore(); //This skips the left over stream data.
        std::cout << "====================================//\nERROR: Please enter a positive integer only." << std::endl;
      }
    }
    simulation_start = false;
  }
  std::cout << "RAM = " << RAM << std::endl;
  std::cout << "hard disks = " << hard_disks << std::endl;
  std::cout << "\n====================================\nEnter a command: " << std::endl;
  std::cout << " > ";
  std::string input;
  OperatingSystem current_OS(RAM, hard_disks);
  while(getline(std::cin, input)) {
    std::istringstream ss(input);
    std::string command;
    ss >> command;
    /*
      NEW PROCESS COMMAND ------------------------------------------------------------------------
    */
    if(command == "A") {
      std::string data;
      int priority = 0;
      unsigned long int size = 0;
      if(ss >> data && is_number(data)) {
        priority = std::stoi(data, nullptr, 0);
        if(ss >> data && is_number(data)) {
          size = std::stoul(data, nullptr, 0);
          if (ss >> data) {
            std::cout << "====================================\nERROR: Unexpected input(s). Please try again. \nEnter a command: " << std::endl;
            std::cout << "Please follow the following syntax:\nA <priority_level> <size>" << std::endl;
            std::cout << "Enter a command: " << std::endl;
            std::cout << " > ";
          }
          else if(size > 0) {
            current_OS.CreateProcess(priority, size);
            //current_OS.print();
            std::cout << "\n====================================\nEnter a command: " << std::endl;
            std::cout << " > ";
          } else {
            std::cout << "====================================\nERROR: Input a size greater than 0. \nEnter a command: " << std::endl;
            std::cout << "Enter a command: " << std::endl;
            std::cout << " > ";
          }
        } else {
          std::cout << "====================================\nERROR: Unexpected input type. Please enter a numeric value. \nEnter a command: " << std::endl;
          std::cout << "Please follow the following syntax:\nA <priority_level> <size>" << std::endl;
          std::cout << "Enter a command: " << std::endl;
          std::cout << " > ";
        }
      } else {
          std::cout << "====================================\nERROR: Unexpected input type. Please enter a numeric value." << std::endl;
          std::cout << "Please follow the following syntax:\nA <priority_level> <size>" << std::endl;
          std::cout << "Enter a command: " << std::endl;
          std::cout << " > ";
      }
    }

    /*
      TERMINATE CURRENT PROCESS COMMAND -------------------------------------------------------------------
     */
    else if(command == "t") {
      current_OS.TerminateCurrentProcess();
      std::cout << "\n====================================\nEnter a command: " << std::endl;
      std::cout << " > ";
    }

    /*
      DISK COMMAND ------------------------------------------------------------------------
    */
    else if(command == "d") {
      std::string input;
      int disk_num = 0;
      std::list<int> cylinders;
      bool error_caught = false;
      if(ss >> input && is_number(input)) {
        disk_num = std::stoi(input);
        if(disk_num > hard_disks) {
          std::cout << "ERROR: Disk " << input << " does not exist on the current OS.\n";
        } else {
          while(ss >> input) {
            if(is_number(input)) {
              cylinders.push_back(std::stoi(input));
            } else {
              error_caught = true;
              break;
            }
          }
          if(error_caught == false) {
            current_OS.newDiskRead(disk_num, cylinders);
          } else {
            std::cout << "ERROR: One or more cylinder inputs were not numbers. Please enter numeric values.\n";
          }
        }
      } else {
        std::cout << "ERROR: Please enter a numeric value for the disk number.\n";
      }
      std::cout << "\n====================================\nEnter a command: \n";
      std::cout << " > ";
    }

    else if(command == "D") {
      std::string input;
      ss >> input;
      if(is_number(input) == true) {
        if(std::stoi(input) > hard_disks) {
          std::cout << "ERROR: Disk " << input << " does not exist on the current OS.\n";
        } else {
          current_OS.readCylinder(std::stoi(input));
        }
      } else {
        std::cout << "ERROR: Please enter a numeric value for the disk number.\n";
      }
      std::cout << "\n====================================\nEnter a command: \n";
      std::cout << " > ";
    }

    /*
      SUMMARY COMMANDS ------------------------------------------------------------------------
     */
    else if(command == "S") {
      std::string subcommand;
      std::string excess;
      ss >> subcommand;
      if(subcommand == "r" || subcommand == "i" || subcommand == "m") {
        if(ss >> excess) {
          std::cout << "====================================\nERROR: Unexpected input(s). Please try again." << std::endl;
          //SYNTAX GUIDELINES MESSAGE UPON SUMMARY COMMAND ERROR
          std::cout << "Please follow the following syntax:\n S <summary_type>" << std::endl;
          std::cout << "S r = Shows what process is currently using the CPU and what processes are waiting in the ready-queue.\n";
          std::cout << "S i = Shows what processes are currently using the hard disks and what processes are waiting to use them. For each busy hard disk show the process that uses it and show its I/O-queue. The enumeration of hard disks starts from 0.\n";
          std::cout << "S m = Shows the state of memory. Show the range of memory addresses used by each process in the system.\n";
        }
        else if(subcommand == "r") {
          current_OS.PrintCurrent();
          std::cout << "\n====================================\nEnter a command: \n";
          std::cout << " > ";
        }
        else if(subcommand == "i") {
          current_OS.PrintDisks();
          std::cout << "\n====================================\nEnter a command: \n";
          std::cout << " > ";
        }
        else if(subcommand == "m") {
          current_OS.PrintMEM();
          std::cout << "\n====================================\nEnter a command: \n";
          std::cout << " > ";
        }
      }
      else { //NO MATCHING SUMMARY COMMAND
        std::cout << "\n====================================\nERROR: Unkwown comamnd.\n";
        std::cout << "\n====================================\nEnter a command: \n";
        std::cout << " > ";
      }
    }
  }

  return 0;
}
