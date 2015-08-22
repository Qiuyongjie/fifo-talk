

#include "fifomsg.h"
#include "iotpanda.h"

int check_package(fmsg_pack *p)
{
	if (p == NULL)
		err_common("bad package");

	if (p->from == NULL || p->to == NULL || p->fmsg == NULL)
		err_common("bad package");

	return 0;
}

int msg_packup(msg_t *m, f_name_t *to, f_name_t *from, fmsg_pack *p)
{
	if (p == NULL || m == NULL || to == NULL || from == NULL ) 
		err_args_null("fifo msg pack null");

	strncpy(p->fmsg, m, MAX_FMSG);
	strncpy(p->to, to, MAX_FLEN);
	strncpy(p->from, from, MAX_FLEN);

	return 0;
}


int msg_send(fmsg_pack *p, int fdto)
{
	if (check_package(p) == -1)
		return -1;
	//lock fdto 
	if (lockf(fdto, 1, 0) == -1)
		sys_quit("lock failed");

	if (write(fdto, p, sizeof(fmsg_pack)) < 0)
		sys_quit("error occured while attempted to write :");
	//unlock fdto
	if (lockf(fdto, 0, 0) == -1)
		sys_quit("unlock failed");

	return 0;
}

int msg_receive(fmsg_pack *q, int fdself)
{

	if (q == NULL)
		err_common("bad address");
	
	//lock fdself
	if (lockf(fdself, 1, 0) == -1)
		sys_quit("lock failed");

	if (read(fdself, q, sizeof(fmsg_pack)) < 0)
		sys_quit("error occured while attempted to read :");
	
	//unlock fdself 
	if (lockf(fdself, 0, 0) == -1)
		sys_quit("unlock failed");

	if (check_package(q))
		return -1;

	return 0;
}

void msg_print(fmsg_pack *p)
{
	printf("Received from :%s\n", p->from);
	printf("Context:  %s", p->fmsg);
}
