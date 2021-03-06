#include<iostream>
#include<string>
#include<fstream>

using namespace std;

namespace sdl{

    typedef struct people{
        int val;
        struct people* pnext;
        people();
    }node;

    people::people() :val(0), pnext(0){}

    void printlist(node* phead)
    {
        node* p = phead;
        while (p)
        {
            cout << p->val << " ";
            p = p->pnext;
        }
        cout << endl;
    }

    node* create()
    {
        node* phead;
        phead = new node;
        int num;
        cout << "input informations in next line." << endl;
        cin >> num;
        phead->val = num;
        //phead->pnext = NULL;
        node* p = phead;

        while (cin >> num)
        {
            node* tp = new node;
            p->pnext = tp;
            tp->val = num;
            p = tp;
            //tp->pnext = NULL;
            if (cin.get() == '\n')break;
        }
        return phead;
    }


    node* create_from_file(const char* file)
    {
        std::ifstream in;
        in.open(file, std::ios::in);

        node* phead = 0;
        node* tp = 0;
        node* p = 0;
        int is_head = 1;
        int num;

        while(in >> num) {
            tp = new node;
            tp->val = num;
            if(is_head){
                phead = tp;
                is_head = 0;
            }else{
                p->pnext = tp;
            }
            p = tp;
        }
        return phead;
    }

    int length(node* phead)
    {
        int len = 0;
        node* p = phead;
        while (p)
        {
            p = p->pnext;
            len++;
        }

        return len;
    }

    void replace_val(node* phead, int origin, int target)
    {
        node* p = phead;
        while (p)
        {
            if (p->val == origin)
                p->val = target;

            p = p->pnext;
        }
    }

    node* del_nth_node(int n, node* phead)
    {
        if (n == 1)
        {
            node* phead_new = phead->pnext;
            delete phead;
            return phead_new;
        }

        int len = length(phead);
        if (n > len)
        {
            cout << "overflow index!" << endl;
            return phead;
        }

        if (n == len)
        {
            node*p = phead;
            int ct = 1;
            while (p && ct != len - 1)
            {
                p = p->pnext;
                ++ct;
            }
            delete p->pnext;
            p->pnext = NULL;
            return phead;
        }

        node* p = phead;
        int ct = 1;
        while (ct != n - 1)
        {
            p = p->pnext;
            ++ct;
        }

        node* tp = p->pnext;
        p->pnext = p->pnext->pnext;
        delete tp;
        return phead;
    }

    node* del_val(int value, node* phead)
    {
        node* phead_new = phead;
        if (phead->val == value)
        {
            phead_new = phead->pnext;
            delete phead;
            return del_val(value, phead_new);
        }

        node* p = phead_new;
        while (p && p->pnext && p->pnext->pnext)
        {
            if (p->pnext->val == value)
            {
                node* tp = p->pnext;
                p->pnext = p->pnext->pnext;
                delete tp;
            }
            else{ p = p->pnext; }
        }

        if (p->pnext->val == value)
        {
            delete p->pnext->pnext;
            p->pnext = NULL;
        }
        return phead_new;

    }

    void ins_val_after_n(int n, node* phead, int value)
    {
        int len = length(phead);
        if (n > len || n < 1)
        {
            cout << "overflow or negative index!" << endl;
            return;
        }

        int ct = 1;
        node* p = phead;
        while (p && ct != n)
        {
            p = p->pnext;
            ++ct;
        }

        node* tp = new node;
        tp->val = value;

        tp->pnext = p->pnext;
        p->pnext = tp;

    }

    node* ins_val_before_n(int n, node* phead, int value)
    {
        int len = length(phead);
        if (n > len || n < 1)
        {
            cout << "overflow or negative index!" << endl;
            return phead;
        }

        if (n == 1)
        {
            node* tp = new node;
            tp->val = value;
            tp->pnext = phead;
            return tp;
        }

        int ct = 1;
        node* p = phead;
        while (p && ct != n - 1)
        {
            p = p->pnext;
            ++ct;
        }

        node* tp = new node;
        tp->val = value;

        tp->pnext = p->pnext;
        p->pnext = tp;
        return phead;
    }

    node* reverse_link(node* phead)
    {
        node* org = phead;

        node* p = phead;

        node* headnow = phead;

        while (p)
        {
            if (p == phead)
            {
                p = p->pnext;
                continue;
            }
            else{
                node* tp = new node;
                tp->val = p->val;
                tp->pnext = headnow;
                headnow = tp;
            }
            p = p->pnext;
        }

        org->pnext = NULL;

        return headnow;
    }

    void sort_link(node* phead)
    {
        if (!phead || !phead->pnext)
            return;

        node* p = phead;
        int len = length(phead);
        int tmp;

        for (int j = 1; j < len; j++)
        {
            p = phead;

            for (int i = 0; i < len - j; i++)
            {
                if (p->val > p->pnext->val)
                {
                    tmp = p->val;
                    p->val = p->pnext->val;
                    p->pnext->val = tmp;
                }
                p = p->pnext;
            }
        }

    }


}
