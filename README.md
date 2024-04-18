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
	The dup() system call creates a copy of a file descriptor.
dup2
execve,
exit
fork
pipe
unlink
wait
waitpid
