This is a demo of TCP communication between server and client

To compile the program, run the following in terminal
```
gcc -g -o client client.c
gcc -g -o server server.c
```

To run the program, start the server to wait for the data, and pass in the IP address or host name. For example, for localhost
```
./server 127.0.0.1
```
Run the similar command to client to send data
```
./client 127.0.0.1
```

The data transferred is named as `myfile.txt`