//Name: Nabil Said
//email:nabil.said54@myhunter.cuny.edu
//Course: CSCI-135
//Instructor: Tong yi
#include "Board.hpp"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

Board::Board()
{
  srand(1);

  numRows = 3;
  numCols = 3;
  max = 0;
  target = 32;
  panel = new int *[numRows];
  for (int i = 0; i < numRows; i++)
  {
    panel[i] = new int[numCols];
    for (int j = 0; j < numCols; j++)
    {
      panel[i][j] = 0;
    }
  }
}

Board::Board(int m)
{
  srand(1);

  if (m >= 1)
  {
    numRows = m;
    numCols = m;
  }
  else
  {
    numRows = 3;
    numCols = 3;
  }
  max = 0;
  target = 32;

  this->allocateMemory();
}

Board::Board(int m, int n)
{
  srand(1);

  if (m >= 1 && n >= 1)
  {
    numRows = m;
    numCols = n;
  }
  else
  {
    numRows = 3;
    numCols = 3;
  }

  max = 0;
  target = 32;

  this->allocateMemory();
}

/**
 * Release memory space pointed by panel and remember to handle
 * dangling pointer problem.
 */
Board::~Board()
{
  for (int i = 0; i < numRows; i++)
  {
    delete[] panel[i];
  }
  delete[] panel;
  panel = nullptr;
}

void Board::allocateMemory()
{
  panel = new int *[numRows];
  for (int i = 0; i < numRows; i++)
  {
    panel[i] = new int[numCols];
    for (int j = 0; j < numCols; j++)
    {
      panel[i][j] = 0;
    }
  }
}
//
///**
// * Define print method, which prints panel as a tabular format, each number in a cell with 4-
// * character wide, if the number is a not zero, print it, otherwise, do not print it out. See
// * sample output in the project.
// *
// */
void Board::print() const
{
  // use "+----+" for the border of the table
  // use "|    |" for each empty cell

  cout << "+";
  for (int i = 0; i < numCols; i++)
  {
    cout << "----+";
  }
  cout << endl;

  for (int i = 0; i < numRows; i++)
  {
    cout << "|";
    for (int j = 0; j < numCols; j++)
    {
      if (panel[i][j] == 0)
      {
        cout << setw(4) << " ";
      }
      else
      {
        cout << setw(4) << panel[i][j];
      }
      cout << "|";
    }
    cout << endl;
    cout << "+";
    for (int i = 0; i < numCols; i++)
    {
      cout << "----+";
    }
    cout << endl;
  }
}

int Board::getNumRows() const
{
  return numRows;
}

int Board::getNumCols() const
{
  return numCols;
}

int Board::getTarget() const
{
  return target;
}

int Board::getMax() const
{
  return max;
}

void Board::selectRandomCell(int &row, int &col)
{
  struct Location
  {
    int row;
    int col;
  };

  vector<Location> zeros;
  Location cell;

  for (int i = 0; i < numRows; i++)
  {
    for (int j = 0; j < numCols; j++)
    {
      if (panel[i][j] == 0)
      {
        cell.row = i;
        cell.col = j;
        zeros.push_back(cell);
      }
    }
  }

  if (zeros.size() > 0)
  {
    int index = rand() % zeros.size();
    row = zeros[index].row;
    col = zeros[index].col;
    panel[row][col] = 1;
    this->print();
  }

  if (zeros.size() == 0 || zeros.size() == 1)
  {
    if (noAdjacentSameValue())
    {
      if (max < target)
        cout << "Game over. Try again." << endl;
      else
        cout << "Congratulations!" << endl;

      exit(0);
    }
    else
      return;
  }
}

/**
 * Define method noAdjacentSameValue, which checks whether the game can be over
 * or not. That is, if all cells are filled up (no empty cell, which represents zero, in the
 * panel) and no two adjacent cells have the same value, return true, otherwise,
 * return false.
 *
 */
bool Board::noAdjacentSameValue() const
{
  // check horizontal direction
  for (int i = 0; i < numRows; i++)
  {
    for (int j = 0; j < numCols - 1; j++)
    {
      if (panel[i][j] == panel[i][j + 1])
      {
        return false;
      }
    }
  }

  // check vertical direction
  for (int j = 0; j < numCols; j++)
  {
    for (int i = 0; i < numRows - 1; i++)
    {
      if (panel[i][j] == panel[i + 1][j])
      {
        return false;
      }
    }
  }

  return max < target;
}

void Board::pressUp()
{
  for (int col = 0; col < numCols; col++)
  {
    vector<int> nonZeros;
    for (int row = 0; row < numRows; row++)
    {
      if (panel[row][col] != 0)
      {
        nonZeros.push_back(panel[row][col]);
      }
    }

    int curr = 0;
    while (curr < nonZeros.size())
    {
      if (curr + 1 < nonZeros.size() && nonZeros[curr] == nonZeros[curr + 1])
      {
        nonZeros[curr] *= 2;
        nonZeros[curr + 1] = 0;
        if (nonZeros[curr] > max)
        {
          max = nonZeros[curr];
        }
        curr += 2;
      }
      else
      {
        curr++;
      }
    }

    int row = 0;
    for (curr = 0; curr < nonZeros.size(); curr++)
    {
      if (nonZeros[curr] != 0)
      {
        panel[row][col] = nonZeros[curr];
        row++;
      }
    }

    for (int i = row; i < numRows; i++)
    {
      panel[i][col] = 0;
    }
  }

  int row, col;
  this->selectRandomCell(row, col);
}

/**
 * Define pressDown method, which is similar to pressUp method, except that the
 * direction is from bottom to top.
 */
void Board::pressDown()
{
  for (int col = 0; col < numCols; col++)
  {
    vector<int> nonZeros;
    for (int row = numRows - 1; row >= 0; row--)
    {
      if (panel[row][col] != 0)
      {
        nonZeros.push_back(panel[row][col]);
      }
    }

    int curr = 0;
    while (curr < nonZeros.size())
    {
      if (curr + 1 < nonZeros.size() && nonZeros[curr] == nonZeros[curr + 1])
      {
        nonZeros[curr] *= 2;
        nonZeros[curr + 1] = 0;
        if (nonZeros[curr] > max)
        {
          max = nonZeros[curr];
        }
        curr += 2;
      }
      else
      {
        curr++;
      }
    }

    int row = numRows - 1;
    for (curr = 0; curr < nonZeros.size(); curr++)
    {
      if (nonZeros[curr] != 0)
      {
        panel[row][col] = nonZeros[curr];
        row--;
      }
    }

    for (int i = row; i >= 0; i--)
    {
      panel[i][col] = 0;
    }
  }

  int row, col;
  this->selectRandomCell(row, col);
}

/**
 * Define pressLeft method, which is similar to pressUp method, except that the
 * direction is from left to right.
 */
void Board::pressLeft()
{
  for (int row = 0; row < numRows; row++)
  {
    vector<int> nonZeros;
    for (int col = 0; col < numCols; col++)
    {
      if (panel[row][col] != 0)
      {
        nonZeros.push_back(panel[row][col]);
      }
    }

    int curr = 0;
    while (curr < nonZeros.size())
    {
      if (curr + 1 < nonZeros.size() && nonZeros[curr] == nonZeros[curr + 1])
      {
        nonZeros[curr] *= 2;
        nonZeros[curr + 1] = 0;
        if (nonZeros[curr] > max)
        {
          max = nonZeros[curr];
        }
        curr += 2;
      }
      else
      {
        curr++;
      }
    }

    int col = 0;
    for (curr = 0; curr < nonZeros.size(); curr++)
    {
      if (nonZeros[curr] != 0)
      {
        panel[row][col] = nonZeros[curr];
        col++;
      }
    }

    for (int i = col; i < numCols; i++)
    {
      panel[row][i] = 0;
    }
  }

  int row, col;
  this->selectRandomCell(row, col);
}

/**
 * Define pressRight method, which is similar to pressUp method, except that the
 * direction is from right to left.
 */
void Board::pressRight()
{
  for (int row = 0; row < numRows; row++)
  {
    vector<int> nonZeros;
    for (int col = numCols - 1; col >= 0; col--)
    {
      if (panel[row][col] != 0)
      {
        nonZeros.push_back(panel[row][col]);
      }
    }

    int curr = 0;
    while (curr < nonZeros.size())
    {
      if (curr + 1 < nonZeros.size() && nonZeros[curr] == nonZeros[curr + 1])
      {
        nonZeros[curr] *= 2;
        nonZeros[curr + 1] = 0;
        if (nonZeros[curr] > max)
        {
          max = nonZeros[curr];
        }
        curr += 2;
      }
      else
      {
        curr++;
      }
    }

    int col = numCols - 1;
    for (curr = 0; curr < nonZeros.size(); curr++)
    {
      if (nonZeros[curr] != 0)
      {
        panel[row][col] = nonZeros[curr];
        col--;
      }
    }

    for (int i = col; i >= 0; i--)
    {
      panel[row][i] = 0;
    }
  }

  int row, col;
  this->selectRandomCell(row, col);
}

void Board::start(){
    int round = 1;
    int row;
    int col;
    char ch;
    max = 1;
    selectRandomCell(row, col);
    selectRandomCell(row,col);
    while(true){
        if(max >= target){
            cout << "Congratulation!" << endl;
            break;
        }
        ch = getchar();
        if(ch == 'S'){
            break;
        }
        if(ch == '\033'){
            getchar();
            switch(getchar()){
            case 'A':
                cout << "Round " << setw(4) << round << ": ";
                cout << "Press UP. "
                     << "Goal: " << target << endl;
                pressUp();
                round++;
                break;
            case 'B':
                cout << "Round " << setw(4) << round << ": ";
                cout << "Press DOWN. "
                     << "Goal: " << target << endl;
                pressDown();
                round++;
                break;
            case 'D':
                cout << "Round " << setw(4) << round << ": ";
                cout << "Press LEFT. "
                     << "Goal: " << target << endl;
                pressLeft();
                round++;
                break;
            case 'C':
                cout << "Round " << setw(4) << round << ": ";
                cout << "Press RIGHT. "
                     << "Goal: " << target << endl;
                pressRight();
                round++;
                break;
            }
        }
    }
}