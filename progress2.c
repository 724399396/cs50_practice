#include <unistd.h>
#include <stdio.h>

int main() {
    for(int i = 0; i <= 100; i++) {
        printf("Percent complete: %d%%\r", i);
        fflush(stdout);
        sleep(1);
    }
}
