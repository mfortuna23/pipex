allowed functions
# open
	opens file
# close
	closes file
# read
	reads file if the file is open
# write
	...
# malloc
	allocates memory
# free
	frees memory allocated
# perror <!-- this function discribes the preivious error, it prints first the argument given-->
	#include <errno.h> 
	void perror(const char *s);
		The  perror()  function produces a message on standard error describing the last error encountered during a call to a system or library function.
		First (if s is not NULL and *s is not a null byte ('\0')), the argument string s is printed, followed by a colon and a blank. Then an error message corresponding to the current value of errno and a new-line.
# strerror <!-- this function gives a *str with the error message with the given error number-->
	#include <string.h> 
	char *strerror(int errnum)
		The strerror() function returns a pointer to a  string  that  describes the  error  code  passed  in  the  argument  errnum, possibly using the 
		LC_MESSAGES part of the current locale to select the  appropriate  language.
		*to call function use "errno" as argument*
# access <!-- this function checks the file permissions -->
	int access(const char *path, int amode)
 		The access() function shall check the file named by the pathname pointed to by the path argument for accessibility according to the bit pattern contained in amode, using the real user ID in place of the effective user ID and the real group ID in place of the effective group ID.
   		The value of amode is either the bitwise-inclusive OR of the access permissions to be checked (R_OK(reed), W_OK(write), X_OK(executed or if it is a directory if it is accessible)) or the existence test (F_OK). -> they need to be checked individual.
# dup <!-- this function creates a copy of the file descriptor-->
	int dup(int oldfd);
		The  dup() system call creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new descriptor.
    	After a successful return, the old and new file descriptors may be used interchangeably.
		They refer to the same open file description (see open(2)) and thus share file offset and file status flags; 
		for example, if the file offset is modified by using lseek(2) on one of the file descriptors, the offset is also changed for the other.
    	The two file descriptors do not share file descriptor flags (the closeon-exec  flag).The close-on-exec flag (FD_CLOEXEC; see fcntl(2)) for the duplicate descriptor is off.

# dup2 <!-- this function creates a copy of the file descriptor with the given number-->
	int dup2(int oldfd, int newfd);
		The dup2() system call performs the same task as dup(), but instead  of using  the lowest-numbered unused file descriptor, it uses the file descriptor number specified in newfd. If the file descriptor newfd was previously open, it is silently closed before being reused.
    	The  steps  of  closing  and reusing the file descriptor newfd are performed atomically.  
		This is  important,  because  trying  to  implement equivalent  functionality  using close(2) and dup() would be subject to race conditions, whereby newfd might be reused between the  two  steps.
    	Such  reuse  could  happen because the main program is interrupted by asignal handler that allocates a file descriptor, or because a parallel thread allocates a file descriptor.

# execve <!-- this function executes the given command onn the file, 1st"command path", 2nd"command","command flag","filename" 3nd"enviorenment path"-->
	int execve(const char *pathname, char *const argv[], char *const envp[]);
		execve() executes the program referred to by pathname. This causes the program that is currently being run by the calling process  to  be  replaced  with  a  new  program,  with newly initialized stack, heap, and (initialized and uninitialized) data segments.
		argv  is  an  array of pointers to strings passed to the new program as its command-line arguments.  By convention, the first of these  strings (i.e.,  argv[0])  should  contain the filename associated with the file being executed. The argv array must be terminated by a  NULL  pointer. (Thus, in the new program, argv[argc] will be NULL.)

# exit <!--this funtion  terminates the program and frees dinamic allocated memory only (need to close any file) it doesnt return anything but it shows if it was an error or it was exopected depending on the argument given-->
	void exit(int status)
		The C library function void exit(int status) terminates the calling process immediately. Any open file descriptors belonging to the process are closed and any children of the process are inherited by process 1, init, and the process parent is sent a SIGCHLD signal.
# fork <!--this function creates a "copy" of the function called child. you can make the parrent do something while child does a diferent thing-->
	#include <sys/types.h>
	int fork(void)
		The Fork system call is used for creating a new process in Linux, and Unix systems, which is called the child process, which runs concurrently with the process that makes the fork() call (parent process). After a new child process is created, both processes will execute the next instruction following the fork() system call.
		The child process uses the same pc(program counter), same CPU registers, and same open files which use in the parent process. It takes no parameters and returns an integer value.
		if the return value is 0 the function child runs, if it is negative it didnt create child if it is positive the function parrent is running
# pipe <!--this function allow parent and child process to comunicate, the parent writes in th fd given and the child reads the massage-->
# unlink <!--this function deletes a file if you have permissions to do so and if all of the fds associeted with that file are closed. the file's directory entry will be removed, but the file's data blocks on the disk will remain allocated. The file will only be effectively deleted from the file system once all open file descriptors associated with it are closed and there are no more references to it. -->
# wait <!--this function will make the parrent process to wait for the child process to terminate for it to continue to work-->
	#include <sys/wait.h>
# waitpit


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_LEN 1024

char* find_executable_path(const char* command) {
    // Define a list of directories to search
    const char* search_dirs[] = {"/bin", "/usr/bin", "/usr/local/bin", NULL};

    for (int i = 0; search_dirs[i] != NULL; ++i) {
        char full_path[MAX_PATH_LEN];
        snprintf(full_path, MAX_PATH_LEN, "%s/%s", search_dirs[i], command);
        if (access(full_path, X_OK) == 0) {
            return strdup(full_path);
        }
    }

    return NULL; // Executable not found
}

int main() {
    const char* command = "ls"; // Example command
    char* executable_path = find_executable_path(command);
    if (executable_path != NULL) {
        printf("Executable path: %s\n", executable_path);
        free(executable_path);
    } else {
        printf("Executable '%s' not found\n", command);
    }

    return 0;
}
