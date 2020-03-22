#include YSI\y_hooks

new AgenciaMapIcon[MAX_PLAYERS] = 0,
    AgenciaPickup[MAX_PLAYERS] = 0,
    bool:AgenciaEncaminhado[MAX_PLAYERS] = false;

hook OnGameModeInit(playerid)
{
    CreateDynamicMapIcon(1154.0808, -1771.9812, 16.5992, 23, -1, -1, -1, -1, 100.0);     //Agencia LS
    CreateDynamicMapIcon(937.8450, 1733.1957, 8.8516, 23, -1, -1, -1, -1, 100.0);        //Agencia LV
    CreateDynamicMapIcon(-2171.8110, 252.0813, 35.3378, 23, -1, -1, -1, -1, 100.0);      //Agencia SF
    CreateDynamicMapIcon(1481.0637, -1770.9515, 18.7958, 42, -1, -1, -1, -1, 100.0);     //Prefeitura LS
    CreateDynamicMapIcon(2447.0620, 2376.2354, 12.1635, 42, -1, -1, -1, -1, 100.0);      //Prefeitura LV
    CreateDynamicMapIcon(-2765.8796, 375.5812, 6.3347, 42, -1, -1, -1, -1, 100.0);       //Prefeitura SF
    CreateDynamicMapIcon(1554.8657, -1675.6693, 16.1953, 30, -1, -1, -1, -1, 100.0);     // Departamento LS
    CreateDynamicMapIcon(2290.1218, 2430.9775, 10.8203, 30, -1, -1, -1, -1, 100.0);      // Departamento LV
    CreateDynamicMapIcon(-1605.5848, 710.8436, 13.8672, 30, -1, -1, -1, -1, 100.0);      // Departamento SF
    CreateDynamicMapIcon(627.7621, -571.7207, 17.5526, 30, -1, -1, -1, -1, 100.0);       // Departamento DM
    CreateDynamicMapIcon(1172.6787, -1323.3129, 15.4022, 22, -1, -1, -1, -1, 100.0);     // Hospital LS
    CreateDynamicMapIcon(1607.3579, 1815.6309, 10.8203, 22, -1, -1, -1, -1, 100.0);      // Hospital LV
    CreateDynamicMapIcon(-2655.0662, 639.1497, 14.4531, 22, -1, -1, -1, -1, 100.0);      // Hospital SF
    CreateDynamicMapIcon(-1514.8217, 2520.3232, 55.9185, 22, -1, -1, -1, -1, 100.0);     // Hospital EL
    CreateDynamicMapIcon(1241.8073, 327.1022, 19.7555, 22, -1, -1, -1, -1, 100.0);       // Hospital MG
    CreateDynamicMapIcon(-320.0716, 1049.2637, 20.3403, 22, -1, -1, -1, -1, 100.0);      // Hospital FC
    CreateDynamicMapIcon(-2223.1670, -2293.6865, 31.6719, 22, -1, -1, -1, -1, 100.0);    // Hospital AP
    CreateDynamicMapIcon(1778.3052, -1663.5337, 14.4362, 52, -1, -1, -1, -1, 100.0);     // Banco LS
    CreateDynamicMapIcon(2388.6733, 2466.0430, 10.8203, 52, -1, -1, -1, -1, 100.0);      // Banco LV
    CreateDynamicMapIcon(-2649.8374, 376.0090, 6.1563, 52, -1, -1, -1, -1, 100.0);       // Banco SF
    CreateDynamicMapIcon(-180.3883, 1133.1510, 19.7422, 52, -1, -1, -1, -1, 100.0);      // Banco FC
    CreateDynamicMapIcon(1372.9271, 405.2487, 19.9555, 52, -1, -1, -1, -1, 100.0);       // Banco MG
    CreateDynamicMapIcon(2302.9521, -16.2789, 26.4844, 52, -1, -1, -1, -1, 100.0);       // Banco PC
    CreateDynamicMapIcon(-828.0650, 1503.6166, 19.7585, 52, -1, -1, -1, -1, 100.0);      // Banco LB
    CreateDynamicMapIcon(-1480.8273, 2592.3015, 55.8359, 52, -1, -1, -1, -1, 100.0);     // Banco EQ
    CreateDynamicMapIcon(207.7767, -62.5814, 1.6498, 52, -1, -1, -1, -1, 100.0);         // Banco BB
    CreateDynamicMapIcon(1798.4763, -1578.3191, 14.0849, 58, -1, -1, -1, -1, 100.0);     // Imobiliaria LS
    CreateDynamicMapIcon(2413.2390, 1123.8374, 10.8203, 58, -1, -1, -1, -1, 100.0);      // Imobiliaria LV
    CreateDynamicMapIcon(-1881.1293, 822.7573, 35.1773, 58, -1, -1, -1, -1, 100.0);      // Imobiliaria SF
    CreateDynamicMapIcon(1519.0413, -1453.5895, 14.2073, 36, -1, -1, -1, -1, 100.0);     // Auto Escola LS
    CreateDynamicMapIcon(2183.2483, 2295.2205, 10.8203, 36, -1, -1, -1, -1, 100.0);      // Auto Escola LV
    CreateDynamicMapIcon(-2026.5950, -101.3410, 35.1641, 36, -1, -1, -1, -1, 100.0);     // Auto Escola SF
    CreateDynamicMapIcon(1310.1411, -1367.8086, 13.5408, 19, -1, -1, -1, -1, 100.0);     // Detran LS
    CreateDynamicMapIcon(1173.1600, 1349.0011, 10.9219, 19, -1, -1, -1, -1, 100.0);      // Detran LV
    CreateDynamicMapIcon(-2720.6375, 127.7373, 7.0391, 19, -1, -1, -1, -1, 100.0);       // Detran SF
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    AgenciaMapIcon[playerid] = 0;
    AgenciaPickup[playerid] = 0;
    AgenciaEncaminhado[playerid] = false;
	return 1;
}

hook OnPlayerEnterCheckpoint(playerid)
{
    if(CPS_GetPlayerCheckpoint(playerid) == cps_mafia)
    {
        ShowPlayerDialog(playerid, mob, DIALOG_STYLE_LIST, "{FF0000}Cargos", "{FFFFFF}Ladr�o de g�s ", "Selecionar", "Fechar");
    }
    if(CPS_GetPlayerCheckpoint(playerid) == cps_agencia)
    {
        ShowPlayerDialog(playerid, agency, DIALOG_STYLE_LIST, "{FF0000}Menu Empregos", "{FFFFFF}Classe � {80FF80}Honesta \n{FFFFFF}Classe � {80FFFF}Transporte \n{FFFFFF}Classe � {51A8FF}Policia \n{FFFFFF}Classe � {626262}Governo ", "Selecionar", "Fechar");
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == agency)
    {
        if(response)
        {
            switch(listitem)
            {
                case 0:
                {
                    new string[500];
                    strcat(string,"{FFFFFF}Profiss�o\t {FF0000}Level\t {1CEB00}Salario\n");
                    strcat(string,"{FFFFFF}Entregador de Jornais\t {F71616}0\t {1CEB00}$250\n");
                    strcat(string,"{FFFFFF}Entregador de Pizzas\t {F71616}10\t {1CEB00}$500\n");
                    strcat(string,"{FFFFFF}Vendedor de Skins\t {F71616}55\t {1CEB00}$980\n");
                    strcat(string,"{FFFFFF}Advogado\t {F71616}100\t {1CEB00}$1000\n");
                    ShowPlayerDialog(playerid, honest, DIALOG_STYLE_TABLIST_HEADERS, "{80FF80}Honesta", string, "Selecionar", "Voltar");
                }
                case 1:
                {
                    new string[200];
                    strcat(string,"{FFFFFF}Profiss�o\t {FF0000}Level\t {1CEB00}Salario\n");
                    strcat(string,"{FFFFFF}Taxi\t{F71616}5\t {1CEB00}$350");
                    ShowPlayerDialog(playerid, transport, DIALOG_STYLE_TABLIST_HEADERS, "{80FFFF}Transporte", string, "Selecionar", "Voltar");
                }
                case 2:
                {
                    new string[200];
                    strcat(string,"{FFFFFF}Profiss�o\t {FF0000}Level\t {1CEB00}Salario\n");
                    strcat(string,"{FFFFFF}Policia Municipal\t {F71616}100\t {1CEB00}$1000");
                    ShowPlayerDialog(playerid, police, DIALOG_STYLE_TABLIST_HEADERS, "{51A8FF}Policia", string, "Selecionar", "Voltar");
                }
                case 3:
                {
                    new string[200];
                    strcat(string,"{FFFFFF}Profiss�o\t {FF0000}Level\t {1CEB00}Salario\n");
                    strcat(string,"{FFFFFF}Corregedoria\t {F71616}1000\t {1CEB00}$5000\n");
                    ShowPlayerDialog(playerid, government, DIALOG_STYLE_TABLIST_HEADERS, "{626262}Governo", string, "Selecionar", "Voltar");
                }
            }
        }
        return 1;
    }
    if(dialogid == mob)
    {
        if(response)
        {
            switch(listitem)
            {
                case 0:
                {
                    if(PlayerInfo[playerid][Level] < 0)
                        return 0;

                    if(IsPlayerUniformePM(playerid))
                        { SetPlayerSkin(playerid, PlayerInfo[playerid][Skin]); }

                    if(AgenciaPickup[playerid] != 0)
                        { DestroyPickup(AgenciaPickup[playerid]); }
                    if(AgenciaMapIcon[playerid] != 0)
                        { DestroyDynamicMapIcon(AgenciaMapIcon[playerid]); }

                    AgenciaEncaminhado[playerid] = true;
                    PlayerInfo[playerid][Profissao] = Desempregado;
                    PlayerInfo[playerid][Semprofissao] = LadraoGas;
                    AgenciaPickup[playerid] = CreatePickup(1210, 1, -453.7872, 2230.1296, 42.4993);
                    AgenciaMapIcon[playerid] = CreateDynamicMapIcon(-453.7872, 2230.1296, 42.4993, 53, -1, -1, 0, -1, 100000.0, MAPICON_GLOBAL);
                    SetColorProfession(playerid);
                    PlayerPlaySound(playerid, 1057, 0, 0, 0);
                    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{FF0000}Encaminhamento - {FFFFFF}Agencia de Empregos", "{FFFFFF}Voc� foi aceito no cargo {00FF00}Ladr�o de G�s \n\n{FFFFFF}Para iniciar os servi�os siga a bandeira {FF0000}Preta e Branca {FFFFFF}em seu radar", "Fechar", "");
                }
            }
        }
        return 1;
    }
    if(dialogid == honest)
    {
        if(!response)
            return ShowPlayerDialog(playerid, agency, DIALOG_STYLE_LIST, "{FF0000}Menu Empregos", "{FFFFFF}Classe � {80FF80}Honesta \n{FFFFFF}Classe � {80FFFF}Transporte \n{FFFFFF}Classe � {51A8FF}Policia \n{FFFFFF}Classe � {626262}Governo ", "Selecionar", "Fechar");

        if(response)
        {
            switch(listitem)
            {
                case 0:
                {
                    if(IsPlayerUniformePM(playerid))
                        { SetPlayerSkin(playerid, PlayerInfo[playerid][Skin]); }

                    if(AgenciaPickup[playerid] != 0)
                        { DestroyPickup(AgenciaPickup[playerid]); }
                    if(AgenciaMapIcon[playerid] != 0)
                        { DestroyDynamicMapIcon(AgenciaMapIcon[playerid]); }

                    AgenciaEncaminhado[playerid] = true;
                    PlayerInfo[playerid][Profissao] = Desempregado;
                    PlayerInfo[playerid][Semprofissao] = EntregadorJornais;
                    AgenciaPickup[playerid] = CreatePickup(1210, 1, 785.2020, -1327.7697, 13.5469);
                    AgenciaMapIcon[playerid] = CreateDynamicMapIcon(785.2020, -1327.7697, 13.5469, 53, -1, -1, 0, playerid, -1.0, MAPICON_GLOBAL);
                    SetColorProfession(playerid);
                    PlayerPlaySound(playerid, 1057, 0, 0, 0);
                    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{FF0000}Encaminhamento - {FFFFFF}Agencia de Empregos", "{FFFFFF}Voc� foi aceito no emprego {00FF00}Entregador de Jornais \n\n{FFFFFF}Para iniciar os servi�os siga a bandeira {FF0000}Preta e Branca {FFFFFF}em seu radar", "Fechar", "");
                }
                case 1:
                {
                    if(PlayerInfo[playerid][Level] < 10)
                        return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem level suficiente para pegar essa profiss�o!");

                    if(IsPlayerUniformePM(playerid))
                        { SetPlayerSkin(playerid, PlayerInfo[playerid][Skin]); }

                    if(AgenciaPickup[playerid] != 0)
                        { DestroyPickup(AgenciaPickup[playerid]); }

                    if(AgenciaMapIcon[playerid] != 0)
                        { DestroyDynamicMapIcon(AgenciaMapIcon[playerid]); }

                    AgenciaEncaminhado[playerid] = true;
                    PlayerInfo[playerid][Profissao] = Desempregado;
                    PlayerInfo[playerid][Semprofissao] = EntregadorPizzas;
                    AgenciaPickup[playerid] = CreatePickup(1210, 1, 2107.9692, -1788.2231, 13.5608);
                    AgenciaMapIcon[playerid] = CreateDynamicMapIcon(2107.9692, -1788.2231, 13.5608, 53, -1, -1, 0, playerid, -1.0, MAPICON_GLOBAL);
                    SetColorProfession(playerid);
                    PlayerPlaySound(playerid, 1057, 0, 0, 0);
                    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{FF0000}Encaminhamento - {FFFFFF}Agencia de Empregos", "{FFFFFF}Voc� foi aceito no emprego {00FF00}Entregador de Pizzas \n\n{FFFFFF}Para iniciar os servi�os siga a bandeira {FF0000}Preta e Branca {FFFFFF}em seu radar", "Fechar", "");
                }
                case 2:
                {
                    if(PlayerInfo[playerid][Level] < 55)
                        return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem level suficiente para pegar essa profiss�o!");

                    if(IsPlayerUniformePM(playerid))
                        { SetPlayerSkin(playerid, PlayerInfo[playerid][Skin]); }

                    if(AgenciaPickup[playerid] != 0)
                        { DestroyPickup(AgenciaPickup[playerid]); }

                    if(AgenciaMapIcon[playerid] != 0)
                        { DestroyDynamicMapIcon(AgenciaMapIcon[playerid]); }

                    AgenciaEncaminhado[playerid] = true;
                    PlayerInfo[playerid][Profissao] = Desempregado;
                    PlayerInfo[playerid][Semprofissao] = VendedorSkins;
                    AgenciaPickup[playerid] = CreatePickup(1210, 1, 2251.76929, -1665.62854, 15.58825);
                    AgenciaMapIcon[playerid] = CreateDynamicMapIcon(2251.76929, -1665.62854, 15.58825, 53, -1, -1, 0, playerid, -1.0, MAPICON_GLOBAL);
                    SetColorProfession(playerid);
                    PlayerPlaySound(playerid, 1057, 0, 0, 0);
                    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{FF0000}Encaminhamento - {FFFFFF}Agencia de Empregos", "{FFFFFF}Voc� foi aceito no emprego {00FF00}Vendedor de Skins \n\n{FFFFFF}Para iniciar os servi�os siga a bandeira {FF0000}Preta e Branca {FFFFFF}em seu radar", "Fechar", "");
                }
                case 3:
                {
                    if(PlayerInfo[playerid][Level] < 100)
                        return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem level suficiente para pegar essa profiss�o!");

                    if(IsPlayerUniformePM(playerid))
                        { SetPlayerSkin(playerid, PlayerInfo[playerid][Skin]); }

                    if(AgenciaPickup[playerid] != 0)
                        { DestroyPickup(AgenciaPickup[playerid]); }

                    if(AgenciaMapIcon[playerid] != 0)
                        { DestroyDynamicMapIcon(AgenciaMapIcon[playerid]); }

                    AgenciaEncaminhado[playerid] = true;
                    PlayerInfo[playerid][Profissao] = Desempregado;
                    PlayerInfo[playerid][Semprofissao] = Advogado;
                    AgenciaPickup[playerid] = CreatePickup(1210, 1, -2051.2988, 459.8927, 35.1719);
                    AgenciaMapIcon[playerid] = CreateDynamicMapIcon(-2051.2988, 459.8927, 35.1719, 53, -1, -1, 0, playerid, -1.0, MAPICON_GLOBAL);
                    SetColorProfession(playerid);
                    PlayerPlaySound(playerid, 1057, 0, 0, 0);
                    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{FF0000}Encaminhamento - {FFFFFF}Agencia de Empregos", "{FFFFFF}Voc� foi aceito no emprego {00FF00}Advogado \n\n{FFFFFF}Para iniciar os servi�os siga a bandeira {FF0000}Preta e Branca {FFFFFF}em seu radar", "Fechar", "");
                }
            }
        }
        return 1;
    }
    if(dialogid == transport)
    {
        if(!response)
            return ShowPlayerDialog(playerid, agency, DIALOG_STYLE_LIST, "{FF0000}Menu Empregos", "{FFFFFF}Classe � {80FF80}Honesta \n{FFFFFF}Classe � {80FFFF}Transporte \n{FFFFFF}Classe � {51A8FF}Policia \n{FFFFFF}Classe � {626262}Governo ", "Selecionar", "Fechar");

        if(response)
        {
            switch(listitem)
            {
                case 0:
                {
                    if(PlayerInfo[playerid][Level] < 5)
                        return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem level suficiente para pegar essa profiss�o!");

                    if(IsPlayerUniformePM(playerid))
                        { SetPlayerSkin(playerid, PlayerInfo[playerid][Skin]); }

                    if(AgenciaPickup[playerid] != 0)
                        { DestroyPickup(AgenciaPickup[playerid]); }

                    if(AgenciaMapIcon[playerid] != 0)
                        { DestroyDynamicMapIcon(AgenciaMapIcon[playerid]); }

                    AgenciaEncaminhado[playerid] = true;
                    PlayerInfo[playerid][Profissao] = Desempregado;
                    PlayerInfo[playerid][Semprofissao] = Taxi;
                    AgenciaPickup[playerid] = CreatePickup(1210, 1, 2229.5803, -1368.1969, 23.99221);
                    AgenciaMapIcon[playerid] = CreateDynamicMapIcon(2229.5803, -1368.1969, 23.99221, 53, -1, -1, 0, playerid, -1.0, MAPICON_GLOBAL);
                    SetColorProfession(playerid);
                    PlayerPlaySound(playerid, 1057, 0, 0, 0);
                    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{FF0000}Encaminhamento - {FFFFFF}Agencia de Empregos", "{FFFFFF}Voc� foi aceito no emprego {00FF00}Taxi \n\n{FFFFFF}Para iniciar os servi�os siga a bandeira {FF0000}Preta e Branca {FFFFFF}em seu radar", "Fechar", "");
                }
            }
        }
        return 1;
    }
    if(dialogid == police)
    {
        if(!response)
            return ShowPlayerDialog(playerid, agency, DIALOG_STYLE_LIST, "{FF0000}Menu Empregos", "{FFFFFF}Classe � {80FF80}Honesta \n{FFFFFF}Classe � {80FFFF}Transporte \n{FFFFFF}Classe � {51A8FF}Policia \n{FFFFFF}Classe � {626262}Governo ", "Selecionar", "Fechar");

        if(response)
        {
            switch(listitem)
            {
                case 0:
                {
                    if(PlayerInfo[playerid][Level] < 100)
                        return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem level suficiente para pegar essa profiss�o!");

                    if(IsPlayerUniformePM(playerid))
                        { SetPlayerSkin(playerid, PlayerInfo[playerid][Skin]); }

                    if(IsPlayerUniformePM(playerid))
                        { SetPlayerSkin(playerid, PlayerInfo[playerid][Skin]); }

                    if(AgenciaPickup[playerid] != 0)
                        { DestroyPickup(AgenciaPickup[playerid]); }

                    if(AgenciaMapIcon[playerid] != 0)
                        { DestroyDynamicMapIcon(AgenciaMapIcon[playerid]); }

                    AgenciaEncaminhado[playerid] = true;
                    PlayerInfo[playerid][Profissao] = Desempregado;
                    PlayerInfo[playerid][Semprofissao] = PoliciaMunicipal;
                    AgenciaPickup[playerid] = CreatePickup(1210, 1, 1579.5728, -1635.3932, 13.5611);
                    AgenciaMapIcon[playerid] = CreateDynamicMapIcon(1579.5728, -1635.3932, 13.5611, 53, -1, -1, 0, playerid, -1.0, MAPICON_GLOBAL);
                    SetColorProfession(playerid);
                    PlayerPlaySound(playerid, 1057, 0, 0, 0);
                    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{FF0000}Encaminhamento - {FFFFFF}Agencia de Empregos", "{FFFFFF}Voc� foi aceito no emprego {00FF00}Policia Municipal \n\n{FFFFFF}Para iniciar os servi�os siga a bandeira {FF0000}Preta e Branca {FFFFFF}em seu radar", "Fechar", "");
                }
            }
        }
        return 1;
    }
    if(dialogid == government)
    {
        if(!response)
            return ShowPlayerDialog(playerid, agency, DIALOG_STYLE_LIST, "{FF0000}Menu Empregos", "{FFFFFF}Classe � {80FF80}Honesta \n{FFFFFF}Classe � {80FFFF}Transporte \n{FFFFFF}Classe � {51A8FF}Policia \n{FFFFFF}Classe � {626262}Governo ", "Selecionar", "Fechar");

        if(response)
        {
            switch(listitem)
            {
                case 0:
                {
                    if(PlayerInfo[playerid][Level] < 1000)
                        return SendClientMessage(playerid, Erro, "| ERRO | Voc� n�o tem level suficiente para pegar essa profiss�o!");

                    if(IsPlayerUniformePM(playerid))
                        { SetPlayerSkin(playerid, PlayerInfo[playerid][Skin]); }

                    if(IsPlayerUniformePM(playerid))
                        { SetPlayerSkin(playerid, PlayerInfo[playerid][Skin]); }

                    if(AgenciaPickup[playerid] != 0)
                        { DestroyPickup(AgenciaPickup[playerid]); }

                    if(AgenciaMapIcon[playerid] != 0)
                        { DestroyDynamicMapIcon(AgenciaMapIcon[playerid]); }

                    AgenciaEncaminhado[playerid] = true;
                    PlayerInfo[playerid][Profissao] = Desempregado;
                    PlayerInfo[playerid][Semprofissao] = Corregedoria;
                    AgenciaPickup[playerid] = CreatePickup(1210, 1, 2339.9778, 2457.2256, 14.9688);
                    AgenciaMapIcon[playerid] = CreateDynamicMapIcon(2339.9778, 2457.2256, 14.9688, 53, -1, -1, 0, -1, 100000.0, MAPICON_GLOBAL);
                    SetColorProfession(playerid);
                    PlayerPlaySound(playerid, 1057, 0, 0, 0);
                    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{FF0000}Encaminhamento - {FFFFFF}Agencia de Empregos", "{FFFFFF}Voc� foi aceito no emprego {00FF00}Corregedoria \n\n{FFFFFF}Para iniciar os servi�os siga a bandeira {FF0000}Preta e Branca {FFFFFF}em seu radar", "Fechar", "");
                }
            }
        }
        return 1;
    }
    return 1;
}