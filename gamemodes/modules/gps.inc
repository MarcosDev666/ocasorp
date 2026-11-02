#define GPS_MAP_ICON_ID 50
#define GPS_FIXED_DESTINATIONS 6

new bool:gpsRouteActive[MAX_PLAYERS];
new Float:gpsRouteX[MAX_PLAYERS];
new Float:gpsRouteY[MAX_PLAYERS];
new Float:gpsRouteZ[MAX_PLAYERS];
new gpsRouteName[MAX_PLAYERS][48];

public InitializeGPSPlayer(playerid)
{
	gpsRouteActive[playerid] = false;
	gpsRouteX[playerid] = 0.0;
	gpsRouteY[playerid] = 0.0;
	gpsRouteZ[playerid] = 0.0;
	gpsRouteName[playerid][0] = '\0';
	RemovePlayerMapIcon(playerid, GPS_MAP_ICON_ID);
	return 1;
}

public CleanupGPSPlayer(playerid)
{
	InitializeGPSPlayer(playerid);
	DisablePlayerCheckpoint(playerid);
	return 1;
}

stock UpdatePlayerRouteCheckpoint(playerid)
{
	if (gpsRouteActive[playerid])
	{
		SetPlayerCheckpoint(playerid, gpsRouteX[playerid], gpsRouteY[playerid], gpsRouteZ[playerid], 5.0);
		return 1;
	}

	if (jobOnShift[playerid]
		&& PI[playerid][jJob] >= JOB_TAXI
		&& PI[playerid][jJob] <= JOB_COUNT
		&& jobRoute[playerid] >= 0
		&& jobRoute[playerid] < JOB_ROUTE_POINTS)
	{
		new routeIndex = PI[playerid][jJob] - 1;
		SetPlayerCheckpoint(playerid,
			JobRouteX[routeIndex][jobRoute[playerid]],
			JobRouteY[routeIndex][jobRoute[playerid]],
			JobRouteZ[routeIndex][jobRoute[playerid]], 4.0);
		return 1;
	}

	SetPlayerCheckpoint(playerid, RENTAL_X, RENTAL_Y, RENTAL_Z, 3.0);
	return 1;
}

stock SetGPSRoute(playerid, const name[], Float:x, Float:y, Float:z)
{
	gpsRouteActive[playerid] = true;
	gpsRouteX[playerid] = x;
	gpsRouteY[playerid] = y;
	gpsRouteZ[playerid] = z;
	format(gpsRouteName[playerid], sizeof gpsRouteName[], "%s", name);
	SetPlayerMapIcon(playerid, GPS_MAP_ICON_ID, x, y, z, 0, 0xFF3333FF, MAPICON_GLOBAL);
	UpdatePlayerRouteCheckpoint(playerid);

	new message[96];
	format(message, sizeof message, "GPS configurado: %s. Sigue el checkpoint y el marcador del mapa.", name);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	return 1;
}

stock CancelGPSRoute(playerid, bool:notify)
{
	if (!gpsRouteActive[playerid])
	{
		if (notify) SendClientMessage(playerid, COLOR_ERROR, "No tienes una ruta GPS activa.");
		return 0;
	}

	gpsRouteActive[playerid] = false;
	gpsRouteName[playerid][0] = '\0';
	RemovePlayerMapIcon(playerid, GPS_MAP_ICON_ID);
	UpdatePlayerRouteCheckpoint(playerid);
	if (notify) SendClientMessage(playerid, COLOR_GLOBAL, "Ruta GPS cancelada.");
	return 1;
}

stock ShowGPSMenu(playerid)
{
	new text[768];
	text[0] = '\0';
	strcat(text,
		"Punto de inicio\nAgencia de empleo\nRenta de vehiculos\nConcesionario\nBanco\nGarage",
		sizeof text);
	for (new store = 0; store < STORE_COUNT; store++)
	{
		strcat(text, "\n", sizeof text);
		strcat(text, StoreName[store], sizeof text);
	}
	for (new house = 0; house < HOUSE_COUNT; house++)
	{
		strcat(text, "\n", sizeof text);
		strcat(text, HouseName[house], sizeof text);
	}
	return Dialog_Show(playerid, "OnDialogGPS", DIALOG_STYLE_LIST,
		"GPS - Selecciona un destino", text, "Marcar", "Cerrar");
}

CMD:gps(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	return ShowGPSMenu(playerid);
}

CMD:quitarGPS(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	CancelGPSRoute(playerid, true);
	return 1;
}

CMD:borrarblip(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	CancelGPSRoute(playerid, true);
	return 1;
}

Dialog:OnDialogGPS(playerid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if (!response || !IsAccountLoaded(playerid)) return 1;

	switch (listitem)
	{
		case 0: SetGPSRoute(playerid, "Punto de inicio", 1715.1680, -1878.6772, 13.5665);
		case 1: SetGPSRoute(playerid, "Agencia de empleo", JOB_CENTER_X, JOB_CENTER_Y, JOB_CENTER_Z);
		case 2: SetGPSRoute(playerid, "Renta de vehiculos", RENTAL_X, RENTAL_Y, RENTAL_Z);
		case 3: SetGPSRoute(playerid, "Concesionario", DEALERSHIP_X, DEALERSHIP_Y, DEALERSHIP_Z);
		case 4: SetGPSRoute(playerid, "Banco", ECONOMY_BANK_X, ECONOMY_BANK_Y, ECONOMY_BANK_Z);
		case 5: SetGPSRoute(playerid, "Garage", GARAGE_X, GARAGE_Y, GARAGE_Z);
		default:
		{
			new destination = listitem - GPS_FIXED_DESTINATIONS;
			if (destination < STORE_COUNT)
			{
				SetGPSRoute(playerid, StoreName[destination],
					StoreX[destination], StoreY[destination], StoreZ[destination]);
				return 1;
			}
			new house = destination - STORE_COUNT;
			if (house < 0 || house >= HOUSE_COUNT) return 1;
			SetGPSRoute(playerid, HouseName[house], HouseX[house], HouseY[house], HouseZ[house]);
		}
	}
	return 1;
}

public HandleGPSCheckpoint(playerid)
{
	if (!gpsRouteActive[playerid]) return 0;
	if (!IsPlayerInRangeOfPoint(playerid, 8.0, gpsRouteX[playerid], gpsRouteY[playerid], gpsRouteZ[playerid]))
	{
		return 0;
	}

	new message[80];
	format(message, sizeof message, "Llegaste a tu destino: %s.", gpsRouteName[playerid]);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	CancelGPSRoute(playerid, false);
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if (!IsAccountLoaded(playerid)) return 1;
	SetGPSRoute(playerid, "Marcador elegido en el mapa", fX, fY, fZ);
	return 1;
}
