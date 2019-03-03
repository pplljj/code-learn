/*
 * stack.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: penglijiang
 */


#include "basestack.hpp"
#include <stdio.h>

using namespace bs;

int main(){

    bsk * pStack = new bsk;
    pStack = push_in_stack(1024,pStack);
    pStack = push_in_stack(996,pStack);
    pStack = push_in_stack(985,pStack);
    pStack = push_in_stack(966,pStack);
    printlist(pStack);
    node res;
    pop_out_stack(res, pStack);
    printf("val: %d\n", res.val);
    pop_out_stack(res, pStack);
    printf("val: %d\n", res.val);
    printlist(pStack);
    return 0;
}

