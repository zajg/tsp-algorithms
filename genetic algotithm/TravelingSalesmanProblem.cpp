
#include "TravelingSalesmanProblem.h"
#include <vector>
#include <algorithm>


TravelingSalesmanProblem::TravelingSalesmanProblem()
{
	cities_matrix = new std::vector< std::vector<int>* >;
}


TravelingSalesmanProblem::~TravelingSalesmanProblem()
{
	cities_matrix->clear();
	delete cities_matrix;
}

bool TravelingSalesmanProblem::readCitiesDataFromFileToCitiesMatrix(std::string file_path)
{
	std::ifstream file_with_cities(file_path);

	if (file_with_cities.good())
	{		
		readEdgeCostsFromFile(file_with_cities);
		file_with_cities.close();
		if (cities_matrix->size() > 0)
		{
			return true;
		}
		
	}
	return false;

}

void TravelingSalesmanProblem::readEdgeCostsFromFile(std::ifstream& file_with_cities)
{
	int dimension = getMatrixDimensionFromFile(file_with_cities);
	cities_matrix->clear();
	for (int i = 0; i < dimension; ++i)
	{
		cities_matrix->push_back(new std::vector<int>);
		readMatrixRowFromFile(dimension, file_with_cities, i);
	}
}

int TravelingSalesmanProblem::getMatrixDimensionFromFile(std::ifstream& file_with_cities)
{
	int position = -1;
	int dimension = -1;
	std::string line;
	do
	{
		std::getline(file_with_cities, line);
		position = line.find("DIMENSION: ");
		if (position != std::string::npos)
		{
			position += 11; //"DIMENSION: " has 11 characters
			dimension = string2int(line.substr(position));
		}
	} while (line.find("EDGE_WEIGHT_SECTION") == std::string::npos);
	return dimension;
}

void TravelingSalesmanProblem::readMatrixRowFromFile(int dimension, std::ifstream& file_with_cities, int row)
{
	std::string edgeCost;
	for (int j = 0; j < dimension; ++j)
	{
		file_with_cities >> edgeCost;
		cities_matrix->at(row)->push_back(string2int(edgeCost));
	}
}

int TravelingSalesmanProblem::string2int(const std::string &string)
{
	return atoi(string.c_str());
}

std::string TravelingSalesmanProblem::getMatrixToString()
{
	std::string matrix = "";
	for (std::size_t i = 0; i < cities_matrix->size(); i++)
	{
		for (std::size_t j = 0; j < cities_matrix->at(i)->size(); j++)
		{
			matrix.append(std::to_string(getEdgeCost(i, j)));
			matrix.append(" ");
		}
		matrix.append("\n\n");
	}
	return matrix;
}

int TravelingSalesmanProblem::getEdgeCost(int row, int column)
{
	return cities_matrix->at(row)->at(column);
}

int TravelingSalesmanProblem::getCitiesCount()
{
	return cities_matrix->size();
}

void TravelingSalesmanProblem::setCitiesCount(int count)
{
	cities_matrix->clear();
	for (int i = 0; i < count; ++i)
	{
		cities_matrix->push_back(new std::vector<int>);
		for (int j = 0; j < count; ++j)
		{
			cities_matrix->at(i)->push_back(9999);
		}
	}
}

void TravelingSalesmanProblem::setEdgeCost(int cost, int beginning, int destination)
{
	cities_matrix->at(beginning)->operator[](destination) = cost;
}

