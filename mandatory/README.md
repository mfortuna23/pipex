allowed functions
open
close
read
write
malloc
free
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
		*to call function use "errno"*
# access

dup
dup2
execve,
exit
fork
pipe
unlink
wait
waitpid