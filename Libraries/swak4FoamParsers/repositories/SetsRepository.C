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

Contributors/Copyright:
    2012-2013, 2015-2016, 2018 Bernhard F.W. Gschaider <bgschaid@hfd-research.com>
    2018 Mark Olesen <Mark.Olesen@esi-group.com>

 SWAK Revision: $Id$
\*---------------------------------------------------------------------------*/

#include "SetsRepository.H"
#include "writer.H"

#include "polyMesh.H"
#include "meshSearch.H"

#include "swakTime.H"

namespace Foam {

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

defineTypeNameAndDebug(SetsRepository, 0);

SetsRepository *SetsRepository::repositoryInstance(NULL);

SetsRepository::SetsRepository(const IOobject &o)
    :
    RepositoryBase(o)
{
}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

SetsRepository::~SetsRepository()
{
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

SetsRepository &SetsRepository::getRepository(const objectRegistry &obr)
{
    SetsRepository*  ptr=repositoryInstance;

    if(debug) {
        Pout << "SetsRepository: asking for Singleton" << endl;
    }

    if(ptr==NULL) {
        Pout << "swak4Foam: Allocating new repository for sampledSets\n";

        ptr=new SetsRepository(
            IOobject(
                "swakSets",
                obr.time().timeName(),
                "setRepository",
                obr.time(),
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            )
        );
    }

    repositoryInstance=ptr;

    return *repositoryInstance;
}

sampledSet &SetsRepository::getSet(
    const word &name,
    const polyMesh &mesh
)
{
    if(debug) {
        Pout << "SetsRepository: Lookuing up" << name << " (assuming it exists)" << endl;
    }

    sampledSet &found=*(sets_[name]);

    if((&mesh)!=(&(found.mesh()))) {
        FatalErrorIn("SampledSet &SetsRepository::getSet")
            << "Found a mesh named " << name << " which is not for the mesh "
                << mesh.name() << "but for the mesh " << found.mesh().name()
                << endl
                << exit(FatalError);
    }

    return found;
}

sampledSet &SetsRepository::getSet(
    const dictionary &dict,
    const polyMesh &mesh
)
{
    word name(dict.lookup("setName"));

    if(debug) {
        Pout << "SetsRepository: getting set " << name << endl;
    }

    if(sets_.found(name)) {
        if(debug) {
            Pout << "SetsRepository: " << name << " already exists" << endl;
        }

        if(dict.found("set")) {
            WarningIn("SampledSet &SetsRepository::getSet")
                << "Already got a set named " << name
                    << ". There is a specification for the set here "
                    << "which is ignored. It is: " << endl
                    << dict.subDict("set") << endl;
        }

        return getSet(name,mesh);
    } else {
        if(debug) {
            Pout << "SetsRepository: " << name << " does not exist" << endl;
        }
        sets_.insert(
            name,
            sampledSet::New(
                name,
                mesh,
                getSearch(mesh),
                dict.subDict("set")
#ifdef FOAM_HASH_PTR_LIST_ACCEPTS_NO_RAW_POINTERS
            )
#else
            ).ptr()
#endif
        );

        if(debug) {
            Pout << "Created set " << name << " :" << endl;
            sets_[name]->write(Pout);
            Pout << endl;
        }

        bool writeSet=dict.lookupOrDefault<bool>("autoWriteSet",false);
        bool writeSetNow=dict.lookupOrDefault<bool>("writeSetOnConstruction",false);
        if(
            writeSet
            ||
            writeSetNow
        ) {
            word format(dict.lookup("setFormat"));

            // Just to check whether the format actually exists
            autoPtr<writer<scalar> > theWriter(
                writer<scalar>::New(format)
            );

            if(writeSet) {
                formatNames_.insert(name,format);
            }
            if(writeSetNow) {
                sampledSet &set=*sets_[name];

                fileName fName(theWriter->getFileName(set,wordList(0)));
                if(!exists(this->path())) {
                    mkDir(this->path());
                }
                OFstream o(this->path()/("geometry_AtCreation_"+fName));
                Info << "Writing set " << name << " to " << o.name() << endl;
                theWriter->write(
                    set,
                    wordList(0),
                    List<const Field<scalar> *>(0),
                    o
                );
            }
        }

        return *sets_[name];
    }
}

meshSearch &SetsRepository::getSearch(
    const polyMesh &mesh
)
{
    word name(mesh.name());

    if(debug) {
        Pout << "SetsRepository: getting meshSearch " << name << endl;
    }

    if(meshSearches_.found(name)) {
        if(debug) {
            Pout << "SetsRepository: meshSearch for mesh " << name << " already exists" << endl;
        }

        meshSearch &found=*(meshSearches_[name]);

        if((&mesh)!=(&(found.mesh()))) {
        FatalErrorIn("SampledSet &SetsRepository::getSearch")
            << "Found a mesh named " << name << " which is not for the mesh "
                << mesh.name() << "but for the mesh " << found.mesh().name()
                << endl
                << exit(FatalError);
        }

        return found;
    } else {
        if(debug) {
            Pout << "SetsRepository: meshSearch for mesh " << name << " does not exist" << endl;
        }
        meshSearches_.insert(
            name,
#ifdef FOAM_HASH_PTR_LIST_ACCEPTS_NO_RAW_POINTERS
            autoPtr<meshSearch>(
#endif
                new meshSearch(mesh)
#ifdef FOAM_HASH_PTR_LIST_ACCEPTS_NO_RAW_POINTERS
            )
#endif
        );

        return *meshSearches_[name];
    }
}

void SetsRepository::updateRepo()
{
}

bool SetsRepository::writeData(Ostream &f) const
{
    if(debug) {
        Info << "SetsRepository::write()" << endl;
    }

    f << sets_;

    typedef HashTable<word> wordWord;

    forAllConstIter(wordWord,formatNames_,it) {
        const word &name=it.key();
        const word &format=it();

        const sampledSet &set=*sets_[name];

        autoPtr<writer<scalar> > theWriter(
            writer<scalar>::New(format)
        );

        fileName fName(theWriter->getFileName(set,wordList(0)));
        OFstream o(f.name().path()/("geometry_"+fName));

        theWriter->write(
            set,
            wordList(0),
            List<const Field<scalar> *>(0),
            o
        );
    }

    return true;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

} // namespace

// ************************************************************************* //
