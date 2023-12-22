
#ifndef __HEADER_H
#define __HEADER_H

#pragma once

#include <boost/geometry.hpp>
#include <iostream>
#include <fstream>

namespace bg = boost::geometry;
namespace bgm = bg::model;

using point = bgm::d2::point_xy<double>;
using polygon = bgm::polygon<point>;
using multi_polygon = bgm::multi_polygon<polygon>;

template <typename G>
void write_svg(std::string fname, G const& g);

template <typename G>
void force_fix(G& g);

using std::string;
using std::vector;
using std::exception;
using std::stoi;
using std::ifstream;

vector<polygon> vectorOfPolis;
string nameFile, line;

int polyIndex0, polyIndex1, errorIndex;

char operation;

string errors[] =
{
    " default file: points.txt",
    "couldn't find:",
    "Error parsing command line: One of the indexes is not a number",
    "Index out of range",
    "Operation not found... Allowed operations are: + - x"
};


template <typename G>
void write_svg(std::string fname, G const& g)
{
    std::ofstream ofs(fname);
    bg::svg_mapper<point> mapper(ofs, 400, 400);

    mapper.add(g);
    mapper.map(g, "fill-opacity:0.1;fill:rgb(100,0,0);stroke:rgb(200,0,0);stroke-width:2", 5);

}

template <typename G> void force_fix(G& g)
{
    G previous;
    std::string reason;
    do 
    {
        if (bg::is_valid(g, reason))
            return;

        std::cout << "Invalid: " << reason << "\n";
        previous = g;
        bg::correct(g);
    } 
    while (!bg::equals(previous, g));
    std::cout << "Warning: could not force_fix\n";
}

#endif // !__HEADER_H