#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot){
    if (head == nullptr) {  // end of list
        smaller = nullptr;
        larger = nullptr;
    } 
    else{
        llpivot(head->next, smaller, larger, pivot);
        if(head->val <= pivot){  // when smaller
            head->next = smaller;
            smaller = head;
            head = nullptr;
        }
        else{  // when larger
            head->next = larger;
            larger = head;
            head = nullptr;
        }
    }
}

// void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot){
//     if (head == nullptr) {  // end of list
//         smaller->next = nullptr;
//         larger->next = nullptr;
//     } 
//     else if (head->val <= pivot) {  // smaller than pivot
//         if(smaller == nullptr){  // nothing in smaller
//             smaller->val = head->val;
//             smaller->next = nullptr;
//         }
//         else{  // iterate to the end of the list and update
//             Node* temp = smaller;
//             while (temp->next != nullptr){
//                 temp = temp->next;
//             }
//             temp->next = head;
//             smaller = temp;
//         }
//         llpivot(head->next, smaller, larger, pivot);
//     } 
//     else {  // larger than pivot
//         if(larger == nullptr){  // nothing in larger
//             larger = head;
//             larger->next = nullptr;
//         }
//         else{  // iterate to the end of the list and update
//             while (larger->next != nullptr){
//                 larger = larger->next;
//             }
//             larger->next = head;
//         }
//         llpivot(head->next, smaller, larger, pivot);
//     }
// }


