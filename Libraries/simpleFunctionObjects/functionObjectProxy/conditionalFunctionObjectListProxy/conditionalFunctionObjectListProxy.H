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
    conditionalFunctionObjectListProxy

Description
    Basis for the other function objects here. Evaluates the most common options

SourceFiles
    conditionalFunctionObjectListProxy.C

Contributors/Copyright:
    2011, 2013, 2016-2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

#ifndef conditionalFunctionObjectListProxy_H
#define conditionalFunctionObjectListProxy_H

#include "functionObjectListProxy.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class conditionalFunctionObjectListProxy Declaration
\*---------------------------------------------------------------------------*/

class conditionalFunctionObjectListProxy
:
    public functionObjectListProxy
{
    // Private Member Functions

    //- Disallow default bitwise copy construct
    conditionalFunctionObjectListProxy(const conditionalFunctionObjectListProxy&);

    //- Disallow default bitwise assignment
    void operator=(const conditionalFunctionObjectListProxy&);

    autoPtr<functionObjectListProxy> else_;

    autoPtr<dictionary> elseDict_;

    //- read the else-part
    void readElse(const dictionary &dict);
protected:

    //- the actual conition that determines whether the FO should be executed
    virtual bool condition()=0;

public:

    //- Runtime type information
    TypeName("conditionalFunctionObjectListProxy");


    // Constructors

    //- Construct from components
    conditionalFunctionObjectListProxy
    (
        const word&,
        const Time&,
        const dictionary&
    );

    // Member Functions

    //- start is called at the start of the time-loop
    virtual bool start();

    //- execute is called at each ++ or += of the time-loop
    virtual bool execute(const bool forceWrite);

    //- Called when Time::run() determines that the time-loop exits.
    //  By default it simply calls execute().
    virtual bool end();

    //- Read and set the function object if its data have changed
    virtual bool read(const dictionary&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
