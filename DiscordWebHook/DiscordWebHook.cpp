#include "curl/curl.h"

#include "DiscordWebHook.h"

#define API_URL "https://discord.com/api/v9/webhooks"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Discord::WebHook::setId(const char* id) {
    this->id = id;
}

void Discord::WebHook::setToken(const char* token) {
    this->token = token;
}

void Discord::WebHook::embed::setTitle(const char* title) {
   this->title = title; 
}

void Discord::WebHook::embed::setDescription(const char* description) {
    this->description = description;
}

void Discord::WebHook::embed::setURL(const char* URL) {
    this->URL = URL;
}

void Discord::WebHook::embed::setColor(int color) {
    this->color = color;
}

void Discord::WebHook::embed::addField(const char* name, const char* value, bool inLine) {
    Discord::WebHook::embedFields field;
    field.name = name;
    field.value = value;
    field.inLine = inLine;
    this->fields.push_back(field);
}

const char* Discord::WebHook::embed::getTitle() {
    return this->title;
}

const char* Discord::WebHook::embed::getDescription() {
    return this->description;
}

const char* Discord::WebHook::embed::getURL() {
    return this->URL;
}

std::vector<Discord::WebHook::embedFields> Discord::WebHook::embed::getFields() {
    return this->fields;
}

int Discord::WebHook::embed::getColor() {
    return this->color;
}

void Discord::WebHook::send(std::variant<const char*, Discord::WebHook::embed> value) {
    if(this->id == nullptr || this->token == nullptr) return;
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        char url[150];
        sprintf_s(url, sizeof(url), "%s/%s/%s", API_URL, this->id, this->token);

        char postFields[1000];
        switch(value.index()) {
            case 0: {
                const char* content = std::get<const char*>(value);
                sprintf_s(postFields, sizeof(postFields), "{\"content\":\"%s\"}", content);
                break;
            }
            case 1: {
                Discord::WebHook::embed embed = std::get<Discord::WebHook::embed>(value);
                char embedFields[500];
                sprintf_s(embedFields, sizeof(embedFields), "[");
                bool first = true;
                for(auto value : embed.getFields()) {
                    sprintf_s(embedFields, sizeof(embedFields), "%s%s{\"name\": \"%s\", \"value\": \"%s\", \"inline\": %s}", embedFields, !first ? "," : "", value.name, value.value, value.inLine ? "true" : "false");
                    if(first) first = false;
                }
                sprintf_s(embedFields, sizeof(embedFields), "%s]", embedFields);
                sprintf_s(postFields, sizeof(postFields), "{\"embeds\": [{\"title\": \"%s\", \"description\": \"%s\", \"url\": \"%s\", \"color\": %d, \"fields\": %s}]}", embed.getTitle(), embed.getDescription(), embed.getURL(), embed.getColor(), embedFields);
                break;
            }
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        std::cout << readBuffer << std::endl;
    }
}