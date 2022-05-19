#include "labellist.h"
#include <cassert>

// Complete - Do not alter
LabelList::MsgNode::MsgNode(const MsgType& msg)
    : msg_(msg)
{
    // Every message is part of the "all" (index 0) label
    labelled_.push_back(true);
    next_.push_back(nullptr);
    prev_.push_back(nullptr);
}


// Complete - Do not alter
LabelList::MsgToken::MsgToken()
 : node_(nullptr), list_(nullptr)
{
}

// To be completed - must adhere to any requirements in the .h file - Done
LabelList::MsgToken::MsgToken(MsgNode* node, LabelList* list) //:  node_{node}, list_{list}
{
    node_ = node;
    list_ = list;
}

// To be completed - must adhere to any requirements in the .h file - DOne
bool LabelList::MsgToken::operator==(const MsgToken& rhs) const{
    bool flag = false;
    if (node_ == rhs.node_){
        flag = true;
    }
    return flag;
}

// Complete - Do not alter
bool LabelList::MsgToken::operator!=(const MsgToken& rhs) const
{
    return !operator==(rhs);
}

// To be completed - must adhere to any requirements in the .h file - Done
LabelList::MsgToken::operator bool() const{
    if (isValid()){
        return true;
    }
    return false;
}

// Complete - Do not alter
bool LabelList::MsgToken::isValid() const
{
    return this->node_ != nullptr;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::next(const LabelType& label)
{
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->next_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::prev(const LabelType& label)
{
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->prev_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(const LabelType& label) const
{
    size_t index = this->list_->findLabelIndex(label);
    return isLabelMember(index);
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(size_t index) const
{
    return this->isValid() && 
            index != INVALID_LABEL &&
            index < this->node_->labelled_.size() &&
            this->node_->labelled_[index] ;
}

// To be completed - must adhere to any requirements in the .h file - Done
LabelList::MsgType const & LabelList::MsgToken::msg() const
{
    if(this->isValid()){
        return this->node_->msg_;
    }
    throw std::logic_error("token references an invalid message");
    
}
// To be completed - must adhere to any requirements in the .h file - Done
LabelList::MsgType& LabelList::MsgToken::msg() 
{
    if(this->isValid()){
        return this->node_->msg_;
    }
    throw std::logic_error("token references an invalid message");
}

// Complete
std::ostream& operator<<(std::ostream& ostr, const LabelList::MsgToken& token)
{
    if(token.isValid())
    {
        ostr << token.node_->msg_;
    }
    return ostr;
}

// Static constant 
const LabelList::MsgToken LabelList::end_(nullptr, nullptr);

// To be completed - must adhere to any requirements in the .h file
LabelList::LabelList() //:  labels_{"all"}, heads_{nullptr}{
{   labels_.push_back("all");
    heads_.push_back(nullptr);
    tail_ = nullptr;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::~LabelList()
{
    clear();
}

// To be completed - must adhere to any requirements in the .h file - Done
void LabelList::clear(){
    MsgNode* allPtr = heads_[0];
    while(allPtr != nullptr){  // iterate to last msg
        MsgNode* allPtrDelete = allPtr;
        delete allPtrDelete;
        allPtr = allPtr->next_[0];
    }
}

// To be completed - must adhere to any requirements in the .h file - Done
bool LabelList::empty() const{
    if (heads_[0] == nullptr){
        return true;
    }
    return false;
}

// Complete
size_t LabelList::size() const
{
    MsgNode* n = this->heads_[0];
    size_t cnt = 0;
    while(n != nullptr){
        cnt++;
        n = n->next_[0];
    }
    return cnt;
}

// To be completed - must adhere to any requirements in the .h file - Done
LabelList::MsgToken LabelList::add(const MsgType& msg){
    MsgNode* newMsg = new MsgNode(msg);
    MsgToken newT(newMsg, this);

    if(heads_[0] == nullptr){  // no messages in all
        heads_[0] = newMsg;  // points to first MsgNode  -  @290
        newMsg->prev_[0] = nullptr;  // prev is null
        newMsg->next_[0] = nullptr;  // next is null
    }
    else{
        newMsg->prev_[0] = tail_;  // prev is last MsgNode
        newMsg->next_[0] = nullptr;  // next is null
        tail_->next_[0] = newMsg;  // update last MsgNode's next
    }
    tail_ = newMsg;  // update tail
    return newT;
}


// To be completed - must adhere to any requirements in the .h file
void LabelList::remove(const MsgToken& token){
    if(!token.isValid()){  // invalid Token
        return;
    }

    MsgNode* prevMsg = token.node_->prev_[0];
    MsgNode* nextMsg = token.node_->next_[0];
    if(prevMsg == nullptr){ // when first msg node
        for (size_t i = 0; i < heads_.size(); i++){
            heads_[i] = token.node_->next_[i];
        }
    }
    else{  // something left
        for (size_t i = 0; i < prevMsg->next_.size(); i++){
            prevMsg->next_[i] = token.node_->next_[i];
        }
    }
    
    if(nextMsg != nullptr){  // elements to the right
        for (size_t i = 0; i < nextMsg->prev_.size(); i++){
            nextMsg->prev_[i] = token.node_->prev_[i];
        }
    }

    // your msg points to nothing
    for(size_t i = 0; i < token.node_->next_.size(); i++){
        token.node_->next_[i] = nullptr;  // your next = null
        token.node_->prev_[i] = nullptr;  // your prev = null
        token.node_->labelled_[i] = false;  // no longer a member
    }
}

// To be completed - must adhere to any requirements in the .h file - Done but wrong
void LabelList::label(const MsgToken& token, const LabelType& label){
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }

    size_t labelIndex = this->findLabelIndex(label);

    if(labelIndex == INVALID_LABEL){  // label doesn't exist

        if (token.node_->labelled_.size() < labels_.size() - 1){  // resize NodeMsg 
            token.node_->labelled_.resize(labels_.size(), false);
            token.node_->next_.resize(labels_.size(), nullptr);
            token.node_->prev_.resize(labels_.size(), nullptr);
        }

        labels_.push_back(label);  // add label to vector
        heads_.push_back(token.node_);  // update new label head
        token.node_->prev_.push_back(nullptr);  // prev is null
        token.node_->next_.push_back(nullptr);  // next is null
        token.node_->labelled_.push_back(true);
    }
    else{  // label exists - access previous through all and check if the prev has the label

        if (token.node_->labelled_.size() <= labelIndex){  // resize NodeMsg
            token.node_->labelled_.resize(labelIndex + 1, false);
            token.node_->next_.resize(labelIndex + 1, nullptr);
            token.node_->prev_.resize(labelIndex + 1, nullptr);
        }

        if(heads_[labelIndex] == nullptr){
            heads_[labelIndex] = token.node_;
            token.node_->prev_[labelIndex] = nullptr;
            token.node_->next_[labelIndex] = nullptr;
        }
        else{
            // left side
            MsgNode* tempToken = token.node_->prev_[0];
            if(tempToken == nullptr){ // when first msg node
                token.node_->next_[labelIndex] = heads_[labelIndex];
                heads_[labelIndex] = token.node_;
                token.node_->prev_[labelIndex] = nullptr;
            }
            else{  // when there msgs on the left
                bool unfound = true;
                while(unfound){  //and tempToken != nullptr
                    if (tempToken->labelled_[labelIndex] == true){  // find msg also in label
                        tempToken->next_[labelIndex] = token.node_;  // prevMsg's next = you
                        token.node_->prev_[labelIndex] = tempToken;  // your prev = prevMsg
                        unfound = false;
                    }
                    else{
                        tempToken = tempToken->prev_[0];  // go back another msg
                    }
                }
            }

            // right side 
            MsgNode* tempTokenR = token.node_->next_[0];  
            if(tempTokenR == nullptr){  // when last msg node
                token.node_->next_[labelIndex] = nullptr;
            }
            else{  // when msgs on the right
                bool unfound = true;
                while(unfound and tempTokenR != nullptr){  // iterate through all msgs on right
                    if (tempTokenR->labelled_[labelIndex] == true){  // msg also in label
                        tempTokenR->prev_[labelIndex] = token.node_;  // nextMsg's prev = you
                        token.node_->next_[labelIndex] = tempTokenR;  // your next = nextMsg
                        unfound = false;
                    }
                    else{
                        tempTokenR = tempTokenR->next_[0];  // go forward another msg
                    }
                }
                if(unfound && tempTokenR == nullptr){
                    token.node_->next_[labelIndex] = nullptr;
                }
            }
        }
        token.node_->labelled_[labelIndex] = true;
    }
}

// To be completed - must adhere to any requirements in the .h file
void LabelList::unlabel(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }

    size_t labelIndex = this->findLabelIndex(label);
    if(labelIndex == INVALID_LABEL){
        throw std::out_of_range("Label doesn't exist");
    }

    if(label == "all" or token.node_->labelled_[labelIndex] != true){  // do nothing if unlabeling from all
        return;                                                        // or if element isn't a member of label                                                        
    }

    MsgNode* prevMsg = token.node_->prev_[labelIndex];
    MsgNode* nextMsg = token.node_->next_[labelIndex];
    if(prevMsg == nullptr){ // when first msg node
        heads_[labelIndex] = token.node_->next_[labelIndex];  // heads = nextMsg
        if(nextMsg != nullptr){
            nextMsg->prev_[labelIndex] = nullptr;  // nextMsg's prev = null
        }
    }
    else{  // something left
        prevMsg->next_[labelIndex] = nextMsg;
    }
    
    if(prevMsg != nullptr){
        if(nextMsg == nullptr){  // last node
            prevMsg->next_[labelIndex] = nullptr;
        }
        else{  // something right
            nextMsg->prev_[labelIndex] = prevMsg;
        }
    }

    // your msg points to nothing
    token.node_->next_[labelIndex] = nullptr;  // your next = null
    token.node_->prev_[labelIndex] = nullptr;  // your prev = null
    token.node_->labelled_[labelIndex] = false;  // no longer a member

}

// Complete - Do not alter
LabelList::MsgToken LabelList::find(const MsgType& msg, const LabelType& label)
{
    // See if the label exists, will throw if not
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(n != nullptr)
    {
        if(n->msg_ == msg)
        {
            return MsgToken(n, this);
        }
        n = n->next_[level];
    }
    return end();
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken LabelList::find(size_t index, const LabelType& label){
    // See if the label exists, will throw if not
    size_t labelIndex = this->findLabelIndex(label);
    if(labelIndex == INVALID_LABEL){
        throw std::out_of_range("Label doesn't exist");
    }

    MsgNode* n = this->heads_[labelIndex];
    size_t count = 0;
    while(count < index){
        if(n->next_[labelIndex] == nullptr){  // ensure valid index
            return end();
        }
        n = n->next_[labelIndex];
        count++;
    }
    return MsgToken(n, this);
}

// Complete - Do not alter
LabelList::MsgToken const & LabelList::end() const
{
    return end_;
}

// Complete - Do not alter
void LabelList::print(std::ostream& ostr, const LabelType& label, char separator) const
{
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(nullptr != n)
    {
        ostr << n->msg_ << separator;
        n = n->next_[level];
    }
    ostr << std::endl;
}

// To be completed - must adhere to any requirements in the .h file
size_t LabelList::findLabelIndex(const LabelType& label) const{
    for (size_t i = 0; i < labels_.size(); i++){
        if(labels_[i] == label){
            return i;
        }
    }
    return INVALID_LABEL;
}

// Complete - Do not alter
size_t LabelList::getLabelIndex(const LabelType& label) const
{
    size_t retval = this->findLabelIndex(label);
    if(INVALID_LABEL == retval)
    {
        throw std::out_of_range("Label doesn't exist");
    }
    return retval;
}


