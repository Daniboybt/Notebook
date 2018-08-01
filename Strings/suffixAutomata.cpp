#include <bits/stdc++.h>
#define MAX 200007
 
using namespace std;
 
struct node{
    int next[27];
    long long link, len;
} sa[2*MAX];
 
int sz, last, n;
string palavra;

void init(){
    sz = 1;
    last = 0;
    sa[0].link = -1;
    sa[0].len = 0;
    for(int i = 0; i < 26; i++) sa[0].next[i] = 0;
}
 
void add(int c){
    int cur = sz++;
    sa[cur].len = sa[last].len + 1LL;
   
    for(int i = 0; i < 26; i++) sa[cur].next[i] = 0;
    for(; last != -1 && !sa[last].next[c]; last = sa[last].link) {
        cout << "link with " << last << endl;
        sa[last].next[c] = cur;
    }
 
    if(last == -1) {
        cout << "end in root\n";
        sa[cur].link = 0;
    }else{
        int q = sa[last].next[c];
        if(sa[q].len == sa[last].len + 1){
            cout << "so close\n";
            sa[cur].link = q;
        }else{
            cout << "clone\n";
            int clone = sz++;
            sa[clone].len = sa[last].len + 1LL;
            sa[clone].link = sa[q].link;
            memcpy(sa[clone].next, sa[q].next, sizeof sa[q].next);
            for(; last != -1 && sa[last].next[c] == q; last = sa[last].link) sa[last].next[c] = clone;
            sa[q].link = sa[cur].link = clone;
        }
    }
    last = cur;
}
 

// Somatório (i , size): length[i] - length[link[i]] = Número de substrings distintas
// Substrings distintas do range de [length[link[i]] + 1, length[i]]

long long sub(){
    long long ans = 0LL;
    for(int i = 1; i < sz; i++){
        if(sa[sa[i].link].len+1 <= palavra.size()){
            if(sa[i].len > palavra.size()) ans -= sa[i].len - palavra.size();
            ans += sa[i].len - sa[sa[i].link].len;
        }
    }
    return ans;
}

int main(){
    cin >> palavra;
    long long ans = 0;
    init();
    for(int i = 0; i < palavra.size(); i++) {
        cout << "letra " << palavra[i] << endl;
        add(palavra[i]-'a');
        cout << "link equals " << sa[sz-1].link << endl;
        cout << "len equals " << sa[sz-1].len << endl;
        cout << "-----------------------\n";
    }
    return 0;
}