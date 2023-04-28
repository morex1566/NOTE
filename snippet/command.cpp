#include <memory>
#include <vector>
#include <iostream>

class Command
{
public:
    virtual ~Command() = default;

private:
    enum class CommandState
    {
        WALK,
        Run
    };

public:
    template <typename T> using IsCommand = std::enable_if_t<std::is_base_of_v<Command, T>, Command>;
    template <typename T, typename U = IsCommand<T>> void AddCommand()
    {
        commands.push_back(std::make_shared<T>());
    }

    virtual void Execute() = 0;
    void Update()
    {
        while(!commands.empty())
        {
            commands.back().lock()->Execute();
            commands.pop_back();
        }
    }
    
private:
    static std::vector<std::weak_ptr<Command>> commands;
};

class Walk : public Command
{
public:
    void Execute() override
    {
        std::cout << "walk" << std::endl;
    }
};

class Run : public Command
{
    void Execute() override
    {
        std::cout << "run" << std::endl;

    }
};

int main(int argc, char* argv[])
{
    std::unique_ptr<Command> command;
    command->AddCommand<Run>();
    command->AddCommand<Walk>();

    std::unique_ptr<Command> command2;

    command2->Update();
    
    return 0;
}
