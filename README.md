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
# perror
	#include <errno.h>
	void perror(const char *s);
		The  perror()  function produces a message on standard error describing the last error encountered during a call to a system or library function.
		First (if s is not NULL and *s is not a null byte ('\0')), the argument string s is printed, followed by a colon and a blank. Then an error message corresponding to the current value of errno and a new-line.
# strerror
	#include <string.h>
	char *strerror(int errnum)
		The strerror() function returns a pointer to a  string  that  describes the  error  code  passed  in  the  argument  errnum, possibly using the 
		LC_MESSAGES part of the current locale to select the  appropriate  language.
		*to call function use "errno" as argument*
# access
	int access(const char *path, int amode)
 		The access() function shall check the file named by the pathname pointed to by the path argument for accessibility according to the bit pattern contained in amode, using the real user ID in place 		of the effective user ID and the real group ID in place of the effective group ID.
   		The value of amode is either the bitwise-inclusive OR of the access permissions to be checked (R_OK(reed), W_OK(write), X_OK(executed or if it is a directory if it is accessible)) or the existence 		test (F_OK). -> they need to be checked individual.
# dup
	The  dup() system call creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new descriptor.

    After a successful return, the old and new file descriptors may be used interchangeably.
	They refer to the same open file description (see open(2)) and thus share file offset and file status flags; 
	for example, if the file offset is modified by using lseek(2) on one of the file descriptors, the offset is also changed for the other.
    The two file descriptors do not share file descriptor flags (the closeon-exec  flag).The close-on-exec flag (FD_CLOEXEC; see fcntl(2)) for the duplicate descriptor is off.

# dup2
	The dup2() system call performs the same task as dup(), but instead  of using  the lowest-numbered unused file descriptor, it uses the file descriptor number specified in newfd. If the file descriptor newfd was previously open, it is silently closed before being reused.

    The  steps  of  closing  and reusing the file descriptor newfd are performed atomically.  
	This is  important,  because  trying  to  implement equivalent  functionality  using close(2) and dup() would be subject to race conditions, whereby newfd might be reused between the  two  steps.
    Such  reuse  could  happen because the main program is interrupted by asignal handler that allocates a file descriptor, or because a parallel thread allocates a file descriptor.

execve,
exit
fork
pipe
unlink
wait
waitpid
