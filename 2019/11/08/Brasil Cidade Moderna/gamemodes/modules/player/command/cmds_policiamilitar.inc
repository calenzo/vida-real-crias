    if(strcmp(cmd, "/prenderarmas", true)==0)
    {
        if(PlayerInfo[playerid][Profissao] != PoliciaMunicipal)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem permiss�o!");

        if(!IsPlayerUniformePM(playerid))
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o est� com o uniforme!");

        new tmp[128], id;

        tmp = strtok(cmdtext, idx);

        if(!strlen(tmp))
            return SendClientMessage(playerid, Erro, "| ERRO | Digite: /Prenderarmas [id]");

        id = strval(tmp);

        if(PlayerInfo[id][Logado] == false)
            return SendClientMessage(playerid, Erro, "| ERRO | Jogador(a) n�o est� conectado(a)!");

        if(playerid == id)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o pode efetuar comando em s� mesmo!");

        if(GetDistanceBetweenPlayers(playerid, id) > 15)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� est� muito longe, chegue mais perto!");

        if(PlayerInfo[id][Estrelas] == 0)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) n�o est� procurado(a)!");

        ResetPlayerWeapons(id);
        format(String, sizeof(String), " | POLICIA | Voc� prendeu todas as armas do(a) jogador(a) %s[%d]!", PlayerInfo[id][Nome], id);
        SendClientMessage(playerid, 0x2894FFAA, String);
        format(String, sizeof(String), " | POLICIA | O(A) Policial %s[%d] prendeu todas as suas armas!", PlayerInfo[playerid][Nome], playerid);
        SendClientMessage(id, 0x2894FFAA, String);
        return 1;
    }
    if(strcmp(cmd, "/perseguicao", true)==0)
    {
        if(PlayerInfo[playerid][Profissao] != PoliciaMunicipal)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem permiss�o!");

        if(!IsPlayerUniformePM(playerid))
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o est� com o uniforme!");

        new tmp[128], id;

        tmp = strtok(cmdtext, idx);

        if(!strlen(tmp))
            return SendClientMessage(playerid, Erro, "| ERRO | Digite: /Perseguicao [id]");

        id = strval(tmp);

        if(PlayerInfo[id][Logado] == false)
            return SendClientMessage(playerid, Erro, "| ERRO | Jogador(a) n�o est� conectado(a)!");

        if(playerid == id)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o pode efetuar comando em s� mesmo!");

        if(GetDistanceBetweenPlayers(playerid, id) > 15)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� est� muito longe, chegue mais perto!");

        if(Abordado[id] == false)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) n�o est� abordado(a)!");

        if(Perseguicao[id] == true)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) j� est� em persegui��o!");

        Perseguicao[id]=true;
        PerseguicaoTime[id] = SetTimerEx("ExitPersecution", 1000*60*5, false, "i", id);
        format(String, sizeof(String), "PERSEGUI��O: O(A) Policial %s[%d] iniciou uma persegui��o no(a) jogador(a) %s[%d] por n�o se render!", PlayerInfo[playerid][Nome], playerid, PlayerInfo[id][Nome], id);
        SendClientMessageToAll(0x2894FFAA, String);
        return 1;
    }
    if(strcmp(cmd, "/localizar", true)==0)
    {
        if(PlayerInfo[playerid][Profissao] != PoliciaMunicipal)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem permiss�o!");

        if(!IsPlayerUniformePM(playerid))
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o est� com o uniforme!");

        new tmp[128], id;

        tmp = strtok(cmdtext, idx);

        if(!strlen(tmp))
            return SendClientMessage(playerid, Erro, "| ERRO | Digite: /Localizar [id]");

        id = strval(tmp);

        if(PlayerInfo[id][Logado] == false)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) n�o conectado(a)!");

        if(playerid == id)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o pode efetuar comando em s� mesmo!");

        if(PlayerInfo[id][Estrelas] == 0)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) n�o est� procurado(a)!");

        if(localizado[id] == true)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) j� foi localizado(a)!");

        TimerProcurando[id] = SetTimerEx("GPSUpdate", 1500, true, "dd", playerid, id);
        SendClientMessage(playerid, Verde, "GPS:{FFFFFF} Jogador(a) localizado(a) com sucesso!");
        return 1;
    }
    if(strcmp(cmd, "/deslocalizar", true)==0)
    {
        if(PlayerInfo[playerid][Profissao] != PoliciaMunicipal)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem permiss�o!");

        if(!IsPlayerUniformePM(playerid))
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o est� com o uniforme!");

        new tmp[128], id;

        tmp = strtok(cmdtext, idx);

        if(!strlen(tmp))
            return SendClientMessage(playerid, Erro, "| ERRO | Digite: /Deslocalizar [id]");

        id = strval(tmp);

        if(PlayerInfo[id][Logado] == false)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) n�o conectado(a)!");

        if(playerid == id)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o pode efetuar comando em s� mesmo!");

        if(PlayerInfo[id][Estrelas] == 0)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) n�o est� procurado(a)!");

        if(localizado[id] == false)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) n�o est� localizado(a)!");

        DisablePlayerCheckpoint(id);
        KillTimer(TimerProcurando[id]);
    	localizado[id]=false;
        SendClientMessage(playerid, Verde, "GPS:{FFFFFF} Jogador(a) deslocalizado(a) com sucesso!");
        return 1;
    }
    if(strcmp(cmd, "/abordar", true) == 0)
	{
        if(PlayerInfo[playerid][Profissao] != PoliciaMunicipal)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem permiss�o!");

        if(!IsPlayerUniformePM(playerid))
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o est� com o uniforme!");

        new tmp[128], id;

        tmp = strtok(cmdtext, idx);

        if(!strlen(tmp))
            return SendClientMessage(playerid, Erro, "| ERRO | Digite: /abordar [ID Procurado(a)]");

        id = strval(tmp);

        if(PlayerInfo[id][Logado] == false)
            return SendClientMessage(playerid, Erro, "| ERRO | Jogador(a) n�o est� conectado(a)!");

        if(playerid == id)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o pode efetuar comando em s� mesmo!");

        if(GetDistanceBetweenPlayers(playerid, id) > 15)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� est� muito longe, chegue mais perto!");

        if(Abordado[id] == true)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) j� est� abordado(a)!");

        if(PlayerInfo[id][Estrelas] == 0)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) n�o est� procurado(a)!");

        Abordado[id]=true;
        GameTextForPlayer(id, "~b~Abordagem!", 3000, 0);
        format(String, sizeof(String), " | ABORDAGEM | Voc� foi abordado pelo Policial %s[%d]", PlayerInfo[playerid][Nome], playerid);
        SendClientMessage(id, 0x2894FFAA, String);
        format(String, sizeof(String), " | ABORDAGEM | Voc� abordou o(a) Jogador(a) %s[%d]", PlayerInfo[id][Nome], id);
        SendClientMessage(playerid, 0x2894FFAA, String);
     	return 1;
	}
    if(strcmp(cmd, "/algemar", true) == 0)
	{
        if(PlayerInfo[playerid][Profissao] != PoliciaMunicipal)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem permiss�o!");

        if(!IsPlayerUniformePM(playerid))
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o est� com o uniforme!");

        new tmp[128], id;

        tmp = strtok(cmdtext, idx);

        if(!strlen(tmp))
            return SendClientMessage(playerid, Erro, "| ERRO | Digite: /algemar [ID Procurado(a)]");

        id = strval(tmp);

        if(PlayerInfo[id][Logado]==false)
            return SendClientMessage(playerid, Erro, "| ERRO | Jogador(a) n�o est� conectado(a)!");

        if(playerid == id)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o pode efetuar comando em s� mesmo!");

        if(GetDistanceBetweenPlayers(playerid, id) > 15)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� est� muito longe, chegue mais perto!");

        if(Abordado[id] == false)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) n�o est� abordado(a)!");

        if(IsPlayerInAnyVehicle(playerid) == 1)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� est� em um veiculo!");

        if(IsPlayerInAnyVehicle(id) == 1)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) Jogador(a) est� em um veiculo!");

        Algemado[id]=true;
        Abordado[id]=false;
        TogglePlayerControllable(id, false);
        SetPlayerSpecialAction(id, SPECIAL_ACTION_CUFFED);
        SetPlayerAttachedObject(id,4,19418,6,-0.031999,0.024000,-0.024000,-7.900000,-32.000011,-72.299987,1.115998,1.322000,1.406000);

        GameTextForPlayer(id, "~b~ALGEMADO!", 3000, 0);
        format(String, sizeof(String), " | ALGEMADO | Voc� algemou o(a) Jogador(a) %s ", PlayerInfo[id][Nome]);
        SendClientMessage(playerid, 0x2894FFAA, String);
        format(String, sizeof(String), " | ALGEMADO | Voc� foi algemado pelo Policial %s ", PlayerInfo[playerid][Nome]);
        SendClientMessage(id, 0x2894FFAA, String);
     	return 1;
	}
    if(strcmp(cmd, "/prender", true) == 0)
    {
        if(PlayerInfo[playerid][Profissao] != PoliciaMunicipal)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem permiss�o!");

        if(!IsPlayerUniformePM(playerid))
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o est� com o uniforme!");

        new tmp[128], id;

        tmp = strtok(cmdtext, idx);

        if(!strlen(tmp))
            return SendClientMessage(playerid, Erro, "| ERRO | /Prender [ID]");

        id = strval(tmp);

        if(PlayerInfo[id][Logado] == false)
            return SendClientMessage(playerid, Erro, "| ERRO | Jogador(a) n�o est� conectado(a)!");

        if(playerid == id)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o pode efetuar comando em s� mesmo!");

        if(PrisonEnum[id][pTempo] != 0)
            return SendClientMessage(playerid, Erro, "| ERRO | O(A) jogador(a) est� preso!");

        if(GetDistanceBetweenPlayers(playerid, id) > 15)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� est� muito longe, chegue mais perto!");

        if(Algemado[id] == false)
            return SendClientMessage(playerid, Erro, "| ERRO | O(a) Jogador(a) precisa estar algemado para prender!");

        Algemado[id]=false;
        RemovePlayerAttachedObject(id, 4);
        TogglePlayerControllable(id, true);
        KillTimer(PerseguicaoTime[playerid]);
        SetPlayerSpecialAction(id, SPECIAL_ACTION_NONE);
        GivePlayerMoney(playerid, PlayerInfo[id][Estrelas]*100);
        PlayerInfo[playerid][Dinheiro] += ( PlayerInfo[id][Estrelas]*100 );
        PrisonEnum[id][pTempo] = PlayerInfo[id][Estrelas]*60;
        format(PrisonEnum[id][pCadeia], 9, "Municipal");
        format(PrisonEnum[id][pMotivo], 15, "Procurado(a)");

        GameTextForPlayer(id, "~w~PRESO!", 3000, 0);
        format(String, sizeof(String), "| PRIS�O | Voc� foi preso pelo Policial %s ( Motivo: Procurado(a) )", PlayerInfo[playerid][Nome]);
        SendClientMessage(id, 0x2894FFAA, String);
        format(String, sizeof(String), "| POLICIA | Voc� prendeu o(a) Jogador(a) %s ( Procurado(a) )", PlayerInfo[id][Nome]);
        SendClientMessage(playerid, 0x2894FFAA, String);
        format(String, sizeof(String), "| POLICIA | Voc� recebeu a recompensa de $%d por prender um jogador(a) que estava sendo procurado(a) pela policia", PlayerInfo[id][Estrelas]*100);
        SendClientMessage(playerid, 0x2894FFAA, String);
        format(String, sizeof(String),"| CORREGEDORIA | O Policial %s[%d] Prendeu o(a) Jogador(a) %s[%d] ( Motivo: Procurado(a) )", PlayerInfo[playerid][Nome], playerid, PlayerInfo[id][Nome], id);
        OnPlayerMessageCorregedoria(C_Corregedoria, String);
        CheckChain(id);
        return 1;
    }