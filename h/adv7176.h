#ifndef	__ADV7176_H
#define	__ADV7176_H

void	adv7176_setup(void);
void	adv7176_setup_output(int opt);
void	adv7176_setup_ntsc(void);
void	adv7176_setup_pal60(void);
void	adv7176_setup_pal(void);
void	adv7176_sleep(void);
void	adv7176_resume(void);
void	adv7176_writel21_data(int n, unsigned d);

#endif
