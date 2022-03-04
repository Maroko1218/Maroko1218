#include "prog3.h"
#include "helper.h"


struct distance_table dt3;

void printdt3(struct distance_table *dtptr) {
    printf("             via     \n");
    printf("   D3 |    0     2 \n");
    printf("  ----|-----------\n");
    printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
    printf("dest 1|  %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][2]);
    printf("     2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
}

/* students to write the following two routines, and maybe some others */


void rtinit3() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dt3.costs[i][j] = 999;
        }
    }
       
    dt3.costs[3][0] = 7;
    //dt3.costs[3][1] = 999;
    dt3.costs[3][2] = 2;
    dt3.costs[3][3] = 0;       
/*
999 999 999 7
999 999 999 999
999 999 999 2
999 999 999 0
*/
    shotgunlayer2(3, mincost(dt3));
}


void rtupdate3(struct rtpkt *rcvdpkt) {
    struct distance_table *debug = &dt3;
    int changed = 0; //boolean
    for (int i = 0; i < 4; i++) {
        if (i == rcvdpkt->destid) { continue; } // Exclude self node
        int temp = dt3.costs[rcvdpkt->sourceid][i]; // Temporarily store old value
        dt3.costs[rcvdpkt->sourceid][i] = mincost(dt3)[rcvdpkt->sourceid] + rcvdpkt->mincost[i]; // Potentially change value
        if (dt3.costs[rcvdpkt->sourceid][i] > 999) { dt3.costs[rcvdpkt->sourceid][i] = 999; } // if the cost was infinite reset back to 999
        if (temp < dt3.costs[rcvdpkt->sourceid][i]) { dt3.costs[rcvdpkt->sourceid][i] == temp; } // Don't want to increase distance
        if (temp != dt3.costs[rcvdpkt->sourceid][i]) { changed++; } // A change was made 
    }
    if (changed) {
        shotgunlayer2(rcvdpkt->destid, mincost(dt3));
    }
    printdt3(&dt3);
}



