#include <iostream>
#include <iris.hpp>
#include <common/folder.hpp>

[[nodiscard]] inline bool is_alphanumeric(const std::string& str)
{
    switch(str[0])
    {
        case alpha:
        break;
        default:
            return false;
    }
    for(const char c : str)
        switch(c)
        {
            case alphanumeric:
            break;
            default:
                return false;
        }
    return true;
}

inline void create_project(const std::string& pn)
{
    if(not iris::folder::create(pn))
        std::cout << iris::db::error + "error(cl9)" + iris::db::normal + ": the project folder " + iris::db::file + pn + iris::db::normal + " couldn't be created";
    else
    {
        const std::string bf = pn + '/', df = bf + "docs", lf = bf + "libs", of = bf + "out", rf = bf + "res", sf = bf + "src", bfi = bf + pn + '.', sfi = bfi + "sclera", cfi = bfi + "cornea";
        if(not iris::folder::create(df))
            std::cout << iris::db::error + "error(cl10)" + iris::db::normal + ": the documentation folder " + iris::db::file + df + iris::db::normal + " couldn't be created";
        else if(not iris::folder::create(lf))
            std::cout << iris::db::error + "error(cl11)" + iris::db::normal + ": the libraries folder " + iris::db::file + lf + iris::db::normal + " couldn't be created";
        else if(not iris::folder::create(of))
            std::cout << iris::db::error + "error(cl12)" + iris::db::normal + ": the output folder " + iris::db::file + of + iris::db::normal + " couldn't be created";
        else if(not iris::folder::create(rf))
            std::cout << iris::db::error + "error(cl13)" + iris::db::normal + ": the resources folder " + iris::db::file + rf + iris::db::normal + " couldn't be created";
        else if(not iris::folder::create(sf))
            std::cout << iris::db::error + "error(cl14)" + iris::db::normal + ": the source folder " + iris::db::file + sf + iris::db::normal + " couldn't be created";
        else if(not iris::file::create(sfi))
            std::cout << iris::db::error + "error(cl15)" + iris::db::normal + ": the Sclera file " + iris::db::file + sfi + iris::db::normal + " couldn't be created";
        else if(not iris::file::write(cfi, "name = " + pn + ";\nversion = 0.0.1;\n\nmy_unit\n{\n    \n}"))
            std::cout << iris::db::error + "error(cl16)" + iris::db::normal + ": the Cornea file " + iris::db::file + cfi + iris::db::normal + " couldn't be created";
        else
            std::cout << "the project " + iris::db::sequence + pn + iris::db::normal + " were successfully created";
    }
}

inline void clear()
{
    iris::db::output_log.clear();
    iris::db::indentation = 4ull;
    iris::db::measure_unit = iris::measurement::microseconds;
    iris::db::compiler_version = "0.0.1";
    iris::db::_0_0_1::units.clear();
    iris::db::_0_0_1::project_name = "project";
}

inline void compile_project()
{
    if(not iris::folder::exists(iris::db::project_folder))
        std::cout << iris::db::error + "error(cl18)" + iris::db::normal + ": the project folder " + iris::db::file + iris::db::project_folder + iris::db::normal + " couldn't be found";
    else if(not iris::folder::exists(iris::db::documentation_folder))
        std::cout << iris::db::error + "error(cl19)" + iris::db::normal + ": the documentation folder " + iris::db::file + iris::db::documentation_folder + iris::db::normal + " couldn't be found";
    else if(not iris::folder::exists(iris::db::libraries_folder))
        std::cout << iris::db::error + "error(cl20)" + iris::db::normal + ": the libraries folder " + iris::db::file + iris::db::libraries_folder + iris::db::normal + " couldn't be found";
    else if(not iris::folder::exists(iris::db::output_folder))
        std::cout << iris::db::error + "error(cl21)" + iris::db::normal + ": the output folder " + iris::db::file + iris::db::output_folder + iris::db::normal + " couldn't be found";
    else if(not iris::folder::exists(iris::db::resource_folder))
        std::cout << iris::db::error + "error(cl22)" + iris::db::normal + ": the resources folder " + iris::db::file + iris::db::resource_folder + iris::db::normal + " couldn't be found";
    else if(not iris::folder::exists(iris::db::source_folder))
        std::cout << iris::db::error + "error(cl23)" + iris::db::normal + ": the source folder " + iris::db::file + iris::db::source_folder + iris::db::normal + " couldn't be found";
    else if(not iris::file::exists(iris::db::cornea_file))
        std::cout << iris::db::error + "error(cl24)" + iris::db::normal + ": the Cornea file " + iris::db::file + iris::db::cornea_file + iris::db::normal + " couldn't be found";
    else if(not iris::file::exists(iris::db::sclera_file))
        std::cout << iris::db::error + "error(cl25)" + iris::db::normal + ": the Sclera file " + iris::db::file + iris::db::sclera_file + iris::db::normal + " couldn't be found";
    else
    {
        iris::compile();
        iris::db::output_log += "\n\npress 'r' to recompile or any other key to exit, and then hit 'enter':\n";
        std::cout << iris::db::output_log;
        char console_input;
        std::cin >> console_input;
        if(console_input == 'r')
        {
            clear();
            compile_project();
        }
    }
}

int main(int argc, char** argv)
{
    switch(argc)
    {
        case 2:
        {
            std::string option(argv[1]);
            std::cout << (option == "version" ? iris::db::actual_compiler_version : option == "create" ? (iris::db::error + "error(cl3)" + iris::db::normal + ": empty project name after the " + iris::db::sequence + "create" + iris::db::normal + " command") : option == "compile" ? (iris::db::error + "error(cl4)" + iris::db::normal + ": empty project name after the " + iris::db::sequence + "compile" + iris::db::normal + " command") : (iris::db::error + "error(cl5)" + iris::db::normal + ": found " + iris::db::sequence + option + iris::db::normal + ", expected " + iris::db::sequence + "version" + iris::db::normal));
        }
        break;
        case 3:
            if(std::string(argv[1]) == "create")
            {
                const std::string pn(argv[2]);
                if(not is_alphanumeric(pn))
                    std::cout << iris::db::error + "error(cl7)" + iris::db::normal + ": the project name " + iris::db::sequence + pn + iris::db::normal + " isn't an alphanumeric sequence";
                else if(iris::folder::exists(pn))
                    std::cout << iris::db::error + "error(cl8)" + iris::db::normal + ": the project with the name " + iris::db::sequence + pn + iris::db::normal + " already exists at the current directory";
                else
                    create_project(pn);
            }
            else if(std::string(argv[1]) == "compile")
            {
                if(not is_alphanumeric(std::string(argv[2])))
                    std::cout << iris::db::error + "error(cl17)" + iris::db::normal + ": the project name " + iris::db::sequence + argv[2] + iris::db::normal + " isn't an alphanumeric sequence";
                else
                {
                    iris::db::project_folder = std::string(argv[2]);
                    iris::db::documentation_folder = iris::db::project_folder + "/docs";
                    iris::db::libraries_folder = iris::db::project_folder + "/libs";
                    iris::db::output_folder = iris::db::project_folder + "/out";
                    iris::db::resource_folder = iris::db::project_folder + "/res";
                    iris::db::source_folder = iris::db::project_folder + "/src";
                    iris::db::cornea_file = iris::db::project_folder + '/' + iris::db::project_folder + ".cornea";
                    iris::db::sclera_file = iris::db::project_folder + '/' + iris::db::project_folder + ".sclera";
                    compile_project();
                }
            }
            else
                std::cout << iris::db::error + "error(cl6)" + iris::db::normal + ": found " + iris::db::sequence + std::string(argv[1]) + iris::db::normal + ", expected " + iris::db::sequence + "create" + iris::db::normal + " or " + iris::db::sequence + "compile" + iris::db::normal;
        break;
        case 1:
            std::cout << iris::db::error + "error(cl1)" + iris::db::normal + ": no arguments";
        break;
        default:
            std::cout << iris::db::error + "error(cl2)" + iris::db::normal + ": too many arguments";
        break;
    }
}