class ChordNode: # contrução da classe ChordNode
    def __init__(self):
        self.children = {}
        self.is_end_of_progression = False

class ChordTrie: # construção da classe ChordTrie
    def __init__(self):
        self.root = ChordNode()
    
    def insert(self, progression):  # inserção de progressão de acordes
        node = self.root
        for chord in progression:
            if chord not in node.children:
                node.children[chord] = ChordNode() # se o acorde não estiver na progressão, insere
            node = node.children[chord]
        node.is_end_of_progression = True

    def search(self, progression): # busca de progressão de acordes
        node = self.root
        for chord in progression:
            if chord not in node.children:
                return False
            node = node.children[chord] # se a progressão estiver na árvore, retorna True
        return node.is_end_of_progression
    
    def starts_with(self, prefix): # busca de prefixos de acordes
        node = self.root
        for chord in prefix:
            if chord not in node.children: 
                return False
            node = node.children[chord] # se o acorde estiver na progressão, retorna True
        return True


progressions = {
    "C": ["C", "Dm", "Em", "F", "G", "Am", "Bdim"],
    "C#": ["C#", "D#m", "E#m", "F#", "G#", "A#m", "Cdim"],
    "D": ["D", "Em", "F#m", "G", "A", "Bm", "C#dim"],
    "D#": ["D#", "Fm", "Gm", "G#", "A#", "Cm", "Ddim"],
    "E": ["E", "F#m", "G#m", "A", "B", "C#m", "D#dim"],
    "F": ["F", "Gm", "Am", "A#", "C", "Dm", "Edim"],
    "F#": ["F#", "G#m", "A#m", "B", "C#", "D#m", "Fdim"],
    "G": ["G", "Am", "Bm", "C", "D", "Em", "F#dim"],
    "G#": ["G#", "A#m", "Cm", "C#", "D#", "Fm", "Gdim"],
    "A": ["A", "Bm", "C#m", "D", "E", "F#m", "G#dim"],
    "A#": ["A#", "Cm", "Dm", "D#", "F", "Gm", "Adim"],
    "B": ["B", "C#m", "D#m", "E", "F#", "G#m", "A#dim"]
}

chord_trie = ChordTrie()

for key, progression in progressions.items():
    chord_trie.insert(progression)


# Inserindo progressões de acordes
#chord_trie.insert(["C", "Dm", "Em", "F", "G", "Am", "Bdim"])
#chord_trie.insert(["G", "Am", "Bm", "C", "D", "Em", "F#dim"])

# Buscando por uma progressão de acordes
print(chord_trie.search(["C", "Dm", "Em", "F", "G", "Am", "Bdim"]))  # True
print(chord_trie.search(["C", "Dm", "Em"]))  # False
print(chord_trie.search(["G", "Am", "Bm", "C", "D", "Em", "F#dim"])) 
#faça um para false 
print("Prefixos de acordes:")

print(chord_trie.starts_with(["C", "F#"]))  # False
print(chord_trie.starts_with(["C", "Dm"]))  # True
print(chord_trie.starts_with(["G", "A#m"]))  # False

