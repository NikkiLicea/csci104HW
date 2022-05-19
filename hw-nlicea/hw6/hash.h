#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <vector>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const{
        // Add your code here
        unsigned long long w[5] = {0};
        HASH_INDEX_T a[6] = {0};  // holder for 6 letter substring
        unsigned long long h = 0;

        int sIndex = 0;
        int wIndex = 4;
        int aIndex = 0;
        int kSize = k.size() - 1;

        while (sIndex < (kSize + 1)){  // iterate through string
            if(aIndex == 6){  // substring of 6 letters
                w[wIndex] = bin2dec(a);  // convert to decimal
                wIndex--;
                std::fill(a, a+6, 0);  // reset a
                aIndex = 0;
            }
            HASH_INDEX_T letterNumber = letterDigitToNumber(k.at(kSize - sIndex)); 
            a[aIndex] = letterNumber;
            aIndex++;
            sIndex++;
        }
        w[wIndex] = bin2dec(a);  // process last subString

        for (int k = 0; k < 5; k++)  // get h(k)
            h += (rValues[k] * w[k]);
        
        return h;
    }

    unsigned long long bin2dec(HASH_INDEX_T a[6]) const{ 
        // unsigned long long val = 0; 
        // for(int i=0; i < 6; i++){
        //     val += b[i] * pow(36,i);
        // }
        return ((((((a[5]) * 36 + a[4]) * 36 + a[3]) * 36 + a[2]) * 36 + a[1]) * 36 + a[0]);
        // return val;
    }


    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const{
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T l = tolower(letter);  // convert to lowercase
        if(l >= 48 and l <= 57){  // 0-9
            return l -= 22;
        }
        return l -= 97;  // a-z
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
