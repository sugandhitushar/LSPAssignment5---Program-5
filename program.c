#include"program.h"

struct message
{
	long mtype;
	char mtext[50];
};

int main(int argc, char *argv[])
{
	int msqid,res;
	char str[50];
	msqid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
	
	struct message mymsg;
	
	printf("Enter the message: ");
	fgets(str,sizeof(str),stdin);
	
	mymsg.mtype=1;
	strcpy(mymsg.mtext,str);
	
	res = msgsnd(msqid, &mymsg, sizeof(mymsg.mtext), IPC_NOWAIT);
	if(res == -1)
	{
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}
	
	strcpy(mymsg.mtext,"");
	
	if(fork() == 0)
	{
		char receivedData[50];
		
		res = msgrcv(msqid, (void *) &mymsg, sizeof(mymsg.mtext),1, IPC_NOWAIT);
		if(res < 0)
		{
			perror("msgrcv");
			exit(EXIT_FAILURE);
		}
		
		printf("Received Message: %s\n",mymsg.mtext);
	}	
	return 0;
}

