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





#define INVALID_TEAM_ID		(-1)
#define COLOR_TEAM			(COLOR_LIGHTBLUE)


//===================team handle==================================
#define team_send(%1,%2,%3)	\
	format(ssstr,MAX_MSG_STR,(%2),%3); \
	SendClientMessage((%1),COLOR_TEAM,ssstr)
	
stock team_send(playerid,const sendfstring[]){
	SendClientMessage(playerid,COLOR_TEAM,sendfstring);
}

#define team_sendAll(%1,%2)	\
	format(ssstr,MAX_MSG_STR,(%1),%2); \
	SendClientMessageToAll(COLOR_TEAM,ssstr)
	
stock team_sendAll(const sendfstring[]){
	SendClientMessageToAll(COLOR_TEAM,sendfstring);
}
//===================================================================================

/*
stock GetPlayerAdminLevel(playerid){
	return CallRemoteFunction("GetPlayerAdminLevel","i",playerid);
}
*/


static stock
	
	//gTeam_pLevel[MAX_PLAYERS],

	//gTeam_pTeam[MAX_PLAYERS],
	gTeam_index = 10;


stock team_spLevel(playerid,level){
	SetPVarInt(playerid,"wl_team_player_level",level);
	return true;
}

stock team_gpLevel(playerid){
	return GetPVarInt(playerid,"wl_team_player_level");
}

stock team_spTeam(playerid,teamid){
	SetPVarInt(playerid,"wl_team_player_team",teamid);
	return true;
}

stock team_gpTeam(playerid){
	return GetPVarInt(playerid,"wl_team_player_team");
}

stock team_spInNew(playerid){
	++gTeam_index;
	return team_spTeam(playerid,gTeam_index);
}


team_struct(){
	for(new i;i<MAX_PLAYERS;i++){
		team_spTeam(i,INVALID_TEAM_ID);
		team_spLevel(i,0);
	}
}

team_pregister(playerid){
	#pragma unused playerid
	gini_writei(acc_pLevel,0);
}

team_plogin(playerid){
	team_spLevel(playerid,gini_readi(acc_pLevel));
	//team_sp(playerid,gini_readi(acc_pLevel));
}

team_playerConnect(playerid){
	new
		endpos,
		plrTeamslot = INVALID_TEAM_ID;
	if(strfind(pName(playerid),"[") == 0 && (endpos = strfind(pName(playerid),"]")) != -1){
		loopPlayer(i){
			if(playerid == i)continue;
			if(!strcmp(pName(playerid),pName(i),true,endpos)){
				plrTeamslot = team_gpTeam(i);
				break;
			}
		}
		if(plrTeamslot != INVALID_TEAM_ID){
			team_spTeam(playerid,plrTeamslot);
		}
		else {
			team_spInNew(playerid);
		}
	}
	else {
		team_spTeam(playerid,INVALID_TEAM_ID);
	}
}

team_playerDisconnect(playerid){
   team_spTeam(playerid,INVALID_TEAM_ID);
   team_spLevel(playerid,0);
}

team_playerText(playerid,text[]){
	if(text[0] == '!' && text[1]){
        if(team_gpTeam(playerid) != INVALID_TEAM_ID){
            new 
				sendstr[MAX_MSG_STR];
            format(sendstr, sizeof(sendstr),"    [����]%s(%d): %s", pName(playerid),playerid, text[1]);
			loopPlayer(i){
				if(team_gpTeam(playerid) == team_gpTeam(i)){
					SendClientMessage(i,COLOR_TEAM,sendstr);
				}
			}
			return false;
		}
	}
    return true;
}


TODOList_teaminc(){}
/*
zcmd(team_handle,playerid,params[]){ //todo
	new
		str1[128],str2[128],
		id;
	sscanf(params,"ss",str1,str2);
	id = strval(str2);
	//printf("%d_ %s",id,str2);
	if(!strcmp("makeadmin",str1)){
		if(GetPlayerAdminLevel(playerid) < 3 && team_gpLevel(playerid) < 5){
			team_send(playerid,"[�Ŷ�]��û���㹻��Ȩ��ʹ�ø�����");
			return true;
		}
		if(isnull(str2)){
			team_send(playerid,"[�Ŷ�]���������ID");
			return true;
		}
		if(!IsNumeric(str2)){
			team_send(playerid,"[�Ŷ�]ID���Ϸ�");
			return true;
		}
		if(!IsPlayerConnected(id)){
			team_send(playerid,"[�Ŷ�]IDΪ%d����Ҳ�����",id);
			return true;
		}
		if(team_gpTeam(id) == INVALID_TEAM_ID){
			team_send(playerid,"[�Ŷ�]����Ҳ������κ�һ���Ŷ�");
			return true;
		}
		if(!pLogged(id)){
			team_send(playerid,"[�Ŷ�]�����δ��½����������Ϊ�Ŷӹ���Ա");
			return true;
		}
		if(GetPlayerAdminLevel(playerid) >= 3){
			gini_open(player_getAccount(id));
			gini_writei(acc_pLevel,5);
			gini_save();
			gini_close();
			team_spLevel(id,5);
			team_send(playerid,"[�Ŷ�]������%s(%d)Ϊ5���Ŷӹ���Ա",pName(id),id);
			team_send(id,"[�Ŷ�]�㱻%s(%d)����Ϊ5���Ŷӹ���Ա,�����������Ŷӳ�Ա!",pName(playerid),playerid);
		}
		else if(team_gpLevel(playerid) >= 5 && team_gpTeam(id) == team_gpTeam(playerid)){
			gini_open(player_getAccount(id));
			gini_writei(acc_pLevel,3);
			gini_save();
			gini_close();
			team_spLevel(id,3);
			team_send(playerid,"[�Ŷ�]������%s(%d)Ϊ3���Ŷӹ���Ա",pName(id),id);
			team_send(id,"[�Ŷ�]�㱻%s(%d)����Ϊ3���Ŷӹ���Ա,�����������Ŷӳ�Ա!",pName(playerid),playerid);
		}
		else {
			team_send(playerid,"[�Ŷ�]���÷����㲻��ͬһ�Ŷӣ����öԷ�Ϊ3������Աʧ��");
		}
	}
	else if(!strcmp("unmakeadmin",str1)){
		if(GetPlayerAdminLevel(playerid) < 3 && team_gpLevel(playerid) < 5){
			team_send(playerid,"[�Ŷ�]��û���㹻��Ȩ��ʹ�ø�����");
			return true;
		}
		if(isnull(str2)){
			team_send(playerid,"[�Ŷ�]���������ID");
			return true;
		}
		if(!IsNumeric(str2)){
			team_send(playerid,"[�Ŷ�]ID���Ϸ�");
			return true;
		}
		if(!IsPlayerConnected(id)){
			team_send(playerid,"[�Ŷ�]IDΪ%d����Ҳ�����",id);
			return true;
		}
		if(team_gpTeam(id) == INVALID_TEAM_ID){
			team_send(playerid,"[�Ŷ�]����Ҳ������κ�һ���Ŷ�");
			return true;
		}
		if(!pLogged(id)){
			team_send(playerid,"[�Ŷ�]�����δ��½����������Ϊ�Ŷӹ���Ա");
			return true;
		}
		if(GetPlayerAdminLevel(playerid) >= 3){
			gini_open(player_getAccount(id));
			gini_writei(acc_pLevel,0);
			gini_save();
			gini_close();
			team_spLevel(id,0);
			team_send(playerid,"[�Ŷ�]��ȡ����%s(%d)�Ŷӹ���ԱȨ��",pName(id),id);
			team_send(id,"[�Ŷ�]�㱻%s(%d)ȡ�����Ŷӹ���ԱȨ��!",pName(playerid),playerid);
		}
		else if(team_gpLevel(playerid) >= 5 && team_gpTeam(id) == team_gpTeam(playerid)){
			gini_open(player_getAccount(id));
			gini_writei(acc_pLevel,0);
			gini_save();
			gini_close();
			team_spLevel(id,0);
			team_send(playerid,"[�Ŷ�]��ȡ����%s(%d)�Ŷӹ���ԱȨ��",pName(id),id);
			team_send(id,"[�Ŷ�]�㱻%s(%d)ȡ�����Ŷӹ���ԱȨ��!",pName(playerid),playerid);
		}
		else {
			team_send(playerid,"[�Ŷ�]���÷����㲻��ͬһ�Ŷӣ�ȡ���Է��Ŷӹ���Աʧ��");
		}
	}
	else if(!strcmp("kill",str1)){
		if(!team_gpLevel(playerid)){
			team_send(playerid,"[�Ŷ�]����Ȩʹ�ø�����");
			return true;
		}
		if(isnull(str2) || !IsPlayerConnected(id)){
			team_send(playerid,"[�Ŷ�]����������ID������/����");
			return true;
		}
		if(team_gpTeam(id) != team_gpTeam(playerid)){
			team_send(playerid,"[�Ŷ�]�Է�����ͬ�ӳ�Ա");
			return true;
		}
		SetPlayerHealth(id,0);
		team_send(id,"[�Ŷ�]�㱻�Ŷӹ���Ա%s(%d)����",pName(playerid),playerid);
		team_send(playerid,"[�Ŷ�]��ʹ�ù�������Ŷӳ�Ա%s(%d)��Ѫ������Ϊ0",pName(id),id);
	}
	else if(!strcmp("kick",str1)){
		if(!team_gpLevel(playerid)){
			team_send(playerid,"[�Ŷ�]����Ȩʹ�ø�����");
			return true;
		}
		if(isnull(str2) || !IsPlayerConnected(id)){
			team_send(playerid,"[�Ŷ�]����������ID������/����");
			return true;
		}
		if(team_gpTeam(id) != team_gpTeam(playerid)){
			team_send(playerid,"[�Ŷ�]�Է�����ͬ�ӳ�Ա");
			return true;
		}
		Kick(id);
		team_send(id,"[�Ŷ�]�㱻�Ŷӹ���Ա%s(%d)�߳�������",pName(playerid),playerid);
		team_send(playerid,"[�Ŷ�]��ʹ�ù�������Ŷӳ�Ա%s(%d)�߳�������",pName(id),id);
	}
	else if(!strcmp("goto",str1)){
		if(!team_gpLevel(playerid)){
			team_send(playerid,"[�Ŷ�]����Ȩʹ�ø�����");
			return true;
		}
		if(isnull(str2) || !IsPlayerConnected(id)){
			team_send(playerid,"[�Ŷ�]����������ID������/����");
			return true;
		}if(team_gpTeam(id) != team_gpTeam(playerid)){
			team_send(playerid,"[�Ŷ�]�Է�����ͬ�ӳ�Ա");
			return true;
		}
		TeleportPlayer(playerid,pX(id),pY(id),pZ(id),pAngle(id),pInterior(id),false,pVirtualWorld(id));
		team_send(id,"[�Ŷ�]�Ŷӹ���Ա%s(%d)���͵�������",pName(playerid),playerid);
		team_send(playerid,"[�Ŷ�]�㴫�͵��Ŷӳ�Ա%s(%d)����",pName(id),id);
	}
	else if(!strcmp("gethere",str1)){
		if(!team_gpLevel(playerid)){
			team_send(playerid,"[�Ŷ�]����Ȩʹ�ø�����");
			return true;
		}
		if(isnull(str2) || !IsPlayerConnected(id)){
			team_send(playerid,"[�Ŷ�]����������ID������/����");
			return true;
		}if(team_gpTeam(id) != team_gpTeam(playerid)){
			team_send(playerid,"[�Ŷ�]�Է�����ͬ�ӳ�Ա");
			return true;
		}
		TeleportPlayer(id,pX(playerid),pY(playerid),pZ(playerid),pAngle(playerid),pInterior(playerid),false,pVirtualWorld(playerid));
		team_send(id,"[�Ŷ�]�㱻���͵��Ŷӹ���Ա%s(%d)����",pName(playerid),playerid);
		team_send(playerid,"[�Ŷ�]�Ŷӳ�Ա%s(%d)���㴫�͵�������",pName(id),id);
	}
	else if(!strcmp("help",str1)){
		#define DG_TEAM_HELP_CAPTION	"�Ŷ�ϵͳ����:"
		#define DG_TEAM_HELP_INFO	"����:ӵ����ͬ�ӱ����ҽ��Զ�����Ŷ�\n \n��ҿ�������:/t help\n��ͨ��Ա��������: !������Ϣ - ��������\n\
									3���Ŷӹ���Ա����:\n    /t goto/gethere [���id] - ���д��Ͳ���\n    \
									/t kill - ɱ��ָ���Ŷӳ�Ա\n    /t kick - ��ָ����Ա�߳�������\n\
									5��/����������Ա����:\n    /t makeadmin [���id] - ��ָ���������Ϊ�Ŷӹ���Ա\n    /t unmakeadmin [���id] - ȡ����ҹ���ԱȨ��\n"
		#define DG_TEAM_HELP_BUTTON1	"ȷ��"
		#define DG_TEAM_HELP_BUTTON2	"ȡ��"
		ShowPlayerDialog(playerid,1,DIALOG_STYLE_LIST,DG_TEAM_HELP_CAPTION,DG_TEAM_HELP_INFO,DG_TEAM_HELP_BUTTON1,DG_TEAM_HELP_BUTTON2);
	}
	else if(!strcmp("info",str1)){
		loopPlayer(i){
			//if(!pLogged(i) || team_gpTeam(i) == INVALID_TEAM_ID) continue;
			team_send(playerid,"debug:%d(%s) team:%d level:%d logged:%d",i,pName(i),team_gpTeam(i),team_gpLevel(i),pLogged(i));
		}
	}
	else {
		team_send(playerid,"[�Ŷ�]�������������'%s'������",params);
	}
	return true;
}
pzcmd(t){rzcmd(team_handle);}
pzcmd(team){rzcmd(team_handle);}
*/






