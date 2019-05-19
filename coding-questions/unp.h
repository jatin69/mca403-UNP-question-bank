/* Our own header. Tabs are set for 4 spaces, not 8 */
#ifndef __unp_h
#define __unp_h
#include <arpa/inet.h> /* inet(3) functions */
#include <errno.h>
#include <fcntl.h> /* for nonblocking */
#include <netdb.h>
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <poll.h>       /* for convenience */
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> /* for convenience */
#include <sys/ioctl.h>
#include <sys/select.h> /* for convenience */
#include <sys/socket.h> /* basic socket definitions */
#include <sys/stat.h>   /* for S_xxx file mode constants */
#include <sys/sysctl.h>
#include <sys/time.h>  /* timeval{} for select() */
#include <sys/types.h> /* basic system data types */
#include <sys/uio.h>   /* for iovec{} and readv/writev */
#include <sys/un.h>    /* for Unix domain sockets */
#include <sys/wait.h>
#include <time.h> /* timespec{} for pselect() */
#include <unistd.h>

// Standard
// #include <iostream>
// #include <sstream>
// #include <string>

// #include <cctype>
// #include <cstdio>
// #include <cstdlib>
// #include <cstring>
#include <unistd.h>


// socket programming
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
// #include <locale>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

// signal handling
#include <execinfo.h>
#include <signal.h>

#endif
