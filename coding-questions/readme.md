# Coding-Questions

1. Usage of `getsockname`

   - Write a function that return localhost's IP address.
   - If kernel chooses an ephemeral port number for our socket (we called bind() with port number field as 0), how can you obtain the value of port assigned?

2. Write a function `int sockfd_to_family(int sockfd)` that returns the address family of a socket.

3. Write a wrapper Bind that does proper error handling.

4. Write a code segment to handle zombies by using a signal handler?

5. Write a function to change the values of the low water marks of socket send and receive buffers.

6. Write a code segment for server that creates one TCP port and one UDP port, and waits on both of them using select.

7. Write a program for UDP echo client and server that verifies the returned socket address of who sent the reply and ignore any received datagrams that are not from the server the whom the client sent the datagram.

8. Write a client side program that takes service name and hostname as command line arguments. Use predefined functions to convert service name and hostname into appropriate port number and ip address and use this information to establish the connection.

9. Write a TCP client and TCP server (concurrent) implementation in `C/C++`.
   Specification of the client and server are mentioned below:

   - Server is running a service on porr 9012.
   - Client connects to that service of the server.
   - Server prints the IP address and port number of each connected client.
   - Client gets input (string) from user and sends it to the server.
   - Server prints the string on its terminal and sends the same back to the client.
   - Client receives the string and displays on the terminal.
   - Client disconnects from the server

10. Write a TCP client and TCP server implementation in C/C++. Specification client and server are mentioned below:

    - Server is running a service on port 11002.
    - Client connects to that service of the server.
    - Server prints the IP address and port number of each connected client.
    - Client gets an integer input from user and sends it to the server.
    - Server calculates the factorial of the number and sends it back to client.
    - Client then disconnects from the server
