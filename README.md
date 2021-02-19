# HilbertCurve
Creating Hilberts Curves using MFC - 2020

## About
This was one of the most fun projects that I have ever made.
This project was the final project of an OOP course and used MFC framework.
This project implements a Hilbert curve structure, triangle Hilbert curve, and colored Hilbert curve.

## Project Structure
* All the OOPTask4MFC*, targetver.h, resource.h, pch.*, framework.h, MainFrm.h files and res directory are the builtin files of MFC framework
* CartesianDirections.h contain a rnum class of directions
* Color.* represent a single color
* ColorGradient.* gets number of colors and creates a gradient between them
* Point.* represent a single point in the 2d plane
* Line.* represent a line in the 2d plane
 * LineWithPos is a line with direction
* Curve.* is an abstract template which all the curves will inherit from
 * HilbertCurve.* implementation of Hilbert curve
  * HilbertCurveColor.* Abstract class of colored Hilbert curve
   * HilbertCurveColorLine.* implementation of Hilbert curve with colored lines
   * HilbertCurveColorPoints.* implementation of Hilbert curve with colored points
 * TriangleHilbertCurve.* implementation of triangle Hilbert curve
* HilbertCurveState.hse save the state of the current objects
   
