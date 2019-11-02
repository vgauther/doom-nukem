#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

# define BLOCK_SIZE 32

// int zz(int ac, char **av)
// {
// 	int fd;
// 	int ret;
// 	//unsigned char buff[1000];
// 	int i;
// 	int count;
//
// 	i = 0;
// 	count = 0;
// 	if(ac == 1)
// 		return 0;
// 	FILE * stream = fopen(av[1], "r");
// 	scanf("%d\n", &count);
//
// 	{
// 		unsigned char buff[ BLOCK_SIZE * count + 1];
// 		count = fread(buff, BLOCK_SIZE, count, stream);
// 		buff[count * BLOCK_SIZE] = 0;
// 		printf("%s\n", buff);
// 		while (buff[i])
// 		{
// 			printf("%d\n", buff[i]);
// 			i++;
// 		}
//
// 	}
//
// }

int main(void)
{
FILE *file;
int ch;
int i;
int c;
int c2;

c = 0;
c2 = 0;
file = fopen("assets/blue.png","r");
i = 0;
while((ch=fgetc(file))!=EOF )
{
         printf("%d ", ch);
		 i++;
		 if (i == 8)
		 {
			 i= 0;
			 printf("\n");
			 c2++;
		 }
		 c++;
}
printf("\n\n%d\n", c);
printf("\n\n%d\n", c2);

}
