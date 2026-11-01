new PlayerText:GameplayHUD[MAX_PLAYERS];

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

public InitializeHUDPlayer(playerid)
{
	GameplayHUD[playerid] = CreatePlayerTextDraw(playerid, 18.0, 330.0, "Cargando estado...");
	PlayerTextDrawLetterSize(playerid, GameplayHUD[playerid], 0.22, 1.0);
	PlayerTextDrawColor(playerid, GameplayHUD[playerid], 0xFFFFFFFF);
	PlayerTextDrawSetShadow(playerid, GameplayHUD[playerid], 1);
	PlayerTextDrawSetOutline(playerid, GameplayHUD[playerid], 1);
	PlayerTextDrawFont(playerid, GameplayHUD[playerid], 1);
	PlayerTextDrawSetProportional(playerid, GameplayHUD[playerid], 1);
	return 1;
}

public ShowGameplayHUD(playerid)
{
	PlayerTextDrawShow(playerid, GameplayHUD[playerid]);
	return 1;
}

public CleanupHUDPlayer(playerid)
{
	PlayerTextDrawDestroy(playerid, GameplayHUD[playerid]);
	return 1;
}

public UpdateGameplayHUD()
{
	for (new playerid = 0; playerid < MAX_PLAYERS; playerid++)
	{
		if (!IsPlayerConnected(playerid) || !IsAccountLoaded(playerid)) continue;

		new jobName[24], factionName[24], text[192];
		GetJobName(PI[playerid][jJob], jobName, sizeof jobName);
		GetFactionName(PI[playerid][jFaction], factionName, sizeof factionName);
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new Float:vx, Float:vy, Float:vz, Float:speed, Float:vehicleHealth;
			GetVehicleVelocity(vehicleid, vx, vy, vz);
			GetVehicleHealth(vehicleid, vehicleHealth);
			speed = floatsqroot((vx * vx) + (vy * vy) + (vz * vz)) * 180.0;
			format(text, sizeof text,
				"Trabajo: %s %d | Faccion: %s~n~Hambre: %d%%  Sed: %d%%~n~Velocidad: %d km/h  Vehiculo: %d%%",
				jobName, PI[playerid][jJobLevel], factionName,
				PI[playerid][jHunger], PI[playerid][jThirst],
				floatround(speed, floatround_round), floatround(vehicleHealth / 10.0, floatround_round));
		}
		else
		{
			format(text, sizeof text,
				"Trabajo: %s %d | Faccion: %s~n~Hambre: %d%%  Sed: %d%%",
				jobName, PI[playerid][jJobLevel], factionName,
				PI[playerid][jHunger], PI[playerid][jThirst]);
		}
		PlayerTextDrawSetString(playerid, GameplayHUD[playerid], text);
	}
	return 1;
}

forward CleanupHUDPlayer(playerid);
forward InitializeHUDSystem();
forward UpdateGameplayHUD();
