namespace PST {

    const int MAXN = 50010;
    const int M = MAXN * 160;
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
    int query(int root, int l, int r, int s = 1, int t = n) {
        //查詢區間和
        //printf("l=%d r=%d\n",l,r);
        if(l > r) return 0;
        int mid = (s + t) / 2;
        if(l == s && r == t) return c[root];
        else if(r <= mid) return query(lson[root], l, r, s, mid);
        else if(l > mid) return query(rson[root], l, r, mid+1,t);
        else return query(lson[root],l,mid,s,mid) + query(rson[root],mid+1,r,mid+1,t);
    }
}
