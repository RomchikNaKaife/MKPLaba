//
//  main.cpp
//  MKPLABA
//
//  Created by Роман Перепонов on 26.11.2023.
//

#include <iostream>
#include <fstream>
#include <cmath>

const double eccentricity = 0.8276646992;
const long double Pi = 3.14159265358;
const double epsilon = 0.0001;

double eccentricToTrueAnomaly(double eccentricAnomaly)
{
    return atan(sqrt((1 + eccentricity) / (1 - eccentricity)) * tan(eccentricAnomaly / 2)) * 2;
}

double iterationMtd(double nextE, double currentE, double meanAnomaly)
{
    if (fabs(currentE - nextE) < epsilon)
    {
        std::cout << nextE << std::endl;
        return nextE;
    }
    else
    {
        return iterationMtd(eccentricity * sin(nextE) + meanAnomaly, nextE, meanAnomaly);
    }
}

double bisectionMtd(double lowerBound, double upperBound, double meanAnomaly)
{
    if (fabs(upperBound - lowerBound) < 2 * epsilon && fabs(((lowerBound + upperBound) / 2) - eccentricity * sin((lowerBound + upperBound) / 2) - meanAnomaly) < epsilon)
    {
        return (upperBound + lowerBound) / 2;
    }
    else if ((lowerBound - eccentricity * sin(lowerBound) - meanAnomaly) * (((lowerBound + upperBound) / 2) - eccentricity * sin((lowerBound + upperBound) / 2) - meanAnomaly) < 0)
    {
        return bisectionMtd(lowerBound, (lowerBound + upperBound) / 2, meanAnomaly);
    }
    else
    {
        return bisectionMtd((lowerBound + upperBound) / 2, upperBound, meanAnomaly);
    }
}

double goldenRatioMtd(double lowerBound, double upperBound, double ratio, double meanAnomaly)
{
    if (fabs(upperBound - lowerBound) < 2 * epsilon && fabs(((lowerBound + upperBound) / 2) - eccentricity * sin((lowerBound + upperBound) / 2) - meanAnomaly) < epsilon)
    {
        return lowerBound + (upperBound - lowerBound) / ratio;
    }
    else if ((lowerBound - eccentricity * sin(lowerBound) - meanAnomaly) * (((lowerBound + upperBound) / 2) - eccentricity * sin((lowerBound + upperBound) / 2) - meanAnomaly) < 0)
    {
        return goldenRatioMtd(lowerBound, lowerBound + (upperBound - lowerBound) / ratio, ratio, meanAnomaly);
    }
    else
    {
        return goldenRatioMtd(lowerBound + (upperBound - lowerBound) / ratio, upperBound, ratio, meanAnomaly);
    }
}

double newtonMtd(double difference, double eccentricAnomaly, double meanAnomaly)
{
    if (difference < epsilon)
    {
        return eccentricAnomaly - difference;
    }
    else
    {
        return newtonMtd((eccentricAnomaly - eccentricity * sin(eccentricAnomaly) - meanAnomaly) / ((epsilon - eccentricity * sin(eccentricAnomaly + epsilon) - eccentricity * sin(eccentricAnomaly)) / epsilon), eccentricAnomaly - (eccentricAnomaly - eccentricity * sin(eccentricAnomaly) - meanAnomaly) / ((epsilon - eccentricity * sin(eccentricAnomaly + epsilon) - eccentricity * sin(eccentricAnomaly)) / epsilon), meanAnomaly);
    }
}

int main()
{
    std::ofstream outputFile;
    std::ifstream inputFile;
    outputFile.open("iterationMtdResults.txt");

    if (outputFile.is_open())
    {
        for (int i = 0; i <= 360; i++)
        {
            double initialE = eccentricity * sin(i * 2 * Pi / 360) + (i * 2 * Pi / 360);
            double startingE = i * 2 * Pi / 360;
            outputFile << bisectionMtd(initialE, startingE, i * 2 * Pi / 360) << std::endl;
        }
    }
    outputFile.close();

    inputFile.open("iterationMtdResults.txt");
    outputFile.open("trueIterationMtdResults.txt");

    if (inputFile.is_open())
    {
        for (int i = 0; i <= 360; i++)
        {
            char line[50];
            inputFile.getline(line, 50);
            std::string str = line;
            char *ptrEnd;
            outputFile << eccentricToTrueAnomaly(strtod(line, &ptrEnd)) << std::endl;
        }
    }
    inputFile.close();
    outputFile.close();

    outputFile.open("bisectionMtdResults.txt");
    if (outputFile.is_open())
    {
        for (int i = 0; i <= 360; i++)
        {
            outputFile << bisectionMtd((i - 10) * 2 * Pi / 360, (i + 10) * 2 * Pi / 360, i * 2 * Pi / 360) << std::endl;
        }
    }
    outputFile.close();

    inputFile.open("bisectionMtdResults.txt");
    outputFile.open("trueBisectionMtdResults.txt");

    if (inputFile.is_open())
    {
        for (int i = 0; i <= 360; i++)
        {
            char line[50];
            inputFile.getline(line, 50);
            std::string str = line;
            char *ptrEnd;
            outputFile << eccentricToTrueAnomaly(strtod(line, &ptrEnd)) << std::endl;
        }
    }
    inputFile.close();
    outputFile.close();

    outputFile.open("goldenRatioMtdResults.txt");
    if (outputFile.is_open())
    {
        for (int i = 0; i <= 360; i++)
        {
            outputFile << goldenRatioMtd((i - 10) * 2 * Pi / 360, (i + 10) * 2 * Pi / 360, (pow(5, 0.5) + 1) / 2, i * 2 * Pi / 360) << std::endl;
        }
    }
    outputFile.close();

    inputFile.open("goldenRatioMtdResults.txt");
    outputFile.open("trueGoldenRatioMtdResults.txt");

    if (inputFile.is_open())
    {
        for (int i = 0; i <= 360; i++)
        {
            char line[50];
            inputFile.getline(line, 50);
            std::string str = line;
            char *ptrEnd;
            outputFile << eccentricToTrueAnomaly(strtod(line, &ptrEnd)) << std::endl;
        }
    }
    inputFile.close();
    outputFile.close();

    outputFile.open("newtonMtdResults.txt");
    if (outputFile.is_open())
    {
        for (int i = 0; i <= 360; i++)
        {
            outputFile << newtonMtd(((i + 20) * 2 * Pi / 360 - eccentricity * sin((i + 20) * 2 * Pi / 360) - i * 2 * Pi / 360) / ((epsilon - eccentricity * sin((i + 20) * 2 * Pi / 360 + epsilon) - eccentricity * sin((i + 20) * 2 * Pi / 360)) / epsilon), (i + 20) * 2 * Pi / 360, i * 2 * Pi / 360) << std::endl;
        }
    }
    outputFile.close();

    inputFile.open("newtonMtdResults.txt");
    outputFile.open("trueNewtonMtdResults.txt");

    if (inputFile.is_open())
    {
        for (int i = 0; i <= 360; i++)
        {
            char line[50];
            inputFile.getline(line, 50);
            std::string str = line;
            char *ptrEnd;
            outputFile << eccentricToTrueAnomaly(strtod(line, &ptrEnd)) << std::endl;
        }
    }
    inputFile.close();
    outputFile.close();

    return 0;
}
