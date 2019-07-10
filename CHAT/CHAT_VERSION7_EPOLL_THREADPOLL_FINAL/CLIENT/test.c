#include <stdio.h>
#include <string.h>

int main()
{
	char a[20];
	strcpy(a," (group) send to ");
	int len;
	len = strlen(a);
	printf("%d\n",len);
	return 0;
}
