#ifndef	__MPEGSYS_H
#define	__MPEGSYS_H

void	reset_sequence_state(void);
void	resync_picture_state(void);
void	restart_video_engine(void);

int	is_mpeg_video_sequence_ended();
int	is_mpeg_system_program_ended();

INT64	diff_timestamp(INT64 a, INT64 b);

#endif/*__MPEGSYS_H*/

