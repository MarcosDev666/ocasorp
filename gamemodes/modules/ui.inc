#include <YSI_Coding\y_hooks>

#define RP_MENU_PAGE_COUNT 10
#define RP_MENU_DRAWS_PER_PAGE 20
#define RP_MENU_DRAW_COUNT (RP_MENU_PAGE_COUNT * RP_MENU_DRAWS_PER_PAGE)
#define RP_MENU_ROW_COUNT 10
#define RP_MENU_ROW_START 4
#define RP_MENU_PREVIOUS 14
#define RP_MENU_HOME 15
#define RP_MENU_NEXT 16
#define RP_MENU_CLOSE 17
#define RP_MENU_HINT 18
#define RP_MENU_FOOTER 19

new PlayerText:RoleplayMenuDraw[MAX_PLAYERS][RP_MENU_DRAW_COUNT];
new bool:roleplayMenuCreated[MAX_PLAYERS];
new bool:roleplayMenuVisible[MAX_PLAYERS];
new roleplayMenuPage[MAX_PLAYERS];
new roleplayMenuPanelSprite[] = "LD_SPAC:white";

stock PlayerText:CreateRoleplayMenuLabel(playerid, Float:x, Float:y, const text[], color, bool:selectable)
{
    new PlayerText:draw = CreatePlayerTextDraw(playerid, x, y, text);
    PlayerTextDrawLetterSize(playerid, draw, 0.19, 0.88);
    PlayerTextDrawColor(playerid, draw, color);
    PlayerTextDrawSetShadow(playerid, draw, 1);
    PlayerTextDrawSetOutline(playerid, draw, 0);
    PlayerTextDrawFont(playerid, draw, 1);
    PlayerTextDrawSetProportional(playerid, draw, 1);
    if (selectable)
    {
        PlayerTextDrawTextSize(playerid, draw, 356.0, 17.0);
        PlayerTextDrawSetSelectable(playerid, draw, true);
    }
    return draw;
}

stock CreateRoleplayMenu(playerid)
{
    for (new page = 0; page < RP_MENU_PAGE_COUNT; page++)
    {
        new base = page * RP_MENU_DRAWS_PER_PAGE;
        RoleplayMenuDraw[playerid][base] = CreatePlayerTextDraw(playerid, 116.0, 74.0, roleplayMenuPanelSprite);
        PlayerTextDrawTextSize(playerid, RoleplayMenuDraw[playerid][base], 408.0, 344.0);
        PlayerTextDrawColor(playerid, RoleplayMenuDraw[playerid][base], 0x101820DD);
        PlayerTextDrawSetShadow(playerid, RoleplayMenuDraw[playerid][base], 0);
        PlayerTextDrawSetOutline(playerid, RoleplayMenuDraw[playerid][base], 0);
        PlayerTextDrawFont(playerid, RoleplayMenuDraw[playerid][base], 4);

        RoleplayMenuDraw[playerid][base + 1] = CreatePlayerTextDraw(playerid, 116.0, 74.0, roleplayMenuPanelSprite);
        PlayerTextDrawTextSize(playerid, RoleplayMenuDraw[playerid][base + 1], 408.0, 34.0);
        PlayerTextDrawColor(playerid, RoleplayMenuDraw[playerid][base + 1], 0xF2FF00FF);
        PlayerTextDrawSetShadow(playerid, RoleplayMenuDraw[playerid][base + 1], 0);
        PlayerTextDrawSetOutline(playerid, RoleplayMenuDraw[playerid][base + 1], 0);
        PlayerTextDrawFont(playerid, RoleplayMenuDraw[playerid][base + 1], 4);

        RoleplayMenuDraw[playerid][base + 2] = CreateRoleplayMenuLabel(playerid, 132.0, 79.0, "OCASO ROLEPLAY", 0x101820FF, false);
        RoleplayMenuDraw[playerid][base + 3] = CreateRoleplayMenuLabel(playerid, 132.0, 112.0, "Panel de sistemas", 0xF4F6F8FF, false);

        for (new row = 0; row < RP_MENU_ROW_COUNT; row++)
        {
            new Float:y = 143.0 + float(row * 19);
            new index = base + RP_MENU_ROW_START + row;
            RoleplayMenuDraw[playerid][index] = CreateRoleplayMenuLabel(
                playerid, 139.0, y, " ", 0xF4F6F8FF, true);
        }

        RoleplayMenuDraw[playerid][base + RP_MENU_PREVIOUS] = CreateRoleplayMenuLabel(
            playerid, 139.0, 339.0, "< ANTERIOR", 0xF2FF00FF, true);
        RoleplayMenuDraw[playerid][base + RP_MENU_HOME] = CreateRoleplayMenuLabel(
            playerid, 235.0, 339.0, "INICIO", 0xF2FF00FF, true);
        RoleplayMenuDraw[playerid][base + RP_MENU_NEXT] = CreateRoleplayMenuLabel(
            playerid, 304.0, 339.0, "SIGUIENTE >", 0xF2FF00FF, true);
        RoleplayMenuDraw[playerid][base + RP_MENU_CLOSE] = CreateRoleplayMenuLabel(
            playerid, 424.0, 339.0, "CERRAR", 0xFF7777FF, true);
        RoleplayMenuDraw[playerid][base + RP_MENU_HINT] = CreateRoleplayMenuLabel(
            playerid, 139.0, 369.0, "Selecciona una opcion para continuar.", 0xFFFFFFFF, false);
        RoleplayMenuDraw[playerid][base + RP_MENU_FOOTER] = CreateRoleplayMenuLabel(
            playerid, 139.0, 391.0, "Click en una fila | ESC para cerrar", 0xAAB4C0FF, false);
    }
    roleplayMenuCreated[playerid] = true;
    roleplayMenuVisible[playerid] = false;
    roleplayMenuPage[playerid] = 0;
    return 1;
}

stock GetRoleplayMenuTitle(page, title[], size)
{
    switch (page)
    {
        case 0: format(title, size, "MENU PRINCIPAL");
        case 1: format(title, size, "MI PERSONAJE");
        case 2: format(title, size, "EMPLEOS | 1 A 10");
        case 3: format(title, size, "EMPLEOS | 11 A 20");
        case 4: format(title, size, "FACCIONES");
        case 5: format(title, size, "TELEFONO");
        case 6: format(title, size, "INVENTARIO Y TIENDAS");
        case 7: format(title, size, "BANCO Y ECONOMIA");
        case 8: format(title, size, "VEHICULOS Y CASAS");
        case 9: format(title, size, "GPS Y AJUSTES");
        default: format(title, size, "OCASO ROLEPLAY");
    }
    return 1;
}

stock GetRoleplayMenuSubtitle(page, subtitle[], size)
{
    switch (page)
    {
        case 0: format(subtitle, size, "Accede a las funciones principales del servidor.");
        case 1: format(subtitle, size, "Resumen de tu cuenta y personaje actual.");
        case 2, 3: format(subtitle, size, "Selecciona un empleo en la agencia con /empleos.");
        case 4: format(subtitle, size, "Facciones, rangos y servicios disponibles.");
        case 5: format(subtitle, size, "Llamadas, SMS y buzon del telefono.");
        case 6: format(subtitle, size, "Articulos, tiendas 24/7 y espacios del inventario.");
        case 7: format(subtitle, size, "Saldo y operaciones disponibles en el banco.");
        case 8: format(subtitle, size, "Concesionario, garage y propiedades.");
        case 9: format(subtitle, size, "Navegacion y preferencias de interfaz.");
        default: format(subtitle, size, "Ocaso Roleplay");
    }
    return 1;
}

stock GetRoleplayMenuRow(playerid, page, row, text[], size)
{
    new playerName[MAX_PLAYER_NAME], jobName[32], factionName[32], itemName[32];
    switch (page)
    {
        case 0:
        {
            switch (row)
            {
                case 0: format(text, size, "Mi personaje");
                case 1: format(text, size, "Empleos 1-10");
                case 2: format(text, size, "Empleos 11-20");
                case 3: format(text, size, "Facciones");
                case 4: format(text, size, "Telefono");
                case 5: format(text, size, "Inventario y tiendas");
                case 6: format(text, size, "Banco y economia");
                case 7: format(text, size, "Vehiculos y casas");
                case 8: format(text, size, "GPS y ajustes");
                case 9: format(text, size, "Ayuda de comandos");
            }
        }
        case 1:
        {
            GetPlayerName(playerid, playerName, sizeof playerName);
            GetJobName(PI[playerid][jJob], jobName, sizeof jobName);
            GetFactionName(PI[playerid][jFaction], factionName, sizeof factionName);
            switch (row)
            {
                case 0: format(text, size, "Nombre: %s", playerName);
                case 1: format(text, size, "ID de cuenta: %d | ID conectado: %d", PI[playerid][jID], playerid);
                case 2: format(text, size, "Genero: %s | Edad: %d", ConvertGenderStr(playerid), PI[playerid][jAge]);
                case 3: format(text, size, "Efectivo: $%d", GetPlayerMoney(playerid));
                case 4: format(text, size, "Banco: $%d", PI[playerid][jBankMoney]);
                case 5: format(text, size, "Empleo: %s", jobName);
                case 6: format(text, size, "Nivel del empleo: %d | Experiencia: %d", PI[playerid][jJobLevel], PI[playerid][jJobXP]);
                case 7: format(text, size, "Faccion: %s | Rango: %d", factionName, PI[playerid][jFactionRank]);
                case 8: format(text, size, "Hambre: %d%% | Sed: %d%%", PI[playerid][jHunger], PI[playerid][jThirst]);
                case 9: format(text, size, "Telefono: %d", PI[playerid][jPhone]);
            }
        }
        case 2, 3:
        {
            new job = row + 1;
            if (page == 3) job += 10;
            GetJobName(job, jobName, sizeof jobName);
            format(text, size, "%02d. %s", job, jobName);
        }
        case 4:
        {
            if (row < FACTION_MAX)
            {
                GetFactionName(row + 1, factionName, sizeof factionName);
                format(text, size, "%d. %s", row + 1, factionName);
            }
            else if (row == 9)
            {
                new rankName[32];
                GetFactionName(PI[playerid][jFaction], factionName, sizeof factionName);
                GetFactionRankName(PI[playerid][jFaction], PI[playerid][jFactionRank], rankName, sizeof rankName);
                format(text, size, "Tu faccion: %s | Rango: %s", factionName, rankName);
            }
        }
        case 5:
        {
            switch (row)
            {
                case 0: format(text, size, "Tu numero: %d", PI[playerid][jPhone]);
                case 1: format(text, size, "Telefono: %s", phoneEnabled[playerid] ? "encendido" : "apagado");
                case 2: format(text, size, "Abrir opciones del telefono");
                case 3: format(text, size, "Llamar: /llamar <numero>");
                case 4: format(text, size, "Enviar SMS: /sms <numero> <mensaje>");
                case 5: format(text, size, "Buzon persistente: /mensajes");
                case 6: format(text, size, "Contestar o finalizar: /contestar /colgar");
                case 7: format(text, size, "El destinatario puede estar desconectado para SMS.");
                case 8: format(text, size, "Las llamadas conectan jugadores en linea.");
                case 9: format(text, size, "Abre /telefono para activar o apagar el equipo.");
            }
        }
        case 6:
        {
            if (!inventoryReady[playerid])
            {
                if (row == 0) format(text, size, "Inventario cargando desde el servidor...");
                else format(text, size, "Espera a que termine la carga del inventario.");
            }
            else if (row < INVENTORY_SLOTS)
            {
                if (inventoryAmounts[playerid][row] > 0)
                {
                    GetInventoryItemName(inventoryItems[playerid][row], itemName, sizeof itemName);
                    format(text, size, "%02d. %s x%d", row + 1, itemName, inventoryAmounts[playerid][row]);
                }
                else format(text, size, "%02d. Espacio vacio", row + 1);
            }
        }
        case 7:
        {
            switch (row)
            {
                case 0: format(text, size, "Efectivo disponible: $%d", GetPlayerMoney(playerid));
                case 1: format(text, size, "Saldo bancario: $%d", PI[playerid][jBankMoney]);
                case 2: format(text, size, "Consultar saldo: /banco");
                case 3: format(text, size, "Ingresar efectivo: /depositar <cantidad>");
                case 4: format(text, size, "Retirar efectivo: /retirar <cantidad>");
                case 5: format(text, size, "Transferir dinero: /transferir");
                case 6: format(text, size, "Las operaciones bancarias requieren estar en el banco.");
                case 7: format(text, size, "Ventas de vehiculos y casas se cobran al contado.");
                case 8: format(text, size, "Controla el saldo antes de iniciar una compra.");
                case 9: format(text, size, "Usa /ayuda para revisar los comandos.");
            }
        }
        case 8:
        {
            switch (row)
            {
                case 0: format(text, size, "Catalogo de vehiculos: /concesionario");
                case 1: format(text, size, "Ver tus vehiculos: /misvehiculos");
                case 2: format(text, size, "Guardar vehiculo en el garage: /guardarveh");
                case 3: format(text, size, "Casas disponibles: /casas");
                case 4: format(text, size, "Compra una casa: /comprarcasa <id>");
                case 5:
                {
                    if (playerHouseID[playerid] > 0 && playerHouseID[playerid] <= HOUSE_COUNT)
                    {
                        format(text, size, "Tu casa: %s", HouseName[playerHouseID[playerid] - 1]);
                    }
                    else format(text, size, "No tienes una casa registrada.");
                }
                case 6: format(text, size, "Interaccion de casas: /entrar y /salir");
                case 7: format(text, size, "Los vehiculos comprados se guardan en garage.");
                case 8: format(text, size, "El limite por cuenta es de tres vehiculos.");
                case 9: format(text, size, "Ve a los puntos indicados para comprar o guardar.");
            }
        }
        case 9:
        {
            switch (row)
            {
                case 0: format(text, size, "HUD: %s (clic para cambiar)", gameplayHUDVisible[playerid] ? "visible" : "oculto");
                case 1: format(text, size, "Telefono: %s (clic para cambiar)", phoneEnabled[playerid] ? "encendido" : "apagado");
                case 2: format(text, size, "GPS y destinos: /gps");
                case 3: format(text, size, "Cancelar una ruta: /quitarGPS");
                case 4: format(text, size, "Ocultar/mostrar informacion: /hud");
                case 5: format(text, size, "Ayuda general: /ayuda");
                case 6: format(text, size, "Ayuda de trabajos e inventario: /ayudagame");
                case 7: format(text, size, "Ayuda de administracion: /ayudaadmin");
                case 8: format(text, size, "Para cerrar esta ventana: boton CERRAR o tecla ESC.");
                case 9: format(text, size, "La configuracion del HUD es de esta sesion.");
            }
        }
    }
    return 1;
}

stock UpdateRoleplayMenuPage(playerid)
{
    new page = roleplayMenuPage[playerid];
    new base = page * RP_MENU_DRAWS_PER_PAGE;
    new title[48], subtitle[96], text[128], status[64];
    GetRoleplayMenuTitle(page, title, sizeof title);
    GetRoleplayMenuSubtitle(page, subtitle, sizeof subtitle);
    PlayerTextDrawSetString(playerid, RoleplayMenuDraw[playerid][base + 2], title);
    PlayerTextDrawSetString(playerid, RoleplayMenuDraw[playerid][base + 3], subtitle);

    for (new row = 0; row < RP_MENU_ROW_COUNT; row++)
    {
        GetRoleplayMenuRow(playerid, page, row, text, sizeof text);
        PlayerTextDrawSetString(playerid,
            RoleplayMenuDraw[playerid][base + RP_MENU_ROW_START + row], text);
    }
    if (page == 0)
    {
        PlayerTextDrawSetString(playerid, RoleplayMenuDraw[playerid][base + RP_MENU_HINT],
            "Elige una categoria; la navegacion no requiere comandos.");
    }
    else
    {
        PlayerTextDrawSetString(playerid, RoleplayMenuDraw[playerid][base + RP_MENU_HINT],
            "Selecciona una fila para ver acciones y comandos.");
    }
    format(status, sizeof status, "PAGINA %d DE %d", page + 1, RP_MENU_PAGE_COUNT);
    PlayerTextDrawSetString(playerid, RoleplayMenuDraw[playerid][base + RP_MENU_FOOTER], status);
    return 1;
}

stock HideRoleplayMenuPage(playerid, page)
{
    new base = page * RP_MENU_DRAWS_PER_PAGE;
    for (new draw = 0; draw < RP_MENU_DRAWS_PER_PAGE; draw++)
    {
        PlayerTextDrawHide(playerid, RoleplayMenuDraw[playerid][base + draw]);
    }
    return 1;
}

stock OpenRoleplayMenuPage(playerid, page)
{
    if (page < 0 || page >= RP_MENU_PAGE_COUNT) page = 0;
    if (!roleplayMenuCreated[playerid]) CreateRoleplayMenu(playerid);
    if (roleplayMenuVisible[playerid]) HideRoleplayMenuPage(playerid, roleplayMenuPage[playerid]);
    roleplayMenuPage[playerid] = page;
    UpdateRoleplayMenuPage(playerid);

    new base = page * RP_MENU_DRAWS_PER_PAGE;
    for (new draw = 0; draw < RP_MENU_DRAWS_PER_PAGE; draw++)
    {
        PlayerTextDrawShow(playerid, RoleplayMenuDraw[playerid][base + draw]);
    }
    roleplayMenuVisible[playerid] = true;
    SelectTextDraw(playerid, 0xF2FF00FF);
    return 1;
}

stock CloseRoleplayMenu(playerid)
{
    if (!roleplayMenuCreated[playerid] || !roleplayMenuVisible[playerid]) return 1;
    HideRoleplayMenuPage(playerid, roleplayMenuPage[playerid]);
    roleplayMenuVisible[playerid] = false;
    CancelSelectTextDraw(playerid);
    return 1;
}

stock ToggleRoleplayHUD(playerid)
{
    if (gameplayHUDVisible[playerid]) HideGameplayHUD(playerid);
    else ShowGameplayHUD(playerid);
    SendClientMessage(playerid, COLOR_GLOBAL,
        gameplayHUDVisible[playerid] ? "HUD visible." : "HUD oculto.");
    UpdateRoleplayMenuPage(playerid);
    return 1;
}

stock ToggleRoleplayPhone(playerid)
{
    phoneEnabled[playerid] = !phoneEnabled[playerid];
    if (!phoneEnabled[playerid]) EndPhoneCall(playerid, true);
    SendClientMessage(playerid, COLOR_GLOBAL,
        phoneEnabled[playerid] ? "Telefono encendido." : "Telefono apagado.");
    UpdateRoleplayMenuPage(playerid);
    return 1;
}

stock ShowRoleplayMenuRowAction(playerid, page, row)
{
    if (page == 5 && row == 1) return ToggleRoleplayPhone(playerid);
    if (page == 5 && row == 2)
    {
        EnsurePlayerPhoneNumber(playerid);
        CloseRoleplayMenu(playerid);
        return ShowPhoneMenu(playerid);
    }
    if (page == 9 && (row == 0 || row == 4)) return ToggleRoleplayHUD(playerid);
    if (page == 9 && row == 1) return ToggleRoleplayPhone(playerid);
    if (page == 9 && row == 2)
    {
        CloseRoleplayMenu(playerid);
        return ShowGPSMenu(playerid);
    }
    if (page == 9 && row == 3)
    {
        CancelGPSRoute(playerid, true);
        return 1;
    }
    if (page == 9 && row == 8) return CloseRoleplayMenu(playerid);

    if (page == 0 && row == 9)
    {
        SendClientMessage(playerid, COLOR_GLOBAL, "Usa /ayuda para ver la lista completa de comandos.");
    }
    else if (page == 1)
    {
        SendClientMessage(playerid, COLOR_GLOBAL, "Este resumen es informativo. Gestiona empleo, telefono y economia desde sus paginas.");
    }
    else if (page == 2 || page == 3)
    {
        SendClientMessage(playerid, COLOR_GLOBAL, "Para elegir este empleo, visita la agencia y usa /empleos.");
    }
    else if (page == 4)
    {
        SendClientMessage(playerid, COLOR_GLOBAL, "Consulta /facciones; para ingresar a una faccion contacta a un administrador.");
    }
    else if (page == 5)
    {
        SendClientMessage(playerid, COLOR_GLOBAL, "Comandos: /llamar, /contestar, /colgar, /sms y /mensajes.");
    }
    else if (page == 6)
    {
        if (!inventoryReady[playerid])
        {
            SendClientMessage(playerid, COLOR_ERROR, "El inventario todavia se esta cargando.");
        }
        else SendClientMessage(playerid, COLOR_GLOBAL, "Usa /inventario, /usar, /comprar y /tienda para gestionar tus objetos.");
    }
    else if (page == 7)
    {
        SendClientMessage(playerid, COLOR_GLOBAL, "Las operaciones de banco se habilitan al acercarte a una sucursal.");
    }
    else if (page == 8)
    {
        SendClientMessage(playerid, COLOR_GLOBAL, "Usa /concesionario, /misvehiculos, /casas o /gps en los puntos correspondientes.");
    }
    else if (page == 9 && row == 5)
    {
        SendClientMessage(playerid, COLOR_GLOBAL, "Usa /ayuda para ver la lista completa de comandos.");
    }
    else if (page == 9 && row == 6)
    {
        SendClientMessage(playerid, COLOR_GLOBAL, "Usa /ayudagame para consultar empleos, facciones e inventario.");
    }
    else if (page == 9 && row == 7)
    {
        SendClientMessage(playerid, COLOR_GLOBAL, "Usa /ayudaadmin para consultar los comandos de tu nivel.");
    }
    else if (page == 9 && row == 9)
    {
        SendClientMessage(playerid, COLOR_GLOBAL, "El ajuste de visibilidad se mantiene mientras dure esta sesion.");
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    roleplayMenuCreated[playerid] = false;
    roleplayMenuVisible[playerid] = false;
    roleplayMenuPage[playerid] = 0;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    #pragma unused reason
    if (roleplayMenuCreated[playerid])
    {
        if (roleplayMenuVisible[playerid]) CancelSelectTextDraw(playerid);
        for (new draw = 0; draw < RP_MENU_DRAW_COUNT; draw++)
        {
            PlayerTextDrawDestroy(playerid, RoleplayMenuDraw[playerid][draw]);
        }
    }
    roleplayMenuCreated[playerid] = false;
    roleplayMenuVisible[playerid] = false;
    roleplayMenuPage[playerid] = 0;
    return 1;
}

CMD:menu(playerid, params[])
{
    #pragma unused params
    if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
    return OpenRoleplayMenuPage(playerid, 0);
}

CMD:panel(playerid, params[])
{
    #pragma unused params
    if (!IsAccountLoaded(playerid)) return SendClientMessage(playerid, COLOR_ERROR, "Primero debes iniciar sesion.");
    return OpenRoleplayMenuPage(playerid, 0);
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if (!roleplayMenuVisible[playerid]) return 1;
    if (_:playertextid == 0xFFFF)
    {
        return CloseRoleplayMenu(playerid);
    }

    new page = roleplayMenuPage[playerid];
    new base = page * RP_MENU_DRAWS_PER_PAGE;
    if (playertextid == RoleplayMenuDraw[playerid][base + RP_MENU_PREVIOUS])
    {
        return OpenRoleplayMenuPage(playerid, page > 0 ? page - 1 : RP_MENU_PAGE_COUNT - 1);
    }
    if (playertextid == RoleplayMenuDraw[playerid][base + RP_MENU_HOME])
    {
        return OpenRoleplayMenuPage(playerid, 0);
    }
    if (playertextid == RoleplayMenuDraw[playerid][base + RP_MENU_NEXT])
    {
        return OpenRoleplayMenuPage(playerid, (page + 1) % RP_MENU_PAGE_COUNT);
    }
    if (playertextid == RoleplayMenuDraw[playerid][base + RP_MENU_CLOSE])
    {
        return CloseRoleplayMenu(playerid);
    }

    for (new row = 0; row < RP_MENU_ROW_COUNT; row++)
    {
        if (playertextid != RoleplayMenuDraw[playerid][base + RP_MENU_ROW_START + row]) continue;
        if (page == 0 && row < RP_MENU_PAGE_COUNT - 1)
        {
            return OpenRoleplayMenuPage(playerid, row + 1);
        }
        return ShowRoleplayMenuRowAction(playerid, page, row);
    }
    return 1;
}
