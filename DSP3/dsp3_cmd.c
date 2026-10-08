/*
*
*/
//
// FUNCTION
// setupim()
//
// DESCRIPTION
// download gzip compressed binary.
// RETURN
// >=0 size after gunzip.
// <0  error during gunzip.
//
int
dsp3_decompress(const BYTE *rom, BYTE *dst)
{
  int v;
  t_getbit	gb;
  getbits_init(&gb, rom);
  v = gunzip(&gb, dst);	
#ifdef	MONE_DSP3_LOAD
  dsp3_printf("[dspl] %d\n", v);
#endif
  MIPS_flush_LBC_cache();
  return v;
}





//==================================ending=================================
