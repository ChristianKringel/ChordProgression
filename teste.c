#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHORDS 10
#define MAX_CHORD_LENGTH 10
#define ALPHABET_SIZE 10 // Ajuste conforme necessário para o número de acordes

typedef struct ChordNode {
    struct ChordNode *children[ALPHABET_SIZE];
    int isEndOfProgression;
    char *keys[MAX_CHORDS];
    int keyCount;
} ChordNode;

typedef struct ChordTrie {
    ChordNode *root;
} ChordTrie;

// Função para criar um novo nó
ChordNode* createNode() {
    ChordNode *node = (ChordNode *)malloc(sizeof(ChordNode));
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    node->isEndOfProgression = 0;
    node->keyCount = 0;
    return node;
}

// Função para criar uma nova Trie
ChordTrie* createTrie() {
    ChordTrie *trie = (ChordTrie *)malloc(sizeof(ChordTrie));
    trie->root = createNode();
    return trie;
}

// Função para mapear acordes para índices
int chordToIndex(const char *chord) {
    if (strcmp(chord, "C") == 0) return 0;
    if (strcmp(chord, "Dm") == 0) return 1;
    if (strcmp(chord, "Em") == 0) return 2;
    if (strcmp(chord, "F") == 0) return 3;
    if (strcmp(chord, "G") == 0) return 4;
    if (strcmp(chord, "Am") == 0) return 5;
    if (strcmp(chord, "Bdim") == 0) return 6;
    if (strcmp(chord, "G#m") == 0) return 7;
    if (strcmp(chord, "C#") == 0) return 8;
    if (strcmp(chord, "D#m") == 0) return 9;
    // Adicione outros acordes conforme necessário
    return -1; // Retorna -1 para acordes desconhecidos
}

// Função para inserir uma progressão na Trie
void insert(ChordTrie *trie, const char *progression[], int size, const char *key) {
    ChordNode *node = trie->root;
    for (int i = 0; i < size; i++) {
        int index = chordToIndex(progression[i]);
        if (index == -1) continue; // Ignora acordes desconhecidos
        if (node->children[index] == NULL) {
            node->children[index] = createNode();
        }
        node = node->children[index];
        // Adiciona o tom ao nó
        node->keys[node->keyCount] = strdup(key);
        node->keyCount++;
    }
    node->isEndOfProgression = 1;
}

// Função auxiliar para buscar as tonalidades possíveis
void searchRecursive(ChordNode *node, const char *chords[], int index, char *result[], int *resultCount) {
    if (index < 0) {
        // Adiciona todas as tonalidades do nó atual
        for (int i = 0; i < node->keyCount; i++) {
            result[*resultCount] = strdup(node->keys[i]);
            (*resultCount)++;
        }
        return;
    }

    int chordIndex = chordToIndex(chords[index]);
    if (chordIndex != -1 && node->children[chordIndex] != NULL) {
        searchRecursive(node->children[chordIndex], chords, index - 1, result, resultCount);
    }
}

// Função para determinar as tonalidades possíveis
void determineKeys(ChordTrie *trie, const char *chords[], int size, char *result[], int *resultCount) {
    searchRecursive(trie->root, chords, size - 1, result, resultCount);
}

// Função para imprimir resultados
void printResults(char *result[], int count) {
    if (count == 0) {
        printf("Nenhuma tonalidade encontrada.\n");
    }
    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
}

int main() {
    // Inicializando a Trie
    ChordTrie *trie = createTrie();

    // Exemplo de progressões
    const char *progressions[][7] = {
        {"C", "Dm", "Em", "F", "G", "Am", "Bdim"},
        {"G", "Am", "Bm", "C", "D", "Em", "F#dim"},
        {"D", "Em", "F#m", "G", "A", "Bm", "C#dim"},
        {"A", "Bm", "C#m", "D", "E", "F#m", "G#dim"},
        {"E", "F#m", "G#m", "A", "B", "C#m", "D#dim"}
    };
    const char *keys[] = {"C", "G", "D", "A", "E"};

    // Inserindo progressões na Trie
    for (int i = 0; i < 5; i++) {
        insert(trie, progressions[i], 7, keys[i]);
    }

    // Testando com exemplos
    const char *testChords[] = {"C", "Dm", "G", "Am"};
    char *result[MAX_CHORDS];
    int resultCount = 0;

    determineKeys(trie, testChords, 4, result, &resultCount);
    printf("Tonalidades possíveis:\n");
    printResults(result, resultCount);

    // Liberar memória
    for (int i = 0; i < MAX_CHORDS; i++) {
        if (trie->root->children[i]) {
            free(trie->root->children[i]);
        }
    }
    free(trie->root);
    free(trie);

    return 0;
}
