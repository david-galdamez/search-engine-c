//
// Created by mamia on 2/12/2025.
//

#include "searcher.h"
#include <complex>
#include "tokenizer.h"

Searcher::Searcher(const InvertedIndex& idx, int totalDocs) : index(idx), totalDocs(totalDocs) {}

std::unordered_map<int, double> Searcher::calculateTDFIDF(const std::string& word) {
    auto posting = index.queryDocument(word);
    std::unordered_map<int, double> result;

    if (posting.empty()) return result;
    double idf = std::log(static_cast<double>(totalDocs) / static_cast<double>(posting.size()) + 1.0);

    for (const auto& doc : posting) {
        double tf = static_cast<double>(doc.frequency) / static_cast<double>(index.documents[doc.docId].wordCount);
        result[doc.docId] = tf * idf;
    }

    return result;
}

std::vector<std::pair<int, Document>> Searcher::search(const std::string& query) {
    std::unordered_map<int, Document> temp;
    std::vector<std::pair<int, Document>> result;

    auto tokens = tokenizer(query);

    for (const auto& token : tokens) {
        auto calculatedWord = calculateTDFIDF(token);

        for (const auto& [docId, score] : calculatedWord) {
            if (temp.contains(docId)) {
                temp[docId].score += score;
            } else {
                temp[docId] = {
                    .title = index.documents[docId].title,
                    .score = score
                };
            }
        }
    }

    for (const auto& [docId, doc] : temp) {
        result.push_back({docId, doc});
    }

    std::sort(result.begin(),result.end(), [](std::pair<int, Document>& a, std::pair<int, Document>& b) {
        return a.second.score > b.second.score;
    });

    return result;
}