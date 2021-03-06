/*
 * Matheus Oliveira
 * 15/02/2018
 * KMP.cpp
 * O(M+N)
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 3000000
int prefixVal[MAXN];

// prefixVal[i] armazena o valor do maior prefixo, até o index i, que também é sufixo da mesma substring [1, i]
void buildPrefixFunction(const string &word) {
	prefixVal[0] = prefixVal[1] = 0;
	int j;
	for(int i = 2; i <= ((int) word.size()); i++) {
		j = prefixVal[i-1];
		while(true) {
			if(word[i-1] == word[j]) {
				prefixVal[i] = j+1;
				break;
			}

			if(j == 0) {
				prefixVal[i] = 0;
				break;
			}

			j = prefixVal[j];
		}
	}
}

bool searchSubstr(const string &searchedWord, const string &text) {
	int i, j;
	i = j = 0;

	while(true) {
		if(j == ((int) searchedWord.size())) break;
		if(searchedWord[j] == text[i]) {
			i++;
			j++;
			if(i == ((int) text.size())) return true;
			continue;
		}

		if(i > 0) i = prefixVal[i];
		else j++;
	}

	return false;
}
