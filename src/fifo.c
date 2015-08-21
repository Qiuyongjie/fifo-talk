

#include "../include/iotpanda.h"

void install(const char *path)
{
	if (mkfifo(path, 0666) < 0)
		sys_quit("make fifo error:");
}

void delete(const char *path)
{
	struct stat buf;
	int nlink = 0;
	
	if (stat(path, &buf) == -1)
		sys_quit("check hard link error!");

	nlink = buf.st_nlink;

	while (nlink --){
		if (unlink(path) == -1)
			sys_quit("delete fifo error:");
	}
}

int main(int argc, const char *argv[])
{
	if (argc < 3)
		err_arg_quit("Usage: %s ([-d] to delete or [-*] to install fifo)  <dir>\n", argv[0]);


	switch(strncmp(argv[1],"-d",2))
	{
		case 0:
			delete(argv[2]);
			printf("fifo deleted!\n");
			break;
		default:
			install(argv[2]);
			printf("fifo created!\n");
	}

	e_success;
}


