#include "cmdhandler.h"
#include "util.h"
#include <vector>
using namespace std;

// Complete
QuitHandler::QuitHandler()
{

}

// Complete
QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";

}

// Complete
Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

// Complete
PrintHandler::PrintHandler()
{

}

// Complete
PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";

}

// Complete
Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

// Add code for other handler class implementations below

// Incoming
IncomingHandler::IncomingHandler(){
}

IncomingHandler::IncomingHandler(Handler* next) : Handler(next){
}

bool IncomingHandler::canHandle(const std::string& cmd) const{
    return cmd == "INCOMING";
}

Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    string page_name;
    instr >> page_name;  // get name
    
    const WebPage* page = eng->retrieve_page(page_name);
    if(page == NULL){  // page does not exist
        return HANDLER_ERROR;
    }

    const WebPageSet incomingLinks = page->incoming_links();  // get links

    display_hits(incomingLinks, ostr);

    return HANDLER_OK; 
}


// Outgoing
OutgoingHandler::OutgoingHandler(){
}

OutgoingHandler::OutgoingHandler(Handler* next) : Handler(next){
}

bool OutgoingHandler::canHandle(const std::string& cmd) const{
    return cmd == "OUTGOING";
}

Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    string page_name;
    instr >> page_name;  // get name
    
    const WebPage* page = eng->retrieve_page(page_name);
    if(page == NULL){  // page does not exist
        return HANDLER_ERROR;
    }

    const WebPageSet outgoingLinks = page->outgoing_links();  // get links

    display_hits(outgoingLinks, ostr);

    return HANDLER_OK; 
}

// AND
AndHandler::AndHandler(){
}

AndHandler::AndHandler(Handler* next) : Handler(next){
}

bool AndHandler::canHandle(const std::string& cmd) const{
    return cmd == "AND";
}

Handler::HANDLER_STATUS_T AndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    string terms;
    vector<string> vecTerms;
    AndWebPageSetCombiner andSearch;

    while((instr >> terms)){  // create vector of terms
        vecTerms.push_back(conv_to_lower(terms));
    }

    WebPageSet ws;
    if(vecTerms.size() != 0){
        ws = eng->search(vecTerms, &andSearch);
    }

    display_hits(ws, ostr);
    return HANDLER_OK; 
}


// OR HANDLER
OrHandler::OrHandler(){
}

OrHandler::OrHandler(Handler* next) : Handler(next){
}

bool OrHandler::canHandle(const std::string& cmd) const{
    return cmd == "OR";
}

Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    string terms;
    vector<string> vecTerms;
    OrWebPageSetCombiner orSearch;

    while(!(instr >> terms)){  // create vector of terms
        vecTerms.push_back(conv_to_lower(terms));
    }

    WebPageSet ws;
    if(vecTerms.size() != 0){
        ws = eng->search(vecTerms, &orSearch);
    }

    display_hits(ws, ostr);
    return HANDLER_OK; 
}



// DIFF HANDLER
DiffHandler::DiffHandler(){
}

DiffHandler::DiffHandler(Handler* next) : Handler(next){
}

bool DiffHandler::canHandle(const std::string& cmd) const{
    return cmd == "DIFF";
}

Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    string terms;
    vector<string> vecTerms;
    DiffWebPageSetCombiner diffSearch;

    while(!(instr >> terms)){  // create vector of terms
        vecTerms.push_back(conv_to_lower(terms));
    }

    WebPageSet ws;
    if(vecTerms.size() != 0){
        ws = eng->search(vecTerms, &diffSearch);
    }

    display_hits(ws, ostr);
    return HANDLER_OK; 
}

