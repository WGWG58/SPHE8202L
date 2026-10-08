#if defined(SUPPORT_MP4) && defined(TURBO_DECODE)
    extern int __flddec_decode_mp4_video(int will_be_top_field, int decode_synced);
    int		(*flddec_decode_mp4_video)(int will_be_top_field, int decode_synced) = __flddec_decode_mp4_video;
#else
    int viddec_mp4_null_func3(int a1 __attribute__((unused)), int a2 __attribute__((unused))) {return 0;}
    int (*flddec_decode_mp4_video)(int will_be_top_field, int decode_synced) = viddec_mp4_null_func3;
#endif

#ifdef SUPPORT_MP4
    extern int __intr_decode_mp4_video(int will_be_top_field, int decode_synced);
    extern int __intr_dec_avi_sup(int will_be_top_field);
    extern void __calc_accm_audio_fPTS();
	extern INT64 GET_MP4_TIME_STC();
	extern void do_avi_audio_sync();
    int		(*intr_decode_mp4_video)(int will_be_top_field, int decode_synced) = __intr_decode_mp4_video;
    int		(*intr_dec_avi_sup)(int will_be_top_field) = __intr_dec_avi_sup;
    int		(*calc_accm_audio_fPTS)() = (int(*)())__calc_accm_audio_fPTS;
	INT64 	(*calc_accm_video_fPTS)() = (INT64(*)()) GET_MP4_TIME_STC;
	int 	(*do_audio_sync)() = (int(*)())do_avi_audio_sync;
#else	// SUPPORT_MP4
    void viddec_mp4_null_func1() {}
    int sup_mp4_null_func1(int will_be_top_field __attribute__((unused))) {return 0;}
	extern INT64 frctl_cur_frame_to_stc();
    void do_audio_sync_dummy_func() {}
    int (*intr_decode_mp4_video)(int will_be_top_field, int decode_synced) = viddec_mp4_null_func3;
    int (*intr_dec_avi_sup)(int will_be_top_field) = sup_mp4_null_func1;
    int	(*calc_accm_audio_fPTS)() = (int(*)())viddec_mp4_null_func1;
	INT64 (*calc_accm_video_fPTS)() = (INT64(*)())frctl_cur_frame_to_stc;
	int 	(*do_audio_sync)() = (int(*)())do_audio_sync_dummy_func;
#endif	// SUPPORT_MP4
