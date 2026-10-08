#ifndef __SRV2_H
#define __SRV2_H
//
// USEAGE:
// 1. DURING YOUR SOURCE POLLING:
//		1. stream_full() to check if we can put data in
//		2. call stream_putheader to get the pointer to write to
//		3. copy len(<2k) into stream_putheader
//		4. call stream_append(len) to let stream system know 
//		   data appended
//
// 2. Sample playing:
//		stream_init();
//		play_state = VCD_STATE_NORMAL;
//		while (1)
//		{
//			audif_set_coding_mode(AUDIF_CODING_MODE_MP2);	  
//			MacroPlayStream();
//			MediaMainLoop();
//		}
//
// Limitation: NOT to append more than STREAM_MAX_ACCESS
//             to stream in each access !!
//
//

//======================================================
//void stream_init()
//      initial stream buffer
//INPUT  ARGUMENTS: NONE 
//OUTPUT ARGUMENTS: NONE;
//RETURN: NONE
//======================================================
void stream_init();

//======================================================
//int stream_full()
//      Check if stream buffer is full
//INPUT  ARGUMENTS: NONE;
//OUTPUT ARGUMENTS: NONE;
//RETURN: nonzero means full
//======================================================
int stream_full();

//======================================================
//void *stream_putheader()
//      Get the stream-buffer header
//      Thus we can put data there
//INPUT  ARGUMENTS: NONE;
//OUTPUT ARGUMENTS: NONE;
//RETURN: buffer header to put buffer
//======================================================
void *stream_putheader();

//======================================================
//void stream_append(UINT32 len)
//      append stream with putted length
//INPUT  ARGUMENTS: 
//      len: length to append to stream
//OUTPUT ARGUMENTS: NONE;
//RETURN: NONE
//======================================================
void stream_append(UINT32 len);

//======================================================
//unsigned	stream_get_buffer(UINT8 **p)
//      get data pointer to play
//INPUT  ARGUMENTS: none
//OUTPUT ARGUMENTS: 
//     **p: data pointer return
//RETURN: 0: no data in stream
//     otherwize: stream len
//======================================================
unsigned	stream_get_buffer(UINT8 **p);

//======================================================
//int srv_stream(void)
//      Service Routine for kernel callback
//INPUT  ARGUMENTS: NONE 
//OUTPUT ARGUMENTS: NONE;
//RETURN: 0: no meaning now
//======================================================
int srv_stream(void);



//=============================================================================================
//    MACRO DEFINES
//=============================================================================================
// 
// 0x88400000, 4th mega in SDRAM
//    block0   | block1    | ..........| block15
//  -----------+-----------+------------------ 
//	|  32k	   |  32k      |           |
//  (power of 2)

#define STREAM_MAX_ACCESS 32768 // Not too much for one access!!
#define STREAM_DATA_BASE	(0x88400000)
#define STREAM_BLK_NUM		8 //POWER of 2
#define STREAM_BLK_LEN_PWR 17 // 15=32k
#define	STREAM_BLK_LEN	(1<<STREAM_BLK_LEN_PWR)
#define START_BUFF_KEEP (STREAM_BLK_NUM-3)
//
// USEAGE:
// 1. DURING YOUR SOURCE POLLING:
//		1. stream_full() to check if we can put data in
//		2. call stream_putheader to get the pointer to write to
//		3. copy len(<2k) into stream_putheader
//		4. call stream_append(len) to let stream system know 
//		   data appended
//
// 2. Sample playing:
//		stream_init();
//		play_state = VCD_STATE_NORMAL;
//		while (1)
//		{
//			audif_set_coding_mode(AUDIF_CODING_MODE_MP2);	  
//			MacroPlayStream();
//			MediaMainLoop();
//		}
//
// Limitation: NOT to append more than STREAM_MAX_ACCESS
//             to stream in each access !!
//
//


#endif //#ifndef  __SRV2_H

