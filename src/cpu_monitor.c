#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sysinfo.h>

// Function to get CPU usage percentage
double get_cpu_usage() {
    FILE* file = fopen("/proc/stat", "r");
    if (!file) {
        perror("Error opening /proc/stat");
        return -1.0;
    }

    char line[256];
    fgets(line, sizeof(line), file);
    fclose(file);

    unsigned long user, nice, system, idle;
    sscanf(line, "cpu %lu %lu %lu %lu", &user, &nice, &system, &idle);

    unsigned long total = user + nice + system + idle;
    unsigned long idle_time = idle;

    sleep(1); // Wait for 1 second

    file = fopen("/proc/stat", "r");
    fgets(line, sizeof(line), file);
    fclose(file);

    unsigned long user2, nice2, system2, idle2;
    sscanf(line, "cpu %lu %lu %lu %lu", &user2, &nice2, &system2, &idle2);

    unsigned long total2 = user2 + nice2 + system2 + idle2;
    unsigned long idle_time2 = idle2;

    unsigned long total_diff = total2 - total;
    unsigned long idle_diff = idle_time2 - idle_time;

    if (total_diff == 0) return 0.0;
    return 100.0 * (1.0 - ((double)idle_diff / total_diff));
}

int main() {
    printf("CPU Usage Monitor\n");
    printf("-----------------\n");

    while (1) {
        double cpu_usage = get_cpu_usage();
        if (cpu_usage >= 0) {
            printf("CPU Usage: %.2f%%\r", cpu_usage);
            fflush(stdout);
        }
        sleep(1);
    }

    return 0;
} 