#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>

#include "read_flow.h"

int main(int argc,char* argv[])
{
    int i = 0 ;
    int ret = 0 ;
    int fd = 0 ;
    float get = 1.0 ;

    system("ifconfig wwan0 | grep \"RX bytes:\" > date.txt") ;

    if(argc > 1)
        get = get_flow(atoi(argv[1])) ;
    else
    {
        printf("argv too less\r\n") ;
        return 0;
    }

    switch(atoi(argv[1]))
    {
        case 1:
            printf("RX:%.1f KiB\r\n", get);
            break;
        case 2:
            printf("TX:%.1f KiB\r\n", get);
            break;
        case 3:
            printf("ALL:%.1f KiB\r\n", get);
            break;
        case 4:
            system("cat /dev/ttyUSB3 > log.txt &") ;
            usleep(500000) ;
            system("echo AT+CSQ > /dev/ttyUSB3") ;
            usleep(500000) ;
            system("sync") ;
            system("killall cat ") ;
            sleep(1) ;
            printf("RISS=%s\r\n", get_riss(0)) ;
            break;
        default:break;
    }

	return 0 ;
}

