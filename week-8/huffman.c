#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256
#define MAX_CODE 100

typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

typedef struct {
    Node *data[MAX_CHAR];
    int size;
} MinHeap;

Node *newNode(char ch, int freq) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

void heapify(MinHeap *h, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < h->size && h->data[left]->freq < h->data[smallest]->freq)
        smallest = left;
    if (right < h->size && h->data[right]->freq < h->data[smallest]->freq)
        smallest = right;
    if (smallest != i) {
        Node *temp = h->data[i];
        h->data[i] = h->data[smallest];
        h->data[smallest] = temp;
        heapify(h, smallest);
    }
}

void insert(MinHeap *h, Node *node) {
    h->data[h->size] = node;
    int i = h->size++;
    while (i && h->data[i]->freq < h->data[(i - 1) / 2]->freq) {
        Node *temp = h->data[i];
        h->data[i] = h->data[(i - 1) / 2];
        h->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Node *extractMin(MinHeap *h) {
    Node *min = h->data[0];
    h->data[0] = h->data[--h->size];
    heapify(h, 0);
    return min;
}

Node *buildHuffmanTree(char chars[], int freq[], int n) {
    MinHeap h;
    h.size = 0;
    for (int i = 0; i < n; i++)
        insert(&h, newNode(chars[i], freq[i]));

    while (h.size > 1) {
        Node *left = extractMin(&h);
        Node *right = extractMin(&h);
        Node *merged = newNode('$', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        insert(&h, merged);
    }
    return extractMin(&h);
}

void generateCodes(Node *root, char code[], int depth, char codes[][MAX_CODE], char chars[], int n) {
    if (!root) return;
    if (!root->left && !root->right) {
        code[depth] = '\0';
        for (int i = 0; i < n; i++)
            if (chars[i] == root->ch)
                strcpy(codes[i], code);
        return;
    }
    code[depth] = '0';
    generateCodes(root->left, code, depth + 1, codes, chars, n);
    code[depth] = '1';
    generateCodes(root->right, code, depth + 1, codes, chars, n);
}

int main() {
    char *text = "AMRITA VISHWA VIDYAPEETHAM CHENNAI CAMPUS";
    int freq[MAX_CHAR] = {0};

    for (int i = 0; text[i]; i++)
        freq[(int)text[i]]++;

    char chars[MAX_CHAR];
    int freqs[MAX_CHAR];
    int n = 0;

    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i] > 0) {
            chars[n] = (char)i;
            freqs[n] = freq[i];
            n++;
        }
    }

    printf("Huffman Coding\n");
    printf("==============\n");
    printf("Input: %s\n\n", text);

    printf("Character Frequencies:\n");
    printf("Char\tFrequency\n");
    for (int i = 0; i < n; i++) {
        if (chars[i] == ' ')
            printf("SPACE\t%d\n", freqs[i]);
        else
            printf("%c\t%d\n", chars[i], freqs[i]);
    }

    Node *root = buildHuffmanTree(chars, freqs, n);

    char codes[MAX_CHAR][MAX_CODE];
    char code[MAX_CODE];
    generateCodes(root, code, 0, codes, chars, n);

    printf("\nHuffman Codes:\n");
    printf("Char\tFreq\tCode\t\tBits\n");
    int totalBits = 0, fixedBits = 0;
    for (int i = 0; i < n; i++) {
        if (chars[i] == ' ')
            printf("SPACE\t%d\t%s\t\t%d\n", freqs[i], codes[i], (int)strlen(codes[i]));
        else
            printf("%c\t%d\t%s\t\t%d\n", chars[i], freqs[i], codes[i], (int)strlen(codes[i]));
        totalBits += freqs[i] * strlen(codes[i]);
        fixedBits += freqs[i] * 8;
    }

    printf("\nTotal characters: %d\n", (int)strlen(text));
    printf("Unique characters: %d\n", n);
    printf("Bits with Huffman encoding: %d\n", totalBits);
    printf("Bits with fixed 8-bit encoding: %d\n", fixedBits);
    printf("Compression ratio: %.2f%%\n", (1.0 - (double)totalBits / fixedBits) * 100);

    return 0;
}