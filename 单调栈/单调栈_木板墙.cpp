#include<cstdio>
#include<stack>

using namespace std;

typedef long long ll;

struct p {
    ll h;
    int pre, pos; //当前木板前面的连续的比他高的木板的个数
    p(ll _h, int _pre, int _pos) {
        h = _h;
        pre = _pre;
        pos = _pos;
    }
};
int N;
stack<p> S;
ll res = 0;

int main() {
    while(~scanf("%d",&N) && N) {
        res = 0;
        for(int i = 1; i <= N; i++) {
            ll hgt;
            int pre = 0;
            scanf("%lld",&hgt);
            while(!S.empty() && S.top().h > hgt) {
                p temp = S.top();
                S.pop();
                pre += temp.pre + 1;
                // pre的值 = 所有比当前高度高的栈顶元素的pre的和 + 元素的个数
                res = max(res, temp.h*(i - temp.pos + temp.pre));
                //以temp为最低木板，往左看最大长度为temp.pre，往右看最大长度为i - temp.pos
                //（因为i位置是第一个比单调栈顶元素高度低的位置）
            }
            S.push(p(hgt, pre, i));
        }
        while(!S.empty()) {
            p temp = S.top();
            S.pop();
            res = max(res, temp.h*(N+1 - temp.pos + temp.pre));
            //后面没有比栈顶元素低的木板，所以往右看为 N + 1 - temp.pos
            
        }
        printf("%lld\n",res);
    }
    return 0;
}