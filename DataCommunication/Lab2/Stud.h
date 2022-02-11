#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 ALTERNATING BIT AND GO-BACK-N NETWORK EMULATOR: VERSION 1.1  J.F.Kurose

   This code should be used for PA2, unidirectional or bidirectional
   data transfer protocols (from A to B. Bidirectional transfer of data
   is for extra credit and is not required).  Network properties:
   - one way network delay averages five time units (longer if there
     are other messages in the channel for GBN), but can be larger
   - packets can be corrupted (either the header or the data portion)
     or lost, according to user-defined probabilities
   - packets will be delivered in the order in which they were sent
     (although some can be lost).
**********************************************************************/

/* Change to 1 if you want to implement the assignment for both
 * directions. You do not have to do so in this assignment. */
#define BIDIRECTIONAL 0

/* You can check the simulated time using the time variable */
extern float time;

/* a "msg" is the data unit passed from layer 5 (teachers code) to layer  */
/* 4 (students' code).  It contains the data (characters) to be delivered */
/* to layer 5 via the students transport level protocol entities.         */
struct msg {
  char data[20];
};

/* a packet is the data unit passed from layer 4 (students code) to layer */
/* 3 (teachers code).  Note the pre-defined packet structure, which all   */
/* students must follow. */
struct pkt {
   int seqnum;
   int acknum;
   int checksum;
   char payload[20];
};


//Dessa funktioner finns i Jim.c och tillhör gränsnitten mellan
//Applikationslager - Transportlager samt Transportlager - Nätverkslager

/* called by students routine to cancel a previously-started timer */
void stoptimer(int AorB);  /* A or B is trying to stop timer */

void starttimer(int AorB, float increment);  /* A or B is trying to stop timer */
  
void tolayer3(int AorB, struct pkt packet);  /* A or B is trying to stop timer */
  
void tolayer5(int AorB,char datasent[20]);
  

//Dessa funktioner ska implementeras av studenterna i Stud.c och anropas
//av det simulerade applikationslagret samt nätverkslagret

/* called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message);
  
void B_output(struct msg message);  /* need be completed only for extra credit */

/* called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet);

/* called when A's timer goes off */
void A_timerinterrupt();

/* the following routine will be called once (only) before any other */
/* entity A routines are called. You can use it to do any initialization */
void A_init();

/* Note that with simplex transfer from a-to-B, there is no B_output() */

/* called from layer 3, when a packet arrives for layer 4 at B*/
void B_input(struct pkt packet);

/* called when B's timer goes off */
void B_timerinterrupt();

/* the following rouytine will be called once (only) before any other */
/* entity B routines are called. You can use it to do any initialization */
void B_init();
