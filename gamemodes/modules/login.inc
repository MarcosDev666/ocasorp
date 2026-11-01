/*
    OcasoRP - 2026
    Login
*/

   
new Text:Login[21];

LoadTextdraws()
{
		Login[0] = TextDrawCreate(110.000000, 5.226665, "loadsc8:loadsc8");
		TextDrawLetterSize(Login[0], 0.000000, 0.000000);
		TextDrawTextSize(Login[0], 532.500000, 357.653778);
		TextDrawAlignment(Login[0], 1);
		TextDrawColor(Login[0], -1);
		TextDrawSetShadow(Login[0], 0);
		TextDrawSetOutline(Login[0], 0);
		TextDrawFont(Login[0], 4);
		Login[1] = TextDrawCreate(0.000000, 0.000000, "LD_SPAC:white");
		TextDrawLetterSize(Login[1], 0.000000, 0.000000);
		TextDrawTextSize(Login[1], 301.250000, 448.000000);
		TextDrawAlignment(Login[1], 1);
		TextDrawColor(Login[1], 255);
		TextDrawSetShadow(Login[1], 0);
		TextDrawSetOutline(Login[1], 0);
		TextDrawFont(Login[1], 4);
		Login[2] = TextDrawCreate(294.375000, -7.466688, "LD_SPAC:white");
		TextDrawLetterSize(Login[2], 0.000000, -1.562500);
		TextDrawTextSize(Login[2], 56.250000, 82.879951);
		TextDrawAlignment(Login[2], 1);
		TextDrawColor(Login[2], 255);
		TextDrawUseBox(Login[2], true);
		TextDrawBoxColor(Login[2], 0);
		TextDrawSetShadow(Login[2], 0);
		TextDrawSetOutline(Login[2], 0);
		TextDrawFont(Login[2], 4);
		Login[3] = TextDrawCreate(265.625000, 321.066741, "LD_SPAC:white");
		TextDrawLetterSize(Login[3], 0.000000, 0.000000);
		TextDrawTextSize(Login[3], 115.000000, 129.920013);
		TextDrawAlignment(Login[3], 1);
		TextDrawColor(Login[3], 255);
		TextDrawUseBox(Login[3], true);
		TextDrawBoxColor(Login[3], 0);
		TextDrawSetShadow(Login[3], 0);
		TextDrawSetOutline(Login[3], 0);
		TextDrawFont(Login[3], 4);
		TextDrawSetPreviewModel(Login[3], 0);
		TextDrawSetPreviewRot(Login[3], 0.000000, 0.000000, 0.000000, 0.000000);
		Login[4] = TextDrawCreate(348.750000, 1.493332, "LD_SPAC:white");
		TextDrawLetterSize(Login[4], 0.000000, 1.875000);
		TextDrawTextSize(Login[4], 8.750000, 450.240020);
		TextDrawAlignment(Login[4], 1);
		TextDrawColor(Login[4], 255);
		TextDrawUseBox(Login[4], true);
		TextDrawBoxColor(Login[4], 0);
		TextDrawSetShadow(Login[4], 0);
		TextDrawSetOutline(Login[4], 0);
		TextDrawFont(Login[4], 4);
		TextDrawSetPreviewModel(Login[4], 0);
		TextDrawSetPreviewRot(Login[4], 0.000000, 0.000000, 0.000000, 0.000000);
		Login[5] = TextDrawCreate(333.125000, -2.240000, "LD_SPAC:white");
		TextDrawLetterSize(Login[5], 0.000000, 0.000000);
		TextDrawTextSize(Login[5], 81.250000, 52.266674);
		TextDrawAlignment(Login[5], 1);
		TextDrawColor(Login[5], 255);
		TextDrawUseBox(Login[5], true);
		TextDrawBoxColor(Login[5], 0);
		TextDrawSetShadow(Login[5], 0);
		TextDrawSetOutline(Login[5], 0);
		TextDrawFont(Login[5], 4);
		Login[6] = TextDrawCreate(357.500000, 271.787200, "LD_SPAC:white");
		TextDrawLetterSize(Login[6], 0.000000, 6.562500);
		TextDrawTextSize(Login[6], 53.125000, 181.440002);
		TextDrawAlignment(Login[6], 1);
		TextDrawColor(Login[6], 255);
		TextDrawUseBox(Login[6], true);
		TextDrawBoxColor(Login[6], 0);
		TextDrawSetShadow(Login[6], 0);
		TextDrawSetOutline(Login[6], 0);
		TextDrawFont(Login[6], 4);
		Login[7] = TextDrawCreate(408.125000, -1.493332, "LD_SPAC:white");
		TextDrawLetterSize(Login[7], 0.000000, 0.000000);
		TextDrawTextSize(Login[7], 7.500000, 447.253326);
		TextDrawAlignment(Login[7], 1);
		TextDrawColor(Login[7], 255);
		TextDrawUseBox(Login[7], true);
		TextDrawBoxColor(Login[7], 0);
		TextDrawSetShadow(Login[7], 0);
		TextDrawSetOutline(Login[7], 0);
		TextDrawFont(Login[7], 4);
		Login[8] = TextDrawCreate(413.750000, -11.199995, "LD_SPAC:white");
		TextDrawLetterSize(Login[8], 0.000000, 0.000000);
		TextDrawTextSize(Login[8], 63.750000, 17.173357);
		TextDrawAlignment(Login[8], 1);
		TextDrawColor(Login[8], 255);
		TextDrawUseBox(Login[8], true);
		TextDrawBoxColor(Login[8], 0);
		TextDrawSetShadow(Login[8], 0);
		TextDrawSetOutline(Login[8], 0);
		TextDrawFont(Login[8], 4);
		Login[9] = TextDrawCreate(410.625000, 327.040008, "LD_SPAC:white");
		TextDrawLetterSize(Login[9], 0.000000, 0.000000);
		TextDrawTextSize(Login[9], 65.000000, 121.706665);
		TextDrawAlignment(Login[9], 1);
		TextDrawColor(Login[9], 255);
		TextDrawUseBox(Login[9], true);
		TextDrawBoxColor(Login[9], 0);
		TextDrawSetShadow(Login[9], 0);
		TextDrawSetOutline(Login[9], 0);
		TextDrawFont(Login[9], 4);
		Login[10] = TextDrawCreate(480.000000, 0.746666, "LD_SPAC:white");
		TextDrawLetterSize(Login[10], 0.000000, 0.000000);
		TextDrawTextSize(Login[10], -6.875000, 448.000000);
		TextDrawAlignment(Login[10], 1);
		TextDrawColor(Login[10], 255);
		TextDrawUseBox(Login[10], true);
		TextDrawBoxColor(Login[10], 0);
		TextDrawSetShadow(Login[10], 0);
		TextDrawSetOutline(Login[10], 0);
		TextDrawFont(Login[10], 4);
		Login[11] = TextDrawCreate(477.500000, -114.986633, "LD_SPAC:white");
		TextDrawLetterSize(Login[11], 0.000000, 0.000000);
		TextDrawTextSize(Login[11], 64.375000, 224.000000);
		TextDrawAlignment(Login[11], 1);
		TextDrawColor(Login[11], 255);
		TextDrawUseBox(Login[11], true);
		TextDrawBoxColor(Login[11], 0);
		TextDrawSetShadow(Login[11], 0);
		TextDrawSetOutline(Login[11], 0);
		TextDrawFont(Login[11], 4);
		TextDrawSetPreviewModel(Login[11], 0);
		TextDrawSetPreviewRot(Login[11], 0.000000, 0.000000, 0.000000, 0.000000);
		Login[12] = TextDrawCreate(479.375000, 360.640075, "LD_SPAC:white");
		TextDrawLetterSize(Login[12], 0.000000, 0.000000);
		TextDrawTextSize(Login[12], 61.875000, 111.999992);
		TextDrawAlignment(Login[12], 1);
		TextDrawColor(Login[12], 255);
		TextDrawSetShadow(Login[12], 0);
		TextDrawSetOutline(Login[12], 0);
		TextDrawFont(Login[12], 4);
		Login[13] = TextDrawCreate(540.000000, 0.000000, "LD_SPAC:white");
		TextDrawLetterSize(Login[13], 0.000000, 0.000000);
		TextDrawTextSize(Login[13], 5.625000, 448.000000);
		TextDrawAlignment(Login[13], 1);
		TextDrawColor(Login[13], 255);
		TextDrawSetShadow(Login[13], 0);
		TextDrawSetOutline(Login[13], 0);
		TextDrawFont(Login[13], 4);
		Login[14] = TextDrawCreate(543.750000, 0.000000, "LD_SPAC:white");
		TextDrawLetterSize(Login[14], 0.000000, 0.000000);
		TextDrawTextSize(Login[14], 51.250000, 64.213333);
		TextDrawAlignment(Login[14], 1);
		TextDrawColor(Login[14], 255);
		TextDrawSetShadow(Login[14], 0);
		TextDrawSetOutline(Login[14], 0);
		TextDrawFont(Login[14], 4);
		Login[15] = TextDrawCreate(545.000000, 262.826660, "LD_SPAC:white");
		TextDrawLetterSize(Login[15], 0.000000, 0.000000);
		TextDrawTextSize(Login[15], 49.375000, 185.173339);
		TextDrawAlignment(Login[15], 1);
		TextDrawColor(Login[15], 255);
		TextDrawSetShadow(Login[15], 0);
		TextDrawSetOutline(Login[15], 0);
		TextDrawFont(Login[15], 4);
		Login[16] = TextDrawCreate(593.750000, 0.000000, "LD_SPAC:white");
		TextDrawLetterSize(Login[16], 0.000000, 0.000000);
		TextDrawTextSize(Login[16], 4.375000, 448.000000);
		TextDrawAlignment(Login[16], 1);
		TextDrawColor(Login[16], 255);
		TextDrawSetShadow(Login[16], 0);
		TextDrawSetOutline(Login[16], 0);
		TextDrawFont(Login[16], 4);
		Login[17] = TextDrawCreate(596.250000, 0.000000, "LD_SPAC:white");
		TextDrawLetterSize(Login[17], 0.000000, 0.000000);
		TextDrawTextSize(Login[17], 43.750000, 162.026672);
		TextDrawAlignment(Login[17], 1);
		TextDrawColor(Login[17], 255);
		TextDrawSetShadow(Login[17], 0);
		TextDrawSetOutline(Login[17], 0);
		TextDrawFont(Login[17], 4);
		Login[18] = TextDrawCreate(586.875000, 363.626678, "LD_SPAC:white");
		TextDrawLetterSize(Login[18], 0.000000, 0.000000);
		TextDrawTextSize(Login[18], 53.125000, 84.373321);
		TextDrawAlignment(Login[18], 1);
		TextDrawColor(Login[18], 255);
		TextDrawSetShadow(Login[18], 0);
		TextDrawSetOutline(Login[18], 0);
		TextDrawFont(Login[18], 4);
		Login[19] = TextDrawCreate(1041.875000, -496.533264, "LD_SPAC:white");
		TextDrawLetterSize(Login[19], 0.000000, 0.000000);
		TextDrawTextSize(Login[19], 1226.250000, -70.933372);
		TextDrawAlignment(Login[19], 1);
		TextDrawColor(Login[19], 255);
		TextDrawSetShadow(Login[19], 0);
		TextDrawSetOutline(Login[19], 0);
		TextDrawFont(Login[19], 4);
		Login[20] = TextDrawCreate(84.375000, 146.346755, "   Ocaso~w~RP");
		TextDrawLetterSize(Login[20], 0.418747, 1.973332);
		TextDrawAlignment(Login[20], 1);
		TextDrawColor(Login[20], 0xeb4040FF);
		TextDrawSetShadow(Login[20], -24);
		TextDrawSetOutline(Login[20], 0);
		TextDrawBackgroundColor(Login[20], 51);
		TextDrawFont(Login[20], 2);
		TextDrawSetProportional(Login[20], 1);
}

ShowTextdraws(playerid)
{
	for(new i = 0; i < 21; i++)
	{
		TextDrawShowForPlayer(playerid, Login[i]);
	}
	return 1;
}
HideTextdraws(playerid)
{
	for(new i = 0; i < 21; i++)
	{
		TextDrawHideForPlayer(playerid, Login[i]);
	}
	return 1;
}

Dialog_ShowAccents(playerid)
{
    new text[1024];
    text[0] = '\0';

    for (new i = 0; i < sizeof Accents; i++)
    {
        if (i > 0) strcat(text, "\n", sizeof text);
        strcat(text, Accents[i], sizeof text);
    }

	Dialog_Show(playerid, "OnDialogAccents", DIALOG_STYLE_LIST, ""MAIN_COLOR"OcasoZone{f5f5f5} > Selecciona tu acento", text, "�Aceptar", "xSalir");
    return 1;
}


#define CONST_HOST "db-core.bitercloud.lat"
#define CONST_USER "u90_ewJiWXDOJA"
#define CONST_PASS "Vmm9bn7!Hxe.CeXsz2!TwM^e"
#define CONST_DB "s90_orpdb"

new playerSession[MAX_PLAYERS];

ConnectDatabase()
{
    print("[MySQL] Conectando a la base de datos...");

	dbz = mysql_connect(CONST_HOST, CONST_USER, CONST_PASS, CONST_DB);

	if (mysql_errno(dbz) != 0)
	{
		print("[MySQL]*Error al conectar la base de datos.");
	}
	else
	{
  		print("[MySQL]*BASE DE DATOS CONECTADA EXITOSAMENTE");
	}
	return 1;

}

hook OnGameModeInit()
{
	LoadTextdraws();
	return 1;
}

hook OnPlayerConnect(playerid)
{
	playerSession[playerid]++;
	InitializePropertyPlayer(playerid);
	InitializeRentalPlayer(playerid);
	InitializeGameplayPlayer(playerid);
	PI[playerid][jID] = 0;
	PI[playerid][jState] = ROLEPLAY_STATE_INLOGIN;
	PI[playerid][jAdmin] = 0;

	TogglePlayerSpectating(playerid, true);
	ShowTextdraws(playerid);

	ClearPlayerChat(playerid);
	SetPlayerCameraPos(playerid, 1948.9082, -1504.6945, 98.9190);
	SetPlayerCameraLookAt(playerid, 1949.5, -1504.0, 98.5);

	new session = playerSession[playerid];
	inline CheckAccount()
	{
		if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;

		new DB_RESULT_ROWS;
		cache_get_row_count(DB_RESULT_ROWS);

		if (DB_RESULT_ROWS == 0)
		{
			Dialog_Show(playerid, "OnDialogRegister", DIALOG_STYLE_PASSWORD, ""MAIN_COLOR"OcasoZone{f5f5f5} > Registro de cuenta", "{f5f5f5}Bienvenido a "MAIN_COLOR"OcasoZone{f5f5f5}!\n\nTu cuenta no se encuentra "MAIN_COLOR"registrada.{f5f5f5}\nIngresa una "MAIN_COLOR"contrase�a (6-18 CARACTERES)", "�Siguiente", "xSalir");
			PI[playerid][jState] = ROLEPLAY_STATE_INLOGIN;
		}
		else
		{
			cache_get_value_name(0, "jIP_reg", PI[playerid][jIP_reg], 22);
			GetPlayerIp(playerid, PT[playerid][pt_IP_CONN], 22);

			if (!strcmp(PI[playerid][jIP_reg], PT[playerid][pt_IP_CONN], false))
			{
				JoinPlayer(playerid);
			}
			else
			{
				Dialog_Show(playerid, "OnDialogLogin", DIALOG_STYLE_PASSWORD, ""MAIN_COLOR"OcasoZone{f5f5f5} > Ingresa al servidor", "{f5f5f5}Bienvenido de nuevo a "MAIN_COLOR"OcasoZone{f5f5f5}!\n\nTu cuenta fue "MAIN_COLOR"encontrada {f5f5f5}\nIngresa tu "MAIN_COLOR"contrase�a para ingresar al servidor", "�Siguiente", "xSalir");
			}
		}
	}
	mysql_format(dbz, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM players WHERE jName='%e'", PlayerName(playerid));
	MySQL_TQueryInline(dbz, using inline CheckAccount, QUERY_BUFFER);
	
	return 1;
}

Dialog:OnDialogRegister(playerid, response, listitem, inputtext[])
{
	if (!response) return Kick(playerid);

	new passlength = strlen(inputtext);
	if (passlength < PASS_LEN_MIN || passlength > PASS_LEN_MAX) return Dialog_Show(playerid, "OnDialogRegister", DIALOG_STYLE_PASSWORD, ""MAIN_COLOR"OcasoZone{f5f5f5} > Registro de cuenta", "{f5f5f5}Bienvenido a "MAIN_COLOR"OcasoZone{f5f5f5}!\n\nTu cuenta no se encuentra "MAIN_COLOR"registrada.{f5f5f5}\nIngresa una "MAIN_COLOR"contrase�a (6-18 CARACTERES)", "�Siguiente", "xSalir");
	if (IsOnlySpaces(inputtext)) return Dialog_Show(playerid, "OnDialogRegister", DIALOG_STYLE_PASSWORD, ""MAIN_COLOR"OcasoZone{f5f5f5} > Registro de cuenta", "{f5f5f5}Bienvenido a "MAIN_COLOR"OcasoZone{f5f5f5}!\n\nLa cuenta "MAIN_COLOR"%s{f5f5f5} no se encuentra "MAIN_COLOR"registrada.{f5f5f5}\nIngresa una "MAIN_COLOR"contrase�a (6-18 CARACTERES)", "�Siguiente", "xSalir", PlayerName(playerid));
	
	format(PI[playerid][jPass], PASS_LEN_MAX, "%s", inputtext);

	Dialog_Show(playerid, "OnDialogGender", DIALOG_STYLE_MSGBOX, ""MAIN_COLOR"OcasoZone{f5f5f5} > ?Cual es tu genero?", "{f5f5f5}Selecciona tu "MAIN_COLOR"Genero {f5f5f5}para continuar con el registro!", "Masculino", "Femenino");
	return 1;
}
Dialog:OnDialogGender(playerid, response, listitem, inputtext[])
{
	if (response) //masculino
	{
		PI[playerid][jGender] = 1;
		PI[playerid][jSkin] = 250;
	}
	else //femenino
	{
		PI[playerid][jGender] = 2;
		PI[playerid][jSkin] = 11;
	}
	Dialog_Show(playerid, "OnDialogAge", DIALOG_STYLE_INPUT, ""MAIN_COLOR"OcasoZone{f5f5f5} > Ingresa tu edad", "{f5f5f5}Ingresa tu edad"MAIN_COLOR", Ya falta poco para que puedas jugar!", "�Siguiente", "xSalir");
	return 1;
}
Dialog:OnDialogAge(playerid, response, listitem, inputtext[])
{
	new agei = strval(inputtext);
	if (!response) return Dialog_Show(playerid, "OnDialogGender", DIALOG_STYLE_MSGBOX, ""MAIN_COLOR"OcasoZone{f5f5f5} > ?Cual es tu genero?", "{f5f5f5}Selecciona tu "MAIN_COLOR"Genero {f5f5f5}para continuar con el registro!", "Masculino", "Femenino");
	if (agei < 18 || agei > 60) return Dialog_Show(playerid, "OnDialogAge", DIALOG_STYLE_INPUT, ""MAIN_COLOR"OcasoZone{f5f5f5} > Ingresa tu edad", "{f5f5f5}Ingresa tu edad"MAIN_COLOR", Ya falta poco para que puedas jugar!", "�Siguiente", "xSalir");
	
	PI[playerid][jAge] = agei;
	Dialog_ShowAccents(playerid);
	return 1;
}
Dialog:OnDialogAccents(playerid, response, listitem, inputtext[])
{
	if (!response) return Dialog_Show(playerid, "OnDialogAge", DIALOG_STYLE_INPUT, ""MAIN_COLOR"OcasoZone{f5f5f5} > Ingresa tu edad", "{f5f5f5}Ingresa tu edad"MAIN_COLOR", Ya falta poco para que puedas jugar!", "�Siguiente", "xSalir");

	PI[playerid][jAccent] = listitem;

	Dialog_Show(playerid, "OnDialogConfirmDate", 
	DIALOG_STYLE_MSGBOX, 
	""MAIN_COLOR"OcasoZone{f5f5f5} > ?Esta todo correcto?", 
	"{f5f5f5}Si crees que los datos de tu cuenta son correctos, pulsa continuar\
	\nDe lo contrario, pulsa salir\n\
	\nNombre: %s\nGenero: %s\n\
	Edad: %d\nAcento: %s", 
	"�Continuar", "xSalir", 
	PlayerName(playerid), ConvertGenderStr(playerid), PI[playerid][jAge], Accents[PI[playerid][jAccent]]);
	return 1;
}
Dialog:OnDialogConfirmDate(playerid, response, listitem, inputtext[])
{
	if (!response) return Dialog_ShowAccents(playerid);

	CreateAccount(playerid);
	return 1;
}
Dialog:OnDialogLogin(playerid, response, listitem, inputtext[])
{
	if (!response) return Kick(playerid);

	inline PassWord()
	{
		new DB_RESULT_ROWS;
		cache_get_row_count(DB_RESULT_ROWS);

		if (DB_RESULT_ROWS == 0)
		{
			return Dialog_Show(playerid, "OnDialogLogin", DIALOG_STYLE_PASSWORD, ""MAIN_COLOR"OcasoZone{f5f5f5} > Ingresa al servidor", "{f5f5f5}Bienvenido de nuevo a "MAIN_COLOR"OcasoZone{f5f5f5}!\n\nTu cuenta fue "MAIN_COLOR"encontrada {f5f5f5}\nIngresa tu "MAIN_COLOR"contrase�a para ingresar al servidor", "�Siguiente", "xSalir");
		}
		
		JoinPlayer(playerid);
	}
	mysql_format(dbz, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM players WHERE jName='%e' AND jPass='%e'", PlayerName(playerid), inputtext);
	MySQL_TQueryInline(dbz, using inline PassWord, QUERY_BUFFER);

	return 1;
}

/*FUNCS MYSQL*/
forward CreateAccount(playerid);
public CreateAccount(playerid)
{
	GetPlayerIp(playerid, PI[playerid][jIP_reg], 22);

	PI[playerid][jCash] = 5000;
	PI[playerid][jBankMoney] = 1000;
	PI[playerid][jHealth] = 100.0;
	PI[playerid][jArmour] = 0.0;

	PI[playerid][jGmail][0] = '\0';
	PI[playerid][jAdmin] = 0;

	/*spawnpos*/			//1715.1680,-1878.6772,13.5665,0.4240
	PI[playerid][jPosX] = 1715.1680;
	PI[playerid][jPosY] = -1878.6772;
	PI[playerid][jPosZ] = 13.5665;
	PI[playerid][jRot] = 0.4240;
	SetSpawnInfo(playerid, 
	NO_TEAM, 
	PI[playerid][jSkin], 
	PI[playerid][jPosX], 
	PI[playerid][jPosY], 
	PI[playerid][jPosZ], 
	PI[playerid][jRot], 0,0,0,0,0,0);

	mysql_format(dbz, 
	QUERY_BUFFER, 
	sizeof QUERY_BUFFER, 
	"INSERT INTO players\
	(jname, jpass, jgmail, jip_reg, jdateregister, jlastconnexion, jcash,\
	jbankmoney, jscore, jskin, jstate,\
	jgender, jage, jaccent, jposx,\
	jposy, jposz, jrot, jhealth, jarmour, jAdmin, jJob, jJobLevel, jJobXP,\
	jFaction, jFactionRank, jHunger, jThirst) VALUES \
	('%e', '%e', '%e', '%e', NOW(), NOW(), %i, %i, %i, %i, %i, %i, \
	%i, %i, %f, %f, %f, %f, %f, %f, 0, 0, 1, 0, 0, 0, 100, 100)", 

	PlayerName(playerid), 
	PI[playerid][jPass], 
	PI[playerid][jGmail],
	PI[playerid][jIP_reg],
	PI[playerid][jCash],
	PI[playerid][jBankMoney],
	PI[playerid][jScore],
	PI[playerid][jSkin],
	ROLEPLAY_STATE_NORMAL,
	PI[playerid][jGender],
	PI[playerid][jAge],
	PI[playerid][jAccent],
	PI[playerid][jPosX],
	PI[playerid][jPosY],
	PI[playerid][jPosZ],
	PI[playerid][jRot],
	PI[playerid][jHealth],
	PI[playerid][jArmour]);
	mysql_tquery(dbz, QUERY_BUFFER, "OnAccountCreated", "ii", playerid, playerSession[playerid]);
	printf("%s", QUERY_BUFFER);

	return 1;
}

forward OnAccountCreated(playerid, session);
public OnAccountCreated(playerid, session)
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[MySQL] Error al crear la cuenta de %s: %s", PlayerName(playerid), error);

		if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
		{
			SendClientMessage(playerid, COLOR_ERROR, "No se pudo guardar tu cuenta. Intenta ingresar nuevamente.");
			Kick(playerid);
		}
		return 1;
	}

	if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;

	PI[playerid][jID] = cache_insert_id();
	PI[playerid][jState] = ROLEPLAY_STATE_NORMAL;
	GivePlayerMoney(playerid, PI[playerid][jCash]);
	OnGameplayPlayerLoaded(playerid);
	SetupRentalCheckpoint(playerid);
	HideTextdraws(playerid);
	TogglePlayerSpectating(playerid, false);

	SendMsg(playerid, -1, "�Bienvenido "MAIN_COLOR"%s{f5f5f5} esperamos que disfrutes en "MAIN_COLOR"OcasoZone!{f5f5f5}", PlayerName(playerid));
	SendClientMessage(playerid, -1, "�Si nesecitas ayuda usa "MAIN_COLOR"/ayuda {f5f5f5}o "MAIN_COLOR"/duda{f5f5f5}, el staff y usuarios siempre estan para "MAIN_COLOR"ayudar.");
	SendClientMessage(playerid, -1, "�"MAIN_COLOR"OcasoZone{f5f5f5} esta en constante "MAIN_COLOR"crecimiento{f5f5f5}, no dudes en reportar "MAIN_COLOR"bugs{f5f5f5} o dar "MAIN_COLOR"sugerencias{f5f5f5} para el server.");
	return 1;
}

forward JoinPlayer(playerid);
public JoinPlayer(playerid)
{
	new session = playerSession[playerid];
	inline OnLoadedPlayerData()
	{
		if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;

		new rows;
		if (cache_get_row_count(rows))
		{
			if (rows)
			{
				cache_get_value_name(0, "jPass", PI[playerid][jPass], PASS_LEN_MAX);
				cache_get_value_name(0, "jGmail", PI[playerid][jGmail], 48);
				cache_get_value_name(0, "jIP_reg", PI[playerid][jIP_reg], 22);
				cache_get_value_name(0, "jDateRegister", PI[playerid][jDateRegister], 25);
				cache_get_value_name(0, "jLastConnexion", PI[playerid][jLastConnexion], 25);

				cache_get_value_name_int(0, "id", PI[playerid][jID]);
				cache_get_value_name_int(0, "jCash", PI[playerid][jCash]);
				cache_get_value_name_int(0, "jBankMoney", PI[playerid][jBankMoney]);
				cache_get_value_name_int(0, "jAdmin", PI[playerid][jAdmin]);
				cache_get_value_name_int(0, "jJob", PI[playerid][jJob]);
				cache_get_value_name_int(0, "jJobLevel", PI[playerid][jJobLevel]);
				cache_get_value_name_int(0, "jJobXP", PI[playerid][jJobXP]);
				cache_get_value_name_int(0, "jFaction", PI[playerid][jFaction]);
				cache_get_value_name_int(0, "jFactionRank", PI[playerid][jFactionRank]);
				cache_get_value_name_int(0, "jHunger", PI[playerid][jHunger]);
				cache_get_value_name_int(0, "jThirst", PI[playerid][jThirst]);
				cache_get_value_name_int(0, "jScore", PI[playerid][jScore]);
				cache_get_value_name_int(0, "jSkin", PI[playerid][jSkin]);
				cache_get_value_name_int(0, "jState", PI[playerid][jState]);
				cache_get_value_name_int(0, "jGender", PI[playerid][jGender]);
				cache_get_value_name_int(0, "jAge", PI[playerid][jAge]);
				cache_get_value_name_int(0, "jAccent", PI[playerid][jAccent]);
				
				cache_get_value_name_float(0, "jPosX", PI[playerid][jPosX]);
				cache_get_value_name_float(0, "jPosY", PI[playerid][jPosY]);
				cache_get_value_name_float(0, "jPosZ", PI[playerid][jPosZ]);
				cache_get_value_name_float(0, "jRot", PI[playerid][jRot]);
				cache_get_value_name_float(0, "jHealth", PI[playerid][jHealth]);
				cache_get_value_name_float(0, "jArmour", PI[playerid][jArmour]);

				SetSpawnInfo(playerid, 
				NO_TEAM, 
				PI[playerid][jSkin], 
				PI[playerid][jPosX], 
				PI[playerid][jPosY], 
				PI[playerid][jPosZ], 
				PI[playerid][jRot], 0,0,0,0,0,0);

				GivePlayerMoney(playerid, PI[playerid][jCash]);
				SetPlayerScore(playerid, PI[playerid][jScore]);
				SetPlayerHealth(playerid, PI[playerid][jHealth]);
				SetPlayerArmour(playerid, PI[playerid][jArmour]);

				PI[playerid][jState] = ROLEPLAY_STATE_NORMAL;

				TogglePlayerSpectating(playerid, false);
				OnGameplayPlayerLoaded(playerid);
				SetupRentalCheckpoint(playerid);
				HideTextdraws(playerid);
			}
		}
	}
	mysql_format(dbz, QUERY_BUFFER, sizeof QUERY_BUFFER, "SELECT * FROM players WHERE jName = '%e'", PlayerName(playerid));
	MySQL_TQueryInline(dbz, using inline OnLoadedPlayerData, QUERY_BUFFER);
	return 1;
}

forward SaveData(playerid);
forward SaveDataSync(playerid);
public SaveData(playerid)
{
	return SavePlayerData(playerid, false);
}

public SaveDataSync(playerid)
{
	return SavePlayerData(playerid, true);
}

stock SavePlayerData(playerid, bool:sync)
{
	/*gets*/
	GetPlayerPos(playerid, 
	PI[playerid][jPosX], 
	PI[playerid][jPosY], 
	PI[playerid][jPosZ]);
	GetPlayerFacingAngle(playerid, PI[playerid][jRot]);

	GetPlayerHealth(playerid, PI[playerid][jHealth]);
	GetPlayerArmour(playerid, PI[playerid][jArmour]);

	PI[playerid][jCash] = GetPlayerMoney(playerid);
	PI[playerid][jScore] = GetPlayerScore(playerid);
	PI[playerid][jSkin] = GetPlayerSkin(playerid);


	mysql_format(dbz, 
	QUERY_BUFFER, 
	sizeof QUERY_BUFFER, 
	"UPDATE players SET \
			jname='%e',\
			jpass='%e',\
			jgmail='%e',\
			jJob=%i,\
			jJobLevel=%i,\
			jJobXP=%i,\
			jFaction=%i,\
			jFactionRank=%i,\
			jHunger=%i,\
			jThirst=%i,\
			jlastconnexion=NOW(),\
			jcash=%i,\
			jbankmoney=%i,\
			jscore=%i,\
			jskin=%i,\
			jstate=%i,\
			jgender=%i,\
			jage=%i,\
			jaccent=%i,\
			jposx=%f,\
			jposy=%f,\
			jposz=%f,\
			jrot=%f,\
			jhealth=%f,\
			jarmour=%f\
			WHERE jname='%e'", 

			PlayerName(playerid), PI[playerid][jPass],
			PI[playerid][jGmail], PI[playerid][jJob], PI[playerid][jJobLevel],
			PI[playerid][jJobXP], PI[playerid][jFaction], PI[playerid][jFactionRank],
			PI[playerid][jHunger], PI[playerid][jThirst], PI[playerid][jCash], 
			PI[playerid][jBankMoney], PI[playerid][jScore], 
			PI[playerid][jSkin], PI[playerid][jState], 
			PI[playerid][jGender], PI[playerid][jAge], 
			PI[playerid][jAccent], PI[playerid][jPosX], PI[playerid][jPosY], PI[playerid][jPosZ],
			PI[playerid][jRot], PI[playerid][jHealth], PI[playerid][jArmour], PlayerName(playerid));
	SaveGameplayDataInternal(playerid, sync);
	if (sync)
	{
		mysql_query(dbz, QUERY_BUFFER, false);
		if (mysql_errno(dbz) != 0)
		{
			new error[128];
			mysql_error(error, sizeof error, dbz);
			printf("[MySQL] Error al guardar los datos durante el cierre: %s", error);
		}
	}
	else
	{
		mysql_tquery(dbz, QUERY_BUFFER, "OnPlayerDataSaved");
	}

	return 1;
}

forward OnPlayerDataSaved();
public OnPlayerDataSaved()
{
	if (mysql_errno(dbz) != 0)
	{
		new error[128];
		mysql_error(error, sizeof error, dbz);
		printf("[MySQL] Error al guardar los datos de un jugador: %s", error);
	}
	return 1;
}
