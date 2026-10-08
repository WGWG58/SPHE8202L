#ifndef	__MPGKERN_H
#define	__MPGKERN_H

void	restart_video_engine();
void	restart_audio_engine();

void	resync_video();
void	resync_audio();
void	resync_audio_bitstream();

int	get_vbv_free(int vy);
int	get_vbv_free_exact(int vy);

void	set_timesearch_C_ELTM(UINT32);

#endif/*__MPGKERN_H*/

