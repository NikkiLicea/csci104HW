// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
std::set<std::string> wordleHelper(
    const string& in, const string& floating, 
    const set<std::string>& dict, 
    set<std::string>& validWords);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict){
    // Add your code here

    std::set<std::string> validWords;
    wordleHelper(in, floating, dict, validWords);
    return validWords;

}

std::set<std::string> wordleHelper(
    const string& in, const string& floating, 
    const set<std::string>& dict, 
    set<std::string>& validWords){
    size_t index = in.find('-');
    
    if(index == string::npos){ // no more '-'
        if(dict.find(in) != dict.end()){  // insert to set if valid word
            validWords.insert(in);
        }
    }
    else if(floating != ""){  // insert floating letters
        for (size_t i = index; i < in.size(); i++){   // iterate over all indexes
            string inTemp = in;         
            if(inTemp[i] == '-' and (int)count(inTemp.begin(), inTemp.end(), '-') >= (int)floating.size()){  // replace '-'
                for(size_t s = 0; s < floating.size(); s++){
                    inTemp = in;
                    inTemp[i] = floating[s];
                    string floatingTemp = floating;
                    floatingTemp.erase(s, 1);
                    wordleHelper(inTemp, floatingTemp, dict, validWords);  // recurse on remaining floating letters
                }
            }
        }   
    }
    else{  // insert random letters
        for (size_t i = index; i < in.size(); i++){   // iterate over all indexes
            string inTemp = in;
            if(inTemp[i] == '-'){
                for(char c = 'a'; c <= 'z'; c++){  // iterate a-z
                    inTemp = in;
                    inTemp[i] = c;
                    wordleHelper(inTemp, floating, dict, validWords);  // recurse for remaining '-' 
                }
            }         
        }
    }
    return validWords;
}

// Define any helper functions here
// std::set<std::string> wordleHelper(
//     const string& in, const string& floating, 
//     const set<std::string>& dict, 
//     set<std::string>& validWords, int pos){
//     size_t index = in.find('-');
    
//     if(pos == (int)(in.size()) or in.find('-') == string::npos){ // iterated through whole word or no more '-'
//         if(dict.find(in) != dict.end()){  // insert to set if valid word
//             validWords.insert(in);
//         }
//         return validWords;
//     }
//     else if(in[pos] == '-' and floating != ""){  // insert floating letters
//         string inTemp = in;
//         for (size_t i = 0; i < floating.size(); i++){
//             int posTemp = pos;
//             inTemp[pos] = floating[i];
//             wordleHelper(inTemp, floating.substr(1), dict, validWords, ++posTemp);  // recurse on remaining floating letters
//         }   
//     }
//     else if(in[pos] == '-'){  // insert random letters
//         string inTemp = in;
//         for(char c = 'a'; c <= 'z'; c++){
//             int posTemp = pos;
//             inTemp[pos] = c;
//             wordleHelper(inTemp, floating, dict, validWords, ++posTemp);  // recurse for remaining '-' 
//         }
//     }
//     else{
//         wordleHelper(inTemp, floating, dict, validWords, ++pos);
//     }
//     return validWords;
// }

// Define any helper functions here
// std::set<std::string> wordleHelper(
//     const std::string& in,
//     const std::string& floating,
//     const std::set<std::string>& dict){
//     if(in.find('-') == string::npos){ // no '-' characters
//         if(dict.find(in) != dict.end()){  // insert to set if valid word
//             validWords.insert(in);
//             return validWords;
//         }
//     }

//     string inTemp = in;  // temp in
//     for(int i = 0; i < in.size(); i++){  // find '-' characters
//         if(inTemp[i] == '-' and floating != ""){  // insert floating letters
//             inTemp[i] = floating[0];
//             wordle(inTemp, floating.substr(1), dict);  // recurse on remaining floating letters
//         }
//         else{  // insert random letters
//             for(char c = 'a'; c <= 'z'; c++){
//                 inTemp[i] = c;
//                 wordle(inTemp, floating, dict);  // recurse for remaining '-' 
//             }
//         }
//     }

// }