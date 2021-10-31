#include "lexer/lexer.h"
#include "parser/parser.h"
#include "env/env.h"
#include "expr/temp.h"
#include "stmt/stmt.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

static void clean_compiler()
{
   LBC::Env::s_id = 0;
   LBC::Lexer::s_line = 0;
   LBC::TempNode::s_temp_id = 0;
   LBC::Stmt::s_lable_seed = 0;
}

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
      std::string text_path = dir_entry.path().string();
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
         clean_compiler();
      }
   }

   return 0;
}

