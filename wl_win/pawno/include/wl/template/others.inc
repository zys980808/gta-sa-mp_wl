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





stock wl_tmp_o_setPlayerSkin(playerid,skinid){
	
	wl_sPlr_Player_Skin(playerid,skinid);
	return true;
}

stock wl_tmp_o_getPlayerSkin(playerid){
	return wl_gPlr_Player_Skin(playerid);
}

zcmd(tmp_skin,playerid,params[]){
	if(Skin_isValid(strval(params))){
		SetPlayerSkin(playerid,strval(params));
		wl_tmp_o_setPlayerSkin(playerid,strval(params));
		System_send(playerid,"[ϵͳ]�������Ƥ��,Ƥ�����%d",strval(params));
	}else{
		System_send(playerid,"[ϵͳ]Ƥ��ID��Ч");
	}
	return true;
}
pzcmd(skin) 	rzcmd(tmp_skin);
pzcmd(pifu) 	rzcmd(tmp_skin);
pzcmd(hf)		rzcmd(tmp_skin);
pzcmd(huanfu) 	rzcmd(tmp_skin);

/*
//===================�л�����=====================================

zcmd(tmp_world,playerid,params[]){
	if(isnull(params)){
		if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER){
			SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),0);
		}
		SetPlayerVirtualWorld(playerid,0);	
		System_send(playerid,"[�л�����]���л��ص���~");
		System_send(playerid,"[�л�����]ʹ�÷���:/w [��������]");
	}else{
		new
			vid;
		if(IsNumeric(params)){
			vid = strval(params);
		}else{
			for(new i;params[i];i++){
				vid += params[i]*(i+1)*(i+1)*(i+1);
			}
		}
		if(vid >= 0 && vid <= 1000000000){
			if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER){
				SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),vid);
			}
			SetPlayerVirtualWorld(playerid,vid);
			System_send(playerid,"[�л�����]���л���'%s'������",params);
		}else{
			System_send(playerid,"[�л�����]����������粻�Ϸ�");
		}
	}
	return true;
}		
pzcmd(shijie) 	rzcmd(tmp_world);
pzcmd(w) 	rzcmd(tmp_world);
*/
//===================Save&Load pos=============================================================
static stock
	Float:wl_tmp_o_psavex[MAX_PLAYERS],
	Float:wl_tmp_o_psavey[MAX_PLAYERS],
	Float:wl_tmp_o_psavez[MAX_PLAYERS];
	

zcmd(tmp_sp,playerid,params[]){
	GetPlayerPos(playerid,wl_tmp_o_psavex[playerid],wl_tmp_o_psavey[playerid],wl_tmp_o_psavez[playerid]);
	System_send(playerid,"[ϵͳ]��������Ѿ�����,����/lp ���Դ��͵�����");
	return true;
}
pzcmd(sp) 		rzcmd(tmp_sp);
pzcmd(savepos) 	rzcmd(tmp_sp);

zcmd(tmp_lp,playerid,params[]){
	TeleportPlayer(
		playerid,wl_tmp_o_psavex[playerid],wl_tmp_o_psavey[playerid],wl_tmp_o_psavez[playerid]);
	System_send(playerid,"[ϵͳ]�㱻���͵��ϴα����Ŀ�ĵ�");
	return true;
}
pzcmd(l) 		rzcmd(tmp_lp);
pzcmd(lp) 		rzcmd(tmp_lp);
pzcmd(loadpos) 	rzcmd(tmp_lp);
//==============�񶷷��=====================
static
	pFightsytle_dialogid = 41;
zcmd(tmp_fightstyle,playerid,params[]){
	ShowPlayerDialog(playerid,pFightsytle_dialogid,DIALOG_STYLE_LIST,"�񶷷��","�񶷷��ѡ�� - ��лfly_luck�ṩ\n \n1.һ����\n2.ȭ�����\n3.������(��)\n4.��ս���1\n5.��ս���2\n6.��ս���3\n \n[��ʾ]ѡ��һ��,˫����ѡ�����л���ť.\n[��ʾ]ʹ�÷���:�ܶ���ֹʱ��ס����Ҽ�+F��س�.","�л�","ȡ��");
	return true;
}
pzcmd(fight) 		rzcmd(tmp_fightstyle);
pzcmd(gedou) 		rzcmd(tmp_fightstyle);
pzcmd(ff) 	rzcmd(tmp_fightstyle);

Fightsytle_DialogResponse(playerid, dialogid, response, listitem){
	if(dialogid == pFightsytle_dialogid){
		if(response){
			if(listitem == 2) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_NORMAL),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[��]��ɹ����񶷷���л�Ϊ����.");
			if(listitem == 3) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_BOXING),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[��]��ɹ����񶷷���л�Ϊȭ��.");
			if(listitem == 4) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_KUNGFU),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[��]��ɹ����񶷷���л�Ϊ����.");
			if(listitem == 5) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_KNEEHEAD),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[��]��ɹ����񶷷���л�Ϊ��ս1.");
			if(listitem == 6) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_GRABKICK),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[��]��ɹ����񶷷���л�Ϊ��ս2.");
			if(listitem == 7) 
				SetPlayerFightingStyle(playerid,FIGHT_STYLE_ELBOW),SendClientMessage(playerid,COLOR_LIGHTBLUE,"[��]��ɹ����񶷷���л�Ϊ��ս3.");
		}
	}
}
//=============================================
//=================================================

wl_tmp_o_PlayerRequestSpawn(playerid){
	wl_tmp_o_setPlayerSkin(playerid,GetPlayerSkin(playerid));
	return true;
}

wl_tmp_o_PlayerSpawn(playerid){
	SetPlayerSkin(playerid,wl_tmp_o_getPlayerSkin(playerid));
	return true;
}

wl_tmp_o_PlayerDisconnect(playerid){
	wl_tmp_o_setPlayerSkin(playerid,0);
	return true;
}



//========================================================

//======================�������Ƿ��л�/����======================================
/*
Pause_OnPlayerSpawn(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
Pause_OnPlayerDeath(playerid, killerid, reason){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	SetPVarInt(killerid,"wl_plr_online",true);
	SetPVarInt(killerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
*/
Pause_OnPlayerText(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return false;
}
Pause_OnPlayerCommandText(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return false;
}
/*
Pause_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
Pause_OnPlayerExitVehicle(playerid, vehicleid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
*/
Pause_OnPlayerStateChange(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
/*
Pause_OnPlayerSelectedMenuRow(playerid, row){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
Pause_OnPlayerExitedMenu(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
*/
Pause_OnPlayerKeyStateChange(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
Pause_OnPlayerUpdate(playerid){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
/*
Pause_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
Pause_OnPlayerClickPlayer(playerid, clickedplayerid, source){
	SetPVarInt(playerid,"wl_plr_online",true);
	SetPVarInt(playerid,"wl_plr_online_tick",GetTickCount());
	return true;
}
*/
Pause_struction(){
	SetTimer("Pause_Check",999*3,true);
}

forward Pause_Check();
public Pause_Check(){ debug_public_track("Pause_Check(){");
	new
		gPause_gTick = GetTickCount();
	for(new playerid;playerid < MAX_PLAYERS;playerid++){
		if(IsPlayerConnected(playerid)){
			if(GetPVarInt(playerid,"wl_plr_online")){
				if(gPause_gTick - GetPVarInt(playerid,"wl_plr_online_tick") > 5000){
					SetPVarInt(playerid,"wl_plr_online",false);
				}
			}
		}
	}
}

//=============================================================
zcmd(tmp_kill,playerid,params[]){
	SetPlayerHealth(playerid,0);
	System_send(playerid,"[ϵͳ]��ɱ�ɹ�...");
	return true;
}
pzcmd(k) 		rzcmd(tmp_kill);
pzcmd(kill) 	rzcmd(tmp_kill);
pzcmd(zisha) 	rzcmd(tmp_kill);


zcmd(tmp_search,playerid,params[]){
	if(isnull(params)){
		System_send(playerid,"[ϵͳ]��������ҵĹؼ���");
	}
	else {
		searchPlayer(playerid,params);
	}
	return true;
}
pzcmd(id) 	rzcmd(tmp_search);
pzcmd(search) 	rzcmd(tmp_search);
pzcmd(chazhao) 	rzcmd(tmp_search);


zcmd(tmp_parachute,playerid,params[]){
	GivePlayerWeapon(playerid,WEAPON_PARACHUTE,1);
	return true;
}

pzcmd(jls) 			rzcmd(tmp_parachute);
pzcmd(jiangluosan) 	rzcmd(tmp_parachute);
pzcmd(parachute) 	rzcmd(tmp_parachute);

zcmd(tmp_dive,playerid,params[]){
	new
		Float:ppx,
		Float:ppy,
		Float:ppz;
	GetPlayerPos(playerid,ppx,ppy,ppz);
	SetPlayerPos(playerid,ppx,ppy,ppz+500);
	GivePlayerWeapon(playerid,WEAPON_PARACHUTE,1);
	System_send(playerid,"[ϵͳ]һ�ɳ���!!!");
	return true;
}
pzcmd(tiaosan) 	rzcmd(tmp_dive);
pzcmd(dive) 	rzcmd(tmp_dive);
pzcmd(ts) 		rzcmd(tmp_dive);


zcmd(tmp_afk_sta,playerid,params[]){
	TogglePlayerControllable(playerid, false);
	if(isnull(params)) System_send(playerid,"[ϵͳ]%s(%d)��ʱ�뿪(ԭ��:δ֪)",PlayerName(playerid),playerid);
	else System_send(playerid,"[ϵͳ]%s(%d)��ʱ�뿪(ԭ��:%s)",PlayerName(playerid),playerid,params);
	new
		bubble[MAX_MSG_STR];
	format(bubble,sizeof(bubble),"%s(%d)�ڹһ�(ԭ��:%s)",pName(playerid),playerid,((isnull(params))?("δ֪"):(params)));
	SetPlayerChatBubble(playerid,bubble, GetPlayerColor(playerid), 50, 1000*60*60*60);
	//if(paramn(1)) System_sendAll("[ϵͳ]%s(%d)��ʱ�뿪(ԭ��:δ֪)",PlayerName(playerid),playerid);
	//else System_sendAll("[ϵͳ]%s(%d)��ʱ�뿪(ԭ��:%s)",PlayerName(playerid),playerid,params(1));
	return true;
}
pzcmd(afk) 		rzcmd(tmp_afk_sta);
pzcmd(likai) 	rzcmd(tmp_afk_sta);

zcmd(tmp_afk_end,playerid,params[]){
	TogglePlayerControllable(playerid,true);
	System_send(playerid,"[ϵͳ]%s(%d)����!",PlayerName(playerid),playerid);
	SetPlayerChatBubble(playerid,"�ҹ�����!", GetPlayerColor(playerid), 50, 1000*5);
	//System_sendAll("[ϵͳ]%s(%d)����!",PlayerName(playerid),playerid);
	return true;
}
pzcmd(huilai) 	rzcmd(tmp_afk_end);
pzcmd(back) 	rzcmd(tmp_afk_end);


zcmd(tmp_jetpack,playerid,params[]){
	System_send(playerid,"[ϵͳ]�ٻ�JetPack�ɹ�");
	SetPlayerSpecialAction(playerid, 2);
	return true;
}
pzcmd(feixingqi) 	rzcmd(tmp_jetpack);
pzcmd(fxq) 			rzcmd(tmp_jetpack);
pzcmd(jetpack) 		rzcmd(tmp_jetpack);
//==========Count down=====================
forward wl_tmp_CountDown();

static
	wl_tmp_gCount = 5,
	wl_tmp_gCountText[5][5]=
{
   "~r~1",
   "~y~2",
   "~b~3",
   "~g~4",
   "~p~5"
},
	Float:wl_tmp_gCountrange[3];

public wl_tmp_CountDown(){ debug_public_track("wl_tmp_CountDown(){");
	if(wl_tmp_gCount > 0){
		wl_tmp_gCount--;
		loopPlayer(i){
			if(IsPlayerInRangeOfPoint(i,100,wl_tmp_gCountrange[0],wl_tmp_gCountrange[1],wl_tmp_gCountrange[2])){
				PlayerPlaySound(i,1056);
				GameTextForPlayer(i,wl_tmp_gCountText[wl_tmp_gCount],2500,3);
			}
		}
		SetTimer("wl_tmp_CountDown",998,false);
	}else{
		loopPlayer(i){
			if(IsPlayerInRangeOfPoint(i,100,wl_tmp_gCountrange[0],wl_tmp_gCountrange[1],wl_tmp_gCountrange[2])){
				PlayerPlaySound(i,1057);
				GameTextForPlayer(i,"~g~GO~r~!!~n~~g~GO~r~!!~n~~g~GO~r~!!", 2500, 3);
			}
		}
		wl_tmp_gCount = 5;
	}
	return true;
}

zcmd(tmp_countdown,playerid,params[]){
	if(wl_tmp_gCount >= 5){
		GetPlayerPos(playerid,wl_tmp_gCountrange[0],wl_tmp_gCountrange[1],wl_tmp_gCountrange[2]);
		System_send(playerid, "[�ɹ�] ����ʱ��ʼ");
		wl_tmp_CountDown();
	}else{
		System_send(playerid, "[����] ��Ǹ, ����ʱ�Ѿ�����....");
	}
	return true;
}
pzcmd(count) 	rzcmd(tmp_countdown);
pzcmd(djs) 		rzcmd(tmp_countdown);
pzcmd(daoshu) 	rzcmd(tmp_countdown);
//=============================//

	zcmd(shang,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz+2);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px,py,pz+2);
		}
		return true;
	}
	zcmd(xia,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz-2);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px,py,pz-2);
		}
		return true;
	}
	zcmd(zuo,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px+2,py,pz);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px+2,py,pz);
		}
		return true;
	}
	zcmd(you,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px-2,py,pz);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px-2,py,pz);
		}
		return true;
	}
	zcmd(qian,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px,py+2,pz);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px,py+2,pz);
		}
		return true;
	}
	zcmd(hou,playerid,params[]){
		new
			Float:px,Float:py,Float:pz;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
			GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			SetVehiclePos(GetPlayerVehicleID(playerid),px,py-2,pz);
		}else{
			GetPlayerPos(playerid,px,py,pz);
			SetPlayerPos(playerid,px,py-2,pz);
		}
		return true;
	}
	//
	zcmd(zican,playerid,params[]){
		new
			Float:ph;
		GetPlayerHealth(playerid,ph);
		SetPlayerHealth(playerid,ph-5);
		System_send(playerid,"[ϵͳ]�����Բ�ing(ʣ��Ѫ��:%f) -0-",ph-5);
		return true;
	}

