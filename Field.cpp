//Name: Nabil Said
//email:nabil.said54@myhunter.cuny.edu
//Course: CSCI-135
//Instructor: Tong yi

#include "Field.hpp"
#include <iostream>
#include <cstdlib> //rand, srand
#include <ctime>

using namespace std;

Field::Field():Field(7, 2){
} //constructor
  

Field:: Field (int size, int num_mines) {
    if(size <= 3) {
        size = 7; 
    }

    if(num_mines < 2) {
        num_mines = 2; 
    }

    if(num_mines >= size) {
        num_mines = size/3;
    }

    this->num_mines = num_mines;
    this->size = size;

    cells = new int[size];
    checked = new bool[size];

    for(int i = 0; i < size; i++) {
        cells[i] = 0;
        checked[i] = false;
    }

    int count = 0;
    srand(time(0));

    while(count < num_mines) { //random placement
        int index = rand() % size;
        if(cells[index] == 0) {
            cells[index] = 1;
            count++;
        }
    }
} 


Field::~Field(){ //destructor
            delete[] cells;
            delete[] checked;
            cells = nullptr;
            checked = nullptr;
        }

string get_labels(int size) {
    string str;
    for (int i = 0; i < size; i++) { 
        str += "  ";
        if (i < 10)
           str += " " + std::to_string(i);
        else str += to_string(i);
        str += "  ";
    }
    str += "\n";
    return str;
}

string get_separate_line(int size) {
    string str = "+";
    for (int i = 0; i < size; i++)
        str += "-----+";
    str += "\n";
    return str;
}

string Field::to_string() const {
    string str = get_labels(size);
    str += get_separate_line(size);

    str += "|";
    for (int i = 0; i < size; i++) {
       if (cells[i] == 0) 
        {
           if (checked[i] == true)
               str += "  " + std::to_string(neighbor_mines(i)) +
                      "  |";
           else str += "     |";
        }
        else //must have a mine 
            str += "     |";

        //The above if-else can be simplified.
        //Idea: if a cell has no mine and is checked,
        //display its neighboring information,
        //otherwise, that is,
        //a cell has a mine or
        //it does not have a mine but is not checked yet,
        //do not display anything in that cell.
        //The code is as follows.

        //if (cells[i] == 0 && 
        //    checked[i] == true)
        //   str += "  " + std::to_string(neighbor_mines(i)) +
        //             "  |";
        //else str += "     |";
    }

    str += "\n";

    str += get_separate_line(size);

    return str;
}


string Field::answer_string() const {
    string str = get_labels(size); 
    str += get_separate_line(size);
    str += "|";
    for(int i = 0; i < size; i++) {
        if(cells[i] == 1) { // if cell element has a mine
            str += "  *  |"; // display asterisk
        }
        else { // cell element doesn't have a mine
            str += "  " + std::to_string(neighbor_mines(i)) + "  |"; // display neighboring info
        }
    }
    str += "\n";
    str += get_separate_line(size);
    return str;

}

string Field:: empty_layout_string() const {
    string str = get_labels(size); 
    str += get_separate_line(size);
    str += "|";
    for (int i = 0; i < size; i++) {
        str += "     |";
    }
    str += "\n";
    str += get_separate_line(size);
    return str;
}


int Field::get_size() const {
    return size;
}

int Field::get_num_mines() const {
    return num_mines;
}


int Field::neighbor_mines(int index) const {
    
    if(cells[index] == 1) { // if current index has mine
        return -1;
    }

    int count = 0;
    if(index > 0 && cells[index - 1] == 1) { // if left side has a mine and index within bound
        count++;
    }
    if(index + 1  < size  && cells[index + 1] == 1) { // if right side has a mine and index within bound
        count++;
    }

    return count;
}


void Field::mark_checked(int index){
            if(index >= 0 && index < size){
                checked[index] = true;
            }
        }


bool Field::is_checked(int index) const{
            if(checked[index] == true){
                return true;
            }
            
            return false;
            
        }

bool Field::has_mine(int index) const{
            if ( cells[index]==1){
                return true;
            }
        
            return false;
            
        }