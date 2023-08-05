#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct TrieNode {
    struct TrieNode *children[26];
    int count;
};
struct Trie {
    struct TrieNode *root;
};
struct TrieNode *createTrieNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    node->count = 0;
    return node;
}
void insert(struct Trie *pTrie, char *word) {
    if (pTrie == NULL || word == NULL) {
        return;
    }

    struct TrieNode *current = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }
    current->count++;
}
int numberOfOccurrences(struct Trie *pTrie, char *word) {
    if (pTrie == NULL || word == NULL) {
        return 0;
    }

    struct TrieNode *current = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            return 0;
        }
        current = current->children[index];
    }
    return current->count;
}
void deallocateNodes(struct TrieNode *node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        deallocateNodes(node->children[i]);
    }
    free(node);
}
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    deallocateNodes(pTrie->root);
    free(pTrie);
    return NULL;
}
struct Trie *createTrie() {
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    pTrie->root = createTrieNode();
    return pTrie;
}

int readDictionary(char *filename, char **pInWords) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening the file: %s\n", filename);
        exit(EXIT_FAILURE);
    }int numWords = 0;
    char word[256];
    fgets(word, sizeof(word), fp);
    while (fgets(word, sizeof(word), fp)) {
        word[strcspn(word, "\n")] = '\0';
        pInWords[numWords] = strdup(word);
        numWords++;
    }

    fclose(fp);
    return numWords;
}



int main(void)
{
	char *inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("C:\\Users\\blueg\\CLionProjects\\lab_10\\dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}

	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}