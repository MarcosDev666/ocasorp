#define ECONOMY_BANK_X 1463.5
#define ECONOMY_BANK_Y -1010.5
#define ECONOMY_BANK_Z 26.8
#define ECONOMY_MAX_MONEY 999999999

CMD:banco(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!IsPlayerInRangeOfPoint(playerid, 8.0, ECONOMY_BANK_X, ECONOMY_BANK_Y, ECONOMY_BANK_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en el banco.");
	}

	new message[96];
	format(message, sizeof message, "Efectivo: $%d | Cuenta bancaria: $%d",
		GetPlayerMoney(playerid), PI[playerid][jBankMoney]);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	SendClientMessage(playerid, COLOR_GLOBAL, "Usa /depositar, /retirar o /transferir desde el banco.");
	return 1;
}

CMD:depositar(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (IsWalletTransactionPending(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Espera a que termine tu otra transaccion.");
	if (!IsPlayerInRangeOfPoint(playerid, 8.0, ECONOMY_BANK_X, ECONOMY_BANK_Y, ECONOMY_BANK_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en el banco.");
	}

	new amount;
	if (sscanf(params, "i", amount)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /depositar <cantidad>");
	if (amount < 1 || amount > GetPlayerMoney(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Cantidad invalida o efectivo insuficiente.");
	if (PI[playerid][jBankMoney] > ECONOMY_MAX_MONEY - amount) return SendClientMessage(playerid, COLOR_ERROR, "Tu cuenta bancaria alcanzaria el limite permitido.");

	GivePlayerMoney(playerid, -amount);
	PI[playerid][jCash] = GetPlayerMoney(playerid);
	PI[playerid][jBankMoney] += amount;
	SaveData(playerid);

	new message[64];
	format(message, sizeof message, "Depositaste $%d. Saldo bancario: $%d.", amount, PI[playerid][jBankMoney]);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	return 1;
}

CMD:retirar(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (IsWalletTransactionPending(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Espera a que termine tu otra transaccion.");
	if (!IsPlayerInRangeOfPoint(playerid, 8.0, ECONOMY_BANK_X, ECONOMY_BANK_Y, ECONOMY_BANK_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en el banco.");
	}

	new amount;
	if (sscanf(params, "i", amount)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /retirar <cantidad>");
	if (amount < 1 || amount > PI[playerid][jBankMoney]) return SendClientMessage(playerid, COLOR_ERROR, "Cantidad invalida o saldo bancario insuficiente.");
	if (GetPlayerMoney(playerid) > ECONOMY_MAX_MONEY - amount) return SendClientMessage(playerid, COLOR_ERROR, "No puedes llevar tanto efectivo.");

	PI[playerid][jBankMoney] -= amount;
	GivePlayerMoney(playerid, amount);
	PI[playerid][jCash] = GetPlayerMoney(playerid);
	SaveData(playerid);

	new message[64];
	format(message, sizeof message, "Retiraste $%d. Saldo bancario: $%d.", amount, PI[playerid][jBankMoney]);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	return 1;
}

CMD:transferir(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (IsWalletTransactionPending(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Espera a que termine tu otra transaccion.");
	if (!IsPlayerInRangeOfPoint(playerid, 8.0, ECONOMY_BANK_X, ECONOMY_BANK_Y, ECONOMY_BANK_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en el banco.");
	}

	new targetid, amount;
	if (sscanf(params, "ui", targetid, amount)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /transferir <jugador/id> <cantidad>");
	if (targetid == playerid) return SendClientMessage(playerid, COLOR_ERROR, "No puedes transferirte dinero a ti mismo.");
	if (!IsPlayerConnected(targetid) || !IsAccountLoaded(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "El destinatario debe estar conectado e iniciar sesion.");
	if (IsWalletTransactionPending(targetid)) return SendClientMessage(playerid, COLOR_ERROR, "El destinatario esta completando otra transaccion.");
	if (amount < 1 || amount > PI[playerid][jBankMoney]) return SendClientMessage(playerid, COLOR_ERROR, "Cantidad invalida o saldo bancario insuficiente.");
	if (PI[targetid][jBankMoney] > ECONOMY_MAX_MONEY - amount) return SendClientMessage(playerid, COLOR_ERROR, "La cuenta del destinatario alcanzaria el limite permitido.");

	PI[playerid][jBankMoney] -= amount;
	PI[targetid][jBankMoney] += amount;
	SaveData(playerid);
	SaveData(targetid);

	new message[96], targetName[MAX_PLAYER_NAME];
	GetPlayerName(targetid, targetName, sizeof targetName);
	format(message, sizeof message, "Transferiste $%d a %s.", amount, targetName);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	format(message, sizeof message, "Recibiste una transferencia de $%d.", amount);
	SendClientMessage(targetid, COLOR_GLOBAL, message);
	return 1;
}

public RefreshPlayerCash(playerid, session)
{
	if (!IsPlayerConnected(playerid) || playerSession[playerid] != session || PI[playerid][jID] <= 0) return 1;
	new query[96];
	mysql_format(dbz, query, sizeof query, "SELECT jCash FROM players WHERE id=%i", PI[playerid][jID]);
	mysql_tquery(dbz, query, "OnPlayerCashRefreshed", "ii", playerid, session);
	return 1;
}

forward OnPlayerCashRefreshed(playerid, session);
public OnPlayerCashRefreshed(playerid, session)
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[Economy] Error al sincronizar efectivo: %s", error);
		return 1;
	}
	if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;

	new rows, cash;
	cache_get_row_count(rows);
	if (rows < 1) return 1;
	cache_get_value_name_int(0, "jCash", cash);
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, cash);
	PI[playerid][jCash] = cash;
	return 1;
}
