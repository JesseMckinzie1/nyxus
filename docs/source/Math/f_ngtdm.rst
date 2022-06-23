
Texture features / NGTDM
========================

A Neighbouring Gray Tone Difference Matrix quantifies the difference between a gray value and the average gray value
of its neighbours within distance $\delta$. The sum of absolute differences for gray level $i$ is stored in the matrix.
Let $\textbf{X}\ *{gl}$ be a set of segmented voxels and $x*\ {gl}(j_x,j_y,j\ *z) \in \textbf{X}*\ {gl}$ be the gray level of a voxel at postion
$(j_x,j_y,j_z)$, then the average gray level of the neigbourhood is:

$$
    \bar{A}_i = \bar{A}(j_x, j_y, j\ *z) 
    = \displaystyle\frac{1}{W} \displaystyle\sum*\ {k\ *x=-\delta}^{\delta}\displaystyle\sum*\ {k_y=-\delta}^{\delta}

.. code-block::

   \displaystyle\sum_{k_z=-\delta}^{\delta}{x_{gl}(j_x+k_x, j_y+k_y, j_z+k_z)}, \\\text{ where } (k_x,k_y,k_z)\neq(0,0,0) \\ \text{ and } x_{gl}(j_x+k_x, j_y+k_y, j_z+k_z) \in \textbf{X}_{gl}

$$

Here, $W$ is the number of voxels in the neighbourhood that are also in $\textbf{X}_{gl}$.

As a two dimensional example, let the following matrix $\textbf{I}$ represent a 4x4 image,
having 5 discrete grey levels, but no voxels with gray level 4:

$$
    \textbf{I} = \begin{bmatrix}
    1 & 2 & 5 & 2\
    3 & 5 & 1 & 3\
    1 & 3 & 5 & 5\
    3 & 1 & 1 & 1\end{bmatrix}
$$

The following NGTDM can be obtained:

$$
    \begin{array}{cccc}
    i & n_i & p_i & s_i\
    \hline
    1 & 6 & 0.375 & 13.35\
    2 & 2 & 0.125 & 2.00\
    3 & 4 & 0.25  & 2.63\
    4 & 0 & 0.00  & 0.00\
    5 & 4 & 0.25  & 10.075\end{array}
$$

6 pixels have gray level 1, therefore:

$s_1 = |1-10/3| + |1-30/8| + |1-15/5| + |1-13/5| + |1-15/5| + |1-11/3| = 13.35$

For gray level 2, there are 2 pixels, therefore:

$s_2 = |2-15/5| + |2-9/3| = 2$

Similar for gray values 3 and 5:

$s_3 = |3-12/5| + |3-18/5| + |3-20/8| + |3-5/3| = 3.03 \
s_5 = |5-14/5| + |5-18/5| + |5-20/8| + |5-11/5| = 10.075$

Let:

$n\ *i$ be the number of voxels in $X*\ {gl}$ with gray level $i$

$N\ *{v,p}$ be the total number of voxels in $X*\ {gl}$ and equal to $\sum{n\ *i}$ (i.e. the number of voxels
with a valid region; at least 1 neighbor). $N*\ {v,p} \leq N_p$, where $N_p$ is the total number of voxels in the ROI.

$p_i$ be the gray level probability and equal to $n_i/N_v$

$$
s_i = \left{ {\begin{array} {rcl} \sum^{n_i}{|i-\bar{A}_i|} & \text for & n_i \neq 0 \
0 \text { for } & n_i = 0 \end{array}}\right.
$$
be the sum of absolute differences for gray level $i$.

$N_g$ be the number of discrete gray levels

$N_{g,p}$ be the number of gray levels where $p_i \neq 0$

Coarseness
----------

NGTDM_COARSENESS $= \displaystyle \frac{1}{\sum^{N\ *g}*\ {i=1}{p\ *{i}s*\ {i}}}$

Contrast
--------

NGTDM\ *CONTRAST $= \left(\frac{1}{N*\ {g,p}(N_{g,p}-1)}\displaystyle\sum^{N\ *g}*\ {i=1}\displaystyle\sum^{N\ *g}*\ {j=1}{p\ *{i}p*\ {j}(i-j)^2}\right)
    \left(\frac{1}{N_{v,p}}\displaystyle\sum^{N\ *g}*\ {i=1}{s_i}\right)$ where $p_i \neq 0$, $p_j \neq 0$

Busyness
--------

NGTDM_BUSYNESS $= \frac{\sum^{N\ *g}*\ {i = 1}{p\ *{i}s*\ {i}}}{\sum^{N\ *g}*\ {i = 1}\sum^{N\ *g}*\ {j = 1}{|ip_i - jp_j|}}$ where $p_i \neq 0$, $p_j \neq 0$

Complexity
----------

NGTDM\ *COMPLEXITY $= \frac{1}{N*\ {v,p}}\displaystyle\sum^{N\ *g}*\ {i = 1}\displaystyle\sum^{N\ *g}*\ {j = 1}{|i - j|
    \frac{p\ *{i}s*\ {i} + p\ *{j}s*\ {j}}{p_i + p_j}}$ where $p_i \neq 0, p_j \neq 0$

Strength
--------

NGTDM_STRENGTH $= \displaystyle \frac{\sum^{N\ *g}*\ {i = 1}\sum^{N\ *g}*\ {j = 1}{(p_i + p_j)(i-j)^2}}{\sum^{N\ *g}*\ {i = 1}{s_i}}$ where $p_i \neq 0, p_j \neq 0$

References
----------

Amadasun M, King R; Textural features corresponding to textural properties; Systems, Man and Cybernetics, IEEE Transactions on 19:1264-1274 (1989). doi: 10.1109/21.44046
