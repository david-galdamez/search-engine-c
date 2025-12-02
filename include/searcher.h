//
// Created by mamia on 2/12/2025.
//

#pragma once
#include "inverted_index.h"

struct Document {
    std::string title;
    double score;
};

class Searcher {
public:
    Searcher(const InvertedIndex& idx, int totalDocs);
    std::vector<std::pair<int, Document>> search(const std::string& query);
    std::unordered_map<int, double> calculateTDFIDF(const std::string& word);
private:
    InvertedIndex index;
    int totalDocs;
};