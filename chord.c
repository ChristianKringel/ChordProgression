#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10              // Número máximo de acordes que um nó pode ter como filhos (ajuste conforme necessário)
#define MAX_ACORDE_LEN 10 // Comprimento máximo do acorde, por exemplo, "C#m"

typedef struct TrieNode
{
    char acorde[MAX_ACORDE_LEN];
    struct TrieNode *children[N];
    int is_leaf;
} TrieNode;

TrieNode *create_node(const char *acorde)
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    strncpy(node->acorde, acorde, MAX_ACORDE_LEN);
    node->acorde[MAX_ACORDE_LEN - 1] = '\0'; // fim null
    node->is_leaf = 0;
    for (int i = 0; i < N; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

void insert(TrieNode *root, const char *acorde)
{
    TrieNode *node = root;
    for (int i = 0; i < N; i++)
    {
        if (node->children[i] == NULL)
        {
            node->children[i] = create_node(acorde);
            printf("Inserido '%s' no indice %d\n", acorde, i);
            return;
        }
        else if (strcmp(node->children[i]->acorde, acorde) == 0)
        {
            printf("Acorde '%s' ja existe\n", acorde);
            return;
        }
    }
}

void insert_scale(TrieNode *root, const char *scale_root, const char *scale[], int size)
{
    TrieNode *node = root;

    //
    for (int i = 0; i < N; i++)
    {
        if (node->children[i] != NULL && strcmp(node->children[i]->acorde, scale_root) == 0)
        {
            node = node->children[i];
            break;
        }
    }

    //
    if (node == root)
    {
        node = create_node(scale_root);
        for (int i = 0; i < N; i++)
        {
            if (root->children[i] == NULL)
            {
                root->children[i] = node;
                break;
            }
        }
    }

    // inserindo os acordes filhos (da escalas) na trie
    for (int i = 0; i < size; i++)
    {
        TrieNode *child = create_node(scale[i]);
        for (int j = 0; j < N; j++)
        {
            if (node->children[j] == NULL)
            {
                node->children[j] = child;
                printf("Inserido '%s' no indice %d\n", scale[i], j);
                break;
            }
            else if (strcmp(node->children[j]->acorde, scale[i]) == 0)
            {
                printf("Acorde '%s' ja existe\n", scale[i]);
                break;
            }
        }
    }
}

void print_trie(TrieNode *root, int level)
{
    if (root == NULL)
    {
        return;
    }

    // espaco em branco pra espacar cada escala
    for (int i = 0; i < level; i++)
    {
        printf("  ");
    }

    // printa no atual
    if (strlen(root->acorde) > 0)
    {
        printf("|-- %s\n", root->acorde);
    }

    // printando recursivamente
    for (int i = 0; i < N; i++)
    {
        if (root->children[i] != NULL)
        {
            print_trie(root->children[i], level + 1);
        }
    }
}


int main()
{
    TrieNode *root = create_node(""); // Raiz vazia

    // Setando escalas
    const char *C_scale[] = {"C", "Dm", "Em", "F", "G", "Am", "Bdim"};
    const char *Csharp_scale[] = {"C#", "D#m", "E#m", "F#", "G#", "A#m", "Cdim"};
    const char *D_scale[] = {"D", "Em", "F#m", "G", "A", "Bm", "C#dim"};
    const char *Dsharp_scale[] = {"D#", "Fm", "Gm", "G#", "A#", "Cm", "Ddim"};
    const char *E_scale[] = {"E", "F#m", "G#m", "A", "B", "C#m", "D#dim"};
    const char *F_scale[] = {"F", "Gm", "Am", "A#", "C", "Dm", "Edim"};
    const char *Fsharp_scale[] = {"F#", "G#m", "A#m", "B", "C#", "D#m", "Fdim"};
    const char *G_scale[] = {"G", "Am", "Bm", "C", "D", "Em", "F#dim"};
    const char *Gsharp_scale[] = {"G#", "A#m", "Cm", "C#", "D#", "Fm", "Gdim"};
    const char *A_scale[] = {"A", "Bm", "C#m", "D", "E", "F#m", "G#dim"};
    const char *Asharp_scale[] = {"A#", "Cm", "Dm", "D#", "F", "Gm", "Adim"};
    const char *B_scale[] = {"B", "C#m", "D#m", "E", "F#", "G#m", "A#dim"};

    // Inserindo as escalas na trie
    insert_scale(root, "C", C_scale, 7);
    insert_scale(root, "C#", Csharp_scale, 7);
    insert_scale(root, "D", D_scale, 7);
    insert_scale(root, "D#", Dsharp_scale, 7);
    insert_scale(root, "E", E_scale, 7);
    insert_scale(root, "F", F_scale, 7);
    insert_scale(root, "F#", Fsharp_scale, 7);
    insert_scale(root, "G", G_scale, 7);
    insert_scale(root, "G#", Gsharp_scale, 7);
    insert_scale(root, "A", A_scale, 7);
    insert_scale(root, "A#", Asharp_scale, 7);
    insert_scale(root, "B", B_scale, 7);

    // Imprimir a estrutura da Trie
    printf("Estrutura da Trie:\n");
    print_trie(root, 0);

    printf("\n");
    //printf("Buscando acordes:\n");
    //wich_scale(root, "Edim");

    return 0;
}
