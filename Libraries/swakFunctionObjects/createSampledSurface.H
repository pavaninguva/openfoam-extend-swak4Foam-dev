/*---------------------------------------------------------------------------*\
|                       _    _  _     ___                       | The         |
|     _____      ____ _| | _| || |   / __\__   __ _ _ __ ___    | Swiss       |
|    / __\ \ /\ / / _` | |/ / || |_ / _\/ _ \ / _` | '_ ` _ \   | Army        |
|    \__ \\ V  V / (_| |   <|__   _/ / | (_) | (_| | | | | | |  | Knife       |
|    |___/ \_/\_/ \__,_|_|\_\  |_| \/   \___/ \__,_|_| |_| |_|  | For         |
|                                                               | OpenFOAM    |
-------------------------------------------------------------------------------
License
    This file is part of swak4Foam.

    swak4Foam is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    swak4Foam is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with swak4Foam; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    createSampledSurface

Description
    Function object creates a sampledSurface and puts it into a repository
    to be used by others

SourceFiles
    createSampledSurface.C

Contributors/Copyright:
    2010, 2013-2014, 2016, 2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>
    2013 Bruno Santos <wyldckat@gmail.com>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

#ifndef createSampledSurface_H
#define createSampledSurface_H

#include "primitiveFieldsFwd.H"
#include "pointFieldFwd.H"

#include "swak.H"

namespace Foam
{
// Forward declaration of classes
class objectRegistry;
class dictionary;
class mapPolyMesh;
class polyMesh;

class createSampledSurface
{
    //- Disallow default bitwise copy construct
    createSampledSurface(const createSampledSurface&);

    //- Disallow default bitwise assignment
    void operator=(const createSampledSurface&);

protected:

    //- are we working?
    bool active_;

    //- mesh where the surface goes
    const objectRegistry& obr_;

    void redoSurface();

    word surfaceName_;

public:

    //- Runtime type information
    TypeName("createSampledSurface");


    // Constructors

    //- Construct for given objectRegistry and dictionary.
    //  Allow the possibility to load fields from files
    createSampledSurface
    (
        const word& name,
        const objectRegistry&,
        const dictionary&,
        const bool loadFromFiles = false
    );


    //- Destructor
    virtual ~createSampledSurface();


    // Member Functions

    //- Called when time was set at the end of the Time::operator++
    virtual void timeSet();

    //- Read the forces data
    virtual void read(const dictionary&);

    //- Execute, currently does nothing
    virtual void execute();

    //- Execute at the final time-loop, currently does nothing
    virtual void end();

    //- Write the forces
#ifdef FOAM_IOFILTER_WRITE_NEEDS_BOOL
    virtual bool write();
#else
    virtual void write();
#endif

    //- Update for changes of mesh
    virtual void updateMesh(const mapPolyMesh&);

    //- Update for changes of mesh
#ifdef FOAM_MOVEPOINTS_GETS_POLYMESH
    virtual void movePoints(const polyMesh&);
#else
    virtual void movePoints(const pointField&);
#endif

    //- Clear all data
    void clearData();
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif
