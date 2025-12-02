//
// Created by mamia on 2/12/2025.
//

#pragma once
#include <string>
#include <unordered_map>
#include <vector>

struct Posting {
    int docId;
    int frequency;
};

struct DocInfo {
    std::string title;
    int wordCount;
};

class InvertedIndex {
public:
    std::unordered_map<int, DocInfo> documents;
    void addDocument(int docId, const std::string& title, const std::string& text);
    const std::vector<Posting>& queryDocument (const std::string& word);
private:
    std::unordered_map<std::string, std::vector<Posting>> index;
};


