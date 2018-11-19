#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct Timer {
    struct timeval src_tv;
    struct timeval dst_tv;
} timer;

timer *t;
int nTimers = 0;

int myTimer_init(int numTimers) {
    nTimers = numTimers;
    t = (timer *)malloc(sizeof(struct Timer) * numTimers);
}

int myTimer_finalize(void) { free(t); }

int myTimer_on(int timerID) {
    if (t[timerID].src_tv.tv_sec != 0) {
        register int tmp_sec = t[timerID].src_tv.tv_sec;
        register int tmp_usec = t[timerID].src_tv.tv_usec;

        gettimeofday(&t[timerID].src_tv, NULL);

        t[timerID].src_tv.tv_sec += tmp_sec;
        t[timerID].src_tv.tv_usec += tmp_usec;
    }
    else
        gettimeofday(&t[timerID].src_tv, NULL);
}

int myTimer_off(int timerID) { gettimeofday(&t[timerID].dst_tv, NULL); }

int myTimer_print(void) {
    for (register int i = 0; i < nTimers; ++i) {
        register double dst = (double)t[i].dst_tv.tv_sec + (double)t[i].dst_tv.tv_usec / 1000000.;
        register double src = (double)t[i].src_tv.tv_sec + (double)t[i].src_tv.tv_usec / 1000000.;
        printf("%.02fms\n",(dst - src) * 1000.);
    }
}
