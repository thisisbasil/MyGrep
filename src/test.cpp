#include "MyGrep.hpp"
#include <gtest/gtest.h>

class MyGrepTest : public testing::Test
{
private:
protected:
    MyGrepTest() 
    {
        std::filesystem::create_directories("test_dir/dir1/dir1_2");
        std::filesystem::create_directories("test_dir/dir1/dir1_2");
        std::filesystem::create_directories("test_dir/dir2");
        std::filesystem::create_directory("empty_dir");
        std::filesystem::create_directory("loads_of_files");

        std::ofstream file;

        file.open("test_dir/dir1/file1");
        file << "this is a file with some text in it\n";
        file.close();

        file.open("test_dir/dir1/dir1_2/file1_2");
        for (int j = 0; j < 100; ++j)
        { 
            for (int i = 0; i < 5000; ++i)
            {
                file << "this is a very large file that has a very large amount of text inside of it\n";
            }
            file << "random text\n";
	}
        file.close();
        
        for (int i = 0; i < 400; ++i)
        {
            std::string temp = "loads_of_files/file";
            temp += std::to_string(i);
            file.open(temp);
            file << "there are loads of duplicate files here\n";
            file.close();
        }
    }

    ~MyGrepTest() override
    {
        //std::filesystem::remove_all("test_dir");
        //std::filesystem::remove_all("empty_dir");
        //std::filesystem::remove_all("loads_of_files");
    }
    
};

TEST_F(MyGrepTest, match)
{
    auto out = MyGrep::getInstance().initialize("test_dir", "text");
    EXPECT_EQ(out.empty(), false);
}

TEST_F(MyGrepTest, nofiles)
{
    EXPECT_EQ(MyGrep::getInstance().initialize("empty_dir", ""), "");
}

TEST_F(MyGrepTest, badpath)
{
    std::string s;
    try
    {
        MyGrep::getInstance().initialize("DOES NOT EXIST","NO");
    } catch (std::string e)
    {
        s = e;
    }
    
    EXPECT_EQ(s.empty(), false);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
