inline void power_on_init_car(void)
{
  ClearOsdMsg(1);
  browser = read_iso9660;
  cd_type_loaded=CDROM;
  cd_type=CDROM;
  system_state=SYSTEM_STOP;
  media_type = MEDIA_CD;
  sys_cmd=CMD_FUNC|CMD_FUNC_CLOSE;
//  dac_turn_on();
}
