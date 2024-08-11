


#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	struct timeval	start;
	struct timeval	sub;
	struct timeval	end;
	struct timeval	aim;
	int				cnt;

	cnt = 0;
	gettimeofday(&start, NULL);
	timeradd(&start, &((struct timeval){.tv_sec = 0, .tv_usec = 10000}), &aim);
	while (timercmp(&end, &aim, <))
	{
		gettimeofday(&end, NULL);
		timersub(&end, &start, &sub);
		start = end;
		printf("%d: %ld   \n", cnt, sub.tv_sec * 1000000 + sub.tv_usec);
		cnt++;
	}
	printf("\n");
	return (0);
}
