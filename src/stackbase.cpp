/*
 * stack.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: penglijiang
 */


#include "basestack.hpp"

using namespace bs;

int main(){

    bsk * pStack = new bsk;
    pStack = push_in_stack(1024,pStack);
    printlist(pStack);
    return 0;
}

