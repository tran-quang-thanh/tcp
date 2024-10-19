This is a demo of TCP communication between server and client

To compile the program, run the following in terminal
```
gcc -g -o tcp_client tcp_client.c client.c checksum.c
gcc -g -o tcp_server tcp_server.c server.c checksum.c
```

To run the program, start the server to wait for the data, and pass in the IP address or host name. For example, for localhost
```
./tcp_server 127.0.0.1
```
Run the similar command to client to send data
```
./tcp_client 127.0.0.1
```

The data transferred is named as `myfile.txt`