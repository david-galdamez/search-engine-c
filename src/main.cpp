#include <iostream>
#include <fstream>
#include <filesystem>
#include "inverted_index.h"
#include "searcher.h"

int main() {

    InvertedIndex index;
    int docId = 0;

    for (const auto& file : std::filesystem::directory_iterator("data/docs")) {
        std::ifstream in(file.path());
        std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

        index.addDocument(++docId, file.path().filename().string(), text);
    }

    Searcher searcher(index, static_cast<int>(index.documents.size()));

    std::cout << "Searcher ready! Type something: " << std::endl;

    std::string query;
    while (true) {
        std::cout << "> ";
        std::cin >> query;

        auto results = searcher.search(query);

        if (results.empty()) {
            std::cout << "No documents found!" << std::endl;
        }else {
            for (auto& [id, document ] : results) {
               std::cout << "Document " << id << " - Title: " << document.title << " - Score: " << document.score << std::endl;
            }
        }
    }
}