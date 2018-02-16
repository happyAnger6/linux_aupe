#ifndef __UNPIPC_H
#define __UNPIPC_H

#include "config.h"

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#ifdef HAVE_MQUEUE_H
#include <mqueue.h>
#endif

#ifdef  HAVE_SYS_IPC_H
#include <sys/ipc.h>     /* System V IPC */
#endif

#ifdef  HAVE_SYS_MSG_H
#include <sys/msg.h>     /* System V message queues */
#endif

#ifdef	HAVE_PTHREAD_H
# include	<pthread.h>
#endif

#ifdef  HAVE_SYS_MSG_H
            /* 4System V message queues */
int Msgget(key_t key, int flag);
void Msgctl(int, int, struct msqid_ds *);
void Msgsnd(int, const void *, size_t, int);
ssize_t Msgrcv(int, void *, size_t, int, int);
#endif  /* HAVE_SYS_MSG_H */


#ifdef  __bsdi__
#define va_mode_t   int
#else
#define va_mode_t   mode_t
#endif

extern char *px_ipc_name(const char *);

void err_dump(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_ret(const char *, ...);
void err_sys(const char *, ...);

#define MAX_PATH    1024
/* $$.ix [MAX_PATH]~constant,~definition~of$$ */

#define MAXLINE     4096    /* max text line length */
/* $$.ix [MAXLINE]~constant,~definition~of$$ */

/* $$.ix [BUFFSIZE]~constant,~definition~of$$ */
#define BUFFSIZE    8192    /* buffer size for reads and writes */

/* Miscellaneous constants */
#ifndef PATH_MAX            /* should be in <limits.h> */
#define PATH_MAX    1024    /* max # of characters in a pathname */
#endif

#define MAX_PATH    1024
/* $$.ix [MAX_PATH]~constant,~definition~of$$ */
#define MAXLINE     4096    /* max text line length */
/* $$.ix [MAXLINE]~constant,~definition~of$$ */
/* $$.ix [BUFFSIZE]~constant,~definition~of$$ */
#define BUFFSIZE    8192    /* buffer size for reads and writes */

#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
                    /* default permissions for new files */
/* $$.ix [FILE_MODE]~constant,~definition~of$$ */
#define DIR_MODE    (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
                    /* default permissions for new directories */
/* $$.ix [DIR_MODE]~constant,~definition~of$$ */

#define SVMSG_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
                    /* default permissions for new SV message queues */
/* $$.ix [SVMSG_MODE]~constant,~definition~of$$ */
#define SVSEM_MODE  (SEM_R | SEM_A | SEM_R>>3 | SEM_R>>6)
                    /* default permissions for new SV semaphores */
/* $$.ix [SVSEM_MODE]~constant,~definition~of$$ */
#define SVSHM_MODE  (SHM_R | SHM_W | SHM_R>>3 | SHM_R>>6)
                    /* default permissions for new SV shared memory */
/* $$.ix [SVSHM_MODE]~constant,~definition~of$$ */

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

#endif

#ifdef	HAVE_SIGINFO_T_STRUCT
typedef	void	Sigfunc_rt(int, siginfo_t *, void *);
#endif

typedef	void	Sigfunc(int);	/* for signal handlers */

void     Mkfifo(const char *, mode_t);
void*     Malloc(size_t size);
typedef	void	Sigfunc(int);	/* for signal handlers */
