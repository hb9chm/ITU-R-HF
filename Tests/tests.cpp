#include <gtest/gtest.h>

#include <array>
#include <fstream>
#include <filesystem>

namespace
{
    enum class Decile
    {
        Lower,
        Upper
    };
    enum class Season
    {
        Winter,
        Equinox,
        Summer
    };
    enum class R12
    {
        Less50,
        Less100,
        Greater100
    };

    struct Row
    {
        double LatDeg;
        std::array<double, 24> values;
    };

    struct Table
    {
        Decile decile;
        Season season;
        R12 r12;
        std::array<Row, 19> rows;
    };

    std::array<Table, 18> tables;

    void readData(const std::string &filename)
    {

        std::ifstream file(filename);
        std::string line;

        // Skip the first 2 lines (header)
        std::getline(file, line);
        std::getline(file, line);

        size_t tableIndex = 0;

        auto findStr = [](const std::string& line, const std::string& toFind)
        {
            return line.find(toFind) != std::string::npos;
        };

        for (auto& table : tables)
        {
            std::getline(file, line);
            std::getline(file, line);

            //This defines the table.
            table.decile = findStr(line, "lower decile") ? Decile::Lower : Decile::Upper;
            table.season = findStr(line, "winter") ? Season::Winter : findStr(line, "equinox") ? Season::Equinox : Season::Summer;
            table.r12 = findStr(line, "R12 < 50") ? R12::Less50 : findStr(line, "R12 > 100") ? R12::Greater100 : R12::Less100;

            std::getline(file, line);
            std::getline(file, line);

            for (auto& row : table.rows)
            {
                if (!std::getline(file, line))
                    return;

                char degreeSymbol = '°';

                std::erase(line, degreeSymbol);

                std::istringstream ss(line);
                ss >> row.LatDeg;

                double value;

                size_t rowIndex = 0;
                while (ss >> value)
                {
                    row.values[rowIndex] = value;
                    ++rowIndex;
                }

            }
            ++tableIndex;
        }
    }
}

// A simple test case
TEST(SampleTest1, AssertionTrue)
{
    EXPECT_EQ(1, 1);
}

TEST(SampleTest2, ReadFile)
{
    readData("../../../../ITURHFProp/Data/P1239-3 Decile Factors.txt");
    EXPECT_EQ(tables[0].rows[0].LatDeg, 90.0);
}

TEST(SampleTest3, AssertionFalse)
{
    EXPECT_NE(1, 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}