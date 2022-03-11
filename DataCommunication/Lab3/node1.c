#include "prog3.h"
#include "helper.h"


struct distance_table dt1;

void printdt1(struct distance_table *dtptr) {
    printf("             via   \n");
    printf("   D1 |    0     2 \n");
    printf("  ----|-----------\n");
    printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
    printf("dest 2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
    printf("     3|  %3d   %3d\n", dtptr->costs[3][0], dtptr->costs[3][2]);

}

/* students to write the following two routines, and maybe some others */

static int nodeToShortestPath[4];

void rtinit1() {
    for (int i = 0; i < 4; i++) {
        nodeToShortestPath[i] = i;
        for (int j = 0; j < 4; j++) {
            dt1.costs[i][j] = 999;
        }
    }
    dt1.costs[0][0] = 1;
    dt1.costs[1][1] = 0;
    dt1.costs[2][2] = 1;
    //dt1.costs[3][3] = 999;
/*
999 1 999 999
999 0 999 999
999 1 999 999
999 999 999 999
*/
    shotgunlayer2(1, dt1.costs, nodeToShortestPath);
    //make shitty ass packet code goes here
}


void rtupdate1(struct rtpkt *rcvdpkt) {
    struct distance_table *debug = &dt1;
    int changed = 0; //boolean/flag
    for (int i = 0; i < 4; i++) {
        if (i == rcvdpkt->destid) { continue; } //Skip self node
        int old = dt1.costs[i][nodeToShortestPath[i]]; // Temporarily store old value
        int new = dt1.costs[rcvdpkt->sourceid][rcvdpkt->sourceid] + rcvdpkt->mincost[i]; // Potentially change value
        dt1.costs[i][rcvdpkt->sourceid] = new; 
        if(new < old){
            nodeToShortestPath[i] = rcvdpkt->sourceid;
            changed++;
        } 
        if (dt1.costs[i][rcvdpkt->sourceid] > 999) { dt1.costs[i][rcvdpkt->sourceid] = 999; } // if the cost was infinite reset back to 999
    }
    if (changed) {
        shotgunlayer2(rcvdpkt->destid, dt1.costs, nodeToShortestPath);
    }
    printdt1(&dt1);
}

/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
void linkhandler1(int linkid, int newcost)
{
}