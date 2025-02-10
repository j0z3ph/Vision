import socket, cv2, pickle,struct

client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host_ip = '127.0.0.1' 
port = 65535
client_socket.connect((host_ip,port)) 

# Socket Accept
while True:
    vid = cv2.VideoCapture(0)
    while(vid.isOpened()):
        img,frame = vid.read()
        a = pickle.dumps(frame)
        message = struct.pack("Q",len(a))+a
        client_socket.sendall(message)
        
        cv2.imshow('TRANSMITTING VIDEO',frame)
        key = cv2.waitKey(1) & 0xFF
        if key ==ord('q'):
            client_socket.close()