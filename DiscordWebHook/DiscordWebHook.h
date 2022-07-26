#include <iostream>
#include <variant>
#include <vector>

namespace Discord
{
    class WebHook 
    {
        private:
            const char* id = nullptr;
            const char* token = nullptr;
        public:
            void setId(const char* id);
            void setToken(const char* token);
            class embedFields
            {
                public:
                    const char* name = nullptr;
                    const char* value = nullptr;
                    bool inLine = false;
            };
            class embed
            {
                private:
                    const char* title = nullptr;
                    const char* description = nullptr;
                    const char* URL = nullptr;
                    int color = 0;
                    std::vector<embedFields> fields;
                public:
                    void setTitle(const char* title);
                    void setDescription(const char* description);
                    void setURL(const char* URL);
                    void setColor(int color);
                    void addField(const char* name, const char* value, bool inLine = false);
                    const char* getTitle();
                    const char* getDescription();
                    const char* getURL();
                    std::vector<embedFields> getFields();
                    int getColor();
            };
            void send(std::variant<const char*, embed> value);
    };
}