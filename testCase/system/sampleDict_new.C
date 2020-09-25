/*--------------------------------*- C++ -*----------------------------------*\
| =========                 |                                                 |
| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
|  \\    /   O peration     | Version:  3.0.1                                 |
|   \\  /    A nd           | Web:      www.OpenFOAM.org                      |
|    \\/     M anipulation  |                                                 |
\*---------------------------------------------------------------------------*/
FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionarxyz;
    location    system;
    object      sampleDict;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Set output format : choice of
//      xmgr
//      jplot
//      gnuplot
//      raw
//      vtk
//      ensight
//      csv

type      sets;
libs ("libsampling.so");

interpolationScheme cellPoint;

setFormat csv;

// Surface output format. Choice of
//      null        : suppress output
//      ensight     : Ensight Gold format, one field per case file
//      foamFile    : separate points, faces and values file
//      dx          : DX scalar or vector format
//      vtk         : VTK ascii format
//      raw         : x y z value format for use with e.g. gnuplot 'splot'.
//
// Note:
// other formats such as obj, stl, etc can also be written (by proxy)
// but without any values!
// surfaceFormat vtk;

// optionally define extra controls for the output formats
// formatOptions
// {
//     ensight
//     {
//         format  ascii;
//     }
// }

// interpolationScheme. choice of
//      cell          : use cell-centre value onlxyz; constant over cells
//                      (default)
//      cellPoint     : use cell-centre and vertex values
//      cellPointFace : use cell-centre, vertex and face values.
//      pointMVC      : use point values only (Mean Value Coordinates)
//      cellPatchConstrained : like 'cell' but uses cell-centre except on
//                             boundary faces where it uses the boundary value.
//                             For use with e.g. patchCloudSet.
// 1] vertex values determined from neighbouring cell-centre values
// 2] face values determined using the current face interpolation scheme
//    for the field (linear, gamma, etc.)

// Fields to sample.
fields
(
      Ux_mean
      T
      // mag(U)
);

// Set sampling definition: choice of
//      uniform             evenly distributed points on line
//      face                one point per face intersection
//      midPoint            one point per cell, inbetween two face intersections
//      midPointAndFace     combination of face and midPoint
//
//      polyLine            specified points, not nessecary on line, uses
//                          tracking
//      cloud               specified points, uses findCell
//      triSurfaceMeshPointSet  points of triSurface
//
// axis: how to write point coordinate. Choice of
// - x/y/z: x/y/z coordinate only
// - xyz: three columns
//  (probably does not make sense for anything but raw)
// - y: y from start of sampling line (if uses line) or
//             y from first specified sampling point
//
// type specific:
//      uniform, face, midPoint, uniform : start and start coordinate
//      uniform: extra number of sampling points
//      polyLine, cloud: list of coordinates
//      patchCloud: list of coordinates and set of patches to look for nearest
//      patchSeed: random sampling on set of patches. Points slightly off
//                 face centre.
sets
(
lineY0
  {
    type      uniform;
    axis      xyz;
    start    (0.001 0.0175 0.);
    end    (0.001 0.019 0.);
    nPoints    200;
  }
lineY1
  {
    type      uniform;
    axis      xyz;
    start    (0.002 0.0175 0.);
    end    (0.002 0.019 0.);
    nPoints    200;
  }
lineY2
  {
    type      uniform;
    axis      xyz;
    start    (0.003 0.0175 0.);
    end    (0.003 0.019 0.);
    nPoints    200;
  }
lineY3
  {
    type      uniform;
    axis      xyz;
    start    (0.004 0.0175 0.);
    end    (0.004 0.019 0.);
    nPoints    200;
  }
lineY4
  {
    type      uniform;
    axis      xyz;
    start    (0.005 0.0175 0.);
    end    (0.005 0.019 0.);
    nPoints    200;
  }
lineY5
  {
    type      uniform;
    axis      xyz;
    start    (0.006 0.0175 0.);
    end    (0.006 0.019 0.);
    nPoints    200;
  }
lineY6
  {
    type      uniform;
    axis      xyz;
    start    (0.007 0.0175 0.);
    end    (0.007 0.019 0.);
    nPoints    200;
  }
);