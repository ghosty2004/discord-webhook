#include "DiscordWebHook.h"
#include "cpr/cpr.h"

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

	cpr::Header header = cpr::Header{{"Content-Type", "application/json"}};
    cpr::Url url = cpr::Url{API_URL, "/", id, "/", token};

    cpr::Body postFields;
    switch(value.index()) {
        case 0: {
            const char* content = std::get<const char*>(value);
			postFields = cpr::Body{R"({"content":")", content, R"("})"};
            break;
        }
        case 1: {
            Discord::WebHook::embed embed = std::get<Discord::WebHook::embed>(value);
			std::string embedFields = "[";
            bool first = true;
            for(auto field : embed.getFields()) {
				if (first) {
					embedFields += R"({"name": ")" + std::string(field.name) + R"(", "value: ")" + field.value + R"(", "inline": )" + (field.inLine ? "true}" : "false}");
					first = false;
				} else {
					embedFields += R"(,{"name": ")" + std::string(field.name) + R"(", "value: ")" + field.value + R"(", "inline": )" + (field.inLine ? "true}" : "false}");
				}

            }
			embedFields += "]";
            postFields = cpr::Body{R"({"embeds": [{"title": ")", embed.getTitle(), R"(", "description": ")", embed.getDescription(), R"(", "url": ")", embed.getURL(), R"(", "color": )", std::to_string(embed.getColor()), R"(, "fields": )", embedFields};
			break;
        }
    }

	cpr::Response response = cpr::Post(url, postFields, header, cpr::VerifySsl{false});
    std::cout << response.text << std::endl;
}