#ifdef SUPPORT_SPG_GAME
extern void __game16_field_start(int is_top_field);
extern int __game16_field_end();

void	(*game16_field_start)(int is_top_field) = __game16_field_start;
int		(*game16_field_end)() = __game16_field_end;

#else	// SUPPORT_SPG_GAME
void game16_null_func1(int is_top_field __attribute__((unused))) {}
int game16_null_func2() {return 0;}

void	(*game16_field_start)(int is_top_field) = game16_null_func1;
int		(*game16_field_end)() = game16_null_func2;
#endif	// SUPPORT_SPG_GAME

