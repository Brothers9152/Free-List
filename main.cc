#include "freeList.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
using namespace std;

long int* RAM; // Simulating RAM as a dynamically allocated array of long ints

int main() {
    RAM = new long int[8192]; // Allocate simulated RAM (8192 long ints)

    freeList me(RAM, 8192); // Initialize the free list
    me.print(); // Print the initial state of the free list

    // Reserve two blocks of memory and print the state after each reservation
    long int* addr1 = me.reserve_space(100);
    me.print();
    long int* addr2 = me.reserve_space(200);
    me.print();

    // Free the first block and print the state
    me.free_space(addr1);
    me.print();

    // Coalesce consecutive free blocks and print the state
    me.coalesce_forward();
    me.print();

    // Free the second block and print the state
    me.free_space(addr2);
    me.print();

    // Attempt to coalesce again and print the final state
    me.coalesce_forward();
    me.print();

    // Clean up the dynamically allocated RAM
    delete[] RAM;
    return 0;
}
