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




/*
enum e_wl_objective_object_Data{
	e_wl_objective_object_modelid,
	Float:e_wl_objective_object_ox,
	Float:e_wl_objective_object_oy,
	Float:e_wl_objective_object_oz,
	Float:e_wl_objective_object_rx,
	Float:e_wl_objective_object_ry,
	Float:e_wl_objective_object_rz
};

static const stock
	wl_s_obj_objectInfo[][e_wl_objective_object_Data] = {
	//��ʽ��ģ�ͣ�����X������Y������Z���Ƕ�X���Ƕ�Y���Ƕ�Z
	//��Ҫ���ӵĻ�,����ѭ�����ʽ
	//ע�⣺���һ����ж���
		{16771, 1854.919922, -2700.062256, 913.993896, 0.0000, 0.0000, 0.0000},
		{1634, 1844.271240, -1413.313965, 13.462946, 0.0000, 0.0000, 179.9996},
		{1634, 1848.378784, -1413.330078, 13.466778, 0.0000, 0.0000, 179.9996},
		{1634, 1852.512939, -1413.291504, 13.449255, 0.0000, 0.0000, 179.9996}//��β�����ж���
	};
*/
/*
wl_objective_object_struction(){
	Object_Object();
	for(new i,j = sizeof(wl_s_obj_objectInfo);i < j;i++)
	CreateDynamicObject(
		wl_s_obj_objectInfo[i][e_wl_objective_object_modelid],
		wl_s_obj_objectInfo[i][e_wl_objective_object_ox],
		wl_s_obj_objectInfo[i][e_wl_objective_object_oy],
		wl_s_obj_objectInfo[i][e_wl_objective_object_oz],
		wl_s_obj_objectInfo[i][e_wl_objective_object_rx],
		wl_s_obj_objectInfo[i][e_wl_objective_object_ry],
		wl_s_obj_objectInfo[i][e_wl_objective_object_rz]
	);
}
*/

wl_objective_object_struction(){
	//Object_Object();
	Streamer_TickRate(100);
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, 200);	
	if(!fexist("wl/objects.ini")){
		printf(" ����obj����,wl/objects.ini ������");
		return;
	}
	new 
		File:ofile = fopen("wl/objects.ini",io_read),
		rstr[256],
		objamount,line;
	while(fread(ofile,rstr)){
		new
			iom,Float:iox,Float:ioy,Float:ioz,Float:irx,Float:iry,Float:irz;
		line++;
		//printf("%d",line);
		if(!sscanf(rstr,"p,iffffff",iom,iox,ioy,ioz,irx,iry,irz)){
			//F_CreateObject(iom,iox,ioy,ioz,irx,iry,irz);
			//printf("%i,%f,%f,%f,%f,%f,%f",om,ox,oy,oz,rx,ry,rz);
			//CreateDynamicObject(om,ox,oy,oz,rx,ry,rz);
			new
				obj = CreateDynamicObject(iom,iox,ioy,ioz,irx,iry,irz,0,0);
			Streamer_SetFloatData(STREAMER_TYPE_OBJECT,obj,E_STREAMER_DRAW_DISTANCE,300.0);
			//CreateDynamicObject(iom,iox,ioy,ioz,irx,iry,irz, .distance = 280.0, .worldid = 0 , .interiorid = 0);//yezizhu:streamer
			//CreateObject(iom,iox,ioy,ioz,irx,iry,irz, .DrawDistance = 280);
			objamount++;
		}else{
			//printf("  obj��������ʧ�ܣ�������:%d",line);
			//printf("  �������ַ���:%s",rstr);
		}
	}
	fclose(ofile);
	printf(" ��̬���(object)����ɹ�,����:%d",objamount);
	
}










