#include<stdio.h>
#include<iostream>
#include"binarysearchtree.hpp"

//平均查找长度ASL
//层数：L, 总节点个数：M
//第i层的节点个数: Ni
//N1+N2+...+NL = M

//       L 
//ASL = ∑i*Ni  /  M
//      i=1

//平衡二叉树
//平衡因子 BF= H(left) - H(right)
//AVL树：任一节点满足 |BF| <= 1

//设n(h)为高度为h的AVL树的最少节点数，则
//n(h) = n(h-1)+n(h-2)+1（斐波那契数列：F[0]=1,F[1]=1,F[i]=F[i-1]+F[i-2]）
//n(h) = F[h+2]-1
//给定节点数为N的AVL树的最大高度是O(log2N)

//平衡二叉树的调整
//几种情况：
/*
Ax表示A节点的x子树(左或者右)
括号中的数字表示当前节点的左右高度差
箭头或逗号表示插入结点后的变化
☆表示插入的结点
多个五星表示任一位置
*****************************************************************************
	A(-1)->(-2)      ---->        B(0)
   / \                           / \
 Al	  B(0)->(-1)             (0)A   Br
     / \                       / \  ☆
    Bl Br                     Al Bl
	   ☆
插入☆,产生不平衡，发现者是A, ☆在发现者右子树的右边，因此叫做RR插入，需要RR旋转（右单旋）
****************************************************************************
	    A 1,2      ---->         B(0)
       / \                       / \
 0,1  B	  Ar                    Bl  A(0)
     / \                        ☆ / \ 
    Bl Br                         Br Ar
	☆
插入☆,产生不平衡，发现者是A, ☆在发现者左子树的左边，因此叫做LL插入，需要LL旋转（左单旋）
****************************************************************************
	    A 1,2      ---->         C(0)
       / \                       /  \
 0,-1 B	  Ar            0 or 1  B    A -1 or 0
     / \                       / \   / \ 
    Bl  C 0,±1               Bl Cl Cr Ar
	   / \                       ☆ ☆
	  Cl Cr
	  ☆ ☆
插入☆,产生不平衡，发现者是A, ☆在发现者左子树的右边，因此叫做LR插入，需要LR旋转
****************************************************************************
	    A 1,-2      ---->         C(0)
       / \                       /  \
     Al   B 0,1	        0 or 1  A    B -1 or 0
         / \                   / \   / \ 
  0,±1 C   Br                Al Cl Cr Br
	   / \                       ☆ ☆
	  Cl Cr
	  ☆ ☆
插入☆,产生不平衡，发现者是A, ☆在发现者右子树的左边，因此叫做RL插入，需要RL旋转
****************************************************************************
*/

namespace bbt{


}
