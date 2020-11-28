#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> //FILE chdor
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <sys/types.h>

#define MAXIMUM   1000 // лінія 
#define MAXIMUM1   100 //аргументи
#define SPACE  " \n\r\t\v"
/*
1. display a prompt in the form [{path}]
2. support the help
3. fork() + exec*()) present
4. stderr present
5. 4 additional commands: cp, whoami, changing the color, touch command
6. support the cd command,
7. cd goes to user home address
8. support the exit


total: 7 points earned
*/
int
main () // table of characters
{
  char line[MAXIMUM], PATH[100], c;
  char *argv[MAXIMUM1],/* table of pointers*/ *p, *login;
  FILE *file1, *file2;
  int i, status;

  for (;;) // foreveer loop for input
    {
      if (getcwd (PATH, sizeof (PATH)) != NULL) //deternines the useer location of the user
	{
	  fprintf (stderr, "[%s] s123456@lts:~$ ", PATH);
	  fgets (line, MAXIMUM, stdin);
/*              // line pointer (1st char and the length)
                 // fgets reads a limited number of characters
 parsing*/
	  p = strtok (line, SPACE); //determines a white space
	  for (i = 0; i < MAXIMUM1 && p != NULL; i++)
	    {
	      argv[i] = p; //веде до вищрї табл
	      p = strtok (NULL, SPACE);
	    }
	  argv[i] = NULL;
/* parsing end */
	  if (argv[0] == NULL) //enter
	    continue;
	  else if (strcmp (argv[0], "exit") == 0)
	    exit (0);
	  else if (strcmp (argv[0], "cd") == 0)
	    chdir (argv[1] != NULL ?/*? = if*/ argv[1] : getenv ("HOME"));
	  else if (strcmp (argv[0], "cp") == 0)
	    {
	      file1 = fopen (argv[1], "r");
	      file2 = fopen (argv[2], "w");
	      while ((c = getc (file1)) != EOF)
		putc (c, file2);
	      fclose (file1);
	      fclose (file2);
	    }
	//implementation
	  else if (strcmp (argv[0], "mkdir") == 0){
		  char string [20];
			fgets(string,sizeof(string),stdin);

		  mkdir("%s",(int) string  );

	  }

	  else if (strcmp (argv[0], "whoami") == 0)
	    {
	      login = getenv ("USER");
	      fprintf (stderr, "login of the current user: %s\n", login);
	    }
 	  else if (strcmp(argv[0], "chcolour") == 0){ //changing the terminal color
			char cur_colour[20];
			printf("choose colour: \nyellow \nblue \nred \ndef\n");
			fgets(cur_colour,sizeof(cur_colour),stdin);
			cur_colour[strlen(cur_colour)-1] = '\0';
			if (strcmp(cur_colour, "red") == 0){
				printf("\033[0;31m");
			}
			else if (strcmp(cur_colour, "blue") == 0) {
				printf("\033[0;34m");
			}
			else if (strcmp(cur_colour, "yellow") == 0) {
				printf("\033[0;33m");
			}
			else if (strcmp(cur_colour,"def") == 0){
				printf("\033[0m");
			}
			else{
				printf("no such a color\n");
			}
	   }
	   else if (strcmp(argv[0], "touch")==0){
			c=creat(argv[1], 0640);
			//return 1;
		}
	  else if (strcmp (argv[0], "help") == 0){
	    fprintf (stderr,
		     "Project Microshell \nIt was made by Maksym Dmyterko");
             sleep (2);
        fprintf (stderr,
        "\ncd;\nhelp;\nexit;\nwhoami;\n");
      }
	  else

	    {
	      if (fork () != 0) // for opening a program within a program
		{
		  waitpid (-1, &status, 0); // waits for child finishes (returns 0 to parent)
		}
	      else
		{
		  execvp (argv[0], argv); //opens a program
		  fprintf (stderr, "Couldn't run a command: %s\n", argv[0]);
		  return 1;
		}
	    }
	}
    }
}
