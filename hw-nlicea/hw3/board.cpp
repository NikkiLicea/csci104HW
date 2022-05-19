#include "board.h"
#include <iomanip>
#include <string>
#include <stdexcept>
#include <set>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

const Board::VID_T Board::escapeID_ = 'a';

// Complete
Board::Board()
{
    
}

// Complete
Board::Board(std::istream& is)
{
    vector<string > rawBoard;
    string line;
    while(getline(is, line)) {
        // skip empty lines
        stringstream ss(line);
        string temp;
        // Skip if no text on this line
        if(!(ss << temp)){
            continue;
        }
        // Must have contents, let's add it
        rawBoard.push_back(line);
    }
    // Error check
    if(rawBoard.size() == 0) {
        throw std::logic_error("0 size board");
    }
    unsigned i = 0;
    // Ensure same number of columns and rows
    while(i < rawBoard.size()) {
        if(rawBoard[i].size() != rawBoard.size()) {
            throw std::logic_error("Invalid row size");
        }
        i++;
    }

    // allocate rows for the 2D board
    grid_.resize(rawBoard.size());

    // Find and build all the Vehicle objects from the 2D grid
    for(int r = 0; r < (int)rawBoard.size(); r++) {
        // allocate columns for each row
        grid_[r].resize(rawBoard[r].size());
        for(int c = 0; c < (int)rawBoard[r].size(); c++) {
            
            // If we have vehicle in this location, update the vehicle
            if( isalpha(rawBoard[r][c] )) {
                grid_[r][c] = rawBoard[r][c];
                map<char, Vehicle>::iterator it = vehicles_.find(rawBoard[r][c]);
                if(it == vehicles_.end()) {
                    vehicles_.insert(make_pair(rawBoard[r][c], Vehicle(r, c, rawBoard[r][c])));
                }
                else {
                    if(it->second.startr == r) {
                        it->second.direction = Vehicle::HORIZONTAL;
                        it->second.length = (c - it->second.startc + 1);
#ifdef DEBUG
                        cout << "Increasing " << it->second.id << " to len " << it->second.length
                             << " and dir=" << it->second.direction << endl;
#endif
                    }
                    else {
                        it->second.direction = Vehicle::VERTICAL;
                        it->second.length = (r - it->second.startr + 1);
#ifdef DEBUG
                        cout << "Increasing " << it->second.id << " to len " << it->second.length
                             << " and dir=" << it->second.direction << endl;
#endif
                    }
                }
            }
            // Blank space
            else if( Vehicle::INVALID_ID  == rawBoard[r][c] )
            {
                grid_[r][c] = rawBoard[r][c];
            }
            else {
                throw std::logic_error("Invalid character in board");
            }
        }
    }
}

// Update if necessary
Board::Board(const Board& b) :
    vehicles_(b.vehicles_), grid_(b.grid_)
{
}

// Update if necessary
Board::~Board()
{
}

// Complete
int Board::size() const 
{
    return (int) grid_.size();
}

// Complete
Board::VID_T Board::at(int r, int c) const
{
    if(r >= (int)grid_.size() || c >= (int)grid_.size() || r < 0 || c < 0)
    {
        throw std::invalid_argument("Out of bounds index to at()");
    }
    return grid_[r][c];
}

// Complete
const Vehicle& Board::vehicle(VID_T vid) const
{
    // can't use operator[] since it isn't a const member of map
    return vehicles_.at(vid);
}

// Complete
const Vehicle& Board::escapeVehicle() const
{
    // can't use operator[] since it isn't a const member of map
    return vehicles_.at(escapeID_);
}

// Complete but may be updated, if necessary
bool Board::solved() const
{
    // can't use operator[] since it isn't a const member of map
    const Vehicle& v = vehicles_.at(escapeID_);
    int r = v.startr;
    for(int c = v.startc + v.length; c < (int)grid_[r].size(); c++)
    {
        if(grid_[r][c] != Vehicle::INVALID_ID){
            return false;
        }
    }
    return true;
}

// Complete
bool Board::isLegalMove(VID_T vid, int amount) const
{
    // can't use operator[] since it isn't a const member of map
    const Vehicle& v = vehicles_.at(vid);
    if(v.direction == Vehicle::VERTICAL) {
        int newr = v.startr + amount;
        // Is target location still on the board
        if( (newr < 0) || ((newr + v.length) > (int) grid_.size()) ) {
            return false;
        }

        // Check if any other vehicle is blocking
        if(amount < 0)
        { 
            for(int r = v.startr-1; r >= newr; r--)
            {
                if(grid_[r][v.startc] != Vehicle::INVALID_ID)
                {
                    return false;
                }
            }
        }
        else 
        {
            for(int r = v.startr + v.length; r < v.startr + v.length + amount; r++)
            {
                if(grid_[r][v.startc] != Vehicle::INVALID_ID)
                {
                    return false;
                }
            }
        }
    }
    if(v.direction == Vehicle::HORIZONTAL) {
        int newc = v.startc + amount;

        // Is target location still on the board
        if( (newc < 0) || ((newc + v.length) > (int) grid_.size()) ) {
            return false;
        }

        // Check if any other vehicle is blocking
        if(amount < 0)
        { 
            for(int c = v.startc-1; c >= newc; c--)
            {
                if(grid_[v.startr][c] != Vehicle::INVALID_ID)
                {
                    return false;
                }
            }
        }
        else 
        {
            for(int c = v.startc + v.length; c < v.startc + v.length + amount; c++)
            {
                if(grid_[v.startr][c] != Vehicle::INVALID_ID)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// Complete but may be updated, if necessary
bool Board::move(VID_T vid, int amount)
{
    if(isLegalMove(vid, amount)) {
        Vehicle& v = vehicles_[vid];
        if(v.direction == Vehicle::VERTICAL) {
            v.startr += amount;
        }
        else {
            v.startc += amount;
        }
        // add to pastMoves
        pastVID.push(vid);
        pastAmt.push(amount);
        updateBoard();

        return true;
    }
    else {
        return false;
    }

}

// To be completed - DONE
void Board::undoLastMove(){
    if(pastVID.empty() or pastAmt.empty()){
        throw std::underflow_error("No moves to undo");
    }

    move(pastVID.top(), -1*pastAmt.top());  // move opposite way
    pastVID.pop();  // get rid of last values
    pastAmt.pop();
}

// To be completed - DONE
Board::MovePairList Board::potentialMoves() const{
    MovePairList pairs;  // holder
    for(VehicleMap::const_iterator it = vehicles_.begin(); it != vehicles_.end(); it++){  // iterate through all vehicles
        if(it->second.direction == Vehicle::VERTICAL) {  // vertical orientation
            int countTop = -1;
            for(int r = (int)it->second.startr - 1; r >= 0; r--) {  // iterate through above rows
                if(grid_[r][it->second.startc] == '.'){  // add to pairs if open
                    pairs.push_back(make_pair(it->first, countTop));
                    countTop--;
                }
                else if(grid_[r][it->second.startc] != it->first){  // stop when unable to move
                    break;
                }
            }
            int countDown = 1;
            for(int r = (int)it->second.startr + 1; r < (int)grid_.size(); r++) {  // iterate through below rows
                if(grid_[r][it->second.startc] == '.'){  // add to pairs if open
                    pairs.push_back(make_pair(it->first, countDown));
                    countDown++;
                }
                else if(grid_[r][it->second.startc] != it->first){  // stop when unable to move
                    break;
                }
            }
        }
        else {  // when horizontal orientation
            int countLeft = -1;
            for(int c = (int)it->second.startc - 1; c >= 0; c--) {  // iterate through left columns
                if(grid_[it->second.startr][c] == '.'){  // add to pairs if open
                    pairs.push_back(make_pair(it->first, countLeft));
                    countLeft--;
                }
                else if(grid_[it->second.startr][c] != it->first){  // stop when unable to move
                    break;
                }
            }
            int countRight = 1;
            for(int c = (int)it->second.startc + 1; c < (int)grid_.size(); c++) {  // iterate through right columns
                if(grid_[it->second.startr][c] == '.'){  // add to pairs if open
                    pairs.push_back(make_pair(it->first, countRight));
                    countRight++;
                }
                else if(grid_[it->second.startr][c] != it->first){  // stop when unable to move
                    break;
                }
            }
        }
    }
    return pairs;
}

// To be completed
bool Board::operator<(const Board& other) const{
    int thisVal = 0;
    for(int r = 0; r < (int)grid_.size(); r++) {  // iterate through my board
        for(int c = 0; c < (int)grid_[r].size(); c++) {
            if(isalpha(grid_[r][c])){  // increase value for letters
                thisVal += ((r+1) * (c+1));
            }
        }
    }
    
    int otherVal = 0;
    for(int r = 0; r < (int)other.grid_.size(); r++) {  // iterate through other board
        for(int c = 0; c < (int)other.grid_[r].size(); c++) {
            if(isalpha(other.grid_[r][c])){  // increase value for letters
                otherVal += ((r+1) * (c+1));
            }
        }
    }
    return thisVal < otherVal;
}

// Complete
std::ostream& operator<<(std::ostream& os, const Board& b)
{
    for(int r = 0; r < (int)b.grid_.size(); r++) {
        for(int c = 0; c < (int)b.grid_[r].size(); c++) {
            os << b.grid_[r][c];
        }
        os << endl;
    }
    return os;
}

// Complete
void Board::updateBoard()
{
    for(int r = 0; r < (int)grid_.size(); r++) {
        for(int c = 0; c < (int)grid_[r].size(); c++) {
            grid_[r][c] = '.';
        }
    }
    for (auto mypair : vehicles_)
    {
        if(mypair.second.direction == Vehicle::VERTICAL)
        {
            for(int r = 0; r < mypair.second.length; r++)
            {
                grid_[mypair.second.startr + r][mypair.second.startc] = mypair.second.id;
            }
        }
        else 
        {
            // horizontal
            for(int c = 0; c < mypair.second.length; c++)
            {
                grid_[mypair.second.startr][mypair.second.startc + c] = mypair.second.id;
            }
        }
    }
}
