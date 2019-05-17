# Theory-questions

- What are the different entities that comprise a socket pair?
- Explain how socket address structure is passed from kernel to process
- What is the purpose of SO-REUSEADDR option? Explain.
- Why do we need TIME_WAIT State during termination of TCP connection? Briefly explain
- What happens when SO_LINGER socket option is called:
  - If l_onoff is nonzero and Ninger is nonzero.
  - If l_onoff is nonzero and 1Jinger is zero.
- Explain Servent Structure

- What is a signal disposition? What are the choices for the disposition of software interrupts?

- What do you mean by connected UDP sockets? Does it start the 3WHS process? What is the purpose of specifying `AF_UNSPEC` in address family of connect call in case of UDP sockets.
- How the port number allocated to a UDP client if it does not call bind().
- If kernel chooses an ephemeral port number for our socket (we called bind() with port number field as 0), how can you obtain the value of port assigned?

- What are wrapper functions? Write a wrapper Bind( ) that does proper error handling
- Explain the scenarios where connect() returns an error.
- Briefly explain the significance of `backlog` parameter in listen system call. Why don't we specify a backlog of 0?
- What are socket send and receive buffers? Write a function to change the values of the low water marks of both the buffers.
- Consider a typical concurrent server, why doesn't the close of connfd by the parent terminate its connection with client.

- Compare the functions bcopyQ and memcopyQ.
- Differentiate between network byte order and host byte order. How network byte order is converted to host byte order?
- What happens when a router receives an IPv4 datagram whose size exceeds the outgoing link's MTU?

- Briefly explain IPv6 Socket Address Structure.
- In the function `const char inet_ntop(...., size_t len)` . What is the value of 'len' parameter for IPV6 address and why.
- What are the different ways of setting RES_USE_INET6 resolver option?
- Explain why the function inet_addr() has been deprecated?

- What happens when select is called in the following cases? ( Also see - coding question on select )
  - If we specify the timeout argument as a null pointer.
  - If we specify all three middle arguments (readset, writeset and exceptset) as null.
- Compare blocking I/O model, non-blocking I/O model and I/O multiplexing model.
- Explain with an example why we need to use waitpid() instead wait() while writing the signal handler to avoid zombies. Also see code segment to reap off zombies
- State the conditions under which a descriptor is ready for reading

## Diagrams

- Draw the diagram to show connections between client host, resolvers and name server.
- Explain 3-Way handshaking process with the help of diagram.
- Assume that a client performs two writes: the first of 4 bytes and the second of 396 bytes. Also assume that the server's delayed ACK time is 100 ms, the RTT between the client and the server is 100ms, and the server' s processing time for the client's request is 50ms. Draw a timeline that shows the interaction of Nagle Algorithm with delayed ACKs. Also draw the timeline chart if TCP_NODELAY socket option is set.
- With the help of a diagram show how actual packet exchange takes place for a complete TCP connection. Clearly show the various TCP states through which client and server passes.

## Logical

- We have two applications, one using TCP and other using UDP. 4096 bytes are in the receive buffer for the TCP socket and two 2048-bye datagrams are in the receive buffer for the UDP socket. The TCP application calls read() with the third argument of 4096 and UDP applicationcalls recvfrom() with third argument of 4096, Is there any difference?

- Output of code

  ```c
  include <stdio.h>
  include <sys/types.h>
  int main(){
      Pid__tpid = fork();
      if(pid == 0) *
      printff’Child process created\n");
      else
      printffParent process created\n");
      return 0;
  }
  ```
