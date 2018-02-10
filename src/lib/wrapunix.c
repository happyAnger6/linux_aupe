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
