#include "DiscordWebHook/DiscordWebHook.h"
using namespace Discord;

int main() 
{
    WebHook hook;
    hook.setId("997155650423500840");
    hook.setToken("Nl7h1CRugWo06od1GpMZ_UhyKvGI2OtdO65Pk-ivbIfj_tYWGCNpX7iTYab-LqNWcCoK");
    WebHook::embed embed;
    embed.setTitle("Test");
    embed.setDescription("Functioneaza");
    embed.setURL("https://pe-promenada.agency/discord");
    embed.setColor(0xAA1144);
    embed.addField("Nume1", "Valoare1");
    embed.addField("Nume2", "Valoare2");
    hook.send(embed);
    return 0;
}