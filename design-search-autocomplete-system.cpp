#include<bits/stdc++.h>
using namespace std;

const int N = 26;
class AutocompleteSystem {
  private:
    struct Node {
        bool is_sentence_;
        int cnt_;
        vector<Node*> children_;
        Node() :is_sentence_(false), cnt_(0){
            for (int i = 0; i < N + 1; ++i)
                children_.push_back(NULL);
        }
    };
    Node *root;
    string cur_sentence_;
    struct Candidate {
        int cnt_;
        string sentence_;
        Candidate(int &cnt, string &sentence) :cnt_(cnt), sentence_(sentence) {};
        bool operator<(const Candidate& cand) const {
            return (cnt_ < cand.cnt_) || (cnt_ == cand.cnt_&&sentence_ > cand.sentence_);
        }
    };
    void AddSentence(const string& sentence, const int& time) {
        Node *cur = root;
        for (const auto& c : sentence) {
            int idx = c - 'a';
            if (c == ' ')
                idx = N;
            if (cur->children_[idx] == NULL)
                cur->children_[idx] = new Node();
            cur = cur->children_[idx];
        }
        cur->is_sentence_ = true;
        cur->cnt_ += time;
    }
    void FindSentences(Node *root, string &sentence, priority_queue<Candidate>& candidates) {
        if (root != NULL&&root->is_sentence_)
            candidates.push(Candidate(root->cnt_, sentence));
        if (root == NULL)
            return;
        for (int i = 0; i < N + 1; ++i) {
            if (root->children_[i] != NULL) {
                if (i == N)
                    sentence.push_back(' ');
                else
                    sentence.push_back('a' + i);
                FindSentences(root->children_[i], sentence, candidates);
                sentence.pop_back();
            }
        }
    }
    void StartWith(priority_queue<Candidate>& candidates) {
        Node *cur = root;
        for (const auto& c : cur_sentence_) {
            int idx = c - 'a';
            if (c == ' ')
                idx = N;
            if (cur->children_[idx] == NULL)
                return;
            cur = cur->children_[idx];
        }
        string sentence = cur_sentence_;
        FindSentences(cur, sentence, candidates);
    }
  public:
    AutocompleteSystem(vector<string> sentences, vector<int> times) {
        root = new Node();
        cur_sentence_ = "";
        for (int i = 0; i < sentences.size(); ++i)
            AddSentence(sentences[i], times[i]);
    }
    vector<string> input(char c) {
        if (c == '#') {
            AddSentence(cur_sentence_, 1);
            cur_sentence_ = "";
            return{};
        }
        else {
            cur_sentence_.push_back(c);
            priority_queue<Candidate> candidates;
            StartWith(candidates);
            if (candidates.empty())
                return{};
            vector<string> ans;
            while (!candidates.empty()) {
                ans.push_back(candidates.top().sentence_);
                candidates.pop();
                if (ans.size() == 3)
                    break;
            }
            return ans;
        }
    }
};
void printarr(vector<string>&arr){
    for(auto el : arr)
        cout<< el << endl;
    cout<< "###############" <<endl;
}
#if 0
int main(){
    vector<string>strs;
    strs.push_back("i love you");
    strs.push_back("island");
    strs.push_back("ironman");
    strs.push_back("i love leetcode");
    vector<int>ints;
    ints.push_back(5);
    ints.push_back(3);
    ints.push_back(2);
    ints.push_back(2);
    AutocompleteSystem*obj = new AutocompleteSystem(strs, ints);
    vector<string> param1 = obj->input('i');puts("out1");printarr(param1);
    vector<string> param2 = obj->input(' ');puts("out2");printarr(param2);
    vector<string> param3 = obj->input('a');puts("out3");printarr(param3);
    vector<string> param4 = obj->input('#');puts("out4");printarr(param4);
}
#endif
/*
out1
i love you
island
i love leetcode
###############
out2
i love you
i love leetcode
###############
out3
###############
out4
###############

*/






















