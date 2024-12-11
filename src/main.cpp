#include "MyGrep.hpp"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: MyGrep <search_string> <path>\n";
        return 1; 
    }

    try
    {
        std::cout << MyGrep::getInstance().initialize(argv[2], argv[1]);
    } 
    catch(std::string e)
    {
	std::cerr << e << std::endl;
    }

    return 0;
}
