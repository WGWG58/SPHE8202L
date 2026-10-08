void
intr_timer1(void)
{
  regs0->pic_start = 2;
}
