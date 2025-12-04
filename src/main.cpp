#include <iostream>
#include <fstream>
#include <filesystem>
#include "inverted_index.h"
#include "searcher.h"
#include "httplib.h"
#include <nlohmann/json.hpp>

int main() {

    httplib::Server svr;
    InvertedIndex index;
    int docId = 0;

    for (const auto& file : std::filesystem::directory_iterator("data/docs")) {
        std::ifstream in(file.path());
        std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

        index.addDocument(++docId, file.path().filename().string(), text);
    }

    svr.set_logger([](const httplib::Request& req, const httplib::Response& res) {
      std::cout << req.method << " " << req.path << " -> " << res.status << std::endl;
    });

    svr.Get("/search", [index](const httplib::Request& req, httplib::Response& res) {

        nlohmann::json response;

        if (req.has_param("q")) {
            Searcher searcher(index, static_cast<int>(index.documents.size()));

            auto val = req.get_param_value("q");
            auto results = searcher.search(val);

            if (results.empty()) {
                response["message"] = "No results found";

                res.set_content(response.dump(4), "application/json");
                res.status = httplib::StatusCode::OK_200;
                return;
            }

            for (auto& [id, doc] : results) {
                response["message"] = "Results found";
                response["data"].push_back({
                    {"id", id},
                     {"title", doc.title},
                     {"score", doc.score}
                });
            }
            res.set_content(response.dump(4), "application/json");
            res.status = httplib::StatusCode::OK_200;
            return;
        }

        response["message"] = "No results found";
        res.set_content(response.dump(4), "application/json");
        res.status = httplib::StatusCode::BadRequest_400;
    });

    /*

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
    */

    svr.listen("0.0.0.0", 8080);
}