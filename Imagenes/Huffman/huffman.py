from collections import Counter
import heapq

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None
        self.isleaf = True
        
    def __lt__(self, other):
        return self.freq < other.freq

def build_priority_queue(frequencies):
    priority_queue = [Node(char, freq) for char, freq in frequencies.items()]
    heapq.heapify(priority_queue)
    return priority_queue

def frequency_analysis(data):
    frequencies = Counter(data)
    return frequencies

def build_huffman_tree(priority_queue):
    while len(priority_queue) > 1:
        left = heapq.heappop(priority_queue)
        right = heapq.heappop(priority_queue)
        merged = Node(left.char + right.char, left.freq + right.freq)
        merged.left = left
        merged.right = right
        merged.isleaf = False
        heapq.heappush(priority_queue, merged)
        print("Priority Queue:", [(node.char, node.freq) for node in priority_queue])
    return heapq.heappop(priority_queue)

def generate_huffman_codes(node, current_code="", codes={}):
    if node is None:
        return
    if node.isleaf:
        codes[node.char] = current_code
    generate_huffman_codes(node.left, current_code + "0", codes)
    generate_huffman_codes(node.right, current_code + "1", codes)
    return codes

def encode_data(data, huffman_codes):
    encoded_data = ''.join(huffman_codes[char] for char in data)
    return encoded_data

def decode_data(encoded_data, huffman_tree):
    decoded_data = []
    current_node = huffman_tree
    for bit in encoded_data:
        if bit == '0':
            current_node = current_node.left
        else:
            current_node = current_node.right
        if current_node.isleaf:
            decoded_data.append(current_node.char)
            current_node = huffman_tree
    return ''.join(decoded_data)

data = "ABRACADABRA"
frequencies = frequency_analysis(data)
print("Frequencies:", frequencies)

priority_queue = build_priority_queue(frequencies)
print("Priority Queue:", [(node.char, node.freq) for node in priority_queue])

huffman_tree = build_huffman_tree(priority_queue)
print("Huffman Tree Root Frequency:", (huffman_tree.char, huffman_tree.freq))

huffman_codes = generate_huffman_codes(huffman_tree)
print("Huffman Codes:", huffman_codes)

encoded_data = encode_data(data, huffman_codes)
print("Encoded Data:", encoded_data)
original_size = len(data) * 8
compressed_size = len(encoded_data)
compression_ratio = compressed_size / original_size
percentage_compression = (1 - compression_ratio) * 100
print("Original Size (bits):", original_size)
print("Compressed Size (bits):", compressed_size)
print("Compression Ratio:", compression_ratio)
print("Percentage Compression:", percentage_compression)


decoded_data = decode_data(encoded_data, huffman_tree)
print("Decoded Data:", decoded_data)