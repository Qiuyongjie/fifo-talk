
#include "../include/iotpanda.h"



int main(int argc, char *argv[])
{
	int fdself, fdto;

	char *to;
	char *from;

	fmsg_pack p; // msg to send.
	fmsg_pack q; // msg from client.

	if (argc < 2)
		err_arg_quit("Usage: %s  <serv_fifo>\n", argv[0]);

	from = argv[1];


	if ((fdself = open(argv[1], O_RDWR)) == -1) /*for receive*/
		sys_quit("[fifo] open error : ");

	
	
	while (1)
	{
		bzero(&p, sizeof(p));
		bzero(&q, sizeof(q));
		/*wating for receive*/
		if (msg_receive(&q, fdself) == -1)
			sys_quit("receive error");
		
		msg_print(&q); /*print the msg that received from client */

		
		to = q.from;
		/*pack up message*/
		if (msg_packup(q.fmsg, to, from, &p) == -1)
			sys_quit("pack up error");
		
		/*open fdto*/
		if ((fdto = open(to, O_RDWR)) == -1)
			sys_quit("open client fifo error");

		/*send to clients*/
		if (msg_send(&p,fdto) == -1)
			sys_quit("send error ");

		printf("---------echo back to %s okay!-------------\n", p.to);
		
		close(fdto);
	}

	close(fdself);
	
	return 0;
}


