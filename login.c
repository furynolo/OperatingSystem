/*
						Proc#2:
  (1). P2 is a login process. It executes /bin/login on the console terminal 
	   /dev/tty0. So the special file /dev/tty0 MUST exist. To support serial 
	   terminals and printer, /dev/ttyS0, /dev/ttyS1 and /dev/lp0 must also 
	   exist.

  (2). In /bin/login, P2 opens its tty special file (/dev/tty0) as stdin(0), 
	   stdout(1) and stderr(2). Then it displays (to its stdout)
				  login: 

  and waits for a user to login. When a user tries to login, it reads the
  user name and password (from its stdin), opens the /etc/passwd file to 
  authenticate the user. Each line of /etc/passwd has the format:

		  username:password:gid:uid:fullname:HOMEDIR:program
  e.g.    root:xxxxxxx:1000:0:superuser:/root:sh

  (Use plain text for password OR devise your own encryption schemes)

  If the user has a valid account in /etc/passwd, P2 becomes the user's process
  (by taking on the user's uid). It chdir to user's HOMEDIR and execute the 
  listed program, which is normally the sh (/bin/sh).
 
  (3). then (in sh) it loops forever (until "logout" or Contro-D):
		{
		   prompts for a command line, e.g. cmdLine="cat filename"
		   if (cmd == "logout") 
			  syscall to die;

		   // if just ONE cmd:  
		   pid = fork();
		   if (pid==0)
			   exec(cmdLine);
		   else
			   pid = wait(&status);
		}    

   (3). When the child proc terminates (by exit() syscall to MTX kernel), it 
   wakes up sh, which prompts for another cmdLine, etc.

   (4). When sh dies, it wakes up its parent, INIT, which forks another
		login process.
*/

 //////////////////////////////////////////////////////////////////////////////////
//                   LOGIC of login.c file										 //
//////////////////////////////////////////////////////////////////////////////////

#include "ucode.c"

char *tty;

main(int argc, char *argv[])	// invoked by exec("login /dev/ttyxx")
{
	tty =  argv[1];

//	1.	login process may run on different terms
	close(0);
	close(1);
	close(2);

//	2.	Open its own tty (passed in by INIT) as stdin, stdout, stderr

//	3.	Store tty string in PROC.tty[] for putc()
	settty(tty);

//	NOW we can use printf, which calls putc() to our tty
	printf("KCLOGIN : open %s as stdin, stdout, stderr\n", tty);

	signal(2,1);	// ignore Control-C interrupts so that 
					// Control-C KILLs other procs on this tty but not the main sh

	while(1)
	{
//	1. Show login:           to stdout
//	2. Read user nmae        from stdin
//	3. Show passwd:
//	4. Read user passwd

//	5. Verify user name and passwd from /etc/passwd file

//	6. If the user account is valid:  setuid to user uid, chdir to user HOME directory, exec to the program in users's account}
		printf("login failed, try again\n");
	}
}