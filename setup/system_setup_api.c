#ifdef DVD_SETUP_REENG
void Set_SetUp_Item_Value(int page,int index,BYTE data)
{
	
	UINT32 cur_index ;
	cur_index = setup_item[page][index][MAX_ITEM_SEL+1] ;
	setup_VA[cur_index] = data ;
	run_save_sel_cmd(data,cur_index);
	
	
}
UINT8  Get_Setup_Item_Value(int page,int index)
{
	 
	UINT32 cur_index ;
	cur_index = setup_item[page][index][MAX_ITEM_SEL+1] ;
	return setup_VA[cur_index];

}

#else
void Set_SetUp_Item_Value(int page,int index,BYTE data)
{
	
	setup_sel[page][index] = data ;
	run_save_sel_cmd(page,index);
	
	
}
UINT8  Get_Setup_Item_Value(int page,int index)
{
	 
	return setup_sel[page][index];

}



#endif




