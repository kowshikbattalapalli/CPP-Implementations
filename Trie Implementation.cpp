#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    char data;
    vector<Node*> next;
    bool isTerminal;

    Node(char d, bool it) {
        data = d;
        next.resize(26, NULL);
        isTerminal = it;
    }
};

class Trie {
public:
    Node* root = new Node('@', false);

    void insert(string word) {
        Node* temp = root;

        for (int i = 0; i < word.size(); i++) {
            int idx = word[i] - 'a';

            if (temp->next[idx]) {
                temp = temp->next[idx];
            }
            else {
                temp->next[idx] = new Node(word[i], false);
                temp = temp->next[idx];
            }
        }

        temp->isTerminal = true;
    }

    bool search(string word) {
        Node* temp = root;
        int n = word.size();

        for (int i = 0; i < n; i++) {
            int idx = word[i] - 'a';

            if (temp->next[idx]) {
                temp = temp->next[idx];
            }
            else {
                return false;
            }
        }

        return temp->isTerminal;
    }

    bool prefixSearch(string word) {
        Node* temp = root;
        int n = word.size();

        for (int i = 0; i < n; i++) {
            int idx = word[i] - 'a';

            if (temp->next[idx]) {
                temp = temp->next[idx];
            }
            else {
                return false;
            }
        }

        return true;
    }
};

int main() {
    Trie t;

    t.insert("app");
    t.insert("apple");

    cout << "Searching for apple: "
         << t.search("apple") << endl;

    t.insert("mango");

    cout << "Searching for man: "
         << t.search("man") << endl;

    cout << "Prefix Searching for man: "
         << t.prefixSearch("man") << endl;

    return 0;
}