//
// Created by mamia on 2/12/2025.
//

#include "inverted_index.h"
#include "tokenizer.h"

void InvertedIndex::addDocument(const int docId, const std::string& title, const std::string& text) {
    const auto tokens = tokenizer(text);
    int wordCount = tokens.size();

    documents[docId] = { .title = title, .wordCount = wordCount };

    std::unordered_map<std::string, int> freq;

    for (const auto& token : tokens) {
        freq[token]++;
    }

    for (const auto& [word, count] : freq) {
        index[word].push_back({
        .docId = docId, .frequency = count});
    }
}

const std::vector<Posting>& InvertedIndex::queryDocument(const std::string& word)  {
    static const std::vector<Posting> empty;

    if (const auto it = index.find(word); it != index.end())
        return it->second;

    return empty;
}