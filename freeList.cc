#include "freeList.h"
#include <iostream>

using namespace std;


freeList::freeList(long int* inRAM, int size) {
    head = inRAM;              
    head[0] = size - 2;        
    head[1] = (long int)NULL;  
}


long int* freeList::reserve_space(int size) {
    long int* current = head;
    long int* prev = NULL;

    // Traverse the free list to find a suitable block (First-fit strategy)
    while (current != NULL) {
        if (current[0] >= size) {
            // Found a suitable block
            long int remaining = current[0] - size - 2; 

            if (remaining > 0) {
                // Split the block if there is enough remaining space to create a new free block
                long int* newBlock = current + size + 2; 
                newBlock[0] = remaining;                
                newBlock[1] = current[1];              

                current[1] = (long int)newBlock;     
                current[0] = size;                     
            }

          
            if (prev == NULL) {
                head = (long int*)current[1];
            } else {
                prev[1] = current[1];
            }

            return current + 2; 
        }

      
        prev = current;
        current = (long int*)current[1];
    }

    return NULL; 
}


void freeList::free_space(long int* location) {
  
    long int* block = location - 2;

    
    block[1] = (long int)head; 
    head = block;              
}


void freeList::coalesce_forward() {
    long int* current = head;

    while (current != NULL && current[1] != (long int)NULL) {
        long int* next = (long int*)current[1];

  
        if ((current + current[0] + 2) == next) {
          
            current[0] += next[0] + 2; 
            current[1] = next[1];      
        } else {
        
            current = next;
        }
    }
}


void freeList::print() {
    long int * printHead = head;

    while (printHead != NULL) {
        cout << "at " << printHead << "(" << dec << printHead[0] << " : 0x" << hex << printHead[1] << ")\n";
        printHead = (long int *)printHead[1];
    }
}
