#include "feature_mgr.h"
#include "features/basic_morphology.h"
#include "features/caliper.h"
#include "features/chords.h"
#include "features/convex_hull.h"
#include "features/ellipse_fitting.h"
#include "features/euler_number.h"
#include "features/circle.h"
#include "features/extrema.h"
#include "features/fractal_dim.h"
#include "features/erosion.h"
#include "features/radial_distribution.h"
#include "features/gabor.h"
#include "features/geodetic_len_thickness.h"
#include "features/glcm.h"
#include "features/glrlm.h"
#include "features/glszm.h"
#include "features/gldm.h"
#include "features/hexagonality_and_polygonality.h"
#include "features/ngtdm.h"
#include "features/image_moments.h"
#include "features/intensity.h"
#include "features/moments.h"
#include "features/neighbors.h"
#include "features/caliper.h"
#include "features/roi_radius.h"
#include "features/zernike.h"

FeatureManager::FeatureManager()
{
	register_feature(new PixelIntensityFeatures());
	register_feature(new BasicMorphologyFeatures());
	register_feature(new ContourFeature());
	register_feature(new ConvexHullFeature());
	register_feature(new EllipseFittingFeature());
	register_feature(new ExtremaFeature());
	register_feature(new EulerNumberFeature());
	//register_feature(new CaliperFeretFeature());
	//register_feature(new CaliperMartinFeature());
	register_feature(new CaliperNassensteinFeature());
	register_feature(new ChordsFeature());
	//register_feature(new HexagonalityPolygonalityFeature());
	//register_feature(new EnclosingInscribingCircumscribingCircleFeature());
	//register_feature(new GeodeticLengthThicknessFeature());
	//register_feature(new RoiRadiusFeature());
	//register_feature(new ErosionPixelsFeature());
	//register_feature(new FractalDimensionFeature());
	//register_feature(new GLCMFeature());
	//register_feature(new GLRLMFeature());
	//register_feature(new GLSZMFeature());
	//register_feature(new GLDMFeature());
	//register_feature(new NGTDMFeature());
	//register_feature(new ImageMomentsFeature());
	register_feature(new GaborFeature());
	//register_feature(new ZernikeFeature());
	//register_feature(new RadialDistributionFeature());

}


