#include <memory>
#include <unordered_map>
#include <unordered_set> 
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <stdlib.h>
#include <stdio.h>

#include "sensemaker.h"

// Macro to make some file i/o calls platform-independent
#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL
#endif

void print_label_stats()
{
	std::cout << "\tFeatures by label. Number of processed labels " << uniqueLabels.size() << std::endl;

	// Print stats by label
	/*
	print_by_label("Min", labelMins);
	print_by_label("Max", labelMaxs);
	print_by_label("Mean", labelMeans);
	print_by_label("Median", labelMedians);
	print_by_label("Energy", labelMassEnergy);
	print_by_label("Variance", labelVariance);
	*/
}

// Saves the result of image scanning and feature calculation. Must be called after the reduction phase.
bool save_features (std::string inputFpath, std::string outputDir)
{
	// Sort the labels
	std::vector<int> L { uniqueLabels.begin(), uniqueLabels.end() };
	std::sort (L.begin(), L.end());

	// Tear off the directory part of 'inputPath', we don't need it
	std::string fullPath = outputDir + "/" + getPureFname(inputFpath) + ".csv";

	std::cout << "Creating file " << fullPath << std::endl;

	//fullPath.replace("//", "/");
	//fullPath.replace("\\\\", "\\");

	// Output label data
	// -- Create a file
	FILE* fp = nullptr;
	fopen_s(&fp, fullPath.c_str(), "w");
	if (!fp) 
	{
		std::perror("fopen failed"); 
		return false;
	}

	// -- Configure buffered write
	if (std::setvbuf(fp, nullptr, _IOFBF, 32768) != 0) {
		std::perror("setvbuf failed"); 
		return false;
	}
	
	// -- Header
	fprintf (fp, 
		"label , "
		"mean, "
		"median , "
		"min , "
		"max , "
		"range , "
		"standard_deviation , "
		"skewness , "
		"kurtosis , "
		"mean_absolute_deviation , "
		"energy , "
		"root_mean_squared , "
		"entropy , "
		"mode , "
		"uniformity , "
		"P10 , P25 , P75 , P90 , "
		"interquartile_range , "
		"robust_mean_absolute_deviation , "
		"weighted_centroid_y , "
		"weighted_centroid_x , "
		"pixelCount"
		"\n");

	// -- Dump numbers
	int cnt = 1; 
	for (auto l : L)
	{
		std::stringstream ss;
		
		LR& lr = labelData[l];
		auto _pixCnt = lr.labelCount;
		auto _min = lr.labelMins;
		auto _max = lr.labelMaxs;
		auto _range = _max - _min;
		auto _mean = lr.labelMeans;
		auto _median = lr.labelMedians;
		auto _energy = lr.labelMassEnergy;
		auto _stdev = lr.labelStddev;
		auto _skew = lr.labelSkewness;
		auto _kurt = lr.labelKurtosis;
		auto _mad = lr.labelMAD;
		auto _rms = lr.labelRMS;
		auto _wcx = lr.labelCentroid_x,
			_wcy = lr.labelCentroid_y;
		auto _entro = lr.labelEntropy;
		auto _p10 = lr.labelP10,
			_p25 = lr.labelP25,
			_p75 = lr.labelP75,
			_p90 = lr.labelP90,
			_iqr = lr.labelIQR,
			_rmad = lr.labelRMAD,
			_mode = lr.labelMode,
			_unifo = lr.labelUniformity;


		ss	<< l		<< " , " 
			<< _mean	<< " , " 
			<< _median	<< " , " 			
			<< _min		<< " , " 
			<< _max		<< " , " 
			<< _range	<< " , "
			<< _stdev	<< " , "
			<< _skew	<< " , "
			<< _kurt	<< " , "
			<< _mad		<< " , "			
			<< _energy	<< " , " 
			<< _rms		<< " , "
			<< _entro	<< " , "
			<< _mode	<< " , "
			<< _unifo	<< " , "
			<< _p10		<< " , "
			<< _p25		<< " , "
			<< _p75		<< " , " 
			<< _p90		<< " , "
			<< _iqr		<< " , "
			<< _rmad	<< " , "
			<< _wcy		<< " , "
			<< _wcx		<< " , "
			<< _pixCnt	<< " , ";

		fprintf (fp, "%s\n", ss.str().c_str());
	}
	std::fflush(fp);
	std::fclose(fp);

	#ifdef SANITY_CHECK_INTENSITIES_FOR_LABEL
	// Output label's intensities for debug
	for (auto l : L)
	{
		if (l != SANITY_CHECK_INTENSITIES_FOR_LABEL)
			continue;
		
		std::stringstream ss;
		LR& lr = labelData[l];
		auto& I = lr.raw_intensities;
		ss << outputDir << "/" << "intensities_label_" << l << ".txt";
		fullPath = ss.str();	
		std::cout << "Dumping intensities of label " << l << " to file " << fullPath << std::endl;


		fopen_s(&fp, fullPath.c_str(), "w");
		if (fp)
		{
			ss.clear();
			ss << "I_" << l << " = [\n";
			for (auto w : I)
				ss << "\t" << w << ", \n";
			ss << "\t]; \n";
			fprintf (fp, "%s\n", ss.str().c_str());
			std::fclose(fp);
		}		
	}
	#endif

	return true;
}


// Diagnostic function
void print_by_label(const char* featureName, std::unordered_map<int, StatsInt> L, int numColumns)
{
	std::stringstream ss;

	std::cout << std::endl << featureName << std::endl;
	
	int i = 1;
	for (auto& x : L)
	{
		ss << 'L' << x.first << ':' << x.second;
		std::cout << std::setw(10) << ss.str();
		ss.str (std::string()); // Clear ss

		if (i++ % numColumns == 0)
			std::cout << std::endl;
	}

}

// Another diagnostic function
void print_by_label(const char* featureName, std::unordered_map<int, StatsReal> L, int numColumns)
{
	std::stringstream ss;

	std::cout << std::endl << featureName << std::endl;

	int i = 1;
	for (auto& x : L)
	{
		ss << 'L' << x.first << ':' << x.second;
		std::cout << std::setw(30) << ss.str();
		ss.str(std::string()); // Clear ss

		if (i++ % numColumns == 0)
			std::cout << std::endl;
	}

}
