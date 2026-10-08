@echo off
del mipsel-elf\libdsp3.a
package\makeim -b dsp3\dsp3rom.d16.ac3.2ch dsp3\mips\dsp3ac3.bin 
package\makeim -b dsp3\dsp3rom.d16.dts dsp3\mips\dsp3dts.bin
package\makeim -b dsp3\dsp3rom.d16.mp3.2ch dsp3\mips\dsp3mp3.bin
package\makeim -b dsp3\dsp3rom.d16.cd dsp3\mips\dsp3cd.bin
package\makeim -b dsp3\dsp3rom.d16.wma dsp3\mips\dsp3wma.bin
package\makeim -b dsp3\dsp3rom.d16.lpcm dsp3\mips\dsp3lpcm.bin
package\makeim -b dsp3\dsp3rom.d16.jp dsp3\mips\dsp3jpg.bin
package\makeim -b dsp3\dsp3rom.d16.nes dsp3\mips\dsp3nes.bin
package\makeim -b dsp3\dsp3rom.d16.spdif dsp3\mips\dsp3spdif.bin
package\makeim -b dsp3\dsp3rom.d16.dtscd dsp3\mips\dsp3dtscd.bin
package\makeim -b dsp3\dsp3rom.d16.ppcm dsp3\mips\dsp3ppcm.bin
cd dsp3
make
cd..
