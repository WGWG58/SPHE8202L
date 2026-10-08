# Sunplus SPHE8202L 固件源码包

## 项目简介

本仓库为凌阳（Sunplus）**SPHE8202L** DVD/多媒体 SoC 的固件源码包。该芯片采用 **MIPS 内核 + 专用 DSP** 架构，典型应用场景为 **DVD 影碟机、便携多媒体播放器（MP3/MP4/JPEG/CD/卡播放等）**。

源码包共约 1865 个文件，涵盖应用层 C 源码、核心预编译静态库（.a）、音频解码 DSP ROM、构建工具链与 Makefile/批处理脚本，可编译生成完整 `rom.bin` 固件。

> 声明：本仓库内容仅供学习研究使用，请勿用于商业用途。

## 顶层目录结构

| 目录 | 说明 |
|---|---|
| `h/` | 全部头文件（寄存器映射、驱动、应用接口），407 个 |
| `IR_VFD/` | 红外遥控（IR）解码 + VFD/LED 显示驱动 |
| `DSP3/` | 音频 DSP3 固件与解码 ROM（AC3/DTS/AAC/MP3/WMA/OGG/LPCM 等） |
| `system/` | 系统层：硬件接口（hwif）、HDD、EMU、存储卡/读卡器（cardif） |
| `IOP/` | 协处理器（I/O Processor）固件：iop.c / ioprom.c，含 8202/8202L 变体 |
| `mipsel-elf/` | MIPS 小端预编译静态库（lib*.a），含 portable/ 与 DVB 调谐器 NIM 库 |
| `setup/` | 设置菜单（Setup）UI 与多语言字符串（18 种语言） |
| `Customers/` | 客户定制配置（general 通用 / INTECH 等），cfg_*.h |
| `osd/` | OSD 屏幕显示层（含 libosd.a） |
| `fs/` | 文件系统 GUI（fsGUI）、DRM、文件浏览 |
| `package/` | 构建工具链（binobj / dump2bin / fgzip / font_parse 等 exe） |
| `pl/` | Perl 辅助脚本（makedep / dump2hex / hex2bin 等） |
| `srv-elf/` | 光盘伺服/服务库（libsrvdp_8202L.a 等） |
| `MIPS/` | 编译中间产物目录（*.o / *.d，构建时生成） |

### 顶层关键文件

| 文件 | 作用 |
|---|---|
| `Makefile` | 主构建脚本：链接 romL.obj，分段生成 dvd/mpeg/jpeg/ap1/cdrom/iop/dvb 等 bin.gz 并打包 ROM |
| `Makefile.utl` | 工具链与编译选项定义（CFLAGS_MIPS、XCC、XOBJDUMP 等） |
| `1.bat` / `1.bak` | 总编译入口（预处理 1.bak 生成 1_run.bat 并执行） |
| `2.bat` | 一键构建脚本：`all 16`（16Mb SDRAM）或 `all 32`（32Mb） |
| `sys.bat` / `ir.bat` / `fs.bat` / `osd.bat` | 各子模块构建入口 |
| `user_init.h` | 功能配置总开关（DVD 品牌模式、DVB、卡播放、MP4、HDD 等宏） |
| `cust_def.h` / `cust_pre_def.h` | 客户默认配置 |
| `kernel.c` | 内核接口：解码服务调度（ROMV/CDDA/CARDFILE 等） |
| `crt0_8202.S` / `init0_8202.S` / `intdrv_8202.S` | 启动/初始化/中断向量（8202 系列汇编） |
| `boot_flashs.S` + `boot_flash.ldp` | Flash 引导代码与链接脚本 |
| `dvdL.ldp` 等 11 个 `.ldp` | 链接脚本模板（经 cpp 生成 .ld） |
| `down.exe` / `load.exe` | 8202L 固件下载工具 |

## 源码构成统计

| 类型 | 数量 | 说明 |
|---|---|---|
| `.h` | 634 | 头文件 |
| `.c` | 547 | C 源码（应用/UI 层） |
| `.inc` | 197 | 汇编/数据包含文件（OSD 图标、字体、字符串、解码 ROM 数据） |
| `.o` | 115 | 已编译目标文件（中间产物） |
| `.d` | 112 | 依赖文件（中间产物） |
| `.a` | 100 | 预编译静态库（核心模块二进制） |
| `.gz` | 52 | 压缩固件/解码 ROM（dsp3rom.*.bin.gz 等） |
| `.exe` | 41 | 构建工具链 |
| `.ldp` | 11 | 链接脚本模板 |
| `.S` | 10 | 汇编源码（启动/引导/中断） |
| `.bat` | 10 | 批处理构建脚本 |
| `.pl` | 7 | Perl 脚本 |

**构成特点**：
- 应用/UI 层为完整 C 源码（可修改、可重编）；
- 核心解码、内核、文件系统等以 `lib*.a` 预编译库形式提供；
- 音频解码以 DSP3 ROM 镜像（`.bin.gz + .c/.inc`）形式嵌入，含 AC3/DTS/AAC/MP3/WMA/OGG/LPCM/MIDI/NES/SPDIF/HDCD/PPCM/Tuner 等大量配置变体。

## 构建方式

### 编译环境

- **目标架构**：MIPS 小端（`-m728 -membedded-data -DLITTLE_ENDIAN`，见 `Makefile.utl`）；
- **编译器**：需支持 `-m728` 的定制 GCC（凌阳 728 内核工具链，如 `gccl2.bat` 指向 `d:\gccl2\bin`）；
- **辅助工具**：`package/` 下的 exe 需在 PATH 中（`1.bak` 中 `SET path=.\package;%path%`）；
- **Perl**：`pl/` 脚本需要 perl 环境；
- **操作系统**：工程按 Windows 批处理 + GNU make 设计。

### 构建入口（流程）

```
2.bat 16  或  2.bat 32     # 一键构建（16Mb / 32Mb SDRAM）
```

1. `2.bat` → `sys.bat`：编译 `system/` 生成 `libsys_16.a` / `libsys_8202.a`；
2. `2.bat` → `1.bat`：预处理 `1.bak` 生成 `1_run.bat` 并执行；
3. `1.bak` 主流程：构建 `IR_VFD`（`ir.bat` → `libir_8202.a`）→ 生成 `icon.c` → 运行 `font_parse.exe` 生成字库 → 执行 `make`；
4. `make`（顶层 `Makefile`）：编译 SOURCES 到 `MIPS/*.o`，cpp 展开 `dvdL.ldp` → `dvdL.ld`，链接出 `romL.obj`，分段 dump → dump2bin → fgzip2 压缩，`module` 打包生成 `romL.bin`，`xb2 0x70 romL.bin rom.bin` 生成最终固件 **`rom.bin`**。

### 功能定制流程

1. 在 `user_init.h` 中选择/取消功能宏（DVD 品牌模式、DVB、卡播放、MP4、HDD 等）；
2. 在 `Customers/<客户>/cfg_*.h`（或 `cust_def.h`）设置机型配置（SDRAM 容量、OSD 风格、VFD 型号等）；
3. 切换 DSP3 解码 ROM：选对应 `dsp3rom.d16.*.c` 变体（AC3/DTS/AAC/MP3 等组合）；
4. 重新执行 `2.bat 16/32` 生成新 `rom.bin`。

### 烧录/下载

8202L 使用 `down.exe` 将 `rom.bin` 下载到芯片/Flash（其他 8202 系使用 `package\ep4.exe`）。

## 注意事项

1. **核心库为预编译二进制**：核心解码/内核/文件系统以 `.a` 静态库提供，无对应源码，二次深度开发受限于库接口（可用 `srv_lib_8202L.h` 等头文件）；
2. **需厂家专用工具链**：编译依赖特定版本定制 GCC（`-m728`）与凌阳私有打包工具（binobj/dump2bin/fgzip/xb2/module 等），现代环境需自行搭建 Windows 兼容环境或移植 Makefile；
3. **仅供学习研究**：本源码包来源于网络收集（原始站点为液晶之家），仅限学习交流使用，请勿用于商业用途；
4. **版权合规**：包内含 CSS 解密、DRM、Auth 等版权保护相关代码/库，涉及 DVD 解密等受专利与版权法规约束的内容，分发与使用前请注意法律合规风险。
