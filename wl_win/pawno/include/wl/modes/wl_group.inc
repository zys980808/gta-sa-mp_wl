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


//=======================================Group======================================
#define DEBUG_GROUP				(true)
#define COLOR_GROUP				(0xFF4F3C)
#define MAX_GROUPS				(MAX_PLAYERS)
#define MAX_GROUP_MEMBERS		(MAX_PLAYERS)
#define MAX_GROUP_NAME			(24)
#define INVALID_GROUP_ID		(0)

enum{
	group_tele_none,
	group_tele_goto,
	group_tele_gethere,
	group_request_none,
	group_request_goto,
	group_request_gethere
};
const
	Group_requestTele_Time = 5000;

//===================================================================================


enum _Group_Info{
	Name[MAX_GROUP_NAME],
	//Member[MAX_GROUP_MEMBERS],
	bool:active,
	Members,
	Color
};
static GroupInfo[MAX_GROUPS][_Group_Info];





stock Group_isValid(groupid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_isValid called");
	#endif
	return (groupid > INVALID_GROUP_ID && groupid < MAX_GROUPS)?true:false;
}
stock Group_getPlayerInvited(playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getPlayerInvited called");
	#endif
	return PlayerInfo[playerid][Group_Invited];
}

stock Group_getName(groupid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getName called");
	#endif
	return GroupInfo[groupid][Name];

}

stock Group_setName(groupid,const group_name[]){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setName called");
	#endif
	format(GroupInfo[groupid][Name],MAX_GROUP_NAME,"%s",group_name);
	return true;
}


stock Group_getMemberAmount(groupid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getMemberAmount called");
	#endif
	if(GroupInfo[groupid][active]){
		return GroupInfo[groupid][Members];
	}
	return 0;
}
stock Group_setMemberAmount(groupid,amount){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setMemberAmount called");
	#endif
	GroupInfo[groupid][Members] = amount;
	return true;
}


stock Group_isPlayerMember(groupid,playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_isPlayerMember called");
	#endif
	return (PlayerInfo[playerid][Group_Joined] == groupid)?true:false;
}
stock Group_setMember(groupid,playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setMember called");
	#endif
	GroupInfo[groupid][Members]++;
	PlayerInfo[playerid][Group_Joined] = groupid;
	PlayerInfo[playerid][Group_Invited] = groupid;
	return true;
}
stock Group_removeMember(groupid,playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_removeMember called");
	#endif
	PlayerInfo[playerid][Group_Joined] = INVALID_GROUP_ID;
	PlayerInfo[playerid][Group_Invited] = INVALID_GROUP_ID;
	GroupInfo[groupid][Members]--;
	return false;
}


stock Group_setColor(groupid,color){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setColor called");
	#endif
	GroupInfo[groupid][Color] = color;
	return true;
}
stock Group_getColor(groupid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getColor called");
	#endif
	
	if(GroupInfo[groupid][active]){
		return GroupInfo[groupid][Color];
	}
	return 0;
}


stock Group_setActive(groupid,bool:Active){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setActive called");
	#endif
	GroupInfo[groupid][active] = Active;
	return true;
}
stock Group_isActive(groupid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_isActive called");
	#endif
	return (Group_isValid(groupid) && GroupInfo[groupid][active])?true:false;
}


stock Group_setPlayerInvited(groupid,playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setPlayerInvited called");
	#endif
	wl_sPlr_Group_Invited(playerid,groupid);
	return true;
}
stock Group_getPlayer(playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getPlayer called");
	#endif
	return wl_gPlr_Group_Joined(playerid);
}

stock Group_setPlayerTele(playerid,teleportype){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setPlayerTele called");
	#endif
	
	wl_sPlr_Group_requestTele(playerid,teleportype);
	return true;
}

stock Group_getPlayerTele(playerid){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getPlayerTele called");
	#endif
	return wl_gPlr_Group_requestTele(playerid);
}

stock Group_setTeleRequester(player,playee){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_setTeleRequester called");
	#endif
	wl_sPlr_Group_requester(player,playee);
	return true;
}
stock Group_getTeleRequester(player){
	#if DEBUG_GROUP
		writetolog("[DEBUG_GROUP]Group_getTeleRequester called");
	#endif
	return wl_gPlr_Group_requester(player);
}






//=========================Group=========================================
#define Group_send(%1,%2,%3) \
do{\
	new \
		sendfstring[MAX_STRING];\
	format(sendfstring,MAX_STRING,(%2),%3);\
	SendClientMessage((%1),COLOR_GROUP,sendfstring);\
}while(FALSE)

stock Group_send(playerid,const sendfstring[]){
	SendClientMessage(playerid,COLOR_GROUP,sendfstring);
}

#define Group_sendAll(%1,%2) \
do{ \
	new \
	sendfstring[MAX_STRING];\
	format(sendfstring,MAX_STRING,(%1),%2);\
	SendClientMessageToAll(COLOR_GROUP,sendfstring);\
}while(FALSE)
stock Group_sendAll(const sendfstring[]){
	SendClientMessageToAll(COLOR_GROUP,sendfstring);
}


#define Group_sendMember(%1,%2,%3) \ 
do{ \
	new \
		sendfstring[MAX_STRING];\
	new const \
		color = Group_getColor((%1));\
	format(sendfstring,MAX_STRING,(%2),%3);\
	loopPlayer(tmptmptmpval){\
		if(Group_getPlayer(tmptmptmpval) == (%1)){\
			SendClientMessage(tmptmptmpval,color,sendfstring);\
		} \
	} \
}while(FALSE)

stock Group_sendMember(groupid,const group_msg[]){
	loopPlayer(playerid){
		if(Group_getPlayer(playerid) == groupid){
			SendClientMessage(playerid,Group_getColor(groupid),group_msg);
		}
	}
}
//===================================================================//

forward Group_rejectTeleport(player,playee,teleportype);//used for timer




stock Group_Help(playerid){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_help called");
	#endif
	
	Group_send(playerid,"[�Ŷ�]�ŶӰ���:");
	Group_send(playerid,"/group create [����]---����С�Ŷ�");
	Group_send(playerid,"/group join ---�����Ŷ�");
	Group_send(playerid,"/group invite [���ID] ---������Ҽ����Ŷ�");
	Group_send(playerid,"/group refuse  ---�ܾ���ǰ�Ŷӵ�����");
	Group_send(playerid,"/group leave ---�˳���ǰ�Ŷ�");
	Group_send(playerid,"/group info [����]---��ʾ�Ŷӵ���Ϣ");
	Group_send(playerid,"------->/group goto ���� gethere [���ID] ---���͵��������<-------");
	Group_send(playerid,"@ ---�������ݿ����Ŷ�����");
	return true;
}





stock Group_PlayerInvitePlayer(inviter,invitee){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerInvitePlayer called");
	#endif
	if(IPC(invitee)){
		if(!Group_getPlayerInvited(invitee)){
			if(!Group_getPlayer(invitee) && Group_getPlayer(inviter)){
				new
					group_name[MAX_GROUP_NAME],
					groupid = Group_getPlayer(inviter);
				
				format(group_name,MAX_GROUP_NAME,"%s",Group_getName(groupid));
				Group_setPlayerInvited(groupid,invitee);
				Group_send(invitee,"[�Ŷ�]�����������'%s'(id:%d)��֯,������ %s(%d)",group_name,groupid,PlayerName(inviter),inviter);
				Group_sendMember( \
					groupid,"[��Ƶ]%s(%d)���� %s(%d)�������ǵ���֯", \
					PlayerName(inviter),inviter,PlayerName(invitee),invitee \
				);
			}else
			{
				Group_send(inviter,"[�Ŷ�]%s(%d)�Ѿ�����֯��,��������",PlayerName(invitee),invitee);
			}
		}else
		{
			Group_send(inviter,"[�Ŷ�]%s(%d)�Ѿ���������,��������",PlayerName(invitee),invitee);
		}
	}else
	{
		Group_send(inviter,"[�Ŷ�]�Է�������");
	}
	return true;
}



stock Group_PlayerCreate(playerid,const group_name[]){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerCreate called");
	#endif
	if(!Group_getPlayer(playerid)){
		new
			groupid;
		for(new i=1;i<MAX_GROUPS;i++){
			if(!Group_isActive(i)){
				groupid = i;
				break;
			}			
		}
		if(
			Group_setName(groupid,group_name) &&
			Group_setMember(groupid,playerid) &&
			Group_setColor(groupid,GetPlayerColor(playerid)) &&
			Group_setActive(groupid,true)
		){
			Group_send(playerid,"[�Ŷ�]�㴴������֯'%s'(id:%d)",Group_getName(groupid),groupid);
		}
	}else
	{
		Group_send(playerid,"[�Ŷ�]���Ѿ���һ����֯��,���ܴ�������֯");
	}
	return true;
}



stock Group_PlayerCheckInfo(playerid,groupid){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerCheckInfo called");
	#endif
	if(Group_isActive(groupid)){
		Group_send(playerid,"[�Ŷ�]=============================================================");
		Group_send(playerid,"[�Ŷ�]'%s'(id:%d) ��Ա",Group_getName(groupid),groupid);
		for(new i,j = Group_getMemberAmount(groupid);i < j;i++){
			loopPlayer(k){
				if(Group_isPlayerMember(groupid,k)){
					Group_send(playerid,"[�Ŷ�]%s(%d)",PlayerName(k),k);
				}
			}
		}
		Group_send(playerid,"[�Ŷ�]============================================================");
	}else
	{
		Group_send(playerid,"[�Ŷ�]��û�м����κ���֯.");
	}
	return true;
}



stock Group_PlayerJoin(playerid){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerJoin called");
	#endif
	if(Group_getPlayerInvited(playerid)){
		new
			groupid = Group_getPlayerInvited(playerid);
		Group_setPlayerInvited(INVALID_GROUP_ID,playerid);
		Group_setMember(groupid,playerid);
		SetPlayerColor(playerid,Group_getColor(groupid));
		Group_Help(playerid);
		Group_sendMember(groupid,"[�Ŷ�]��ӭ %s(%d)�������֯^^",PlayerName(playerid),playerid);
	}else
	{
		Group_send(playerid,"[�Ŷ�]����ʧ��,��ȷ�����ܷ������֯");
	}
	return true;
}


stock Group_PlayerRefuse(playerid){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerRefuse called");
	#endif
	if(Group_getPlayerInvited(playerid)){
		new 
			groupid = Group_getPlayerInvited(playerid);
			//group_name[MAX_GROUP_NAME];
		
		//Group_getName(groupid,group_name);
		Group_sendMember(groupid,"[��Ƶ]%s(%d)�ܾ������Ұ�",PlayerName(playerid),playerid);
		Group_send(playerid,"[�Ŷ�]��ܾ�������֯%s(%d)",Group_getName(groupid),groupid);
		Group_setPlayerInvited(INVALID_GROUP_ID,playerid);
	}else
	{
		Group_send(playerid,"[�Ŷ�]�ܾ���Ч");
	}
	return true;
}

stock Group_PlayerLeave(playerid){
	#if DEBUG_GROUP
		print("[DEBUG_GROUP]Group_PlayerLeave called");
	#endif
	if(Group_getPlayer(playerid)){
		new
			groupid = Group_getPlayer(playerid),
			group_name[MAX_GROUP_NAME];
		
		format(group_name,MAX_GROUP_NAME,"%s",Group_getName(groupid));
		Group_removeMember(groupid,playerid);
		SetPlayerColor(playerid,COLOR_WHITE);
		if(!Group_getMemberAmount(groupid)){
			loopPlayer(i){
				if(Group_getPlayerInvited(i) == groupid){
					Group_setPlayerInvited(INVALID_GROUP_ID,i);
				}
			}
			Group_setActive(groupid,false);
			Group_send(playerid,"[�Ŷ�]���뿪��ԭ������֯,ԭ��֯��ɢ");
		}else
		{
			if(!IPC(playerid)){
				Group_sendMember(groupid,"[��Ƶ](%d)�뿪����֯(ԭ��:����)",playerid);
			}else
			{
				Group_send(playerid,"[�Ŷ�]���뿪��ԭ������֯%s(%d)",group_name,groupid);
				Group_sendMember(groupid,"[��Ƶ]%s(%d)�뿪����֯",PlayerName(playerid),playerid);
			}
		}
	}
	return true;
}


public Group_rejectTeleport(player,playee,teleportype){ debug_public_track("Group_rejectTeleport(player,playee,teleportype){");
	#pragma unused teleportype
	if(Group_getPlayerTele(playee) && Group_getPlayerTele(player)){
		Group_setPlayerTele(playee,group_tele_none);
		Group_setPlayerTele(player,group_tele_none);
		Group_setTeleRequester(player,INVALID_PLAYER_ID);
		Group_send(playee,"[�Ŷ�][����]%s�ܾ�����Ĵ�������(��ʱ��ܾ�)",PlayerName(player));
		Group_send(player,"[�Ŷ�][����]��ܾ���%s�Ĵ�������(��ʱ��ܾ�)",PlayerName(playee));
		remindPlayerText(playee,"%s has rejected ur request",PlayerName(player));
		remindPlayerText(player,"You have rejected %s's request",PlayerName(playee));
	}
	return true;
}

stock Group_acceptTeleport(player,playee,teleportype){
	if(Group_getPlayerTele(playee) && Group_getPlayerTele(player)){
		new
			Float:pposx,
			Float:pposy,
			Float:pposz;
		switch(teleportype){
			case group_tele_goto:{
				GetPlayerPos(player,pposx,pposy,pposz);
				TeleportPlayer(playee,pposx,pposy,pposz);
			}
			case group_tele_gethere:{
				GetPlayerPos(playee,pposx,pposy,pposz);
				TeleportPlayer(player,pposx,pposy,pposz);
			}
		}
		
		Group_setPlayerTele(playee,group_tele_none);
		Group_setPlayerTele(player,group_tele_none);
		Group_setTeleRequester(player,INVALID_PLAYER_ID);	
		Group_send(playee,"[�Ŷ�][����]%s��������Ĵ�������",PlayerName(player));
		Group_send(player,"[�Ŷ�][����]�������%s�Ĵ�������",PlayerName(playee));
		remindPlayerText(playee,"%s has accepted ur request",PlayerName(player));
		remindPlayerText(player,"You have accepted %s's request",PlayerName(playee));	
	}
	return true;
}

stock Group_requestTeleport(player,playee,teleportype){
	if(Group_getPlayer(player) && Group_getPlayer(player) == Group_getPlayer(playee)){
		if(!Group_getPlayerTele(playee) && !Group_getPlayerTele(player)){
			Group_setPlayerTele(playee,teleportype);
			Group_setPlayerTele(player,teleportype+3);
			SetTimerEx("Group_rejectTeleport",Group_requestTele_Time,false,"iii",player,playee,teleportype);
			Group_setTeleRequester(playee,player);
			switch(teleportype){
				case group_tele_goto:{
					Group_send(playee,"[�Ŷ�][����]%s�����͵�������,����%d��������yes����no��Ӧ",PlayerName(player),Group_requestTele_Time/1000);
					Group_send(player,"[�Ŷ�][����]�������͵�%s����,����%ds�ڵȴ���Ӧ",PlayerName(playee),Group_requestTele_Time/1000);
					remindPlayerText(playee,"%s is requesting for teleporting",PlayerName(player));
				}
				case group_tele_gethere:{
					Group_send(playee,"[�Ŷ�][����]%s�����㵽���Ա�,����%d��������yes����no��Ӧ",PlayerName(player),Group_requestTele_Time);
					Group_send(player,"[�Ŷ�][����]������%s�����Ա�,����%d���ڵȴ���Ӧ",PlayerName(playee),Group_requestTele_Time);
					remindPlayerText(playee,"%s is requesting for teleporting",PlayerName(player));
				}
			}
		}else
		{
			Group_send(player,"[�Ŷ�][����]���˴��ڴ���״̬,����ʧ��,���Ժ�����");
		}
	}else
	{
		Group_send(player,"[�Ŷ�][����]˫��������ͬһ��֯,����ʧ��");
	}
	return true;
}


/*
gcmd(gg_group){
	
	if(paramn(1)){
		Group_Help(player());
	}else if(paramsame(1,"goto")){
		if(!paramn(2) && IsNumeric(params(2)) && IsPlayerConnected(parami(2))) 
			Group_requestTeleport(player(),parami(2),group_tele_goto);
		else Group_send(player(),"[�Ŷ�]��������ID��Ч");
	}else if(paramsame(1,"gethere")){
		if(!paramn(2) && IsNumeric(params(2)) && IsPlayerConnected(parami(2))) 
			Group_requestTeleport(player(),parami(2),group_tele_gethere);
		else Group_send(player(),"[�Ŷ�]��������ID��Ч");
	}else if(paramsame(1,"invite")){
		if(!paramn(2) && IsNumeric(params(2)) && IsPlayerConnected(parami(2))) 
			Group_PlayerInvitePlayer(player(),parami(2));
		else Group_send(player(),"[�Ŷ�]��������ID��Ч");
	}else if(paramsame(1,"info")){
		if(paramn(2)) Group_PlayerCheckInfo(playerid,Group_getPlayer(player()));
		else Group_PlayerCheckInfo(player(),parami(2));
	}else if(paramsame(1,"create")){
		if(paramn(2)) Group_send(playerid,"[�Ŷ�]��������Ҫ�������Ŷӵ�����");
		else Group_PlayerCreate(playerid,params(2));
	}else if(paramsame(1,"join")){
		Group_PlayerJoin(player());	
	}else if(paramsame(1,"refuse")){
		Group_PlayerRefuse(player());	
	}else if(paramsame(1,"leave")){
		if(Group_getPlayer(player())) Group_PlayerLeave(player());
		else Group_send(player(),"[�Ŷ�]��û�м����κ���֯,��ô�뿪?");
	}else if(paramsame(1,"help")){
		Group_Help(player());
	}else{
		Group_send(player(),"[�Ŷ�]�������������\"%s\"��Ч,������/group help �鿴����",params);
	}
}
*/
/*
gg_OnPlayerText(playerid,text[]){
	if(text[0] == '@' && text[1]){
		if(Group_getPlayer(playerid)){
			Group_sendMember( \
				Group_getPlayer(playerid),"[��Ƶ]%s(%d):%s", \
				PlayerName(playerid),playerid,text[1]\
			);
		}else{
			Group_send(playerid,"[�Ŷ�]��û�м����κ���֯,����ʹ����Ƶ");
		}
		return false;
	}else
	if(
		text[0] == 'y' && text[1] == 'e' && text[2] == 's' &&
		Group_getPlayerTele(playerid) == group_tele_goto ||
		Group_getPlayerTele(playerid) == group_tele_gethere
	){
		Group_acceptTeleport(playerid,Group_getTeleRequester(playerid),Group_getPlayerTele(playerid));
		return false;
	}else
	if(text[0] == 'n' && text[1] == 'o' && 
		Group_getPlayerTele(playerid) == group_tele_goto ||
		Group_getPlayerTele(playerid) == group_tele_gethere
	){
		Group_rejectTeleport(playerid,Group_getTeleRequester(playerid),Group_getPlayerTele(playerid));
		return false;
	}
	return true;
}


gg_OnPlayerDisconnect(playerid,reason){
	#pragma unused reason
	Group_PlayerLeave(playerid);
	return true;
}
*/