

void reset_mjpeg_video_buffer() __WEAK;
void reset_mjpeg_video_buffer()
{  
}

int intr_decode_mjpeg(int will_be_top_field) __WEAK;
int intr_decode_mjpeg(int will_be_top_field __UNUSED)
{
    return 0;
}

#ifdef SUPPORT_MJPEG

//extern void __reset_mjpeg_video_buffer();
//extern int __intr_decode_mjpeg(int will_be_top_field);

//void (*reset_mjpeg_video_buffer)() = __reset_mjpeg_video_buffer;
//int (*intr_decode_mjpeg)(int will_be_top_field) = __intr_decode_mjpeg;

#else	// SUPPORT_MJPEG

//void mjpeg_null_func1() {}
//int mjpeg_null_func2(int a) {}

//void (*reset_mjpeg_video_buffer)() = mjpeg_null_func1;
//int (*intr_decode_mjpeg)(int will_be_top_field) = mjpeg_null_func2;

#endif	// SUPPORT_MJPEG
