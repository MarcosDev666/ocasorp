#define ADMIN_MAX_LEVEL 5

stock bool:HasAdminLevel(playerid, level)
{
	if (!IsAccountLoaded(playerid) || PI[playerid][jAdmin] < level)
	{
		SendClientMessage(playerid, COLOR_ERROR, "No tienes el nivel de administrador necesario.");
		return false;
	}
	return true;
}

stock bool:CanAdminAffectTarget(playerid, targetid)
{
	if (PI[targetid][jAdmin] >= PI[playerid][jAdmin])
	{
		SendClientMessage(playerid, COLOR_ERROR, "No puedes realizar esa accion contra un administrador de tu mismo nivel o superior.");
		return false;
	}
	return true;
}

stock GetAdminRank(level, rank[], size)
{
	switch (level)
	{
		case 1: format(rank, size, "Ayudante");
		case 2: format(rank, size, "Moderador");
		case 3: format(rank, size, "Administrador");
		case 4: format(rank, size, "Administrador Senior");
		case 5: format(rank, size, "Propietario");
		default: format(rank, size, "Usuario");
	}
	return 1;
}

CMD:admins(playerid, params[])
{
	#pragma unused params
	SendClientMessage(playerid, COLOR_ADMIN, "=== ADMINISTRADORES EN LINEA ===");
	new count;
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (!IsPlayerConnected(i) || !IsAccountLoaded(i) || PI[i][jAdmin] < 1) continue;

		new name[MAX_PLAYER_NAME], rank[32], message[96];
		GetPlayerName(i, name, sizeof name);
		GetAdminRank(PI[i][jAdmin], rank, sizeof rank);
		format(message, sizeof message, "%s (ID %d) - %s", name, i, rank);
		SendClientMessage(playerid, COLOR_GLOBAL, message);
		count++;
	}
	if (!count) SendClientMessage(playerid, COLOR_GLOBAL, "No hay administradores conectados.");
	return 1;
}

CMD:adminchat(playerid, params[])
{
	if (!HasAdminLevel(playerid, 1)) return 1;
	if (isnull(params)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /adminchat <mensaje>");

	new name[MAX_PLAYER_NAME], message[192];
	GetPlayerName(playerid, name, sizeof name);
	format(message, sizeof message, "[ADMIN] %s (nivel %d): %s", name, PI[playerid][jAdmin], params);
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (IsPlayerConnected(i) && IsAccountLoaded(i) && PI[i][jAdmin] > 0)
		{
			SendClientMessage(i, COLOR_ADMIN, message);
		}
	}
	return 1;
}

CMD:kickear(playerid, params[])
{
	if (!HasAdminLevel(playerid, 2)) return 1;
	new targetid;
	if (sscanf(params, "u", targetid)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /kickear <jugador/id>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	if (!CanAdminAffectTarget(playerid, targetid)) return 1;

	new name[MAX_PLAYER_NAME], message[96];
	GetPlayerName(targetid, name, sizeof name);
	format(message, sizeof message, "%s fue expulsado por un administrador.", name);
	SendClientMessageToAll(COLOR_ADMIN, message);
	Kick(targetid);
	return 1;
}

CMD:banear(playerid, params[])
{
	if (!HasAdminLevel(playerid, 3)) return 1;
	new targetid;
	if (sscanf(params, "u", targetid)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /banear <jugador/id>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	if (!CanAdminAffectTarget(playerid, targetid)) return 1;

	new name[MAX_PLAYER_NAME], message[96];
	GetPlayerName(targetid, name, sizeof name);
	format(message, sizeof message, "%s fue baneado por un administrador.", name);
	SendClientMessageToAll(COLOR_ADMIN, message);
	Ban(targetid);
	return 1;
}

CMD:ir(playerid, params[])
{
	if (!HasAdminLevel(playerid, 2)) return 1;
	new targetid;
	if (sscanf(params, "u", targetid)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /ir <jugador/id>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	if (targetid != playerid && !CanAdminAffectTarget(playerid, targetid)) return 1;

	new Float:x, Float:y, Float:z, interior = GetPlayerInterior(targetid), virtualWorld = GetPlayerVirtualWorld(targetid);
	GetPlayerPos(targetid, x, y, z);
	SetPlayerInterior(playerid, interior);
	SetPlayerVirtualWorld(playerid, virtualWorld);
	SetPlayerPos(playerid, x + 1.0, y, z);
	return 1;
}

CMD:traer(playerid, params[])
{
	if (!HasAdminLevel(playerid, 2)) return 1;
	new targetid;
	if (sscanf(params, "u", targetid)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /traer <jugador/id>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	if (!CanAdminAffectTarget(playerid, targetid)) return 1;

	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	SetPlayerInterior(targetid, GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
	SetPlayerPos(targetid, x + 1.0, y, z);
	return 1;
}

CMD:congelar(playerid, params[])
{
	if (!HasAdminLevel(playerid, 2)) return 1;
	new targetid;
	if (sscanf(params, "u", targetid)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /congelar <jugador/id>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	if (!CanAdminAffectTarget(playerid, targetid)) return 1;
	TogglePlayerControllable(targetid, false);
	SendClientMessage(targetid, COLOR_ERROR, "Un administrador te ha congelado.");
	return 1;
}

CMD:descongelar(playerid, params[])
{
	if (!HasAdminLevel(playerid, 2)) return 1;
	new targetid;
	if (sscanf(params, "u", targetid)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /descongelar <jugador/id>");
	if (!IsPlayerConnected(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	TogglePlayerControllable(targetid, true);
	SendClientMessage(targetid, COLOR_GLOBAL, "Un administrador te ha descongelado.");
	return 1;
}

CMD:curar(playerid, params[])
{
	if (!HasAdminLevel(playerid, 3)) return 1;
	new targetid;
	if (sscanf(params, "u", targetid)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /curar <jugador/id>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	if (targetid != playerid && !CanAdminAffectTarget(playerid, targetid)) return 1;
	SetPlayerHealth(targetid, 100.0);
	PI[targetid][jHealth] = 100.0;
	return 1;
}

CMD:dararmadura(playerid, params[])
{
	if (!HasAdminLevel(playerid, 3)) return 1;
	new targetid;
	new Float:armour;
	if (sscanf(params, "uf", targetid, armour)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /dararmadura <jugador/id> <0-100>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	if (targetid != playerid && !CanAdminAffectTarget(playerid, targetid)) return 1;
	if (armour < 0.0 || armour > 100.0) return SendClientMessage(playerid, COLOR_ERROR, "La armadura debe estar entre 0 y 100.");
	SetPlayerArmour(targetid, armour);
	PI[targetid][jArmour] = armour;
	return 1;
}

CMD:setdinero(playerid, params[])
{
	if (!HasAdminLevel(playerid, 4)) return 1;
	new targetid, amount;
	if (sscanf(params, "ui", targetid, amount)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /setdinero <jugador/id> <cantidad>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	if (IsWalletTransactionPending(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "El jugador esta completando otra transaccion.");
	if (targetid != playerid && !CanAdminAffectTarget(playerid, targetid)) return 1;
	if (amount < 0 || amount > 99999999) return SendClientMessage(playerid, COLOR_ERROR, "La cantidad debe estar entre 0 y 99999999.");
	ResetPlayerMoney(targetid);
	GivePlayerMoney(targetid, amount);
	PI[targetid][jCash] = amount;
	return 1;
}

CMD:setskin(playerid, params[])
{
	if (!HasAdminLevel(playerid, 4)) return 1;
	new targetid, skin;
	if (sscanf(params, "ui", targetid, skin)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /setskin <jugador/id> <skin 0-311>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado.");
	if (targetid != playerid && !CanAdminAffectTarget(playerid, targetid)) return 1;
	if (skin < 0 || skin > 311) return SendClientMessage(playerid, COLOR_ERROR, "El skin debe estar entre 0 y 311.");
	SetPlayerSkin(targetid, skin);
	PI[targetid][jSkin] = skin;
	return 1;
}

CMD:setadmin(playerid, params[])
{
	if (!HasAdminLevel(playerid, 5)) return 1;
	new targetid, level;
	if (sscanf(params, "ui", targetid, level)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /setadmin <jugador/id> <nivel 0-5>");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado o no ha iniciado sesion.");
	if (targetid == playerid) return SendClientMessage(playerid, COLOR_ERROR, "No puedes cambiar tu propio nivel.");
	if (level < 0 || level > ADMIN_MAX_LEVEL) return SendClientMessage(playerid, COLOR_ERROR, "El nivel debe estar entre 0 y 5.");

	new query[128];
	mysql_format(dbz, query, sizeof query, "UPDATE players SET jAdmin=%i WHERE jName='%e'", level, PlayerName(targetid));
	mysql_tquery(dbz, query, "OnAdminLevelSet", "iiiii", playerid, targetid, level, playerSession[playerid], playerSession[targetid]);
	return 1;
}

CMD:setfaccion(playerid, params[])
{
	if (!HasAdminLevel(playerid, 4)) return 1;
	new targetid, faction, rank;
	if (sscanf(params, "uii", targetid, faction, rank))
	{
		return SendClientMessage(playerid, COLOR_USAGE, "Uso: /setfaccion <jugador/id> <faccion 0-9> <rango 0-5>");
	}
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Ese jugador no esta conectado o no ha iniciado sesion.");
	}
	if (targetid == playerid) return SendClientMessage(playerid, COLOR_ERROR, "No puedes cambiar tu propia faccion.");
	if (!CanAdminAffectTarget(playerid, targetid)) return 1;
	if (faction < FACTION_NONE || faction > FACTION_MAX
		|| rank < 0 || rank > FACTION_MAX_RANK)
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Faccion: 0-9; rango: 0-5.");
	}
	if ((faction == FACTION_NONE && rank != 0) || (faction != FACTION_NONE && rank == 0))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Usa faccion 0/rango 0 para quitarla; para asignar, usa rango 1-5.");
	}

	new query[128];
	mysql_format(dbz, query, sizeof query,
		"UPDATE players SET jFaction=%i,jFactionRank=%i WHERE id=%i",
		faction, rank, PI[targetid][jID]);
	mysql_tquery(dbz, query, "OnFactionAssigned", "iiiiii", playerid, targetid,
		faction, rank, playerSession[playerid], playerSession[targetid]);
	return 1;
}

forward OnFactionAssigned(actorid, targetid, faction, rank, actorSession, targetSession);
public OnFactionAssigned(actorid, targetid, faction, rank, actorSession, targetSession)
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[Admin] Error al guardar la faccion: %s", error);
		if (IsPlayerConnected(actorid) && playerSession[actorid] == actorSession)
		{
			SendClientMessage(actorid, COLOR_ERROR, "No se pudo guardar la faccion.");
		}
		return 1;
	}
	if (IsPlayerConnected(targetid) && playerSession[targetid] == targetSession)
	{
		PI[targetid][jFaction] = faction;
		PI[targetid][jFactionRank] = rank;

		new factionName[24], rankName[32], message[96];
		GetFactionName(faction, factionName, sizeof factionName);
		GetFactionRankName(faction, rank, rankName, sizeof rankName);
		format(message, sizeof message, "Tu faccion fue actualizada: %s, rango %s.", factionName, rankName);
		SendClientMessage(targetid, COLOR_GLOBAL, message);
	}
	if (IsPlayerConnected(actorid) && playerSession[actorid] == actorSession)
	{
		SendClientMessage(actorid, COLOR_GLOBAL, "Faccion actualizada correctamente.");
	}
	return 1;
}

forward OnAdminLevelSet(actorid, targetid, level, actorSession, targetSession);
public OnAdminLevelSet(actorid, targetid, level, actorSession, targetSession)
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[MySQL] Error al actualizar el nivel de administrador: %s", error);
		if (IsPlayerConnected(actorid) && playerSession[actorid] == actorSession)
		{
			SendClientMessage(actorid, COLOR_ERROR, "No se pudo guardar el nivel de administrador.");
		}
		return 1;
	}

	if (!IsPlayerConnected(targetid) || playerSession[targetid] != targetSession) return 1;
	PI[targetid][jAdmin] = level;

	new rank[32], message[96];
	GetAdminRank(level, rank, sizeof rank);
	format(message, sizeof message, "Tu nivel de administrador ahora es %d (%s).", level, rank);
	SendClientMessage(targetid, COLOR_ADMIN, message);
	if (IsPlayerConnected(actorid) && playerSession[actorid] == actorSession)
	{
		SendClientMessage(actorid, COLOR_GLOBAL, "El nivel de administrador se guardo correctamente.");
	}
	return 1;
}

CMD:ayudaadmin(playerid, params[])
{
	#pragma unused params
	if (!HasAdminLevel(playerid, 1)) return 1;
	SendClientMessage(playerid, COLOR_ADMIN, "=== COMANDOS DE ADMINISTRACION ===");
	SendClientMessage(playerid, COLOR_GLOBAL, "Nivel 1: /adminchat");
	SendClientMessage(playerid, COLOR_GLOBAL, "Nivel 2: /kickear /ir /traer /congelar /descongelar");
	SendClientMessage(playerid, COLOR_GLOBAL, "Nivel 3: /banear /curar /dararmadura");
	SendClientMessage(playerid, COLOR_GLOBAL, "Nivel 4: /setdinero /setskin");
	SendClientMessage(playerid, COLOR_GLOBAL, "Nivel 4: /setfaccion <id> <faccion> <rango>");
	SendClientMessage(playerid, COLOR_GLOBAL, "Nivel 5: /setadmin <id> <nivel>");
	return 1;
}
