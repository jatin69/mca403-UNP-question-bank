#include "unp.h"

// general functions
void InstallSignalHandlers();
void installSignalHandler(int signalType, void (*singalHandlerFunction)(int));

// signal handler functions
void segmentationFaultHandler(int sig);
void zombieProcessesHandler(int sig);


/**Wrapper function : Install Signal Handlers
 *
 * @usage
 * Cleanly install required signal handlers
 *
*/
void InstallSignalHandlers() {
	// reap off zombie processes
	installSignalHandler(SIGCHLD, zombieProcessesHandler);
}

/**install signal handler
 *
 * @usage
 * install a single signal handler cleanly
 *
 * Note that,
 * sigaction is used instead of signal because,
 * sigaction is portable, predictable and thread safe.
 *
*/
void installSignalHandler(int signalType, void (*singalHandlerFunction)(int)) {
	struct sigaction sa;
	sa.sa_handler = singalHandlerFunction;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(signalType, &sa, NULL) == -1) {
		printError();
		exit(1);
	}
}

void zombieProcessesHandler(int sig[[gnu::unused]]) {
	// @logging
	// logs("REAPING OFF ZOMBIE PROCESS");
	// fprintf(stderr, "Error: signal %d:\n", sig);

	/**
	 * The usual function of waitpid is to wait for child process to exit.
	 *
	 * However, WNOHANG in waitpid
	 * tells it to return immediately if no child processes have exited yet.
	 * It does not go into blocking state.
	 *
	 * waitpid() might overwrite errno, so we save and restore it
	*/
	int saved_errno = errno;
	while (waitpid(-1, NULL, WNOHANG) > 0);
	errno = saved_errno;
}