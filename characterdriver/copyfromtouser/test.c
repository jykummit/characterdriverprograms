#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


int main()
{
	int fd;
	char buff[50] = "hi jyothimanikanth doing well";
	char kerndata[50];
	int len = strlen(buff);
	fd=open("/dev/example_device",O_RDWR);
	if(fd<0){
		perror(" ");
	}
	else{
		write(fd,buff,len);
		printf("data from user %s\n",buff);

		read(fd,buff,len);
		printf("data from kernel %s\n",kerndata);
	}
	close(fd);
	return 0;
}


