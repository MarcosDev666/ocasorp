#define JOB_NONE 0
#define JOB_TAXI 1
#define JOB_COURIER 2
#define JOB_SANITATION 3
#define JOB_CENTER_X 1727.0
#define JOB_CENTER_Y -1877.5
#define JOB_CENTER_Z 13.5
#define MARKET_X 1721.0
#define MARKET_Y -1877.5
#define MARKET_Z 13.5
#define JOB_MAX_LEVEL 10

#define FACTION_NONE 0
#define FACTION_POLICE 1
#define FACTION_EMS 2
#define FACTION_MECHANIC 3
#define FACTION_MAX_RANK 5

new bool:jobOnShift[MAX_PLAYERS];
new jobRoute[MAX_PLAYERS];
new factionServiceCooldown[MAX_PLAYERS];
new gameplayNeedsTimer;

new Float:JobRouteX[3][4] =
{
	{1790.0, 1640.0, 1815.0, 1705.0},
	{1665.0, 1775.0, 1810.0, 1620.0},
	{1795.0, 1615.0, 1745.0, 1830.0}
};
new Float:JobRouteY[3][4] =
{
	{-1905.0, -1855.0, -1720.0, -1775.0},
	{-1810.0, -1690.0, -1850.0, -1920.0},
	{-1815.0, -1750.0, -1940.0, -1830.0}
};
new Float:JobRouteZ[3][4] =
{
	{13.4, 13.4, 13.4, 13.4},
	{13.4, 13.4, 13.4, 13.4},
	{13.4, 13.4, 13.4, 13.4}
};

forward UpdatePlayerNeeds();

stock GetJobName(job, name[], size)
{
	switch (job)
	{
		case JOB_TAXI: format(name, size, "Taxista");
		case JOB_COURIER: format(name, size, "Repartidor");
		case JOB_SANITATION: format(name, size, "Recolector");
		default: format(name, size, "Desempleado");
	}
	return 1;
}

stock GetFactionName(faction, name[], size)
{
	switch (faction)
	{
		case FACTION_POLICE: format(name, size, "Policia");
		case FACTION_EMS: format(name, size, "EMS");
		case FACTION_MECHANIC: format(name, size, "Mecanicos");
		default: format(name, size, "Civil");
	}
	return 1;
}

stock GetFactionRankName(faction, rank, name[], size)
{
	if (rank < 1 || rank > FACTION_MAX_RANK)
	{
		format(name, size, "Sin rango");
		return 1;
	}

	switch (faction)
	{
		case FACTION_POLICE:
		{
			switch (rank)
			{
				case 1: format(name, size, "Cadete");
				case 2: format(name, size, "Oficial");
				case 3: format(name, size, "Sargento");
				case 4: format(name, size, "Teniente");
				case 5: format(name, size, "Comisario");
			}
		}
		case FACTION_EMS:
		{
			switch (rank)
			{
				case 1: format(name, size, "Practicante");
				case 2: format(name, size, "Paramedico");
				case 3: format(name, size, "Medico");
				case 4: format(name, size, "Jefe de guardia");
				case 5: format(name, size, "Director");
			}
		}
		case FACTION_MECHANIC:
		{
			switch (rank)
			{
				case 1: format(name, size, "Aprendiz");
				case 2: format(name, size, "Mecanico");
				case 3: format(name, size, "Especialista");
				case 4: format(name, size, "Capataz");
				case 5: format(name, size, "Jefe de taller");
			}
		}
	}
	return 1;
}

public InitializeGameplaySystems()
{
	new timerName[18] = "UpdatePlayerNeeds";
	gameplayNeedsTimer = SetTimer(timerName, 300000, true);
	if (!gameplayNeedsTimer)
	{
		printf("[Gameplay] Error: no se pudo iniciar el temporizador de necesidades.");
		return 0;
	}
	if (!InitializeHUDSystem()) return 0;
	return 1;
}

public InitializeGameplayPlayer(playerid)
{
	jobOnShift[playerid] = false;
	jobRoute[playerid] = 0;
	factionServiceCooldown[playerid] = 0;
	PI[playerid][jJob] = JOB_NONE;
	PI[playerid][jJobLevel] = 1;
	PI[playerid][jJobXP] = 0;
	PI[playerid][jFaction] = FACTION_NONE;
	PI[playerid][jFactionRank] = 0;
	PI[playerid][jHunger] = 100;
	PI[playerid][jThirst] = 100;
	InitializeInventoryPlayer(playerid);
	InitializeGPSPlayer(playerid);
	InitializeHUDPlayer(playerid);
	return 1;
}

public OnGameplayPlayerLoaded(playerid)
{
	if (PI[playerid][jJob] < JOB_NONE || PI[playerid][jJob] > JOB_SANITATION)
	{
		PI[playerid][jJob] = JOB_NONE;
	}
	if (PI[playerid][jJobLevel] < 1 || PI[playerid][jJobLevel] > JOB_MAX_LEVEL)
	{
		PI[playerid][jJobLevel] = 1;
	}
	if (PI[playerid][jJobXP] < 0) PI[playerid][jJobXP] = 0;
	if (PI[playerid][jFaction] < FACTION_NONE || PI[playerid][jFaction] > FACTION_MECHANIC)
	{
		PI[playerid][jFaction] = FACTION_NONE;
		PI[playerid][jFactionRank] = 0;
	}
	if (PI[playerid][jFaction] == FACTION_NONE
		|| PI[playerid][jFactionRank] < 1
		|| PI[playerid][jFactionRank] > FACTION_MAX_RANK)
	{
		PI[playerid][jFaction] = FACTION_NONE;
		PI[playerid][jFactionRank] = 0;
	}
	if (PI[playerid][jHunger] < 0 || PI[playerid][jHunger] > 100) PI[playerid][jHunger] = 100;
	if (PI[playerid][jThirst] < 0 || PI[playerid][jThirst] > 100) PI[playerid][jThirst] = 100;

	LoadPlayerInventory(playerid);
	LoadPlayerHouse(playerid);
	ShowGameplayHUD(playerid);
	return 1;
}

public SaveGameplayData(playerid)
{
	return SaveGameplayDataInternal(playerid, false);
}

stock SaveGameplayDataInternal(playerid, bool:sync)
{
	if (PI[playerid][jID] <= 0) return 1;
	new query[256];
	mysql_format(dbz, query, sizeof query,
		"UPDATE players SET jJob=%i,jJobLevel=%i,jJobXP=%i,jFaction=%i,jFactionRank=%i,jHunger=%i,jThirst=%i WHERE id=%i",
		PI[playerid][jJob], PI[playerid][jJobLevel], PI[playerid][jJobXP],
		PI[playerid][jFaction], PI[playerid][jFactionRank], PI[playerid][jHunger],
		PI[playerid][jThirst], PI[playerid][jID]);
	if (sync)
	{
		mysql_query(dbz, query, false);
		if (mysql_errno(dbz) != 0)
		{
			new error[128];
			mysql_error(error, sizeof error, dbz);
			printf("[MySQL] Error al guardar gameplay durante el cierre: %s", error);
		}
	}
	else
	{
		mysql_tquery(dbz, query, "OnGameplayDataSaved");
	}
	if (sync) SaveInventoryDataSync(playerid);
	else SaveInventoryData(playerid);
	return 1;
}

forward OnGameplayDataSaved();
public OnGameplayDataSaved()
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[Gameplay] Error al guardar los datos de trabajo/faccion/necesidades: %s", error);
	}
	return 1;
}

public CleanupGameplayPlayer(playerid)
{
	jobOnShift[playerid] = false;
	jobRoute[playerid] = 0;
	CleanupInventoryPlayer(playerid);
	CleanupGPSPlayer(playerid);
	CleanupHUDPlayer(playerid);
	return 1;
}

public HandleGameplayCheckpoint(playerid)
{
	if (!jobOnShift[playerid]) return 0;
	if (PI[playerid][jJob] < JOB_TAXI || PI[playerid][jJob] > JOB_SANITATION) return 0;
	if (jobRoute[playerid] < 0 || jobRoute[playerid] >= 4) return 0;

	new routeIndex = PI[playerid][jJob] - 1;
	if (!IsPlayerInRangeOfPoint(playerid, 8.0,
		JobRouteX[routeIndex][jobRoute[playerid]],
		JobRouteY[routeIndex][jobRoute[playerid]],
		JobRouteZ[routeIndex][jobRoute[playerid]]))
	{
		return 0;
	}

	new reward = 250 + (PI[playerid][jJobLevel] * 50);
	GivePlayerMoney(playerid, reward);
	PI[playerid][jCash] = GetPlayerMoney(playerid);
	if (PI[playerid][jJobLevel] < JOB_MAX_LEVEL)
	{
		PI[playerid][jJobXP]++;
		new requiredXP = PI[playerid][jJobLevel] * 5;
		if (PI[playerid][jJobXP] >= requiredXP)
		{
			PI[playerid][jJobXP] -= requiredXP;
			PI[playerid][jJobLevel]++;
			if (PI[playerid][jJobLevel] == JOB_MAX_LEVEL) PI[playerid][jJobXP] = 0;
			SendClientMessage(playerid, COLOR_ADMIN, "Subiste de nivel en tu trabajo.");
		}
	}

	new message[112];
	format(message, sizeof message, "Servicio completado: cobraste $%d y ganaste experiencia.", reward);
	SendClientMessage(playerid, COLOR_GLOBAL, message);

	jobRoute[playerid]++;
	if (jobRoute[playerid] >= 4) jobRoute[playerid] = 0;
	UpdatePlayerRouteCheckpoint(playerid);
	SaveData(playerid);
	return 1;
}

public UpdatePlayerNeeds()
{
	for (new playerid = 0; playerid < MAX_PLAYERS; playerid++)
	{
		if (!IsPlayerConnected(playerid) || !IsAccountLoaded(playerid)) continue;

		if (PI[playerid][jHunger] > 0) PI[playerid][jHunger]--;
		if (PI[playerid][jThirst] > 0) PI[playerid][jThirst] -= 2;
		if (PI[playerid][jThirst] < 0) PI[playerid][jThirst] = 0;

		new Float:health;
		GetPlayerHealth(playerid, health);
		if (PI[playerid][jHunger] == 0 || PI[playerid][jThirst] == 0)
		{
			health -= 2.0;
			if (health < 1.0) health = 1.0;
			SetPlayerHealth(playerid, health);
		}
		PI[playerid][jHealth] = health;

		PersistNeeds(playerid);
	}
	return 1;
}

stock PersistNeeds(playerid)
{
	if (PI[playerid][jID] <= 0) return 1;
	new query[160];
	mysql_format(dbz, query, sizeof query,
		"UPDATE players SET jHunger=%i,jThirst=%i,jHealth=%f WHERE id=%i",
		PI[playerid][jHunger], PI[playerid][jThirst], PI[playerid][jHealth], PI[playerid][jID]);
	mysql_tquery(dbz, query, "OnNeedsSaved");
	return 1;
}

forward OnNeedsSaved();
public OnNeedsSaved()
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[Gameplay] Error al guardar hambre/sed: %s", error);
	}
	return 1;
}

CMD:empleos(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!IsPlayerInRangeOfPoint(playerid, 10.0, JOB_CENTER_X, JOB_CENTER_Y, JOB_CENTER_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes ir a la agencia de empleo, cerca del spawn.");
	}
	Dialog_Show(playerid, "OnDialogChooseJob", DIALOG_STYLE_LIST,
		"Agencia de empleo",
		"Taxista\nRepartidor\nRecolector municipal\nRenunciar a mi empleo",
		"Seleccionar", "Cerrar");
	return 1;
}

Dialog:OnDialogChooseJob(playerid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if (!response || !IsAccountLoaded(playerid)) return 1;

	new job = listitem + 1;
	if (listitem == 3) job = JOB_NONE;
	if (job < JOB_NONE || job > JOB_SANITATION) return 1;

	new query[128];
	mysql_format(dbz, query, sizeof query,
		"UPDATE players SET jJob=%i,jJobLevel=1,jJobXP=0 WHERE id=%i",
		job, PI[playerid][jID]);
	mysql_tquery(dbz, query, "OnJobChanged", "iii", playerid, job, playerSession[playerid]);
	return 1;
}

forward OnJobChanged(playerid, job, session);
public OnJobChanged(playerid, job, session)
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[Gameplay] Error al cambiar el trabajo: %s", error);
		if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
		{
			SendClientMessage(playerid, COLOR_ERROR, "No se pudo guardar el cambio de trabajo.");
		}
		return 1;
	}
	if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;

	jobOnShift[playerid] = false;
	jobRoute[playerid] = 0;
	PI[playerid][jJob] = job;
	PI[playerid][jJobLevel] = 1;
	PI[playerid][jJobXP] = 0;
	SetupRentalCheckpoint(playerid);

	new name[24], message[80];
	GetJobName(job, name, sizeof name);
	format(message, sizeof message, "Tu nuevo estado laboral es: %s.", name);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	return 1;
}

CMD:turno(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (IsWalletTransactionPending(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Espera a que termine tu otra transaccion.");
	if (PI[playerid][jJob] == JOB_NONE) return SendClientMessage(playerid, COLOR_ERROR, "Primero consigue un empleo en /empleos.");

	if (jobOnShift[playerid])
	{
		jobOnShift[playerid] = false;
		jobRoute[playerid] = 0;
		SetupRentalCheckpoint(playerid);
		SendClientMessage(playerid, COLOR_GLOBAL, "Terminaste tu turno.");
		return 1;
	}

	jobOnShift[playerid] = true;
	jobRoute[playerid] = 0;
	UpdatePlayerRouteCheckpoint(playerid);
	SendClientMessage(playerid, COLOR_GLOBAL, "Turno iniciado. Sigue los checkpoints y cobra por cada servicio.");
	return 1;
}

CMD:miempleo(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	new name[24], message[128];
	GetJobName(PI[playerid][jJob], name, sizeof name);
	format(message, sizeof message, "Trabajo: %s | Nivel: %d | Experiencia: %d/%d",
		name, PI[playerid][jJobLevel], PI[playerid][jJobXP], PI[playerid][jJobLevel] * 5);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	return 1;
}

CMD:faccion(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	new name[24], rank[32], message[100];
	GetFactionName(PI[playerid][jFaction], name, sizeof name);
	GetFactionRankName(PI[playerid][jFaction], PI[playerid][jFactionRank], rank, sizeof rank);
	format(message, sizeof message, "Faccion: %s | Rango: %s (%d)", name, rank, PI[playerid][jFactionRank]);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	return 1;
}

CMD:facciones(playerid, params[])
{
	#pragma unused params
	SendClientMessage(playerid, COLOR_ADMIN, "Facciones disponibles: Policia (1), EMS (2), Mecanicos (3).");
	SendClientMessage(playerid, COLOR_GLOBAL, "La asignacion de miembros se realiza con /setfaccion <id> <faccion 0-3> <rango 0-5>.");
	return 1;
}

CMD:miembrosfaccion(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (PI[playerid][jFaction] == FACTION_NONE) return SendClientMessage(playerid, COLOR_ERROR, "No perteneces a ninguna faccion.");

	new factionName[24], rankName[32], name[MAX_PLAYER_NAME], message[96], count;
	GetFactionName(PI[playerid][jFaction], factionName, sizeof factionName);
	SendClientMessage(playerid, COLOR_ADMIN, "=== MIEMBROS DE TU FACCION ===");
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (!IsPlayerConnected(i) || !IsAccountLoaded(i)
			|| PI[i][jFaction] != PI[playerid][jFaction]) continue;
		GetPlayerName(i, name, sizeof name);
		GetFactionRankName(PI[i][jFaction], PI[i][jFactionRank], rankName, sizeof rankName);
		format(message, sizeof message, "%s (ID %d) - %s", name, i, rankName);
		SendClientMessage(playerid, COLOR_GLOBAL, message);
		count++;
	}
	if (!count)
	{
		format(message, sizeof message, "No hay miembros conectados de %s.", factionName);
		SendClientMessage(playerid, COLOR_GLOBAL, message);
	}
	return 1;
}

CMD:f(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (PI[playerid][jFaction] == FACTION_NONE) return SendClientMessage(playerid, COLOR_ERROR, "No perteneces a ninguna faccion.");
	if (isnull(params)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /f <mensaje>");

	new faction[24], name[MAX_PLAYER_NAME], message[192];
	GetFactionName(PI[playerid][jFaction], faction, sizeof faction);
	GetPlayerName(playerid, name, sizeof name);
	format(message, sizeof message, "[%s] %s: %s", faction, name, params);
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (IsPlayerConnected(i) && IsAccountLoaded(i)
			&& PI[i][jFaction] == PI[playerid][jFaction])
		{
			SendClientMessage(i, COLOR_ADMIN, message);
		}
	}
	return 1;
}

CMD:promover(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (PI[playerid][jFaction] == FACTION_NONE || PI[playerid][jFactionRank] != FACTION_MAX_RANK)
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Solo el lider de una faccion puede promover miembros.");
	}

	new targetid, rank;
	if (sscanf(params, "ui", targetid, rank)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /promover <jugador/id> <rango 1-4>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	if (targetid == playerid || PI[targetid][jFaction] != PI[playerid][jFaction]) return SendClientMessage(playerid, COLOR_ERROR, "El jugador debe pertenecer a tu faccion y no puedes promoverte.");
	if (rank < 1 || rank >= FACTION_MAX_RANK || rank <= PI[targetid][jFactionRank])
	{
		return SendClientMessage(playerid, COLOR_ERROR, "El rango debe ser mayor al actual y menor que el rango de lider (5).");
	}
	if (!IsPlayerInRangeOfPoint(playerid, 25.0, JOB_CENTER_X, JOB_CENTER_Y, JOB_CENTER_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en la base de facciones para promover.");
	}
	SaveFactionRank(playerid, targetid, rank);
	return 1;
}

CMD:degradar(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (PI[playerid][jFaction] == FACTION_NONE || PI[playerid][jFactionRank] != FACTION_MAX_RANK)
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Solo el lider de una faccion puede degradar miembros.");
	}

	new targetid, rank;
	if (sscanf(params, "ui", targetid, rank)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /degradar <jugador/id> <rango 0-4>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	if (targetid == playerid || PI[targetid][jFaction] != PI[playerid][jFaction]) return SendClientMessage(playerid, COLOR_ERROR, "El jugador debe pertenecer a tu faccion y no puedes degradarte.");
	if (rank < 0 || rank >= PI[targetid][jFactionRank]) return SendClientMessage(playerid, COLOR_ERROR, "El rango nuevo debe ser menor al actual.");
	if (!IsPlayerInRangeOfPoint(playerid, 25.0, JOB_CENTER_X, JOB_CENTER_Y, JOB_CENTER_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en la base de facciones para degradar.");
	}
	SaveFactionRank(playerid, targetid, rank);
	return 1;
}

stock SaveFactionRank(actorid, targetid, rank)
{
	new query[112];
	mysql_format(dbz, query, sizeof query,
		"UPDATE players SET jFactionRank=%i,jFaction=%i WHERE id=%i",
		rank, rank == 0 ? FACTION_NONE : PI[targetid][jFaction], PI[targetid][jID]);
	mysql_tquery(dbz, query, "OnFactionRankSaved", "iiiii", actorid, targetid,
		rank, playerSession[actorid], playerSession[targetid]);
	return 1;
}

forward OnFactionRankSaved(actorid, targetid, rank, actorSession, targetSession);
public OnFactionRankSaved(actorid, targetid, rank, actorSession, targetSession)
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[Gameplay] Error al cambiar el rango de faccion: %s", error);
		if (IsPlayerConnected(actorid) && playerSession[actorid] == actorSession)
		{
			SendClientMessage(actorid, COLOR_ERROR, "No se pudo guardar el cambio de rango.");
		}
		return 1;
	}
	if (IsPlayerConnected(targetid) && playerSession[targetid] == targetSession)
	{
		PI[targetid][jFactionRank] = rank;
		if (rank == 0) PI[targetid][jFaction] = FACTION_NONE;
		SendClientMessage(targetid, COLOR_GLOBAL, "Tu rango de faccion fue actualizado.");
	}
	if (IsPlayerConnected(actorid) && playerSession[actorid] == actorSession)
	{
		SendClientMessage(actorid, COLOR_GLOBAL, "Rango de faccion actualizado.");
	}
	return 1;
}

CMD:uniforme(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (PI[playerid][jFaction] == FACTION_NONE) return SendClientMessage(playerid, COLOR_ERROR, "No perteneces a una faccion.");
	if (!IsPlayerInRangeOfPoint(playerid, 25.0, JOB_CENTER_X, JOB_CENTER_Y, JOB_CENTER_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Acercate a la base de facciones para cambiarte el uniforme.");
	}

	switch (PI[playerid][jFaction])
	{
		case FACTION_POLICE: SetPlayerSkin(playerid, 280);
		case FACTION_EMS: SetPlayerSkin(playerid, 276);
		case FACTION_MECHANIC: SetPlayerSkin(playerid, 50);
	}
	PI[playerid][jSkin] = GetPlayerSkin(playerid);
	SendClientMessage(playerid, COLOR_GLOBAL, "Uniforme de faccion equipado.");
	return 1;
}

stock bool:CanUseFactionService(playerid)
{
	if (factionServiceCooldown[playerid] > gettime())
	{
		SendClientMessage(playerid, COLOR_ERROR, "Debes esperar antes de volver a usar un servicio de faccion.");
		return false;
	}
	factionServiceCooldown[playerid] = gettime() + 15;
	return true;
}

stock bool:IsFactionTargetNearby(playerid, targetid)
{
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return false;
	if (GetPlayerInterior(playerid) != GetPlayerInterior(targetid)
		|| GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(targetid))
	{
		return false;
	}
	new Float:x, Float:y, Float:z;
	GetPlayerPos(targetid, x, y, z);
	return IsPlayerInRangeOfPoint(playerid, 6.0, x, y, z) != 0;
}

CMD:curarfac(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (PI[playerid][jFaction] != FACTION_EMS || PI[playerid][jFactionRank] < 2)
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Necesitas ser EMS de rango 2 o superior.");
	}
	new targetid;
	if (sscanf(params, "u", targetid)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /curarfac <jugador/id>");
	if (targetid == playerid || !IsFactionTargetNearby(playerid, targetid))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "El paciente debe estar conectado, cerca y en tu mismo interior.");
	}
	if (!CanUseFactionService(playerid)) return 1;

	SetPlayerHealth(targetid, 100.0);
	PI[targetid][jHealth] = 100.0;
	SaveData(targetid);
	SendClientMessage(targetid, COLOR_GLOBAL, "Un paramedico de EMS te atendio.");
	SendClientMessage(playerid, COLOR_GLOBAL, "Atencion medica completada.");
	return 1;
}

CMD:reparar(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (PI[playerid][jFaction] != FACTION_MECHANIC || PI[playerid][jFactionRank] < 2)
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Necesitas ser mecanico de rango 2 o superior.");
	}
	new targetid;
	if (sscanf(params, "u", targetid)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /reparar <jugador/id>");
	if (targetid == playerid || !IsFactionTargetNearby(playerid, targetid))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "El cliente debe estar cerca y en tu mismo interior.");
	}
	if (!IsPlayerInAnyVehicle(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "El cliente debe estar dentro de su vehiculo.");
	if (!CanUseFactionService(playerid)) return 1;

	RepairVehicle(GetPlayerVehicleID(targetid));
	SendClientMessage(targetid, COLOR_GLOBAL, "Un mecanico reparo tu vehiculo.");
	SendClientMessage(playerid, COLOR_GLOBAL, "Reparacion completada.");
	return 1;
}

CMD:multar(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (PI[playerid][jFaction] != FACTION_POLICE || PI[playerid][jFactionRank] < 3)
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Necesitas ser policia de rango 3 o superior.");
	}
	new targetid, amount;
	if (sscanf(params, "ui", targetid, amount)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /multar <jugador/id> <monto 1-5000>");
	if (targetid == playerid || !IsFactionTargetNearby(playerid, targetid))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "El ciudadano debe estar cerca y en tu mismo interior.");
	}
	if (amount < 1 || amount > 5000) return SendClientMessage(playerid, COLOR_ERROR, "La multa debe estar entre $1 y $5000.");
	if (GetPlayerMoney(targetid) < amount) return SendClientMessage(playerid, COLOR_ERROR, "El ciudadano no tiene dinero suficiente.");
	if (!CanUseFactionService(playerid)) return 1;
	if (IsWalletTransactionPending(targetid))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "El ciudadano esta completando otra transaccion.");
	}

	GivePlayerMoney(targetid, -amount);
	PI[targetid][jCash] = GetPlayerMoney(targetid);
	SaveData(targetid);
	new message[80];
	format(message, sizeof message, "Recibiste una multa policial de $%d.", amount);
	SendClientMessage(targetid, COLOR_ERROR, message);
	format(message, sizeof message, "Multa aplicada correctamente: $%d.", amount);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	return 1;
}

CMD:ayudagame(playerid, params[])
{
	#pragma unused params
	SendClientMessage(playerid, COLOR_ADMIN, "=== SISTEMAS DE JUEGO ===");
	SendClientMessage(playerid, COLOR_GLOBAL, "/empleos (agencia) | /turno | /miempleo");
	SendClientMessage(playerid, COLOR_GLOBAL, "/faccion | /facciones | /miembrosfaccion | /f <mensaje> | /promover | /degradar | /uniforme");
	SendClientMessage(playerid, COLOR_GLOBAL, "Policia: /multar | EMS: /curarfac | Mecanicos: /reparar");
	SendClientMessage(playerid, COLOR_GLOBAL, "/inventario | /usar <slot> | /comprar <agua|comida|botiquin|kit> [cantidad]");
	SendClientMessage(playerid, COLOR_GLOBAL, "Hambre y sed se recuperan usando objetos del inventario; el HUD muestra velocidad y estado.");
	return 1;
}
