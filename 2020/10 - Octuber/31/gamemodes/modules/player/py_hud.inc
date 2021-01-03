#include YSI\y_hooks

#include modules\database\db_hud

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case hud:
        {
            if(!response) return 0;

            switch(listitem)
            {
                case 0:
                {
                    if(statePlayer[playerid])
                        HideTDStatus(playerid);
                    else
                        ShowTDStatus(playerid);

                    return 1;
                }
                case 1:
                {
                    if(!IsPlayerInAnyVehicle(playerid))
                        return SendClientMessage(playerid, Erro, "Voc� n�o est� em um ve�culo");

                    if(stateVehicle[playerid])
                        HidePlayerVelocimetro(playerid);
                    else
                        ShowPlayerVelocimetro(playerid);

                    return 1;
                }
                case 2:
                {
                    if(stateTime[playerid])
                        HideTDTime(playerid);
                    else
                        ShowTDTime(playerid);

                    return 1;
                }
                case 3:
                    return ShowPlayerDialog(playerid, hudbackcolor, DIALOG_STYLE_INPUT, "{FF0000}Alterar cor status background", "{FFFFFF}Digite um codigo em '{FF0000}HTML{FFFFFF}' abaixo\nPesquise no Google algo como {00FF00}Cores em HTML {FFFFFF}:\n{FF0000}Exemplo {FFFFFF}00FF00 = {00FF00}Calenzo", "Alterar", "Cancelar");

                case 4:
                    return ShowPlayerDialog(playerid, hudcolor, DIALOG_STYLE_INPUT, "{FF0000}Alterar cor status", "{FFFFFF}Digite um codigo em '{FF0000}HTML{FFFFFF}' abaixo\nPesquise no Google algo como {00FF00}Cores em HTML {FFFFFF}:\n{FF0000}Exemplo {FFFFFF}00FF00 = {00FF00}Calenzo", "Alterar", "Cancelar");

                case 5:
                    return ShowPlayerDialog(playerid, hudfontcolor, DIALOG_STYLE_INPUT, "{FF0000}Alterar cor fonte", "{FFFFFF}Digite um codigo em '{FF0000}HTML{FFFFFF}' abaixo\nPesquise no Google algo como {00FF00}Cores em HTML {FFFFFF}:\n{FF0000}Exemplo {FFFFFF}{00FF00} = {00FF00}Calenzo", "Alterar", "Cancelar");
            }
            return 1;
        }
        case hudbackcolor:
        {
            if(!response)
                return 0;

            if(!strlen(inputtext))
                return ShowPlayerDialog(playerid, hudbackcolor, DIALOG_STYLE_INPUT, "{FF0000}Alterar cor status background", "{FFFFFF}Digite um codigo em '{FF0000}HTML{FFFFFF}' abaixo\nPesquise no Google algo como {00FF00}Cores em HTML {FFFFFF}:\n{FF0000}Exemplo {FFFFFF}00FF00 = {00FF00}Calenzo\n{FF4000}Voc� n�o digitou nada!", "Alterar", "Cancelar");

            if(strlen(inputtext) != 6)
                return ShowPlayerDialog(playerid, hudbackcolor, DIALOG_STYLE_INPUT, "{FF0000}Alterar cor status background", "{FFFFFF}Digite um codigo em '{FF0000}HTML{FFFFFF}' abaixo\nPesquise no Google algo como {00FF00}Cores em HTML {FFFFFF}:\n{FF0000}Exemplo {FFFFFF}00FF00 = {00FF00}Calenzo\n{FF4000}Voc� n�o digitou 6 digitos!", "Alterar", "Cancelar");

            format(PlayerInfo[playerid][hud_backcolor], 7, inputtext);
            SendClientMessage(playerid, Green, "Cor status background alterada");

            HideTDStatus(playerid);
            TDPlayerBarStatus(playerid);
            ShowTDStatus(playerid);
            return 1;
        }
        case hudcolor:
        {
            if(!response)
                return 0;

            if(!strlen(inputtext))
                return ShowPlayerDialog(playerid, hudcolor, DIALOG_STYLE_INPUT, "{FF0000}Alterar cor status background", "{FFFFFF}Digite um codigo em '{FF0000}HTML{FFFFFF}' abaixo\nPesquise no Google algo como {00FF00}Cores em HTML {FFFFFF}:\n{FF0000}Exemplo {FFFFFF}00FF00 = {00FF00}Calenzo\n{FF4000}Voc� n�o digitou nada!", "Alterar", "Cancelar");

            if(strlen(inputtext) != 6)
                return ShowPlayerDialog(playerid, hudcolor, DIALOG_STYLE_INPUT, "{FF0000}Alterar cor status background", "{FFFFFF}Digite um codigo em '{FF0000}HTML{FFFFFF}' abaixo\nPesquise no Google algo como {00FF00}Cores em HTML {FFFFFF}:\n{FF0000}Exemplo {FFFFFF}00FF00 = {00FF00}Calenzo\n{FF4000}Voc� n�o digitou 6 digitos!", "Alterar", "Cancelar");

            format(PlayerInfo[playerid][hud_color], 7, inputtext);
            SendClientMessage(playerid, Green, "Cor status alterada");

            HideTDStatus(playerid);
            TDPlayerBarStatus(playerid);
            ShowTDStatus(playerid);        //Update mais otimizado
            return 1;
        }
        case hudfontcolor:
        {
            if(!response)
                return 0;

            if(!strlen(inputtext))
                return ShowPlayerDialog(playerid, hudfontcolor, DIALOG_STYLE_INPUT, "{FF0000}Alterar cor status background", "{FFFFFF}Digite um codigo em '{FF0000}HTML{FFFFFF}' abaixo\nPesquise no Google algo como {00FF00}Cores em HTML {FFFFFF}:\n{FF0000}Exemplo {FFFFFF}00FF00 = {00FF00}Calenzo\n{FF4000}Voc� n�o digitou nada!", "Alterar", "Cancelar");

            if(strlen(inputtext) != 6)
                return ShowPlayerDialog(playerid, hudfontcolor, DIALOG_STYLE_INPUT, "{FF0000}Alterar cor status background", "{FFFFFF}Digite um codigo em '{FF0000}HTML{FFFFFF}' abaixo\nPesquise no Google algo como {00FF00}Cores em HTML {FFFFFF}:\n{FF0000}Exemplo {FFFFFF}00FF00 = {00FF00}Calenzo\n{FF4000}Voc� n�o digitou 6 digitos!", "Alterar", "Cancelar");

            format(PlayerInfo[playerid][hud_fontcolor], 7, inputtext);
            SendClientMessage(playerid, Green, "Cor da fonte alterada");

            HideTDStatus(playerid);
            TDPlayerBarStatus(playerid);
            ShowTDStatus(playerid);
            return 1;
        }
    }
	return 1;
}

CMD:hud(playerid)
{
    new txt[500];

    strcat(txt, "{FFFFFF}TextDraw\t Status\n");

    format(String, 50, "{FFFFFF}Status Jogador\t %s\n", (statePlayer[playerid] ? ("{FF4000}Ocultar") : ("{1B6302}Mostrar")));
    strcat(txt, String);
    format(String, 50, "{FFFFFF}Status Ve�culo\t %s\n", (stateVehicle[playerid] ? ("{FF4000}Ocultar") : ("{1B6302}Mostrar")));
    strcat(txt, String);
    format(String, 50, "{FFFFFF}Hora e Data\t %s\n", (stateTime[playerid] ? ("{FF4000}Ocultar") : ("{1B6302}Mostrar")));
    strcat(txt, String);

    strcat(txt, "{FFFFFF}Alterar cor status background\n");
    strcat(txt, "{FFFFFF}Alterar cor status\n");
    strcat(txt, "{FFFFFF}Alterar cor fonte\n");

    ShowPlayerDialog(playerid, hud, DIALOG_STYLE_TABLIST_HEADERS, "{FF0000}HUD", txt, "Continuar", "Cancelar");
    return 1;
}