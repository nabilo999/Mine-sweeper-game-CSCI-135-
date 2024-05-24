//Name: Nabil Said
//email:nabil.said54@myhunter.cuny.edu
//Course: CSCI-135
//Instructor: Tong yi

#include "Game.hpp"
#include <iostream>
using namespace std;

Game:: Game(): area() {
}

Game:: Game(int size, int num_mines): area(size, num_mines){
}

int Game::input() const {
    int num;
    cout << "Please choose a cell (the first starts from 0): ";
    cin >> num;

    while (true) { // will loop continously
        if (!(num >= 0 && num <= this->area.get_size() - 1)) { // if num is NOT a valid index
            cout << "Enter an integer in [0, " << area.get_size()-1 << "]: "; // asks user to re-enter num
            cin >> num;
            continue; // checks condition again
        }

        if(this->area.is_checked(num)) { // if cell is already checked
            cout << "Cell " << num << "is already chosen. Please re-enter: "; // asks user to re-enter num
            cin >> num;
            continue; // checks condition again
        }
      
        break;
    }
    return num;
}

void Game::play() {
  int round = 1;
  int check = 0; // # of checked cells

  while(true) {
    cout << area.to_string() << endl; // prints current field
    cout << "Round " << round << ": ";

    int num = input(); // user's input for cell
    area.mark_checked(num); // marks user's choosen cell checked
    // cout << area.to_string() << endl; // prints current field
    check++; // update checked cells

    if(area.has_mine(num)) { // if choosen cell has mine
      cout << "Mine explodes! Game ends." << endl;
      break;
    }

    else if(check == area.get_size() - area.get_num_mines()) { 
      cout << area.to_string() << endl;
      cout << "Congratulations! Find out all the cells without mines." << endl;
      break;
    }

    area.mark_checked(num); // marks cell checked
    round++;
  }
  cout <<"\nThe answer is " << endl;
  cout << area.answer_string(); 
}