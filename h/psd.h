#ifndef	__PSD_H
#define	__PSD_H

typedef	struct {
  UINT16	timeout;
  BYTE		loopcnt;
} t_loop;

enum	{
	PLAYBACK_NONE,
	PLAYBACK_TRACK,
	PLAYBACK_ENTRY,
	PLAYBACK_RESERVED,
	PLAYBACK_SEGMENT
};

#define	LIST_PLAY	0x10
#define	LIST_SELECTION	0x18
#define	LIST_END	0x1f

typedef	struct {
  BYTE		header;
  BYTE		reserved;
  BYTE		nos;
  BYTE		bsn;
  UINT16	list_id;
  UINT16	list_prev;
  UINT16	list_next;
  UINT16	list_return;
  UINT16	list_default;
  UINT16	list_timeout;
  BYTE		wait_time;
  BYTE		loop_count;
  UINT16	item;
  UINT16	select[255];
} t_selection_list;


typedef	struct {
  BYTE		header;
  BYTE		noi;
  UINT16	list_id;
  UINT16	list_prev;
  UINT16	list_next;
  UINT16	list_return;
  UINT16	play_time;
  BYTE		wait_time;
  BYTE		wait_time_autopause;
  UINT16	item[255];
} t_play_list;

typedef	struct {
  BYTE		header;
} t_end_list;
#endif/*__PSD_H*/
