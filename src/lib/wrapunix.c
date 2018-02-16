#include    "unpipc.h"

#include    <stdarg.h>      /* for variable arg lists */


void
Stat(const char *pathname, struct stat *ptr)
{
    if (stat(pathname, ptr) == -1)
        err_sys("stat error");
}

void
Mkfifo(const char *pathname, mode_t mode)
{
    if (mkfifo(pathname, mode) == -1)
        err_sys("mkfifo error for %s", pathname);
}

void
Pipe(int *fds)
{
    if (pipe(fds) < 0)
        err_sys("pipe error");
}

ssize_t
Read(int fd, void *ptr, size_t nbytes)
{
    ssize_t     n;

    if ( (n = read(fd, ptr, nbytes)) == -1)
        err_sys("read error");
    return(n);
}

pid_t
Fork(void)
{
    pid_t   pid;

    if ( (pid = fork()) == -1)
        err_sys("fork error");
    return(pid);
}

/* include Close */
void
Close(int fd)
{
    if (close(fd) == -1)
        err_sys("close error");
}
/* end Close */

pid_t
Wait(int *iptr)
{
    pid_t   pid;

    if ( (pid = wait(iptr)) == -1)
        err_sys("wait error");
    return(pid);
}

pid_t
Waitpid(pid_t pid, int *iptr, int options)
{
    pid_t   retpid;

    if ( (retpid = waitpid(pid, iptr, options)) == -1)
        err_sys("waitpid error");
    return(retpid);
}

void
Write(int fd, void *ptr, size_t nbytes)
{
    if (write(fd, ptr, nbytes) != nbytes)
        err_sys("write error");
}

int
Open(const char *pathname, int oflag, ...)
{
    int     fd;
    va_list ap;
    mode_t  mode;

    if (oflag & O_CREAT) {
        va_start(ap, oflag);        /* init ap to final named argument */
        mode = va_arg(ap, va_mode_t);
        if ( (fd = open(pathname, oflag, mode)) == -1)
            err_sys("open error for %s", pathname);
        va_end(ap);
    } else {
        if ( (fd = open(pathname, oflag)) == -1)
            err_sys("open error for %s", pathname);
    }
    return(fd);
}

void
Unlink(const char *pathname)
{
    if (unlink(pathname) == -1)
        err_sys("unlink error for %s", pathname);
}


Pathconf(const char *pathname, int name)
{
    long    val;

    errno = 0;      /* in case pathconf() does not change this */
    if ( (val = pathconf(pathname, name)) == -1) {
        if (errno != 0)
            err_sys("pathconf error");
        else
            err_sys("pathconf: %d not defined", name);
    }
    return(val);
}

long
Sysconf(int name)
{
    long    val;

    errno = 0;      /* in case sysconf() does not change this */
    if ( (val = sysconf(name)) == -1) {
        if (errno != 0)
            err_sys("sysconf error");
        else
            err_sys("sysconf: %d not defined", name);
    }
    return(val);
}

void
Fstat(int fd, struct stat *ptr)
{
    if (fstat(fd, ptr) == -1)
        err_sys("fstat error");
}

int
Getopt(int argc, char *const *argv, const char *str)
{
    int     opt;

    if ( ( opt = getopt(argc, argv, str)) == '?')
        exit(1);        /* getopt() has already written to stderr */
    return(opt);
}

void *
Calloc(size_t n, size_t size)
{
    void    *ptr;

    if ( (ptr = calloc(n, size)) == NULL)
        err_sys("calloc error");
    return(ptr);
}

void *
Malloc(size_t size)
{
    void    *ptr;

    if ( (ptr = malloc(size)) == NULL)
        err_sys("malloc error");
    return(ptr);
}

/* include Select */
int
Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
       struct timeval *timeout)
{
	int		n;

again:
	if ( (n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0) {
		if (errno == EINTR)
			goto again;
		else
			err_sys("select error");
	} else if (n == 0 && timeout == NULL)
		err_quit("select returned 0 with no timeout");
	return(n);		/* can return 0 on timeout */
}

#ifdef  HAVE_SYS_IPC_H
key_t
Ftok(const char *pathname, int id)
{
    key_t   key;

    if ( (key = ftok(pathname, id)) == -1)
        err_sys("ftok error for pathname \"%s\" and id %d", pathname, id);
    return(key);
}
#endif  /* HAVE_SYS_IPC_H */


#ifdef  HAVE_SYS_MSG_H
int
Msgget(key_t key, int flag)
{
    int     rc;

    if ( (rc = msgget(key, flag)) == -1)
        err_sys("msgget error");
    return(rc);
}

void
Msgctl(int id, int cmd, struct msqid_ds *buf)
{
    if (msgctl(id, cmd, buf) == -1)
        err_sys("msgctl error");
}

void
Msgsnd(int id, const void *ptr, size_t len, int flag)
{
    if (msgsnd(id, ptr, len, flag) == -1)
        err_sys("msgsnd error");
}

ssize_t
Msgrcv(int id, void *ptr, size_t len, int type, int flag)
{
    ssize_t rc;

    if ( (rc = msgrcv(id, ptr, len, type, flag)) == -1)
        err_sys("msgrcv error");
    return(rc);
}
#endif  /* HAVE_SYS_MSG_H */


#ifdef  HAVE_MQUEUE_H

mqd_t
Mq_open(const char *pathname, int oflag, ...)
{
    mqd_t   mqd;
    va_list ap;
    mode_t  mode;
    struct mq_attr  *attr;

    if (oflag & O_CREAT) {
        va_start(ap, oflag);        /* init ap to final named argument */
        mode = va_arg(ap, va_mode_t);
        attr = va_arg(ap, struct mq_attr *);
        if ( (mqd = mq_open(pathname, oflag, mode, attr)) == (mqd_t) -1)
            err_sys("mq_open error for %s", pathname);
        va_end(ap);
    } else {
        if ( (mqd = mq_open(pathname, oflag)) == (mqd_t) -1)
            err_sys("mq_open error for %s", pathname);
    }
    return(mqd);
}

void
Mq_close(mqd_t mqd)
{
    if (mq_close(mqd) == -1)
        err_sys("mq_close error");
}

void
Mq_unlink(const char *pathname)
{
    if (mq_unlink(pathname) == -1)
        err_sys("mq_unlink error");
}

void
Mq_send(mqd_t mqd, const char *ptr, size_t len, unsigned int prio)
{
    if (mq_send(mqd, ptr, len, prio) == -1)
        err_sys("mq_send error");
}

ssize_t
Mq_receive(mqd_t mqd, char *ptr, size_t len, unsigned int *prio)
{
    ssize_t n;

    if ( (n = mq_receive(mqd, ptr, len, prio)) == -1)
        err_sys("mq_receive error");
    return(n);
}

void
Mq_notify(mqd_t mqd, const struct sigevent *notification)
{
    if (mq_notify(mqd, notification) == -1)
        err_sys("mq_notify error");
}

void
Mq_getattr(mqd_t mqd, struct mq_attr *mqstat)
{
    if (mq_getattr(mqd, mqstat) == -1)
        err_sys("mq_getattr error");
}

void
Mq_setattr(mqd_t mqd, const struct mq_attr *mqstat, struct mq_attr *omqstat)
{
    if (mq_setattr(mqd, mqstat, omqstat) == -1)
        err_sys("mq_setattr error");
}
#endif  /* HAVE_SYS_MSG_H */

void
Sigaddset(sigset_t *set, int signo)
{
	if (sigaddset(set, signo) == -1)
		err_sys("sigaddset error");
}

void
Sigdelset(sigset_t *set, int signo)
{
	if (sigdelset(set, signo) == -1)
		err_sys("sigdelset error");
}

void
Sigemptyset(sigset_t *set)
{
	if (sigemptyset(set) == -1)
		err_sys("sigemptyset error");
}

void
Sigfillset(sigset_t *set)
{
	if (sigfillset(set) == -1)
		err_sys("sigfillset error");
}

int
Sigismember(const sigset_t *set, int signo)
{
	int		n;

	if ( (n = sigismember(set, signo)) == -1)
		err_sys("sigismember error");
	return(n);
}

void
Sigpending(sigset_t *set)
{
	if (sigpending(set) == -1)
		err_sys("sigpending error");
}

void
Sigprocmask(int how, const sigset_t *set, sigset_t *oset)
{
	if (sigprocmask(how, set, oset) == -1)
		err_sys("sigprocmask error");
}

#ifdef	HAVE_SIGWAIT
void
Sigwait(const sigset_t *set, int *signo)
{
	int		n;

	if ( (n = sigwait(set, signo)) == 0)
		return;
	errno = n;
	err_sys("sigwait error");
}
#endif

#ifdef	HAVE_SIGINFO_T_STRUCT
void
Sigqueue(pid_t pid, int signo, const union sigval val)
{
	if (sigqueue(pid, signo, val) == -1)
		err_sys("sigqueue error");
}
#endif