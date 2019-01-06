#ifndef _BINTREE_COMMON_
#define _BINTREE_COMMON_

namespace bbt {

    typedef struct people{
        int val;
        struct people* pleft;
        struct people* pright;
        people(): val(0),pleft(0),pright(0){};
    }node;
    
}
#endif
