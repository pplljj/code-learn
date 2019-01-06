#include<iostream>
//#include<string>

using namespace std;

namespace bq{

    typedef struct people{
        int val;
        struct people* pnext;
        people();
    }node;

    people::people() :val(0), pnext(0){}

    typedef struct basequeue{
        node* phead;
        node* ptail;
        basequeue();
    }bqe;

    basequeue::basequeue():phead(0),ptail(0){}


    bqe* push_in_queue(int value, bqe* bqee)
    {

        node* tp = new node;
        tp->val = value;

        if (bqee->phead == NULL)
        {
            bqee->phead = tp;
            bqee->ptail = tp;

            return bqee;
        }
        else{
            tp->pnext = bqee->phead;
            bqee->phead = tp;

            return bqee;
        }

    }


    bqe* pop_out_queue(node& res,bqe* bqee)
    {
        node* p = bqee->phead;
        if (bqee->phead == NULL) return bqee;
        else{
            if (bqee->phead == bqee->ptail)
            {
                res = *p;
                delete p;
                bqee->phead = bqee->ptail = NULL;
                return bqee;
            }
        }

        while (p && p->pnext && p->pnext->pnext)
        {
            p = p->pnext;
        }
        node* last = p->pnext;
        res = *last;
        p->pnext = NULL;
        bqee->ptail = p;
        delete last;

        return bqee;

    }

    void printlist(bqe* bqee)
    {
        node* p = bqee->phead;

        while (1)
        {
            if (!p) return;
            cout << p->val << " ";
            if (p == bqee->ptail) break;
            p = p->pnext;
        }
        cout << "\n";
    }

}
