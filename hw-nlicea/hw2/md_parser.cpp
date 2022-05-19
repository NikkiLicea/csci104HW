#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;

// To be completed
void MDParser::parse(std::istream& istr, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks){

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();

    // Complete your code below
    string term = "";
    string link = "";
    PARSE_STATE_T type = NORMALTEXT;

    // Get the first character from the file.
    char c = istr.get();

    // Continue reading from the file until input fails.
    while(!istr.fail()){
        if(c != '(' and c!= '[' and type == ISLINK){
            type = NORMALTEXT; 
        }
        else if (isalnum(c) and type == NORMALTEXT){
            while(c != '[' and isalnum(c) and !istr.fail()){
                string s(1, c);
                term += conv_to_lower(s);
                c = istr.get();
            }    
            allSearchableTerms.insert(term);
            term = "";
            if(c != '['){
                c = istr.get(); 
            }            
        }
        else if(c == '['){
            type = LINKTEXT;
            c = istr.get();
            while(c != ']' and !istr.fail()){
                if(!isalnum(c)){
                    if(term != ""){
                        allSearchableTerms.insert(term);
                        term = "";
                    }
                    c = istr.get();
                    continue;
                }
                string s(1, c);
                term += conv_to_lower(s);
                c = istr.get();
            }
            if(c == ']'){
                type = ISLINK;
            }
            if(term != ""){
                allSearchableTerms.insert(term);
                term = "";
            }
            c = istr.get();
        }
        else if(c == '(' and type == ISLINK){
            type = LINKURL;
            c = istr.get();
            while(c != ')' and !istr.fail()){
                string s(1, c);
                link += conv_to_lower(s);
                c = istr.get();
            }
            if(link != ""){
                allOutgoingLinks.insert(link);
                link = "";
            }
            type = NORMALTEXT;
            c = istr.get();
        }
        else if(c == ')'){
            type = NORMALTEXT;
            c = istr.get();
        }
        else{  // continue onto next char
            c = istr.get();
        }           
    }

}

// To be completed
std::string MDParser::display_text(std::istream& istr){
    string text;
    PARSE_STATE_T type = NORMALTEXT;
    char c = istr.get();

    while(!istr.fail()){
        if(c != '(' and c!= '[' and type == ISLINK){
            type = NORMALTEXT; 
        }
        else if(c == '['){
            type = LINKTEXT;
            while(c != ']' and !istr.fail()){
                text += c;
                c = istr.get();
            }
            if(c == ']'){
                type = ISLINK;
                text += c;
                c = istr.get();
            }
        }
        else if(c == '(' and type == ISLINK){
            type = LINKURL;
            while(c != ')' and !istr.fail()){  // continue until non-link is reached
                c = istr.get();
            }
            type = NORMALTEXT;
            c = istr.get();
        }
        else if (type == NORMALTEXT){
            while(c != '[' and !istr.fail()){
                text += c;
                c = istr.get();
            }             
        }
        else{  // continue onto next char
            c = istr.get();
        }           
    }
    return text;
}


