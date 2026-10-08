#ifndef	__SP721_H
#define	__SP721_H

void	sp721_setup(void);
void	sp721_setup_output(int opt);
void	sp721_setup_ntsc(void);
void	sp721_setup_pal(void);
void	sp721_setup_pal60(void);
void	sp721_sleep(void);
void	sp721_resume(void);
void	sp721_setup_aspect(int aspect);
void	sp721_l21_enable(int n);
void	sp721_writel21_data(int n, unsigned d);
void	sp721_set_misc(int type);

#endif

