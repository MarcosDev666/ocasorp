#include <YSI_Coding\y_hooks>

#define INVENTORY_SLOTS 10
#define INVENTORY_STACK_LIMIT 20

#define ITEM_WATER 1
#define ITEM_FOOD 2
#define ITEM_MEDKIT 3
#define ITEM_REPAIR_KIT 4
#define ITEM_ARMOUR_VEST 5
#define ITEM_BANDAGE 6
#define ITEM_ENERGY_DRINK 7
#define ITEM_CIGARETTE 8

#define STORE_COUNT 12

new smokingAnimLibrary[] = "SMOKING";
new smokingAnimName[] = "M_smk_in";

new StoreName[STORE_COUNT][32] =
{
	"24/7 Centro",
	"24/7 Idlewood",
	"24/7 Willowfield",
	"24/7 Ganton",
	"24/7 Market",
	"24/7 Temple",
	"24/7 Downtown",
	"24/7 Jefferson",
	"24/7 Ocean Docks",
	"24/7 Santa Maria",
	"24/7 Dillimore",
	"24/7 Palomino Creek"
};
new Float:StoreX[STORE_COUNT] =
{
	1721.0, 1928.0, 2448.0, 2424.0, 1111.0, 1039.0, 1315.0, 2196.0,
	2750.0, 496.0, 663.0, 2330.0
};
new Float:StoreY[STORE_COUNT] =
{
	-1877.5, -1776.0, -2038.0, -1741.0, -923.0, -1334.0, -897.0, -1165.0,
	-2400.0, -1750.0, -573.0, 88.0
};
new Float:StoreZ[STORE_COUNT] =
{
	13.5, 13.5, 13.5, 13.5, 43.4, 13.7, 39.5, 25.7,
	13.5, 14.8, 16.3, 23.0
};
new storePickups[STORE_COUNT];

new inventoryItems[MAX_PLAYERS][INVENTORY_SLOTS];
new inventoryAmounts[MAX_PLAYERS][INVENTORY_SLOTS];
new bool:inventoryReady[MAX_PLAYERS];

forward InitializeInventoryPlayer(playerid);
forward CleanupInventoryPlayer(playerid);
forward InitializeStores();

public InitializeStores()
{
	for (new store = 0; store < STORE_COUNT; store++)
	{
		storePickups[store] = CreatePickup(1274, 1, StoreX[store], StoreY[store], StoreZ[store], 0);
		if (storePickups[store] == -1)
		{
			printf("[Stores] Error: no se pudo crear el pickup de %s.", StoreName[store]);
		}
	}
	return 1;
}

stock bool:IsPlayerNearStore(playerid)
{
	for (new store = 0; store < STORE_COUNT; store++)
	{
		if (IsPlayerInRangeOfPoint(playerid, 8.0, StoreX[store], StoreY[store], StoreZ[store]))
		{
			return true;
		}
	}
	return false;
}

stock Show24StoreMenu(playerid)
{
	return Dialog_Show(playerid, "OnDialog24Store", DIALOG_STYLE_LIST,
		"Tiendas 24/7 | articulos",
		"Agua - $50\nComida - $75\nBotiquin - $250\nKit mecanico - $500\nChaleco - $850\nVenda - $120\nBebida energetica - $90\nCigarrillo - $60",
		"Comprar", "Cerrar");
}

stock GetInventoryItemName(itemid, name[], size)
{
	switch (itemid)
	{
		case ITEM_WATER: format(name, size, "Agua");
		case ITEM_FOOD: format(name, size, "Comida");
		case ITEM_MEDKIT: format(name, size, "Botiquin");
		case ITEM_REPAIR_KIT: format(name, size, "Kit mecanico");
		case ITEM_ARMOUR_VEST: format(name, size, "Chaleco antibalas");
		case ITEM_BANDAGE: format(name, size, "Venda");
		case ITEM_ENERGY_DRINK: format(name, size, "Bebida energetica");
		case ITEM_CIGARETTE: format(name, size, "Cigarrillo");
		default: format(name, size, "Desconocido");
	}
	return 1;
}

public InitializeInventoryPlayer(playerid)
{
	inventoryReady[playerid] = false;
	for (new slot = 0; slot < INVENTORY_SLOTS; slot++)
	{
		inventoryItems[playerid][slot] = 0;
		inventoryAmounts[playerid][slot] = 0;
	}
	return 1;
}

public CleanupInventoryPlayer(playerid)
{
	return InitializeInventoryPlayer(playerid);
}

public LoadPlayerInventory(playerid)
{
	if (PI[playerid][jID] <= 0) return 1;
	new query[128];
	mysql_format(dbz, query, sizeof query,
		"SELECT slot,item_id,amount FROM player_inventory WHERE player_id=%i AND amount>0",
		PI[playerid][jID]);
	mysql_tquery(dbz, query, "OnInventoryLoaded", "ii", playerid, playerSession[playerid]);
	return 1;
}

forward OnInventoryLoaded(playerid, session);
public OnInventoryLoaded(playerid, session)
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[Inventory] Error al cargar inventario: %s", error);
		if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
		{
			SendClientMessage(playerid, COLOR_ERROR, "No se pudo cargar tu inventario. Reinicia sesion o avisa al staff.");
		}
		return 1;
	}
	if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;

	InitializeInventoryPlayer(playerid);
	new rows;
	cache_get_row_count(rows);
	for (new row = 0; row < rows; row++)
	{
		new slot, itemid, amount;
		cache_get_value_name_int(row, "slot", slot);
		cache_get_value_name_int(row, "item_id", itemid);
		cache_get_value_name_int(row, "amount", amount);
		if (slot < 0 || slot >= INVENTORY_SLOTS || itemid < ITEM_WATER || itemid > ITEM_CIGARETTE) continue;
		if (amount < 1 || amount > INVENTORY_STACK_LIMIT) continue;
		inventoryItems[playerid][slot] = itemid;
		inventoryAmounts[playerid][slot] = amount;
	}
	inventoryReady[playerid] = true;
	return 1;
}

public SaveInventoryData(playerid)
{
	return SaveInventoryDataInternal(playerid, false);
}

forward SaveInventoryDataSync(playerid);
public SaveInventoryDataSync(playerid)
{
	return SaveInventoryDataInternal(playerid, true);
}

stock SaveInventoryDataInternal(playerid, bool:sync)
{
	if (PI[playerid][jID] <= 0 || !inventoryReady[playerid]) return 1;

	new query[1200], rowQuery[64];
	format(query, sizeof query,
		"INSERT INTO player_inventory (player_id,slot,item_id,amount) VALUES ");
	for (new slot = 0; slot < INVENTORY_SLOTS; slot++)
	{
		if (slot > 0) strcat(query, ",", sizeof query);
		format(rowQuery, sizeof rowQuery, "(%d,%d,%d,%d)",
			PI[playerid][jID], slot,
			inventoryItems[playerid][slot], inventoryAmounts[playerid][slot]);
		strcat(query, rowQuery, sizeof query);
	}
	strcat(query,
		" ON DUPLICATE KEY UPDATE item_id=VALUES(item_id),amount=VALUES(amount)",
		sizeof query);
	if (sync)
	{
		mysql_query(dbz, query, false);
		if (mysql_errno(dbz) != 0)
		{
			new error[128];
			mysql_error(error, sizeof error, dbz);
			printf("[Inventory] Error al guardar durante el cierre: %s", error);
		}
	}
	else
	{
		mysql_tquery(dbz, query, "OnInventorySaved");
	}
	return 1;
}

forward OnInventorySaved();
public OnInventorySaved()
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[Inventory] Error al guardar inventario: %s", error);
	}
	return 1;
}

hook OnPlayerPickUpPickup(playerid, pickupid)
{
	if (!IsAccountLoaded(playerid)) return 1;
	for (new store = 0; store < STORE_COUNT; store++)
	{
		if (storePickups[store] == -1) continue;
		if (storePickups[store] == pickupid)
		{
			if (!inventoryReady[playerid])
			{
				SendClientMessage(playerid, COLOR_ERROR, "Tu inventario todavia se esta cargando; intenta de nuevo en unos segundos.");
				return 1;
			}
			new message[64];
			format(message, sizeof message, "Llegaste a %s. Usa /tienda para comprar.", StoreName[store]);
			SendClientMessage(playerid, COLOR_GLOBAL, message);
			Show24StoreMenu(playerid);
			return 1;
		}
	}
	HandleHousePickup(playerid, pickupid);
	return 1;
}

CMD:tienda(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!inventoryReady[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Tu inventario todavia se esta cargando.");
	if (!IsPlayerNearStore(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en una tienda 24/7.");
	return Show24StoreMenu(playerid);
}

stock bool:AddInventoryItem(playerid, itemid, amount)
{
	new oldItems[INVENTORY_SLOTS], oldAmounts[INVENTORY_SLOTS];
	for (new slot = 0; slot < INVENTORY_SLOTS; slot++)
	{
		oldItems[slot] = inventoryItems[playerid][slot];
		oldAmounts[slot] = inventoryAmounts[playerid][slot];
	}

	new remaining = amount;
	for (new slot = 0; slot < INVENTORY_SLOTS && remaining > 0; slot++)
	{
		if (inventoryItems[playerid][slot] != itemid) continue;
		new freeSpace = INVENTORY_STACK_LIMIT - inventoryAmounts[playerid][slot];
		if (freeSpace <= 0) continue;
		new added = (remaining < freeSpace) ? remaining : freeSpace;
		inventoryAmounts[playerid][slot] += added;
		remaining -= added;
	}

	for (new slot = 0; slot < INVENTORY_SLOTS && remaining > 0; slot++)
	{
		if (inventoryItems[playerid][slot] != 0) continue;
		new added = (remaining < INVENTORY_STACK_LIMIT) ? remaining : INVENTORY_STACK_LIMIT;
		inventoryItems[playerid][slot] = itemid;
		inventoryAmounts[playerid][slot] = added;
		remaining -= added;
	}

	if (remaining > 0)
	{
		for (new slot = 0; slot < INVENTORY_SLOTS; slot++)
		{
			inventoryItems[playerid][slot] = oldItems[slot];
			inventoryAmounts[playerid][slot] = oldAmounts[slot];
		}
		return false;
	}
	return true;
}

stock bool:RemoveInventoryItem(playerid, slot, amount)
{
	if (slot < 0 || slot >= INVENTORY_SLOTS || amount < 1
		|| inventoryAmounts[playerid][slot] < amount)
	{
		return false;
	}
	inventoryAmounts[playerid][slot] -= amount;
	if (inventoryAmounts[playerid][slot] == 0)
	{
		inventoryItems[playerid][slot] = 0;
	}
	return true;
}

CMD:inventario(playerid, params[])
{
	#pragma unused params
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!inventoryReady[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Tu inventario todavia se esta cargando.");
	SendClientMessage(playerid, COLOR_ADMIN, "=== INVENTARIO (10 espacios, maximo 20 por espacio) ===");

	new found, name[32], message[64];
	for (new slot = 0; slot < INVENTORY_SLOTS; slot++)
	{
		if (inventoryAmounts[playerid][slot] <= 0) continue;
		GetInventoryItemName(inventoryItems[playerid][slot], name, sizeof name);
		format(message, sizeof message, "%d. %s x%d", slot + 1, name, inventoryAmounts[playerid][slot]);
		SendClientMessage(playerid, COLOR_GLOBAL, message);
		found++;
	}
	if (!found) SendClientMessage(playerid, COLOR_GLOBAL, "Tu inventario esta vacio.");
	return 1;
}

CMD:comprar(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!inventoryReady[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Tu inventario todavia se esta cargando.");
	if (!IsPlayerNearStore(playerid))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en una tienda 24/7.");
	}

	new itemName[16], amount;
	if (sscanf(params, "s[16]i", itemName, amount))
	{
		return SendClientMessage(playerid, COLOR_USAGE, "Uso: /comprar <agua|comida|botiquin|kit|chaleco|venda|energetica|cigarro> <cantidad 1-20>");
	}
	if (amount < 1 || amount > INVENTORY_STACK_LIMIT)
	{
		return SendClientMessage(playerid, COLOR_ERROR, "La cantidad debe estar entre 1 y 20.");
	}

	new itemid, price;
	if (!strcmp(itemName, "agua", true)) { itemid = ITEM_WATER; price = 50; }
	else if (!strcmp(itemName, "comida", true)) { itemid = ITEM_FOOD; price = 75; }
	else if (!strcmp(itemName, "botiquin", true)) { itemid = ITEM_MEDKIT; price = 250; }
	else if (!strcmp(itemName, "kit", true)) { itemid = ITEM_REPAIR_KIT; price = 500; }
	else if (!strcmp(itemName, "chaleco", true)) { itemid = ITEM_ARMOUR_VEST; price = 850; }
	else if (!strcmp(itemName, "venda", true)) { itemid = ITEM_BANDAGE; price = 120; }
	else if (!strcmp(itemName, "energetica", true)) { itemid = ITEM_ENERGY_DRINK; price = 90; }
	else if (!strcmp(itemName, "cigarro", true)) { itemid = ITEM_CIGARETTE; price = 60; }
	else return SendClientMessage(playerid, COLOR_USAGE, "Articulos: agua, comida, botiquin, kit, chaleco, venda, energetica, cigarro.");

	return PurchaseStoreItem(playerid, itemid, amount, price);
}

stock PurchaseStoreItem(playerid, itemid, amount, price)
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (IsWalletTransactionPending(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Espera a que termine tu otra transaccion.");
	if (!inventoryReady[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Tu inventario todavia se esta cargando.");
	if (!IsPlayerNearStore(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Debes estar en una tienda 24/7.");
	if (amount < 1 || amount > INVENTORY_STACK_LIMIT)
	{
		return SendClientMessage(playerid, COLOR_ERROR, "La cantidad debe estar entre 1 y 20.");
	}

	new total = price * amount;
	if (GetPlayerMoney(playerid) < total)
	{
		return SendClientMessage(playerid, COLOR_ERROR, "No tienes suficiente dinero.");
	}
	if (!AddInventoryItem(playerid, itemid, amount))
	{
		return SendClientMessage(playerid, COLOR_ERROR, "No tienes espacio suficiente en el inventario.");
	}

	GivePlayerMoney(playerid, -total);
	PI[playerid][jCash] = GetPlayerMoney(playerid);
	SaveData(playerid);
	new message[80];
	format(message, sizeof message, "Compra realizada: %d articulo(s), total $%d.", amount, total);
	SendClientMessage(playerid, COLOR_GLOBAL, message);
	return 1;
}

Dialog:OnDialog24Store(playerid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if (!response || !IsAccountLoaded(playerid)) return 1;
	new itemid, price;
	switch (listitem)
	{
		case 0: { itemid = ITEM_WATER; price = 50; }
		case 1: { itemid = ITEM_FOOD; price = 75; }
		case 2: { itemid = ITEM_MEDKIT; price = 250; }
		case 3: { itemid = ITEM_REPAIR_KIT; price = 500; }
		case 4: { itemid = ITEM_ARMOUR_VEST; price = 850; }
		case 5: { itemid = ITEM_BANDAGE; price = 120; }
		case 6: { itemid = ITEM_ENERGY_DRINK; price = 90; }
		case 7: { itemid = ITEM_CIGARETTE; price = 60; }
		default: return 1;
	}
	return PurchaseStoreItem(playerid, itemid, 1, price);
}

CMD:usar(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!inventoryReady[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Tu inventario todavia se esta cargando.");
	new slot;
	if (sscanf(params, "i", slot)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /usar <espacio 1-10>");
	if (slot < 1 || slot > INVENTORY_SLOTS) return SendClientMessage(playerid, COLOR_ERROR, "Ese espacio no existe.");
	slot--;

	new itemid = inventoryItems[playerid][slot];
	if (inventoryAmounts[playerid][slot] <= 0) return SendClientMessage(playerid, COLOR_ERROR, "Ese espacio esta vacio.");

	switch (itemid)
	{
		case ITEM_WATER:
		{
			PI[playerid][jThirst] += 30;
			if (PI[playerid][jThirst] > 100) PI[playerid][jThirst] = 100;
		}
		case ITEM_FOOD:
		{
			PI[playerid][jHunger] += 30;
			if (PI[playerid][jHunger] > 100) PI[playerid][jHunger] = 100;
		}
		case ITEM_MEDKIT:
		{
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 35.0;
			if (health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			PI[playerid][jHealth] = health;
		}
		case ITEM_REPAIR_KIT:
		{
			if (PI[playerid][jFaction] != FACTION_MECHANIC || PI[playerid][jFactionRank] < 2)
			{
				return SendClientMessage(playerid, COLOR_ERROR, "Solo un mecanico de rango 2 o superior puede usar el kit.");
			}
			if (!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Debes estar dentro del vehiculo que quieres reparar.");
			RepairVehicle(GetPlayerVehicleID(playerid));
		}
		case ITEM_ARMOUR_VEST:
		{
			new Float:armour;
			GetPlayerArmour(playerid, armour);
			if (armour >= 100.0) return SendClientMessage(playerid, COLOR_ERROR, "Ya tienes la armadura al maximo.");
			armour += 50.0;
			if (armour > 100.0) armour = 100.0;
			SetPlayerArmour(playerid, armour);
			PI[playerid][jArmour] = armour;
		}
		case ITEM_BANDAGE:
		{
			new Float:health;
			GetPlayerHealth(playerid, health);
			if (health >= 100.0) return SendClientMessage(playerid, COLOR_ERROR, "No necesitas una venda ahora.");
			health += 15.0;
			if (health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			PI[playerid][jHealth] = health;
		}
		case ITEM_ENERGY_DRINK:
		{
			PI[playerid][jThirst] += 20;
			PI[playerid][jHunger] += 5;
			if (PI[playerid][jThirst] > 100) PI[playerid][jThirst] = 100;
			if (PI[playerid][jHunger] > 100) PI[playerid][jHunger] = 100;
		}
		case ITEM_CIGARETTE:
		{
			ApplyAnimation(playerid, smokingAnimLibrary, smokingAnimName, 4.1, 0, 0, 0, 0, 0);
		}
		default: return SendClientMessage(playerid, COLOR_ERROR, "Ese objeto no se puede usar.");
	}

	RemoveInventoryItem(playerid, slot, 1);
	SaveData(playerid);
	SendClientMessage(playerid, COLOR_GLOBAL, "Usaste el objeto del inventario.");
	return 1;
}

CMD:tirar(playerid, params[])
{
	if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
	if (!inventoryReady[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Tu inventario todavia se esta cargando.");
	new slot;
	if (sscanf(params, "i", slot)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /tirar <espacio 1-10>");
	if (slot < 1 || slot > INVENTORY_SLOTS) return SendClientMessage(playerid, COLOR_ERROR, "Ese espacio no existe.");
	slot--;
	if (!RemoveInventoryItem(playerid, slot, 1)) return SendClientMessage(playerid, COLOR_ERROR, "Ese espacio esta vacio.");
	SaveInventoryData(playerid);
	SendClientMessage(playerid, COLOR_GLOBAL, "Eliminaste un objeto del inventario.");
	return 1;
}
