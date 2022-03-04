#include "prog3.h"
#include "helper.h"


struct distance_table dt2;

void printdt2(struct distance_table *dtptr) {
    printf("                via     \n");
    printf("   D2 |    0     1    3 \n");
    printf("  ----|-----------------\n");
    printf("     0|  %3d   %3d   %3d\n", dtptr->costs[0][0],
           dtptr->costs[0][1], dtptr->costs[0][3]);
    printf("dest 1|  %3d   %3d   %3d\n", dtptr->costs[1][0],
           dtptr->costs[1][1], dtptr->costs[1][3]);
    printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][0],
           dtptr->costs[3][1], dtptr->costs[3][3]);
}

/* students to write the following two routines, and maybe some others */


void rtinit2() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dt2.costs[i][j] = 999;
        }
    }
       
    dt2.costs[2][0] = 3;
    dt2.costs[2][1] = 1;
    dt2.costs[2][2] = 0;
    dt2.costs[2][3] = 2;       
/*
999 999 3 999
999 999 1 999
999 999 0 999
999 999 2 999
*/
    shotgunlayer2(2, mincost(dt2));
}


void rtupdate2(struct rtpkt *rcvdpkt) {
    struct distance_table *debug = &dt2;
    int changed = 0; //boolean
    for (int i = 0; i < 4; i++) {
        if (i == rcvdpkt->destid) { continue; } // Exclude self node
        int temp = dt2.costs[rcvdpkt->sourceid][i]; // Temporarily store old value
        dt2.costs[rcvdpkt->sourceid][i] = mincost(dt2)[rcvdpkt->sourceid] + rcvdpkt->mincost[i]; // Potentially change value
        if (dt2.costs[rcvdpkt->sourceid][i] > 999) { dt2.costs[rcvdpkt->sourceid][i] = 999; } // if the cost was infinite reset back to 999
        if (temp < dt2.costs[rcvdpkt->sourceid][i]) { dt2.costs[rcvdpkt->sourceid][i] == temp; } // Don't want to increase distance
        if (temp != dt2.costs[rcvdpkt->sourceid][i]) { changed++; } // A change was made 
    }
    if (changed) {
        shotgunlayer2(rcvdpkt->destid, mincost(dt2));
    }
    printdt2(&dt2);

}

