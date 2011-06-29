/*
								The MIT License  
								
	Copyright (c) <2010> <yezizhu>  
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:  

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.  
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.  
	==================================
	��Ȩ(c) <2010> <yezizhu>  

	ʹ�ø�����֤����������������Ȩ�ޣ���ѣ��κ��˿��Եõ����������������ĵ���һ��������
	���Ҿ�Ӫ�����������κ����ƣ����������Ƶ�ʹ�á����ơ��޸ġ��ϲ������桢���С����Ŵ���֤�顢���߳��۸������Ŀ�����Ȩ����
	ͬʱ���������Щ�������û�������ЩȨ����ʹ����������������  
	
	���ϵİ�Ȩ֪ͨ��Ȩ��֪ͨӦ�ð��������и������Ŀ����л�������������������ʵ�����С�
	
	�������������������ṩ��û���κ���ʽ�ĵ�������������ȷ�ػ��߰����ģ�������Щ���ǲ�����ҵ���ʵĵ��������ơ�
	�ʺ�һ���ض�����;���Ҳ����ַ������ߺͰ�Ȩ���������κγ��϶�ʹ�ø������漰���κ�Ҫ���𺦻����������ζ���Ӧ����
	�����������������û���ֻ�Ǻ�ͬ��ʽ��������Ȩ����������ʽ�������������������÷�Χ�ڡ������������ϵ����������ʹ�û�����������������������Ϊ��  
	=====================================   
*/	


//#include <wl\objective\wl_objective_spawn_h>
/*
enum e_wl_obj_spawn_Data{
	Float:e_wl_obj_spawn_x,
	Float:e_wl_obj_spawn_y,
	Float:e_wl_obj_spawn_z,
	Float:e_wl_obj_spawn_a,
	e_wl_obj_spawn_Interior,
	e_wl_obj_spawn_String[MAX_STRING]
};



static const stock
	wl_s_obj_spawnInfo[][e_wl_obj_spawn_Data] = {
	//��ʽ:����������X������������Y������������Z����������Ƕȣ���������ʾ����
	//��Ҫ���ӵĻ�,����ѭ�����ʽ
	//ע�⣺���һ����ж���
		{409.2281,2573.1426,16.3672,90.0, 0, ">> ������ /aa �����ؼ���"},
		{1384.4961,-2442.0063,13.5547,90.0, 0,">> ������ /ls"},
		{1318.9706,1266.0952,10.8203,90.0, 0, ">> ������ /lv"},
		{-1642.7762,-197.9458,14.1484,90.0, 0, ">> ������ /sf"}//��β�����ж���
	};
*/
wl_obj_spawn_SpawnPlayer(playerid){
	new
		pos = random(sizeof(wl_s_obj_spawnInfo));
	TeleportPlayer(
		playerid,
		wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_x],
		wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_y],
		wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_z],
		wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_a],
		wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_Interior],
		true
	);
	System_send(playerid,wl_s_obj_spawnInfo[pos][e_wl_obj_spawn_String]);
	return true;
}
