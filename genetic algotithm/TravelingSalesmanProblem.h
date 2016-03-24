#pragma once

#include <string>
#include <fstream>
#include <vector>
class TravelingSalesmanProblem
{
	std::vector< std::vector<int>* >* cities_matrix;

	void readEdgeCostsFromFile(std::ifstream& file_with_cities);
	void readMatrixRowFromFile(int dimension, std::ifstream& file_with_cities, int row);
	int getMatrixDimensionFromFile(std::ifstream& file_with_cities);
	int string2int(const std::string &string);

public:
	TravelingSalesmanProblem();
	~TravelingSalesmanProblem();
	bool readCitiesDataFromFileToCitiesMatrix(std::string filePath);
	std::string getMatrixToString();
	int getEdgeCost(int row, int column);
	int getCitiesCount();
	void setCitiesCount(int count);
	void setEdgeCost(int cost, int beginning, int destination);
};

