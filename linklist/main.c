#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "linklist.h"
#include <string.h>

#define CVT(cvt) *(cvt*)

bool print_string(void* data,void* args)
{
    printf("%s\n",(char*)data);
    return false;
}

bool print_int(void* data,void* args)
{
    printf("%d\n",*(int*)data);
    return false;
}

bool del(void* data,void* args)
{
    return *(int*)data == *(int*)args;
}

bool find_data(void* data,void* args)
{
    return *(int*)data == *(int*)args;
}

void write_data_string()
{
    void* plist_string = init_list(0);
    char buff[215] = {};
    time_t current_time;
    for(int i = 0;i < 100000;i++)
    {
        memset(buff,0,sizeof buff);
        time(&current_time);
        sprintf(buff,"%d,%s",i,asctime(gmtime(&current_time)));
        insert_list(plist_string,buff,strlen(buff) + 1);
    }
    
    //read_file_to_list(plist_string,"list_string.bin");
    traversal_list(plist_string,print_string,0);
    write_list_to_file(plist_string,"list_string.bin","wb");
    destroy_list(&plist_string);
}

void read_data_string()
{
    void* plist = init_list(0);
    read_file_to_list(plist,"list_string.bin","rb");
    traversal_list(plist,print_string,NULL);
    destroy_list(&plist);
}

void write_data_int()
{
    void* plist = init_list(sizeof(int));
    for(int  i= 0;i < 10000;i++)
        insert_list(plist,&i);
    write_list_to_file(plist,"list_int.bin","wb");
    destroy_list(&plist);
}

void read_data_int()
{
    void* plist = init_list(sizeof(int));
    read_file_to_list(plist,"list_int.bin","rb");
    traversal_list(plist,print_int,0);
    destroy_list(&plist);
}

int main(int argc,char** argv)
{
    return 0;
}

