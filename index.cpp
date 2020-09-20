#include <iostream>
#include <map>
using namespace std;

struct trie
{
    map<char, struct trie *> nextNodesMap;
    int isEndOfTrie;
    trie()
    {
        char i;
        for (i = 'a'; i <= 'z'; i++)
        {
            nextNodesMap[i] = NULL;
        }
        isEndOfTrie = 0;
    }
};

struct trie *root = NULL;

void insert(string word)
{
    int len = word.length();
    struct trie *itr = root;
    int i;
    for (i = 0; i < len; i++)
    {
        struct trie *nextnode = itr->nextNodesMap[word[i]];
        if (nextnode == NULL)
        {
            nextnode = new trie();
            itr->nextNodesMap[word[i]] = nextnode;
        }
        itr = nextnode;
        if (i == len - 1)
        {
            itr->isEndOfTrie = 1;
        }
    }
}
void showContactsHelperFunctions(struct trie *curNode, string prefix)
{
    if (curNode->isEndOfTrie)
        cout << prefix << endl;

    for (char i = 'a'; i <= 'z'; i++)
    {
        struct trie *nextNode = curNode->nextNodesMap[i];
        if (nextNode != NULL)
            showContactsHelperFunctions(nextNode, prefix + (char)i);
    }
}
void showContacts(string str)
{
    struct trie *prevnode = root;
    string prefix = "";
    int len = str.length();
    int i;
    for (i = 0; i < len; i++)
    {
        prefix += (char)str[i];
        char lastchar = prefix[i];
        struct trie *currnode = prevnode->nextNodesMap[lastchar];
        if (currnode == NULL)
        {
            cout << "no contacts for query" << prefix << "\n";
            i++;
            break;
        }
        cout << "suggestions based on " << prefix << "\n";
        showContactsHelperFunctions(currnode, prefix);
        prevnode = currnode;
    }
}

void insertIntoTrie(string contacts[], int n)
{
    // Initialize root Node
    root = new trie();

    // Insert each contact into the trie
    for (int i = 0; i < n; i++)
        insert(contacts[i]);
}

int main()
{
    // Contact list of the User
    string contacts[] = {"shree", "sagar", "rawat"};

    // Size of the Contact List
    int n = sizeof(contacts) / sizeof(string);

    // Insert all the Contacts into Trie
    insertIntoTrie(contacts, n);

    string query = "shrii";

    showContacts(query);

    return 0;
}
