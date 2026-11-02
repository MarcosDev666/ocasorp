#define HUD_DRAW_COUNT 12

enum
{
    HUD_PANEL,
    HUD_TITLE,
    HUD_PLAYER,
    HUD_CASH,
    HUD_BANK,
    HUD_JOB,
    HUD_FACTION,
    HUD_NEEDS,
    HUD_HEALTH,
    HUD_PHONE,
    HUD_CALL,
    HUD_SPEED
}

new PlayerText:GameplayHUD[MAX_PLAYERS][HUD_DRAW_COUNT];
new bool:gameplayHUDVisible[MAX_PLAYERS];

public InitializeHUDSystem()
{
    new timerName[19] = "UpdateGameplayHUD";
    new timerid = SetTimer(timerName, 1000, true);
    if (!timerid)
    {
        printf("[HUD] Error: no se pudo iniciar el temporizador del HUD.");
        return 0;
    }
    return 1;
}

stock SetupHUDLabel(playerid, draw, Float:x, Float:y, const text[])
{
    GameplayHUD[playerid][draw] = CreatePlayerTextDraw(playerid, x, y, text);
    PlayerTextDrawLetterSize(playerid, GameplayHUD[playerid][draw], 0.18, 0.78);
    PlayerTextDrawColor(playerid, GameplayHUD[playerid][draw], 0xF4F6F8FF);
    PlayerTextDrawSetShadow(playerid, GameplayHUD[playerid][draw], 1);
    PlayerTextDrawSetOutline(playerid, GameplayHUD[playerid][draw], 0);
    PlayerTextDrawFont(playerid, GameplayHUD[playerid][draw], 1);
    PlayerTextDrawSetProportional(playerid, GameplayHUD[playerid][draw], 1);
    return 1;
}

public InitializeHUDPlayer(playerid)
{
    gameplayHUDVisible[playerid] = false;
    GameplayHUD[playerid][HUD_PANEL] = CreatePlayerTextDraw(playerid, 14.0, 297.0, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, GameplayHUD[playerid][HUD_PANEL], 224.0, 147.0);
    PlayerTextDrawColor(playerid, GameplayHUD[playerid][HUD_PANEL], 0x101720AA);
    PlayerTextDrawSetShadow(playerid, GameplayHUD[playerid][HUD_PANEL], 0);
    PlayerTextDrawSetOutline(playerid, GameplayHUD[playerid][HUD_PANEL], 0);
    PlayerTextDrawFont(playerid, GameplayHUD[playerid][HUD_PANEL], 4);

    SetupHUDLabel(playerid, HUD_TITLE, 23.0, 302.0, "OCASO ROLEPLAY");
    PlayerTextDrawColor(playerid, GameplayHUD[playerid][HUD_TITLE], 0xF2FF00FF);
    SetupHUDLabel(playerid, HUD_PLAYER, 23.0, 316.0, "Ciudadano");
    SetupHUDLabel(playerid, HUD_CASH, 23.0, 329.0, "Efectivo: $0");
    SetupHUDLabel(playerid, HUD_BANK, 23.0, 342.0, "Banco: $0");
    SetupHUDLabel(playerid, HUD_JOB, 23.0, 355.0, "Empleo: Desempleado");
    SetupHUDLabel(playerid, HUD_FACTION, 23.0, 368.0, "Faccion: Civil");
    SetupHUDLabel(playerid, HUD_NEEDS, 23.0, 381.0, "Hambre: 100% | Sed: 100%");
    SetupHUDLabel(playerid, HUD_HEALTH, 23.0, 394.0, "Salud: 100% | Armadura: 0%");
    SetupHUDLabel(playerid, HUD_PHONE, 23.0, 407.0, "Telefono: sin asignar");
    SetupHUDLabel(playerid, HUD_CALL, 23.0, 420.0, "Estado: disponible");
    SetupHUDLabel(playerid, HUD_SPEED, 23.0, 433.0, "Velocidad: a pie");
    return 1;
}

public ShowGameplayHUD(playerid)
{
    if (gameplayHUDVisible[playerid]) return 1;
    for (new draw = 0; draw < HUD_DRAW_COUNT; draw++)
    {
        PlayerTextDrawShow(playerid, GameplayHUD[playerid][draw]);
    }
    gameplayHUDVisible[playerid] = true;
    return 1;
}

stock HideGameplayHUD(playerid)
{
    if (!gameplayHUDVisible[playerid]) return 1;
    for (new draw = 0; draw < HUD_DRAW_COUNT; draw++)
    {
        PlayerTextDrawHide(playerid, GameplayHUD[playerid][draw]);
    }
    gameplayHUDVisible[playerid] = false;
    return 1;
}

public CleanupHUDPlayer(playerid)
{
    for (new draw = 0; draw < HUD_DRAW_COUNT; draw++)
    {
        PlayerTextDrawDestroy(playerid, GameplayHUD[playerid][draw]);
    }
    gameplayHUDVisible[playerid] = false;
    return 1;
}

public UpdateGameplayHUD()
{
    for (new playerid = 0; playerid < MAX_PLAYERS; playerid++)
    {
        if (!IsPlayerConnected(playerid) || !IsAccountLoaded(playerid)
            || !gameplayHUDVisible[playerid]) continue;

        new jobName[32], factionName[32], name[MAX_PLAYER_NAME], text[128];
        GetJobName(PI[playerid][jJob], jobName, sizeof jobName);
        GetFactionName(PI[playerid][jFaction], factionName, sizeof factionName);
        GetPlayerName(playerid, name, sizeof name);

        format(text, sizeof text, "%s (ID %d)", name, playerid);
        PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_PLAYER], text);
        format(text, sizeof text, "Efectivo: $%d", GetPlayerMoney(playerid));
        PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_CASH], text);
        format(text, sizeof text, "Banco: $%d", PI[playerid][jBankMoney]);
        PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_BANK], text);
        format(text, sizeof text, "Empleo: %s (nivel %d)", jobName, PI[playerid][jJobLevel]);
        PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_JOB], text);
        format(text, sizeof text, "Faccion: %s", factionName);
        PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_FACTION], text);
        format(text, sizeof text, "Hambre: %d%% | Sed: %d%%", PI[playerid][jHunger], PI[playerid][jThirst]);
        PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_NEEDS], text);

        new Float:health, Float:armour;
        GetPlayerHealth(playerid, health);
        GetPlayerArmour(playerid, armour);
        format(text, sizeof text, "Salud: %d%% | Armadura: %d%%",
            floatround(health, floatround_round), floatround(armour, floatround_round));
        PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_HEALTH], text);
        format(text, sizeof text, "Telefono: %d", PI[playerid][jPhone]);
        PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_PHONE], text);

        if (phoneCallState[playerid] == PHONE_CALL_ACTIVE)
        {
            PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_CALL], "Estado: llamada activa");
        }
        else if (phoneCallState[playerid] == PHONE_CALL_RINGING)
        {
            PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_CALL], "Estado: llamada entrante/saliente");
        }
        else
        {
            PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_CALL], "Estado: disponible");
        }

        if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            new vehicleid = GetPlayerVehicleID(playerid);
            new Float:vx, Float:vy, Float:vz;
            GetVehicleVelocity(vehicleid, vx, vy, vz);
            new speed = floatround(floatsqroot((vx * vx) + (vy * vy) + (vz * vz)) * 180.0, floatround_round);
            format(text, sizeof text, "Velocidad: %d km/h", speed);
        }
        else
        {
            format(text, sizeof text, "Velocidad: a pie");
        }
        PlayerTextDrawSetString(playerid, GameplayHUD[playerid][HUD_SPEED], text);
    }
    return 1;
}

CMD:hud(playerid, params[])
{
    #pragma unused params
    if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
    if (gameplayHUDVisible[playerid])
    {
        HideGameplayHUD(playerid);
        SendClientMessage(playerid, COLOR_GLOBAL, "HUD oculto. Usa /hud para volver a mostrarlo.");
    }
    else
    {
        ShowGameplayHUD(playerid);
        SendClientMessage(playerid, COLOR_GLOBAL, "HUD visible.");
    }
    return 1;
}

forward InitializeHUDSystem();
forward UpdateGameplayHUD();
