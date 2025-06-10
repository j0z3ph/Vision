import socket
import threading
import socket, cv2, pickle, struct


class Cliente:
    name = ""
    conn = None
    addr = None


def clientthread(conn, addr):
    # conn.send(bytes(f"Bienvenido {addr}\n", 'utf-8'))
    client_type = conn.recv(BUFFER_SIZE).decode()
    if(client_type == "Emisor"):
        conn.send(b"OK")
        while True:
            data = b""
            payload_size = struct.calcsize("Q")
            while len(data) < payload_size:
                packet = conn.recv(BUFFER_SIZE)
                if not packet:
                    break
                data += packet
            packed_msg_size = data[:payload_size]
            data = data[payload_size:]
            msg_size = struct.unpack("Q", packed_msg_size)[0]

            while len(data) < msg_size:
                data += conn.recv(BUFFER_SIZE)
            
            message = struct.pack("Q", len(data)) + data
            for client in list_of_clients:
                if client.conn != conn:
                    try:
                        client.conn.sendall(message)
                    except Exception as e:
                        print(f"An unexpected error occurred: {e}")
                        client.conn.close()
                        list_of_clients.remove(client)
                        
            conn.send(b"OK") # Confirmacion al emisor
            
    elif client_type == "Receiver":
        conn.send(b"OK")
        while True:
            msg = conn.recv(BUFFER_SIZE).decode()
            if msg:
                for client in list_of_clients:
                    if client.conn != conn:
                        client.conn.sendall(msg)
                    

if __name__ == "__main__":
    host = socket.gethostname()  # Esta función nos da el nombre de la máquina
    # host = "0.0.0.0"
    port = 65535
    BUFFER_SIZE = 4 * 1024
    # Creamos un socket TCP
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((host, port))
    server.listen(100)  # Escuchamos hasta 100 clientes
    list_of_clients = []  # Lista de clientes conectados
    print(f"Escuchando conexiones en: {(host, port)}")
    try:
        while True:
            conn, addr = server.accept()
            nuevo_cliente = Cliente()
            nuevo_cliente.conn = conn
            nuevo_cliente.addr = addr
            # list_of_clients.append(conn)  # Agregamos a la lista de clientes
            list_of_clients.append(nuevo_cliente)  # Agregamos a la lista de clientes
            print(f"Cliente conectado: {addr}")
            # Creamos y ejecutamos el hilo para atender al cliente
            threading.Thread(
                target=clientthread, args=(conn, addr), daemon=True
            ).start()
    except KeyboardInterrupt:
        print("Caught keyboard interrupt, exiting")
    finally:
        conn.close()
        server.close()
    print("Conexión terminada.")
