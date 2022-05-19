#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "searcheng.h"

using namespace std;

// Helper function that will extract the extension of a filename
std::string extract_extension(const std::string& filename);

std::string extract_extension(const std::string& filename)
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}


// To be updated as needed 
SearchEng::SearchEng()
{

}

// To be completed
SearchEng::~SearchEng(){
    std::map<std::string, WebPage*>::iterator itPage;
    for(itPage = pageObjects_.begin(); itPage != pageObjects_.end(); itPage++){
        delete pageObjects_[itPage->first];
    }

    std::map<std::string, PageParser*>::iterator itTerm;
    for(itTerm = parsers_.begin(); itTerm != parsers_.end(); itTerm++){
        delete parsers_[itTerm->first];
    }
}

// Complete
void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{
    if (parsers_.find(extension) != parsers_.end())
    {
        throw std::invalid_argument("parser for provided extension already exists");
    }
    parsers_.insert(make_pair(extension, parser));
}

// Complete
void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

// To be completed - DONE
void SearchEng::read_page(const string& filename){
    string ext = extract_extension(filename);
    
    // Logic Error
    bool foundParser = false;
    std::map<std::string, PageParser*>::iterator it;
    for (it = parsers_.begin(); it != parsers_.end(); it++){  // iterate through all of setA
        if(it->first == ext){
            foundParser = true;
            break;
        }
    }
    if(!foundParser){
        throw std::logic_error("no parser is registered for extension");
    }

    // Invalid Argument Error
    ifstream ifile(filename.c_str());
    if(ifile.fail()) {
        throw std::invalid_argument("filename doesn't exist");
    }

    // Parse
    std::set<std::string> allSearchableTerms;
    std::set<std::string> allOutgoingLinks;
    parsers_.at(ext)->parse(ifile, allSearchableTerms, allOutgoingLinks);

    // Update Webpage objects and ability to look them up via their page/filename
    WebPage* newPage = retrieve_page(filename);
    if(newPage == NULL){
        newPage = new WebPage(filename);
    }
    newPage->all_terms(allSearchableTerms);
    pageObjects_.insert(std::pair<string,WebPage*>(filename, newPage));

    // Update outgoing and incoming links
    std::set<std::string>::iterator itLinks;
    for(itLinks = allOutgoingLinks.begin(); itLinks != allOutgoingLinks.end(); itLinks++){
        WebPage* page = retrieve_page(*itLinks);  // Pointer to page in allOutgoingLinks
        if(page != NULL){
            page->add_incoming_link(newPage);  // add newPage to incoming links
            newPage->add_outgoing_link(page);  // add page to outgoing links
        }
        else{  // page doesn't exist
            WebPage* newTemp = new WebPage(*itLinks);
            newTemp->add_incoming_link(newPage);
            newPage->add_outgoing_link(newTemp);
            pageObjects_.insert(std::pair<string,WebPage*>(*itLinks, newTemp));
        }
    }

    // Update webpages that match a particular search term
    std::set<std::string>::iterator itTerms;
    for (itTerms = allSearchableTerms.begin(); itTerms != allSearchableTerms.end(); itTerms++){  // iterate through allSearchableTerms
        map<std::string, WebPageSet>::iterator findTerm = searchTerms_.find(*itTerms);
        if(findTerm != searchTerms_.end()){  // add to existing term
            findTerm->second.insert(newPage);
        }
        else{  // add new term
            WebPageSet newSet;
            newSet.insert(newPage);
            searchTerms_.insert(std::pair<std::string, WebPageSet>(*itTerms, newSet));
        }
    }

}

// To be completed - DONE
WebPage* SearchEng::retrieve_page(const std::string& page_name) const{
    std::map<std::string, WebPage*>::const_iterator itFind = pageObjects_.find(page_name);  // find
    if (itFind != pageObjects_.end()){
        return itFind->second;
    }
    return NULL;
}

// To be completed - DONE
void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const{
    // Invalid Argument Error
    if(retrieve_page(page_name) == NULL){
        throw std::invalid_argument("page_name does not exist");
    }

    // Logic Error
    string ext = extract_extension(page_name);
    bool foundParser = false;
    std::map<std::string, PageParser*>::const_iterator it;
    for (it = parsers_.begin(); it != parsers_.end(); it++){  // iterate through all of setA
        if(it->first == ext){
            foundParser = true;
            break;
        }
    }
    if(!foundParser){
        throw std::logic_error("no parser is registered for extension");
    }

    // Display Page
    ifstream ifile(page_name);
    string output = parsers_.at(ext)->display_text(ifile);
    ostr << output;

}

// To be completed - DONE
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const{
    WebPageSet finalSet = {}; // Set of webpages matching the query
    int count = 0;

    for(size_t i = 0; i < terms.size(); i++){  // iterate through all terms
        count++;
        WebPageSet tempSet = {}; // empty holder
        std::map<std::string, WebPageSet>::const_iterator findIt = searchTerms_.find(terms[i]);
        if(findIt != searchTerms_.end()){  // get set of WebPages for term
            finalSet = findIt->second;
            break;
        }
    }
        
    for(size_t i = count; i < terms.size(); i++){  // iterate through all terms
        WebPageSet tempSet = {}; // empty holder
        std::map<std::string, WebPageSet>::const_iterator findIt = searchTerms_.find(terms[i]);
        if(findIt != searchTerms_.end()){  // get set of WebPages for term
            tempSet = findIt->second;
        }
        finalSet = combiner->combine(finalSet, tempSet);  // combine the sets together
    }
    return finalSet;
}

// Add private helper function implementations here

