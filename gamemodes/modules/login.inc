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


new playerSession[MAX_PLAYERS];
new loginAttempts[MAX_PLAYERS];
new ACCOUNT_SALT_PEPPER[] = "OcasoRP-account-salt-v1";
#define LOGIN_MAX_ATTEMPTS 5
new pendingRegistrationPassword[MAX_PLAYERS][PASS_LEN_MAX + 1];

ConnectDatabase()
{
    print("[MySQL] Conectando a la base de datos...");
    dbz = mysql_connect_file("mysql.ini");
    if (mysql_errno(dbz) != 0)
    {
        new error[128];
        mysql_error(error, sizeof error, dbz);
        printf("[MySQL] No se pudo conectar. Revisa mysql.ini: %s", error);
        return 0;
    }
    print("[MySQL] Base de datos conectada.");
    return 1;
}

stock GenerateAccountSalt(playerid, salt[], size)
{
    new name[MAX_PLAYER_NAME], ip[22], seed[128];
    GetPlayerName(playerid, name, sizeof name);
    GetPlayerIp(playerid, ip, sizeof ip);
    format(seed, sizeof seed, "%d|%d|%d|%s|%s", gettime(), playerid,
        random(2147483647), name, ip);
    SHA256_PassHash(seed, ACCOUNT_SALT_PEPPER, salt, size);
    return 1;
}

stock ShowRegisterDialog(playerid)
{
    return Dialog_Show(playerid, "OnDialogRegister", DIALOG_STYLE_PASSWORD,
        ""MAIN_COLOR"OcasoRP | Crear cuenta",
        "Bienvenido a Ocaso Roleplay.\n\nCrea una contrasena de 8 a 64 caracteres.\nSe almacenara como hash, nunca como texto plano.",
        "Continuar", "Salir");
}

stock ShowLoginDialog(playerid)
{
    new body[192];
    format(body, sizeof body,
        "Bienvenido de nuevo, %s.\n\nIntroduce tu contrasena para entrar.\nIntentos restantes: %d",
        PlayerName(playerid), LOGIN_MAX_ATTEMPTS - loginAttempts[playerid]);
    return Dialog_Show(playerid, "OnDialogLogin", DIALOG_STYLE_PASSWORD,
        ""MAIN_COLOR"OcasoRP | Iniciar sesion", body, "Entrar", "Salir");
}

hook OnGameModeInit()
{
	LoadTextdraws();
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    #pragma unused reason
    pendingRegistrationPassword[playerid][0] = '\0';
    loginAttempts[playerid] = 0;
    return 1;
}

hook OnPlayerConnect(playerid)
{
    playerSession[playerid]++;
    cooldown[playerid] = 0;
    loginAttempts[playerid] = 0;
    pendingRegistrationPassword[playerid][0] = '\0';
    InitializePropertyPlayer(playerid);
    InitializeRentalPlayer(playerid);
    InitializeGameplayPlayer(playerid);
    PI[playerid][jID] = 0;
    PI[playerid][jState] = ROLEPLAY_STATE_INLOGIN;
    PI[playerid][jAdmin] = 0;
    PI[playerid][jPhone] = 0;

    TogglePlayerSpectating(playerid, true);
    ShowTextdraws(playerid);
    ClearPlayerChat(playerid);
    SetPlayerCameraPos(playerid, 1948.9082, -1504.6945, 98.9190);
    SetPlayerCameraLookAt(playerid, 1949.5, -1504.0, 98.5);

    new session = playerSession[playerid];
    inline CheckAccount()
    {
        if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;
        if (mysql_errno(dbz) != 0)
        {
            SendClientMessage(playerid, COLOR_ERROR, "No se pudo consultar tu cuenta. Intenta mas tarde.");
            Kick(playerid);
            return 1;
        }

        new rows;
        cache_get_row_count(rows);
        if (rows == 0)
        {
            PI[playerid][jState] = ROLEPLAY_STATE_INREGISTER;
            ShowRegisterDialog(playerid);
        }
        else
        {
            // No se usa la IP para entrar automaticamente: siempre se valida la contrasena.
            PI[playerid][jState] = ROLEPLAY_STATE_INLOGIN;
            ShowLoginDialog(playerid);
        }
        return 1;
    }

    mysql_format(dbz, QUERY_BUFFER, sizeof QUERY_BUFFER,
        "SELECT id FROM players WHERE jName='%e' LIMIT 1", PlayerName(playerid));
    MySQL_TQueryInline(dbz, using inline CheckAccount, QUERY_BUFFER);
    return 1;
}

Dialog:OnDialogRegister(playerid, response, listitem, inputtext[])
{
    #pragma unused listitem
    if (!response) return Kick(playerid);
    if (PI[playerid][jState] != ROLEPLAY_STATE_INREGISTER) return 1;

    new passlength = strlen(inputtext);
    if (passlength < PASS_LEN_MIN || passlength > PASS_LEN_MAX || IsOnlySpaces(inputtext))
    {
        SendClientMessage(playerid, COLOR_ERROR, "La contrasena debe tener entre 8 y 64 caracteres y no puede estar vacia.");
        return ShowRegisterDialog(playerid);
    }
    format(pendingRegistrationPassword[playerid], PASS_LEN_MAX + 1, "%s", inputtext);
    Dialog_Show(playerid, "OnDialogGender", DIALOG_STYLE_MSGBOX,
        ""MAIN_COLOR"OcasoRP | Crear personaje",
        "Selecciona el genero de tu personaje.", "Masculino", "Femenino");
    return 1;
}

Dialog:OnDialogGender(playerid, response, listitem, inputtext[])
{
    #pragma unused listitem, inputtext
    if (PI[playerid][jState] != ROLEPLAY_STATE_INREGISTER) return 1;
    if (response)
    {
        PI[playerid][jGender] = 1;
        PI[playerid][jSkin] = 250;
    }
    else
    {
        PI[playerid][jGender] = 2;
        PI[playerid][jSkin] = 11;
    }
    Dialog_Show(playerid, "OnDialogAge", DIALOG_STYLE_INPUT,
        ""MAIN_COLOR"OcasoRP | Edad del personaje",
        "Ingresa una edad entre 18 y 60 anos.", "Continuar", "Volver");
    return 1;
}

Dialog:OnDialogAge(playerid, response, listitem, inputtext[])
{
    #pragma unused listitem
    if (!response)
    {
        return Dialog_Show(playerid, "OnDialogGender", DIALOG_STYLE_MSGBOX,
            ""MAIN_COLOR"OcasoRP | Crear personaje",
            "Selecciona el genero de tu personaje.", "Masculino", "Femenino");
    }
    if (PI[playerid][jState] != ROLEPLAY_STATE_INREGISTER || !IsNumericString(inputtext))
    {
        SendClientMessage(playerid, COLOR_ERROR, "Ingresa una edad numerica valida.");
        return Dialog_Show(playerid, "OnDialogAge", DIALOG_STYLE_INPUT,
            ""MAIN_COLOR"OcasoRP | Edad del personaje",
            "Ingresa una edad entre 18 y 60 anos.", "Continuar", "Volver");
    }

    new age = strval(inputtext);
    if (age < 18 || age > 60)
    {
        SendClientMessage(playerid, COLOR_ERROR, "La edad permitida es de 18 a 60 anos.");
        return Dialog_Show(playerid, "OnDialogAge", DIALOG_STYLE_INPUT,
            ""MAIN_COLOR"OcasoRP | Edad del personaje",
            "Ingresa una edad entre 18 y 60 anos.", "Continuar", "Volver");
    }
    PI[playerid][jAge] = age;
    Dialog_ShowAccents(playerid);
    return 1;
}

Dialog:OnDialogAccents(playerid, response, listitem, inputtext[])
{
    #pragma unused inputtext
    if (!response) return Dialog_Show(playerid, "OnDialogAge", DIALOG_STYLE_INPUT,
        ""MAIN_COLOR"OcasoRP | Edad del personaje",
        "Ingresa una edad entre 18 y 60 anos.", "Continuar", "Volver");
    if (PI[playerid][jState] != ROLEPLAY_STATE_INREGISTER
        || listitem < 0 || listitem >= sizeof Accents)
    {
        return 1;
    }

    PI[playerid][jAccent] = listitem;
    Dialog_Show(playerid, "OnDialogConfirmDate", DIALOG_STYLE_MSGBOX,
        ""MAIN_COLOR"OcasoRP | Confirmar personaje",
        "Nombre: %s\nGenero: %s\nEdad: %d\nAcento: %s\n\nTu contrasena se guardara protegida con hash.",
        "Crear cuenta", "Volver", PlayerName(playerid), ConvertGenderStr(playerid),
        PI[playerid][jAge], Accents[PI[playerid][jAccent]]);
    return 1;
}

Dialog:OnDialogConfirmDate(playerid, response, listitem, inputtext[])
{
    #pragma unused listitem, inputtext
    if (!response) return Dialog_ShowAccents(playerid);
    if (PI[playerid][jState] != ROLEPLAY_STATE_INREGISTER
        || !pendingRegistrationPassword[playerid][0]) return 1;
    CreateAccount(playerid);
    return 1;
}

Dialog:OnDialogLogin(playerid, response, listitem, inputtext[])
{
    #pragma unused listitem
    if (!response) return Kick(playerid);
    if (PI[playerid][jState] != ROLEPLAY_STATE_INLOGIN) return 1;
    if (!strlen(inputtext) || strlen(inputtext) > PASS_LEN_MAX)
    {
        SendClientMessage(playerid, COLOR_ERROR, "Contrasena incorrecta.");
        return ShowLoginDialog(playerid);
    }

    new query[128];
    mysql_format(dbz, query, sizeof query,
        "SELECT jPass,jPassSalt FROM players WHERE jName='%e' LIMIT 1", PlayerName(playerid));
    mysql_tquery(dbz, query, "OnLoginPasswordChecked", "iis[65]",
        playerid, playerSession[playerid], inputtext);
    return 1;
}

forward OnLoginPasswordChecked(playerid, session, password[]);
public OnLoginPasswordChecked(playerid, session, password[])
{
    if (!IsPlayerConnected(playerid) || playerSession[playerid] != session
        || PI[playerid][jState] != ROLEPLAY_STATE_INLOGIN) return 1;
    if (mysql_errno(dbz) != 0)
    {
        new error[128];
        mysql_error(error, sizeof error, dbz);
        printf("[Login] Error al verificar una cuenta: %s", error);
        SendClientMessage(playerid, COLOR_ERROR, "No se pudo verificar la cuenta. Intenta nuevamente.");
        return ShowLoginDialog(playerid);
    }

    new rows, storedHash[PASS_HASH_SIZE], storedSalt[PASS_SALT_SIZE];
    cache_get_row_count(rows);
    if (rows < 1)
    {
        SendClientMessage(playerid, COLOR_ERROR, "La cuenta ya no existe. Vuelve a conectarte.");
        return Kick(playerid);
    }
    cache_get_value_name(0, "jPass", storedHash, sizeof storedHash);
    cache_get_value_name(0, "jPassSalt", storedSalt, sizeof storedSalt);

    new bool:validPassword = false, bool:legacyPassword = false;
    if (!storedSalt[0])
    {
        // Migracion transparente de cuentas antiguas que guardaban el texto plano.
        validPassword = !strcmp(password, storedHash, false);
        legacyPassword = validPassword;
    }
    else
    {
        new candidate[PASS_HASH_SIZE];
        SHA256_PassHash(password, storedSalt, candidate, sizeof candidate);
        validPassword = !strcmp(candidate, storedHash, false);
    }

    if (!validPassword)
    {
        loginAttempts[playerid]++;
        if (loginAttempts[playerid] >= LOGIN_MAX_ATTEMPTS)
        {
            SendClientMessage(playerid, COLOR_ERROR, "Demasiados intentos fallidos. Vuelve a conectarte.");
            return Kick(playerid);
        }
        SendClientMessage(playerid, COLOR_ERROR, "Contrasena incorrecta.");
        return ShowLoginDialog(playerid);
    }

    if (legacyPassword)
    {
        GenerateAccountSalt(playerid, PI[playerid][jPassSalt], PASS_SALT_SIZE);
        SHA256_PassHash(password, PI[playerid][jPassSalt], PI[playerid][jPass], PASS_HASH_SIZE);
        new query[256];
        mysql_format(dbz, query, sizeof query,
            "UPDATE players SET jPass='%e',jPassSalt='%e' WHERE jName='%e' AND jPassSalt=''",
            PI[playerid][jPass], PI[playerid][jPassSalt], PlayerName(playerid));
        mysql_tquery(dbz, query, "OnLegacyPasswordUpgraded", "ii", playerid, session);
    }
    else
    {
        JoinPlayer(playerid);
    }
    return 1;
}

forward OnLegacyPasswordUpgraded(playerid, session);
public OnLegacyPasswordUpgraded(playerid, session)
{
    if (mysql_errno(dbz) != 0)
    {
        new error[128];
        mysql_error(error, sizeof error, dbz);
        printf("[Login] No se pudo actualizar el hash heredado: %s", error);
        if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
        {
            SendClientMessage(playerid, COLOR_ERROR, "No se pudo proteger la contrasena antigua. Intenta conectarte de nuevo.");
            Kick(playerid);
        }
        return 1;
    }
    if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;
    JoinPlayer(playerid);
    return 1;
}

stock IsNumericString(const text[])
{
    if (!text[0]) return 0;
    for (new index = 0; text[index] != '\0'; index++)
    {
        if (text[index] < '0' || text[index] > '9') return 0;
    }
    return 1;
}

/*FUNCS MYSQL*/
forward CreateAccount(playerid);
public CreateAccount(playerid)
{
	if (!IsPlayerConnected(playerid) || PI[playerid][jState] != ROLEPLAY_STATE_INREGISTER) return 0;
	GetPlayerIp(playerid, PI[playerid][jIP_reg], 22);
	GenerateAccountSalt(playerid, PI[playerid][jPassSalt], PASS_SALT_SIZE);
	SHA256_PassHash(pendingRegistrationPassword[playerid], PI[playerid][jPassSalt],
		PI[playerid][jPass], PASS_HASH_SIZE);
	pendingRegistrationPassword[playerid][0] = '\0';

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
	(jname, jpass, jPassSalt, jgmail, jip_reg, jdateregister, jlastconnexion, jcash,\
	jbankmoney, jscore, jskin, jstate,\
	jgender, jage, jaccent, jposx,\
	jposy, jposz, jrot, jhealth, jarmour, jAdmin, jJob, jJobLevel, jJobXP,\
	jFaction, jFactionRank, jHunger, jThirst) VALUES \
	('%e', '%e', '%e', '%e', '%e', NOW(), NOW(), %i, %i, %i, %i, %i, %i, \
	%i, %i, %f, %f, %f, %f, %f, %f, 0, 0, 1, 0, 0, 0, 100, 100)", 

	PlayerName(playerid), 
	PI[playerid][jPass], 
	PI[playerid][jPassSalt],
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
	PI[playerid][jPhone] = 0;
	PI[playerid][jState] = ROLEPLAY_STATE_NORMAL;
	loginAttempts[playerid] = 0;
	EnsurePlayerPhoneNumber(playerid);
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
		if (mysql_errno(dbz) != 0)
		{
			SendClientMessage(playerid, COLOR_ERROR, "No se pudieron cargar tus datos. Intenta conectarte nuevamente.");
			Kick(playerid);
			return 1;
		}

		new rows;
		if (!cache_get_row_count(rows) || rows < 1)
		{
			SendClientMessage(playerid, COLOR_ERROR, "No se encontro tu cuenta al cargar los datos.");
			Kick(playerid);
			return 1;
		}
		if (rows)
		{
				cache_get_value_name(0, "jPass", PI[playerid][jPass], PASS_HASH_SIZE);
				cache_get_value_name(0, "jPassSalt", PI[playerid][jPassSalt], PASS_SALT_SIZE);
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
				cache_get_value_name_int(0, "jPhone", PI[playerid][jPhone]);
				
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
				loginAttempts[playerid] = 0;
				EnsurePlayerPhoneNumber(playerid);

				TogglePlayerSpectating(playerid, false);
				OnGameplayPlayerLoaded(playerid);
				SetupRentalCheckpoint(playerid);
				HideTextdraws(playerid);
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
			jPassSalt='%e',\
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

			PlayerName(playerid), PI[playerid][jPass], PI[playerid][jPassSalt],
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
