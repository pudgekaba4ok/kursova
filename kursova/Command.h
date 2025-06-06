#ifndef COMMAND_H
#define COMMAND_H

class Game; 

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(Game& game) = 0;
};

// Concrete Commands:
class ReturnToMainMenuCommand : public Command {
public:
    void execute(Game& game) override;
};

class NewGameCommand : public Command {
public:
    void execute(Game& game) override;
};
class EasyDifficultyCommand : public Command {
public:
    void execute(Game& game) override;
};

class MediumDifficultyCommand : public Command {
public:
	void execute(Game& game) override;
};

class HardDifficultyCommand : public Command {
public:
	void execute(Game& game) override;
};


class ContinueGameCommand : public Command {
public:
    void execute(Game& game) override;
};

class ShowStatsCommand : public Command {
public:
    void execute(Game& game) override;
};

class ShowSettingsCommand : public Command {
public:
    void execute(Game& game) override;
};

class ResumeGameCommand : public Command {
public:
	void execute(Game& game) override;
};

class ExitCommand : public Command {
public:
    void execute(Game& game) override;
};

#endif // COMMAND_H
