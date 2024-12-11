#include <filesystem>
#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
#include <queue>
#include <string>
#include <mutex>
#include <sstream>

class MyGrep
{
private:
    static std::queue<std::filesystem::path> files;
    static std::mutex q_mtx;
    static std::mutex out_mtx;
    static std::stringstream output;
    static std::regex r;

    static void grep(const std::string& search)
    {
    	while (true)
	{
            std::filesystem::path file;
            {
                std::lock_guard<std::mutex> lock(q_mtx);
            	if (files.empty()) break;
            	file = files.front();
	    	files.pop();
	    }
            std::cout << "looking at " << file << std::endl;
	    std::ifstream inFile;
            inFile.open(file.string());
            std::string line;
            bool match = false;

            while (inFile.good() && !match)
            {
                while (std::getline(inFile, line) && !match)
                {
                    match = regex_search(line, r);
                }
            }
	    inFile.close();
            if (match) 
            {
                 std::lock_guard<std::mutex> lock(out_mtx);
                 output << file << " matches the search string\n";
            }
        }
    }

public:
    static MyGrep& getInstance() 
    {
       static MyGrep _instance;
       return _instance;
    }

    static std::string initialize(const std::filesystem::path& init, 
                                        std::string search)
    {
        auto coreCount = std::thread::hardware_concurrency() - 1;
        r = std::regex(search);
        output = std::stringstream();
        if (!std::filesystem::is_directory(init))
        {
            std::string temp = init.string();
            temp += " cannot be initialized\n";
            throw temp;
        }
        for (const auto& item : std::filesystem::recursive_directory_iterator(init))
        {
            if (std::filesystem::is_regular_file(item)) files.push(item);
        }
        std::vector<std::thread> threads; 
        while (coreCount--)
	{
           threads.push_back(std::thread(grep, search)); 
	}
	for (auto& thread : threads) thread.join();
        return std::string(output.str());
    }
};

std::queue<std::filesystem::path> MyGrep::files;
std::mutex MyGrep::q_mtx;
std::mutex MyGrep::out_mtx;
std::stringstream MyGrep::output;
std::regex MyGrep::r;
