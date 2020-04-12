#include YSI\y_hooks

enum e_vrpz
{
    Float:vrpz_x,
    Float:vrpz_y,
    Float:vrpz_z
};

new vr_pizzaboy[6][e_vrpz] =
{
    {2121.20, -1779.24, 12.96},
    {2121.16, -1776.75, 12.95},
    {2121.12, -1774.24, 12.96},
    {2121.13, -1771.60, 12.96},
    {2121.12, -1769.12, 12.96},
    {2121.00, -1766.65, 12.96}
};

enum e_pbdt
{
    Float:pbdt_x,
    Float:pbdt_y,
    Float:pbdt_z,
    pbdt_value
};

enum e_pbif
{
    Float:pbif_x,
    Float:pbif_y,
    Float:pbif_z,
    pbif_value
};

new pb_data[12][e_pbdt] =
{
    {802.90, -1731.16, 13.54, 155},
    {760.19, -1660.28, 4.36, 120},
    {851.89, -1413.33, 13.36, 125},
    {1183.66, -1264.12, 15.17, 200},
    {1230.58, -1017.63, 32.60, 180},
    {1193.52, -1020.56, 32.54, 140},
    {1089.81, -1093.62, 25.50, 105},
    {1268.93, -908.62, 42.88, 120},
    {2652.80, -1997.71, 13.55, 160},
    {2306.96, -1666.37, 14.54, 100},
    {2505.80, -1682.95, 13.54, 220},
    {2175.58, -999.38, 62.97, 130}
};

new pb_info[MAX_PLAYERS][e_pbif];
new pb_pizzas[MAX_PLAYERS];
new Text3D:pb_label[MAX_PLAYERS];
new pb_pickup[MAX_PLAYERS];
new pb_mapicon[MAX_PLAYERS];
//new vp_pizzaboy[MAX_PLAYERS][e_vppz]; office.inc

hook OnGameModeInit()
{
    CreateDynamicPickup(1582, 1, 2122.31, -1789.06, 13.55, -1, -1, -1, 30.0);
    CreateDynamic3DTextLabel("{FFFFFF}Precione {FF0000}Y{FFFFFF} e crie um\nve�culo profiss�o", 0xFFFFFFFF, 2122.31, -1789.06, 13.55, 30.0);
	return 1;
}

hook OnVehicleDeath(vehicleid, killerid)
{
    if(vehicleid == vp_pizzaboy[killerid][vp_vehicle])
    {
        DestroyVehicle(vp_pizzaboy[killerid][vp_vehicle]);
        DestroyDynamic3DTextLabel(vp_pizzaboy[killerid][vp_label]);
        vp_pizzaboy[killerid][vp_vehicle] = 0;
        SendClientMessage(killerid, Yellow, "Seu ve�culo profiss�o foi destruido ou respawnado");
        return 1;
    }
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(vp_pizzaboy[playerid][vp_vehicle])
        { DestroyVehicle(vp_pizzaboy[playerid][vp_vehicle]); }
    if(vp_pizzaboy[playerid][vp_label])
        { DestroyDynamic3DTextLabel(vp_pizzaboy[playerid][vp_label]); }

    if(pb_pickup[playerid])
        { DestroyDynamicPickup(pb_pickup[playerid]); }
    if(pb_mapicon[playerid])
        { DestroyDynamicMapIcon(pb_mapicon[playerid]); }
    if(pb_label[playerid])
        { DestroyDynamic3DTextLabel(pb_label[playerid]); }

    vp_pizzaboy[playerid][vp_vehicle] = 0;
	return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    for(new i; i < MAX_PLAYERS; i++)
    {
        if(vehicleid == vp_pizzaboy[i][vp_vehicle])
        {
            if(!ispassenger && vehicleid != INVALID_VEHICLE_ID)
            {
                if(PlayerInfo[playerid][Profissao] != pizzaboy)
                {
                    ClearAnimations(playerid);
                    SendClientMessage(playerid, Erro, "Veiculo exclusivo da profiss�o PizzaBoy");
                    return 1;
                }
                else
                {
                    if(strcmp(vp_pizzaboy[i][vp_owner], PlayerInfo[playerid][Nome]))
                    {
                        ClearAnimations(playerid);
                        format(String, sizeof(String), "Este ve�culo pertence � %s", vp_pizzaboy[i][vp_owner]);
                        SendClientMessage(playerid, Erro, String);
                        return 1;
                    }
                }
            }

        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_YES) && IsPlayerInRangeOfPoint(playerid, 2.0, 2122.31, -1789.06, 13.55))
	{
        if(PlayerInfo[playerid][Profissao] != pizzaboy)
            return SendClientMessage(playerid, Erro, "Voc� n�o tem permiss�o");

        if(vp_pizzaboy[playerid][vp_vehicle])
            return SendClientMessage(playerid, Erro, "Voc� j� criou um ve�culo profiss�o");

        SetPlayerSkin(playerid, 155);

        new rand = random(sizeof(vr_pizzaboy));

        format(String, sizeof(String), "{FFFFFF}PizzaBoy {0080FF}%s", PlayerInfo[playerid][Nome]);
        format(vp_pizzaboy[playerid][vp_owner], MAX_PLAYER_NAME, PlayerInfo[playerid][Nome]);
        vp_pizzaboy[playerid][vp_vehicle] = CreateVehicle(448, vr_pizzaboy[rand][vrpz_x], vr_pizzaboy[rand][vrpz_y], vr_pizzaboy[rand][vrpz_z], 268.0, -1, -1, 100);
        vp_pizzaboy[playerid][vp_label] = CreateDynamic3DTextLabel(String, 0xFFFFFFFF, vr_pizzaboy[rand][vrpz_x], vr_pizzaboy[rand][vrpz_y], vr_pizzaboy[rand][vrpz_z], 20.0, INVALID_PLAYER_ID, vp_pizzaboy[playerid][vp_vehicle]);
        SetVehicleParamsEx(vp_pizzaboy[playerid][vp_vehicle], 0, 0, 0, 0, 0, 0, 0);

        SendClientMessage(playerid, color_pizzaboy, "Foi criado um ve�culo profiss�o no estacionamento");
        return 1;
	}
	return 1;
}

/******************************************************************************/
/****************************| COMMANDS PIZZA BOY |****************************/
/******************************************************************************/

CMD:pegarpizzas(playerid)
{
    if(PlayerInfo[playerid][Profissao] != pizzaboy)
        return SendClientMessage(playerid, Erro, "Voc� n�o tem permiss�o");

    if(!IsPlayerInRangeOfPoint(playerid, 20.0, 2115.87, -1776.93, 13.39))
        return SendClientMessage(playerid, Erro, "Voc� n�o est� na localidade correta");

    if(pb_pizzas[playerid])
        return SendClientMessage(playerid, Erro, "Voc� ainda tem pizzas para entregar, termine e depois pegue mais");

    new rand = random(sizeof(pb_data));

    pb_pizzas[playerid] = 5;

    pb_info[playerid][pbif_x] = pb_data[rand][pbdt_x];
    pb_info[playerid][pbif_y] = pb_data[rand][pbdt_y];
    pb_info[playerid][pbif_z] = pb_data[rand][pbdt_z];
    pb_info[playerid][pbif_value] = pb_data[rand][pbdt_value];

    pb_pickup[playerid] = CreateDynamicPickup(1239, 1, pb_data[rand][pbdt_x], pb_data[rand][pbdt_y], pb_data[rand][pbdt_z], -1, -1, playerid, -1.0);
    pb_mapicon[playerid] = CreateDynamicMapIcon(pb_data[rand][pbdt_x], pb_data[rand][pbdt_y], pb_data[rand][pbdt_z], 0, 0xFF0000AA, -1, -1, playerid, -1.0, MAPICON_GLOBAL, -1, 0);
    pb_label[playerid] = CreateDynamic3DTextLabel("{FF0000}Digite: {FFFFFF}/EntregarPizza", 0xFFFFFFFF, pb_data[rand][pbdt_x], pb_data[rand][pbdt_y], pb_data[rand][pbdt_z], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);

    SendClientMessage(playerid, color_pizzaboy, "Voc� pegou 5 Pizzas");
    SendClientMessage(playerid, color_pizzaboy, "V� at� a marca��o vermelha em seu mini-mapa e as entregue");
    return 1;
}

CMD:entregarpizza(playerid)
{
    if(PlayerInfo[playerid][Profissao] != pizzaboy)
        return SendClientMessage(playerid, Erro, "Voc� n�o tem permiss�o");

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, pb_info[playerid][pbif_x], pb_info[playerid][pbif_y], pb_info[playerid][pbif_z]))
        return SendClientMessage(playerid, Erro, "Voc� n�o est� na localidade correta");

    if(!pb_pizzas[playerid])
        return SendClientMessage(playerid, Erro, "Voc� n�o tem pizzas, volte at� � sua HQ para pegar mais");

    pb_pizzas[playerid]--;
    PlayerInfo[playerid][Dinheiro] += pb_info[playerid][pbif_value];
    UpdatePlayerMoney(playerid);

    format(String, sizeof(String), "Voc� recebeu $%d pela entrega", pb_info[playerid][pbif_value]);
    SendClientMessage(playerid, color_pizzaboy, String);

    if(pb_pizzas[playerid])
    {
        new rand = random(sizeof(pb_data));

        pb_info[playerid][pbif_x] = pb_data[rand][pbdt_x];
        pb_info[playerid][pbif_y] = pb_data[rand][pbdt_y];
        pb_info[playerid][pbif_z] = pb_data[rand][pbdt_z];
        pb_info[playerid][pbif_value] = pb_data[rand][pbdt_value];

        GetPlayer2DZone(zone, MAX_ZONE_NAME, pb_data[rand][pbdt_x], pb_data[rand][pbdt_y]);

        format(String, sizeof(String), "Agora v� at� � pr�xima localizada em %s", zone);
        SendClientMessage(playerid, color_pizzaboy, String);

        if(pb_pickup[playerid])
            { DestroyDynamicPickup(pb_pickup[playerid]); }
        if(pb_mapicon[playerid])
            { DestroyDynamicMapIcon(pb_mapicon[playerid]); }
        if(pb_label[playerid])
            { DestroyDynamic3DTextLabel(pb_label[playerid]); }

        pb_pickup[playerid] = CreateDynamicPickup(1239, 1, pb_data[rand][pbdt_x], pb_data[rand][pbdt_y], pb_data[rand][pbdt_z], -1, -1, playerid, -1.0);
        pb_mapicon[playerid] = CreateDynamicMapIcon(pb_data[rand][pbdt_x], pb_data[rand][pbdt_y], pb_data[rand][pbdt_z], 0, 0xFF0000AA, -1, -1, playerid, -1.0, MAPICON_GLOBAL, -1, 0);
        pb_label[playerid] = CreateDynamic3DTextLabel("{FF0000}Digite: {FFFFFF}/EntregarPizza", 0xFFFFFFFF, pb_data[rand][pbdt_x], pb_data[rand][pbdt_y], pb_data[rand][pbdt_z], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);
    }
    else
    {
        if(pb_pickup[playerid])
            { DestroyDynamicPickup(pb_pickup[playerid]); }
        if(pb_mapicon[playerid])
            { DestroyDynamicMapIcon(pb_mapicon[playerid]); }
        if(pb_label[playerid])
            { DestroyDynamic3DTextLabel(pb_label[playerid]); }

        SendClientMessage(playerid, color_pizzaboy, "Acabou as suas pizzas, v� at� HQ e pegue mais");
    }
    return 1;
}