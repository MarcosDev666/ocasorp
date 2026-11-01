// Chat commands: duda and twitter

CMD:duda(playerid, params[])
{
    // Cooldown de 10 minutos
    if (!CanUseCooldown(playerid, 30)) return 1;

	if(!strlen(params)) {
		new usage[64];
		format(usage, sizeof usage, "Uso: /duda <mensaje>");
		SendClientMessage(playerid, COLOR_USAGE, usage);
		return 0;
	}

	new name[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, name, sizeof name);

	new msg[256+1];
	format(msg, sizeof msg, "[{E0FFFF}duda{EEEEEE}] %s: %s", name, params);
	SendClientMessageToAll(COLOR_DUDA, msg);
	return 1;
}

CMD:twitter(playerid, params[])
{
	// Cooldown de 5 minutos 
	if (!CanUseCooldown(playerid, 10)) return 1;

	if(!strlen(params)) {
		new usage[64];
		format(usage, sizeof usage, "Uso: /twitter <mensaje>");
		SendClientMessage(playerid, COLOR_USAGE, usage);
		return 0;
	}

	new name[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, name, sizeof name);

	new msg[256+1];
	format(msg, sizeof msg, "[{00ACEE}twitter{EEEEEE}] @%s: %s", name, params);
	SendClientMessageToAll(COLOR_TWITTER, msg);
	return 1;
}

// Comando /me - acci?n (roleplay)
CMD:me(playerid, params[])
{
	if(!strlen(params)) {
		new usage[64];
		format(usage, sizeof usage, "Uso: /me <acci?n>");
		SendClientMessage(playerid, COLOR_USAGE, usage);
		return 0;
	}

	new name[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, name, sizeof name);
	new msg[256+1];
	format(msg, sizeof msg, "%s %s", name, params);
	SendLocalMessage(playerid, msg);
	return 1;
}

// Comando /do - descripci?n (roleplay)
CMD:do(playerid, params[])
{
	if(!strlen(params)) {
		new usage[64];
		format(usage, sizeof usage, "Uso: /do <descripci?n>");
		SendClientMessage(playerid, COLOR_USAGE, usage);
		return 0;
	}

	new msg[256+1];
	format(msg, sizeof msg, "[ACCI?N] %s", params);
	SendLocalMessage(playerid, msg);
	return 1;
}

// Comando /gritar - hablar en volumen alto
CMD:gritar(playerid, params[])
{
	if(!strlen(params)) {
		new usage[64];
		format(usage, sizeof usage, "Uso: /gritar <mensaje>");
		SendClientMessage(playerid, COLOR_USAGE, usage);
		return 0;
	}

	new name[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, name, sizeof name);
	new msg[256+1];
	format(msg, sizeof msg, "%s GRITA: %s", name, params);
	SendClientMessageToAll(0xFF6347FF, msg); // Rojo-naranja
	return 1;
}

// Comando /susurrar - hablar en volumen bajo
CMD:susurrar(playerid, params[])
{
	if(!strlen(params)) {
		new usage[64];
		format(usage, sizeof usage, "Uso: /susurrar <mensaje>");
		SendClientMessage(playerid, COLOR_USAGE, usage);
		return 0;
	}

	new name[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, name, sizeof name);
	new msg[256+1];
	format(msg, sizeof msg, "%s susurra: %s", name, params);
	SendLocalMessage(playerid, msg);
	return 1;
}

// Comando /llorar - expresi?n emocional
CMD:llorar(playerid, params[])
{
	new name[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, name, sizeof name);
	new msg[128];
	format(msg, sizeof msg, "%s est? llorando... :(", name);
	SendLocalMessage(playerid, msg);
	return 1;
}

// Comando /reir - expresi?n emocional
CMD:reir(playerid, params[])
{
	new name[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, name, sizeof name);
	new msg[128];
	format(msg, sizeof msg, "%s se r?e a carcajadas... XD", name);
	SendLocalMessage(playerid, msg);
	return 1;
}

// Comando /ayuda - mostrar comandos disponibles
CMD:ayuda(playerid, params[])
{
	SendClientMessage(playerid, COLOR_ADMIN, "=== COMANDOS DISPONIBLES ===");
	SendClientMessage(playerid, COLOR_GLOBAL, "/me <acci?n> - Realizar una acci?n");
	SendClientMessage(playerid, COLOR_GLOBAL, "/do <descripci?n> - Describir algo");
	SendClientMessage(playerid, COLOR_GLOBAL, "/gritar <mensaje> - Hablar en volumen alto");
	SendClientMessage(playerid, COLOR_GLOBAL, "/susurrar <mensaje> - Hablar en volumen bajo");
	SendClientMessage(playerid, COLOR_GLOBAL, "/llorar - Llorar");
	SendClientMessage(playerid, COLOR_GLOBAL, "/reir - Re?r");
	SendClientMessage(playerid, COLOR_GLOBAL, "/duda <mensaje> - Enviar una duda global");
	SendClientMessage(playerid, COLOR_GLOBAL, "/twitter <mensaje> - Tweet global");
	SendClientMessage(playerid, COLOR_GLOBAL, "/rentar - Rentar un vehiculo en el checkpoint");
	SendClientMessage(playerid, COLOR_GLOBAL, "/devolverveh - Devolver el vehiculo en la agencia");
	SendClientMessage(playerid, COLOR_GLOBAL, "/gps - Marcar destino o un punto elegido en el mapa");
	SendClientMessage(playerid, COLOR_GLOBAL, "/quitarGPS /borrarblip - Cancelar la ruta GPS");
	SendClientMessage(playerid, COLOR_GLOBAL, "/tienda - Abrir una tienda 24/7 cercana");
	SendClientMessage(playerid, COLOR_GLOBAL, "/banco /depositar /retirar /transferir - Gestion bancaria");
	SendClientMessage(playerid, COLOR_GLOBAL, "/concesionario /misvehiculos /guardarveh - Vehiculos y garage");
	SendClientMessage(playerid, COLOR_GLOBAL, "/casas /comprarcasa /micasa /vendercasa /entrar /salir - Propiedades");
	SendClientMessage(playerid, COLOR_GLOBAL, "/admins - Ver administradores conectados");
	SendClientMessage(playerid, COLOR_GLOBAL, "/ayudaadmin - Comandos segun tu nivel de administrador");
	SendClientMessage(playerid, COLOR_GLOBAL, "/ayudagame - Ayuda de trabajos, facciones e inventario");
	SendClientMessage(playerid, COLOR_GLOBAL, "/empleos /turno /miempleo - Sistema de trabajos");
	SendClientMessage(playerid, COLOR_GLOBAL, "/faccion /facciones /f <mensaje> - Sistema de facciones");
	SendClientMessage(playerid, COLOR_GLOBAL, "/miembrosfaccion /promover /degradar /uniforme - Gestion de faccion");
	SendClientMessage(playerid, COLOR_GLOBAL, "/curarfac (EMS) /reparar (mecanico) /multar (policia)");
	SendClientMessage(playerid, COLOR_GLOBAL, "/inventario /usar <slot> /comprar <articulo> <cantidad> (en tiendas 24/7)");
	SendClientMessage(playerid, COLOR_GLOBAL, "/dinero - Ver tu dinero");
	SendClientMessage(playerid, COLOR_GLOBAL, "/ping - Ver tu ping");
	return 1;
}

// Comando /ping - ver latencia
CMD:ping(playerid, params[])
{
	new ping = GetPlayerPing(playerid);
	new msg[64];
	format(msg, sizeof msg, "Tu ping es: %i ms", ping);
	SendClientMessage(playerid, COLOR_GLOBAL, msg);
	return 1;
}

// Comando /dinero - ver dinero del jugador
CMD:dinero(playerid, params[])
{
	new cash = GetPlayerMoney(playerid);
	new msg[64];
	format(msg, sizeof msg, "Dinero: $%i", cash);
	SendClientMessage(playerid, COLOR_GLOBAL, msg);
	return 1;
}
