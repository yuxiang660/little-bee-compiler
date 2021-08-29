#include "lexer/lexer.h"
#include "parser/parser.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char const *argv[])
{
   std::cout << "Little Bee Compiler Test" << std::endl;

   auto dir_path = fs::path("./main/mock");
   auto dir_status = fs::status(dir_path);

   if (!fs::is_directory(dir_status)) {
      std::cout << dir_path << " doesn't exit, please create one for testing." << std::endl;
      return -1;
   }

   for (auto const& dir_entry : fs::directory_iterator { dir_path }) {
      std::string text_path = dir_entry.path().u8string();
      // Print test data
      {
         std::cout << "-------- Test Data in " << text_path << " --------\n";
         std::ifstream data(text_path);
         if (data.is_open()) std::cout << data.rdbuf();
      }
      // Print parsed output
      {
         std::cout << "-------- Compiler Output Begin" << " --------\n";
         std::ifstream code(text_path);
         auto l = LBC::Lexer(code);
         auto parser = LBC::Parser(l);
         parser.program();
         parser.dump();
         std::cout << "-------- Compiler Output End" << " --------\n";
      }
   }

   return 0;
}

