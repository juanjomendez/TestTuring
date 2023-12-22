#include "Header.h"


void displaySyntaxError()
{
    std::cout << "Usage : testpoly [file (optional)] poly1(index) operation poly2(index)" << std::endl;
    std::cout << "where:" << std::endl;
    std::cout << "[file]: optional file for parsing... If not provided, a default 'points.txt' in this folder will be used" << std::endl;
    std::cout << "poly1(index): index of first polygon in the txt file" << std::endl;
    std::cout << "operation: +, -, *" << std::endl;
    std::cout << "+ For Union" << std::endl;
    std::cout << "- For Difference" << std::endl;
    std::cout << "* For Intersection" << std::endl;
    std::cout << "poly2(index): index of second polygon in the txt file" << std::endl;
}

int main(int argc, char** argv)
{

    vectorOfPolis.clear(); 

    //for testing from VS
    /*
    argc = 4;
    argv[1] = (char*)"3";
    argv[2] = (char*)"-";
    argv[3] = (char*)"4";
    */

    if (argc != 4 && argc != 5)
        displaySyntaxError();
    else
    {
        bool error = false;
        if (argc == 4)//no file provided, take the default one!
        {
            nameFile = "points.txt";
            try
            {
                polyIndex0 = stoi(argv[1]);
                polyIndex1 = stoi(argv[3]);
                operation = argv[2][0];
            }
            catch (exception e)
            {
                error = true;
                errorIndex = 2;
            }
        }
        else
        {
            try
            {
                nameFile = argv[1];
                polyIndex0 = stoi(argv[2]);
                polyIndex1 = stoi(argv[4]);
                operation = argv[3][0];
            }
            catch (exception e)
            {
                error = true;
                errorIndex = 2;
            }
        }
        if (error == false)//arguments are ok in terms of type... 
        {

            string newpoly;

            if (ifstream(nameFile).good())
            {

                ifstream file(nameFile);

                if (file.is_open())
                {
                    while (getline(file, line))
                    {
                        if (line.compare("") == 0)
                        {
                            if (newpoly.size() == 0)//starting to parse the new poly...
                            {
                                newpoly.clear();
                                newpoly.append("POLYGON((");
                            }
                        }
                        if (line.compare("END") == 0)//convert the newpoly string to a "polygon" and store it in our vector...
                        {
                            newpoly.resize(newpoly.size() - 1);
                            newpoly.append("))");

                            polygon p;
                            bg::read_wkt(newpoly, p);
                            force_fix(p);
                            vectorOfPolis.push_back(p);

                            newpoly = "";
                        }
                        else if ((line.compare("") != 0) && (line[0] != '#'))//keep adding coordinates to the newpoly string!!!
                        {
                            size_t index = line.find_first_of(',');
                            size_t index2 = line.find_last_of(',');
                            string firstNumber = line.substr(0, index);
                            string secondNumber = line.substr(index + 1, index2 - index - 1);

                            newpoly.append(firstNumber);
                            //newpoly.append(" ");
                            newpoly.append(secondNumber);
                            newpoly.append(",");
                        }
                    }
                    file.close();
                }
                //now that I have the whole list of polys, check if I am in the range...
                if (polyIndex0 < 0 || polyIndex0 >= (int)vectorOfPolis.size() || polyIndex1 < 0 || polyIndex1 >= (int)vectorOfPolis.size())
                {
                    std::cout << errors[3] << std::endl;//not in the range!
                }
                else
                {
                    bool operationError = false;
                    int i = 0;
                    multi_polygon ab;

                    switch (operation)
                    {
                    case '+':
                        bg::union_(vectorOfPolis[polyIndex0], vectorOfPolis[polyIndex1], ab);
                        write_svg("result.svg", ab);
                    break;

                    case '-':
                        bg::difference(vectorOfPolis[polyIndex0], vectorOfPolis[polyIndex1], ab);
                        write_svg("result.svg", ab);
                    break;

                    case '*':
                        bg::intersection(vectorOfPolis[polyIndex0], vectorOfPolis[polyIndex1], ab);
                        write_svg("result.svg", ab);
                    break;

                    default://undefined operation!
                        operationError = true;
                        std::cout << errors[4] << std::endl;
                    break;
                    }
                    if (operationError == false)
                    {
                        //save all the individual polis
                        for (size_t i = 0; i < vectorOfPolis.size(); i++)
                            write_svg("Poly" + std::to_string(i) + ".svg", vectorOfPolis[i]);

                        std::cout << "Success !!" << std::endl;
                    }

                }

            }

        }
        else
        {
            std::cout << errors[errorIndex] << std::endl;
        }

    }

}