#pragma once

#include <unordered_map>
#include "../featureset.h"
#include "../roi_data.h"
#include "pixel.h"

/// @brief Class encapsulating Legendre's ellipse of inertia of ROI pixels (ellipse that has the same normalized second central moments as the particle shape).
class EllipseFittingFeatures
{
public:
	EllipseFittingFeatures(const std::vector<Pixel2> & roi_pixels, double centroid_x, double centroid_y, double area);

	/// @brief Major axis length of Legendre's ellipse of inertia
	/// @return 
	double get_major_axis_length();

	/// @brief M axis length of Legendre's ellipse of inertia
	/// @return 
	double get_minor_axis_length();

	/// @brief The eccentricity of an ellipse is the ratio of the distance c between the center of the ellipse and each focus to the length of the semimajor axis a: 
	/// @return 
	double get_eccentricity();

	/// @brief Orientation describes whather the ellipse is horizontal or vertical
	/// @return 
	double get_orientation();

	/// @brief Roundness is calculated as (4 \times Area) / (\pi \times MajorAxis^2). Roundness should not be confused with circularity as the latter captures perimeter smoothness and not overall structural shape.
	/// @return 
	double get_roundness();

	static bool required (const FeatureSet& fs) { return fs.anyEnabled ({ MAJOR_AXIS_LENGTH, MINOR_AXIS_LENGTH, ECCENTRICITY, ORIENTATION, ROUNDNESS }); }
	static void reduce (size_t start, size_t end, std::vector<int>* ptrLabels, std::unordered_map <int, LR>* ptrLabelData);

private:

	double majorAxisLength = 0,
		minorAxisLength = 0,
		eccentricity = 0,
		orientation = 0, 
		roundness = 0;
};
