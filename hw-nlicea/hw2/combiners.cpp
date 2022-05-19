#include "searcheng.h"
#include "combiners.h"

// Complete the necessary code

WebPageSet AndWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB){
    WebPageSet setC;  // combined set

    WebPageSet::iterator itA;
    for (itA = setA.begin(); itA != setA.end(); itA++){  // iterate through all of setA
        WebPageSet::iterator itFind = setB.find(*itA);  // check if A is in B
        if (itFind != setB.end()){  // add to setC if element is in A and B
            setC.insert(*itA);
        }
    }
    return setC;
}

WebPageSet OrWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB){
    WebPageSet setC = setB;  // combined set

    WebPageSet::iterator itA;
    for (itA = setA.begin(); itA != setA.end(); itA++){  // iterate through all of setA
        WebPageSet::iterator itFind = setB.find(*itA);  // check if A is in B
        if (itFind == setB.end()){  // insert A if not in B
            setC.insert(*itA);
        }
    }
    return setC;
}

WebPageSet DiffWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB){
    WebPageSet setC = setA;  // combined set

    WebPageSet::iterator itA;
    for (itA = setA.begin(); itA != setA.end(); itA++){  // iterate through all of setA
        WebPageSet::iterator itFind = setB.find(*itA);  // check if A is in B
        if (itFind != setB.end()){  // remove A if in B
            setC.erase(*itA);
        }
    }
    return setC;
}