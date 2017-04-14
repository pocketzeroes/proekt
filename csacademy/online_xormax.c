#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ nmax = 100010};
int n, v[nmax], xs[nmax], pos[nmax], left[nmax], right[nmax], res[nmax];
int f[nmax], sz[nmax];
bool active[nmax];

typedef struct TrieS
{
    struct TrieS*son[2];
}Trie;
Trie*newTrie()
{
    Trie*rez=malloc(sizeof(Trie));
    rez->son[0] = 0;
    rez->son[1] = 0;
    return rez;
}

Trie *T[nmax];

void ins(Trie *t, int nr, int bit)
{
    if (bit == 0)
        return ;
    int b = (nr & (1 << (bit - 1))) > 0;
    if (t -> son[b] == 0)
        t -> son[b] = newTrie();
    return ins(t -> son[b], nr, bit - 1);
}
int findXor(Trie *t, int nr, int bit)
{
    if (bit == 0) return 0;
    int b = (nr & (1 << (bit - 1))) > 0;
    if (b == 0)
    {
        if (t -> son[1]) return (1 << (bit - 1)) + findXor(t -> son[1], nr, bit - 1);
        else return findXor(t -> son[0], nr, bit - 1);
    }else
    {
        if (t -> son[0]) return (1 << (bit - 1)) + findXor(t -> son[0], nr, bit - 1);
        else return findXor(t -> son[1], nr, bit - 1);
    }
}
int root(int x)
{
    int y, p;
    for (p = x; p != f[p]; p = f[p]);
    for (; x != p ;)
    {
        y = f[x];
        f[x] = p;
        x = y;
    }
    return p;
}
void unite(int rx, int ry)
{
    if (sz[rx] >= sz[ry])
        f[ry] = rx, sz[rx] += sz[ry];
    else
        f[rx] = ry, sz[ry] += sz[rx];
}
int main()
{
    scanf("%i", &n);
    for (int i = 1; i <= n; ++ i)
    {
        scanf("%i", &v[i]);
        xs[i] = xs[i - 1] ^ v[i];
    }
    for (int i = 1; i <= n; ++ i)
        scanf("%i", &pos[i]);
    for (int i = 0; i <= n; ++ i)
        f[i] = i, sz[i] = 1, T[i] = newTrie();
    for (int i = n; i; -- i)
    {
        int p = pos[i];
        active[p] = 1;
        left[i] = right[i] = p;
        if (active[p - 1])
        {
            int rx = root(p), ry = root(p - 1);
            res[i] = max(res[i], findXor(T[ry], xs[p], 30));
            left[i] -= sz[ry];
            res[i] = max(res[i], xs[p] ^ xs[left[i] - 1]);
            unite(rx, ry);
        }
        if (active[p + 1])
        {
            int rx = root(p), ry = root(p + 1);
            res[i] = max(res[i], findXor(T[ry], xs[p], 30));
            right[i] += sz[ry];
            unite(rx, ry);
        }
        int szleft = p - left[i], szright = right[i] - p, rp = root(p);
        if (szleft == 0 && szright == 0)
        {
            ins(T[rp], xs[p], 30);
            res[i] = v[p];
            continue;
        }
        if (rp < p)
        {
            for (int j = p; j <= right[i]; ++ j)
            {
                res[i] = max(res[i], findXor(T[rp], xs[j], 30));
                res[i] = max(res[i], xs[j] ^ xs[left[i] - 1]);
                res[i] = max(res[i], xs[j] ^ xs[p - 1]);
            }
            for (int j = p; j <= right[i]; ++ j)
                ins(T[rp], xs[j], 30);
        }else if (rp > p)
        {
            for (int j = left[i]; j <= p; ++ j)
            {
                res[i] = max(res[i], findXor(T[rp], xs[j - 1], 30));
                res[i] = max(res[i], xs[p] ^ xs[j - 1]);
            }
            for (int j = left[i]; j <= p; ++ j)
                ins(T[rp], xs[j], 30);
        }else
        {
            for (int j = left[i]; j < p; ++ j)
                res[i] = max(res[i], xs[p] ^ xs[j - 1]);
            for (int j = p; j <= right[i]; ++ j)
                res[i] = max(res[i], xs[j] ^ xs[p - 1]);
            for (int j = left[i]; j <= right[i]; ++ j)
                ins(T[rp], xs[j], 30);
        }
        if (right[i] - left[i] + 1 <= 30)
        {
            for (int j = left[i]; j <= right[i]; ++ j)
                for (int k = j; k <= right[i]; ++ k)
                    res[i] = max(res[i], xs[k] ^ xs[j - 1]);
        }
    }
    for (int i = n; i; -- i) res[i] = max(res[i], res[i + 1]);
    for (int i = 1; i <= n; ++ i) printf("%i\n", res[i]);
    return 0;
}



















































