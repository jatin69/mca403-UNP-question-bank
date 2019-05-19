# Theory-questions

<details><summary>
TCP state transition diagram - IMPORTANT
</summary>

![TCP states](./data/tcp-states.png)

</details>

<details><summary>What are the different entities that comprise a socket pair?</summary>

A socket pair uniquely identifies every TCP connection on internet.
Socket pair comprise of 4 entities -

- local IP address
- local TCP port
- Foreign IP address
- Foreign TCP Port
</details>

<details><summary>What happens when a router receives an IPv4 datagram whose size exceeds the outgoing link's MTU?</summary>

## IPv4

- If size is greater than MTU, fragmentation is performed by the router on the packets it forwards.
- Fragments are reassembled once they reach the destination.
- IPv4 hosts performs fragmentation on datagrams they generate.
- IPv4 routers performs fragmentation on datagrams that they forward.
- If the "don't fragment" (DF) bit is set in the IPv4 header, it specifies that this datagram must not be fragmented, either by the sending host or by any router.
- A router that receives an IPv4 datagram with the DF bit set whose size exceeds the outgoing link's MTU generates an ICMPv4 error message "destination unreachable, fragmentation needed but DF bit set".
- If some intermediate router returns an ICMP "destination unreachable, fragmentation needed but DF bit set" error, TCP decreases the amount of data it sends per datagram and retransmits.

## IPv6

- IPv6 hosts performs fragmentation on datagrams they generate.
- IPv6 routers does not perform fragmentation on datagrams that they forward.
- Since IPv6 routers do not perform fragmentation, there is an implied DF bit
  with every IPv6 datagram. When an IPv6 router receives a datagram whose
  size exceeds the outgoing link's MTU, it generates an ICMPv6 "packet too big"
  error message.

</details>

<details>
<summary>Explain how socket address structure is passed from kernel to process. </summary>

pg 81, section 3.3

## Process to kernel

- Three functions, bind, connect, and sendto, pass a socket address structure from the process to the kernel. One argument to these three functions is the pointer to the socket address structure and another argument is the integer size of the structure.
- Since the kernel is passed both the pointer and the size of what the pointer points to, it knows exactly how much data to copy from the process into the kernel. Figure 3.7 shows this scenario.

![process to kernel](./data/socket-address-structure-passing-from-process-to-kernel.png)

## Kernel to process

- Four functions, accept, recvfrom, getsockname, and getpeername, pass a socket address structure from the kernel to the process, the reverse direction from the previous scenario. Two of the arguments to these four functions are the pointer to the socket address structure along with a pointer to an integer containing the size of the structure.
- The reason that the size changes from an integer to be a pointer to an integer is because the size is both a value when the function is called (it tells the kernel the size of the structure so that the kernel does not write past the end of the structure when filling it in) and a result when the function returns (it tells the process how much information the kernel actually stored in the structure).
- This type of argument is called a value-result argument. Figure 3.8 shows this
scenario.

![kernel to process](./data/socket-address-structure-passing-from-kernel-to-process.png)

</details>

<details><summary>
Why do we need TIME_WAIT State during termination of TCP connection? Briefly explain
</summary>

- reliably establish full duplex connection
- allowing duplicate packets to expire in network
- Consider this example,
  - consider a connection, a client and a server
  - a packet is sent by server, it is delayed because of router crashes
  - server does not get ack, so it retransmits
  - this retransmitted packet reaches client, all good
  - connection is now closed
  - then opened again with exactly same ports between exactly these client and server, i.e. connection is `reincarnated`
  - so the packet which was delayed reaches the client (because everything is exactly same)
  - now from packets perspective, everything is normal
  - but what actually happened here is a packet from previous connection get received by the current connection messing up the sequence number and everything else
  - we cannot allow this to happen
  - so TCP says a connection must take care of these `lost duplicate` packets themselves
  - therefore, a socket once actively closed, is still in TIME_WAIT state to allow these `lost duplicates` to expire in network
- for this, the TIME_WAIT time is 2*MSL (max segment lifetime)
- why is it exactly double? because of 4-way termination mechanics
  - assume the last ack in 4-way termination is lost
  - the server will get to know of it, after 1-MSL (when timer times out)
  - it will then resend packet of step-3 which will take maximum 1-MSL to reach client
  - so we see, client when waits for 2-MSL is able to capture most of the duplicate packets, even the ones lost at termination.

</details>


<details><summary>
What are socket send and receive buffers? Write a function to change the values of the low water marks of both the buffers.
</summary>

- when a application calls send/write, the kernel copies all the data from the application buffer to the socket send buffer. 
- If the whole data cannot be copied because of insufficient space or application data being too much, process sleeps until there is more space on send buffer. The size of Send buffer is `SO_SNDBUF`.
- The kernel will not return from write until all the data has been copied to the send buffer.
- This copied data in the send buffer will be sent by the kernel.
- This is broken down into MSS
- Then broken to MTU if MSS > MTU-40 or MTU-60
- Until ack is received of this data, the data remains in the send buffer

pg 69, pg 207

</details>

<details><summary>
Differentiate between network byte order and host byte order. How network byte order is converted to host byte order?
</summary>

- little endian and big endian
![byte ordering](./data/byte-ordering.png)

functions use for conversion -

- Both return: value in network byte order
  - `uint16_t htons(uint16_t host16bitvalue) ;`
  - `uint32_t htonl(uint32_t host32bitvalue) ;`

- Both return: value in host byte order
  - `uint16_t ntohs(uint16_t net16bitvalue) ;`
  - `uint32_t ntohl(uint32_t net32bitvalue) ;`

</details>

<details><summary>Compare the functions bcopy and memcopy. </summary>

- `void bcopy(const void *src, void *dest, size_t nbytes);`
- bcopy moves the specified number of bytes from the source to the destination.
- `void *memcpy(void *dest, const void *src, size_t nbytes);`
- memcpy is similar to bcopy, but the order of the two pointer arguments is swapped. bcopy correctly handles overlapping fields, while the behavior of memcpy is undefined if the source and destination overlap. The ANSI C memmove function must be used when the fields overlap.

</details>

<details><summary>Briefly explain IPv6 Socket Address Structure.</summary>

Fig 3.1 - ipv4 socket address structure
![ipv4 socket address structure](./data/ipv4-socket-address-structure.png)

Fig 3.4 - ipv6 socket address structure
![ipv6 socket address structure](./data/ipv6-socket-address-structure.png)

- the `sin6_flowinfo` is divided into 3 fields
  - lower order 24 bits for flow label
  - next 4 bits for priority
  - next 4 are reserved

Fig 3.5 - comparison of socket address structures
![comparison of socket address structures](./data/comparison-of-socket-address-structures.png)

</details>

<details><summary>Explain why the function inet_addr() has been deprecated?</summary>

- `int inet_aton(const char *strptr, struct in_addr *addrptr);`
  - inet_aton, converts the C character string pointed to by strptr into its 32-bit binary network byte ordered value, which is stored through the pointer addrptr. If successful, 1 is returned; otherwise, 0 is returned.
- `in_addr_t inet_addr(const char *strptr);`
  - inet_addr does the same conversion, returning the 32-bit binary network byte ordered value as the return value. 
  - The problem with this function is that all 2^32 possible binary values are valid IP addresses (0.0.0.0 through 255.255.255.255), but the function returns the constant INADDR_NONE (typically 32 one-bits i.e. 255.255.255.255) on an error.
  - This means the dotted-decimal string 255.255.255.255 (the IPv4 limited broadcast address) cannot be handled by this function since its binary value appears to indicate failure of the function
- `char *inet_ntoa(struct in_addr inaddr);`
  - The inet_ntoa function converts a 32-bit binary network byte ordered IPv4 address into its corresponding dotted-decimal string. 
  - The string pointed to by the return value of the function resides in static memory. This means the function is not reentrant, which we will discuss in Section 11.18. 
  - Finally, notice that this function takes a structure as its argument, not a pointer to a structure. Functions that take actual structures as arguments are rare. It is more common to pass a pointer to the structure.

</details>

<details>
<summary>
In the function `const char inet_ntop(...., size_t len)` . What is the value of 'len' parameter for IPV6 address and why.
</summary>

- `int inet_pton(int family, const char *strptr, void *addrptr);`
  - The first function tries to convert the string pointed to by strptr, storing the binary result through the pointer addrptr. If successful, the return value is 1. If the input string is not a valid presentation format for the specified family, 0 is returned.
- `const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len);`
  - inet_ntop does the reverse conversion, from numeric (addrptr) to presentation (strptr). The len argument is the size of the destination, to prevent the function from overflowing the caller's buffer. 
  - To help specify this size, the following two definitions are defined by including the `<netinet/in.h>` header:
  - `#define INET_ADDRSTRLEN 16 /* for IPv4 dotted-decimal */`
  - `#define INET6_ADDRSTRLEN 46 /* for IPv6 hex string */`
  - If len is too small to hold the resulting presentation format, including the terminating null, a null pointer is returned and errno is set to ENOSPC. The strptr argument to inet_ntop cannot be a null pointer. The caller must allocate memory for the destination and specify its size. On success, this pointer is the return value of the function.

summary 

![summary](./data/summary-of-address-conversion-functions.png)

</details>

<details><summary>Signatures of all socket programming functions. </summary>

- `int socket (int family, int type, int protocol);`
  - Usage : `int sockfd  = socket(AF_INET, SOCK_STREAM, 0);`
  - `0` means let the OS choose the best protocol
- `int connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);`
  - connect can return error in few scenarios mentioned below.
  - if a error is received, the sockfd used must be closed, and then `socket()` must be recalled to get a new sockfd.
- `int bind (int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);`
  - can take `IP` or `port` or `both`
  - on client, bind is not usually performed
    - `IP` refers to client IP. If it is not specified, it is chosen once socket is connected, based on the route required to reach the server
    - `port` refers to the port to be used for this connection. If not specified, an ephemeral port is assigned by kernel
  - on server, bind is performed to bind to a well known port
    - `IP` - If a TCP server does not bind an IP address to its socket, the kernel uses the destination IP address of the client's SYN as the server's source IP address. (smart right)
    - `port` - server usually provides a well-known port to the bind function so it can be advertised to clients. In case it does not provide, kernel will use an ephemeral port.
  - If we specify a port number of 0, the kernel chooses an ephemeral port when bind is called. But if we specify a wildcard IP address, the kernel does not choose the local IP address until either the socket is connected (TCP) or a datagram is sent on the socket (UDP).
  - With IPv4, the wildcard address is specified by the constant INADDR_ANY, whose value is normally 0. This tells the kernel to choose the IP address.
- `int listen (int sockfd, int backlog);`
  - When a socket is created by the socket function, it is assumed to be an active socket, that is, a client socket that will issue a connect. The listen function converts an unconnected socket into a passive socket, indicating that the kernel should accept incoming connection requests directed to this socket. In terms of the TCP state transition diagram (Figure 2.4), the call to listen moves the socket from the CLOSED state to the LISTEN state.
  - The second argument to this function specifies the maximum number of connections the kernel should queue for this socket.
- `int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);`
  - accept is called by a TCP server to return the next completed connection from the front of the completed connection queue (Figure 4.7). If the completed connection queue is empty, the process is put to sleep (assuming the default of a blocking socket).
  - The `cliaddr` and `addrlen` arguments are used to return the protocol address of the connected peer process (the client). `addrlen` is a value-result argument.
  - Before the call, we set the integer value referenced by `*addrlen` to the size of the socket address structure pointed to by `cliaddr`; on return, this integer value contains the actual number of bytes stored by the kernel in the socket address structure.
- `int close (int sockfd);`
  - The default action of close with a TCP socket is to mark the socket as closed and return to the process immediately. The socket descriptor is no longer usable by the process: It cannot be used as an argument to read or write. But, TCP will try to send any data that is already queued to be sent to the other end, and after this occurs, the normal TCP connection termination sequence takes place.
  - Note that : close decrements ref count by 1
  - We must also be aware of what happens in our concurrent server if the parent does not call close for each connected socket returned by accept. First, the parent will eventually run out of descriptors, as there is usually a limit to the number of descriptors that any process can have open at any time. But more importantly, none of the client connections will be terminated. When the child closes the connected socket, its reference count will go from 2 to 1 and it will remain at 1 since the parent never closes the connected socket. This will prevent TCP's connection termination sequence from occurring, and the connection will remain open.
- `shutdown(int sockfd)`
  - At the end of Section 4.8, we mentioned that when the parent process in our concurrent server closes the connected socket, this just decrements the reference count for the descriptor. Since the reference count was still greater than 0, this call to close did not initiate TCP's four-packet connection termination sequence. This is the behavior we want with our concurrent server with the connected socket that is shared between the parent and child.
  - If we really want to send a FIN on a TCP connection, the shutdown function can be used (Section 6.6) instead of close.
  - Section 6.5

</details>

<details>
<summary>Explain the scenarios where connect() returns an error.</summary>

- If the client TCP receives no response to its SYN segment, `ETIMEDOUT` is returned. 
  - In BSD, for example sends one SYN when connect is called, another 6 seconds later, and another 24 seconds later (p. 828 of  TCPv2). If no response is received after a total of 75 seconds, the error is returned.
- If the server's response to the client's SYN is a reset (RST), this indicates that no process is waiting for connections on the server host at the port specified (i.e., the server process is probably not running). This is a hard error and the error `ECONNREFUSED` is returned to the client as soon as the RST is received. 
  - An RST is a type of TCP segment that is sent by TCP when something is wrong. 
  - Three conditions that generate an RST are: 
  - when a SYN arrives for a port that has no listening server (what we just described), 
  - when TCP wants to abort an existing connection, and 
  - when TCP receives a segment for a connection that does not exist.
- If the client's SYN elicits an ICMP "destination unreachable" from some intermediate router, this is considered a soft error. The client kernel saves the message but keeps sending SYNs with the same time between each SYN as in the first scenario. If no response is received after some fixed amount of time
(75 seconds for 4.4BSD), the saved ICMP error is returned to the process as either `EHOSTUNREACH` or `ENETUNREACH`.


In terms of the TCP state transition diagram (Figure 2.4), connect moves from the `CLOSED` state (the state in which a socket begins when it is created by the socket function) to the `SYN_SENT` state, and then, on success, to the `ESTABLISHED` state. If connect fails, the socket is no longer usable and must be closed. We cannot call connect again on the socket. In Figure 11.10, we will see that when we call connect in a loop, trying each IP address for a given host until one works, each time connect
fails, we must close the socket descriptor and call socket again.

</details>

<details>
<summary>
What are wrapper functions? Write a wrapper Bind() that does proper error handling
</summary>

- Wrapper functions are used to encapsulate the complexity. It can be thought of a function which will hide all the nitty gritty details and error handling for us. It will simply take only important parameters and return important values.

Find the code for wrapper Bind [here](./../coding-questions/Q3.c)

</details>

<details>
<summary>
If kernel chooses an ephemeral port number for our socket (we called bind() with port number field as 0), how can you obtain the value of port assigned?
</summary>

- If we tell the kernel to choose an ephemeral port number for our socket, notice that bind does not return the chosen value. Indeed, it cannot return this value since the second argument to bind has the const qualifier. To obtain the value of the ephemeral port assigned by the kernel, we must call `getsockname` to return the protocol address.
- `int getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen);`

- Get this port number [code here](./../coding-questions/Q1.c)
- Get localhost IP [code here](./../coding-question/Q1.c)
- Getting the address family of a socket [code here](./../coding-questions/Q2.c)

</details>

<details>
<summary>
Briefly explain the significance of `backlog` parameter in listen system call. Why don't we specify a backlog of 0?
</summary>
 
Backlog specifies the maximum number of connections the kernel should queue for this socket.

- To understand the backlog argument, we must realize that for a given listening socket, the kernel maintains two queues:
- An incomplete connection queue, which contains an entry for each SYN that has arrived from a client for which the server is awaiting completion of the TCP three-way handshake. These sockets are in the SYN_RCVD state (Figure 2.4).
- A completed connection queue, which contains an entry for each client with whom the TCP three-way handshake has completed. These sockets are in the ESTABLISHED state.

![TCP Backlog queues](./data/tcp-backlog-queues.png)

- When a SYN arrives from a client, TCP creates a new entry on the incomplete queue and then responds with the second segment of the three-way handshake: the server's SYN with an ACK of the client's SYN.
- This entry will remain on the incomplete queue until the third segment of the three-way handshake arrives (the client's ACK of the server's SYN), or until the entry times out (1 RTT - from receiving the 1 of 3 handshake packet to 3 to 3 handshake packet - fig 4.9 - pg 112). 
- If the three-way handshake completes normally, the entry moves from the incomplete queue to the end of the completed queue. When the process calls accept, the first entry on the completed queue is returned to the process, or if the queue is empty, the process is put to sleep until an entry is
placed onto the completed queue.
- If the queues are full when a client SYN arrives, TCP ignores the arriving SYN; it does not send an RST. 
- This is because the condition is considered temporary, and the client TCP will retransmit its SYN, hopefully finding room on the queue in the near future. 
- If the server TCP immediately responded with an RST, the client's connect would return an error, forcing the application to handle this condition instead of letting TCP's normal retransmission take over. 
- Also, the client could not differentiate between an RST in response to a SYN meaning "there is no server at this port" versus "there is a server at this port but its queues are full."

#### Backlog shouldn't be 0

- Do not specify a backlog of 0, as different implementations interpret this differently.
- some implementation allow one queued connections while others do not allow any queued connections.
- If you do not want any clients connecting to your listening socket, close the listening socket.

</details>

<details><summary>
Consider a typical concurrent server, why doesn't the close of connfd by the parent terminate its connection with client.
</summary>

To understand what's happening, we must understand that every file or socket has a reference count. 

- The reference count is maintained in the file table entry. This is a count of the number of descriptors that are currently open that refer to this file or socket. 
- In Figure 4.13, after socket returns, the file table entry associated with listenfd has a reference count of 1. 
- After accept returns, the file table entry associated with connfd has a reference count of 1. 
- But, after fork returns, both descriptors are shared (i.e., duplicated) between the parent and child, so the file table entries associated with both sockets now have a reference count of 2. 
- Therefore, when the parent closes connfd, it just decrements the reference count from 2 to 1 and that is all. The actual cleanup and de-allocation of the socket does not happen until the reference count reaches 0. This will occur at some time later when the child closes connfd.

Fig 4.14, 4.15, 4.16, 4.17 - pg 123

- 4 diagrams showing the exact state by using 2 boxes
- connect -> listenfd
- connect <- connfd
- fork called
- connect <- 2 instances of server box
- connfd closed with original server instance -> one link is reduced
- so, ref count is decreased by 1, one link is still alive, so connfd does not close

</details>

-------------

<details><summary>What is the purpose of SO-REUSEADDR option? Explain.</summary>

pg 210, 4 big points

</details>

-------------

- What happens when SO_LINGER socket option is called:
  - If l_onoff is nonzero and Ninger is nonzero.
  - If l_onoff is nonzero and 1Jinger is zero.

Section 7.5

- Explain Servent Structure

- What is a signal disposition? What are the choices for the disposition of software interrupts?

- What do you mean by connected UDP sockets? Does it start the 3WHS (3-way handshake) process? What is the purpose of specifying `AF_UNSPEC` in address family of connect call in case of UDP sockets.
- How the port number allocated to a UDP client if it does not call bind().

- What are the different ways of setting RES_USE_INET6 resolver option?
- What happens when select is called in the following cases? ( Also see - coding question on select )
  - If we specify the timeout argument as a null pointer.
  - If we specify all three middle arguments (readset, writeset and exceptset) as null.
- Compare blocking I/O model, non-blocking I/O model and I/O multiplexing model.
- Explain with an example why we need to use waitpid() instead wait() while writing the signal handler to avoid zombies. Also see code segment to reap off zombies
- State the conditions under which a descriptor is ready for reading

## Diagrams

<details>
<summary>Explain 3-Way handshaking process with the help of diagram.</summary>

page 54, Fig 2.2

![page 54, Fig 2.2](./data/tcp-3-way-handshake.png)

</details>

<details><summary>
With the help of a diagram show how actual packet exchange takes place for a complete TCP connection. Clearly show the various TCP states through which client and server passes.
</summary>

page 59, Fig 2.5

![page 59, Fig 2.5](./data/tcp-packet-exchange.png)

</details>

-------------

- Draw the diagram to show connections between client host, resolvers and name server.

- Assume that a client performs two writes: the first of 4 bytes and the second of 396 bytes. Also assume that the server's delayed ACK time is 100 ms, the RTT between the client and the server is 100ms, and the server' s processing time for the client's request is 50ms. Draw a timeline that shows the interaction of Nagle Algorithm with delayed ACKs. Also draw the timeline chart if TCP_NODELAY socket option is set.

## Logical

- We have two applications, one using TCP and other using UDP. 4096 bytes are in the receive buffer for the TCP socket and two 2048-bye datagrams are in the receive buffer for the UDP socket. The TCP application calls read() with the third argument of 4096 and UDP applicationcalls recvfrom() with third argument of 4096, Is there any difference?

- Output of code

  ```c
  include <stdio.h>
  include <sys/types.h>
  int main(){
      pid__tpid = fork();
      if(pid == 0)
      printf("Child process created\n");
      else
      printf("Parent process created\n");
      return 0;
  }
  ```
