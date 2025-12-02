//
// Created by mamia on 2/12/2025.
//

#include "tokenizer.h"
#include <cctype>

std::vector<std::string> tokenizer(const std::string& text) {
    std::vector<std::string> tokens;
    std::string word;

    for (const char c : text) {
        if (std::isalnum(c)) {
            word.push_back(std::tolower(c));
        } else {
            if (!word.empty()) {
                tokens.push_back(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tokens.push_back(word);
    }

    return tokens;
}