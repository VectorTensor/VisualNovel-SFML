#include "DialogueManager.hpp"
#include <iostream>
#include <fstream>

DialogueManager::DialogueManager() : currentEntryIndex(0), dialogueComplete(false) {
    // Initialize with empty script
    currentScript = std::make_unique<DialogueScript>();
}

DialogueManager::~DialogueManager() {
    // Clean up resources if needed
}

bool DialogueManager::loadDialogueFromFile(const std::string& filename) {
    try {
        // Load YAML file
        YAML::Node config = YAML::LoadFile(filename);

        // Reset current state
        currentScript = std::make_unique<DialogueScript>();
        currentEntryIndex = 0;
        dialogueComplete = false;

        // Get script name
        if (config["name"])
            currentScript->name = config["name"].as<std::string>();
        else
            currentScript->name = "Unnamed Script";

        // Process dialogue entries
        if (config["dialogue"] && config["dialogue"].IsSequence()) {
            for (const auto& entry : config["dialogue"]) {
                DialogueEntry dialogueEntry;

                // Get speaker name
                if (entry["speaker"])
                    dialogueEntry.speaker = entry["speaker"].as<std::string>();
                else
                    dialogueEntry.speaker = "";

                // Get dialogue text
                if (entry["text"])
                    dialogueEntry.text = entry["text"].as<std::string>();
                else
                    dialogueEntry.text = "";

                // Get character image path
                if (entry["image"])
                    dialogueEntry.characterImage = entry["image"].as<std::string>();
                else
                    dialogueEntry.characterImage = "";

                // Get character position
                if (entry["position"])
                    dialogueEntry.position = entry["position"].as<std::string>();
                else
                    dialogueEntry.position = "center"; // Default position

                // Get character emotion
                if (entry["emotion"])
                    dialogueEntry.emotion = entry["emotion"].as<std::string>();
                else
                    dialogueEntry.emotion = "neutral"; // Default emotion

                // Get choices if any
                if (entry["choices"] && entry["choices"].IsSequence()) {
                    for (const auto& choice : entry["choices"]) {
                        if (choice["text"]) {
                            std::string choiceText = choice["text"].as<std::string>();
                            dialogueEntry.choices.push_back(choiceText);

                            // If there's a branch target, add it to branches map
                            if (choice["goto"]) {
                                int gotoIndex = choice["goto"].as<int>();
                                currentScript->branches[choiceText] = gotoIndex;
                            }
                        }
                    }
                }

                // Add entry to script
                currentScript->entries.push_back(dialogueEntry);
            }
        }

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading dialogue file: " << e.what() << std::endl;
        return false;
    }
}

DialogueEntry DialogueManager::getCurrentEntry() const {
    if (currentScript && currentEntryIndex < currentScript->entries.size()) {
        return currentScript->entries[currentEntryIndex];
    }

    // Return empty entry if we're at the end or have no script
    return DialogueEntry();
}

bool DialogueManager::advanceDialogue() {
    if (!currentScript || currentEntryIndex >= currentScript->entries.size() - 1) {
        dialogueComplete = true;
        return false;
    }

    // Only advance if we're not at a choice point or if choices were handled
    if (!isAtChoicePoint() || currentScript->entries[currentEntryIndex].choices.empty()) {
        currentEntryIndex++;
        return true;
    }

    return false;
}

bool DialogueManager::selectChoice(const std::string& choiceText) {
    if (!isAtChoicePoint()) {
        return false;
    }

    // Look for branch target for this choice
    auto branchIt = currentScript->branches.find(choiceText);
    if (branchIt != currentScript->branches.end()) {
        // Jump to target index
        if (branchIt->second < currentScript->entries.size()) {
            currentEntryIndex = branchIt->second;
            return true;
        }
    }
    else {
        // If no branch target, just advance to next entry
        return advanceDialogue();
    }

    return false;
}

bool DialogueManager::isAtChoicePoint() const {
    if (!currentScript || currentEntryIndex >= currentScript->entries.size()) {
        return false;
    }

    return !currentScript->entries[currentEntryIndex].choices.empty();
}

bool DialogueManager::isDialogueComplete() const {
    return dialogueComplete;
}

void DialogueManager::resetDialogue() {
    currentEntryIndex = 0;
    dialogueComplete = false;
}
