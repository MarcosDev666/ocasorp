#define DEALERSHIP_X 2131.6
#define DEALERSHIP_Y -1150.4
#define DEALERSHIP_Z 24.1
#define GARAGE_X 1668.0
#define GARAGE_Y -1830.0
#define GARAGE_Z 13.4

#define HOUSE_COUNT 5
#define MAX_OWNED_VEHICLES 3
#define HOUSE_INTERIOR 1
#define HOUSE_INTERIOR_X 223.0439
#define HOUSE_INTERIOR_Y 1287.2598
#define HOUSE_INTERIOR_Z 1082.1406
#define GARAGE_PARKING_SPACES 3

new HouseName[HOUSE_COUNT][32] =
{
	"Casa de Idlewood",
	"Casa de Ganton",
	"Casa de Jefferson",
	"Casa de Marina",
	"Casa de Vinewood"
};
new HousePrice[HOUSE_COUNT] = {25000, 35000, 42000, 50000, 75000};
new Float:HouseX[HOUSE_COUNT] = {2124.0, 2507.0, 2229.0, 807.0, 1298.0};
new Float:HouseY[HOUSE_COUNT] = {-1743.0, -1693.0, -1159.0, -1604.0, -801.0};
new Float:HouseZ[HOUSE_COUNT] = {13.5, 13.5, 25.8, 13.5, 84.1};
new Float:GarageSpawnX[GARAGE_PARKING_SPACES] = {1668.0, 1672.0, 1676.0};
new Float:GarageSpawnY[GARAGE_PARKING_SPACES] = {-1830.0, -1830.0, -1830.0};
new houseOwner[HOUSE_COUNT];
new housePickup[HOUSE_COUNT];
new bool:propertyDataReady;
new playerHouseID[MAX_PLAYERS];
new playerHousePending[MAX_PLAYERS];
new bool:vehiclePurchasePending[MAX_PLAYERS];
new bool:vehicleListPending[MAX_PLAYERS];
new listedVehicleCount[MAX_PLAYERS];
new listedVehicleRecord[MAX_PLAYERS][MAX_OWNED_VEHICLES];
new listedVehicleModel[MAX_PLAYERS][MAX_OWNED_VEHICLES];
new vehicleRecordID[MAX_VEHICLES];
new vehicleOwnerDBID[MAX_VEHICLES];
new bool:vehicleStorePending[MAX_VEHICLES];

new VehicleCatalogModel[] = {410, 401, 466, 492, 516};
new VehicleCatalogPrice[] = {15000, 25000, 32000, 42000, 55000};
new VehicleCatalogName[5][20] =
{
	"Manana",
	"Bravura",
	"Glendale",
	"Greenwood",
	"Nebula"
};

forward InitializePropertySystems();
forward InitializePropertyPlayer(playerid);
forward LoadPlayerHouse(playerid);
forward CleanupPropertyPlayer(playerid);
forward PreparePropertiesDisconnect(playerid);
forward StoreAllVehiclesOnShutdown();
forward bool:FindFreeGarageSpace(&Float:x, &Float:y);
forward Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2);

stock bool:IsWalletTransactionPending(playerid)
{
	return vehiclePurchasePending[playerid] || playerHousePending[playerid] != 0;
}

public InitializePropertySystems()
{
	propertyDataReady = false;
	for (new house = 0; house < HOUSE_COUNT; house++)
	{
		houseOwner[house] = -1;
		housePickup[house] = CreatePickup(1273, 1, HouseX[house], HouseY[house], HouseZ[house], 0);
		if (housePickup[house] == -1)
		{
			printf("[Properties] Error: no se pudo crear el pickup de %s.", HouseName[house]);
		}
	}

	mysql_tquery(dbz, "DELETE FROM player_vehicles WHERE paid=0", "OnVehicleRecoveryComplete");
	mysql_tquery(dbz, "UPDATE player_vehicles SET stored=1 WHERE paid=1 AND stored=0", "OnVehicleRecoveryComplete");
	mysql_tquery(dbz, "SELECT id,owner_id FROM player_houses", "OnPropertyOwnershipLoaded");
	return 1;
}

public InitializePropertyPlayer(playerid)
{
	playerHouseID[playerid] = -2;
	playerHousePending[playerid] = 0;
	vehiclePurchasePending[playerid] = false;
	vehicleListPending[playerid] = false;
	listedVehicleCount[playerid] = 0;
	for (new slot = 0; slot < MAX_OWNED_VEHICLES; slot++)
	{
		listedVehicleRecord[playerid][slot] = 0;
		listedVehicleModel[playerid][slot] = 0;
	}
	return 1;
}

public LoadPlayerHouse(playerid)
{
	if (PI[playerid][jID] <= 0) return 1;
	new query[128];
	mysql_format(dbz, query, sizeof query,
		"SELECT id FROM player_houses WHERE owner_id=%i LIMIT 1", PI[playerid][jID]);
	mysql_tquery(dbz, query, "OnPlayerHouseLoaded", "ii", playerid, playerSession[playerid]);
	return 1;
}

forward OnPropertyOwnershipLoaded();
public OnPropertyOwnershipLoaded()
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[Properties] Error al cargar propietarios: %s", error);
		return 1;
	}

	new rows;
	cache_get_row_count(rows);
	for (new row = 0; row < rows; row++)
	{
		new houseID, ownerID, bool:isNull;
		cache_get_value_name_int(row, "id", houseID);
		cache_is_value_name_null(row, "owner_id", isNull);
		if (!isNull) cache_get_value_name_int(row, "owner_id", ownerID);
		else ownerID = -1;
		if (houseID >= 1 && houseID <= HOUSE_COUNT) houseOwner[houseID - 1] = ownerID;
	}
	propertyDataReady = true;
	return 1;
}

forward OnPlayerHouseLoaded(playerid, session);
public OnPlayerHouseLoaded(playerid, session)
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[Properties] Error al cargar la casa del jugador: %s", error);
		return 1;
	}
	if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;

	new rows;
	cache_get_row_count(rows);
	playerHouseID[playerid] = -1;
	if (rows > 0) cache_get_value_name_int(0, "id", playerHouseID[playerid]);
	return 1;
}

public CleanupPropertyPlayer(playerid)
{
	playerHouseID[playerid] = -1;
	playerHousePending[playerid] = 0;
	vehiclePurchasePending[playerid] = false;
	vehicleListPending[playerid] = false;
	return 1;
}

public PreparePropertiesDisconnect(playerid)
{
	if (playerHouseID[playerid] > 0
		&& GetPlayerInterior(playerid) == HOUSE_INTERIOR
		&& GetPlayerVirtualWorld(playerid) == playerHouseID[playerid] + 999)
	{
		ExitPlayerHouse(playerid, false);
	}

	for (new vehicleid = 1; vehicleid < MAX_VEHICLES; vehicleid++)
	{
		if (vehicleRecordID[vehicleid] <= 0 || vehicleOwnerDBID[vehicleid] != PI[playerid][jID]) continue;
		new query[128];
		mysql_format(dbz, query, sizeof query,
			"UPDATE player_vehicles SET stored=1 WHERE id=%i AND owner_id=%i AND paid=1",
			vehicleRecordID[vehicleid], PI[playerid][jID]);
		mysql_tquery(dbz, query, "OnVehicleRecoveryComplete");
		DestroyVehicle(vehicleid);
		vehicleRecordID[vehicleid] = 0;
		vehicleOwnerDBID[vehicleid] = 0;
		vehicleStorePending[vehicleid] = false;
	}
	return 1;
}

public StoreAllVehiclesOnShutdown()
{
	mysql_query(dbz, "UPDATE player_vehicles SET stored=1 WHERE paid=1", false);
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[Properties] Error al guardar los vehiculos al cerrar: %s", error);
	}
	return 1;
}

forward OnVehicleRecoveryComplete();
public OnVehicleRecoveryComplete()
{
	if (mysql_errno(dbz) != 0) ReportPropertyQueryError("recuperar vehiculos guardados");
	return 1;
}

stock ShowDealershipMenu(playerid)
{
	new text[192], row[48];
	text[0] = '\0';
	for (new index = 0; index < sizeof VehicleCatalogModel; index++)
	{
		format(row, sizeof row, "%s - $%d\n", VehicleCatalogName[index], VehicleCatalogPrice[index]);
		strcat(text, row, sizeof text);
	}
	return Dialog_Show(playerid, "OnDialogDealership", DIALOG_STYLE_LIST,
		"Concesionario - compra permanente", text, "Comprar", "Cerrar");
}

CMD:concesionario(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!IsPlayerInRangeOfPoint(playerid, 10.0, DEALERSHIP_X, DEALERSHIP_Y, DEALERSHIP_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en el concesionario.");
	}
	return ShowDealershipMenu(playerid);
}

Dialog:OnDialogDealership(playerid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if (!response || !IsAccountLoaded(playerid)) return 1;
	if (!IsPlayerInRangeOfPoint(playerid, 12.0, DEALERSHIP_X, DEALERSHIP_Y, DEALERSHIP_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes permanecer en el concesionario.");
	}
	if (listitem < 0 || listitem >= sizeof VehicleCatalogModel) return 1;
	if (vehiclePurchasePending[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Ya tienes una compra en proceso.");
	if (playerHousePending[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Espera a que termine tu otra transaccion.");
	if (jobOnShift[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Termina tu turno antes de comprar un vehiculo.");
	if (GetPlayerMoney(playerid) < VehicleCatalogPrice[listitem])
	{
		return SendClientMessage(playerid, COLOR_ERROR, "No tienes suficiente efectivo para este vehiculo.");
	}

	vehiclePurchasePending[playerid] = true;
	new query[160];
	mysql_format(dbz, query, sizeof query,
		"SELECT COUNT(*) AS total FROM player_vehicles WHERE owner_id=%i AND paid=1",
		PI[playerid][jID]);
	mysql_tquery(dbz, query, "OnVehicleCountChecked", "iiii",
		playerid, playerSession[playerid], VehicleCatalogModel[listitem], VehicleCatalogPrice[listitem]);
	SendClientMessage(playerid, COLOR_GLOBAL, "Procesando la compra del vehiculo...");
	return 1;
}

forward OnVehicleCountChecked(playerid, session, model, price);
public OnVehicleCountChecked(playerid, session, model, price)
{
	if (mysql_errno(dbz) != 0)
	{
		ReportPropertyQueryError("contar vehiculos");
		ClearVehiclePurchasePending(playerid, session);
		return 1;
	}
	if (!IsPlayerConnected(playerid) || playerSession[playerid] != session)
	{
		return 1;
	}

	new total, rows;
	cache_get_row_count(rows);
	if (rows > 0) cache_get_value_name_int(0, "total", total);
	if (total >= MAX_OWNED_VEHICLES)
	{
		vehiclePurchasePending[playerid] = false;
		SendClientMessage(playerid, COLOR_ERROR, "Ya tienes el maximo de vehiculos permitidos.");
		return 1;
	}
	if (!IsPlayerInRangeOfPoint(playerid, 12.0, DEALERSHIP_X, DEALERSHIP_Y, DEALERSHIP_Z))
	{
		vehiclePurchasePending[playerid] = false;
		SendClientMessage(playerid, COLOR_ERROR, "Debes permanecer en el concesionario.");
		return 1;
	}

	new query[192];
	mysql_format(dbz, query, sizeof query,
		"INSERT INTO player_vehicles (owner_id,model,paid,stored) VALUES (%i,%i,0,1)",
		PI[playerid][jID], model);
	mysql_tquery(dbz, query, "OnVehiclePurchaseInserted", "iiii",
		playerid, session, model, price);
	return 1;
}

forward OnVehiclePurchaseInserted(playerid, session, model, price);
public OnVehiclePurchaseInserted(playerid, session, model, price)
{
	if (mysql_errno(dbz) != 0)
	{
		ReportPropertyQueryError("crear vehiculo");
		ClearVehiclePurchasePending(playerid, session);
		return 1;
	}

	new recordID = cache_insert_id();
	if (recordID <= 0)
	{
		printf("[Properties] Error: la compra no devolvio un ID de vehiculo.");
		ClearVehiclePurchasePending(playerid, session);
		return 1;
	}
	if (!IsPlayerConnected(playerid) || playerSession[playerid] != session)
	{
		DeleteUnpaidVehicle(recordID);
		return 1;
	}

	new query[320];
	mysql_format(dbz, query, sizeof query,
		"UPDATE players AS p INNER JOIN player_vehicles AS v ON v.owner_id=p.id \
		SET p.jCash=p.jCash-%i,v.paid=1 \
		WHERE p.id=%i AND p.jCash>=%i AND v.id=%i AND v.paid=0",
		price, PI[playerid][jID], price, recordID);
	mysql_tquery(dbz, query, "OnVehiclePurchaseCharged", "iiiiii",
		playerid, session, model, price, PI[playerid][jID], recordID);
	return 1;
}

forward OnVehiclePurchaseCharged(playerid, session, model, price, ownerID, recordID);
public OnVehiclePurchaseCharged(playerid, session, model, price, ownerID, recordID)
{
	if (mysql_errno(dbz) != 0)
	{
		ReportPropertyQueryError("cobrar vehiculo");
		DeleteUnpaidVehicle(recordID);
		ClearVehiclePurchasePending(playerid, session);
		return 1;
	}
	if (cache_affected_rows() <= 0)
	{
		DeleteUnpaidVehicle(recordID);
		ClearVehiclePurchasePending(playerid, session);
		if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
		{
			SendClientMessage(playerid, COLOR_ERROR, "La compra fallo: saldo insuficiente o cuenta no disponible.");
		}
		return 1;
	}

	if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
	{
		vehiclePurchasePending[playerid] = false;
		RefreshPlayerCash(playerid, session);
		new message[96];
		format(message, sizeof message, "Compra completada. Vehiculo #%d guardado en tu garage.", recordID);
		SendClientMessage(playerid, COLOR_GLOBAL, message);
	}
	return 1;
}

stock ClearVehiclePurchasePending(playerid, session)
{
	if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
	{
		vehiclePurchasePending[playerid] = false;
	}
	return 1;
}

stock DeleteUnpaidVehicle(recordID)
{
	new query[96];
	mysql_format(dbz, query, sizeof query, "DELETE FROM player_vehicles WHERE id=%i AND paid=0", recordID);
	mysql_tquery(dbz, query, "OnVehicleRecoveryComplete");
	return 1;
}

stock ReportPropertyQueryError(const operation[])
{
	new error[128], message[192];
	mysql_error(error, sizeof error, dbz);
	format(message, sizeof message, "[Properties] Error al %s: %s", operation, error);
	printf("%s", message);
	return 1;
}

CMD:misvehiculos(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!IsPlayerInRangeOfPoint(playerid, 12.0, GARAGE_X, GARAGE_Y, GARAGE_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en el garage para retirar un vehiculo.");
	}
	if (vehicleListPending[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Tu lista de vehiculos ya se esta cargando.");
	vehicleListPending[playerid] = true;
	new query[128];
	mysql_format(dbz, query, sizeof query,
		"SELECT id,model FROM player_vehicles WHERE owner_id=%i AND paid=1 AND stored=1 ORDER BY id LIMIT %i",
		PI[playerid][jID], MAX_OWNED_VEHICLES);
	mysql_tquery(dbz, query, "OnOwnedVehiclesLoaded", "ii", playerid, playerSession[playerid]);
	return 1;
}

forward OnOwnedVehiclesLoaded(playerid, session);
public OnOwnedVehiclesLoaded(playerid, session)
{
	if (mysql_errno(dbz) != 0)
	{
		ReportPropertyQueryError("cargar vehiculos");
		if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
		{
			vehicleListPending[playerid] = false;
			SendClientMessage(playerid, COLOR_ERROR, "No se pudo cargar tu garage.");
		}
		return 1;
	}
	if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;

	new rows, text[256], rowText[48];
	cache_get_row_count(rows);
	listedVehicleCount[playerid] = 0;
	text[0] = '\0';
	for (new row = 0; row < rows && row < MAX_OWNED_VEHICLES; row++)
	{
		new recordID, model;
		cache_get_value_name_int(row, "id", recordID);
		cache_get_value_name_int(row, "model", model);
		listedVehicleRecord[playerid][row] = recordID;
		listedVehicleModel[playerid][row] = model;
		format(rowText, sizeof rowText, "Vehiculo modelo %d - #%d\n", model, recordID);
		strcat(text, rowText, sizeof text);
		listedVehicleCount[playerid]++;
	}
	vehicleListPending[playerid] = false;
	if (!listedVehicleCount[playerid])
	{
		SendClientMessage(playerid, COLOR_GLOBAL, "No tienes vehiculos guardados en el garage.");
		return 1;
	}
	Dialog_Show(playerid, "OnDialogOwnedVehicles", DIALOG_STYLE_LIST,
		"Garage - selecciona un vehiculo", text, "Retirar", "Cerrar");
	return 1;
}

Dialog:OnDialogOwnedVehicles(playerid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if (!response || !IsAccountLoaded(playerid)) return 1;
	if (!IsPlayerInRangeOfPoint(playerid, 12.0, GARAGE_X, GARAGE_Y, GARAGE_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes permanecer en el garage.");
	}
	if (listitem < 0 || listitem >= listedVehicleCount[playerid]) return 1;

	new recordID = listedVehicleRecord[playerid][listitem];
	new model = listedVehicleModel[playerid][listitem];
	new query[160];
	mysql_format(dbz, query, sizeof query,
		"UPDATE player_vehicles SET stored=0 WHERE id=%i AND owner_id=%i AND paid=1 AND stored=1",
		recordID, PI[playerid][jID]);
	mysql_tquery(dbz, query, "OnVehicleWithdrawn", "iiii",
		playerid, playerSession[playerid], recordID, model);
	return 1;
}

forward OnVehicleWithdrawn(playerid, session, recordID, model);
public OnVehicleWithdrawn(playerid, session, recordID, model)
{
	if (mysql_errno(dbz) != 0)
	{
		ReportPropertyQueryError("retirar vehiculo");
		return 1;
	}
	if (cache_affected_rows() != 1)
	{
		if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
		{
			SendClientMessage(playerid, COLOR_ERROR, "No se pudo retirar el vehiculo; revisa que siga guardado en el garage.");
		}
		return 1;
	}
	if (!IsPlayerConnected(playerid) || playerSession[playerid] != session
		|| !IsPlayerInRangeOfPoint(playerid, 12.0, GARAGE_X, GARAGE_Y, GARAGE_Z))
	{
		RestoreStoredVehicle(recordID);
		return 1;
	}

	new Float:spawnX, Float:spawnY;
	if (!FindFreeGarageSpace(spawnX, spawnY))
	{
		RestoreStoredVehicle(recordID);
		SendClientMessage(playerid, COLOR_ERROR, "El garage esta lleno; tu vehiculo sigue guardado.");
		return 1;
	}
	new vehicleid = CreateVehicle(model, spawnX, spawnY, GARAGE_Z, 90.0, -1, -1, -1);
	if (vehicleid == INVALID_VEHICLE_ID || vehicleid <= 0)
	{
		RestoreStoredVehicle(recordID);
		SendClientMessage(playerid, COLOR_ERROR, "No se pudo crear el vehiculo. Sigue guardado en tu garage.");
		return 1;
	}
	vehicleRecordID[vehicleid] = recordID;
	vehicleOwnerDBID[vehicleid] = PI[playerid][jID];
	PutPlayerInVehicle(playerid, vehicleid, 0);
	SendClientMessage(playerid, COLOR_GLOBAL, "Vehiculo retirado del garage. Usa /guardarveh para guardarlo.");
	return 1;
}

stock bool:FindFreeGarageSpace(&Float:x, &Float:y)
{
	for (new space = 0; space < GARAGE_PARKING_SPACES; space++)
	{
		new bool:occupied;
		for (new vehicleid = 1; vehicleid < MAX_VEHICLES; vehicleid++)
		{
			if (GetVehicleModel(vehicleid) == 0) continue;
			new Float:vehicleX, Float:vehicleY, Float:vehicleZ;
			GetVehiclePos(vehicleid, vehicleX, vehicleY, vehicleZ);
			if (GetDistanceBetweenPoints(vehicleX, vehicleY, vehicleZ,
				GarageSpawnX[space], GarageSpawnY[space], GARAGE_Z) < 3.5)
			{
				occupied = true;
				break;
			}
		}
		if (!occupied)
		{
			x = GarageSpawnX[space];
			y = GarageSpawnY[space];
			return true;
		}
	}
	return false;
}

stock Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
	new Float:dx = x1 - x2;
	new Float:dy = y1 - y2;
	new Float:dz = z1 - z2;
	return floatsqroot(dx * dx + dy * dy + dz * dz);
}

stock RestoreStoredVehicle(recordID)
{
	new query[96];
	mysql_format(dbz, query, sizeof query, "UPDATE player_vehicles SET stored=1 WHERE id=%i AND paid=1", recordID);
	mysql_tquery(dbz, query, "OnVehicleRecoveryComplete");
	return 1;
}

CMD:guardarveh(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!IsPlayerInRangeOfPoint(playerid, 12.0, GARAGE_X, GARAGE_Y, GARAGE_Z))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes guardar el vehiculo en el garage.");
	}
	if (!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en tu vehiculo.");

	new vehicleid = GetPlayerVehicleID(playerid);
	if (vehicleRecordID[vehicleid] <= 0 || vehicleOwnerDBID[vehicleid] != PI[playerid][jID])
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Este no es un vehiculo tuyo comprado en el concesionario.");
	}
	if (vehicleStorePending[vehicleid]) return SendClientMessage(playerid, COLOR_ERROR, "El vehiculo ya se esta guardando.");

	vehicleStorePending[vehicleid] = true;
	new query[160];
	mysql_format(dbz, query, sizeof query,
		"UPDATE player_vehicles SET stored=1 WHERE id=%i AND owner_id=%i AND paid=1 AND stored=0",
		vehicleRecordID[vehicleid], PI[playerid][jID]);
	mysql_tquery(dbz, query, "OnVehicleStored", "iiii",
		playerid, playerSession[playerid], vehicleid, vehicleRecordID[vehicleid]);
	return 1;
}

forward OnVehicleStored(playerid, session, vehicleid, recordID);
public OnVehicleStored(playerid, session, vehicleid, recordID)
{
	if (mysql_errno(dbz) != 0)
	{
		ReportPropertyQueryError("guardar vehiculo");
		if (vehicleid > 0 && vehicleid < MAX_VEHICLES) vehicleStorePending[vehicleid] = false;
		return 1;
	}
	if (cache_affected_rows() != 1)
	{
		if (vehicleid > 0 && vehicleid < MAX_VEHICLES) vehicleStorePending[vehicleid] = false;
		if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
		{
			SendClientMessage(playerid, COLOR_ERROR, "No se pudo guardar el vehiculo en la base de datos.");
		}
		return 1;
	}
	if (vehicleid > 0 && vehicleid < MAX_VEHICLES && vehicleRecordID[vehicleid] == recordID)
	{
		if (IsPlayerConnected(playerid) && GetPlayerVehicleID(playerid) == vehicleid) RemovePlayerFromVehicle(playerid);
		DestroyVehicle(vehicleid);
		vehicleRecordID[vehicleid] = 0;
		vehicleOwnerDBID[vehicleid] = 0;
		vehicleStorePending[vehicleid] = false;
	}
	if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
	{
		SendClientMessage(playerid, COLOR_GLOBAL, "Vehiculo guardado en tu garage.");
	}
	return 1;
}

stock FindNearbyHouse(playerid)
{
	for (new house = 0; house < HOUSE_COUNT; house++)
	{
		if (IsPlayerInRangeOfPoint(playerid, 5.0, HouseX[house], HouseY[house], HouseZ[house]))
		{
			return house;
		}
	}
	return -1;
}

CMD:casas(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!propertyDataReady) return SendClientMessage(playerid, COLOR_ERROR, "El sistema de propiedades todavia se esta cargando.");

	SendClientMessage(playerid, COLOR_ADMIN, "=== CASAS DISPONIBLES ===");
	new message[96];
	for (new house = 0; house < HOUSE_COUNT; house++)
	{
		if (houseOwner[house] == -1)
		{
			format(message, sizeof message, "%d. %s - $%d (libre)", house + 1, HouseName[house], HousePrice[house]);
		}
		else
		{
			format(message, sizeof message, "%d. %s - ocupada", house + 1, HouseName[house]);
		}
		SendClientMessage(playerid, COLOR_GLOBAL, message);
	}
	return 1;
}

CMD:comprarcasa(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!propertyDataReady || playerHouseID[playerid] == -2) return SendClientMessage(playerid, COLOR_ERROR, "Las propiedades todavia se estan cargando.");
	if (playerHouseID[playerid] > 0 || playerHousePending[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Ya tienes una casa o una compra pendiente.");
	if (vehiclePurchasePending[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Espera a que termine tu otra transaccion.");
	if (jobOnShift[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Termina tu turno antes de comprar una casa.");

	new houseID;
	if (sscanf(params, "i", houseID)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /comprarcasa <id de /casas>");
	if (houseID < 1 || houseID > HOUSE_COUNT) return SendClientMessage(playerid, COLOR_ERROR, "Ese ID de casa no existe.");
	new house = houseID - 1;
	if (!IsPlayerInRangeOfPoint(playerid, 5.0, HouseX[house], HouseY[house], HouseZ[house]))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes estar frente a la casa que quieres comprar.");
	}
	if (houseOwner[house] != -1) return SendClientMessage(playerid, COLOR_ERROR, "Esa casa ya tiene propietario.");
	if (GetPlayerMoney(playerid) < HousePrice[house]) return SendClientMessage(playerid, COLOR_ERROR, "No tienes suficiente efectivo.");

	playerHousePending[playerid] = houseID;
	new query[320];
	mysql_format(dbz, query, sizeof query,
		"UPDATE players AS p INNER JOIN player_houses AS h ON h.id=%i AND h.owner_id IS NULL \
		SET p.jCash=p.jCash-%i,h.owner_id=p.id WHERE p.id=%i AND p.jCash>=%i",
		houseID, HousePrice[house], PI[playerid][jID], HousePrice[house]);
	mysql_tquery(dbz, query, "OnHousePurchased", "iiii",
		playerid, playerSession[playerid], houseID, PI[playerid][jID]);
	return 1;
}

forward OnHousePurchased(playerid, session, houseID, ownerID);
public OnHousePurchased(playerid, session, houseID, ownerID)
{
	if (mysql_errno(dbz) != 0)
	{
		ReportPropertyQueryError("comprar casa");
		ClearHousePurchasePending(playerid, session);
		return 1;
	}
	if (cache_affected_rows() <= 0)
	{
		ClearHousePurchasePending(playerid, session);
		if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
		{
			SendClientMessage(playerid, COLOR_ERROR, "No se pudo comprar: la casa ya fue ocupada o no tienes saldo suficiente.");
		}
		return 1;
	}

	houseOwner[houseID - 1] = ownerID;
	if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
	{
		playerHouseID[playerid] = houseID;
		playerHousePending[playerid] = 0;
		RefreshPlayerCash(playerid, session);
		SendClientMessage(playerid, COLOR_GLOBAL, "Casa comprada. Usa /entrar frente a ella y /micasa para consultar.");
	}
	return 1;
}

stock ClearHousePurchasePending(playerid, session)
{
	if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
	{
		playerHousePending[playerid] = 0;
	}
	return 1;
}

CMD:micasa(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (playerHouseID[playerid] == -2) return SendClientMessage(playerid, COLOR_ERROR, "Tu propiedad todavia se esta cargando.");
	if (playerHouseID[playerid] < 1 || playerHouseID[playerid] > HOUSE_COUNT) return SendClientMessage(playerid, COLOR_ERROR, "No tienes casa.");
	new house = playerHouseID[playerid] - 1;
	new message[96];
	format(message, sizeof message, "Tu propiedad: %s | Valor de reventa: $%d",
		HouseName[house], HousePrice[house] / 2);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	return 1;
}

CMD:vendercasa(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (playerHouseID[playerid] == -2) return SendClientMessage(playerid, COLOR_ERROR, "Tu propiedad todavia se esta cargando.");
	if (playerHouseID[playerid] < 1 || playerHouseID[playerid] > HOUSE_COUNT) return SendClientMessage(playerid, COLOR_ERROR, "No tienes casa.");
	if (playerHousePending[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Ya tienes una transaccion de propiedad en proceso.");
	if (vehiclePurchasePending[playerid] || jobOnShift[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Termina tu turno y espera a que acaben tus transacciones.");
	if (GetPlayerInterior(playerid) != 0) return SendClientMessage(playerid, COLOR_ERROR, "Debes salir de tu casa antes de venderla.");
	if (GetPlayerMoney(playerid) > ECONOMY_MAX_MONEY - HousePrice[playerHouseID[playerid] - 1] / 2)
	{
		return SendClientMessage(playerid, COLOR_ERROR, "No puedes recibir mas efectivo por el limite de dinero.");
	}

	new query[320], houseID = playerHouseID[playerid];
	mysql_format(dbz, query, sizeof query,
		"UPDATE players AS p INNER JOIN player_houses AS h ON h.id=%i AND h.owner_id=p.id \
		SET p.jCash=p.jCash+%i,h.owner_id=NULL WHERE p.id=%i",
		houseID, HousePrice[houseID - 1] / 2, PI[playerid][jID]);
	playerHousePending[playerid] = -1;
	mysql_tquery(dbz, query, "OnHouseSold", "iii", playerid, playerSession[playerid], houseID);
	return 1;
}

forward OnHouseSold(playerid, session, houseID);
public OnHouseSold(playerid, session, houseID)
{
	if (mysql_errno(dbz) != 0)
	{
		ReportPropertyQueryError("vender casa");
		ClearHousePurchasePending(playerid, session);
		return 1;
	}
	if (cache_affected_rows() <= 0)
	{
		ClearHousePurchasePending(playerid, session);
		return 1;
	}
	houseOwner[houseID - 1] = -1;
	if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;
	playerHousePending[playerid] = 0;
	playerHouseID[playerid] = -1;
	RefreshPlayerCash(playerid, session);
	SendClientMessage(playerid, COLOR_GLOBAL, "Vendiste tu casa por la mitad de su precio original.");
	return 1;
}

CMD:entrar(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!propertyDataReady) return SendClientMessage(playerid, COLOR_ERROR, "El sistema de propiedades todavia se esta cargando.");
	new house = FindNearbyHouse(playerid);
	if (house == -1) return SendClientMessage(playerid, COLOR_ERROR, "No estas frente a una casa.");
	if (houseOwner[house] != PI[playerid][jID]) return SendClientMessage(playerid, COLOR_ERROR, "Solo el propietario puede entrar a esta casa.");

	SetPlayerInterior(playerid, HOUSE_INTERIOR);
	SetPlayerVirtualWorld(playerid, house + 1000);
	SetPlayerPos(playerid, HOUSE_INTERIOR_X, HOUSE_INTERIOR_Y, HOUSE_INTERIOR_Z);
	SendClientMessage(playerid, COLOR_GLOBAL, "Entraste a tu casa. Usa /salir para volver a la calle.");
	return 1;
}

CMD:salir(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (playerHouseID[playerid] < 1 || GetPlayerInterior(playerid) != HOUSE_INTERIOR
		|| GetPlayerVirtualWorld(playerid) != playerHouseID[playerid] + 999)
	{
		return SendClientMessage(playerid, COLOR_ERROR, "No estas dentro de tu casa.");
	}
	return ExitPlayerHouse(playerid, true);
}

stock ExitPlayerHouse(playerid, bool:notify)
{
	new house = playerHouseID[playerid] - 1;
	if (house < 0 || house >= HOUSE_COUNT) return 0;
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerPos(playerid, HouseX[house], HouseY[house], HouseZ[house]);
	if (notify) SendClientMessage(playerid, COLOR_GLOBAL, "Saliste de tu casa.");
	return 1;
}

public HandleHousePickup(playerid, pickupid)
{
	if (!IsAccountLoaded(playerid)) return 1;
	if (!propertyDataReady)
	{
		SendClientMessage(playerid, COLOR_ERROR, "El sistema de propiedades todavia se esta cargando.");
		return 1;
	}
	for (new house = 0; house < HOUSE_COUNT; house++)
	{
		if (housePickup[house] == -1 || housePickup[house] != pickupid) continue;
		new message[96];
		if (houseOwner[house] == -1)
		{
			format(message, sizeof message, "%s libre por $%d. Usa /comprarcasa %d para comprarla.",
				HouseName[house], HousePrice[house], house + 1);
		}
		else if (houseOwner[house] == PI[playerid][jID])
		{
			format(message, sizeof message, "%s: usa /entrar para acceder a tu propiedad.", HouseName[house]);
		}
		else
		{
			format(message, sizeof message, "%s ya tiene propietario.", HouseName[house]);
		}
		SendClientMessage(playerid, COLOR_GLOBAL, message);
		return 1;
	}
	return 1;
}
