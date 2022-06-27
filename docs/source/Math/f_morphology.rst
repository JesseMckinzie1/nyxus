.. role:: raw-html-m2r(raw)
   :format: html


Morphology features
===================

Let:
:math:`A` be a set of :math:`Np` pixels included in the ROI

AREA_PIXELS_COUNT :math:`= S = card(A)`

AREA_UM2 :math:`= card(A) s^2` where :math:`s` is pixel size in micrometers 

CENTROID_X :math:`\gets c_X = \frac{1}{n} \sum *i ^n  A*\ {Xi}`

CENTROID_Y :math:`\gets c_Y =  \frac{1}{n} \sum *i ^n  A*\ {Yi}`

WEIGHTED_CENTROID_X :math:`\gets w_X = \frac{1}{n} \sum _i ^n  A_i (A*\ {Xi}-c_X)`

WEIGHTED_CENTROID_Y :math:`= \frac{1}{n} \sum _i ^n  A_i (A*\ {Yi}-c_Y) \to w_Y`

MASS_DISPLACEMENT :math:`= \sqrt {( w_X - c_X)^2 + ( w_Y - c_Y)^2}`

COMPACTNESS :math:`= \frac {1}{n} \displaystyle {\sqrt {\operatorname {E} \left[(A-(c_X,c_Y)) )^{2}\right]}}`

BBOX_YMIN :math:`\gets \epsilon_X = \operatorname {min}A_Y`

BBOX_XMIN :math:`\gets \epsilon_Y = \operatorname {min}A_X`

BBOX_HEIGHT :math:`\gets \epsilon_V = \operatorname {max}A_Y - \epsilon_Y`

BBOX_WIDTH :math:`\gets \epsilon_H = \operatorname {max}A_X - \epsilon_X`

ASPECT_RATIO :math:`\displaystyle =
\left{\begin{array}{cc} 
\frac{\epsilon_V}{\epsilon_H} & \epsilon_V>=\epsilon_H \
\frac{\epsilon_H}{\epsilon_V} & \epsilon_V<\epsilon_H 
\end{array}\right.
` 

EXTENT :math:`= \frac {S}{S_{BB}}$ where $S_BB=\epsilon_H\epsilon_V`

Features related to ROI's contour
---------------------------------

Let :math:`C` be the set of contour pixels of ROI :math:`A`. 

PERIMETER :math:`\displaystyle \gets P = card(C)`

CIRCULARITY :math:`\displaystyle =\sqrt { \frac {4 \pi S}{P^2}}` where :math:`S` and :math:`P` are ROI area and perimeter (features AREA_PIXELS_COUNT and PERIMETER)

EQUIVALENT_DIAMETER :math:`\displaystyle = \frac {P}{\pi}`

EDGE_MEAN_INTENSITY :math:`\displaystyle \gets \mu_C =\frac{1}{card(C)}\sum_i C_i`

EDGE_MAX_INTENSITY :math:`= max \: \textrm C`

EDGE_MIN_INTENSITY :math:`= min \: \textrm C`

EDGE_STDDEV_INTENSITY :math:`\displaystyle = \left[\frac{1}{card(C)}\sum_i (C_i-\mu_C)^2\right]^{\frac {1}{2}}`

EDGE_INTEGRATEDINTENSITY :math:`\displaystyle = \sum _i {C_i}` 

Features related to ROI's convex hull
-------------------------------------

CONVEX_HULL_AREA :math:`=S_H=\displaystyle {\frac {1}{2}}{\Biggl \vert }\sum *\ {i=0}^{n_H-1}(x*\ {i}y_{i+1}-x*\ {i+1}y_{i}){\Biggr \vert }` where :math:`n_H` is the number of convex hull vertices, :math:`\displaystyle {(x_i,y_i)}, i=0, 1, ..., n_H-1` are Cartesian coordinates of the vertives.

SOLIDITY :math:`\displaystyle = \frac {S}{S_H}` where :math:`S` is ROI area (feature AREA_PIXELS_COUNT)

Features related to interpreting ROI pixels as a sampled ellipse
----------------------------------------------------------------

MAJOR_AXIS_LENGTH :math:`= a = 4 \sqrt {\lambda_1}` where :math:`\lambda_1` is the first largest principal component 

MINOR_AXIS_LENGTH :math:`= b = 4 \sqrt {\lambda_2}` where :math:`\lambda_2` is the second largest principal component 

ECCENTRICITY :math:`= \displaystyle \sqrt {1 - \frac {b^2} {a^2}}`

ELONGATION :math:`= \displaystyle \sqrt{\frac{\lambda_2}{\lambda_1}}`

ORIENTATION 
:math:`\displaystyle \theta =
\left{\begin{array}{cc} 
0 & b=0 \:\text{and}\: a \ge c \
\frac{\pi}{2} & b=0 \:\text{and}\: a < c \
\arctg \frac{\lambda_1-a}{b} & b \ne 0
\end{array}\right.`
where 

.. math:: 
  
  cov = \left(\begin{array}{cc} 
  a & b\
  b & c
  \end{array}\right)

  * \text {covariance matrix of ROI pixel coordinates}
  
  and 

  :math:`\displaystyle \lambda_1 = \frac{a+c}{2}+\sqrt{(\frac{a-c}{2})^2 + b^2}$, $\displaystyle \lambda_2 = \frac{a+c}{2}-\sqrt{(\frac{a-c}{2})^2 + b^2}`

ROUNDNESS :math:`\displaystyle = \frac {4 S}{\pi a b}`

Neighbor features
-----------------

NUM_NEIGHBORS :math:`\gets n_N=` the number of neighbor ROIs 

PERCENT_TOUCHING - the ratio of ROIs situated at Euclidean distance 0 to :math:`n_N`

CLOSEST_NEIGHBOR1_DIST - distance to ROI's closest neighbor

CLOSEST_NEIGHBOR1_ANG - angle between the ROI centroid and its closest neighbor's centroid

CLOSEST_NEIGHBOR2_DIST - distance to ROI's 2nd closest neighbor

CLOSEST_NEIGHBOR2_ANG - angle between the ROI centroid and its 2nd closest neighbor's centroid

ANG_BW_NEIGHBORS_MEAN - standard deviation of the angle between ROI's neighbors.

ANG_BW_NEIGHBORS_STDDEV - standard deviation of the angle between ROI's neighbors.

ANG_BW_NEIGHBORS_MODE - the histogram bin value of angle between ROI's neighbors having the highest count.

Polygonal representation features
---------------------------------

POLYGONALITY_AVE :math:`\displaystyle = 5 (r_S + r_A)` where :math:`\displaystyle r_S = 1 - \left|1-\frac{\frac{P}{n_N}}{\sqrt{\frac{4S\tg \frac{\pi}{n_N}}{n_N}}} \right|` - polygonal size ratio, :math:`\displaystyle r_A = 1 - \left| 1 - \frac{S\tg \frac{\pi}{n_N}}{\frac{1}{4} \: n_N \: P^2}\right|` - polygonal area ratio, :math:`n_N` - number of ROI's neighbors, :math:`P` and :math:`S` - ROI's perimeter and area.

HEXAGONALITY_AVE :math:`\displaystyle = \sqrt {\frac {r*\ {\sigma A}^2 + r_{\sigma P}^2}{2} }`

HEXAGONALITY_STDDEV :math:`\displaystyle = 5 (r*\ {HS} + r_{HP})`

Other features
--------------

DIAMETER_MIN_ENCLOSING_CIRCLE minimum diameter of a circle which completely covers the ROI

DIAMETER_CIRCUMSCRIBING_CIRCLE the smallest circle centered at the ROI centroid that totally encloses the profile,

DIAMETER_INSCRIBING_CIRCLE maximum diameter of a circle centered at the ROI centroid which fits inside the ROI

Let :math:`l_G` - geodetic length, :math:`t_G` - thickness. Assuming

.. math::
  \displaystyle 
  \left{\begin{array}{cc} 
  S = l_G t_G \
  P = 2(l_G+t_G)
  \end{array}\right.

we can express the following features as:

GEODETIC_LENGTH :math:`\displaystyle \gets l_G = \frac{P}{4} + \sqrt{\max \left(\frac{P^2}{16}-S, 0\right)}`

THICKNESS :math:`\displaystyle \gets t_G = \frac{P}{2} - l_G`

Let :math:`O=o_X,o_Y` be the ROI centroid and :math:`OC_i` - segment connecting centroid to an edge pixel :math:`i`. Then

ROI_RADIUS_MEAN :math:`\displaystyle \gets \mu_r =\frac{1}{card(C)}\sum_i ||OC_i||`

ROI_RADIUS_MAX :math:`\displaystyle = \max OC_i`

ROI_RADIUS_MEDIAN - median radius :math:`OC_i`

Caliper features
----------------

Feret diameter
^^^^^^^^^^^^^^

:raw-html-m2r:`<img src="./feret3.jpg" height=200>`

MIN_FERET_DIAMETER - minimum :math:`X*\ {Fe}` \
MAX_FERET_DIAMETER - maximum :math:`X*\ {Fe}` \
MIN_FERET_ANGLE - rotation angle delivering :math:`\min X*\ {Fe}` \
MAX_FERET_ANGLE - rotation angle delivering :math:`\max X*\ {Fe}`

Statistics of Feret diameter at 0-90 degree rotation angles:
STAT_FERET_DIAM_MIN :math:`=\min X*\ {Fe}`\
STAT_FERET_DIAM_MAX :math:`=\max X*\ {Fe}`\
STAT_FERET_DIAM_MEAN :math:`=\operatorname {E} ( X*\ {Fe} )`\
STAT_FERET_DIAM_MEDIAN\
STAT_FERET_DIAM_STDDEV\
STAT_FERET_DIAM_MODE

Martin diameter
^^^^^^^^^^^^^^^

:raw-html-m2r:`<img src="./martin.jpg" height=200>`

Statistics of Martin diameter at 0-90 degree rotation angles:
STAT_MARTIN_DIAM_MIN\
STAT_MARTIN_DIAM_MAX\
STAT_MARTIN_DIAM_MEAN\
STAT_MARTIN_DIAM_MEDIAN\
STAT_MARTIN_DIAM_STDDEV\
STAT_MARTIN_DIAM_MODE

Nassenstein diameter
^^^^^^^^^^^^^^^^^^^^

:raw-html-m2r:`<img src="./nassenstein.jpg" height=200>`

Statistics of Nassenstein diameter at 0-90 degree rotation angles:
STAT_NASSENSTEIN_DIAM_MIN\
STAT_NASSENSTEIN_DIAM_MAX\
STAT_NASSENSTEIN_DIAM_MEAN\
STAT_NASSENSTEIN_DIAM_MEDIAN\
STAT_NASSENSTEIN_DIAM_STDDEV\
STAT_NASSENSTEIN_DIAM_MODE

All-chords features
^^^^^^^^^^^^^^^^^^^

:raw-html-m2r:`<img src="./chord.jpg" height=200>`

ALLCHORDS_MAX\
ALLCHORDS_MAX_ANG\
ALLCHORDS_MIN\
ALLCHORDS_MIN_ANG\
ALLCHORDS_MEDIAN\
ALLCHORDS_MEAN\
ALLCHORDS_MODE\
ALLCHORDS_STDDEV

Max-chord features
^^^^^^^^^^^^^^^^^^

MAXCHORDS_MAX\
MAXCHORDS_MAX_ANG\
MAXCHORDS_MIN\
MAXCHORDS_MIN_ANG\
MAXCHORDS_MEDIAN\
MAXCHORDS_MEAN\
MAXCHORDS_MODE\
MAXCHORDS_STDDEV
