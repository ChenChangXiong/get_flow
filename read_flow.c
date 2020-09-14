#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include<time.h>  //getSystemTimer
#include<sys/time.h>
#include <sys/timeb.h>

#include <signal.h>
#include <sys/select.h>

#include "read_flow.h"

float get_flow(int arg)
{
	int i = 0 ;
    int  fd = 0 ;
    int  ret = 0 ;
    char buf[128] = "0" ;
    char tempr[128] = "0" ;
    char tempt[128] = "0" ;

    int startr = 0, endr = 0 ;
    int startt = 0, endt = 0 ;

    float Rxcount = 1.0 ,Txcount = 1.0, Totalcount = 1.0 ;

    fd = open("date.txt", O_RDWR) ;
    if(fd < 0)
    {
        printf("open fail \r\n") ;
        sleep(3) ;
        fd = open("date.txt", O_RDWR) ;
        if(fd < 0)
            return 0;
    }

    ret = read(fd, buf, sizeof(buf)) ;
    if(ret > 0)
    {
        for(i=0;i<ret;i++)
        {
            if(buf[i]==':')
                startr = i + 1 ;
            if(buf[i]=='(')
            {
                endr = i ;
                break;
            }

        }
        //
        for(i=endr+1;i<ret;i++)
        {
            if(buf[i]==':')
                startt = i + 1;
            if(buf[i]=='(')
            {
                endt = i ;
                break;
            }
        }

        memcpy(tempr, &buf[startr], endr - startr) ;
        memcpy(tempt, &buf[startt], endt -startt) ;
        //atof  返回的最小为KB
        Rxcount = atof(tempr)/1024 ;
        Txcount = atof(tempt)/1024 ;
        Totalcount = Rxcount + Txcount ;
        //printf("Rx= %s  Tx=%s \r\n", tempr, tempt) ;
        //printf("all:=%.1f \r\n", Rxcount + Txcount) ;
        memset(tempr, 0 , sizeof(buf)) ;
        memset(tempt, 0 , sizeof(buf)) ;
    }
    i = 0 ; 
    lseek(fd,0,SEEK_SET) ;  //----------

    close(fd) ;

    switch(arg)
    {
        case 1:
            return Rxcount ;
            break;
        case 2:
            return Txcount ;
            break;
        case 3:
            return Totalcount ;
            break;
        default:break;
    }
}

char* get_riss(int arg)
{
    int i = 0 ,start = 0, end = 0 ;
    int fd = 0 ;
    int ret = 0 ;
    char buf[1024] = "0" ;
    static char temp[32] = "0" ;

    fd  = open("log.txt", O_RDWR) ;
    if(fd < 0)
        return  ;

    ret = read(fd, buf, sizeof(buf)) ;
    if(ret < 1)
        return  ;

    for(i=0;i<ret;i++)
    {
        if(buf[i]==':')
            start = i + 2 ;
        if(buf[i]==',')
        {
            end = i ;
            break;
        }

    }

    memcpy(temp, &buf[start], end - start) ;
    //printf("RISS = %s\r\n", temp) ;

    close(fd) ;

    return (char*)temp;
}
