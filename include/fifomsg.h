
#ifndef __FIFOMSG_H__
#define __FIFOMSG_H__

#define MAX_FMSG 1024 /*msg*/
#define MAX_FLEN 256  /*fifo path*/
typedef struct fifomsg fmsg_pack;
typedef char f_name_t;
typedef char msg_t;

struct fifomsg{
	msg_t 		fmsg[MAX_FMSG];
	f_name_t 	to[MAX_FLEN];
	f_name_t    from[MAX_FLEN];
};
int check_package (fmsg_pack *p);
int msg_packup (msg_t *m, f_name_t *to, f_name_t *from, fmsg_pack *p);
//int msg_unpack (msg_t *m, f_name_t *from, fmsg_pack *q);
int msg_send (fmsg_pack *p, int fdto);
int msg_receive (fmsg_pack *q, int fdself);
void msg_print(fmsg_pack *p);

#endif
