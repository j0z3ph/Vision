#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	printf("%ld, %ld, %ld, %ld\n", getpid(), getppid(), getuid(), geteuid());
	return 0;
}
