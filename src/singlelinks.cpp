/*
 * singlelinks.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: penglijiang
 */

#include "singledeslinks.hpp"

using namespace sdl;

int main(){
    node* singleLink = 0;
    const char* file = "../data/singleLink.txt";

    singleLink = create_from_file(file);

    printlist(singleLink);

    int len = length(singleLink);
    printf("length is %d\n",len);

    return 0;
}


