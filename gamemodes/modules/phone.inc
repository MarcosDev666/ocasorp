#include <YSI_Coding\y_hooks>

#define PHONE_MESSAGE_MAX 144
#define PHONE_INBOX_LIMIT 10
#define PHONE_CALL_IDLE 0
#define PHONE_CALL_RINGING 1
#define PHONE_CALL_ACTIVE 2
#define PHONE_CALL_TIMEOUT 30000

new bool:phoneEnabled[MAX_PLAYERS];
new phoneCallPeer[MAX_PLAYERS];
new phoneCallState[MAX_PLAYERS];
new phoneCallTimer[MAX_PLAYERS];
new bool:phoneSmsPending[MAX_PLAYERS];
new phoneSmsNumber[MAX_PLAYERS];
new phoneSmsMessage[MAX_PLAYERS][PHONE_MESSAGE_MAX + 1];
new phoneCallTimeoutName[] = "PhoneCallTimeout";

hook OnPlayerConnect(playerid)
{
    phoneEnabled[playerid] = true;
    phoneCallPeer[playerid] = INVALID_PLAYER_ID;
    phoneCallState[playerid] = PHONE_CALL_IDLE;
    phoneCallTimer[playerid] = 0;
    phoneSmsPending[playerid] = false;
    phoneSmsNumber[playerid] = 0;
    phoneSmsMessage[playerid][0] = '\0';
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    #pragma unused reason
    EndPhoneCall(playerid, true);
    phoneSmsPending[playerid] = false;
    phoneSmsMessage[playerid][0] = '\0';
    return 1;
}

public EnsurePlayerPhoneNumber(playerid)
{
    if (PI[playerid][jID] <= 0) return 0;
    if (PI[playerid][jPhone] <= 0)
    {
        PI[playerid][jPhone] = 55000000 + PI[playerid][jID];
        new query[128];
        mysql_format(dbz, query, sizeof query,
            "UPDATE players SET jPhone=%i WHERE id=%i AND jPhone=0",
            PI[playerid][jPhone], PI[playerid][jID]);
        mysql_tquery(dbz, query, "OnPhoneNumberSaved", "ii",
            playerid, playerSession[playerid]);
    }
    return 1;
}

forward OnPhoneNumberSaved(playerid, session);
public OnPhoneNumberSaved(playerid, session)
{
    if (mysql_errno(dbz) != 0)
    {
        new error[128];
        mysql_error(error, sizeof error, dbz);
        printf("[Phone] No se pudo guardar el numero: %s", error);
        if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
        {
            SendClientMessage(playerid, COLOR_ERROR, "No se pudo guardar tu numero telefonico.");
        }
    }
    return 1;
}

stock FindPlayerByPhoneNumber(number)
{
    for (new playerid = 0; playerid < MAX_PLAYERS; playerid++)
    {
        if (!IsPlayerConnected(playerid) || !IsAccountLoaded(playerid)) continue;
        if (PI[playerid][jPhone] == number) return playerid;
    }
    return INVALID_PLAYER_ID;
}

stock bool:ParsePhoneSMS(const params[], &number, message[], messageSize)
{
    new index, digits, digit;
    message[0] = '\0';
    while (params[index] == ' ' || params[index] == '\t') index++;
    number = 0;
    while (params[index] >= '0' && params[index] <= '9')
    {
        if (digits >= 10) return false;
        digit = params[index] - '0';
        if (number > 214748364 || (number == 214748364 && digit > 7)) return false;
        number = number * 10 + digit;
        digits++;
        index++;
    }
    if (digits < 7) return false;
    while (params[index] == ' ' || params[index] == '\t') index++;
    if (!params[index]) return false;

    new length;
    while (params[index] && length < messageSize - 1)
    {
        message[length++] = params[index++];
    }
    if (params[index])
    {
        message[0] = '\0';
        return false;
    }
    message[length] = '\0';
    while (length > 0 && (message[length - 1] == ' ' || message[length - 1] == '\t'))
    {
        message[--length] = '\0';
    }
    return length > 0;
}

stock ShowPhoneMenu(playerid)
{
    new body[192];
    format(body, sizeof body,
        "Telefono %s | numero %d\nBuzon de SMS\nAyuda: llamadas y mensajes",
        phoneEnabled[playerid] ? "encendido" : "apagado", PI[playerid][jPhone]);
    return Dialog_Show(playerid, "OnDialogPhone", DIALOG_STYLE_LIST,
        "Telefono movil", body, "Abrir", "Cerrar");
}

CMD:telefono(playerid, params[])
{
    #pragma unused params
    if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
    EnsurePlayerPhoneNumber(playerid);
    return ShowPhoneMenu(playerid);
}

CMD:celular(playerid, params[])
{
    #pragma unused params
    if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
    EnsurePlayerPhoneNumber(playerid);
    return ShowPhoneMenu(playerid);
}

Dialog:OnDialogPhone(playerid, response, listitem, inputtext[])
{
    #pragma unused inputtext
    if (!response || !IsAccountLoaded(playerid)) return 1;
    switch (listitem)
    {
        case 0:
        {
            phoneEnabled[playerid] = !phoneEnabled[playerid];
            SendClientMessage(playerid, COLOR_GLOBAL,
                phoneEnabled[playerid] ? "Telefono encendido." : "Telefono apagado; no recibiras llamadas.");
            if (!phoneEnabled[playerid]) EndPhoneCall(playerid, true);
            return ShowPhoneMenu(playerid);
        }
        case 1: return LoadPhoneInbox(playerid);
        case 2:
        {
            SendClientMessage(playerid, COLOR_GLOBAL, "Usa /llamar <numero>, /contestar, /colgar y /sms <numero> <mensaje>.");
        }
    }
    return 1;
}

CMD:llamar(playerid, params[])
{
    if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
    if (!phoneEnabled[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Enciende tu telefono con /telefono.");

    new number;
    if (sscanf(params, "i", number)) return SendClientMessage(playerid, COLOR_USAGE, "Uso: /llamar <numero de telefono>");
    new targetid = FindPlayerByPhoneNumber(number);
    if (targetid == INVALID_PLAYER_ID || !phoneEnabled[targetid])
    {
        return SendClientMessage(playerid, COLOR_ERROR, "Ese numero no esta disponible o el telefono esta apagado.");
    }
    if (targetid == playerid) return SendClientMessage(playerid, COLOR_ERROR, "No puedes llamarte a ti mismo.");
    if (phoneCallState[playerid] != PHONE_CALL_IDLE || phoneCallState[targetid] != PHONE_CALL_IDLE)
    {
        return SendClientMessage(playerid, COLOR_ERROR, "Tu o la otra persona ya esta en una llamada.");
    }

    phoneCallPeer[playerid] = targetid;
    phoneCallPeer[targetid] = playerid;
    phoneCallState[playerid] = PHONE_CALL_RINGING;
    phoneCallState[targetid] = PHONE_CALL_RINGING;
    new name[MAX_PLAYER_NAME], message[112];
    GetPlayerName(playerid, name, sizeof name);
    format(message, sizeof message, "Llamada entrante de %s (numero %d). Usa /contestar o /colgar.",
        name, PI[playerid][jPhone]);
    SendClientMessage(targetid, COLOR_TWITTER, message);
    SendClientMessage(playerid, COLOR_GLOBAL, "Llamando... espera a que contesten o usa /colgar.");

    phoneCallTimer[playerid] = SetTimerEx(phoneCallTimeoutName, PHONE_CALL_TIMEOUT, false,
        "iii", playerid, playerSession[playerid], targetid);
    if (!phoneCallTimer[playerid]) EndPhoneCall(playerid, true);
    return 1;
}

CMD:contestar(playerid, params[])
{
    #pragma unused params
    if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
    if (phoneCallState[playerid] != PHONE_CALL_RINGING
        || phoneCallPeer[playerid] == INVALID_PLAYER_ID)
    {
        return SendClientMessage(playerid, COLOR_ERROR, "No tienes una llamada entrante.");
    }

    new peerid = phoneCallPeer[playerid];
    if (!IsPlayerConnected(peerid) || phoneCallPeer[peerid] != playerid)
    {
        EndPhoneCall(playerid, true);
        return SendClientMessage(playerid, COLOR_ERROR, "La llamada ya no esta disponible.");
    }
    if (phoneCallTimer[playerid])
    {
        KillTimer(phoneCallTimer[playerid]);
        phoneCallTimer[playerid] = 0;
    }
    if (phoneCallTimer[peerid])
    {
        KillTimer(phoneCallTimer[peerid]);
        phoneCallTimer[peerid] = 0;
    }
    phoneCallState[playerid] = PHONE_CALL_ACTIVE;
    phoneCallState[peerid] = PHONE_CALL_ACTIVE;
    SendClientMessage(playerid, COLOR_GLOBAL, "Llamada conectada. Usa el chat para hablar; /colgar para finalizar.");
    SendClientMessage(peerid, COLOR_GLOBAL, "La otra persona contesto. Usa el chat para hablar; /colgar para finalizar.");
    return 1;
}

CMD:colgar(playerid, params[])
{
    #pragma unused params
    if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
    if (phoneCallState[playerid] == PHONE_CALL_IDLE) return SendClientMessage(playerid, COLOR_ERROR, "No estas en una llamada.");
    EndPhoneCall(playerid, true);
    return 1;
}

forward PhoneCallTimeout(playerid, session, targetid);
public PhoneCallTimeout(playerid, session, targetid)
{
    if (!IsPlayerConnected(playerid) || playerSession[playerid] != session
        || phoneCallPeer[playerid] != targetid || phoneCallState[playerid] != PHONE_CALL_RINGING) return 1;
    phoneCallTimer[playerid] = 0;
    SendClientMessage(playerid, COLOR_ERROR, "La llamada no fue contestada.");
    if (IsPlayerConnected(targetid)) SendClientMessage(targetid, COLOR_ERROR, "Llamada perdida.");
    EndPhoneCall(playerid, false);
    return 1;
}

stock EndPhoneCall(playerid, bool:notifyPeer)
{
    new peerid = phoneCallPeer[playerid];
    if (phoneCallTimer[playerid])
    {
        KillTimer(phoneCallTimer[playerid]);
        phoneCallTimer[playerid] = 0;
    }
    phoneCallPeer[playerid] = INVALID_PLAYER_ID;
    phoneCallState[playerid] = PHONE_CALL_IDLE;

    if (peerid != INVALID_PLAYER_ID && peerid >= 0 && peerid < MAX_PLAYERS
        && IsPlayerConnected(peerid) && phoneCallPeer[peerid] == playerid)
    {
        if (phoneCallTimer[peerid])
        {
            KillTimer(phoneCallTimer[peerid]);
            phoneCallTimer[peerid] = 0;
        }
        phoneCallPeer[peerid] = INVALID_PLAYER_ID;
        phoneCallState[peerid] = PHONE_CALL_IDLE;
        if (notifyPeer) SendClientMessage(peerid, COLOR_GLOBAL, "La llamada finalizo.");
    }
    return 1;
}

stock bool:SendPhoneCallText(playerid, const text[])
{
    if (phoneCallState[playerid] != PHONE_CALL_ACTIVE) return false;
    new peerid = phoneCallPeer[playerid];
    if (peerid == INVALID_PLAYER_ID || !IsPlayerConnected(peerid)
        || phoneCallPeer[peerid] != playerid)
    {
        EndPhoneCall(playerid, false);
        SendClientMessage(playerid, COLOR_ERROR, "La llamada se corto.");
        return true;
    }

    new name[MAX_PLAYER_NAME], message[192];
    GetPlayerName(playerid, name, sizeof name);
    format(message, sizeof message, "[Telefono] %s: %s", name, text);
    SendClientMessage(peerid, COLOR_TWITTER, message);
    SendClientMessage(playerid, COLOR_TWITTER, message);
    return true;
}

CMD:sms(playerid, params[])
{
    if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
    if (!phoneEnabled[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Enciende tu telefono con /telefono.");
    if (phoneSmsPending[playerid]) return SendClientMessage(playerid, COLOR_ERROR, "Espera a que se envie tu SMS anterior.");
    if (!ParsePhoneSMS(params, phoneSmsNumber[playerid], phoneSmsMessage[playerid], PHONE_MESSAGE_MAX + 1))
    {
        return SendClientMessage(playerid, COLOR_USAGE, "Uso: /sms <numero> <mensaje de hasta 144 caracteres>");
    }
    if (phoneSmsNumber[playerid] == PI[playerid][jPhone])
    {
        phoneSmsMessage[playerid][0] = '\0';
        return SendClientMessage(playerid, COLOR_ERROR, "No puedes enviarte un SMS a ti mismo.");
    }

    phoneSmsPending[playerid] = true;
    new query[128];
    mysql_format(dbz, query, sizeof query,
        "SELECT id FROM players WHERE jPhone=%i LIMIT 1", phoneSmsNumber[playerid]);
    mysql_tquery(dbz, query, "OnPhoneRecipientLoaded", "ii", playerid, playerSession[playerid]);
    return 1;
}

forward OnPhoneRecipientLoaded(playerid, session);
public OnPhoneRecipientLoaded(playerid, session)
{
    if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;
    if (mysql_errno(dbz) != 0)
    {
        phoneSmsPending[playerid] = false;
        phoneSmsMessage[playerid][0] = '\0';
        SendClientMessage(playerid, COLOR_ERROR, "No se pudo buscar ese numero. Intenta nuevamente.");
        return 1;
    }

    new rows, receiverID;
    cache_get_row_count(rows);
    if (rows < 1)
    {
        phoneSmsPending[playerid] = false;
        phoneSmsMessage[playerid][0] = '\0';
        return SendClientMessage(playerid, COLOR_ERROR, "No existe una cuenta con ese numero de telefono.");
    }
    cache_get_value_name_int(0, "id", receiverID);
    if (receiverID == PI[playerid][jID])
    {
        phoneSmsPending[playerid] = false;
        phoneSmsMessage[playerid][0] = '\0';
        return SendClientMessage(playerid, COLOR_ERROR, "No puedes enviarte un SMS a ti mismo.");
    }

    new query[512];
    mysql_format(dbz, query, sizeof query,
        "INSERT INTO phone_messages (sender_id,receiver_id,body) VALUES (%i,%i,'%e')",
        PI[playerid][jID], receiverID, phoneSmsMessage[playerid]);
    mysql_tquery(dbz, query, "OnPhoneSMSStored", "iii",
        playerid, session, receiverID);
    return 1;
}

forward OnPhoneSMSStored(playerid, session, receiverID);
public OnPhoneSMSStored(playerid, session, receiverID)
{
    if (mysql_errno(dbz) != 0)
    {
        new error[128];
        mysql_error(error, sizeof error, dbz);
        printf("[Phone] Error al guardar SMS: %s", error);
        if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
        {
            phoneSmsPending[playerid] = false;
            phoneSmsMessage[playerid][0] = '\0';
            SendClientMessage(playerid, COLOR_ERROR, "No se pudo guardar el SMS.");
        }
        return 1;
    }

    new targetid = INVALID_PLAYER_ID;
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && IsAccountLoaded(i) && PI[i][jID] == receiverID)
        {
            targetid = i;
            break;
        }
    }
    if (targetid != INVALID_PLAYER_ID && phoneEnabled[targetid])
    {
        if (IsPlayerConnected(playerid) && playerSession[playerid] == session
            && phoneSmsPending[playerid])
        {
            new senderName[MAX_PLAYER_NAME], body[256];
            GetPlayerName(playerid, senderName, sizeof senderName);
            format(body, sizeof body, "SMS de %s (%d): %s", senderName,
                PI[playerid][jPhone], phoneSmsMessage[playerid]);
            SendClientMessage(targetid, COLOR_TWITTER, body);
        }
    }
    if (IsPlayerConnected(playerid) && playerSession[playerid] == session)
    {
        phoneSmsPending[playerid] = false;
        new message[96];
        format(message, sizeof message, "SMS enviado al numero %d.", phoneSmsNumber[playerid]);
        SendClientMessage(playerid, COLOR_GLOBAL, message);
        phoneSmsMessage[playerid][0] = '\0';
    }
    return 1;
}

CMD:mensajes(playerid, params[])
{
    #pragma unused params
    if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
    return LoadPhoneInbox(playerid);
}

stock LoadPhoneInbox(playerid)
{
    new query[384];
    mysql_format(dbz, query, sizeof query,
        "SELECT pm.id,pm.body,pm.sent_at,p.jName AS sender_name,p.jPhone AS sender_phone FROM phone_messages pm INNER JOIN players p ON p.id=pm.sender_id WHERE pm.receiver_id=%i ORDER BY pm.id DESC LIMIT %i",
        PI[playerid][jID], PHONE_INBOX_LIMIT);
    mysql_tquery(dbz, query, "OnPhoneInboxLoaded", "ii", playerid, playerSession[playerid]);
    SendClientMessage(playerid, COLOR_GLOBAL, "Cargando buzon de SMS...");
    return 1;
}

forward OnPhoneInboxLoaded(playerid, session);
public OnPhoneInboxLoaded(playerid, session)
{
    if (!IsPlayerConnected(playerid) || playerSession[playerid] != session) return 1;
    if (mysql_errno(dbz) != 0)
    {
        SendClientMessage(playerid, COLOR_ERROR, "No se pudo abrir el buzon de SMS.");
        return 1;
    }

    new rows, sender[MAX_PLAYER_NAME], body[PHONE_MESSAGE_MAX + 1], message[256], senderPhone, messageID;
    cache_get_row_count(rows);
    if (rows < 1) return SendClientMessage(playerid, COLOR_GLOBAL, "No tienes mensajes guardados.");
    SendClientMessage(playerid, COLOR_TWITTER, "=== BUZON DE SMS (ultimos 10) ===");
    for (new row = 0; row < rows; row++)
    {
        cache_get_value_name_int(row, "id", messageID);
        cache_get_value_name_int(row, "sender_phone", senderPhone);
        cache_get_value_name(row, "sender_name", sender, sizeof sender);
        cache_get_value_name(row, "body", body, sizeof body);
        format(message, sizeof message, "#%d | %s (%d): %s", messageID, sender, senderPhone, body);
        SendClientMessage(playerid, COLOR_GLOBAL, message);
    }
    return 1;
}
