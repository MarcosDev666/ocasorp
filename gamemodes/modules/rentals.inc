#include <YSI_Coding\y_hooks>

#define RENTAL_X 1698.0
#define RENTAL_Y -1876.0
#define RENTAL_Z 13.5
#define RENTAL_VEHICLE_X 1693.5
#define RENTAL_VEHICLE_Y -1876.0
#define RENTAL_VEHICLE_Z 13.2
#define RENTAL_VEHICLE_ANGLE 0.0
#define RENTAL_DURATION 600000
#define RENTAL_DURATION_SECONDS 600

new rentalVehicle[MAX_PLAYERS];
new rentalTimer[MAX_PLAYERS];
new rentalSession[MAX_PLAYERS];

public SetupRentalCheckpoint(playerid)
{
	return UpdatePlayerRouteCheckpoint(playerid);
}

public InitializeRentalPlayer(playerid)
{
	rentalVehicle[playerid] = INVALID_VEHICLE_ID;
	rentalTimer[playerid] = 0;
	rentalSession[playerid]++;
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (rentalVehicle[i] != INVALID_VEHICLE_ID)
		{
			SetVehicleParamsForPlayer(rentalVehicle[i], playerid, 0, 1);
		}
	}
	return 1;
}

public CleanupRentalPlayer(playerid)
{
	rentalSession[playerid]++;
	if (rentalTimer[playerid])
	{
		KillTimer(rentalTimer[playerid]);
		rentalTimer[playerid] = 0;
	}
	if (rentalVehicle[playerid] != INVALID_VEHICLE_ID)
	{
		DestroyVehicle(rentalVehicle[playerid]);
		rentalVehicle[playerid] = INVALID_VEHICLE_ID;
	}
	return 1;
}

stock ShowRentalMenu(playerid)
{
	new text[96];
	if (rentalVehicle[playerid] != INVALID_VEHICLE_ID)
	{
		format(text, sizeof text, "Devolver vehiculo rentado");
		return Dialog_Show(playerid, "OnDialogRental", DIALOG_STYLE_LIST,
			"Renta de vehiculos",
			text,
			"Seleccionar", "Cerrar");
	}

	format(text, sizeof text, "Manana - $500\nStallion - $800\nGlendale - $750\nGreenwood - $1000");
	return Dialog_Show(playerid, "OnDialogRental", DIALOG_STYLE_LIST,
		"Renta de vehiculos - 10 minutos",
		text,
		"Rentar", "Cerrar");
}

hook OnPlayerEnterCheckpoint(playerid)
{
	if (!IsAccountLoaded(playerid)) return 1;
	if (HandleGPSCheckpoint(playerid)) return 1;
	if (HandleGameplayCheckpoint(playerid)) return 1;
	if (IsPlayerInRangeOfPoint(playerid, 8.0, RENTAL_X, RENTAL_Y, RENTAL_Z))
	{
		ShowRentalMenu(playerid);
	}
	return 1;
}

CMD:rentar(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!IsPlayerInRangeOfPoint(playerid, 5.0, RENTAL_X, RENTAL_Y, RENTAL_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en el checkpoint de renta para usar este comando.");
	}
	ShowRentalMenu(playerid);
	return 1;
}

CMD:devolverveh(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (rentalVehicle[playerid] == INVALID_VEHICLE_ID) return SendClientMessage(playerid, COLOR_ERROR, "No tienes un vehiculo rentado.");
	if (!IsPlayerInRangeOfPoint(playerid, 5.0, RENTAL_X, RENTAL_Y, RENTAL_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes devolver el vehiculo en el checkpoint de renta.");
	}
	FinishRental(playerid, true);
	return 1;
}

Dialog:OnDialogRental(playerid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if (!response) return 1;
	if (!IsAccountLoaded(playerid)) return 1;
	if (IsWalletTransactionPending(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Espera a que termine tu otra transaccion.");

	if (rentalVehicle[playerid] != INVALID_VEHICLE_ID)
	{
		if (IsPlayerInRangeOfPoint(playerid, 5.0, RENTAL_X, RENTAL_Y, RENTAL_Z))
		{
			FinishRental(playerid, true);
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Debes estar en el checkpoint para devolver el vehiculo.");
		}
		return 1;
	}

	new model, price;
	switch (listitem)
	{
		case 0: { model = 410; price = 500; }
		case 1: { model = 439; price = 800; }
		case 2: { model = 466; price = 750; }
		case 3: { model = 492; price = 1000; }
		default: return 1;
	}

	if (GetPlayerMoney(playerid) < price)
	{
		SendClientMessage(playerid, COLOR_ERROR, "No tienes suficiente dinero para esa renta.");
		return 1;
	}

	new vehicleid = CreateVehicle(model, RENTAL_VEHICLE_X, RENTAL_VEHICLE_Y, RENTAL_VEHICLE_Z,
		RENTAL_VEHICLE_ANGLE, -1, -1, RENTAL_DURATION_SECONDS);
	if (vehicleid == INVALID_VEHICLE_ID)
	{
		SendClientMessage(playerid, COLOR_ERROR, "No se pudo crear el vehiculo. Intentalo de nuevo.");
		return 1;
	}

	GivePlayerMoney(playerid, -price);
	PI[playerid][jCash] = GetPlayerMoney(playerid);
	rentalVehicle[playerid] = vehicleid;
	rentalSession[playerid]++;

	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if (IsPlayerConnected(i) && i != playerid)
		{
			SetVehicleParamsForPlayer(vehicleid, i, 0, 1);
		}
	}
	SetVehicleParamsForPlayer(vehicleid, playerid, 0, 0);

	new timerName[13] = "ExpireRental";
	new timerParams[4] = "iii";
	rentalTimer[playerid] = SetTimerEx(timerName, RENTAL_DURATION, false,
		timerParams, playerid, rentalSession[playerid], playerSession[playerid]);
	if (!rentalTimer[playerid])
	{
		FinishRental(playerid, false);
		GivePlayerMoney(playerid, price);
		PI[playerid][jCash] = GetPlayerMoney(playerid);
		SendClientMessage(playerid, COLOR_ERROR, "No se pudo iniciar el tiempo de renta; se cancelo y devolvio el cobro.");
		return 1;
	}

	new message[96];
	format(message, sizeof message, "Renta iniciada por 10 minutos. Costo: $%d. Devuelvelo en el checkpoint.", price);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	PutPlayerInVehicle(playerid, vehicleid, 0);
	return 1;
}

forward ExpireRental(playerid, rentalid, playersession);
public ExpireRental(playerid, rentalid, playersession)
{
	if (playerSession[playerid] != playersession || rentalSession[playerid] != rentalid) return 1;
	rentalTimer[playerid] = 0;
	FinishRental(playerid, false);
	if (IsPlayerConnected(playerid))
	{
		SendClientMessage(playerid, COLOR_ERROR, "Tu tiempo de renta termino y el vehiculo fue retirado.");
	}
	return 1;
}

stock FinishRental(playerid, returned)
{
	if (rentalTimer[playerid])
	{
		KillTimer(rentalTimer[playerid]);
		rentalTimer[playerid] = 0;
	}
	if (rentalVehicle[playerid] != INVALID_VEHICLE_ID)
	{
		if (GetPlayerVehicleID(playerid) == rentalVehicle[playerid]) RemovePlayerFromVehicle(playerid);
		DestroyVehicle(rentalVehicle[playerid]);
		rentalVehicle[playerid] = INVALID_VEHICLE_ID;
	}
	rentalSession[playerid]++;
	if (returned)
	{
		SendClientMessage(playerid, COLOR_GLOBAL, "Vehiculo devuelto. Gracias por usar la renta.");
	}
	return 1;
}
