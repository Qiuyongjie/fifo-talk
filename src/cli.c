
#include "../include/iotpanda.h"



int main(int argc, char *argv[])
{
	int fdself, fdto;

	char buff[1024];
	char *to;
	char *from;

	fmsg_pack p; // msg to send.
	fmsg_pack q; // msg from server.

	if (argc < 3)
		err_arg_quit("Usage: %s <cli_fifo> <serv_fifo>\n", argv[0]);
	
	to = argv[2];
	from = argv[1];

	if ((fdself = open(argv[1],O_RDWR)) == -1) /*for receive*/
		sys_quit("[fifo] open error : ");

	if ((fdto = open(argv[2], O_RDWR)) == -1) /*for send*/
		sys_quit("[fifo] open error : ");
	
	
	while (1)
	{				
		
		bzero(buff, sizeof(buff));
	
		fgets (buff, sizeof(buff),stdin);
		
		/*get input from stdin*/
		if (strncmp(buff,"exit\n",sizeof(char) * 5) == 0)
		{
			break;
		}
		/*pack up message*/
		if (msg_packup(buff, to, from, &p) == -1)
			sys_quit("pack up error");
		
		/*send*/
		if (msg_send(&p,fdto) == -1)
			sys_quit("send error ");
		
		/*wating for receive*/
		if (msg_receive(&q, fdself) == -1)
			sys_quit("receive error");
		
		msg_print(&q);

	}

	close(fdself);
	close(fdto);
	return 0;
}


