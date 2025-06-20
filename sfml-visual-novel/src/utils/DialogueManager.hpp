#ifndef DIALOGUEMANAGER_HPP
#define DIALOGUEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <yaml-cpp/yaml.h>
#include <string>
#include <vector>
#include <map>
#include <memory>

// Struct to hold a single dialogue entry
struct DialogueEntry {
    std::string speaker;       // Character speaking
    std::string text;          // The actual dialogue text
    std::string characterImage; // Path to character image
    std::string position;      // Position of character (left, right, center)
    std::string emotion;       // Emotion/expression of character
    std::vector<std::string> choices; // Choices player can make, if any
};

// Struct to hold dialogue script information
struct DialogueScript {
    std::string name;
    std::vector<DialogueEntry> entries;
    std::map<std::string, int> branches; // Maps choice text to entry index
};

class DialogueManager {
public:
    DialogueManager();
    ~DialogueManager();

    // Load a dialogue script from a YAML file
    bool loadDialogueFromFile(const std::string& filename);

    // Get the current dialogue entry
    DialogueEntry getCurrentEntry() const;

    // Advance to the next dialogue entry
    bool advanceDialogue();

    // Handle player choice selection
    bool selectChoice(const std::string& choiceText);

    // Check if we're at a choice point
    bool isAtChoicePoint() const;

    // Check if dialogue is complete
    bool isDialogueComplete() const;

    // Reset dialogue back to beginning
    void resetDialogue();

private:
    std::unique_ptr<DialogueScript> currentScript;
    int currentEntryIndex;
    bool dialogueComplete;
};

#endif // DIALOGUEMANAGER_HPP
