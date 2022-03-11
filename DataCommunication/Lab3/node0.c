#include "prog3.h"
#include "helper.h"

struct distance_table dt0;

void printdt0(struct distance_table *dtptr) {
    printf("                via     \n");
    printf("   D0 |    1     2    3 \n");
    printf("  ----|-----------------\n");
    printf("     1|  %3d   %3d   %3d\n", dtptr->costs[1][1], dtptr->costs[1][2], dtptr->costs[1][3]);
    printf("dest 2|  %3d   %3d   %3d\n", dtptr->costs[2][1], dtptr->costs[2][2], dtptr->costs[2][3]);
    printf("     3|  %3d   %3d   %3d\n", dtptr->costs[3][1], dtptr->costs[3][2], dtptr->costs[3][3]);
}

/* students to write the following two routines, and maybe some others */

static int nodeToShortestPath[4];

void rtinit0() {
    for (int i = 0; i < 4; i++) {
        nodeToShortestPath[i] = i;
        for (int j = 0; j < 4; j++) {
            dt0.costs[i][j] = 999;
        }
    }
    //dtx.costs[dest][via]
    dt0.costs[0][0] = 0;
    dt0.costs[1][1] = 1;
    dt0.costs[2][2] = 3;
    dt0.costs[3][3] = 7;
/*
0 999 999 999
1 999 999 999
3 999 999 999
7 999 999 999
*/

    //make shitty ass packet code goes here
    shotgunlayer2(0, dt0.costs, nodeToShortestPath);
}


void rtupdate0(struct rtpkt *rcvdpkt) {
    struct distance_table *debug = &dt0;
    int changed = 0; //boolean/flag
    for (int i = 0; i < 4; i++) {
        if (i == rcvdpkt->destid) { continue; } //Skip self node
        int old = dt0.costs[i][nodeToShortestPath[i]]; // Temporarily store old value
        int new = dt0.costs[rcvdpkt->sourceid][rcvdpkt->sourceid] + rcvdpkt->mincost[i]; // Potentially change value
        dt0.costs[i][rcvdpkt->sourceid] = new; 
        if(new < old){
            nodeToShortestPath[i] = rcvdpkt->sourceid;
            changed++;
        } 
        if (dt0.costs[i][rcvdpkt->sourceid] > 999) { dt0.costs[i][rcvdpkt->sourceid] = 999; } // if the cost was infinite reset back to 999
    }
    if (changed) {
        shotgunlayer2(rcvdpkt->destid, dt0.costs, nodeToShortestPath);
    }
    printdt0(&dt0);
}

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
void linkhandler0(int linkid, int newcost) {
}