/**  TODO: port to C 
c test has problem , strange error message
   */
class AllOne {
  struct Bucket { int v; unordered_set<string> ks; };
  unordered_map<string, list<Bucket>::iterator> a;
  list<Bucket> b;
public:
  AllOne() {
    b.push_front({0, {}});
  }
  void inc(string key) {
    if (! a.count(key)) {
      a[key] = b.begin();
      b.begin()->ks.insert(key);
    }
    auto y = a[key], x = y++;
    if (y == b.end() || x->v+1 < y->v)
      y = b.insert(y, {x->v+1, {}});
    a[key] = y;
    y->ks.insert(key);
    x->ks.erase(key);
    if (x->ks.empty() && x->v)
      b.erase(x);
  }
  void dec(string key) {
    if (a.count(key)) {
      auto y = a[key], x = y--;
      if (x->v > 1) {
        if (x == b.begin() || y->v < x->v-1)
          y = b.insert(x, {x->v-1, {}});
        a[key] = y;
        y->ks.insert(key);
      } else
        a.erase(key);
      x->ks.erase(key);
      if (x->ks.empty())
        b.erase(x);
    }
  }
  string getMaxKey() {
    return b.size() == 1 ? "" : *b.rbegin()->ks.begin();
  }
  string getMinKey() {
    return b.size() == 1 ? "" : *(++b.begin())->ks.begin();
  }
};
