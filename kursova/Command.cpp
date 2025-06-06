#include "Command.h"
#include "Game.h"

// Start a brand-new game (random seed)
void NewGameCommand::execute(Game& game) {
    game.startNewGame();
}

void EasyDifficultyCommand::execute(Game& game) {
	game.setSelectedDifficulty(LevelFactory::Difficulty::Easy);
	game.startNewGame();
}

void MediumDifficultyCommand::execute(Game& game) {
	game.setSelectedDifficulty(LevelFactory::Difficulty::Medium);
	game.startNewGame();
}

void HardDifficultyCommand::execute(Game& game) {
	game.setSelectedDifficulty(LevelFactory::Difficulty::Hard);
	game.startNewGame();
}

// Continue the current game (if not over)
void ContinueGameCommand::execute(Game& game) {
    game.continueGame();
}

// Show statistics UI
void ShowStatsCommand::execute(Game& game) {
    game.showStats();
}

// Show settings UI
void ShowSettingsCommand::execute(Game& game) {
    game.showSettings();
}

// Exit the application
void ExitCommand::execute(Game& game) {
    game.exitGame();
}

void ReturnToMainMenuCommand::execute(Game& game) {
	while (game.hasOngoingGame()) {
		game.popState(); 
	}
	game.changeState(Game::StateID::MainMenu);
}

void ResumeGameCommand::execute(Game& game) {
	game.popState(); 
}
