/* only main should be in this file, to make all other functions in
 the prograble testable by Check.  in order to test main(), use a
 whole program testing framework like Autotest.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cacacomun.h"
#include "escapecabron.h"

int main(int argc, char *argv[]) {

	caca_log_debug("CACA");
	return 0;
}

/*
 #include <stdio.h>
 #include <string.h>
 #include <unistd.h>

 int main(int argc, char *argv[])
 {
 char src[40];
 char dest[100];

 memset(dest, '\0', sizeof(dest));
 sleep(100);
 strcpy(src, "This is tutorialspoint.com");
 strcpy(dest, src);

 printf("Final copied string : %s\n", dest);

 return(0);
 }
 */

/*

 #include <stdio.h>
 #include <string.h>
 #include <unistd.h>

 int main(int argc, char *argv[])
 {
 if(argc>1){
 sleep(100);
 }

 return(0);
 }
 */

/*
 //XXX: http://www.unix.com/programming/153272-read-redirected-file-stdin-c-out-file.html
 #include <stdio.h>
 int main() {
 char line[BUFSIZ],a[BUFSIZ],b[BUFSIZ];
 while (fgets(line,sizeof(line),stdin) &&
 sscanf(line,"%[0-9.]->%[0-9.] ",a,b) == 2) {
 printf("a(%s) b(%s)\n",a,b);
 }
 return 0;
 }


 192.168.0.254->192.168.0.1
 192.168.0.2->192.168.0.34
 192.168.0.56->192.168.0.77
 */
