#include <iostream>
#include <map>
#include "Schedule.h"

using namespace std;

Schedule::Schedule(string name)
{
    mName = name;
}

bool Schedule::dropCourse(std::string name){
    // TO DO: if the course was not already in the map, return false
    // otherwise, remove it from the map and return true!

    map<string, Course*>::iterator it;
    it = courseMap.find(name);
    if(it == courseMap.end()){
        return false;
    }
    else{
        courseMap.erase(name);
        return true;
    }
}

bool Schedule::addCourse(Course* c){
    // TO DO: if the course was already in the map, return false
    // otherwise, add it to the map and return true!

    map<string, Course*>::iterator it;
    for (it = courseMap.begin(); it != courseMap.end(); ++it){
        if (it->second == c){
            return false;
        }
        
    }
    courseMap[c->getCourseName()] = c;
    return true;
}

void Schedule::printAllAssignments(){
    // TO DO: print out the name of each course, followed by the set of assignments.
    // for each assignment, display its name, its type (essay vs hw vs exam), and whether or not it was completed.
    // formatting is up to you, but make sure it's easy to read!

    map<string, Course*>::iterator it;
   set<Assignment*>::iterator it2;
    for (it = courseMap.begin(); it != courseMap.end(); it++){
        cout << it->first << ':' << endl; // course name (key)
        for(it2 = it->second->getAssignmentSet().begin() ; it2 != it->second->getAssignmentSet().end(); it2++){
            cout << (*it2)->getName()
                 << " has type " << (*it2)->getType()
                 << " and is complete " << (*it2)->isComplete() << endl;
        }
    }
}

std::map<std::string, Course*> Schedule::getCourses()
{
    return courseMap;
}