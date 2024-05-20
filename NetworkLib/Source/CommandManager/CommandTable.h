#include <memory>
#include <stdexcept>
#include <unordered_map>
#include "ICommand.h"
#include "Events/Exceptions/CommandManagerExceptions.h"

namespace CommandManager
{
    void RegisterCommands();

    class CommandTable {
    public:
        using CommandCreator = std::function<std::unique_ptr<ICommand>()>;

        static CommandTable& Instance() {
            static CommandTable instance;
            return instance;
        }

        void RegisterCommand(const int pattern, CommandCreator creator) {
            creators_[pattern] = std::move(creator);
        }

        std::unique_ptr<ICommand> CommandLookup(const int pattern) const {
            auto it = creators_.find(pattern);
            if (it != creators_.end()) {
                return it->second();
            }
            return nullptr;
        }

    private:
        CommandTable() = default;
        std::unordered_map<INT8, CommandCreator> creators_;
    };
}