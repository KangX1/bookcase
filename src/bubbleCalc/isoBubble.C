/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2013 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "isoBubble.H"
#include "error.H"
#include "volPointInterpolation.H"
#include <iomanip>
#include <sstream>
//#include "vtkSurfaceWriter.H"
#include "MeshedSurfaceProxyCore.C"

namespace Foam {

    // Specialize the MeshedSurfaceProxy template with labelledTri for a face.
    makeSurface(MeshedSurfaceProxy, labelledTri)

namespace bookExamples {


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

isoBubble::isoBubble
(
    const IOobject& io, 
    const volScalarField& bubbleField, 
    bool isTime , 
    label timeIndexPad
)
    : 
        regIOobject(io, isTime), 
        isoFieldPtr_(&bubbleField),
        isoPointField_(bubbleField.mesh().nPoints(),0), 
        bubblePtr_(0),
        timeIndexPad_(timeIndexPad)
{}

isoBubble::isoBubble(const isoBubble& copy)
    :
        regIOobject(copy), 
        isoFieldPtr_(copy.isoFieldPtr_),
        isoPointField_(copy.isoPointField_),
        bubblePtr_(0),
        timeIndexPad_(copy.timeIndexPad_)
{}

// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * * //

isoBubble::~isoBubble()
{
    clearPtrData(); 
}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void isoBubble::setBubbleField(const volScalarField& bubbleField)
{
    isoFieldPtr_ = &bubbleField; 
    isoPointField_.resize(bubbleField.mesh().nPoints()); 
}

void isoBubble::reconstruct()
{
    // TODO: make the volPoint interpolation static for the class: assuming execution
    // on the same mesh. 
    // Interpolate the track field to the points using volPointInterpolation. 
    volPointInterpolation pointInterpolation (isoFieldPtr_->mesh());
    
    // Reconstruct the bubble using both fields.
    isoPointField_ = static_cast<scalarField &> 
        (
            pointInterpolation.interpolate(*isoFieldPtr_)()
        );

    // Create the new isoSurface.
    bubblePtr_ = new isoSurface (*isoFieldPtr_, isoPointField_, 0, true); 
}

bool isoBubble::write() const
{
    // Create the path to the instance directory.
    mkDir(path());

    // Get the fileName as the std::string
    std::string outFileName = static_cast<const std::string&> (objectPath()); 
    // We need a string stream and the std:: manipulators since setfill is missing in
    // OpenFOAM 
    std::stringstream ss; 

    // Get the reference to the time from the tracked field.
    const Time& runTime = isoFieldPtr_->time(); 
    // Get the time index. 
    label timeIndex = runTime.timeIndex(); 
    // Padd the time index with zeros. 
    ss << outFileName << "-" << std::setw(timeIndexPad_) << std::setfill('0') 
        << timeIndex << ".vtk";

    // Update the file name from the stuff in stringstream. 
    outFileName = ss.str();  

    if (OFstream::debug)
    {
        Info<< "regIOobject::write() : "
            << "writing file " << outFileName << endl; 
    }

    // Get const references to the bubble mesh data.  
    const pointField& bubblePoints = bubblePtr_->points(); 
    const List<labelledTri>&  bubbleFaces = bubblePtr_->localFaces(); 

    // Write the isoSurface using a MeshedSurfaceProxy class. 
    MeshedSurfaceProxy<labelledTri> surfaceWriter (bubblePoints, bubbleFaces);

    surfaceWriter.write(path() + outFileName);
    return true;
}

bool isoBubble::writeData(Ostream& os) const
{

    return true;
}

// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

void isoBubble::operator=(const isoBubble& rhs)
{
    // Check for assignment to self
    if (this == &rhs)
    {
        FatalErrorIn("isoBubble::operator=(const isoBubble&)")
            << "Attempted assignment to self"
            << abort(FatalError);
    }

    // Track the field that the other bubble is tracking.
    isoFieldPtr_ = rhs.isoFieldPtr_; 

    // Make a deep copy of the point scalar field field. 
    isoPointField_ = rhs.isoPointField_; 
    // Make a deep copy of the bubble iso-surface.
    bubblePtr_ = new isoSurface(*rhs.bubblePtr_);
    // Make a deep copy of the timeIndex pad.
    timeIndexPad_ = rhs.timeIndexPad_;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace bookExamples 


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// ************************************************************************* //
