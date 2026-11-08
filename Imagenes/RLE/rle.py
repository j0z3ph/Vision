def rle_encode(data):
    if not data:
        return []
    
    encoded = []
    current_val = data[0]
    count = 1
    
    for pixel in data[1:]:
        if pixel == current_val:
            count += 1
        else:
            encoded.append((current_val, count))
            current_val = pixel
            count = 1
            
    encoded.append((current_val, count))
    return encoded

def rle_decode(encoded_data):
    decoded = []
    for val, count in encoded_data:
        decoded.extend([val] * count)
    return decoded

# Ejemplo con una fila de una imagen en blanco y negro (0: negro, 1: blanco)
fila_imagen = [0, 0, 0, 1, 1, 1, 1, 0, 0, 1]
comprimido = rle_encode(fila_imagen)
descomprimido = rle_decode(comprimido)

print("Original:", fila_imagen)
print("Comprimido (RLE):", comprimido)
print("Descomprimido:", descomprimido)
