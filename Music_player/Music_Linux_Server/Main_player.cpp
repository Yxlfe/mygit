#include "Music_player_head.h"

int main(void)
{
	TCP_socket_create();
	Sqlite3_register();
	Read_Filename();
	IPC_init();
	Fork1();
	
		
	return 0;
}
