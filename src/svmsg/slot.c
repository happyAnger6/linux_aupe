#include "unpipc.h"

int main(int argc, char *argv[])
{
    int i, msgid;
    struct msqid_ds info;
    
    for(i = 0; i < 10; i++) {
        msgid = Msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);
        printf("i = [%d], msgid = [%d]\r\n", i, msgid);
        Msgctl(msgid, IPC_STAT, &info);
        printf("read-write: %03o, cbytes = %lu, qnum = %lu, qbytes = %lu\n",
            info.msg_perm.mode & 0777, info.msg_cbytes, info.msg_qnum, info.msg_qbytes);
        system("ipcs -q");
        Msgctl(msgid, IPC_RMID, NULL);
    }

    exit(0);
}
