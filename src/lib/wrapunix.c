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
