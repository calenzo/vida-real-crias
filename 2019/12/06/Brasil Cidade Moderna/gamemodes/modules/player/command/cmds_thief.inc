    if(strcmp(cmd, "/roubargas", true)==0)
    {
        if(PlayerInfo[playerid][Profissao] != LadraoGas)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem permiss�o!");

        if(VehicleSGas[playerid][VSGas] == 0)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o pegou seu ve�culo de ladr�o!");

        if(AmountGas[playerid] != 0)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� j� pegou informa��o de roubo de g�s!");

        AmountGas[playerid] = 5;
        SendClientMessage(playerid, 0xFF8080AA, "| LADR�O | Foi informado que tem 5 buj�es de g�s marcando bobeira!!!");
        SendClientMessage(playerid, 0xFF8080AA, "| LADR�O | V� at� o checkpoint marcado no mini-mapa para come�ar a roubar!");

        new i = random(sizeof(LocationsGas));

        format(PLGas[playerid][pLocality], 40, LocationsGas[i][Locality]);
        PLGas[playerid][pGasPosX] = LocationsGas[i][GasPosX];
        PLGas[playerid][pGasPosY] = LocationsGas[i][GasPosY];
        PLGas[playerid][pGasPosZ] = LocationsGas[i][GasPosZ];
        PLGas[playerid][pGetWork] = LocationsGas[i][GetWork];

        CPS_Gas[playerid] = CPS_AddCheckpoint(LocationsGas[i][GasPosX], LocationsGas[i][GasPosY], LocationsGas[i][GasPosZ], 1.0, 999999999);
        ObjectGas[playerid] = CreateObject(1370, LocationsGas[i][GasPosX], LocationsGas[i][GasPosY], LocationsGas[i][GasPosZ], 0.0, 0.0, 0.0);
        return 1;
    }
    if(strcmp(cmd, "/pegargas", true)==0) //{00C40A} {FF8000}
    {
        if(PlayerInfo[playerid][Profissao] != LadraoGas)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem permiss�o!");

        if(AmountGas[playerid] == 0)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem pegou nenhuma informa��o de roubo de g�s!");

        if(VehicleSGas[playerid][VSGas] == 0)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o pegou seu ve�culo de ladr�o!");

        if(IsVehicleInRangeOfPoint(playerid, VehicleSGas[playerid][VSGas], 10))
            return SendClientMessage(playerid, Erro, "| ERRO | Seu ve�culo de ladr�o ta muito longe!");

        if(!IsPlayerInRangeOfPoint(playerid, 10.0, PLGas[playerid][pGasPosX], PLGas[playerid][pGasPosY], PLGas[playerid][pGasPosZ]))
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o est� no local informado!");

        if(!IsPlayerInRangeOfPoint(playerid, 2.0, PLGas[playerid][pGasPosX], PLGas[playerid][pGasPosY], PLGas[playerid][pGasPosZ]))
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� est� longe, v� mas perto do buj�o de g�s!");

        CaughtGas[playerid] = true;
        DestroyObject(ObjectGas[playerid]);
        SetPlayerAttachedObject(playerid, 3, 1370, 6, 0.339000, 0.235000, 0.090999, 69.699974, 118.899940, 36.300010, 0.699999, 0.699999, 0.699999);
        return 1;
    }
    if(!strcmp(cmdtext, "/edit", true))
    {
        EditAttachedObject(playerid, 3);
        SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: You now edit your attached object on index slot 0!");
        return 1;
    }
    if(strcmp(cmd, "/colocargas", true)==0)
    {
        if(PlayerInfo[playerid][Profissao] != LadraoGas)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem permiss�o!");

        if(CaughtGas[playerid] == false)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem nenhum Buj�o de G�s na m�o!");

        AttachObjectToVehicle(1370, 478, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);

        //format(String, sizeof(String), "| LADR�O | Agora tem s� mais %d informa��o de roubo de g�s!", AmountGas[playerid]);
        //SendClientMessage(playerid, 0xFF8080AA, String);
        //format(String, sizeof(String), "| LADR�O | V� at� o pr�ximo roubo de g�s localizado em %s", LocationsGas[playerid][Locality]);
        //SendClientMessage(playerid, 0xFF8080AA, String);
        return 1;
    }
    if(strcmp(cmd, "/cancelarroubo", true)==0)
    {
        if(PlayerInfo[playerid][Profissao] != LadraoGas)
            return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem permiss�o!");

        return 1;
    }