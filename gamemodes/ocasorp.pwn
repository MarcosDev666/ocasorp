/*
    GM Oscaso Roleplay BY Brian & Haunt

                                    |-| CONSULTAS A MI DC: tbone18 & MI COMPAÑERO hauntren. |-|

                                                                        �DEJA CREDITOS!
*/


#define YSI_NO_HEAP_MALLOC
#include <a_samp>
#pragma tabsize 0
#include <core>
#include <float>
#include <sscanf2>
#include <a_mysql>
#include <YSI_Coding\y_stringhash>
#include <YSI_Coding\y_va>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_inline>
#include <YSI_Extra\y_inline_mysql>
#include <easyDialog>
#include <Pawn.CMD>

// Colores principales
#define COLOR_GLOBAL 0xEEEEEEFF
#define COLOR_ADMIN 0xDAA2ACAA
#define COLOR_ERROR 0xFF4444FF
#define COLOR_USAGE 0xBFC0C2FF
#define COLOR_TWITTER 0x00ACEEFF
#define COLOR_DUDA 0xE0FFFFAA

#define MAIN_COLOR "{F2FF00}"

#define MIN_DISTANCE_INTERACTION 3.6

/*acentos by Ocaso*/
new Accents[][] =
{
    {"Acento Argentino"},
    {"Acento Chileno"},
    {"Acento Mexicano"},
    {"Acento Colombiano"},
    {"Acento Venezolano"},
    {"Acento Peruano"},
    {"Acento Uruguayo"},
    {"Acento Paraguayo"},
    {"Acento Boliviano"},
    {"Acento Espanol"},
    {"Acento Cubano"},
    {"Acento Dominicano"},
    {"Acento Puertorriqueno"},
    {"Acento Brasileno"},
    {"Acento Ingles"},
    {"Acento Frances"},
    {"Acento Aleman"},
    {"Acento Italiano"},
    {"Acento Ruso"},
    {"Acento Chino"},
    {"Acento Japones"},
    {"Acento Coreano"},
    {"Acento Indio"},
    {"Acento Pakistani"},
    {"Acento Turco"},
    {"Acento Arabe"},
    {"Acento Griego"},
    {"Acento Sueco"},
    {"Acento Noruego"},
    {"Acento Danes"},
    {"Acento Finlandes"},
    {"Acento Polaco"},
    {"Acento Checo"},
    {"Acento Hungaro"},
    {"Acento Holandes"},
    {"Acento Belga"},
    {"Acento Suizo"},
    {"Acento Canadiense"},
    {"Acento Estadounidense"},
    {"Acento Feminista"}
};


/*pinfo*/

#define PASS_LEN_MAX 18
#define PASS_LEN_MIN 6
enum enum_PI
{
    jPass[PASS_LEN_MAX],
    jGmail[48],
    jIP_reg[22], //ip de registro
    jDateRegister[25], //Fecha de registro
    jLastConnexion[25], //Ultima conexion

    jID,
    jCash,
    jBankMoney,
    jAdmin,
    jJob,
    jJobLevel,
    jJobXP,
    jFaction,
    jFactionRank,
    jHunger,
    jThirst,
    jScore,
    jSkin,
    jState,
    jGender,
    jAge,
    jAccent,

    Float:jPosX,
    Float:jPosY,
    Float:jPosZ,

    Float:jRot,

    Float:jHealth,
    Float:jArmour

}
new PI[MAX_PLAYERS][enum_PI];

enum enum_PT
{
    pt_IP_CONN[22]
}
new PT[MAX_PLAYERS][enum_PT];

main(){}

/*states*/
enum
{
    ROLEPLAY_STATE_NORMAL,
    ROLEPLAY_STATE_JAILED_IC,
    ROLEPLAY_STATE_JAILED_OOC,
    ROLEPLAY_STATE_CUFFED,
    ROLEPLAY_STATE_CRACK, //MORIDO
    ROLEPLAY_STATE_INREGISTER,
    ROLEPLAY_STATE_INLOGIN,
}

stock bool:IsAccountLoaded(playerid)
{
    return PI[playerid][jState] != ROLEPLAY_STATE_INLOGIN
        && PI[playerid][jState] != ROLEPLAY_STATE_INREGISTER;
}

// Cooldown global para comandos
new cooldown[MAX_PLAYERS];

// Devuelve true si el jugador puede usar el comando, false si debe esperar
stock bool:CanUseCooldown(playerid, segundos)
{
    if (cooldown[playerid] > gettime())
    {
        new msg[64];
        format(msg, sizeof msg, "Debes esperar %i segundos para usar este comando.", cooldown[playerid] - gettime());
        SendClientMessage(playerid, 0xFF4444FF, msg);
        return false;
    }
    cooldown[playerid] = gettime() + segundos;
    return true;
}
//se ve?.. 
new QUERY_BUFFER[4096]; //para queryss
    
/*funcs*/
PlayerName(playerid)
{
    new n[MAX_PLAYER_NAME];
    GetPlayerName(playerid, n, sizeof n);
    return n;
}
ClearPlayerChat(playerid)
{
    for (new i =0; i < 200; i++)
    {
        SendClientMessage(playerid, -1, "");
    }
    return 1;
}
IsOnlySpaces(const str[])
{
    for (new i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ')
            return 0;
    }
    return 1;
}
ConvertGenderStr(playerid)
{
    new gender[32];
    switch (PI[playerid][jGender])
    {
        case 1:
        {
            gender = "Masculino";
        }
        case 2:
        {
            gender = "Femenino";
        }
        default:
        {
            gender = "Error al recopilar tus datos";
        }
    }
    return gender;
}
SendLocalMessage(playerid, const lmessage[])
{
    new Float:targX, Float:targY, Float: targZ;
    GetPlayerPos(playerid, targX, targY, targZ);

    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerInRangeOfPoint(i, MIN_DISTANCE_INTERACTION, 
        targX, targY, targZ))
        {
            if (PI[playerid][jState] != ROLEPLAY_STATE_INLOGIN && PI[playerid][jState] != ROLEPLAY_STATE_INREGISTER)
            {
                SendClientMessage(playerid, -1, lmessage);
            }
        }
    }
    return 1;
}
stock SendMsg(playerid, color, const text[], {Float, _}:...)
{
    new str[128];
    format(str, sizeof(str), text, ___(3));
    SendClientMessage(playerid, color, str);
    return 1;
}




/*mysql*/
new MySQL:dbz;

/*......*/
public OnGameModeInit()
{
    ConnectDatabase();
	InitializeGameplaySystems();
	InitializeStores();
	InitializePropertySystems();
	SendRconCommand("hostname [+] Ocaso Roleplay | Estamos En Familia!");
	SendRconCommand("mapname San Andreas");
	SendRconCommand("weburl rol.OcasoRP.com");
	SendRconCommand("language Espa�ol - Spanish");
	SetGameModeText("OS:RP v0.1");

    return 1;
}
public OnPlayerDisconnect(playerid, reason)
{
    PreparePropertiesDisconnect(playerid);
    if (PI[playerid][jState] != ROLEPLAY_STATE_INLOGIN)
    {
        SaveData(playerid);
    }
    CleanupGameplayPlayer(playerid);
    CleanupRentalPlayer(playerid);
    CleanupPropertyPlayer(playerid);
    return 1;
}
public OnGameModeExit()
{
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && PI[i][jState] != ROLEPLAY_STATE_INLOGIN)
        {
            SaveDataSync(i);
        }
    }
    StoreAllVehiclesOnShutdown();
    mysql_close(dbz);
    return 1; 
}
public OnPlayerText(playerid, text[])
{
    new msg[1500];
    format(msg, sizeof msg, "%s (%s) dice: %s", PlayerName(playerid), Accents[PI[playerid][jAccent]], text);
    SendLocalMessage(playerid, msg);
    return 0;
}

forward SetupRentalCheckpoint(playerid);
forward InitializeRentalPlayer(playerid);
forward CleanupRentalPlayer(playerid);
forward InitializeGameplaySystems();
forward InitializeGameplayPlayer(playerid);
forward OnGameplayPlayerLoaded(playerid);
forward SaveGameplayData(playerid);
forward CleanupGameplayPlayer(playerid);
forward HandleGameplayCheckpoint(playerid);
forward HandleGPSCheckpoint(playerid);
forward InitializeGPSPlayer(playerid);
forward CleanupGPSPlayer(playerid);
forward UpdatePlayerRouteCheckpoint(playerid);
forward LoadPlayerInventory(playerid);
forward SaveInventoryData(playerid);
forward InitializeHUDPlayer(playerid);
forward ShowGameplayHUD(playerid);
forward InitializeHUDSystem();
forward CleanupHUDPlayer(playerid);
forward InitializePropertySystems();
forward InitializePropertyPlayer(playerid);
forward LoadPlayerHouse(playerid);
forward CleanupPropertyPlayer(playerid);
forward PreparePropertiesDisconnect(playerid);
forward StoreAllVehiclesOnShutdown();
forward RefreshPlayerCash(playerid, session);
forward HandleHousePickup(playerid, pickupid);
forward bool:IsWalletTransactionPending(playerid);

/*modulos */   
#include "modules/login"
#include "modules/gameplay"
#include "modules/inventory"
#include "modules/hud"
#include "modules/admin"
#include "modules/rentals"
#include "modules/economy"
#include "modules/properties"
#include "modules/gps"
#include "modules/cmds"