# Discord Webhook

Examples

- See *main.cpp*

```cpp
// Send a simple content
int main() 
{
    WebHook hook;
    hook.setId("WebHook Id");
    hook.setToken("WebHook Token");
    hook.send("A Simple Text From C++");
    return 0;
}
```

```cpp
// Send a simple embed
int main() 
{
    WebHook hook;
    hook.setId("WebHook Id");
    hook.setToken("WebHook Token");
    WebHook::embed embed;
    embed.setTitle("Embed Title");
    embed.setDescription("Embed Description");
    embed.setURL("Embed URL");
    embed.setColor(0xAA1144);
    embed.addField("Property Name 1", "Value 1");
    embed.addField("Property Name 2", "Value 2");
    hook.send(embed);
    return 0;
}
```
