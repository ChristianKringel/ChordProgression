class ChordNode:
    def __init__(self):
        self.children = {}
        self.keys = set()  # Conjunto para armazenar os tons

class ChordTrie:
    def __init__(self):
        self.root = ChordNode()

    def insert(self, progression, key):
        node = self.root
        for chord in progression:
            if chord not in node.children:
                node.children[chord] = ChordNode()
            node = node.children[chord]
            node.keys.add(key)  # Adiciona o tom em cada nó da progressão

    def search_keys(self, chords):
        def search_recursive(node, chord_list, index):
            # Se a sequência terminou, acumula todas as tonalidades possíveis
            if index == len(chord_list):
                return node.keys

            current_chord = chord_list[index]
            result = set()

            # Se o acorde atual existir, continua a busca na subárvore correspondente
            if current_chord in node.children:
                result.update(search_recursive(node.children[current_chord], chord_list, index + 1))

            return result

        # Inicia a busca a partir da raiz e para a sequência de acordes
        return list(search_recursive(self.root, chords, 0))

# Exemplo de progressões
progressions = {
    "C": ["C", "Dm", "Em", "F", "G", "Am", "Bdim"],
    "G": ["G", "Am", "Bm", "C", "D", "Em", "F#dim"],
    "D": ["D", "Em", "F#m", "G", "A", "Bm", "C#dim"],
    "A": ["A", "Bm", "C#m", "D", "E", "F#m", "G#dim"],
    "E": ["E", "F#m", "G#m", "A", "B", "C#m", "D#dim"],
}

# Construindo a trie com as progressões e seus tons
chord_trie = ChordTrie()

for key, progression in progressions.items():
    chord_trie.insert(progression, key)

# Função para determinar os tons possíveis
def determine_keys(chords):
    return chord_trie.search_keys(chords)

# Testando com exemplos
print(determine_keys(["C", "Dm", "Em", "F", "G", "Am", "Bdim"]))  # ['C']
print(determine_keys(["G", "Am", "Bm", "C"]))  # ['G']
print(determine_keys(["D", "F#m", "A"]))  # ['D']
print(determine_keys(["A", "E", "F#m"]))  # ['A']
print(determine_keys(["C", "Dm", "G", "Am"]))  # Deve retornar ['C', 'G']
print(determine_keys(["C", "F#", "G"]))  # []
