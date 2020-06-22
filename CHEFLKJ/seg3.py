from collections import defaultdict

# t segment tree
# a array

class node():
    def __init__(self):
        self.c = defaultdict(lambda:0)
        self.d = -1

mx = 100000
t = [node() for _ in range(mx)]

def update_d(v,l,r):

    l2 = (r-l+1)>>1
    if t[v].c[t[2*v].d] > l2:
        t[v].d = t[2*v].d
    elif t[v].c[t[2*v+1].d] > l2:
        t[v].d = t[2*v+1].d
    else:
        t[v].d = -1


def build(v,l,r,a):

    if l==r:
        t[v].c = defaultdict(lambda: 0)
        t[v].c[a[l]] += 1
        t[v].d = a[l]
        return

    mid = (l+r)>>1
    build(2*v, l, mid, a)
    build(2*v+1, mid+1, r, a)

    # update the node
    t[v].c = defaultdict(lambda:0)
    for k,val in t[2*v].c.items(): t[v].c[k] += val
    for k,val in t[2*v+1].c.items(): t[v].c[k] += val
    update_d(v,l,r)


def update(v,l,r,idx,val,oldVal,a):

    if r < idx or idx < l:
        return

    if l == r:
        t[v].c = defaultdict(lambda:0)
        a[idx] = val
        t[v].c[a[idx]] += 1
        t[v].d = a[idx]
        return

    mid = (l+r)>>1
    update(2*v,l,mid,     idx,val,oldVal,a)
    update(2*v+1,mid+1,r, idx,val,oldVal,a)

    # update node
    t[v].c[oldVal] -= 1
    t[v].c[val] += 1
    update_d(v,l,r)


def query(v,l,r,qs,qe,ans):

    if r < qs or qe < l: return

    if qs <= l and r <= qe:
        ans.append(v)
        return

    mid = (l+r)>>1
    query(2*v, l, mid,     qs, qe,ans)
    query(2*v+1, mid+1, r, qs, qe,ans)

def read_int():
    return list(int(x) for x in input().split())

def main():
    n,q = read_int()
    tmp = read_int()
    a = [None]*(n+1)
    a[1:] = tmp
    build(1,1,n,a)

    for _ in range(q):
        typ,x,y = read_int()

        if typ == 1:

            idx,val = x,y
            update(1,1,n,idx,val,a[idx],a)

        else:

            qs,qe = x,y
            ans = []
            query(1,1,n,qs,qe,ans)

            # The potential majority element
            # will necessarily be a majority
            # element in one of the nodes

            l2 = (qe-qs+1)>>1
            found = False
            for i in range(len(ans)):
                count = 0
                for j in range(len(ans)):
                    count += t[ans[j]].c[t[ans[i]].d]
                if count > l2:
                    print("Yes")
                    found = True
                    break

            if not found:
                print("No")

main()
