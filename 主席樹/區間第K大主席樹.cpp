/* ***********************************************
Author        :czw
注：使用了kuangbin大神的主席树模板
************************************************ */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

/*
 * 给出一个序列，查询区间内有多少个不相同的数
 */

namespace PST {

    const int MAXN = 100005;
    const int M = MAXN * 50;
    int tot;
    int T[M],lson[M],rson[M],c[M];
    int n;
    void init(int _n) {
        tot = 0;
        n = _n;
    }
    int build(int l = 1,int r = n)
    {
        int root = tot++;
        c[root] = 0;
        if(l != r)
        {
            int mid = (l+r)>>1;
            lson[root] = build(l,mid);
            rson[root] = build(mid+1,r);
        }
        return root;
    }
    int update(int root,int pos,int val)
    {
        int newroot = tot++, tmp = newroot;
        c[newroot] = c[root] + val;
        int l = 1, r = n;
        while(l < r)
        {
            int mid = (l+r)>>1;
            if(pos <= mid)
            {
                lson[newroot] = tot++; rson[newroot] = rson[root];
                newroot = lson[newroot]; root = lson[root];
                r = mid;
            }
            else
            {
                rson[newroot] = tot++; lson[newroot] = lson[root];
                newroot = rson[newroot]; root = rson[root];
                l = mid+1;
            }
            c[newroot] = c[root] + val;
        }
        return tmp;
    }
    int queryK(int lroot, int rroot, int k) {
        //后缀[l...n],后缀[r+1...n],第k大
        //注意二分的形式要与上面build相同，才能保证区间的对应关系
        int l = 1, r = n, mid;
        while(l < r) {
            mid = (l + r) >> 1;
            if(c[lson[lroot]] - c[lson[rroot]] >= k) {
                r = mid;
                lroot = lson[lroot];
                rroot = lson[rroot];
            }
            else {
                k -= c[lson[lroot]] - c[lson[rroot]];
                l = mid + 1;
                lroot = rson[lroot];
                rroot = rson[rroot];
            }
        }
        return l;
    }

}

const int SIZE = PST::MAXN;
int A[SIZE];
int B[SIZE];
int bc;

int init(int &n) {
    for(int i = 1; i <= n; i++) {
        B[i] = A[i];
    }
    sort(B+1, B+1+n);
    bc = unique(B+1, B+1+n) - B - 1;
}

int Rank(int a) {
    return lower_bound(B+1, B+bc+1, a) - B;
}

int main() {
    int n, q;
    while(~scanf("%d%d",&n,&q)) {
        for(int i = 1; i <= n; i++) {
            scanf("%d",&A[i]);
        }
        init(n);
        PST::init(bc);
        PST::T[n+1] = PST::build();
        for(int i = n; i >= 1; i--) {
            PST::T[i] = PST::update(PST::T[i+1], Rank(A[i]), 1);
        }
        while(q--) {
            int l, r, k;
            scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",B[PST::queryK(PST::T[l],PST::T[r+1],k)]);
        }
    }
}