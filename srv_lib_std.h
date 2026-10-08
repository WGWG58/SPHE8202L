#ifdef USER_SUPER_SA_LOADER    
  #ifdef DVDRELEASE
   INPUT(srv-elf\libsrv_sa0sa0_std.a)
   INPUT(-lsrvdp)
  #else
   INPUT(srv-elf\libsrv_sa0sa0_std_.a)
   INPUT(-lsrvdp_)
  #endif
#endif  

  

